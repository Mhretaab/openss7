/*****************************************************************************

 @(#) File: src/drivers/x25-plp.c

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2019  Monavacon Limited <http://www.monavacon.com/>
 Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software: you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation, version 3 of the license.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
 details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>, or
 write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
 02139, USA.

 -----------------------------------------------------------------------------

 U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
 behalf of the U.S. Government ("Government"), the following provisions apply
 to you.  If the Software is supplied by the Department of Defense ("DoD"), it
 is classified as "Commercial Computer Software" under paragraph 252.227-7014
 of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
 successor regulations) and the Government is acquiring only the license rights
 granted herein (the license rights customarily provided to non-Government
 users).  If the Software is supplied to any unit or agency of the Government
 other than DoD, it is classified as "Restricted Computer Software" and the
 Government's rights in the Software are defined in paragraph 52.227-19 of the
 Federal Acquisition Regulations ("FAR") (or any successor regulations) or, in
 the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
 (or any successor regulations).

 -----------------------------------------------------------------------------

 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See http://www.openss7.com/

 *****************************************************************************/

static char const ident[] = "src/drivers/x25-plp.c (" PACKAGE_ENVR ") " PACKAGE_DATE;

/*
 * This is a multiplexing driver for the X.25 Packet Layer Protocol (PLP).  It
 * accepts DLPI streams linked beneath the multiplexing driver to provide X.25
 * LAPB SLP, MLP, or LLC, or XOT Streams beneath the multiplexing driver.  The
 * driver interrogates the Stream for the appropriate type and accepts link
 * configuration with IOCTLs.  The upper boundary interface is the (Spider)
 * NLI interface offered by Sun, SGI, HP, WindRiver and others.  There are to
 * special minor device numbers that have autopush statements assigned to them
 * in the kernel (yes, we can do that, see autopush(9)).  One autopushes the
 * "npi" module that converts between NLI X.25 and NPI CONS.  The other
 * autopushes the "xx25" module that converts between NLI X.25 and TPI XX25.
 * Thus the multiplexing driver presents three upper interfaces: NLI X.25, TPI
 * X.25, and NPI CONS.  Note that use with SNARE (ISO 10030), ES-IS (ISO
 * 9542), IS-IS (ISO 10589) and IDRP (ISO 10747) is also possible using a
 * user-space routing daemon that listens for the appropriate routing packets.
 * Redirection of CONS Connect Requests using SNARE (OSI 10030) is also
 * possible by supporting call deflection through NPI CONS.
 */

#define NEVER 0

#define _SVR4_SOURCE	1
#define _MPS_SOURCE	1
#define _SUN_SOURCE	1

#include <sys/os7/compat.h>
#if NEVER
#include <sys/nli.h>
#endif

#define PLP_DESCRIP	"SVR 4.2 NLI X.25 PLP Driver for Linux Fast-STREAMS"
#define PLP_EXTRA	"Part of the OpenSS7 X.25 Stack for Linux Fast-STREAMS"
#define PLP_COPYRIGHT	"Copyright (c) 2008-2019  Monavacon Limited.  All Rights Reserved."
#define PLP_REVISION	"OpenSS7 src/drivers/x25-plp.c (" PACKAGE_ENVR ") " PACKAGE_DATE
#define PLP_DEVICE	"SVR 4.2MP NLI Driver (NLI) for X.25/ISO 8208"
#define PLP_CONTACT	"Brian Bidulock <bidulock@openss7.org>"
#define PLP_LICENSE	"GPL"
#define PLP_BANNER	PLP_DESCRIP	"\n" \
			PLP_EXTRA	"\n" \
			PLP_COPYRIGHT	"\n" \
			PLP_REVISION	"\n" \
			PLP_DEVICE	"\n" \
			PLP_CONTACT	"\n"
#define PLP_SPLASH	PLP_DESCRIP	" - " \
			PLP_REVISION

#ifndef CONFIG_STREAMS_PLP_NAME
#error "CONFIG_STREAMS_PLP_NAME must be defined."
#endif				/* CONFIG_SREAMS_PLP_NAME */
#ifndef CONFIG_STREAMS_PLP_MODID
#error "CONFIG_STREAMS_PLP_MODID must be defined."
#endif				/* CONFIG_STREAMS_PLP_MODID */

#ifdef LINUX
#ifdef MODULE
MODULE_AUTHOR(PLP_CONTACT);
MODULE_DESCRIPTION(PLP_DESCRIP);
MODULE_SUPPORTED_DEVICE(PLP_DEVICE);
#ifdef MODULE_LICENSE
MODULE_LICENSE(PLP_LICENSE);
#endif				/* MODULE_LICENSE */
#ifdef MODULE_ALIAS
MODULE_ALIAS("streams-modid-" __stringify(CONFIG_STREAMS_PLP_MODID));
MODULE_ALIAS("streams-driver-x25-plp");
MODULE_ALIAS("streams-module-x25-plp");
MODULE_ALIAS("streams-major-" __stringify(CONFIG_STREAMS_PLP_MAJOR));
MODULE_ALIAS("/dev/streams/x25-plp");
MODULE_ALIAS("/dev/streams/x25-plp/*");
MODULE_ALIAS("/dev/streams/x25-plp/x25");
MODULE_ALIAS("/dev/streams/x25-plp/xx25");
MODULE_ALIAS("/dev/streams/x25-plp/cons");
MODULE_ALIAS("/dev/streams/clone/x25-plp");
MODULE_ALIAS("char-major-" __stringify(CONFIG_STREAMS_CLONE_MAJOR) "-" __stringify(CONFIG_STREAMS_PLP_MAJOR));
MODULE_ALIAS("/dev/x25-plp");
//MODULE_ALIAS("devname:x25-plp");
MODULE_ALIAS("/dev/x25");
MODULE_ALIAS("/dev/xx25");
MODULE_ALIAS("/dev/cons");
#endif				/* MODULE_ALIAS */
#ifdef MODULE_VERSION
MODULE_VERSION(PACKAGE_ENVR);
#endif				/* MODULE_VERSION */
#endif				/* MODULE */
#endif				/* LINUX */

#define PLP_DRV_ID	CONFIG_STREAMS_PLP_MODID
#define PLP_DRV_NAME	CONFIG_STREAMS_PLP_NAME
#define PLP_CMAJORS	CONFIG_STREAMS_PLP_NMAJORS
#define PLP_CMAJOR_0	CONFIG_STREAMS_PLP_MAJOR
#define PLP_UNITS	CONFIG_STREAMS_PLP_NMINORS

#ifndef PLP_DRV_NAME
#define PLP_DRV_NAME	"x25-plp"
#endif				/* PLP_DRV_NAME */

#ifndef PLP_DRV_ID
#define PLP_DRV_ID	0
#endif				/* PLP_DRV_ID */

/*
 * --------------------------------------------------------------------------
 *
 * STREAMS DEFINITIONS
 *
 * --------------------------------------------------------------------------
 */

#define DRV_ID	    PLP_DRV_ID
#define DRV_NAME    PLP_DRV_NAME
#define CMAJORS	    PLP_CMAJORS
#define CMAJOR_0    PLP_CMAJOR_0
#define UNITS	    PLP_UNITS
#ifdef MODULE
#define DRV_BANNER  PLP_BANNER
#else				/* MODULE */
#define DRV_BANNER  PLP_SPLASH
#endif				/* MODULE */

#if NEVER
static struct module_info nl_minfo = {
	.mi_idnum = DRV_ID,
	.mi_idname = DRV_NAME,
	.mi_minpsz = STRMINPSZ,
	.mi_maxpsz = STRMAXPSZ,
	.mi_hiwat = STRHIGH,
	.mi_lowat = STRLOW,
};

static struct module_stat nl_mstat __attribute__ ((__aligned__(SMP_CACHE_BYTES)));

static struct module_info dl_minfo = {
	.mi_idnum = DRV_ID,
	.mi_idname = DRV_NAME,
	.mi_minpsz = STRMINPSZ,
	.mi_maxpsz = STRMAXPSZ,
	.mi_hiwat = STRHIGH,
	.mi_lowat = STRLOW,
};

static struct module_stat dl_mstat __attribute__ ((__aligned__(SMP_CACHE_BYTES)));

/*
 * --------------------------------------------------------------------------
 *
 * PRIVATE STRUCTURE
 *
 * --------------------------------------------------------------------------
 */

struct nl;
struct dl;

/* Upper multiplex structure. */
struct nl {
	struct nl *nl_next;		/* linkage for network layers belonging to same data link */
	struct dl *dl;
	queue_t *oq;
	int state;
	int oldstate;
	struct qosformat qos;
	struct xaddrf cld;
	struct xaddrf clg;
	struct xaddrf res;
	struct xaddrf def;
};

/* Lower multiplex structure. */
struct dl {
	struct nl *nl;			/* list of network layers for this belonging to this data
					   link */
	queue_t *oq;
	dl_ulong state;
	dl_ulong oldstate;
	struct {
		dl_info_ack_t info;
	} proto;
	struct qosformat qosformat;	/* defaults for link */
};

/* Structure representing an X.25 PLE */
struct x25_ple {
	struct dl *dl;
	struct {
		uint8_t gfi;		/* General Format Identifier */
		struct {
			/* registration facilities */
			uint8_t nonneg[1];	/* Non-negotiable facilities. */
			uint8_t avail[2];	/* Facilitiy availability. */
			uint8_t anytime[2];	/* Negotiable anytime. */
			uint8_t idle[1];	/* Negotiable while idle. */
			struct {
				uint8_t ic;	/* Incoming non-standard default packet size */
				uint8_t og;	/* Outgoing non-standard default packet size */
			} ndps;
			struct {
				uint8_t ic;	/* Incoming non-standard default window size */
				uint8_t og;	/* Outgoing non-standard default window size */
			} ndws;
			struct {
				uint8_t ic;	/* Incoming default throughput class */
				uint8_t og;	/* Outgoing default throughput class */
			} dtca;
			/* Logical Channel Type Ranges */
			struct {
				/* Incoming Range */
				struct {
					uint16_t l;	/* LIC */
					uint16_t h;	/* HIC */
				} ic;
				/* Two-way Range */
				struct {
					uint16_t l;	/* LTC */
					uint16_t h;	/* HTC */
				} tc;
				/* Outgoing Range */
				struct {
					uint16_t l;	/* LOC */
					uint16_t h;	/* HOC */
				} oc;
			} lca;
		} fac;
		/* Procedural time intervals (msec). */
		union {
			struct {
				uint32_t t10;
				uint32_t t11;
				uint32_t t12;
				uint32_t t13;
				uint32_t t14;
				uint32_t t15;
				uint32_t t16;
				uint32_t t17;
				uint32_t t18;
			};
			struct {
				uint32_t t20;
				uint32_t t21;
				uint32_t t22;
				uint32_t t23;
				uint32_t t24;
				uint32_t t25;
				uint32_t t26;
				uint32_t t27;
				uint32_t t28;
			};
		} times;
		/* Retransmission counts. */
		union {
			struct {
				uint32_t r10;
				uint32_t r11;
				uint32_t r12;
				uint32_t r13;
				uint32_t r14;
				uint32_t r15;
				uint32_t r16;
				uint32_t r17;
				uint32_t r18;
			};
			struct {
				uint32_t r20;
				uint32_t r21;
				uint32_t r22;
				uint32_t r23;
				uint32_t r24;
				uint32_t r25;
				uint32_t r26;
				uint32_t r27;
				uint32_t r28;
			};
		} counts;
	} proto;
	/* Timer buffers for mi_timer. */
	union {
		struct {
			mblk_t *t10;
			mblk_t *t11;
			mblk_t *t12;
			mblk_t *t13;
			mblk_t *t14;
			mblk_t *t15;
			mblk_t *t16;
			mblk_t *t17;
			mblk_t *t18;
		};
		struct {
			mblk_t *t20;
			mblk_t *t21;
			mblk_t *t22;
			mblk_t *t23;
			mblk_t *t24;
			mblk_t *t25;
			mblk_t *t26;
			mblk_t *t27;
			mblk_t *t28;
		};
	} timers;
};

static caddr_t nl_opens = NULL;
static caddr_t nl_links = NULL;

#define NL_PRIV(q) ((struct nl *)q->q_ptr)
#define DL_PRIV(q) ((struct dl *)q->q_ptr)

#define STRLOGIO    0		/* input-output controls */
#define STRLOGST    1		/* state transitions */
#define STRLOGTO    2		/* timeouts */
#define STRLOGRX    3		/* primitives received */
#define STRLOGTX    4		/* primitives issued */
#define STRLOGTE    5		/* timer events */
#define STRLOGDA    6		/* data */

static inline const char *
nl_iocname(int cmd)
{
	switch (cmd) {
	default:
		return ("(unknown)");
	}
}

static inline const char *
nl_primname(int upward, int xl_type, int xl_command)
{
	if (upward) {
		switch (xl_type) {
		case XL_CTL:
			switch (xl_command) {
			case N_PVC_ATTACH:
				return ("N_PVC_ATTACH confirm");
			case N_PVC_DETACH:
				return ("N_PVC_DETACH confirm");
			case N_Xlisten:
				return ("N_Xlisten confirm");
			case N_Xcanlis:
				return ("N_Xcanlis confirm");
			case N_CI:
				return ("N_CI indication");
			case N_CC:
				return ("N_CC confirm");
			case N_RI:
				return ("N_RI indication");
			case N_RC:
				return ("N_RC confirm");
			case N_DI:
				return ("N_DI indication");
			case N_DC:
				return ("N_DC confirm");
			case N_Abort:
				return ("N_Abort indication");
			default:
				return ("(unknown XL_CTL)");
			}
		case XL_DAT:
			switch (xl_command) {
			case N_Data:
				return ("N_Data indication");
			case N_DAck:
				return ("N_DAck confirm");
			case N_EData:
				return ("N_EData indication");
			case N_EAck:
				return ("N_EAck confirm");
			default:
				return ("(unknown XL_DAT)");
			}
		default:
			return ("(unknown xl_type)");
		}
	} else {
		switch (xl_type) {
		case XL_CTL:
			switch (xl_command) {
			case N_PVC_ATTACH:
				return ("N_PVC_ATTACH request");
			case N_PVC_DETACH:
				return ("N_PVC_DETACH request");
			case N_Xlisten:
				return ("N_Xlisten request");
			case N_Xcanlis:
				return ("N_Xcanlis request");
			case N_CI:
				return ("N_CI request");
			case N_CC:
				return ("N_CC response");
			case N_RI:
				return ("N_RI request");
			case N_RC:
				return ("N_RC response");
			case N_DI:
				return ("N_DI request");
			case N_DC:	/* wrong direction */
				return ("N_DC (invalid)");
			case N_Abort:	/* wrong direction */
				return ("N_Abort (invalid)");
			default:
				return ("(unknown XL_CTL)");
			}
		case XL_DAT:
			switch (xl_command) {
			case N_Data:
				return ("N_Data request");
			case N_DAck:
				return ("N_DAck response");
			case N_EData:
				return ("N_EData request");
			case N_EAck:
				return ("N_EAck response");
			default:
				return ("(unknown XL_DAT)");
			}
		default:
			return ("(unknown xl_type)");
		}
	}
}

static inline const char *
nl_statename(int state)
{
	switch (state) {
	case NS_UNBND:
		return ("NS_UNBND");
	case NS_WACK_BREQ:
		return ("NS_WACK_BREQ");
	case NS_WACK_UREQ:
		return ("NS_WACK_UREQ");
	case NS_IDLE:
		return ("NS_IDLE");
	case NS_WACK_OPTREQ:
		return ("NS_WACK_OPTREQ");
	case NS_WACK_RRES:
		return ("NS_WACK_RRES");
	case NS_WCON_CREQ:
		return ("NS_WCON_CREQ");
	case NS_WRES_CIND:
		return ("NS_WRES_CIND");
	case NS_WACK_CRES:
		return ("NS_WACK_CRES");
	case NS_DATA_XFER:
		return ("NS_DATA_XFER");
	case NS_WCON_RREQ:
		return ("NS_WCON_RREQ");
	case NS_WRES_RIND:
		return ("NS_WRES_RIND");
	case NS_WACK_DREQ6:
		return ("NS_WACK_DREQ6");
	case NS_WACK_DREQ7:
		return ("NS_WACK_DREQ7");
	case NS_WACK_DREQ9:
		return ("NS_WACK_DREQ9");
	case NS_WACK_DREQ10:
		return ("NS_WACK_DREQ10");
	case NS_WACK_DREQ11:
		return ("NS_WACK_DREQ11");
	case NS_NOSTATES:
		return ("NS_NOSTATES");
	default:
		return ("(unknown)");
	}
}

static const char *
nl_strerror(int error)
{
	if (err < 0)
		err = NSYSERR;
	switch (error) {
	case NBADADDR:
		return ("Incorrect address format/illegal address information.");
	case NBADOPT:
		return ("Options in incorrect format or contain illegal information.");
	case NACCESS:
		return ("User did no have proper permissions.");
	case NNOADDR:
		return ("NS Provider could not allocate address.");
	case NOUTSTATE:
		return ("Primitive was issued in wrong sequence.");
	case NBADSEQ:
		return ("Sequence number in primitive was incorrect/illegal.");
	case NSYSERR:
		return ("UNIX system error occured.");
	case NBADDATA:
		return ("User data spec. outside rnage supported by NS provider.");
	case NBADFLAG:
		return ("Flags specified in primitive were illegal/incorrect.");
	case NNOTSUPPORT:
		return ("Primitive type not supported by the NS provider.");
	case NBOUND:
		return ("Illegal second attempt to bind listenter or default listener.");
	case NBADQOSPARAM:
		return ("QOS values outside range supported by NS provider.");
	case NBADQOSTYPE:
		return ("QOS structure type not supported by NS provider.");
	case NBADTOKEN:
		return ("Token used is not associated with an open stream.");
	case NNOPROTOID:
		return ("Protocol id could not be allocated.");
	default:
		return ("(unknown)");
	}
}

static int
nl_get_state(struct nl *nl)
{
	return (nl->state);
}

static int
nl_set_state(struct nl *nl, int newstate)
{
	int oldstate = nl->state;

	if (newstate != oldstate) {
		nl->state = newstate;
		mi_strlog(nl->oq, STRLOGST, SL_TRACE, "%s <- %s", nl_statename(newstate),
			  nl_statename(oldstate));
	}
	return (newstate);
}

static int
nl_save_state(struct nl *nl)
{
	return ((nl->oldstate = nl_get_state(nl)));
}

static int
nl_restore_state(struct nl *nl)
{
	return (nl_set_state(nl, nl->oldstate));
}

static inline const char *
dl_iocname(int cmd)
{
	switch (cmd) {
	default:
		return ("(unknown)");
	}
}

static inline const char *
dl_primname(dl_ulong prim)
{
	switch (prim) {
	case DL_INFO_REQ:
		return ("DL_INFO_REQ");
	case DL_INFO_ACK:
		return ("DL_INFO_ACK");
	case DL_ATTACH_REQ:
		return ("DL_ATTACH_REQ");
	case DL_DETACH_REQ:
		return ("DL_DETACH_REQ");
	case DL_BIND_REQ:
		return ("DL_BIND_REQ");
	case DL_BIND_ACK:
		return ("DL_BIND_ACK");
	case DL_UNBIND_REQ:
		return ("DL_UNBIND_REQ");
	case DL_OK_ACK:
		return ("DL_OK_ACK");
	case DL_ERROR_ACK:
		return ("DL_ERROR_ACK");
	case DL_SUBS_BIND_REQ:
		return ("DL_SUBS_BIND_REQ");
	case DL_SUBS_BIND_ACK:
		return ("DL_SUBS_BIND_ACK");
	case DL_SUBS_UNBIND_REQ:
		return ("DL_SUBS_UNBIND_REQ");
	case DL_ENABMULTI_REQ:
		return ("DL_ENABMULTI_REQ");
	case DL_DISABMULTI_REQ:
		return ("DL_DISABMULTI_REQ");
	case DL_PROMISCON_REQ:
		return ("DL_PROMISCON_REQ");
	case DL_PROMISCOFF_REQ:
		return ("DL_PROMISCOFF_REQ");
	case DL_UNITDATA_REQ:
		return ("DL_UNITDATA_REQ");
	case DL_UNITDATA_IND:
		return ("DL_UNITDATA_IND");
	case DL_UDERROR_IND:
		return ("DL_UDERROR_IND");
	case DL_UDQOS_REQ:
		return ("DL_UDQOS_REQ");
	case DL_CONNECT_REQ:
		return ("DL_CONNECT_REQ");
	case DL_CONNECT_IND:
		return ("DL_CONNECT_IND");
	case DL_CONNECT_RES:
		return ("DL_CONNECT_RES");
	case DL_CONNECT_CON:
		return ("DL_CONNECT_CON");
	case DL_TOKEN_REQ:
		return ("DL_TOKEN_REQ");
	case DL_TOKEN_ACK:
		return ("DL_TOKEN_ACK");
	case DL_DISCONNECT_REQ:
		return ("DL_DISCONNECT_REQ");
	case DL_DISCONNECT_IND:
		return ("DL_DISCONNECT_IND");
	case DL_RESET_REQ:
		return ("DL_RESET_REQ");
	case DL_RESET_IND:
		return ("DL_RESET_IND");
	case DL_RESET_RES:
		return ("DL_RESET_RES");
	case DL_RESET_CON:
		return ("DL_RESET_CON");
	case DL_DATA_ACK_REQ:
		return ("DL_DATA_ACK_REQ");
	case DL_DATA_ACK_IND:
		return ("DL_DATA_ACK_IND");
	case DL_DATA_ACK_STATUS_IND:
		return ("DL_DATA_ACK_STATUS_IND");
	case DL_REPLY_REQ:
		return ("DL_REPLY_REQ");
	case DL_REPLY_IND:
		return ("DL_REPLY_IND");
	case DL_REPLY_STATUS_IND:
		return ("DL_REPLY_STATUS_IND");
	case DL_REPLY_UPDATE_REQ:
		return ("DL_REPLY_UPDATE_REQ");
	case DL_REPLY_UPDATE_STATUS_IND:
		return ("DL_REPLY_UPDATE_STATUS_IND");
	case DL_XID_REQ:
		return ("DL_XID_REQ");
	case DL_XID_IND:
		return ("DL_XID_IND");
	case DL_XID_RES:
		return ("DL_XID_RES");
	case DL_XID_CON:
		return ("DL_XID_CON");
	case DL_TEST_REQ:
		return ("DL_TEST_REQ");
	case DL_TEST_IND:
		return ("DL_TEST_IND");
	case DL_TEST_RES:
		return ("DL_TEST_RES");
	case DL_TEST_CON:
		return ("DL_TEST_CON");
	case DL_PHYS_ADDR_REQ:
		return ("DL_PHYS_ADDR_REQ");
	case DL_PHYS_ADDR_ACK:
		return ("DL_PHYS_ADDR_ACK");
	case DL_SET_PHYS_ADDR_REQ:
		return ("DL_SET_PHYS_ADDR_REQ");
	case DL_GET_STATISTICS_REQ:
		return ("DL_GET_STATISTICS_REQ");
	case DL_GET_STATISTICS_ACK:
		return ("DL_GET_STATISTICS_ACK");
	default:
		return ("(unknown)");
	}
}

static inline const char *
dl_statename(dl_ulong state)
{
	switch (state) {
	case DL_UNATTACHED:
		return ("DL_UNATTACHED");
	case DL_ATTACH_PENDING:
		return ("DL_ATTACH_PENDING");
	case DL_DETACH_PENDING:
		return ("DL_DETACH_PENDING");
	case DL_UNBOUND:
		return ("DL_UNBOUND");
	case DL_BIND_PENDING:
		return ("DL_BIND_PENDING");
	case DL_UNBIND_PENDING:
		return ("DL_UNBIND_PENDING");
	case DL_IDLE:
		return ("DL_IDLE");
	case DL_UDQOS_PENDING:
		return ("DL_UDQOS_PENDING");
	case DL_OUTCON_PENDING:
		return ("DL_OUTCON_PENDING");
	case DL_INCON_PENDING:
		return ("DL_INCON_PENDING");
	case DL_CONN_RES_PENDING:
		return ("DL_CONN_RES_PENDING");
	case DL_DATAXFER:
		return ("DL_DATAXFER");
	case DL_USER_RESET_PENDING:
		return ("DL_USER_RESET_PENDING");
	case DL_PROV_RESET_PENDING:
		return ("DL_PROV_RESET_PENDING");
	case DL_RESET_RES_PENDING:
		return ("DL_RESET_RES_PENDING");
	case DL_DISCON8_PENDING:
		return ("DL_DISCON8_PENDING");
	case DL_DISCON9_PENDING:
		return ("DL_DISCON9_PENDING");
	case DL_DISCON11_PENDING:
		return ("DL_DISCON11_PENDING");
	case DL_DISCON12_PENDING:
		return ("DL_DISCON12_PENDING");
	case DL_DISCON13_PENDING:
		return ("DL_DISCON13_PENDING");
	case DL_SUBS_BIND_PND:
		return ("DL_SUBS_BIND_PND");
	case DL_SUBS_UNBIND_PND:
		return ("DL_SUBS_UNBIND_PND");
	default:
		return ("(unknown)");
	}
}

static inline const char *
dl_errname(dl_long error)
{
	if (error < 0)
		return ("DL_SYSERR");
	switch (error) {
	case DL_ACCESS:
		return ("DL_ACCESS");
	case DL_BADADDR:
		return ("DL_BADADDR");
	case DL_BADCORR:
		return ("DL_BADCORR");
	case DL_BADDATA:
		return ("DL_BADDATA");
	case DL_BADPPA:
		return ("DL_BADPPA");
	case DL_BADPRIM:
		return ("DL_BADPRIM");
	case DL_BADQOSPARAM:
		return ("DL_BADQOSPARAM");
	case DL_BADQOSTYPE:
		return ("DL_BADQOSTYPE");
	case DL_BADSAP:
		return ("DL_BADSAP");
	case DL_BADTOKEN:
		return ("DL_BADTOKEN");
	case DL_BOUND:
		return ("DL_BOUND");
	case DL_INITFAILED:
		return ("DL_INITFAILED");
	case DL_NOADDR:
		return ("DL_NOADDR");
	case DL_NOTINIT:
		return ("DL_NOTINIT");
	case DL_OUTSTATE:
		return ("DL_OUTSTATE");
	case DL_SYSERR:
		return ("DL_SYSERR");
	case DL_UNSUPPORTED:
		return ("DL_UNSUPPORTED");
	case DL_UNDELIVERABLE:
		return ("DL_UNDELIVERABLE");
	case DL_NOTSUPPORTED:
		return ("DL_NOTSUPPORTED");
	case DL_TOOMANY:
		return ("DL_TOOMANY");
	case DL_NOTENAB:
		return ("DL_NOTENAB");
	case DL_BUSY:
		return ("DL_BUSY");
	case DL_NOAUTO:
		return ("DL_NOAUTO");
	case DL_NOXIDAUTO:
		return ("DL_NOXIDAUTO");
	case DL_NOTESTAUTO:
		return ("DL_NOTESTAUTO");
	case DL_XIDAUTO:
		return ("DL_XIDAUTO");
	case DL_TESTAUTO:
		return ("DL_TESTAUTO");
	case DL_PENDING:
		return ("DL_PENDING");
	default:
		return ("(unknown)");
	}
}

static inline const char *
dl_strerror(dl_long error)
{
	if (error < 0)
		return ("UNIX system error occurred.");
	switch (error) {
	case DL_ACCESS:
		return ("Improper permissions for request.");
	case DL_BADADDR:
		return ("DLSAP addr in improper format or invalid.");
	case DL_BADCORR:
		return ("Seq number not from outstand DL_CONN_IND.");
	case DL_BADDATA:
		return ("User data exceeded provider limit.");
	case DL_BADPPA:
		return ("Specified PPA was invalid.");
	case DL_BADPRIM:
		return ("Primitive received not known by provider.");
	case DL_BADQOSPARAM:
		return ("QOS parameters contained invalid values.");
	case DL_BADQOSTYPE:
		return ("QOS structure type is unknown/unsupported.");
	case DL_BADSAP:
		return ("Bad LSAP selector.");
	case DL_BADTOKEN:
		return ("Token used not an active stream.");
	case DL_BOUND:
		return ("Attempted second bind with dl_max_conind.");
	case DL_INITFAILED:
		return ("Physical Link initialization failed.");
	case DL_NOADDR:
		return ("Provider couldn't allocate alt. address.");
	case DL_NOTINIT:
		return ("Physical Link not initialized.");
	case DL_OUTSTATE:
		return ("Primitive issued in improper state.");
	case DL_SYSERR:
		return ("UNIX system error occurred.");
	case DL_UNSUPPORTED:
		return ("Requested serv. not supplied by provider.");
	case DL_UNDELIVERABLE:
		return ("Previous data unit could not be delivered.");
	case DL_NOTSUPPORTED:
		return ("Primitive is known but not supported.");
	case DL_TOOMANY:
		return ("Limit exceeded.");
	case DL_NOTENAB:
		return ("Promiscuous mode not enabled.");
	case DL_BUSY:
		return ("Other streams for PPA in post-attached state.");
	case DL_NOAUTO:
		return ("Automatic handling of XID and TEST response not supported.");
	case DL_NOXIDAUTO:
		return ("Automatic handling of XID not supported.");
	case DL_NOTESTAUTO:
		return ("Automatic handling of TEST not supported.");
	case DL_XIDAUTO:
		return ("Automatic handling of XID response.");
	case DL_TESTAUTO:
		return ("Automatic handling of TEST response.");
	case DL_PENDING:
		return ("pending outstanding connect indications.");
	default:
		return ("(unknown)");
	}
}

static dl_ulong
dl_get_state(sturct dl * dl)
{
	return (dl->state);
}

static dl_ulong
dl_set_state(struct dl *dl, dl_ulong newstate)
{
	dl_ulong oldstate = dl->state;

	if (newstate != oldstate) {
		dl->state = newstate;
		dl->proto.info.dl_current_state = newstate;
		mi_strlog(dl->oq, STRLOGST, SL_TRACE, "%s <- %s", dl_statename(newstate),
			  dl_statename(oldstate));
	}
	return (newstate);
}

static dl_ulong
dl_save_state(struct dl *dl)
{
	return ((dl->oldstate = dl_get_state(dl)));
}

static dl_ulong
dl_restore_state(struct dl *dl)
{
	return (dl_set_state(dl, dl->oldstate));
}

/*
 * --------------------------------------------------------------------------
 *
 * NLI PROVIDER TO NLI USER PRIMITIVES ISSUED UPSTREAM
 *
 * --------------------------------------------------------------------------
 */

static fastcall noinline __unlikely int
m_error(struct nl *nl, queue_t *q, mblk_t *msg)
{
}

/**
 * nl_conn_ind: - issue N_CI indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @conn_id: connection identifier
 * @cons: CONS call when true
 * @cld: called address
 * @clg: calling address
 * @qos: qos parameters (or NULL if no qos)
 * @dp: user data
 */
static fastcall noinline __unlikely int
nl_conn_ind(struct nl *nl, queue_t *q, mblk_t *msg, int conn_id, uchar cons, struct xaddrf *cld,
	    struct xaddrf *clg, struct qosformat *qos, mblk_t *dp)
{
	struct xcallf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(nl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->xl_type = XL_CTL;
			p->xl_command = N_CI;
			p->conn_id = cond_id;
			p->CONS_call = cons;
			p->negotiate_qos = qos ? 1 : 0;
			bcopy(cld, &p->calledaddr, sizeof(*cld));
			bcopy(clg, &p->callingaddr, sizeof(*clg));
			if (qos)
				bcopy(qos, &p->qos, sizeof(*qos));
			else
				bzero(&p->qos, sizeof(*qos));
			mp->b_wptr += sizeof(*p);
			mp->b_cont = dp;
			if (msg && msg->b_cont == dp)
				msg->b_cont = NULL;
			freemsg(msg);
			nl->coninds++;
			nl_set_state(nl, NS_WRES_CIND);
			mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_CI");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * nl_conn_con: - issue N_CC indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @conn_id: connection identifier
 * @cons: CONS call when true
 * @res: responding address
 * @qos: qos parameters (or NULL if no qos)
 * @dp: user data
 */
static fastcall noinline __unlikely int
nl_conn_con(struct nl *nl, queue_t *q, mblk_t *msg, int conn_id, uchar cons, struct xaddrf *res,
	    struct qosformat *qos, mblk_t *dp)
{
	struct xccnff *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(nl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->xl_type = XL_CTL;
			p->xl_command = N_CC;
			p->conn_id = conn_id;
			p->CONS_call = cons;
			p->negotiate_qos = qos ? 1 : 0;
			bcopy(res, &p->responder, sizeof(*res));
			if (qos)
				bcopy(qos, &p->rqos, sizeof(*qos));
			else
				bzero(&p->rqos, sizeof(*qos));
			mp->b_wptr += sizeof(*p);
			mp->b_cont = dp;
			if (msg && msg->b_cont == dp)
				msg->b_cont = NULL;
			freemsg(msg);
			nl_set_state(nl, NS_DATA_XFER);
			mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_CC");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * nl_discon_ind: - issue N_DI indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @orig: originator
 * @reason: reason
 * @cause: cause
 * @diag: diagnostic
 * @conn_id: connection id
 * @res: responding address
 * @def: deflected address
 * @qos: qos parameters (or NULL)
 * @dp: user data (CUD)
 */
static fastcall noinline __unlikely int
nl_discon_ind(struct nl *nl, queue_t *q, mblk_t *msg, uchar orig, uchar reason, uchar cause,
	      uchar diag, int conn_id, struct xaddrf *res, struct xaddrf *def,
	      struct qosformat *qos, mblk_t *dp)
{
	struct xdiscf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(nl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->xl_type = XL_CTL;
			p->xl_command = N_DI;
			p->originator = orig;
			p->reason = reason;
			p->cause = cause;
			p->diag = diag;
			p->conn_id = conn_id;
			p->indicated_qos = qos ? 1 : 0;
			bcopy(res, &p->responder, sizeof(*res));
			bcopy(def, &p->deflected, sizeof(*def));
			if (qos)
				bcopy(qos, &p->qos, sizeof(*qos));
			else
				bzero(&p->qos, sizeof(*qos));
			mp->b_wptr += sizeof(*p);
			mp->b_cont = dp;
			if (msg && msg->b_cont == dp)
				msg->b_cont = NULL;
			freemsg(msg);
			nl_set_state(nl, nl_sequence_free(nl, conn_id) ? NS_WRES_CIND : NS_IDLE);
			mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_DI");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * nl_discon_con: - issue N_DC indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @qos: qos parameters (or NULL for no qos)
 */
static fastcall noinline __unlikely int
nl_discon_con(struct nl *nl, queue_t *q, mblk_t *msg, struct qosformat *qos)
{
	struct xdcnff *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(nl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->xl_type = XL_CTL;
			p->xl_command = N_DC;
			p->indicated_qos = qos ? 1 : 0;
			if (qos)
				bcopy(qos, &p->qos, sizeof(*qos));
			else
				bcopy(&p->qos, sizeof(*qos));
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			nl_set_state(nl, (nl->coninds > 0) ? NS_WRES_CIND : NS_IDLE);
			mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_DC");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * nl_abort_ind: - issue N_Abort indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 */
static fastcall noinline __unlikely int
nl_abort_ind(struct nl *nl, queue_t *q, mblk_t *msg)
{
	struct xabortf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(nl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->xl_type = XL_CTL;
			p->xl_command = N_Abort;
			mp->b_wptr += sizeof(*p);
			nl_set_state(nl, (nl->coninds > 0) ? NS_WRES_CIND : NS_IDLE);
			mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_Abort");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * nl_data_ind: - issue N_Data indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @more: more data in nsdu
 * @dbit: D-bit data
 * @qbit: Q-bit data
 * @dp: user data
 */
static fastcall inline __hot_in int
nl_data_ind(struct nl *nl, queue_t *q, mblk_t *msg, uchar more, uchar dbit, uchar qbit, mblk_t *dp)
{
	struct xdataf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(nl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->xl_type = XL_DAT;
			p->xl_command = N_Data;
			p->More = more;
			p->setDbit = dbit;
			p->setQbit = qbit;
			mp->b_wptr += sizeof(*p);
			mp->b_cont = dp;
			if (msg && msg->b_cont == dp)
				msg->b_cont = NULL;
			freemsg(msg);
			if (dbit && !more)
				nl->datinds++;
			nl_set_state(nl, NS_WRES_CIND);
			mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_Data");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * nl_exdata_ind: - issue N_EData indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @dp: user data
 */
static fastcall inline __hot_in int
nl_exdata_ind(struct nl *nl, queue_t *q, mblk_t *msg)
{
	struct xedataf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(bcanputnext(nl->oq, 1))) {
			DB_TYPE(mp) = M_PROTO;
			mp->b_band = 1;
			p = (typeof(p)) mp->b_wptr;
			p->xl_type = XL_DAT;
			p->xl_command = N_EData;
			mp->b_wptr += sizeof(*p);
			mp->b_cont = dp;
			if (msg && msg->b_cont == dp)
				msg->b_cont = NULL;
			freemsg(msg);
			nl->coninds++;
			nl_set_state(nl, NS_WRES_CIND);
			mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_EData");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * nl_bind_ack: - issue N_Xlisten indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @lmax: maximum number of CIs at a time
 * @pri; priority request
 * @result: listen result
 * @dp: user data containing called address specification
 */
static fastcall noinline __unlikely int
nl_bind_ack(struct nl *nl, queue_t *q, mblk_t *msg, int lmax, int result, mblk_t *dp)
{
	struct xlistenf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		DB_TYPE(mp) = M_PCPROTO;
		p = (typeof(p)) mp->b_wptr;
		p->xl_type = XL_CTL;
		p->xl_command = N_Xlisten;
		p->lmax = lmax;
		p->l_result = result;
		mp->b_wptr += sizeof(*p);
		mp->b_cont = dp;
		if (msg && msg->b_cont == dp)
			msg->b_cont = NULL;
		freemsg(msg);
		nl_set_state(nl, (result == 0) ? NS_IDLE : NS_UNBND);
		mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_Xlisten");
		putnext(nl->oq, mp);
		return (0);
	}
	return (-ENOBUFS);
}

/**
 * nl_unbind_ack: - issue N_Xcanlis indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @result: result of listen cancel
 */
static fastcall noinline __unlikely int
nl_unbind_ack(struct nl *nl, queue_t *q, mblk_t *msg, int result)
{
	struct xcanlisf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		DB_TYPE(mp) = M_PCPROTO;
		p = (typeof(p)) mp->b_wptr;
		p->xl_type = XL_CTL;
		p->xl_command = N_Xcanlis;
		p->c_result = result;
		mp->b_wptr += sizeof(*p);
		freemsg(msg);
		nl_set_state(nl, (result == 0) ? NS_UNBND : NS_IDLE);
		mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_Xcanlis");
		putnext(nl->oq, mp);
		return (0);
	}
	return (-ENOBUFS);
}

/**
 * nl_datack_ind: - issue N_DAck or N_EAck indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @exp: expedited acknowledgement
 */
static fastcall noinline __unlikely int
nl_datack_ind(struct nl *nl, queue_t *q, mblk_t *msg)
{
	struct xdatacf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(bcanputnext(nl->oq, exp ? 1 : 0))) {
			DB_TYPE(mp) = M_PROTO;
			mp->b_band = exp ? 1 : 0;
			p = (typeof(p)) mp->b_wptr;
			p->xl_type = XL_DAT;
			p->xl_command = exp ? N_EAck : N_DAck;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			if (exp)
				nl->edatcons--;
			else
				nl->datcons--;
			nl->coninds++;
			nl_set_state(nl, NS_WRES_CIND);
			mi_strlog(nl->oq, STRLOGTX, SL_TRACE, exp ? "<- NEAck" : "<- N_DAck");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * nl_reset_ind: - issue N_RI indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @orig: originator
 * @reason: reason
 * @cause: cause
 * @diag: diagnostic
 */
static fastcall noinline __unlikely int
nl_reset_ind(struct nl *nl, queue_t *q, mblk_t *msg, uchar orig, uchar reason, uchar cause,
	     uchar diag)
{
	struct xrstf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(nl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->xl_type = XL_CTL;
			p->xl_command = N_RI;
			p->originator = orig;
			p->reason = reason;
			p->cause = cause;
			p->diag = diag;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			nl->resinds++;
			nl_set_state(nl, NS_WRES_RIND);
			mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_RI");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * nl_reset_con: - issue N_RC indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 */
static fastcall noinline __unlikely int
nl_reset_con(struct nl *nl, queue_t *q, mblk_t *msg)
{
	struct xrscf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(nl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->xl_type = XL_CTL;
			p->xl_command = N_RC;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			nl->rescons--;
			nl_set_state(nl, (nl->rescons > 0) ? NS_WCON_RREQ : NS_DATA_XFER);
			mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_RC");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * nl_attach_ack: - issue N_PVC_ATTACH indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @lci: logical channel
 * @sn_id: subnetwork (link) identifier 
 * @ack: receipt acknowledgement requested when set
 * @lmi: nsdulimit requested when set
 * @nsdulimit: the limit
 * @result: result of attach
 */
static fastcall noinline __unlikely int
nl_attach_ack(struct nl *nl, queue_t *q, mblk_t *msg, ushort lci, uint sn_id, uchar ack, uchar lmi,
	      int nsdulimit, int result)
{
	struct pvcattf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		DB_TYPE(mp) = M_PCPROTO;
		p = (typeof(p)) mp->b_wptr;
		p->xl_type = XL_CTL;
		p->xl_command = N_PVC_ATTACH;
		p->lci = lci;
		p->sn_id = sn_id;
		p->reqackservice = ack;
		p->reqnsdulimit = lim;
		p->nsdulimit = nsdulimit;
		p->result_code = result;
		mp->b_wptr += sizeof(*p);
		freemsg(msg);
		nl_set_state(nl, (result == 0) ? NS_DATA_XFER : NS_UNBND);
		mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_PVC_ATTACH");
		putnext(nl->oq, mp);
		return (0);
	}
	return (-ENOBUFS);
}

/**
 * nl_detach_ack: - issue N_PVC_DETACH indication
 * @nl: network layer private structure
 * @q: active queue
 * @msg: message to free upon success
 * @reason: reason
 */
static fastcall noinline __unlikely int
nl_detach_ack(struct nl *nl, queue_t *q, mblk_t *msg, int reason)
{
	struct pvcdetf *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(nl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->xl_type = XL_CTL;
			p->xl_command = N_PVC_DETACH;
			p->reason_code = reason;
			mp->b_wptr += sizeof(*p);
			nl_set_state(nl, (reason == 0) ? NS_UNBND : NS_DATA_XFER);
			mi_strlog(nl->oq, STRLOGTX, SL_TRACE, "<- N_PVC_DETACH");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/*
 * --------------------------------------------------------------------------
 *
 * DLPI USER TO DLPI PROVIDER PRIMITIVES ISSUED DOWNSTREAM
 *
 * --------------------------------------------------------------------------
 */

/**
 * dl_info_req: - issued DL_INFO_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 */
static fastcall noinline __unlikely int
dl_info_req(struct dl *dl, queue_t *q, mblk_t *msg)
{
	dl_info_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_INFO_REQ;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_INFO_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_attach_req: - issued DL_ATTACH_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @ppa; physical point of attachment to attach
 */
static fastcall noinline __unlikely int
dl_attach_req(struct dl *dl, queue_t *q, mblk_t *msg, dl_ulong ppa)
{
	dl_attach_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_ATTACH_REQ;
			p->dl_ppa = ppa;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			dl_set_state(dl, DL_ATTACH_PENDING);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_ATTACH_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_detach_req: - issued DL_DETACH_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 */
static fastcall noinline __unlikely int
dl_detach_req(struct dl *dl, queue_t *q, mblk_t *msg)
{
	dl_detach_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_DETACH_REQ;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			dl_set_state(dl, DL_DETACH_PENDING);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_DETACH_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_bind_req: - issued DL_BIND_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @sap: dlsap address identification
 * @conind: maximum outstanding connection indications
 * @serv: service mode
 * @mgmt: connection management stream when set
 * @flags: XID and TEST flags
 */
static fastcall noinline __unlikely int
dl_bind_req(struct dl *dl, queue_t *q, mblk_t *msg, dl_ulong sap, dl_ulong conind, dl_ushort serv,
	    dl_ushort mgmt, dl_ulong flags)
{
	dl_bind_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_BIND_REQ;
			p->dl_sap = sap;
			p->dl_max_conind = conind;
			p->dl_service_mode = serv;
			p->dl_conn_mgmt = mgmt;
			p->dl_xidtest_flg = flags;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			dl_set_state(dl, DL_BIND_PENDING);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_BIND_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_unbind_req: - issued DL_UNBIND_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 */
static fastcall noinline __unlikely int
dl_unbind_req(struct dl *dl, queue_t *q, mblk_t *msg)
{
	dl_unbind_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_UNBIND_REQ;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			dl_set_state(dl, DL_UNBIND_PENDING);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_UNBIND_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_subs_bind_req: - issued DL_SUBS_BIND_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @sap: buffer describing sap
 * @cls: bind class
 */
static fastcall noinline __unlikely int
dl_subs_bind_req(struct dl *dl, queue_t *q, mblk_t *msg, struct strbuf *sap, dl_ulong cls)
{
	dl_subs_bind_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + sap->len, BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_SUBS_BIND_REQ;
			p->dl_subs_sap_length = sap->len;
			p->dl_subs_sap_offset = sizeof(*p);
			p->dl_subs_bind_class = cls;
			mp->b_wptr += sizeof(*p);
			bcopy(sap->buf, mp->b_wptr, sap->len);
			mp->b_wptr += sap->len;
			freemsg(msg);
			dl_set_state(dl, DL_SUBS_BIND_PND);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_SUBS_BIND_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_subs_unbind_req: - issued DL_SUBS_UNBIND_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 */
static fastcall noinline __unlikely int
dl_subs_unbind_req(struct dl *dl, queue_t *q, mblk_t *msg)
{
	dl_subs_unbind_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_SUBS_UNBIND_REQ;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			dl_set_state(dl, DL_SUBS_UNBIND_PND);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_SUBS_UNBIND_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_enabmulti_req: - issued DL_ENABMULTI_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @add: buffer describing address
 */
static fastcall noinline __unlikely int
dl_enabmulti_req(struct dl *dl, queue_t *q, mblk_t *msg, struct strbuf *add)
{
	dl_enabmulti_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + add->len, BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_ENABMULTI_REQ;
			p->dl_addr_length = add->len;
			p->dl_addr_offset = sizeof(*p);
			mp->b_wptr += sizeof(*p);
			bcopy(add->buf, mp->b_wptr, add->len);
			mp->b_wptr += add->len;
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_ENABMULTI_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_disabmulti_req: - issued DL_DISABMULTI_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @add: buffer describing address
 */
static fastcall noinline __unlikely int
dl_disabmulti_req(struct dl *dl, queue_t *q, mblk_t *msg, struct strbuf *add)
{
	dl_disabmulti_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + add->len, BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_DISABMULTI_REQ;
			p->dl_addr_length = add->len;
			p->dl_addr_offset = sizeof(*p);
			mp->b_wptr += sizeof(*p);
			bcopy(add->buf, mp->b_wptr, add->len);
			mp->b_wptr += add->len;
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_DISABMULTI_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_promiscon_req: - issued DL_PROMISCON_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @level: promiscuous level
 */
static fastcall noinline __unlikely int
dl_promiscon_req(struct dl *dl, queue_t *q, mblk_t *msg, dl_ulong level)
{
	dl_promiscon_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_PROMISCON_REQ;
			p->dl_level = level;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_PROMISCON_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_promiscoff_req: - issued DL_PROMISCOFF_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @level: promiscious level
 */
static fastcall noinline __unlikely int
dl_promiscoff_req(struct dl *dl, queue_t *q, mblk_t *msg, dl_ulong level)
{
	dl_promiscoff_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_PROMISCOFF_REQ;
			p->dl_level = level;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_PROMISCOFF_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_unitdata_req: - issued DL_UNITDATA_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @dst: buffer describing destination address
 * @pri: priority
 * @dp: user data
 */
static fastcall noinline __unlikely int
dl_unitdata_req(struct dl *dl, queue_t *q, mblk_t *msg, struct strbuf *dst, dl_ulong pri,
		mblk_t *dp)
{
	dl_unitdata_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + dst->len, BPRI_MED)))) {
		if (likely(bcanputnext(dl->oq, pri))) {
			DB_TYPE(mp) = M_PROTO;
			mp->b_band = pri;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_UNITDATA_REQ;
			p->dl_dest_addr_length = dst->len;
			p->dl_dest_addr_offset = sizeof(*p);
			p->dl_priority = pri;
			mp->b_wptr += sizeof(*p);
			bcopy(dst->buf, mp->b_wptr, dst->len);
			mp->b_wptr += dst->len;
			mp->b_cont = dp;
			if (msg && msg->b_cont == dp)
				msg->b_cont = NULL;
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_UNITDATA_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_udqos_req: - issued DL_UDQOS_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @qos: buffer describing qos parameters
 */
static fastcall noinline __unlikely int
dl_udqos_req(struct dl *dl, queue_t *q, mblk_t *msg, struct strbuf *qos)
{
	dl_udqos_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + qos->len, BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_UDQOS_REQ;
			p->dl_qos_length = qos->len;
			p->dl_qos_offset = sizeof(*p);
			mp->b_wptr += sizeof(*p);
			bcopy(qos->buf, mp->b_wptr, qos->len);
			mp->b_wptr += qos->len;
			freemsg(msg);
			dl_set_state(dl, DL_UDQOS_PENDING);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_UDQOS_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_connect_req: - issued DL_CONNECT_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @dst: buffer describing destination address
 * @qos: buffer describing qos parameters
 */
static fastcall noinline __unlikely int
dl_connect_req(struct dl *dl, queue_t *q, mblk_t *msg)
{
	dl_connect_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + dst->len + qos->len, BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_CONNECT_REQ;
			p->dl_dest_addr_length = dst->len;
			p->dl_dest_addr_offset = sizeof(*p);
			p->dl_qos_length = qos->len;
			p->dl_qos_offset = sizeof(*p) + dst->len;
			p->dl_growth = 0;
			mp->b_wptr += sizeof(*p);
			bcopy(dst->buf, mp->b_wptr, dst->len);
			mp->b_wptr += dst->len;
			bcopy(qos->buf, mp->b_wptr, qos->len);
			mp->b_wptr += qos->len;
			freemsg(msg);
			dl_set_state(dl, DL_OUTCON_PENDING);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_CONNECT_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_connect_res: - issued DL_CONNECT_RES primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @seq: sequence number
 * @tok: token
 * @qos: buffer describing qos parameters
 */
static fastcall noinline __unlikely int
dl_connect_res(struct dl *dl, queue_t *q, mblk_t *msg, dl_ulong seq, dl_ulong tok,
	       struct strbuf *qos)
{
	dl_connect_res_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + qos->len, BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_CONNECT_RES;
			p->dl_correlation = seq;
			p->dl_resp_token = tok;
			p->dl_qos_length = qos->len;
			p->dl_qos_offset = sizeof(*p);
			p->dl_growth = 0;
			mp->b_wptr += sizeof(*p);
			bcopy(qos->buf, mp->b_wptr, qos->len);
			mp->b_wptr += qos->len;
			freemsg(msg);
			dl_set_state(dl, DL_CONN_RES_PENDING);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_CONNECT_RES ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_token_req: - issued DL_TOKEN_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 */
static fastcall noinline __unlikely int
dl_token_req(struct dl *dl, queue_t *q, mblk_t *msg)
{
	dl_token_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		DB_TYPE(mp) = M_PCPROTO;
		p = (typeof(p)) mp->b_wptr;
		p->dl_primitive = DL_TOKEN_REQ;
		mp->b_wptr += sizeof(*p);
		freemsg(msg);
		mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_TOKEN_REQ ->");
		putnext(nl->oq, mp);
		return (0);
	}
	return (-ENOBUFS);
}

/**
 * dl_disconnect_req: - issued DL_DISCONNECT_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @reason: reason
 * @seq: sequence number
 */
static fastcall noinline __unlikely int
dl_disconnect_req(struct dl *dl, queue_t *q, mblk_t *msg, dl_ulong reason, dl_ulong seq)
{
	dl_disconnect_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_DISCONNECT_REQ;
			p->dl_reason = reason;
			p->dl_correlation = seq;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			if (seq)
				dl->coninds--;
			dl_set_state(dl, (dl->coninds > 0) ? DL_INCON_PENDING : DL_IDLE);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_DISCONNECT_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_reset_req: - issued DL_RESET_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 */
static fastcall noinline __unlikely int
dl_reset_req(struct dl *dl, queue_t *q, mblk_t *msg)
{
	dl_reset_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_RESET_REQ;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			dl_set_state(dl, DL_USER_RESET_PENDING);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_RESET_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_reset_res: - issued DL_RESET_RES primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 */
static fastcall noinline __unlikely int
dl_reset_res(struct dl *dl, queue_t *q, mblk_t *msg)
{
	dl_reset_res_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_RESET_RES;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			dl_set_state(dl, DL_DATAXFER);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_RESET_RES ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_xid_req: - issued DL_XID_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @flag: poll/final flag
 * @dst: buffer describing destination address
 * @dp: user data
 */
static fastcall noinline __unlikely int
dl_xid_req(struct dl *dl, queue_t *q, mblk_t *msg, dl_ulong flag, struct strbuf *dst, mblk_t *dp)
{
	dl_xid_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + dst->len, BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_XID_REQ;
			p->dl_flag = flag;
			p->dl_dest_addr_length = dst->len;
			p->dl_dest_addr_offset = sizeof(*p);
			mp->b_wptr += sizeof(*p);
			bcopy(dst->buf, mp->b_wptr, dst->len);
			mp->b_wptr += dst->len;
			mp->b_cont = dp;
			if (msg && msg->b_cont == dp)
				msg->b_cont = NULL;
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_XID_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_xid_res: - issued DL_XID_RES primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @flag: poll/final flag
 * @dst: buffer describing destination address
 * @dp: user data
 */
static fastcall noinline __unlikely int
dl_xid_res(struct dl *dl, queue_t *q, mblk_t *msg, dl_ulong flag, struct strbuf *dst, mblk_t *dp)
{
	dl_xid_res_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + dst->len, BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_XID_RES;
			p->dl_flag = flag;
			p->dl_dest_addr_length = dst->len;
			p->dl_dest_addr_offset = sizeof(*p);
			mp->b_wptr += sizeof(*p);
			bcopy(dst->buf, mp->b_wptr, dst->len);
			mp->b_wptr += dst->len;
			mp->b_cont = dp;
			if (msg && msg->b_cont == dp)
				msg->b_cont = NULL;
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_XID_RES ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_test_req: - issued DL_TEST_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @flag: poll/final flag
 * @dst: buffer describing destination address
 * @dp: user data
 */
static fastcall noinline __unlikely int
dl_test_req(struct dl *dl, queue_t *q, mblk_t *msg, dl_ulong flag, struct strbuf *dst, mblk_t *dp)
{
	dl_test_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + dst->len, BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_TEST_REQ;
			p->dl_flag = flag;
			p->dl_dest_addr_length = dst->len;
			p->dl_dest_addr_offset = sizeof(*p);
			mp->b_wptr += sizeof(*p);
			bcopy(dst->buf, mp->b_wptr, dst->len);
			mp->b_wptr += dst->len;
			mp->b_cont = dp;
			if (msg && msg->b_cont == dp)
				msg->b_cont = NULL;
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_TEST_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_test_res: - issued DL_TEST_RES primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @flag: poll/final flag
 * @dst: buffer describing destination address
 * @dp: user data
 */
static fastcall noinline __unlikely int
dl_test_res(struct dl *dl, queue_t *q, mblk_t *msg, dl_ulong flag, struct strbuf *dst, mblk_t *dp)
{
	dl_test_res_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + dst->len, BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_TEST_RES;
			p->dl_flag = flag;
			p->dl_dest_addr_length = dst->len;
			p->dl_dest_addr_offset = sizeof(*p);
			mp->b_wptr += sizeof(*p);
			bcopy(dst->buf, mp->b_wptr, dst->len);
			mp->b_wptr += dst->len;
			mp->b_cont = dp;
			if (msg && msg->b_cont == dp)
				msg->b_cont = NULL;
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_TEST_RES ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_phys_addr_req: - issued DL_PHYS_ADDR_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @type; address type
 */
static fastcall noinline __unlikely int
dl_phys_addr_req(struct dl *dl, queue_t *q, mblk_t *msg, dl_ulong type)
{
	dl_phys_addr_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		DB_TYPE(mp) = M_PCPROTO;
		p = (typeof(p)) mp->b_wptr;
		p->dl_primitive = DL_PHYS_ADDR_REQ;
		p->dl_addr_type = type;
		mp->b_wptr += sizeof(*p);
		freemsg(msg);
		mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_PHYS_ADDR_REQ ->");
		putnext(nl->oq, mp);
		return (0);
	}
	return (-ENOBUFS);
}

/**
 * dl_set_phys_addr_req: - issued DL_SET_PHYS_ADDR_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 * @add: address buffer
 */
static fastcall noinline __unlikely int
dl_set_phys_addr_req(struct dl *dl, queue_t *q, mblk_t *msg, struct strbuf *add)
{
	dl_set_phys_addr_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p) + add - len, BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_SET_PHYS_ADDR_REQ;
			p->dl_addr_length = add->len;
			p->dl_addr_offset = sizeof(*p);
			mp->b_wptr += sizeof(*p);
			bcopy(add->buf, mp->b_wptr, add->len);
			mp->b_wptr += add->len;
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_SET_PHYS_ADDR_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/**
 * dl_get_statistics_req: - issued DL_GET_STATISTICS_REQ primitive downstream
 * @dl: data link private structure
 * @q: activeq queue
 * @msg: message to free upon success (or NULL)
 */
static fastcall noinline __unlikely int
dl_get_statistics_req(struct dl *dl, queue_t *q, mblk_t *msg)
{
	dl_get_statistics_req_t *p;
	mblk_t *mp;

	if (likely(!!(mp = mi_allocb(q, sizeof(*p), BPRI_MED)))) {
		if (likely(canputnext(dl->oq))) {
			DB_TYPE(mp) = M_PROTO;
			p = (typeof(p)) mp->b_wptr;
			p->dl_primitive = DL_GET_STATISTICS_REQ;
			mp->b_wptr += sizeof(*p);
			freemsg(msg);
			mi_strlog(dl->oq, STRLOGTX, SL_TRACE, "DL_GET_STATISTICS_REQ ->");
			putnext(nl->oq, mp);
			return (0);
		}
		freeb(mp);
		return (-EBUSY);
	}
	return (-ENOBUFS);
}

/*
 * --------------------------------------------------------------------------
 *
 * X.25 SENT MESSAGES
 *
 * --------------------------------------------------------------------------
 */

#define REG_NONNEG  0x06	/* 00000110 - Non-negotiable facilities */
#define REG_AVAIL   0x46	/* 01000110 - Availability of facilities */
#define REG_ANYTIME 0x45	/* 01000101 - Negotiated any time */
#define REG_IDLE    0x05	/* 00000101 - Negotiated with no VCs */
#define REG_NDPS    0x42	/* 01000010 - Nonstd Default Packet Sizes */
#define REG_NDWSB   0x43	/* 01000011 - Nonstd Default Window Sizes Basic */
#define REG_NDWSE   0xd5	/* 11010101 - Nonstd Default Window Sizes Extended */
#define REG_DTCAB   0x02	/* 00000010 - Default Tput Class Assign Basic */
#define REG_DTCAE   0x4c	/* 01001100 - Default Tput Class Assign Extended */
#define REG_LCTR    0xd8	/* 11001000 - Logical Channel Type Ranges */
#define REG_MARKER  0x00	/* 00000000 - Marker */

#define REGF_NONNEG	(1<<0)
#define REGF_AVAIL	(1<<1)
#define REGF_ANYTIME	(1<<2)
#define REGF_IDLE	(1<<3)
#define REGF_NDPS	(1<<4)
#define REGF_NDWSB	(1<<5)
#define REGF_NDWSE	(1<<6)
#define REGF_DTCAB	(1<<7)
#define REGF_DTCAE	(1<<8)
#define REGF_LCTR	(1<<9)
#define REGF_MARKER	(1<<10)

/**
 * x25_snd_regreq:- send a registration request
 * @q: the active queue
 * @xp: the X.25 Packet Layer Entity for which to send the request.
 * @facilities: a bit mask of the facilities for which changes are to be
 *	requested.
 */
static int
x25_snd_regreq(queue_t *q, struct x25_ple *xp, uint32_t facilities)
{
	int size = 0;
	mblk_t *mp;

	if (unlikely(!canputnext(xp->dl->oq)))
		return (-EBUSY);
	switch (xp->proto.gfi) {
	default:
	case 1:
	case 2:
		size += 6;
		break;
	case 3:
		size += 7;
		break;
	}
	if (facilities & REGF_NONNEG)
		size += 2;
	if (facilities & REGF_AVAIL)
		size += 3;
	if (facilities & REGF_ANYTIME)
		size += 3;
	if (facilities & REGF_IDLE)
		size += 2;
	if (facilities & REGF_NDPS)
		size += 2;
	if (facilities & REGF_NDWSB)
		size += 2;
	if (facilities & REGF_NDWSE)
		size += 3;
	if (facilities & REGF_DTCAB)
		size += 2;
	if (facilities & REGF_DTCAE)
		size += 3;
	if (facilities & REGF_LCTR)
		size += 13;
	if (facilities & REGF_MARKER)
		size += 2;
	if (unlikely((mp = mi_allocb(q, size, BPRI_MED)) == NULL))
		return (-ENOBUFS);
	switch (xp->proto.gif) {
		uint8_t ic, og;

	default:
	case 1:
	case 2:
		mp->b_wptr++ = (xp->proto.gfi << 4) | 0;
		mp->b_wptr++ = 0x00;
		mp->b_wptr++ = 0xF3;	/* REGISTRATION REQUEST */
		mp->b_wptr++ = 0x00;
		mp->b_wptr++ = size - 6;
		break;
	case 3:
		mp->b_wptr++ = 0x30;
		mp->b_wptr++ = 0x30;
		mp->b_wptr++ = 0x00;
		mp->b_wptr++ = 0xF3;	/* REGISTRATION REQUEST */
		mp->b_wptr++ = 0x00;
		mp->b_wptr++ = size - 7;
		break;
	}
	if (facilities & REGF_NONNEG) {
		mp->b_wptr++ = REG_NONNEG;
		mp->b_wptr++ = xp->proto.fac.nonneg[0];
	}
	if (facilities & REGF_AVAIL) {
		mp->b_wptr++ = REG_AVAIL;
		mp->b_wptr++ = xp->proto.fac.avail[0];
		mp->b_wptr++ = xp->proto.fac.avail[1];
	}
	if (facilities & REGF_ANYTIME) {
		mp->b_wptr++ = REG_ANYTIME;
		mp->b_wptr++ = xp->proto.fac.anytime[0];
		mp->b_wptr++ = xp->proto.fac.anytime[1];
	}
	if (facilities & REGF_IDLE) {
		mp->b_wptr++ = REG_IDLE;
		mp->b_wptr++ = xp->proto.fac.idle[0];
	}
	if (facilities & REGF_NDPS) {
		ic = xp->proto.fac.ndps.ic;
		og = xp->proto.fac.ndps.og;
		mp->b_wptr++ = REG_NDPS;
		mp->b_wptr++ = (ic << 4) | og;
	}
	if (facilities & REGF_NDWSB) {
		ic = xp->proto.fac.ndws.ic;
		og = xp->proto.fac.ndws.og;
		mp->b_wptr++ = REG_NDWSB;
		mp->b_wptr++ = (ic << 4) | og;
	}
	if (facilities & REGF_NDWSE) {
		mp->b_wptr++ = REG_NDSWE;
		mp->b_wptr++ = xp->proto.fac.ndws.ic;
		mp->b_wptr++ = xp->proto.fac.ndws.og;
	}
	if (facilities & REGF_DTCAB) {
		ic = xp->proto.fac.dtca.ic;
		og = xp->proto.fac.dtca.og;
		mp->b_wptr++ = REG_DTCAB;
		mp->b_wptr++ = (ic << 4) | og;
	}
	if (facilities & REGF_DTCAE) {
		mp->b_wptr++ = REG_DTCAE;
		mp->b_wptr++ = xp->proto.fac.dtca.ic;
		mp->b_wptr++ = xp->proto.fac.dtca.og;
	}
	if (facilities & REGF_LCTR) {
		mp->b_wptr++ = REG_LCTR;
		mp->b_wptr++ = (xp->proto.lca.ic.l >> 8) & 0x0F;
		mp->b_wptr++ = (xp->proto.lca.ic.l >> 0) & 0xFF;
		mp->b_wptr++ = (xp->proto.lca.ic.h >> 8) & 0x0F;
		mp->b_wptr++ = (xp->proto.lca.ic.h >> 0) & 0xFF;
		mp->b_wptr++ = (xp->proto.lca.tc.l >> 8) & 0x0F;
		mp->b_wptr++ = (xp->proto.lca.tc.l >> 0) & 0xFF;
		mp->b_wptr++ = (xp->proto.lca.tc.h >> 8) & 0x0F;
		mp->b_wptr++ = (xp->proto.lca.tc.h >> 0) & 0xFF;
		mp->b_wptr++ = (xp->proto.lca.oc.l >> 8) & 0x0F;
		mp->b_wptr++ = (xp->proto.lca.oc.l >> 0) & 0xFF;
		mp->b_wptr++ = (xp->proto.lca.oc.h >> 8) & 0x0F;
		mp->b_wptr++ = (xp->proto.lca.oc.h >> 0) & 0xFF;
	}
	if (facilities & REGF_MARKER) {
		mp->b_wptr++ = REG_MARKER;
		mp->b_wptr++ = 0x00;
	}
	putnext(xp->dl->oq, mp);
	mi_timer(xp->timers.t28, xp->proto.times.t28);
	return (0);
}

/*
 * --------------------------------------------------------------------------
 *
 * X.25 RECEIVED MESSAGES
 *
 * --------------------------------------------------------------------------
 */

static int
x25_rcv_regcon(queue_t *q, struct x25_ple *xp, mblk_t *mp)
{
	uint8_t gfi, cause, diag, dtelen, dxelen, reglen, pi, rid, cls;
	uint16_t lcn;
	unsigned char p = mp->b_rptr;
	int changed = 0;

	if (unlikely(MBLKSIZE(mp) < 1))
		goto discard;
	gfi = (p[0] >> 4);
	if (unlikely(gfi != xp->proto.gfi))
		goto discard;
	switch (gfi) {
	case 1:
	case 2:
		if (unlikely(MBLKSIZE(mp) < 7))
			goto discard;
		lcn = ((p[0] & 0x0f) << 8) | p[1];
		pi = p[2];
		cause = p[3];
		diag = p[4];
		dtelen = (p[5] >> 4) & 0x0f;
		dxelen = (p[5] >> 0) & 0x0f;
		reglen = p[6];
		p += 7;
		break;
	case 3:
		if (unlikely(MBLKSIZE(mp) < 8))
			goto discard;
		if (unlikely((p[0] & 0x0f) != 0))
			goto discard;
		gfi = (p[1] >> 4);
		if (unlikely(gfi != 3))
			goto discard;
		lcn = ((p[1] & 0x0f) << 8) | p[2];
		cause = p[4];
		diag = p[5];
		dtelen = (p[6] >> 4) & 0x0f;
		dxelen = (p[6] >> 0) & 0x0f;
		reglen = p[7];
		p += 8;
		break;
	default:
		goto discard;
	}
	if (unlikely(lcn != 0))
		goto discard;
	if (unlikely(pi != 0xF7))
		goto discard;
	if (unlikely(dtelen != 0 || dxelen != 0))
		goto discard;
	if (unlikely(mp->b_wptr != p + reglen))
		goto discard;
	if (unlikely(reglen > 109))
		goto discard;
	while (p < mp->b_wptr) {
		rid = p[0];
		cls = (rid >> 6) & 0x3;
		if (unlikely(mp->b_wptr < p + 2 + cls))
			goto discard;
		switch (rid) {
			uint8_t ic, og;

		case REG_NONNEG:
			/* Non-negotiable facilities. */
			if (xp->proto.fac.nonneg[0] != p[1]) {
				xp->proto.fac.nonneg[0] = p[1];
				changed = 1;
			}
			p += 2 + cls;
			continue;
		case REG_AVAIL:
			/* Available facilities. */
			if (xp->proto.fac.avail[0] != p[1]) {
				xp->proto.fac.avail[0] = p[1];
				changed = 1;
			}
			if (xp->proto.fac.avail[1] != p[2]) {
				xp->proto.fac.avail[1] = p[2];
				changed = 1;
			}
			p += 2 + cls;
			continue;
		case REG_ANYTIME:
			/* Facilities negotiated anytime. */
			if (xp->proto.fac.anytime[0] != p[1]) {
				xp->proto.fac.anytime[0] = p[1];
				changed = 1;
			}
			if (xp->proto.fac.anytime[1] != p[2]) {
				xp->proto.fac.anytime[1] = p[2];
				changed = 1;
			}
			p += 2 + cls;
			continue;
		case REG_IDLE:
			/* Facilities negotiated when idle. */
			if (xp->proto.fac.idle[0] != p[1]) {
				xp->proto.fac.idle[0] = p[1];
				changed = 1;
			}
			p += 2 + cls;
			continue;
		case REG_NDPS:
			/* Non-standard Default Packet Sizes. */
			ic = (p[1] >> 4) & 0x0f;
			if (xp->proto.fac.ndps.ic != ic) {
				xp->proto.fac.ndps.ic = ic;
				changed = 1;
			}
			og = (p[1] >> 0) & 0x0f;
			if (xp->proto.fac.ndps.og != og) {
				xp->proto.fac.ndps.og = og;
				changed = 1;
			}
			p += 2 + cls;
			continue;
		case REG_NDWSB:
			/* Non-standard Default Window Sizes (Basic). */
			ic = (p[1] >> 4) & 0x0f;
			if (xp->proto.fac.ndws.ic != ic) {
				xp->proto.fac.ndws.ic = ic;
				changed = 1;
			}
			og = (p[1] >> 0) & 0x0f;
			if (xp->proto.fac.ndws.og != og) {
				xp->proto.fac.ndws.og = og;
				changed = 1;
			}
			p += 2 + cls;
			continue;
		case REG_NDWSE:
			/* Non-standard Default Window Sizes (Extended). */
			ic = p[1];
			if (xp->proto.fac.ndws.ic != p[1]) {
				xp->proto.fac.ndws.ic = p[1];
				changed = 1;
			}
			og = p[2];
			if (xp->proto.fac.ndws.og != p[2]) {
				xp->proto.fac.ndws.og = p[2];
				changed = 1;
			}
			p += 2 + cls;
			continue;
		case REG_DTCAB:
			/* Default Throughput Class Assignment (Basic). */
			ic = (p[1] >> 4) & 0x0f;
			if (xp->proto.fac.dtca.ic != ic) {
				xp->proto.fac.dtca.ic = ic;
				changed = 1;
			}
			og = (p[1] >> 0) & 0x0f;
			if (xp->proto.fac.dtca.og != og) {
				xp->proto.fac.dtca.og = og;
				changed = 1;
			}
			p += 2 + cls;
			continue;
		case REG_DTCAE:
			/* Default Throughput Class Assignment (Extended). */
			ic = p[1];
			if (xp->proto.fac.dtca.ic != p[1]) {
				xp->proto.fac.dtca.ic = p[1];
				changed = 1;
			}
			og = p[2];
			if (xp->proto.fac.dtca.og != p[2]) {
				xp->proto.fac.dtca.og = p[2];
				changed = 1;
			}
			p += 2 + cls;
			continue;
		case REG_LCTR:
		{
			uint16_t lic, hic, ltc, htc, loc, hoc;

			/* Logical Channel Type Ranges. */
			if (unlikely(mp->b_wptr < p + 13))
				goto discard;
			lic = ((p[1] << 8) & 0x0f) | p[2];
			if (xp->proto.fac.lca.ic.l != lic) {
				xp->proto.fac.lca.ic.l = lic;
				changed = 1;
			}
			hic = ((p[3] << 8) & 0x0f) | p[4];
			if (xp->proto.fac.lca.ic.h != hic) {
				xp->proto.fac.lca.ic.h = hic;
				changed = 1;
			}
			ltc = ((p[5] << 8) & 0x0f) | p[6];
			if (xp->proto.fac.lca.tc.l != ltc) {
				xp->proto.fac.lca.tc.l = ltc;
				changed = 1;
			}
			htc = ((p[7] << 8) & 0x0f) | p[8];
			if (xp->proto.fac.lca.tc.h != htc) {
				xp->proto.fac.lca.tc.h = htc;
				changed = 1;
			}
			loc = ((p[9] << 8) & 0x0f) | p[10];
			if (xp->proto.fac.lca.oc.l != loc) {
				xp->proto.fac.lca.oc.l = loc;
				changed = 1;
			}
			hoc = ((p[11] << 8) & 0x0f) | p[12];
			if (xp->proto.fac.lca.oc.h != hoc) {
				xp->proto.fac.lca.oc.h = hoc;
				changed = 1;
			}
			p += 13;
			continue;
		}
		case REG_MARKER:
			/* Registration Marker. */
			p += 2;
			break;
		default:
			/* Skip by class. */
			switch (cls) {
			case 0:	/* class A */
			case 1:	/* class B */
			case 2:	/* class C */
				p += 2 + cls;	/* skip */
				continue;
			case 3:	/* class D */
				p += 2 + cls;
				/* cannot continue */
				break;
			}
		}
		break;
	}
	/* need to send notifications to management if something changed. */
      discard:
	freemsg(mp);
	return (0);
}

/*
 * --------------------------------------------------------------------------
 *
 * X.25 PROTOCOL STATE MACHINE
 *
 * --------------------------------------------------------------------------
 */

/*
 * ISO/IEC 8208: 2000
 *
 * 13.1 On-line Facility Registration:
 *
 * On-inline Facility Registration is an optional user facility agreed to for
 * a period of tim eby the DTE and DXE.  This user faciltiy, if subscribed to,
 * permits a DTE at any time to request registration of optional user
 * facilities and/or to obtain the current values of such facilities as
 * understood by the interfacing DXE.
 *
 * In a DTE/DTE environment, separate agreement to use the facility is rquired
 * for each direction of registration-procedure initiation.  For initiate of
 * the registration procedure in a given direction, use of this facility
 * permits the initiating DTE to transmit REGISTRATION REQUEST packets and
 * requires the responding DTE to process received REGISTRATION REQUEST
 * packets as described below.  In a DTE/DCE environment, the DTE is always
 * the initiator of the registration procedure while the DCE is always the
 * responder.
 *
 * NOTE -- The 1996 version of Recommendation X.25 has deleted the
 * registration procedure.
 *
 * 13.1.1 Generat procedures for On-lin Facility Registration
 *
 * This subclause described the general procedures for using the On-line
 * Facility Registration Facility.  The registration procedure itself does not
 * affect the state of any logical channel.  Specific procedures depend on the
 * faciltiy to be negotiated and are discussed in 13.1.2.
 *
 * 13.1.1.1  Requesting faciltiy registration
 *
 * This subclause applies to a DTE only when it acts as an initiator for the
 * registration procedure.
 *
 * A DTE requests registration of optional user facilities and/or obtains the
 * current values of optional user facilities, as applicable, by transmitting
 * across the DTE/DXE interface a REGISTRATION REQUEST packet and by starting
 * the Registration Request Response Timer (T28).
 *
 * A REGISTRATION REQUEST packet may be sent without attempting to register
 * any optional user facilities (i.e. without a Registration Field) to obtain
 * the current values of the applicable optional user facilities or to avoid
 * requesting facilities or values of facilities that are not available.
 *
 * Having sent a REGSITRATION REQUEST packet, the DTE should wait for the
 * REGISTRATION CONFIRMATION packet before expiration of T28 after transmision
 * of a REGISTRATION REQUEST packet is considered an error.  The registration
 * procedure is retried up to a maximum number of times R28.  After this, the
 * Packet Layer notifies the appropriate entity that it has not received a
 * confirmation of the registration procedure.
 *
 * See also:
 *
 * -- REGISTRATION REQUEST packet format (12.9.1 and figure 28);
 * -- Receiving a response to facility registration (13.1.1.3);
 * -- Registration Request Response Timer (T28) (table 26);
 * -- Registration Request Retransmission Count (R28) (table 27).
 *
 * 13.1.1.2  Processing a facility registration request
 *
 * This subclause applies to a DTE only in a DTE/DTE environment when it acts
 * as a responder for the registration profcedure.  It always applies to a DCE
 * when the registration procedure is used.
 *
 * The DCE or DTE receive a REGISTRATION REQUEST packet (even if the packet
 * has no Registration Field) will, as a result, report the availability and
 * the current values of all optional user facilities applicable to the
 * interface by transmitting across the DTE/DXE interface a REGISTRATION
 * COMFIRMATION packet.  Optional user facilities that are not subject to the
 * registration procedure will not be reported in the REGISTRATION
 * CONFIRMATION packet.  The REGISTRATION CONFIUGRATION packet also contains
 * an appropriate cause code.
 *
 * When a REGISTRATION CONFIRMATION packet is returned, the facilities values
 * indicated in the packet are in effect for any subsequent Virtual Calls.
 * The values of certain facilities can be modified only when there are no
 * existing Virtual Calls (i.e., all logical channels used for Virtual Calls
 * are in the READY state -- p1).  When these facilities take effect and when
 * there is one or more Permanent Virtual Circuits at the DTE/DXE interface, a
 * restart procedure is intiiated.  In a DTE/DCE environment, the DCE
 * transmits a RESTART INDICATION packet with a cause indicating
 * "Registration/Cancellation Confirmed" and the diagnostic "No Additional
 * Information."  A RESET INDICATION packet is also transmitted by the DCE
 * across the remote DTE/DCE interface with the cause "Remote DTE Operational"
 * and the diagnostic "No Additional Information".  In a DTE/DTE environment,
 * the DTE transmitting the REGISTRATION CONFIRMATION packet also transmits a
 * RESTART REQUEST packet with a cause indicating "DTE Originated" and the
 * diagnostic "Registration/Cancellation Confirmed".
 *
 * If the DCE or DTE cannot make all of the modifications requested in the
 * REGISTRATION REQEUST packet, then it will not alter the values of some
 * facilities.  Circumstances in which all of the modifications requested
 * cannot be made include:
 *
 * a) conflict in facilities settings (e.g., requesting the Reverse Charging
 *    Acceptance Facility when the Local Charging Prevention Facility is in
 *    effect); and
 *
 * b) when the interface has at least one Virtual Call established wen
 *    attempting to negotiate those facilities that require all Virtual
 *    Call logical channels to be in the READY state (p1); this includes the
 *    collision of an INCOMING CALL packet and a REGISTRATION REQUEST packet.
 *
 * If the requested value of a particular facilitiy is not permitted, then the
 * DCE or DTE will report in the REGISTRATION CONFIRMATION packet:
 *
 * a) if the facility has a boolean value, the value permitted;
 *
 * b) if the facility has a numeric value and the requested value is greater
 *    than the maximum-permitted value of that facility, the maximum-permitted
 *    value; or
 *
 * c) if the facility has a numeric value and the requested value is less than
 *    the minimum-permitted value of that facility, the minimum-permitted
 *    value.
 *
 * NOTE -- The values in the REGISTRATION CONFIRMATION packet represent the
 * current values in effect.
 *
 * If, in a DTE/DTE enviroment, a DTE receives a REGISTRATION REQUEST packet
 * after having transmitted its own REGSITRATION REQUEST packet, then the
 * registration procedure is considered cancelled with no effect and no
 * REGISTRATIOn CONFIRMATION packet is returned.  The DTE may transmit another
 * REGISTRATION REQUEST packet after some randomly-chosen time delay.
 *
 * See also:
 *
 * -- REGISTRATION CONFIRMATION pcaket format (12.9.2 and figure 29);
 * -- Facilities that can be modified only when all Virtual Calls are in the
 *    READY state (13.1.2.5);
 * -- Restart procedures (clause 4).
 */

/*
 * --------------------------------------------------------------------------
 *
 * DLPI PROVIDER TO DLPI USER PRIMITIVES RECEIVED FROM BELOW
 *
 * --------------------------------------------------------------------------
 */

/**
 * dl_info_ack: - process DL_INFO_ACK primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_INFO_ACK primitive
 */
static fastcall noinline __unlikely int
dl_info_ack(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_info_ack_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_bind_ack: - process DL_BIND_ACK primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_BIND_ACK primitive
 */
static fastcall noinline __unlikely int
dl_bind_ack(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_bind_ack_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_ok_ack: - process DL_OK_ACK primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_OK_ACK primitive
 */
static fastcall noinline __unlikely int
dl_ok_ack(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_ok_ack_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_error_ack: - process DL_ERROR_ACK primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_ERROR_ACK primitive
 */
static fastcall noinline __unlikely int
dl_error_ack(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_error_ack_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_subs_bind_ack: - process DL_SUBS_BIND_ACK primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_SUBS_BIND_ACK primitive
 */
static fastcall noinline __unlikely int
dl_subs_bind_ack(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_subs_bind_ack_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_unitdata_ind: - process DL_UNITDATA_IND primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_UNITDATA_IND primitive
 */
static fastcall noinline __unlikely int
dl_unitdata_ind(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_unitdata_ind_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_uderror_ind: - process DL_UDERROR_IND primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_UDERROR_IND primitive
 */
static fastcall noinline __unlikely int
dl_uderror_ind(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_uderror_ind_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_connect_ind: - process DL_CONNECT_IND primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_CONNECT_IND primitive
 */
static fastcall noinline __unlikely int
dl_connect_ind(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_connect_ind_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_connect_con: - process DL_CONNECT_CON primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_CONNECT_CON primitive
 */
static fastcall noinline __unlikely int
dl_connect_con(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_connect_con_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_token_ack: - process DL_TOKEN_ACK primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_TOKEN_ACK primitive
 */
static fastcall noinline __unlikely int
dl_token_ack(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_token_ack_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_disconnect_ind: - process DL_DISCONNECT_IND primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_DISCONNECT_IND primitive
 */
static fastcall noinline __unlikely int
dl_disconnect_ind(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_disconnect_ind_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_reset_ind: - process DL_RESET_IND primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_RESET_IND primitive
 */
static fastcall noinline __unlikely int
dl_reset_ind(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_reset_ind_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_reset_con: - process DL_RESET_CON primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_RESET_CON primitive
 */
static fastcall noinline __unlikely int
dl_reset_con(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_reset_con_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_xid_ind: - process DL_XID_IND primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_XID_IND primitive
 */
static fastcall noinline __unlikely int
dl_xid_ind(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_xid_ind_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_xid_con: - process DL_XID_CON primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_XID_CON primitive
 */
static fastcall noinline __unlikely int
dl_xid_con(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_xid_con_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_test_ind: - process DL_TEST_IND primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_TEST_IND primitive
 */
static fastcall noinline __unlikely int
dl_test_ind(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_test_ind_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_test_con: - process DL_TEST_CON primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_TEST_CON primitive
 */
static fastcall noinline __unlikely int
dl_test_con(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_test_con_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_phys_addr_ack: - process DL_PHYS_ADDR_ACK primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_PHYS_ADDR_ACK primitive
 */
static fastcall noinline __unlikely int
dl_phys_addr_ack(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_phys_addr_ack_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_get_statistics_ack: - process DL_GET_STATISTICS_ACK primitive
 * @dl: data link private structure
 * @q: active queue (lower read queue)
 * @mp: the DL_GET_STATISTICS_ACK primitive
 */
static fastcall noinline __unlikely int
dl_get_statistics_ack(struct dl *dl, queue_t *q, mblk_t *mp)
{
	dl_get_statistics_ack_t *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	goto discard;
      discard:
	freemsg(mp);
	return (0);
}

/*
 * --------------------------------------------------------------------------
 *
 * NLI USER TO NLI PROVIDER PRIMITIVES RECEIVED FROM ABOVE
 *
 * --------------------------------------------------------------------------
 */

/*
 * TRUSTED INTERFACE
 * --------------------------------------------------------------------------
 * This is the trusted interface.  This is for use by intermodule
 * communications.  We assume that the upper module knows what it is doing as
 * well as being able to properly format messages.  These routines can also be
 * called by the untrusted interface once sufficient checking has been
 * performed in advance.
 */

/**
 * nl_conn_req_ok: - process received N_CI request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_CI request
 */
static fastcall noinline __unlikely int
nl_conn_req_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xcallf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_conn_res_ok: - process received N_CC response
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_CC response
 */
static fastcall noinline __unlikely int
nl_conn_res_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xccnff *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_discon_req_ok: - process received N_DI request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_DI request
 */
static fastcall noinline __unlikely int
nl_discon_req_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xdiscf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_data_req_ok: - process received N_Data request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_Data request
 */
static fastcall noinline __unlikely int
nl_data_req_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xdataf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_exdata_req_ok: - process received N_EData request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_EData request
 */
static fastcall noinline __unlikely int
nl_exdata_req_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xedataf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_bind_req_ok: - process received N_Xlisten request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_Xlisten request
 */
static fastcall noinline __unlikely int
nl_bind_req_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xlistenf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_unbind_req_ok: - process received N_Xcanlis request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_Xcanlis request
 */
static fastcall noinline __unlikely int
nl_unbind_req_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xcanlisf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_datack_req_ok: - process received N_DAck request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_DAck request
 */
static fastcall noinline __unlikely int
nl_datack_req_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xdatacf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_edatack_req_ok: - process received N_EAck request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_EAck request
 */
static fastcall noinline __unlikely int
nl_edatack_req_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xedatacf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_reset_req_ok: - process received N_RI request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_RI request
 */
static fastcall noinline __unlikely int
nl_reset_req_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xrstf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_reset_res_ok: - process received N_RC response
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_RC response
 */
static fastcall noinline __unlikely int
nl_reset_res_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xrscf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_attach_req_ok: - process received N_PVC_ATTACH request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_PVC_ATTACH request
 */
static fastcall noinline __unlikely int
nl_attach_req_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct pvcattf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/**
 * nl_detach_req_ok: - process received N_PVC_DETACH request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_PVC_DETACH request
 */
static fastcall noinline __unlikely int
nl_detach_req_ok(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct pvcdelf *p = (typeof(p)) mp->b_rptr;
	int err;

}

/*
 * UNTRUSTED INTERFACE
 * --------------------------------------------------------------------------
 */

/**
 * nl_conn_req: - process received N_CI request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_CI request
 */
static fastcall noinline __unlikely int
nl_conn_req(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xcallf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_conn_req_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	/* huh? */
}

/**
 * nl_conn_res: - process received N_CC response
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_CC response
 */
static fastcall noinline __unlikely int
nl_conn_res(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xccnff *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_conn_res_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	/* huh? */
}

/**
 * nl_discon_req: - process received N_DI request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_DI request
 */
static fastcall noinline __unlikely int
nl_discon_req(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xdiscf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_discon_req_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	/* huh? */
}

/**
 * nl_data_req: - process received N_Data request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_Data request
 */
static fastcall noinline __unlikely int
nl_data_req(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xdataf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_data_req(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	/* huh? */
}

/**
 * nl_exdata_req: - process received N_EData request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_EData request
 */
static fastcall noinline __unlikely int
nl_exdata_req(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xedataf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_exdata_req_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	/* huh? */
}

/**
 * nl_bind_req: - process received N_Xlisten request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_Xlisten request
 */
static fastcall noinline __unlikely int
nl_bind_req(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xlistenf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_bind_req_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	/* huh? */
}

/**
 * nl_unbind_req: - process received N_Xcanlis request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_Xcanlis request
 */
static fastcall noinline __unlikely int
nl_unbind_req(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xcanlisf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_unbind_req_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	/* huh? */
}

/**
 * nl_datack_req: - process received N_DAck request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_DAck request
 */
static fastcall noinline __unlikely int
nl_datack_req(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xdatacf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_datack_req_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	/* huh? */
}

/**
 * nl_edatack_req: - process received N_EAck request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_EAck request
 */
static fastcall noinline __unlikely int
nl_edatack_req(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xedatacf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_edatack_req_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	/* huh? */
}

/**
 * nl_reset_req: - process received N_RI request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_RI request
 */
static fastcall noinline __unlikely int
nl_reset_req(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xrstf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_reset_req_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	/* huh? */
}

/**
 * nl_reset_res: - process received N_RC response
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_RC response
 */
static fastcall noinline __unlikely int
nl_reset_res(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct xrscf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_reset_res_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	/* huh? */
}

/**
 * nl_attach_req: - process received N_PVC_ATTACH request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_PVC_ATTACH request
 */
static fastcall noinline __unlikely int
nl_attach_req(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct pvcattf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_attach_req_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	return nl_attach_ack(nl, q, mp, p->lci, p->sn_id, p->reqackservice,
			     p->reqnsdulimit, p->nsdulmit, err);
}

/**
 * nl_detach_req: - process received N_PVC_DETACH request
 * @nl: network layer private structure
 * @q: active queue (upper write queue)
 * @mp: the received N_PVC_DETACH request
 */
static fastcall noinline __unlikely int
nl_detach_req(struct nl *nl, queue_t *q, mblk_t *mp)
{
	struct pvcdelf *p = (typeof(p)) mp->b_rptr;
	int err;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	return nl_detach_req_ok(nl, q, mp);
      tooshort:
	err = -EFAULT;
	goto error;
      error:
	return nl_detach_ack(nl, q, mp, err);
}

/*
 * --------------------------------------------------------------------------
 *
 * INPUT-OUTPUT CONTROLS
 *
 * --------------------------------------------------------------------------
 */

/**
 * nl_i_plink: - perform I_PLINK operation
 * @q: active queue (upper write queue)
 * @mp: the I_PLINK M_IOCTL
 *
 * Link a DL provider stream beneath the X.25 PLP.   Each stream linked
 * beneath the X.25 PLP provides a data link for use by X.25.  The data link
 * can be a LAPB data link, a LAPD data link, an LLC1 or LLC2 data link, or a
 * XOT or XOS data link.
 */
static fastcall noinline __unlikely int
nl_i_plink(queue_t *q, mblk_t *mp)
{
}

/**
 * nl_i_punlink: - perform I_PUNLINK operation
 * @q: active queue (upper write queue)
 * @mp: the I_PUNLINK M_IOCTL
 */
static fastcall noinline __unlikely int
nl_i_punlink(queue_t *q, mblk_t *mp)
{
}

static fastcall noinline __unlikely int
nl_ioctl(struct nl *nl, queue_t *q, mblk_t *mp)
{
	switch (_IOC_NR(ioc->ioc_cmd)) {
	case _IOC_NR(N_getnliversion):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_nuidel):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_nuiget):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_nuimget):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_nuireset):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_getstats):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_zerostats):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_getoneVCstats):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_getpvcmap):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_getVCstats):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_getVCstatus):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_putpvcmap):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_traceon):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_traceoff):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_X25_ADD_ROUTE):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_X25_FLUSH_ROUTE):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_X25_GET_ROUTE):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_X25_NEXT_ROUTE):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_X25_RM_ROUTE):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_linkconfig):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_linkent):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_linkmode):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	case _IOC_NR(N_linkread):
		mi_copy_done(q, mp, EOPNOTSUPP);
		return (0);
	default:
		mi_copy_done(q, mp, EINVAL);
		return (0);
	}
}

/*
 * --------------------------------------------------------------------------
 *
 * STREAMS MESSAGE HANDLING
 *
 * --------------------------------------------------------------------------
 */

/**
 * nl_m_data: - process received M_DATA message
 * @q: active queue (upper write queue)
 * @mp: the received M_DATA message
 */
static fastcall noinline __unlikely int
nl_m_data(queue_t *q, mblk_t *mp)
{
	struct nl *nl = NL_PRIV(q);

	return (m_error(nl, q, mp, EPROTO));
}

/**
 * nl_m_proto: - process received M_PROTO or M_PCPROTO message
 * @q: active queue (upper write queue)
 * @mp: the received M_PROTO or M_PCPROTO message
 */
static fastcall noinline __unlikely int
nl_m_proto(queue_t *q, mblk_t *mp)
{
	struct xhdrf *p;
	struct nl *nl;
	caddr_t priv;
	int rtn;

	if (!MBLKIN(mp, 0, sizeof(*p)))
		goto tooshort;
	p = (typeof(p)) mp->b_rptr;
	if ((priv = mi_trylock(q)) == NULL)
		goto edeadlk;
	nl = NL_PRIV(q);
	nl_save_state(nl);
	switch (p->xl_type) {
	case XL_DAT:
		switch (p->xl_command) {
		case N_Data:
			rtn = nl_data_req(nl, q, mp);
			break;
		case N_EData:
			rtn = nl_exdata_req(nl, q, mp);
			break;
		case N_DAck:
			rtn = nl_datack_req(nl, q, mp);
			break;
		case N_EAck:
			rtn = nl_edatack_req(nl, q, mp);
			break;
		default:
			rtn = nl_other_req(nl, q, mp);
			break;
		}
		break;
	case XL_CTL:
		switch (p->xl_command) {
		case N_CI:
			rtn = nl_conn_req(nl, q, mp);
			break;
		case N_CC:
			rtn = nl_conn_res(nl, q, mp);
			break;
		case N_RI:
			rtn = nl_reset_req(nl, q, mp);
			break;
		case N_RC:
			rtn = nl_reset_res(nl, q, mp);
			break;
		case N_DI:
			rtn = nl_discon_req(nl, q, mp);
			break;
		case N_Xlisten:
			rtn = nl_bind_req(nl, q, mp);
			break;
		case N_Xcanlis:
			rtn = nl_unbind_req(nl, q, mp);
			break;
		case N_PVC_ATTACH:
			rtn = nl_attach_req(nl, q, mp);
			break;
		case N_PVC_DETACH:
			rtn = nl_detach_req(nl, q, mp);
			break;
		case N_DC:
		case N_Abort:
			goto wrongway;
		default:
			rtn = nl_other_req(nl, q, mp);
			break;
		}
		break;
	default:
		rtn = nl_other_ind(nl, q, mp);
		break;
	}
	if (rtn) {
		nl_restore_state(nl);
	}
	mi_unlock(priv);
	return (rtn);
      edeadlk:
	return (-EDEADLK);
      wrongway:
	mi_unlock(priv);
	freemsg(mp);
	mi_strlog(q, 0, SL_ERROR | SL_TRACE, "%s: discarding message in wrong direction",
		  __FUNCTION__);
	return (0);
      tooshort:
	freemsg(mp);
	mi_strlog(q, 0, SL_ERROR | SL_TRACE, "%s: discarding primitive too short", __FUNCTION__);
	return (0);
}

/**
 * nl_m_ctl: - process received M_CTL or M_PCCTL message
 * @q: active queue (upper write queue)
 * @mp: the received M_CTL or M_PCCTL message
 *
 * This is a higher speed interface for use for intermodule messages.  No
 * checks are performed on the messages as they are trusted as being properly
 * formatted by the upper layer module.
 */
static fastcall noinline __unlikely int
nl_m_ctl(queue_t *q, mblk_t *mp)
{
	struct xhdrf *p;
	struct nl *nl;
	caddr_t priv;
	int rtn;

	p = (typeof(p)) mp->b_rptr;
	if ((priv = mi_trylock(q)) == NULL)
		goto edeadlk;
	nl = NL_PRIV(q);
	nl_save_state(nl);
	switch (p->xl_type) {
	case XL_DAT:
		switch (p->xl_command) {
		case N_Data:
			rtn = nl_data_req_ok(nl, q, mp);
			break;
		case N_EData:
			rtn = nl_exdata_req_ok(nl, q, mp);
			break;
		case N_DAck:
			rtn = nl_datack_req_ok(nl, q, mp);
			break;
		case N_EAck:
			rtn = nl_edatack_req_ok(nl, q, mp);
			break;
		default:
			rtn = nl_other_req_ok(nl, q, mp);
			break;
		}
		break;
	case XL_CTL:
		switch (p->xl_command) {
		case N_CI:
			rtn = nl_conn_req_ok(nl, q, mp);
			break;
		case N_CC:
			rtn = nl_conn_res_ok(nl, q, mp);
			break;
		case N_RI:
			rtn = nl_reset_req_ok(nl, q, mp);
			break;
		case N_RC:
			rtn = nl_reset_res_ok(nl, q, mp);
			break;
		case N_DI:
			rtn = nl_discon_req_ok(nl, q, mp);
			break;
		case N_Xlisten:
			rtn = nl_bind_req_ok(nl, q, mp);
			break;
		case N_Xcanlis:
			rtn = nl_unbind_req_ok(nl, q, mp);
			break;
		case N_PVC_ATTACH:
			rtn = nl_attach_req_ok(nl, q, mp);
			break;
		case N_PVC_DETACH:
			rtn = nl_detach_req_ok(nl, q, mp);
			break;
		case N_DC:
		case N_Abort:
			goto wrongway;
		default:
			rtn = nl_other_req_ok(nl, q, mp);
			break;
		}
		break;
	default:
		rtn = nl_other_ind_ok(nl, q, mp);
		break;
	}
	if (rtn) {
		nl_restore_state(nl);
	}
	mi_unlock(priv);
	return (rtn);
      edeadlk:
	return (-EDEADLK);
      wrongway:
	mi_unlock(priv);
	freemsg(mp);
	mi_strlog(q, 0, SL_ERROR | SL_TRACE, "%s: discarding message in wrong direction",
		  __FUNCTION__);
	return (0);
}

/**
 * nl_m_sig: - process received M_SIG or M_PCSIG message
 * @q: active queue (upper write queue)
 * @mp: the received M_SIG or M_PCSIG message
 */
static fastcall noinline __unlikely int
nl_m_sig(queue_t *q, mblk_t *mp)
{
	struct nl *nl;
	caddr_t priv;
	int rtn;

	if (!MBLKIN(mp, 0, sizeof(int)))
		goto passalong;
	if ((priv = mi_trylock(q)) == NULL)
		goto edeadlk;
	if (!mi_timer_valid(mp))
		goto done;
	nl = NL_PRIV(q);
	nl_save_state(nl);
	switch (*(int *) mp->b_rptr) {
	case 1:
		mi_strlog(q, STRLOGTO, SL_TRACE, "-> T1 TIMEOUT <-");
		rtn = nl_t1_timeout(nl, q, mp);
		break;
	default:
		mi_strlog(q, 0, SL_ERROR, "%s: discarding undefined timeout %d", __FUNCTION__,
			  *(int *) mp->b_rptr);
		freemsg(mp);
		rtn = 0;
		break;
	}
	if (rtn) {
		nl_restore_state(nl);
		rtn = mi_timer_requeue(mp) ? rtn : 0;
	}
	mi_unlock(priv);
	return (rtn);
      edeadlk:
	if (mi_timer_requeue(mp))
		return (-EDEADLK);
      done:
	return (0);
      passalong:
	freemsg(mp);
	return (0);
}

/**
 * nl_m_read: - process received M_READ message
 * @q: active queue (upper write queue)
 * @mp: the received M_READ message
 *
 * If we pass M_SETOPTS for M_READ notifications upstream, we might as well
 * pass these downstream if we can.  It does not suit that much purpose
 * because if we hold data at the data link, the data link does not know for
 * which upper stream to deliver the data.
 */
static fastcall noinline __unlikely int
nl_m_read(queue_t *q, mblk_t *mp)
{
	struct nl *nl = NL_PRIV(q);
	pl_t pl;

	pl = RW_RDLOCK(plp_mux_lock, plstr);
	if (nl->dl) {
		putnext(nl->dl->oq, mp);
		RW_UNLOCK(plp_mux_lock, pl);
		return (0);
	}
	RW_UNLOCK(plp_mux_lock, pl);
	freemsg(mp);
	return (0);
}

/**
 * nl_m_ioctl: - process received M_IOCTL message
 * @q: active queue (upper write queue)
 * @mp: the received M_IOCTL message
 */
static fastcall noinline __unlikely int
nl_m_ioctl(queue_t *q, mblk_t *mp)
{
	struct iocblk *ioc = (typeof(ioc)) mp->b_rptr;
	struct nl *nl;
	caddr_t priv;
	int err;
	pl_t pl;

	if (_IOC_TYPE(ioc->ioc_cmd) == STR) {
		switch (_IOC_NR(ioc->ioc_cmd)) {
		case _IOC_NR(I_LINK):
			mi_copy_done(q, mp, EINVAL);
			return (0);
		case _IOC_NR(I_PLINK):
			return nl_i_plink(q, mp);
		case _IOC_NR(I_UNLINK):
			mi_copy_done(q, mp, EINVAL);
			return (0);
		case _IOC_NR(I_PUNLINK):
			return nl_i_punlink(q, mp);
		default:
			mi_copy_done(q, mp, EINVAL);
			return (0);
		}
	}
	if (_IOC_TYPE(ioc->ioc_cmd) != X25_IOC_MAGIC)
		goto notforus;
	if (!mp->b_cont)
		goto efault;
	if ((priv = mi_trylock(q)) == NULL)
		goto edeadlk;
	nl = NL_PRIV(q);
	err = nl_ioctl(nl, q, mp);
	mi_unlock(priv);
	return (err);
      edeadlk:
	return (-EDEADLK);
      efault:
	mi_copy_done(q, mp, EFAULT);
	return (0);
      notforus:
	/* Yes, it is possible to send this data link input-output controls down to the data link
	   provided that we are associated with a data link.  We mark the ioc_id in the private
	   structure so that the lower multiplex stream can search for the correct upper multiplex
	   stream when passing acknowledgment or copy messages up. */
	pl = RW_RDLOCK(plp_mux_lock, plstr);
	if (nl->dl) {
		nl->ioc_cmd = ioc->ioc_cmd;
		nl->ioc_id = ioc->ioc_id;
		putnext(nl->dl->oq, mp);
		RW_UNLOCK(plp_mux_lock, pl);
		return (0);
	}
	RW_UNLOCK(plp_mux_lock, pl);
	freemsg(mp);
	return (0);
}

/**
 * nl_m_iocdata: - process received M_IOCDATA message
 * @q: active queue (upper write queue)
 * @mp: the received M_IOCDATA message
 */
static fastcall noinline __unlikely int
nl_m_iocdata(queue_t *q, mblk_t *mp)
{
	struct copyresp *cp = (typeof(cp)) mp->b_rptr;
	struct nl *nl;
	caddr_t priv;
	mblk_t *dp;
	int err;

	if (_IOC_TYPE(cp->cp_cmd) != X25_IOC_MAGIC)
		goto notforus;
	if (!mp->b_cont)
		goto efault;
	if ((priv = mi_trylock(q)) == NULL)
		goto edeadlk;
	nl = NL_PRIV(q);
	switch (mi_copy_state(q, mp, &dp)) {
	case MI_COPY_CASE(MI_COPY_IN, 1):
		err = nl_copyin1(nl, q, mp, dp);
		break;
	case MI_COPY_CASE(MI_COPY_IN, 2):
		err = nl_copyin2(nl, q, mp, dp);
		break;
	case MI_COPY_CASE(MI_COPY_OUT, 1):
		err = nl_copyout(nl, q, mp, dp);
		break;
	default:
		mi_copy_done(q, mp, EPROTO);
		err = 0;
		break;
	}
	mi_unlock(priv);
	return (err);
      edeadlk:
	return (-EDEADLK);
}

/**
 * nl_m_flush: - process received M_FLUSH message
 * @q: active queue (upper write queue)
 * @mp: the received M_FLUSH message
 */
static fastcall noinline __unlikely int
nl_m_flush(queue_t *q, mblk_t *mp)
{
	if (mp->b_rptr[0] & FLUSHW) {
		if (mp->b_rptr[0] & FLUSHBAND)
			flushband(q, mp->b_rptr[1], FLUSHDATA);
		else
			flushq(q, FLUSHDATA);
		mp->b_rptr[0] &= ~FLUSHW;
	}
	if (mp->b_rptr[0] & FLUSHR) {
		if (mp->b_rptr[0] & FLUSHBAND)
			flushband(RD(q), mp->b_rptr[1], FLUSHDATA);
		else
			flushq(RD(q), FLUSHDATA);
		qreply(q, mp);
		return (0);
	}
	freemsg(mp);
	return (0);
}

/**
 * nl_m_unrec: - process received unrecognized message
 * @q: active queue (upper write queue)
 * @mp: the received unrecognized message
 */
static fastcall noinline __unlikely int
nl_m_unrec(queue_t *q, mblk_t *mp)
{
	struct nl *nl = NL_PRIV(q);

	return (m_error(nl, q, mp, EPROTO));
}

/**
 * nl_msg: - process STREAMS message
 * @q: active queue (upper write queue)
 * @mp: the STREAMS message
 */
static fastcall inline int
nl_msg(queue_t *q, mblk_t *mp)
{
	switch (DB_TYPE(mp)) {
	case M_DATA:
		return nl_m_data(q, mp);
	case M_PROTO:
	case M_PCPROTO:
		return nl_m_proto(q, mp);
	case M_CTL:
	case M_PCCTL:
		return nl_m_proto(q, mp);
	case M_SIG:
	case M_PCSIG:
		return nl_m_sig(q, mp);
	case M_READ:
		return nl_m_read(q, mp);
	case M_IOCTL:
		return nl_m_ioctl(q, mp);
	case M_IOCDATA:
		return nl_m_iocdata(q, mp);
	case M_FLUSH:
		return nl_m_flush(q, mp);
	default:
		return nl_m_unrec(q, mp);
	}
}

/**
 * dl_m_data: = process M_DATA message
 * @q: active queue (lower read queue)
 * @mp: the M_DATA message
 */
static fastcall int
dl_m_data(queue_t *q, mblk_t *mp)
{
	struct dl *dl;
	caddr_t priv;
	int rtn;

	if ((priv = mi_trylock(q)) == NULL)
		goto edeadlk;
	dl = DL_PRIV(q);
	rtn = dl_data_ind(dl, q, mp);
	mi_unlock(priv);
	return (rtn);
      edeadlk:
	return (-EDEADLK);
}

/**
 * dl_m_proto: = process M_PROTO or M_PCPROTO message
 * @q: active queue (lower read queue)
 * @mp: the M_PROTO or M_PCPROTO message
 */
static fastcall int
dl_m_proto(queue_t *q, mblk_t *mp)
{
	dl_ulong prim;
	struct dl *dl;
	caddr_t priv;
	int rtn;

	if (!MBLKIN(mp, 0, sizeof(prim)))
		goto tooshort;
	prim = *(dl_ulong *) mp->b_rptr;
	if ((priv = mi_trylock(q)) == NULL)
		goto edeadlk;
	dl = DL_PRIV(q);
	dl_save_state(dl);
	switch (prim) {
	case DL_INFO_ACK:
		rtn = dl_info_ack(dl, q, mp);
		break;
	case DL_BIND_ACK:
		rtn = dl_bind_ack(dl, q, mp);
		break;
	case DL_OK_ACK:
		rtn = dl_ok_ack(dl, q, mp);
		break;
	case DL_ERROR_ACK:
		rtn = dl_error_ack(dl, q, mp);
		break;
	case DL_SUBS_BIND_ACK:
		rtn = dl_subs_bind_ack(dl, q, mp);
		break;
	case DL_UNITDATA_IND:
		rtn = dl_unitdata_ind(dl, q, mp);
		break;
	case DL_UDERROR_IND:
		rtn = dl_uderror_ind(dl, q, mp);
		break;
	case DL_CONNECT_IND:
		rtn = dl_connect_ind(dl, q, mp);
		break;
	case DL_CONNECT_CON:
		rtn = dl_connect_con(dl, q, mp);
		break;
	case DL_TOKEN_ACK:
		rtn = dl_token_ack(dl, q, mp);
		break;
	case DL_DISCONNECT_IND:
		rtn = dl_disconnect_ind(dl, q, mp);
		break;
	case DL_RESET_IND:
		rtn = dl_reset_ind(dl, q, mp);
		break;
	case DL_RESET_CON:
		rtn = dl_reset_con(dl, q, mp);
		break;
	case DL_XID_IND:
		rtn = dl_xid_ind(dl, q, mp);
		break;
	case DL_XID_CON:
		rtn = dl_xid_con(dl, q, mp);
		break;
	case DL_TEST_IND:
		rtn = dl_test_ind(dl, q, mp);
		break;
	case DL_TEST_CON:
		rtn = dl_test_con(dl, q, mp);
		break;
	case DL_PHYS_ADDR_ACK:
		rtn = dl_phys_addr_ack(dl, q, mp);
		break;
	case DL_GET_STATISTICS_ACK:
		rtn = dl_get_statistics_ack(dl, q, mp);
		break;
	default:
		rtn = dl_other_req(dl, q, mp);
		break;
	}
	if (rtn) {
		dl_restore_state(dl);
	}
	mi_unlock(priv);
	return (rtn);
      edeadlk:
	return (-EDEADLK);
      wrongway:
	mi_unlock(priv);
	freemsg(mp);
	mi_strlog(q, 0, SL_ERROR | SL_TRACE, "%s: discarding message in wrong direction",
		  __FUNCTION__);
	return (0);
      tooshort:
	freemsg(mp);
	mi_strlog(q, 0, SL_ERROR | SL_TRACE, "%s: discarding primitive too short", __FUNCTION__);
	return (0);
}

/**
 * dl_m_ctl: = process M_CTL or M_PCCTL message
 * @q: active queue (lower read queue)
 * @mp: the M_CTL or M_PCCTL message
 *
 * This is a trusted intermodule interface, but we always trust the lower
 * module to some degree as it is unrelated to a user process, so just process
 * as thought M_CTL was M_PROTO and M_PCCTL was M_PCPROTO.
 */
static fastcall int
dl_m_ctl(queue_t *q, mblk_t *mp)
{
	return dl_m_proto(q, mp);
}

/**
 * dl_m_sig: = process M_SIG or M_PCSIG message
 * @q: active queue (lower read queue)
 * @mp: the M_SIG or M_PCSIG message
 */
static fastcall int
dl_m_sig(queue_t *q, mblk_t *mp)
{
	struct dl *dl;
	caddr_t priv;
	int rtn;

	if (!MBLKIN(mp, 0, sizeof(int)))
		goto passalong;
	if ((priv = mi_trylock(q)) == NULL)
		goto edeadlk;
	if (!mi_timer_valid(mp))
		goto done;
	dl = DL_PRIV(q);
	dl_save_state(dl);
	switch (*(int *) mp->b_rptr) {
	case 1:
		mi_strlog(q, STRLOGTO, SL_TRACE, "-> T1 TIMEOUT <-");
		rtn = dl_t1_timeout(dl, q, mp);
		break;
	default:
		mi_strlog(q, 0, SL_ERROR, "%s: discarding undefined timeout %d", __FUNCTION__,
			  *(int *) mp->b_rptr);
		freemsg(mp);
		rtn = 0;
		break;
	}
	if (rtn) {
		dl_restore_state(dl);
		rtn = mi_timer_requeue(mp) ? rtn : 0;
	}
	mi_unlock(priv);
	return (rtn);
      edeadlk:
	if (mi_timer_requeue(mp))
		return (-EDEADLK);
      done:
	return (0);
      passalong:
	freemsg(mp);
	return (0);
}

/**
 * dl_m_copy: = process M_COPYIN or M_COPYOUT message
 * @q: active queue (lower read queue)
 * @mp: the M_COPYIN or M_COPYOUT message
 */
static fastcall int
dl_m_copy(queue_t *q, mblk_t *mp)
{
	/* FIXME: find the upper stream that passed the ioctl and pass it there. */
	freemsg(mp);
	return (0);
}

/**
 * dl_m_iocack: = process M_IOCACK or M_IOCNAK message
 * @q: active queue (lower read queue)
 * @mp: the M_IOCACK or M_IOCNAK message
 */
static fastcall int
dl_m_iocack(queue_t *q, mblk_t *mp)
{
	/* FIXME: find the upper stream that passed the ioctl and pass it there. */
	freemsg(mp);
	return (0);
}

/**
 * dl_m_setopts: = process M_SETOPTS or M_PCSETOPTS message
 * @q: active queue (lower read queue)
 * @mp: the M_SETOPTS or M_PCSETOPTS message
 */
static fastcall int
dl_m_setopts(queue_t *q, mblk_t *mp)
{
	struct stroptions *so = (typeof(so)) mp->b_rptr;

	if (!MBLKIN(mp, 0, sizeof(*so)))
		goto discard;
	if (so->so_flags & SO_WROFF) {
	}
	if (so->so_flags & SO_WRPAD) {
	}
	if (so->so_flags & SO_SKBUFF) {
	}
	if (so->so_flags & SO_NOSKBUFF) {
	}
	if (so->so_flags & SO_DELIM) {
	}
	if (so->so_flags & SO_NODELIM) {
	}
	if (so->so_flags & SO_MREADON) {
	}
	if (so->so_flags & SO_MREADOFF) {
	}
	if (so->so_flags & SO_MINPSZ) {
	}
	if (so->so_flags & SO_MAXPSZ) {
	}
	if (so->so_flags & SO_HIWAT) {
	}
	if (so->so_flags & SO_LOWAT) {
	}
      discard:
	freemsg(mp);
	return (0);
}

/**
 * dl_m_flush: = process M_FLUSH message
 * @q: active queue (lower read queue)
 * @mp: the M_FLUSH message
 */
static fastcall int
dl_m_flush(queue_t *q, mblk_t *mp)
{
}

/**
 * dl_m_error: = process M_ERROR message
 * @q: active queue (lower read queue)
 * @mp: the M_ERROR message
 */
static fastcall int
dl_m_error(queue_t *q, mblk_t *mp)
{
}

/**
 * dl_m_hangpu: = process M_HANGUP message
 * @q: active queue (lower read queue)
 * @mp: the M_HANGUP message
 */
static fastcall int
dl_m_hangup(queue_t *q, mblk_t *mp)
{
}

/**
 * dl_m_unrec: = process unrecognized message
 * @q: active queue (lower read queue)
 * @mp: the unrecognized message
 */
static fastcall int
dl_m_unrec(queue_t *q, mblk_t *mp)
{
}

/**
 * dl_msg: - process STREAMS message
 * @q: active queue (lower read queue)
 * @mp: the STREAMS message
 */
static fastcall inline int
dl_msg(queue_t *q, mblk_t *mp)
{
	switch (DB_TYPE(mp)) {
	case M_DATA:
		return dl_m_data(q, mp);
	case M_PROTO:
	case M_PCPROTO:
		return dl_m_proto(q, mp);
	case M_CTL:
	case M_PCCTL:
		return dl_m_ctl(q, mp);
	case M_SIG:
	case M_PCSIG:
		return dl_m_sig(q, mp);
	case M_COPYIN:
	case M_COPYOUT:
		return dl_m_copy(q, mp);
	case M_IOCACK:
	case M_IOCNAK:
		return dl_m_iocack(q, mp);
	case M_SETOPTS:
	case M_PCSETOPTS:
		return dl_m_setopts(q, mp);
	case M_FLUSH:
		return dl_m_flush(q, mp);
	case M_ERROR:
		return dl_m_error(q, mp);
	case M_HANGUP:
		return dl_m_hangup(q, mp);
	default:
		return dl_m_unrec(q, mp);
	}
}

/*
 * --------------------------------------------------------------------------
 *
 * QUEUE PUT AND SERVICE PROCEDURES
 *
 * --------------------------------------------------------------------------
 */

static streamscall __hot_write int
nl_put(queue_t *q, mblk_t *mp)
{
	if ((!pcmsg(DB_TYPE(mp)) && (q->q_first || (q->q_flag & QSVCBUSY))) || nl_msg(q, mp))
		putq(q, mp);
	return (0);
}
static streamscall __hot_out int
nl_srv(queue_t *q)
{
	mblk_t *mp;

	while ((mp = getq(q))) {
		if (nl_msg(q, mp)) {
			putbq(q, mp);
			break;
		}
	}
	return (0);
}
static streamscall __hot_read int
dl_srv(queue_t *q)
{
	mblk_t *mp;

	while ((mp = getq(q))) {
		if (dl_msg(q, mp)) {
			putbq(q, mp);
			break;
		}
	}
	return (0);
}
static streamscall __hot_in int
dl_put(queue_t *q, mblk_t *mp)
{
	if ((!pcmsg(DB_TYPE(mp)) && (q->q_first || (q->q_flag & QSVCBUSY))) || dl_msg(q, mp))
		putq(q, mp);
	return (0);
}

/*
 * --------------------------------------------------------------------------
 *
 * QUEUE OPEN AND CLOSE PROCEDURES
 *
 * --------------------------------------------------------------------------
 */

static streamscall int
nl_qopen(queue_t *q, dev_t *devp, int oflags, int sflag, cred_t *crp)
{
	struct nl *nl;
	mblk_t *mp;
	int err;

	if (q->q_ptr)
		return (0);	/* already open */
	if ((err = mi_open_comm(&nl_opens, sizeof(*nl), q, devp, oflags, sflag, crp))) {
		freeb(mp);
		return (err);
	}
	nl = NL_PRIV(q);

	/* intiialize private structure */
	nl->oq = q;
	nl->state = NS_UNBND;
	nl->oldstate = NS_UNBND;

	/* FIXME: more */

	qprocson(q);
	return (0);
}

static streamscall int
nl_qclose(queue_t *q, int oflags, cred_t *crp)
{
	qprocsoff(q);
	/* FIXME free timers and other things */
	mi_close_comm(&nl_opens, q);
	return (0);
}

/*
 * --------------------------------------------------------------------------
 *
 * STREAMS INITIALIZATION
 *
 * --------------------------------------------------------------------------
 */

static struct qinit nl_winit = {
	.qi_putp = nl_put,
	.qi_srvp = nl_srv,
	.qi_minfo = &nl_minfo,
	.qi_mstat = &nl_mstat,
};

static struct qinit nl_rinit = {
	.qi_putp = NULL,
	.qi_qopen = &nl_qopen,
	.qi_qclose = &nl_qclose,
	.qi_minfo = &nl_minfo,
	.qi_mstat = &nl_mstat,
};

static struct qinit dl_winit = {
	.qi_putp = NULL,
	.qi_minfo = &dl_minfo,
	.qi_mstat = &dl_mstat,
};

static struct qinit dl_rinit = {
	.qi_putp = dl_put,
	.qi_srvp = dl_srv,
	.qi_minfo = &dl_minfo,
	.qi_mstat = &dl_mstat,
};

struct streamtab plp_info = {
	.st_rdinit = &nl_rinit,
	.st_wrinit = &nl_winit,
	.st_muxrinit = &dl_rinit,
	.st_muxwinit = &dl_winit,
};
#endif

static modID_t modid = DRV_ID;
static unsigned short major = CMAJOR_0;

/*
 * --------------------------------------------------------------------------
 *
 * LINUX KERNEL MODULE INITIALIZATION
 *
 * --------------------------------------------------------------------------
 */

#ifdef LINUX

#ifndef module_param
MODULE_PARM(modid, "h");
MODULE_PARM(major, "h");
#else				/* module_param */
module_param(modid, ushort, 0444);
module_param(major, ushort, 0444);
#endif				/* module_param */
MODULE_PARM_DESC(modid, "Module ID for X25-PLP. (0 for allocation.)");
MODULE_PARM_DESC(major, "Major device number for X25-PLP. (0 for allocation.)");

#if NEVER
/*
 * --------------------------------------------------------------------------
 *
 * LINUX FAST STREAMS REGISTRATION
 *
 * --------------------------------------------------------------------------
 */
static struct cdevsw plp_cdev = {
	.d_str = &plp_info,
	.d_flag = D_MP | D_CLONE,
	.d_fop = NULL,
	.d_mode = S_IFCHR | S_IRUGO | S_IWUGO,
	.d_kmod = THIS_MODULE,
};

static int
plp_register_strdev(major_t major)
{
	int err;

	if ((err = register_strdev(&plp_cdev, major)) < 0)
		return (err);
	return (0);
}

static int
plp_unregister_strdev(major_t major)
{
	int err;

	if ((err = unregister_strdev(&plp_cdev, major)) < 0)
		return (err);
	return (0);
}
#endif

static int
plp_modinit(void)
{
#if NEVER
	int err;
#endif

	cmn_err(CE_NOTE, DRV_BANNER);
#if NEVER
	if ((err = plp_register_strdev(major)) < 0) {
		cmn_err(CE_WARN, "%s: could not register driver major %d", DRV_NAME, (int) major);
		return (err);
	}
#endif
	return (0);
}

static void
plp_modexit(void)
{
#if NEVER
	int err;

	if ((err = plp_unregister_strdev(major)) < 0) {
		cmn_err(CE_WARN, "%s: could not unregister driver, err = %d", DRV_NAME, err);
		return;
	}
#endif
	return;
}

module_init(plp_modinit);
module_exit(plp_modexit);

#endif				/* LINUX */
