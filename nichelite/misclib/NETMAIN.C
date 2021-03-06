/*
 * FILENAME: netmain.c
 *
 *
 * Copyright 1997- 2006 By InterNiche Technologies Inc. All rights reserved
 *
 * Portions Copyright 1986 by Carnegie Mellon
 * Portions Copyright 1984 by the Massachusetts Institute of Technology
 *
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation and other 
 * materials related to such distribution and use acknowledge that 
 * the software was developed by the University of California, Berkeley.
 * The name of the University may not be used to endorse or promote 
 * products derived from this software without specific prior written 
 * permission. THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 * Rights, responsibilities and use of this software are controlled by
 * the agreement found in the "LICENSE.H" file distributed with this
 * source code.  "LICENSE.H" may not be removed from this distribution,
 * modified, enhanced nor references to it omitted.
 *
 *
 * Main file for the Generic Multitasking systems port of 
 * InterNiche TCP/IP package.
 *
 * MODULE: MISCLIB
 *
 * ROUTINES: prep_ifaces(), netmain(), 
 * ROUTINES: tcp_sleep(), tcp_wakeup(), 
 * ROUTINES: ...and all the "tk_xxx" application tasks
 *
 * Contents of this file are enabled when any
 * tasking system is in place (that is SUPERLOOP is disabled).
 *
 * PORTABLE: yes
 */

#define IN_NETMAIN_C    1  /* some ipport.h ports need to know this */

#include "license.h"
#include "ipport.h"

/* Multitasking systems should use these functions, however superloop
 * systems need to be able to ifdef it away
 */

#ifndef SUPERLOOP /* whole file can be ifdeffed out */

#ifdef OSPORT_H
#include OSPORT_H
#endif

/* various network entry points */
extern   char* ip_startup(void);
extern   void  inet_timer(void);
extern   void  netmain_init(void); /* initialize all modules */
extern   int   create_apptasks(void);
extern   int   prep_modules(void);

#ifdef DNS_CLIENT
#include "dns.h"
#endif

#ifdef TCP_ECHOTEST
extern   int   tcp_echo_init(void);
extern   void  tcp_echo_cleanup(void);
extern   void  tcp_echo_poll(void);
#endif

#ifdef TCP_CIPHERTEST
extern   int   tcp_cipher_init(void);
extern   void  tcp_cipher_cleanup(void);
extern   void  tcp_cipher_poll(void);
#endif

#ifdef PING_APP
void  ping_recv(void);     /* check for ping reply */
#endif

#ifdef USE_BROWSER
void  peg_check(void);     /* check for PEG events & post them */
#endif

extern   int      uart_yield;         /* in iuart.c */

/* include project header. Define this in ipport.h to point to a 
 * header file in your project directory.
 */
 
#ifndef OSPORT_H
#error Need to define OSPORT_H
#endif


#ifdef MINI_IP
#define net_system_exit (FALSE)
#else
extern int net_system_exit;   /* TRUE if system is shutting down */
#endif

#ifndef TK_RETURN_UNREACHABLE
#define TK_RETURN_UNREACHABLE() TK_RETURN_OK()
#endif


#ifndef APP_STACK_SIZE
#define APP_STACK_SIZE  4096  /* default on the large side */
#endif

#ifndef SYS_SHORT_SLEEP
#define SYS_SHORT_SLEEP 1
#endif


/* Define thread prototypes.  */

#ifndef NO_INET_STACK
TK_OBJECT(to_netmain);
TK_ENTRY(tk_netmain);
long     netmain_wakes  =  0;
#endif   /* NO_INET_STACK */

#ifndef NO_INET_TICK
TK_OBJECT(to_nettick);
TK_ENTRY(tk_nettick);
long     nettick_wakes  =  0;
#endif   /* NO_INET_TICK */

/* per-application thread definitions */

#ifdef PING_APP
TK_OBJECT(to_pingcheck);
TK_ENTRY(tk_pingcheck);
long     pingcheck_wakes   =  0;
#endif

#ifdef TCP_ECHOTEST
TK_OBJECT(to_echotest);
TK_ENTRY(tk_echotest);
long     echotest_wakes =  0;
#endif

#ifdef TCP_CIPHERTEST
TK_OBJECT(to_ciphertest);
TK_ENTRY(tk_ciphertest);
long     ciphertest_wakes =  0;
#endif

#ifdef USE_BROWSER
TK_OBJECT(to_browcheck);
TK_ENTRY(tk_browcheck);
long     browtask_wakes   =  0;
#endif

struct inet_taskinfo nettasks[]  =  {
#ifndef NO_INET_STACK
   {
      &to_netmain,   /* netmain should always be first in this array */
      "Inet main",
      tk_netmain,
      NET_PRIORITY,
      NET_STACK_SIZE,
   },
#endif   /* NO_INET_STACK */
#ifndef NO_INET_TICK
  
   {
      &to_nettick,
      "clock tick",
      tk_nettick,
      NET_PRIORITY,
      CLOCK_STACK_SIZE,
   },
#endif   /* NO_INET_TICK */
   /************** optional application threads ***************/
#ifdef PING_APP
   {
      &to_pingcheck,
      "PING client",
      tk_pingcheck,
      NET_PRIORITY,
      APP_STACK_SIZE,
   },
#endif
#ifdef TCP_ECHOTEST
   {
      &to_echotest,
      "tcp echo",
      tk_echotest,
      NET_PRIORITY,
      APP_STACK_SIZE,
   },
#endif

#ifdef TCP_CIPHERTEST
   {
      &to_ciphertest,
      "Crypto Engine Server",
      tk_ciphertest,
      NET_PRIORITY,
      APP_STACK_SIZE,
   },
#endif

#ifdef USE_BROWSER
   {
      &to_browcheck,
      "Browser",
      tk_browcheck,
      NET_PRIORITY,
      APP_STACK_SIZE*4,
   },
#endif
};

int      num_net_tasks  = sizeof(nettasks)/sizeof(struct inet_taskinfo);

int iniche_net_ready = FALSE;


/* FUNCTION: netmain()
 * 
 * PARAM1: 
 *
 * RETURNS: 
 */

int
netmain(void)
{
   int   i;
   int   e;

   iniche_net_ready = FALSE;

   e = prep_modules();

   /* Create the threads for net, timer, and apps */
   for (i = 0; i < num_net_tasks; i++)
   {
      e = TK_NEWTASK(&nettasks[i]);
      if (e != 0) 
      {
         dprintf("task create error\n");
         panic("netmain");
         return -1;  /* compiler warnings */
      }
   }

   e = create_apptasks();
   if (e != 0) 
   {
      dprintf("task create error\n");
      panic("netmain");
      return -1;  /* compiler warnings */
   }

   uart_yield = 1;

#ifndef NO_INET_STACK
#ifdef MAIN_TASK_IS_NET
   tk_netmain(TK_NETMAINPARM);
   panic("net task return");
   return -1;
#else
   return 0;
#endif
#endif   /* NO_INET_STACK */
}

/* FUNCTION: tk_netmain()
 *
 * Main thread for starting the net. After startup, it settles into
 * a loop handling received packets. This loop sleeps until a packet
 * has been queued in rcvdq; at which time it should be awakend by the
 * driver which queued the packet.
 *
 * PARAM1: n/a
 *
 * RETURNS: n/a
 */

#ifndef NO_INET_STACK
TK_ENTRY(tk_netmain)
{
   netmain_init(); /* initialize all modules */

   iniche_net_ready = TRUE;    /* let the other threads spin */

   for (;;)
   {
      TK_NETRX_BLOCK();
      netmain_wakes++;  /* count wakeups */

      /* see if there's newly received network packets */
      if (rcvdq.q_len)
         pktdemux();
      /* do not kill packet demux on net_system_exit. It may be
       * vital to a clean shutdown 
       */
   }
   USE_ARG(parm);  /* TK_ENTRY macro defines tk_netmain with 1 arg parm */
   TK_RETURN_UNREACHABLE();
}
#endif   /* NO_INET_STACK */



/* FUNCTION: tk_nettick
 * 
 * PARAM1: n/a
 *
 * RETURNS: n/a
 */

#ifdef DHCP_CLIENT
extern   int dhc_second(void);
#endif

#ifndef NO_INET_TICK
TK_ENTRY(tk_nettick)
{
   /* wait till the stack is initialized */
   while (!iniche_net_ready)
   {
      /* The DHCP Client state machine might need some cycles
       * at this point. This is needed when we start by sending a
       * request and then we receive a NAK. At this point the DHCP
       * client is reset to INIT state and dhc_second() needs to be
       * run to restart it.
       */
#ifdef DHCP_CLIENT
      dhc_second();
#endif
      TK_SLEEP(1);
   }

   for (;;)
   {
      TK_SLEEP(SYS_SHORT_SLEEP);
      nettick_wakes++;  /* count wakeups */
      inet_timer();  /* let various timeouts occur */
      /* do not kill timers on net_system_exit. They may be
       * vital to a clean shutdown 
       */
   }
   USE_ARG(parm);  /* TK_ENTRY macro defines tk_nettick with 1 arg parm */
   TK_RETURN_UNREACHABLE();
}
#endif   /* NO_INET_TICK */



/* the application threads which follow work on a "controlled 
 * polling" basis: they wake up periodically and poll for work. If 
 * there is outstanding work, the next wake is accellerated to give 
 * better performance under heavy loads. The FTP and Web tasks could 
 * aternativly be set up to use blocking sockets, in which case the 
 * loops below would only cann the "xxx_check()" routines - 
 * suspending would be handled by the TCP code. 
 */


/* FUNCTION: tk_pingcheck()
 * 
 * PARAM1: n/a
 *
 * RETURNS: n/a
 */

#ifdef PING_APP
extern   PING_INFO   pingq;

TK_ENTRY(tk_pingcheck)
{
   while (!iniche_net_ready)
      TK_SLEEP(1);

   for (;;)
   {
      ping_recv();         /* check for ping reply */
      TK_BLOCK();          /* block right here, upcall will wake us */
      pingcheck_wakes++;   /* count wakeups */
      if (net_system_exit)
         break;
   }
   TK_RETURN_OK();
}
#endif /* PING_APP */


/* FUNCTION: tk_echotest()
 * 
 * PARAM1: n/a
 *
 * RETURNS: n/a
 */

#ifdef TCP_ECHOTEST
TK_ENTRY(tk_echotest)
{
   int e;

   while (!iniche_net_ready)
      TK_SLEEP(1);

   e=tcp_echo_init();
   if ( e == SUCCESS )
   {
      exit_hook(tcp_echo_cleanup);
   }

   for (;;)
   {
      tcp_echo_poll();     /* This blocks on select() */
      tk_yield();          /* give up CPU in case it didn't block */
      echotest_wakes++;    /* count wakeups */

      if (net_system_exit)
         break;
   }
   TK_RETURN_OK();
}
#endif /* TCP_ECHOTEST */

/* FUNCTION: tk_ciphertest()
 * 
 * PARAM1: n/a
 *
 * RETURNS: n/a
 */

#ifdef TCP_CIPHERTEST
TK_ENTRY(tk_ciphertest)
{
   int e;

   while (!iniche_net_ready)
      TK_SLEEP(1);

   e=tcp_cipher_init();
   if ( e == SUCCESS )
   {
      exit_hook(tcp_cipher_cleanup);
   }

   for (;;)
   {
      tcp_cipher_poll();     /* This blocks on select() */
      tk_yield();          /* give up CPU in case it didn't block */
      ciphertest_wakes++;    /* count wakeups */

      if (net_system_exit)
         break;
   }
   TK_RETURN_OK();
}
#endif /* TCP_CIPHERTEST */



/* FUNCTION: tk_browcheck()
 * 
 * PARAM1: n/a
 *
 * RETURNS: n/a
 */

#ifdef USE_BROWSER

TK_ENTRY(tk_browcheck)
{
   while (!iniche_net_ready)
      TK_SLEEP(1);

   for (;;)
   {
      peg_check();         /* check for PEG messages/events */
      TK_BLOCK();          /* block right here, upcall will wake us */
      browtask_wakes++;   /* count wakeups */
      if (net_system_exit)
         break;
   }
   TK_RETURN_OK();
}
#endif /* USE_BROWSER */


#ifdef  TCPWAKE_RTOS

/* If we're using a tasking system that does not explicitly
 * support blocking on events (i.e. tcp_sleep()) add the support
 * here:
 */
#ifndef MAX_EVENTS
#define  MAX_EVENTS  12
#endif

/* declare an array of structs to store blocking events */

struct tk_wait_event
{
   void *   event;
   TK_OBJECT_REF(task);
};

struct tk_wait_event tk_eventlist[MAX_EVENTS];

/* debug counters */
long     tcp_no_taskslot   =  0;


/* FUNCTION: tcp_sleep()
 * 
 * PARAM1: void * event
 *
 * RETURNS: 
 */

void
tcp_sleep(void * event)
{
   int   i;

   /* search event array for an unused slot */
   for (i = 0; i < MAX_EVENTS; i++)
   {
      if (tk_eventlist[i].event == 0)     /* found a slot */
      {
         tk_eventlist[i].event = event;   /* save event to wake up on */
         tk_eventlist[i].task = TK_THIS;  /* save calling task */
         UNLOCK_NET_RESOURCE(NET_RESID);  /* free stack mutex */
         TK_BLOCK();                      /* suspend calling task */
         LOCK_NET_RESOURCE(NET_RESID);    /* we woke up - reenter stack */
         tk_eventlist[i].event = NULL;    /* clear array entry */
         return;
      }
   }
   /* fall to here if we ran out of free event slots. Best thing to do is
    * let system spin, then return to caller for another sleep test.
    */
   tcp_no_taskslot++;
   tk_yield();
}


/* FUNCTION: tcp_wakeup()
 * 
 * PARAM1: void * event
 *
 * RETURNS: 
 */

void
tcp_wakeup(void * event)
{
   int   i;

   /* search event array for blocked event */
   for (i = 0; i < MAX_EVENTS; i++)
   {
      if (tk_eventlist[i].event == event) /* found one */
         TK_WAKE_EVENT(tk_eventlist[i].task);   /* wake the task */
   }
}
#endif   /* TCPWAKE_RTOS */


#endif   /* SUPERLOOP - whole file can be ifdeffed out */


