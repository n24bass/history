/* ColdFire C Header File
 * Copyright Freescale Semiconductor Inc
 * All rights reserved.
 *
 * 2007/03/19 Revision: 0.91
 */

#ifndef __MCF52235_INTC_H__
#define __MCF52235_INTC_H__


/*********************************************************************
*
* Interrupt Controller (INTC)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_INTC0_IPRH                       (*(vuint32*)(&__IPSBAR[0xC00]))
#define MCF_INTC0_IPRL                       (*(vuint32*)(&__IPSBAR[0xC04]))
#define MCF_INTC0_IMRH                       (*(vuint32*)(&__IPSBAR[0xC08]))
#define MCF_INTC0_IMRL                       (*(vuint32*)(&__IPSBAR[0xC0C]))
#define MCF_INTC0_INTFRCH                    (*(vuint32*)(&__IPSBAR[0xC10]))
#define MCF_INTC0_INTFRCL                    (*(vuint32*)(&__IPSBAR[0xC14]))
#define MCF_INTC0_IRLR                       (*(vuint8 *)(&__IPSBAR[0xC18]))
#define MCF_INTC0_IACKLPR                    (*(vuint8 *)(&__IPSBAR[0xC19]))
#define MCF_INTC0_ICR01                      (*(vuint8 *)(&__IPSBAR[0xC41]))
#define MCF_INTC0_ICR02                      (*(vuint8 *)(&__IPSBAR[0xC42]))
#define MCF_INTC0_ICR03                      (*(vuint8 *)(&__IPSBAR[0xC43]))
#define MCF_INTC0_ICR04                      (*(vuint8 *)(&__IPSBAR[0xC44]))
#define MCF_INTC0_ICR05                      (*(vuint8 *)(&__IPSBAR[0xC45]))
#define MCF_INTC0_ICR06                      (*(vuint8 *)(&__IPSBAR[0xC46]))
#define MCF_INTC0_ICR07                      (*(vuint8 *)(&__IPSBAR[0xC47]))
#define MCF_INTC0_ICR08                      (*(vuint8 *)(&__IPSBAR[0xC48]))
#define MCF_INTC0_ICR09                      (*(vuint8 *)(&__IPSBAR[0xC49]))
#define MCF_INTC0_ICR10                      (*(vuint8 *)(&__IPSBAR[0xC4A]))
#define MCF_INTC0_ICR11                      (*(vuint8 *)(&__IPSBAR[0xC4B]))
#define MCF_INTC0_ICR12                      (*(vuint8 *)(&__IPSBAR[0xC4C]))
#define MCF_INTC0_ICR13                      (*(vuint8 *)(&__IPSBAR[0xC4D]))
#define MCF_INTC0_ICR14                      (*(vuint8 *)(&__IPSBAR[0xC4E]))
#define MCF_INTC0_ICR15                      (*(vuint8 *)(&__IPSBAR[0xC4F]))
#define MCF_INTC0_ICR16                      (*(vuint8 *)(&__IPSBAR[0xC50]))
#define MCF_INTC0_ICR17                      (*(vuint8 *)(&__IPSBAR[0xC51]))
#define MCF_INTC0_ICR18                      (*(vuint8 *)(&__IPSBAR[0xC52]))
#define MCF_INTC0_ICR19                      (*(vuint8 *)(&__IPSBAR[0xC53]))
#define MCF_INTC0_ICR20                      (*(vuint8 *)(&__IPSBAR[0xC54]))
#define MCF_INTC0_ICR21                      (*(vuint8 *)(&__IPSBAR[0xC55]))
#define MCF_INTC0_ICR22                      (*(vuint8 *)(&__IPSBAR[0xC56]))
#define MCF_INTC0_ICR23                      (*(vuint8 *)(&__IPSBAR[0xC57]))
#define MCF_INTC0_ICR24                      (*(vuint8 *)(&__IPSBAR[0xC58]))
#define MCF_INTC0_ICR25                      (*(vuint8 *)(&__IPSBAR[0xC59]))
#define MCF_INTC0_ICR26                      (*(vuint8 *)(&__IPSBAR[0xC5A]))
#define MCF_INTC0_ICR27                      (*(vuint8 *)(&__IPSBAR[0xC5B]))
#define MCF_INTC0_ICR28                      (*(vuint8 *)(&__IPSBAR[0xC5C]))
#define MCF_INTC0_ICR29                      (*(vuint8 *)(&__IPSBAR[0xC5D]))
#define MCF_INTC0_ICR30                      (*(vuint8 *)(&__IPSBAR[0xC5E]))
#define MCF_INTC0_ICR31                      (*(vuint8 *)(&__IPSBAR[0xC5F]))
#define MCF_INTC0_ICR32                      (*(vuint8 *)(&__IPSBAR[0xC60]))
#define MCF_INTC0_ICR33                      (*(vuint8 *)(&__IPSBAR[0xC61]))
#define MCF_INTC0_ICR34                      (*(vuint8 *)(&__IPSBAR[0xC62]))
#define MCF_INTC0_ICR35                      (*(vuint8 *)(&__IPSBAR[0xC63]))
#define MCF_INTC0_ICR36                      (*(vuint8 *)(&__IPSBAR[0xC64]))
#define MCF_INTC0_ICR37                      (*(vuint8 *)(&__IPSBAR[0xC65]))
#define MCF_INTC0_ICR38                      (*(vuint8 *)(&__IPSBAR[0xC66]))
#define MCF_INTC0_ICR39                      (*(vuint8 *)(&__IPSBAR[0xC67]))
#define MCF_INTC0_ICR40                      (*(vuint8 *)(&__IPSBAR[0xC68]))
#define MCF_INTC0_ICR41                      (*(vuint8 *)(&__IPSBAR[0xC69]))
#define MCF_INTC0_ICR42                      (*(vuint8 *)(&__IPSBAR[0xC6A]))
#define MCF_INTC0_ICR43                      (*(vuint8 *)(&__IPSBAR[0xC6B]))
#define MCF_INTC0_ICR44                      (*(vuint8 *)(&__IPSBAR[0xC6C]))
#define MCF_INTC0_ICR45                      (*(vuint8 *)(&__IPSBAR[0xC6D]))
#define MCF_INTC0_ICR46                      (*(vuint8 *)(&__IPSBAR[0xC6E]))
#define MCF_INTC0_ICR47                      (*(vuint8 *)(&__IPSBAR[0xC6F]))
#define MCF_INTC0_ICR48                      (*(vuint8 *)(&__IPSBAR[0xC70]))
#define MCF_INTC0_ICR49                      (*(vuint8 *)(&__IPSBAR[0xC71]))
#define MCF_INTC0_ICR50                      (*(vuint8 *)(&__IPSBAR[0xC72]))
#define MCF_INTC0_ICR51                      (*(vuint8 *)(&__IPSBAR[0xC73]))
#define MCF_INTC0_ICR52                      (*(vuint8 *)(&__IPSBAR[0xC74]))
#define MCF_INTC0_ICR53                      (*(vuint8 *)(&__IPSBAR[0xC75]))
#define MCF_INTC0_ICR54                      (*(vuint8 *)(&__IPSBAR[0xC76]))
#define MCF_INTC0_ICR55                      (*(vuint8 *)(&__IPSBAR[0xC77]))
#define MCF_INTC0_ICR56                      (*(vuint8 *)(&__IPSBAR[0xC78]))
#define MCF_INTC0_ICR57                      (*(vuint8 *)(&__IPSBAR[0xC79]))
#define MCF_INTC0_ICR58                      (*(vuint8 *)(&__IPSBAR[0xC7A]))
#define MCF_INTC0_ICR59                      (*(vuint8 *)(&__IPSBAR[0xC7B]))
#define MCF_INTC0_ICR60                      (*(vuint8 *)(&__IPSBAR[0xC7C]))
#define MCF_INTC0_ICR61                      (*(vuint8 *)(&__IPSBAR[0xC7D]))
#define MCF_INTC0_ICR62                      (*(vuint8 *)(&__IPSBAR[0xC7E]))
#define MCF_INTC0_ICR63                      (*(vuint8 *)(&__IPSBAR[0xC7F]))
#define MCF_INTC0_SWIACK                     (*(vuint8 *)(&__IPSBAR[0xCE0]))
#define MCF_INTC0_L1IACK                     (*(vuint8 *)(&__IPSBAR[0xCE4]))
#define MCF_INTC0_L2IACK                     (*(vuint8 *)(&__IPSBAR[0xCE8]))
#define MCF_INTC0_L3IACK                     (*(vuint8 *)(&__IPSBAR[0xCEC]))
#define MCF_INTC0_L4IACK                     (*(vuint8 *)(&__IPSBAR[0xCF0]))
#define MCF_INTC0_L5IACK                     (*(vuint8 *)(&__IPSBAR[0xCF4]))
#define MCF_INTC0_L6IACK                     (*(vuint8 *)(&__IPSBAR[0xCF8]))
#define MCF_INTC0_L7IACK                     (*(vuint8 *)(&__IPSBAR[0xCFC]))
#define MCF_INTC0_ICR(x)                     (*(vuint8 *)(&__IPSBAR[0xC41 + ((x-1)*0x1)]))
#define MCF_INTC0_LIACK(x)                   (*(vuint8 *)(&__IPSBAR[0xCE4 + ((x-1)*0x4)]))

#define MCF_INTC1_IPRH                       (*(vuint32*)(&__IPSBAR[0xD00]))
#define MCF_INTC1_IPRL                       (*(vuint32*)(&__IPSBAR[0xD04]))
#define MCF_INTC1_IMRH                       (*(vuint32*)(&__IPSBAR[0xD08]))
#define MCF_INTC1_IMRL                       (*(vuint32*)(&__IPSBAR[0xD0C]))
#define MCF_INTC1_INTFRCH                    (*(vuint32*)(&__IPSBAR[0xD10]))
#define MCF_INTC1_INTFRCL                    (*(vuint32*)(&__IPSBAR[0xD14]))
#define MCF_INTC1_IRLR                       (*(vuint8 *)(&__IPSBAR[0xD18]))
#define MCF_INTC1_IACKLPR                    (*(vuint8 *)(&__IPSBAR[0xD19]))
#define MCF_INTC1_ICR01                      (*(vuint8 *)(&__IPSBAR[0xD41]))
#define MCF_INTC1_ICR02                      (*(vuint8 *)(&__IPSBAR[0xD42]))
#define MCF_INTC1_ICR03                      (*(vuint8 *)(&__IPSBAR[0xD43]))
#define MCF_INTC1_ICR04                      (*(vuint8 *)(&__IPSBAR[0xD44]))
#define MCF_INTC1_ICR05                      (*(vuint8 *)(&__IPSBAR[0xD45]))
#define MCF_INTC1_ICR06                      (*(vuint8 *)(&__IPSBAR[0xD46]))
#define MCF_INTC1_ICR07                      (*(vuint8 *)(&__IPSBAR[0xD47]))
#define MCF_INTC1_ICR08                      (*(vuint8 *)(&__IPSBAR[0xD48]))
#define MCF_INTC1_ICR09                      (*(vuint8 *)(&__IPSBAR[0xD49]))
#define MCF_INTC1_ICR10                      (*(vuint8 *)(&__IPSBAR[0xD4A]))
#define MCF_INTC1_ICR11                      (*(vuint8 *)(&__IPSBAR[0xD4B]))
#define MCF_INTC1_ICR12                      (*(vuint8 *)(&__IPSBAR[0xD4C]))
#define MCF_INTC1_ICR13                      (*(vuint8 *)(&__IPSBAR[0xD4D]))
#define MCF_INTC1_ICR14                      (*(vuint8 *)(&__IPSBAR[0xD4E]))
#define MCF_INTC1_ICR15                      (*(vuint8 *)(&__IPSBAR[0xD4F]))
#define MCF_INTC1_ICR16                      (*(vuint8 *)(&__IPSBAR[0xD50]))
#define MCF_INTC1_ICR17                      (*(vuint8 *)(&__IPSBAR[0xD51]))
#define MCF_INTC1_ICR18                      (*(vuint8 *)(&__IPSBAR[0xD52]))
#define MCF_INTC1_ICR19                      (*(vuint8 *)(&__IPSBAR[0xD53]))
#define MCF_INTC1_ICR20                      (*(vuint8 *)(&__IPSBAR[0xD54]))
#define MCF_INTC1_ICR21                      (*(vuint8 *)(&__IPSBAR[0xD55]))
#define MCF_INTC1_ICR22                      (*(vuint8 *)(&__IPSBAR[0xD56]))
#define MCF_INTC1_ICR23                      (*(vuint8 *)(&__IPSBAR[0xD57]))
#define MCF_INTC1_ICR24                      (*(vuint8 *)(&__IPSBAR[0xD58]))
#define MCF_INTC1_ICR25                      (*(vuint8 *)(&__IPSBAR[0xD59]))
#define MCF_INTC1_ICR26                      (*(vuint8 *)(&__IPSBAR[0xD5A]))
#define MCF_INTC1_ICR27                      (*(vuint8 *)(&__IPSBAR[0xD5B]))
#define MCF_INTC1_ICR28                      (*(vuint8 *)(&__IPSBAR[0xD5C]))
#define MCF_INTC1_ICR29                      (*(vuint8 *)(&__IPSBAR[0xD5D]))
#define MCF_INTC1_ICR30                      (*(vuint8 *)(&__IPSBAR[0xD5E]))
#define MCF_INTC1_ICR31                      (*(vuint8 *)(&__IPSBAR[0xD5F]))
#define MCF_INTC1_ICR32                      (*(vuint8 *)(&__IPSBAR[0xD60]))
#define MCF_INTC1_ICR33                      (*(vuint8 *)(&__IPSBAR[0xD61]))
#define MCF_INTC1_ICR34                      (*(vuint8 *)(&__IPSBAR[0xD62]))
#define MCF_INTC1_ICR35                      (*(vuint8 *)(&__IPSBAR[0xD63]))
#define MCF_INTC1_ICR36                      (*(vuint8 *)(&__IPSBAR[0xD64]))
#define MCF_INTC1_ICR37                      (*(vuint8 *)(&__IPSBAR[0xD65]))
#define MCF_INTC1_ICR38                      (*(vuint8 *)(&__IPSBAR[0xD66]))
#define MCF_INTC1_ICR39                      (*(vuint8 *)(&__IPSBAR[0xD67]))
#define MCF_INTC1_ICR40                      (*(vuint8 *)(&__IPSBAR[0xD68]))
#define MCF_INTC1_ICR41                      (*(vuint8 *)(&__IPSBAR[0xD69]))
#define MCF_INTC1_ICR42                      (*(vuint8 *)(&__IPSBAR[0xD6A]))
#define MCF_INTC1_ICR43                      (*(vuint8 *)(&__IPSBAR[0xD6B]))
#define MCF_INTC1_ICR44                      (*(vuint8 *)(&__IPSBAR[0xD6C]))
#define MCF_INTC1_ICR45                      (*(vuint8 *)(&__IPSBAR[0xD6D]))
#define MCF_INTC1_ICR46                      (*(vuint8 *)(&__IPSBAR[0xD6E]))
#define MCF_INTC1_ICR47                      (*(vuint8 *)(&__IPSBAR[0xD6F]))
#define MCF_INTC1_ICR48                      (*(vuint8 *)(&__IPSBAR[0xD70]))
#define MCF_INTC1_ICR49                      (*(vuint8 *)(&__IPSBAR[0xD71]))
#define MCF_INTC1_ICR50                      (*(vuint8 *)(&__IPSBAR[0xD72]))
#define MCF_INTC1_ICR51                      (*(vuint8 *)(&__IPSBAR[0xD73]))
#define MCF_INTC1_ICR52                      (*(vuint8 *)(&__IPSBAR[0xD74]))
#define MCF_INTC1_ICR53                      (*(vuint8 *)(&__IPSBAR[0xD75]))
#define MCF_INTC1_ICR54                      (*(vuint8 *)(&__IPSBAR[0xD76]))
#define MCF_INTC1_ICR55                      (*(vuint8 *)(&__IPSBAR[0xD77]))
#define MCF_INTC1_ICR56                      (*(vuint8 *)(&__IPSBAR[0xD78]))
#define MCF_INTC1_ICR57                      (*(vuint8 *)(&__IPSBAR[0xD79]))
#define MCF_INTC1_ICR58                      (*(vuint8 *)(&__IPSBAR[0xD7A]))
#define MCF_INTC1_ICR59                      (*(vuint8 *)(&__IPSBAR[0xD7B]))
#define MCF_INTC1_ICR60                      (*(vuint8 *)(&__IPSBAR[0xD7C]))
#define MCF_INTC1_ICR61                      (*(vuint8 *)(&__IPSBAR[0xD7D]))
#define MCF_INTC1_ICR62                      (*(vuint8 *)(&__IPSBAR[0xD7E]))
#define MCF_INTC1_ICR63                      (*(vuint8 *)(&__IPSBAR[0xD7F]))
#define MCF_INTC1_SWIACK                     (*(vuint8 *)(&__IPSBAR[0xDE0]))
#define MCF_INTC1_L1IACK                     (*(vuint8 *)(&__IPSBAR[0xDE4]))
#define MCF_INTC1_L2IACK                     (*(vuint8 *)(&__IPSBAR[0xDE8]))
#define MCF_INTC1_L3IACK                     (*(vuint8 *)(&__IPSBAR[0xDEC]))
#define MCF_INTC1_L4IACK                     (*(vuint8 *)(&__IPSBAR[0xDF0]))
#define MCF_INTC1_L5IACK                     (*(vuint8 *)(&__IPSBAR[0xDF4]))
#define MCF_INTC1_L6IACK                     (*(vuint8 *)(&__IPSBAR[0xDF8]))
#define MCF_INTC1_L7IACK                     (*(vuint8 *)(&__IPSBAR[0xDFC]))
#define MCF_INTC1_ICR(x)                     (*(vuint8 *)(&__IPSBAR[0xD41 + ((x-1)*0x1)]))
#define MCF_INTC1_LIACK(x)                   (*(vuint8 *)(&__IPSBAR[0xDE4 + ((x-1)*0x4)]))

#define MCF_INTC_IPRH(x)                     (*(vuint32*)(&__IPSBAR[0xC00 + ((x)*0x100)]))
#define MCF_INTC_IPRL(x)                     (*(vuint32*)(&__IPSBAR[0xC04 + ((x)*0x100)]))
#define MCF_INTC_IMRH(x)                     (*(vuint32*)(&__IPSBAR[0xC08 + ((x)*0x100)]))
#define MCF_INTC_IMRL(x)                     (*(vuint32*)(&__IPSBAR[0xC0C + ((x)*0x100)]))
#define MCF_INTC_INTFRCH(x)                  (*(vuint32*)(&__IPSBAR[0xC10 + ((x)*0x100)]))
#define MCF_INTC_INTFRCL(x)                  (*(vuint32*)(&__IPSBAR[0xC14 + ((x)*0x100)]))
#define MCF_INTC_IRLR(x)                     (*(vuint8 *)(&__IPSBAR[0xC18 + ((x)*0x100)]))
#define MCF_INTC_IACKLPR(x)                  (*(vuint8 *)(&__IPSBAR[0xC19 + ((x)*0x100)]))
#define MCF_INTC_ICR01(x)                    (*(vuint8 *)(&__IPSBAR[0xC41 + ((x)*0x100)]))
#define MCF_INTC_ICR02(x)                    (*(vuint8 *)(&__IPSBAR[0xC42 + ((x)*0x100)]))
#define MCF_INTC_ICR03(x)                    (*(vuint8 *)(&__IPSBAR[0xC43 + ((x)*0x100)]))
#define MCF_INTC_ICR04(x)                    (*(vuint8 *)(&__IPSBAR[0xC44 + ((x)*0x100)]))
#define MCF_INTC_ICR05(x)                    (*(vuint8 *)(&__IPSBAR[0xC45 + ((x)*0x100)]))
#define MCF_INTC_ICR06(x)                    (*(vuint8 *)(&__IPSBAR[0xC46 + ((x)*0x100)]))
#define MCF_INTC_ICR07(x)                    (*(vuint8 *)(&__IPSBAR[0xC47 + ((x)*0x100)]))
#define MCF_INTC_ICR08(x)                    (*(vuint8 *)(&__IPSBAR[0xC48 + ((x)*0x100)]))
#define MCF_INTC_ICR09(x)                    (*(vuint8 *)(&__IPSBAR[0xC49 + ((x)*0x100)]))
#define MCF_INTC_ICR10(x)                    (*(vuint8 *)(&__IPSBAR[0xC4A + ((x)*0x100)]))
#define MCF_INTC_ICR11(x)                    (*(vuint8 *)(&__IPSBAR[0xC4B + ((x)*0x100)]))
#define MCF_INTC_ICR12(x)                    (*(vuint8 *)(&__IPSBAR[0xC4C + ((x)*0x100)]))
#define MCF_INTC_ICR13(x)                    (*(vuint8 *)(&__IPSBAR[0xC4D + ((x)*0x100)]))
#define MCF_INTC_ICR14(x)                    (*(vuint8 *)(&__IPSBAR[0xC4E + ((x)*0x100)]))
#define MCF_INTC_ICR15(x)                    (*(vuint8 *)(&__IPSBAR[0xC4F + ((x)*0x100)]))
#define MCF_INTC_ICR16(x)                    (*(vuint8 *)(&__IPSBAR[0xC50 + ((x)*0x100)]))
#define MCF_INTC_ICR17(x)                    (*(vuint8 *)(&__IPSBAR[0xC51 + ((x)*0x100)]))
#define MCF_INTC_ICR18(x)                    (*(vuint8 *)(&__IPSBAR[0xC52 + ((x)*0x100)]))
#define MCF_INTC_ICR19(x)                    (*(vuint8 *)(&__IPSBAR[0xC53 + ((x)*0x100)]))
#define MCF_INTC_ICR20(x)                    (*(vuint8 *)(&__IPSBAR[0xC54 + ((x)*0x100)]))
#define MCF_INTC_ICR21(x)                    (*(vuint8 *)(&__IPSBAR[0xC55 + ((x)*0x100)]))
#define MCF_INTC_ICR22(x)                    (*(vuint8 *)(&__IPSBAR[0xC56 + ((x)*0x100)]))
#define MCF_INTC_ICR23(x)                    (*(vuint8 *)(&__IPSBAR[0xC57 + ((x)*0x100)]))
#define MCF_INTC_ICR24(x)                    (*(vuint8 *)(&__IPSBAR[0xC58 + ((x)*0x100)]))
#define MCF_INTC_ICR25(x)                    (*(vuint8 *)(&__IPSBAR[0xC59 + ((x)*0x100)]))
#define MCF_INTC_ICR26(x)                    (*(vuint8 *)(&__IPSBAR[0xC5A + ((x)*0x100)]))
#define MCF_INTC_ICR27(x)                    (*(vuint8 *)(&__IPSBAR[0xC5B + ((x)*0x100)]))
#define MCF_INTC_ICR28(x)                    (*(vuint8 *)(&__IPSBAR[0xC5C + ((x)*0x100)]))
#define MCF_INTC_ICR29(x)                    (*(vuint8 *)(&__IPSBAR[0xC5D + ((x)*0x100)]))
#define MCF_INTC_ICR30(x)                    (*(vuint8 *)(&__IPSBAR[0xC5E + ((x)*0x100)]))
#define MCF_INTC_ICR31(x)                    (*(vuint8 *)(&__IPSBAR[0xC5F + ((x)*0x100)]))
#define MCF_INTC_ICR32(x)                    (*(vuint8 *)(&__IPSBAR[0xC60 + ((x)*0x100)]))
#define MCF_INTC_ICR33(x)                    (*(vuint8 *)(&__IPSBAR[0xC61 + ((x)*0x100)]))
#define MCF_INTC_ICR34(x)                    (*(vuint8 *)(&__IPSBAR[0xC62 + ((x)*0x100)]))
#define MCF_INTC_ICR35(x)                    (*(vuint8 *)(&__IPSBAR[0xC63 + ((x)*0x100)]))
#define MCF_INTC_ICR36(x)                    (*(vuint8 *)(&__IPSBAR[0xC64 + ((x)*0x100)]))
#define MCF_INTC_ICR37(x)                    (*(vuint8 *)(&__IPSBAR[0xC65 + ((x)*0x100)]))
#define MCF_INTC_ICR38(x)                    (*(vuint8 *)(&__IPSBAR[0xC66 + ((x)*0x100)]))
#define MCF_INTC_ICR39(x)                    (*(vuint8 *)(&__IPSBAR[0xC67 + ((x)*0x100)]))
#define MCF_INTC_ICR40(x)                    (*(vuint8 *)(&__IPSBAR[0xC68 + ((x)*0x100)]))
#define MCF_INTC_ICR41(x)                    (*(vuint8 *)(&__IPSBAR[0xC69 + ((x)*0x100)]))
#define MCF_INTC_ICR42(x)                    (*(vuint8 *)(&__IPSBAR[0xC6A + ((x)*0x100)]))
#define MCF_INTC_ICR43(x)                    (*(vuint8 *)(&__IPSBAR[0xC6B + ((x)*0x100)]))
#define MCF_INTC_ICR44(x)                    (*(vuint8 *)(&__IPSBAR[0xC6C + ((x)*0x100)]))
#define MCF_INTC_ICR45(x)                    (*(vuint8 *)(&__IPSBAR[0xC6D + ((x)*0x100)]))
#define MCF_INTC_ICR46(x)                    (*(vuint8 *)(&__IPSBAR[0xC6E + ((x)*0x100)]))
#define MCF_INTC_ICR47(x)                    (*(vuint8 *)(&__IPSBAR[0xC6F + ((x)*0x100)]))
#define MCF_INTC_ICR48(x)                    (*(vuint8 *)(&__IPSBAR[0xC70 + ((x)*0x100)]))
#define MCF_INTC_ICR49(x)                    (*(vuint8 *)(&__IPSBAR[0xC71 + ((x)*0x100)]))
#define MCF_INTC_ICR50(x)                    (*(vuint8 *)(&__IPSBAR[0xC72 + ((x)*0x100)]))
#define MCF_INTC_ICR51(x)                    (*(vuint8 *)(&__IPSBAR[0xC73 + ((x)*0x100)]))
#define MCF_INTC_ICR52(x)                    (*(vuint8 *)(&__IPSBAR[0xC74 + ((x)*0x100)]))
#define MCF_INTC_ICR53(x)                    (*(vuint8 *)(&__IPSBAR[0xC75 + ((x)*0x100)]))
#define MCF_INTC_ICR54(x)                    (*(vuint8 *)(&__IPSBAR[0xC76 + ((x)*0x100)]))
#define MCF_INTC_ICR55(x)                    (*(vuint8 *)(&__IPSBAR[0xC77 + ((x)*0x100)]))
#define MCF_INTC_ICR56(x)                    (*(vuint8 *)(&__IPSBAR[0xC78 + ((x)*0x100)]))
#define MCF_INTC_ICR57(x)                    (*(vuint8 *)(&__IPSBAR[0xC79 + ((x)*0x100)]))
#define MCF_INTC_ICR58(x)                    (*(vuint8 *)(&__IPSBAR[0xC7A + ((x)*0x100)]))
#define MCF_INTC_ICR59(x)                    (*(vuint8 *)(&__IPSBAR[0xC7B + ((x)*0x100)]))
#define MCF_INTC_ICR60(x)                    (*(vuint8 *)(&__IPSBAR[0xC7C + ((x)*0x100)]))
#define MCF_INTC_ICR61(x)                    (*(vuint8 *)(&__IPSBAR[0xC7D + ((x)*0x100)]))
#define MCF_INTC_ICR62(x)                    (*(vuint8 *)(&__IPSBAR[0xC7E + ((x)*0x100)]))
#define MCF_INTC_ICR63(x)                    (*(vuint8 *)(&__IPSBAR[0xC7F + ((x)*0x100)]))
#define MCF_INTC_SWIACK(x)                   (*(vuint8 *)(&__IPSBAR[0xCE0 + ((x)*0x100)]))
#define MCF_INTC_L1IACK(x)                   (*(vuint8 *)(&__IPSBAR[0xCE4 + ((x)*0x100)]))
#define MCF_INTC_L2IACK(x)                   (*(vuint8 *)(&__IPSBAR[0xCE8 + ((x)*0x100)]))
#define MCF_INTC_L3IACK(x)                   (*(vuint8 *)(&__IPSBAR[0xCEC + ((x)*0x100)]))
#define MCF_INTC_L4IACK(x)                   (*(vuint8 *)(&__IPSBAR[0xCF0 + ((x)*0x100)]))
#define MCF_INTC_L5IACK(x)                   (*(vuint8 *)(&__IPSBAR[0xCF4 + ((x)*0x100)]))
#define MCF_INTC_L6IACK(x)                   (*(vuint8 *)(&__IPSBAR[0xCF8 + ((x)*0x100)]))
#define MCF_INTC_L7IACK(x)                   (*(vuint8 *)(&__IPSBAR[0xCFC + ((x)*0x100)]))


/* Bit definitions and macros for MCF_INTC_IPRH */
#define MCF_INTC_IPRH_INT32                  (0x1)
#define MCF_INTC_IPRH_INT33                  (0x2)
#define MCF_INTC_IPRH_INT34                  (0x4)
#define MCF_INTC_IPRH_INT35                  (0x8)
#define MCF_INTC_IPRH_INT36                  (0x10)
#define MCF_INTC_IPRH_INT37                  (0x20)
#define MCF_INTC_IPRH_INT38                  (0x40)
#define MCF_INTC_IPRH_INT39                  (0x80)
#define MCF_INTC_IPRH_INT40                  (0x100)
#define MCF_INTC_IPRH_INT41                  (0x200)
#define MCF_INTC_IPRH_INT42                  (0x400)
#define MCF_INTC_IPRH_INT43                  (0x800)
#define MCF_INTC_IPRH_INT44                  (0x1000)
#define MCF_INTC_IPRH_INT45                  (0x2000)
#define MCF_INTC_IPRH_INT46                  (0x4000)
#define MCF_INTC_IPRH_INT47                  (0x8000)
#define MCF_INTC_IPRH_INT48                  (0x10000)
#define MCF_INTC_IPRH_INT49                  (0x20000)
#define MCF_INTC_IPRH_INT50                  (0x40000)
#define MCF_INTC_IPRH_INT51                  (0x80000)
#define MCF_INTC_IPRH_INT52                  (0x100000)
#define MCF_INTC_IPRH_INT53                  (0x200000)
#define MCF_INTC_IPRH_INT54                  (0x400000)
#define MCF_INTC_IPRH_INT55                  (0x800000)
#define MCF_INTC_IPRH_INT56                  (0x1000000)
#define MCF_INTC_IPRH_INT57                  (0x2000000)
#define MCF_INTC_IPRH_INT58                  (0x4000000)
#define MCF_INTC_IPRH_INT59                  (0x8000000)
#define MCF_INTC_IPRH_INT60                  (0x10000000)
#define MCF_INTC_IPRH_INT61                  (0x20000000)
#define MCF_INTC_IPRH_INT62                  (0x40000000)
#define MCF_INTC_IPRH_INT63                  (0x80000000)

/* Bit definitions and macros for MCF_INTC_IPRL */
#define MCF_INTC_IPRL_INT1                   (0x2)
#define MCF_INTC_IPRL_INT2                   (0x4)
#define MCF_INTC_IPRL_INT3                   (0x8)
#define MCF_INTC_IPRL_INT4                   (0x10)
#define MCF_INTC_IPRL_INT5                   (0x20)
#define MCF_INTC_IPRL_INT6                   (0x40)
#define MCF_INTC_IPRL_INT7                   (0x80)
#define MCF_INTC_IPRL_INT8                   (0x100)
#define MCF_INTC_IPRL_INT9                   (0x200)
#define MCF_INTC_IPRL_INT10                  (0x400)
#define MCF_INTC_IPRL_INT11                  (0x800)
#define MCF_INTC_IPRL_INT12                  (0x1000)
#define MCF_INTC_IPRL_INT13                  (0x2000)
#define MCF_INTC_IPRL_INT14                  (0x4000)
#define MCF_INTC_IPRL_INT15                  (0x8000)
#define MCF_INTC_IPRL_INT16                  (0x10000)
#define MCF_INTC_IPRL_INT17                  (0x20000)
#define MCF_INTC_IPRL_INT18                  (0x40000)
#define MCF_INTC_IPRL_INT19                  (0x80000)
#define MCF_INTC_IPRL_INT20                  (0x100000)
#define MCF_INTC_IPRL_INT21                  (0x200000)
#define MCF_INTC_IPRL_INT22                  (0x400000)
#define MCF_INTC_IPRL_INT23                  (0x800000)
#define MCF_INTC_IPRL_INT24                  (0x1000000)
#define MCF_INTC_IPRL_INT25                  (0x2000000)
#define MCF_INTC_IPRL_INT26                  (0x4000000)
#define MCF_INTC_IPRL_INT27                  (0x8000000)
#define MCF_INTC_IPRL_INT28                  (0x10000000)
#define MCF_INTC_IPRL_INT29                  (0x20000000)
#define MCF_INTC_IPRL_INT30                  (0x40000000)
#define MCF_INTC_IPRL_INT31                  (0x80000000)

/* Bit definitions and macros for MCF_INTC_IMRH */
#define MCF_INTC_IMRH_INT_MASK32             (0x1)
#define MCF_INTC_IMRH_INT_MASK33             (0x2)
#define MCF_INTC_IMRH_INT_MASK34             (0x4)
#define MCF_INTC_IMRH_INT_MASK35             (0x8)
#define MCF_INTC_IMRH_INT_MASK36             (0x10)
#define MCF_INTC_IMRH_INT_MASK37             (0x20)
#define MCF_INTC_IMRH_INT_MASK38             (0x40)
#define MCF_INTC_IMRH_INT_MASK39             (0x80)
#define MCF_INTC_IMRH_INT_MASK40             (0x100)
#define MCF_INTC_IMRH_INT_MASK41             (0x200)
#define MCF_INTC_IMRH_INT_MASK42             (0x400)
#define MCF_INTC_IMRH_INT_MASK43             (0x800)
#define MCF_INTC_IMRH_INT_MASK44             (0x1000)
#define MCF_INTC_IMRH_INT_MASK45             (0x2000)
#define MCF_INTC_IMRH_INT_MASK46             (0x4000)
#define MCF_INTC_IMRH_INT_MASK47             (0x8000)
#define MCF_INTC_IMRH_INT_MASK48             (0x10000)
#define MCF_INTC_IMRH_INT_MASK49             (0x20000)
#define MCF_INTC_IMRH_INT_MASK50             (0x40000)
#define MCF_INTC_IMRH_INT_MASK51             (0x80000)
#define MCF_INTC_IMRH_INT_MASK52             (0x100000)
#define MCF_INTC_IMRH_INT_MASK53             (0x200000)
#define MCF_INTC_IMRH_INT_MASK54             (0x400000)
#define MCF_INTC_IMRH_INT_MASK55             (0x800000)
#define MCF_INTC_IMRH_INT_MASK56             (0x1000000)
#define MCF_INTC_IMRH_INT_MASK57             (0x2000000)
#define MCF_INTC_IMRH_INT_MASK58             (0x4000000)
#define MCF_INTC_IMRH_INT_MASK59             (0x8000000)
#define MCF_INTC_IMRH_INT_MASK60             (0x10000000)
#define MCF_INTC_IMRH_INT_MASK61             (0x20000000)
#define MCF_INTC_IMRH_INT_MASK62             (0x40000000)
#define MCF_INTC_IMRH_INT_MASK63             (0x80000000)

/* Bit definitions and macros for MCF_INTC_IMRL */
#define MCF_INTC_IMRL_MASKALL                (0x1)
#define MCF_INTC_IMRL_INT_MASK1              (0x2)
#define MCF_INTC_IMRL_INT_MASK2              (0x4)
#define MCF_INTC_IMRL_INT_MASK3              (0x8)
#define MCF_INTC_IMRL_INT_MASK4              (0x10)
#define MCF_INTC_IMRL_INT_MASK5              (0x20)
#define MCF_INTC_IMRL_INT_MASK6              (0x40)
#define MCF_INTC_IMRL_INT_MASK7              (0x80)
#define MCF_INTC_IMRL_INT_MASK8              (0x100)
#define MCF_INTC_IMRL_INT_MASK9              (0x200)
#define MCF_INTC_IMRL_INT_MASK10             (0x400)
#define MCF_INTC_IMRL_INT_MASK11             (0x800)
#define MCF_INTC_IMRL_INT_MASK12             (0x1000)
#define MCF_INTC_IMRL_INT_MASK13             (0x2000)
#define MCF_INTC_IMRL_INT_MASK14             (0x4000)
#define MCF_INTC_IMRL_INT_MASK15             (0x8000)
#define MCF_INTC_IMRL_INT_MASK16             (0x10000)
#define MCF_INTC_IMRL_INT_MASK17             (0x20000)
#define MCF_INTC_IMRL_INT_MASK18             (0x40000)
#define MCF_INTC_IMRL_INT_MASK19             (0x80000)
#define MCF_INTC_IMRL_INT_MASK20             (0x100000)
#define MCF_INTC_IMRL_INT_MASK21             (0x200000)
#define MCF_INTC_IMRL_INT_MASK22             (0x400000)
#define MCF_INTC_IMRL_INT_MASK23             (0x800000)
#define MCF_INTC_IMRL_INT_MASK24             (0x1000000)
#define MCF_INTC_IMRL_INT_MASK25             (0x2000000)
#define MCF_INTC_IMRL_INT_MASK26             (0x4000000)
#define MCF_INTC_IMRL_INT_MASK27             (0x8000000)
#define MCF_INTC_IMRL_INT_MASK28             (0x10000000)
#define MCF_INTC_IMRL_INT_MASK29             (0x20000000)
#define MCF_INTC_IMRL_INT_MASK30             (0x40000000)
#define MCF_INTC_IMRL_INT_MASK31             (0x80000000)

/* Bit definitions and macros for MCF_INTC_INTFRCH */
#define MCF_INTC_INTFRCH_INTFRC32            (0x1)
#define MCF_INTC_INTFRCH_INTFRC33            (0x2)
#define MCF_INTC_INTFRCH_INTFRC34            (0x4)
#define MCF_INTC_INTFRCH_INTFRC35            (0x8)
#define MCF_INTC_INTFRCH_INTFRC36            (0x10)
#define MCF_INTC_INTFRCH_INTFRC37            (0x20)
#define MCF_INTC_INTFRCH_INTFRC38            (0x40)
#define MCF_INTC_INTFRCH_INTFRC39            (0x80)
#define MCF_INTC_INTFRCH_INTFRC40            (0x100)
#define MCF_INTC_INTFRCH_INTFRC41            (0x200)
#define MCF_INTC_INTFRCH_INTFRC42            (0x400)
#define MCF_INTC_INTFRCH_INTFRC43            (0x800)
#define MCF_INTC_INTFRCH_INTFRC44            (0x1000)
#define MCF_INTC_INTFRCH_INTFRC45            (0x2000)
#define MCF_INTC_INTFRCH_INTFRC46            (0x4000)
#define MCF_INTC_INTFRCH_INTFRC47            (0x8000)
#define MCF_INTC_INTFRCH_INTFRC48            (0x10000)
#define MCF_INTC_INTFRCH_INTFRC49            (0x20000)
#define MCF_INTC_INTFRCH_INTFRC50            (0x40000)
#define MCF_INTC_INTFRCH_INTFRC51            (0x80000)
#define MCF_INTC_INTFRCH_INTFRC52            (0x100000)
#define MCF_INTC_INTFRCH_INTFRC53            (0x200000)
#define MCF_INTC_INTFRCH_INTFRC54            (0x400000)
#define MCF_INTC_INTFRCH_INTFRC55            (0x800000)
#define MCF_INTC_INTFRCH_INTFRC56            (0x1000000)
#define MCF_INTC_INTFRCH_INTFRC57            (0x2000000)
#define MCF_INTC_INTFRCH_INTFRC58            (0x4000000)
#define MCF_INTC_INTFRCH_INTFRC59            (0x8000000)
#define MCF_INTC_INTFRCH_INTFRC60            (0x10000000)
#define MCF_INTC_INTFRCH_INTFRC61            (0x20000000)
#define MCF_INTC_INTFRCH_INTFRC62            (0x40000000)
#define MCF_INTC_INTFRCH_INTFRC63            (0x80000000)

/* Bit definitions and macros for MCF_INTC_INTFRCL */
#define MCF_INTC_INTFRCL_INTFRC1             (0x2)
#define MCF_INTC_INTFRCL_INTFRC2             (0x4)
#define MCF_INTC_INTFRCL_INTFRC3             (0x8)
#define MCF_INTC_INTFRCL_INTFRC4             (0x10)
#define MCF_INTC_INTFRCL_INTFRC5             (0x20)
#define MCF_INTC_INTFRCL_INTFRC6             (0x40)
#define MCF_INTC_INTFRCL_INTFRC7             (0x80)
#define MCF_INTC_INTFRCL_INTFRC8             (0x100)
#define MCF_INTC_INTFRCL_INTFRC9             (0x200)
#define MCF_INTC_INTFRCL_INTFRC10            (0x400)
#define MCF_INTC_INTFRCL_INTFRC11            (0x800)
#define MCF_INTC_INTFRCL_INTFRC12            (0x1000)
#define MCF_INTC_INTFRCL_INTFRC13            (0x2000)
#define MCF_INTC_INTFRCL_INTFRC14            (0x4000)
#define MCF_INTC_INTFRCL_INTFRC15            (0x8000)
#define MCF_INTC_INTFRCL_INTFRC16            (0x10000)
#define MCF_INTC_INTFRCL_INTFRC17            (0x20000)
#define MCF_INTC_INTFRCL_INTFRC18            (0x40000)
#define MCF_INTC_INTFRCL_INTFRC19            (0x80000)
#define MCF_INTC_INTFRCL_INTFRC20            (0x100000)
#define MCF_INTC_INTFRCL_INTFRC21            (0x200000)
#define MCF_INTC_INTFRCL_INTFRC22            (0x400000)
#define MCF_INTC_INTFRCL_INTFRC23            (0x800000)
#define MCF_INTC_INTFRCL_INTFRC24            (0x1000000)
#define MCF_INTC_INTFRCL_INTFRC25            (0x2000000)
#define MCF_INTC_INTFRCL_INTFRC26            (0x4000000)
#define MCF_INTC_INTFRCL_INTFRC27            (0x8000000)
#define MCF_INTC_INTFRCL_INTFRC28            (0x10000000)
#define MCF_INTC_INTFRCL_INTFRC29            (0x20000000)
#define MCF_INTC_INTFRCL_INTFRC30            (0x40000000)
#define MCF_INTC_INTFRCL_INTFRC31            (0x80000000)

/* Bit definitions and macros for MCF_INTC_IRLR */
#define MCF_INTC_IRLR_IRQ(x)                 (((x)&0x7F)<<0x1)

/* Bit definitions and macros for MCF_INTC_IACKLPR */
#define MCF_INTC_IACKLPR_PRI(x)              (((x)&0xF)<<0)
#define MCF_INTC_IACKLPR_LEVEL(x)            (((x)&0x7)<<0x4)

/* Bit definitions and macros for MCF_INTC_ICR */
#define MCF_INTC_ICR_IP(x)                   (((x)&0x7)<<0)
#define MCF_INTC_ICR_IL(x)                   (((x)&0x7)<<0x3)

/* Bit definitions and macros for MCF_INTC_SWIACK */
#define MCF_INTC_SWIACK_VECTOR(x)            (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_INTC_LIACK */
#define MCF_INTC_LIACK_VECTOR(x)             (((x)&0xFF)<<0)


#endif /* __MCF52235_INTC_H__ */