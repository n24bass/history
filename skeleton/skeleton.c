// *** skeleton.c *****************************************************
// this file implements the main loop of skeleton, where we either
// wait for and then process administrative commands, or poll the
// atached USB MST device.

#include "main.h"

// *** ftdi interface ***

// this is the command line we just received from the user console
char *volatile main_command;

// this function is called by the transport when a new command
// command line has been received from the user.
static void
main_command_cbfn(char *command)
{
    // pass the command to the run loop
    assert(! main_command);
    main_command = command;
}

// this function is called by the transport when the user presses
// Ctrl-C.
static void
main_ctrlc_cbfn(void)
{
}

// this function is called by the transport when the USB device
// is reset.
static void
main_reset_cbfn(void)
{
}

// *** command processing ***

enum cmdcode {
    command_clone,  // [run]
    command_connect, // nnn
    command_help,
    command_nodeid,
    command_reset,
    command_upgrade,
    command_uptime
};

static
struct commands {
    char *command;
    enum cmdcode code;
} commands[] = {
    "clone", command_clone,
    "connect", command_connect,
    "help", command_help,
    "nodeid", command_nodeid,
    "reset", command_reset,
    "upgrade", command_upgrade,
    "uptime", command_uptime
};

static
void
basic_trim(IN OUT char **p)
{
    // advance *p past any leading spaces
    while (isspace(**p)) {
        (*p)++;
    }
}

static
bool
basic_char(IN OUT char **text, IN char c)
{
    if (**text != c) {
        return false;
    }

    // advance *text past c
    (*text)++;

    basic_trim(text);
    return true;
}

static
bool
basic_word(IN OUT char **text, IN char *word)
{
    int len;

    len = strlen(word);

    if (strncmp(*text, word, len)) {
        return false;
    }

    // advance *text past word
    (*text) += len;

    basic_trim(text);
    return true;
}

static
bool
basic_const(IN OUT char **text, OUT int *value_out)
{
    int value;

    if (! isdigit((*text)[0])) {
        return false;
    }

    // parse constant value and advance *text past constant
    value = 0;
    while (isdigit((*text)[0])) {
        value = value*10 + (*text)[0] - '0';
        (*text)++;
    }

    *value_out = value;
    basic_trim(text);
    return true;
}

static char *help_general =
"commands:\n"
"  clone [run]\n"
"  connect <nodeid>\n"
"  help\n"
"  reset\n"
"  upgrade\n"
"  uptime\n"
"\n"
"for more information:\n"
"  help about\n"
"  help clone\n"
"  help zigbee\n"
;

static char *help_about =
#if MCF52233
"Welcome to Skeleton for Freescale MCF52233 v" VERSION "!\n"
#elif MCF52221
"Welcome to Skeleton for Freescale MCF52221 v" VERSION "!\n"
#else
#error
#endif
"http://www.cpustick.com\n"
#if INCOMPAT
"incompatible\n"
#endif
#if COMPAT
"compatible\n"
#endif
;

static char *help_clone =
"clone cable:\n"
"  master     slave\n"
"  ---------  ----------------\n"
"  qspi_clk   qspi_clk (ezpck)\n"
"  qspi_din   qspi_dout (ezpq)\n"
"  qspi_dout  qspi_din (ezpd)\n"
"  qspi_cs0   rcon* (ezpcs*)\n"
"  scl        rsti*\n"
"  vbus       vbus\n"
"  vdd        vdd\n"
;

static char *help_zigbee =
"zigbee cable:\n"
"  MCU        MC1320X\n"
"  ---------  -------\n"
"  qspi_clk   spiclk\n"
"  qspi_din   miso\n"
"  qspi_dout  mosi\n"
"  qspi_cs0   ce*\n"
"  irq4*      irq*\n"
"  scl        rst*\n"
"  sda        rxtxen\n"
"  vss        vss\n"
"  vdd        vdd\n"
;

static
void
help(IN char *text_in)
{
    char *p;
    char *text;
    char line[BASIC_LINE_SIZE];

    text = text_in;
    
    // while there is more help to print...
    while (*text) {
        // print the next line of help
        p = strchr(text, '\n');
        assert(p);
        assert(p-text < BASIC_LINE_SIZE);
        memcpy(line, text, p-text);
        line[p-text] = '\0';
        printf("%s\n", line);
        text = p+1;
    }

#if ! _WIN32
    if (text_in == help_about) {
        printf("(checksum 0x%x)\n", flash_checksum);
        if (! SECURE) {
            printf("NOT SECURE\n");
        }
    }
#endif
}

// this function implements the skeleton command interpreter.
static
void
command_run(char *text_in)
{
    int t;
    int d;
    int h;
    int m;
    int cmd;
    int len;
    int nodeid;
    bool boo;
    char *text;

    text = text_in;
    basic_trim(&text);
    
    if (! *text) {
        return;
    }
    
    for (cmd = 0; cmd < LENGTHOF(commands); cmd++) {
        len = strlen(commands[cmd].command);
        if (! strncmp(text, commands[cmd].command, len)) {
            break;
        }
    }

    if (cmd != LENGTHOF(commands)) {
        text += len;
    }
    basic_trim(&text);

    switch (cmd) {
        case command_clone:
            boo = false;
            if (basic_word(&text, "run")) {
                boo = true;
            }
            if (*text) {
                goto XXX_ERROR_XXX;
            }

            help(help_about);
            printf("cloning...\n");
            clone(boo);
            break;
            
        case command_connect:
            if (! zb_present) {
                printf("zigbee not present\n");
            } else if (zb_nodeid == -1) {
                printf("zigbee nodeid not set\n");
            } else {
                if (! basic_const(&text, &nodeid) || nodeid == -1) {
                    goto XXX_ERROR_XXX;
                }
                if (*text) {
                    goto XXX_ERROR_XXX;
                }
                
                printf("press Ctrl-D to disconnect\n");

                assert(main_command);
                main_command = NULL;
                terminal_command_ack(false);

                terminal_rxid = nodeid;
                terminal_txid = -1;
                
                while (terminal_rxid != -1) {
                    terminal_poll();
                    zb_poll();
                }
            }
            break;

        case command_help:
            if (! *text) {
                help(help_general);
            } else if (basic_word(&text, "about")) {
                help(help_about);
            } else if (basic_word(&text, "clone")) {
                help(help_clone);
            } else if (basic_word(&text, "zigbee")) {
                help(help_zigbee);
            } else {
                goto XXX_ERROR_XXX;
            }
            break;

        case command_nodeid:
            if (*text) {
                if (basic_word(&text, "none")) {
                    nodeid = -1;
                } else {
                    if (! basic_const(&text, &nodeid) || nodeid == -1) {
                        goto XXX_ERROR_XXX;
                    }
                }
                if (*text) {
                    goto XXX_ERROR_XXX;
                }
                zb_nodeid = nodeid;
            } else {
                if (zb_nodeid == -1) {
                    printf("none\n");
                } else {
                    printf("%u\n", zb_nodeid);
                }
            }
            break;

        case command_reset:
            if (*text) {
                goto XXX_ERROR_XXX;
            }

#if ! _WIN32
            MCF_RCM_RCR = MCF_RCM_RCR_SOFTRST;
            asm { halt }
#endif
            break;

        case command_upgrade:
            // upgrade skeleton!
            flash_upgrade();
            break;

        case command_uptime:
            if (*text) {
                goto XXX_ERROR_XXX;
            }

            t = seconds;
            d = t/(24*60*60);
            t = t%(24*60*60);
            h = t/(60*60);
            t = t%(60*60);
            m = t/(60);
            printf("%dd %dh %dm\n", d, h, m);
            break;

        default:
            goto XXX_ERROR_XXX;
            break;
    }
    return;

XXX_ERROR_XXX:
    terminal_command_error(text-text_in);
}

#if MCF52233
extern void *rich_so;
#endif

// this function implements the main admin loop of skeleton,
// where we wait for and then process administrative commands.
static
void
main_run_admin(void)
{
    bool ready;
    bool autoend;
    static int first;

    // we just poll here waiting for commands
    for (;;) {
        terminal_poll();

        ready = 0;
        autoend = false;
        if (main_command) {
            terminal_poll();
            if (terminal_echo) {
                printf("\n");
            }
            command_run(main_command);
            ready = 1;
        }

        if (autoend || ready) {
            if (! first) {
                printf(" \n"); delay(1);  // revisit -- why???
                command_run("help about");
                first = 1;
            }
            printf("> ");
        }

        if (ready) {
            ready = 0;
            if (main_command) {
                main_command = NULL;
                terminal_command_ack(false);
            }
        }
    }
}

// this function implements the main loop of skeleton.
void
main_run(void)
{
    for (;;) {
#if MCF52221
        // if our usb device is attached...
        if (scsi_attached) {
            int rv;
            byte cdb[6];
            byte inq[37];
        
            memset(cdb, 0, sizeof(cdb));
            cdb[0] = 0x12;
            cdb[4] = sizeof(inq);
            do {
                rv = scsi_bulk_transfer(1, cdb, sizeof(cdb), inq, sizeof(inq));
                if (rv == 36) {
                    inq[sizeof(inq)] = '\0';
                    printf("found %s\n", inq+8);
                    led_unknown_progress();
                    delay(1000);
                }
            } while (rv == 36);
            usb_host_detach();
        }
        
        // if some other usb device is attached...
        if (other_attached) {
            int rv;
            struct setup setup;
            byte configuration[18];
            
            do {
                // get the first 9 bytes of the configuration descriptor
                usb_setup(1, SETUP_TYPE_STANDARD, SETUP_RECIP_DEVICE, REQUEST_GET_DESCRIPTOR, (CONFIGURATION_DESCRIPTOR<<8)|0, 0, sizeof(configuration), &setup);
                rv = usb_control_transfer(&setup, configuration, sizeof(configuration));
                if (rv > 0) {
                    assert(configuration[4]);
                
                    printf("found 0x%x.0x%x\n", configuration[14], configuration[15]);
                    led_unknown_progress();
                    delay(1000);
                }
            } while (rv > 0);
            usb_host_detach();
        }

        // if our usb host is attached...
        if (ftdi_attached) {
            main_run_admin();
        }
        
#elif MCF52233
        // if our network client is attached...
        if (rich_so) {
            main_run_admin();
        }
#else
#error
#endif
        terminal_poll();
    }
}

int
main_ip_address()
{
    // use dhcp
    return 0;
}

int
main_nodeid()
{
    // none
    return -1;
}

void
main_initialize()
{
    // if we're in device mode...
    if (! usb_host_mode) {
        // register device mode callbacks
        terminal_register(main_command_cbfn, main_ctrlc_cbfn);
    #if MCF52221
        ftdi_register(main_reset_cbfn);
    #endif
    }
}
