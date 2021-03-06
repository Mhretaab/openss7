/*****************************************************************************

 @(#) File: src/drivers/spx.c

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

static char const ident[] = "src/drivers/spx.c (" PACKAGE_ENVR ") " PACKAGE_DATE;

#ifdef NEED_LINUX_AUTOCONF_H
#include NEED_LINUX_AUTOCONF_H
#endif
#include <linux/version.h>
#include <linux/module.h>
#include <linux/init.h>

#include <sys/kmem.h>
#include <sys/stream.h>
#include <sys/strconf.h>
#include <sys/strsubr.h>
#include <sys/ddi.h>

#include "sys/config.h"
#include "src/kernel/strreg.h"

#define SPX_DESCRIP	"SVR 4.2 STREAMS Pipe (SPX) Driver"
#define SPX_EXTRA	"Part of UNIX SYSTEM V RELEASE 4.2 FAST STREAMS FOR LINUX"
#define SPX_COPYRIGHT	"Copyright (c) 2008-2019  Monavacon Limited.  All Rights Reserved."
#define SPX_REVISION	"OpenSS7 src/drivers/spx.c (" PACKAGE_ENVR ") " PACKAGE_DATE
#define SPX_DEVICE	"SVR 4.2 MP STREAMS Pipe Driver"
#define SPX_CONTACT	"Brian Bidulock <bidulock@openss7.org>"
#define SPX_LICENSE	"GPL"
#define SPX_BANNER	SPX_DESCRIP	"\n" \
			SPX_EXTRA	"\n" \
			SPX_COPYRIGHT	"\n" \
			SPX_REVISION	"\n" \
			SPX_DEVICE	"\n" \
			SPX_CONTACT	"\n"
#define SPX_SPLASH	SPX_DEVICE	" - " \
			SPX_REVISION	"\n"

#ifdef CONFIG_STREAMS_SPX_MODULE
MODULE_AUTHOR(SPX_CONTACT);
MODULE_DESCRIPTION(SPX_DESCRIP);
MODULE_SUPPORTED_DEVICE(SPX_DEVICE);
MODULE_LICENSE(SPX_LICENSE);
#ifdef MODULE_VERSION
MODULE_VERSION(PACKAGE_ENVR);
#endif				/* MODULE_VERSION */
#endif				/* CONFIG_STREAMS_SPX_MODULE */

#ifndef CONFIG_STREAMS_SPX_NAME
//#define CONFIG_STREAMS_SPX_NAME "spx"
#error CONFIG_STREAMS_SPX_NAME must be defined.
#endif
#ifndef CONFIG_STREAMS_SPX_MODID
//#define CONFIG_STREAMS_SPX_MODID 9
#error CONFIG_STREAMS_SPX_MODID must be defined.
#endif
#ifndef CONFIG_STREAMS_SPX_MAJOR
//#define CONFIG_STREAMS_SPX_MAJOR 0
#error CONFIG_STREAMS_SPX_MAJOR must be defined.
#endif

#ifdef MODULE
#ifdef MODULE_ALIAS
MODULE_ALIAS("streams-spx");
#endif				/* MODULE_ALIAS */
#endif				/* MODULE */

#ifndef CONFIG_STREAMS_SPX_MODULE
static
#endif
modID_t modid = CONFIG_STREAMS_SPX_MODID;

#ifdef CONFIG_STREAMS_SPX_MODULE
#ifndef module_param
MODULE_PARM(modid, "h");
#else
module_param(modid, ushort, 0444);
#endif
MODULE_PARM_DESC(modid, "Module id number for STREAMS-pipe driver (0 for allocation).");
#endif				/* CONFIG_STREAMS_SPX_MODULE */

#ifdef MODULE
#ifdef MODULE_ALIAS
MODULE_ALIAS("streams-modid-" __stringify(CONFIG_STREAMS_SPX_MODID));
MODULE_ALIAS("streams-driver-spx");
#endif				/* MODULE_ALIAS */
#endif				/* MODULE */

#ifndef CONFIG_STREAMS_SPX_MODULE
static
#endif
major_t major = CONFIG_STREAMS_SPX_MAJOR;

#ifdef CONFIG_STREAMS_SPX_MODULE
#ifndef module_param
MODULE_PARM(major, "h");
#else
module_param(major, uint, 0444);
#endif
MODULE_PARM_DESC(major, "Major device number for STREAMS-pipe driver (0 for allocation).");
#endif				/* CONFIG_STREAMS_SPX_MODULE */

#ifdef MODULE
#ifdef MODULE_ALIAS
MODULE_ALIAS("char-major-" __stringify(CONFIG_STREAMS_CLONE_MAJOR) "-" __stringify(CONFIG_STREAMS_SPX_MAJOR));
MODULE_ALIAS("/dev/spx");
//MODULE_ALIAS("devname:spx");
MODULE_ALIAS("streams-major-" __stringify(CONFIG_STREAMS_SPX_MAJOR));
MODULE_ALIAS("/dev/streams/spx");
MODULE_ALIAS("/dev/streams/spx/*");
MODULE_ALIAS("/dev/streams/clone/spx");
#endif				/* MODULE_ALIAS */
#endif				/* MODULE */

static struct module_info spx_minfo = {
	.mi_idnum = CONFIG_STREAMS_SPX_MODID,
	.mi_idname = CONFIG_STREAMS_SPX_NAME,
	.mi_minpsz = STRMINPSZ,
	.mi_maxpsz = STRMAXPSZ,
	.mi_hiwat = STRHIGH,
	.mi_lowat = STRLOW,
};

static struct module_stat spx_rstat __attribute__ ((__aligned__(SMP_CACHE_BYTES)));
static struct module_stat spx_wstat __attribute__ ((__aligned__(SMP_CACHE_BYTES)));

typedef struct spx {
	struct spx *next;
	struct spx **prev;
	int init;
	queue_t *q;
	dev_t dev;
} spx_t;

#if	defined DEFINE_SPINLOCK
static DEFINE_SPINLOCK(spx_lock);
#elif	defined __SPIN_LOCK_UNLOCKED
static spinlock_t spx_lock = __SPIN_LOCK_UNLOCKED(spx_lock);
#elif	defined SPIN_LOCK_UNLOCKED
static spinlock_t spx_lock = SPIN_LOCK_UNLOCKED;
#else
#error cannot initialize spin locks
#endif
static struct spx *spx_list = NULL;

static streamscall int
spx_rput(queue_t *q, mblk_t *mp)
{
	switch (mp->b_datap->db_type) {
	case M_FLUSH:
		if (mp->b_rptr[0] & FLUSHR) {
			if (mp->b_rptr[0] & FLUSHBAND)
				flushband(q, mp->b_rptr[1], FLUSHDATA);
			else
				flushq(q, FLUSHDATA);
		}
		break;
	}
	putnext(q, mp);
	return (0);
}

static streamscall int
spx_wput(queue_t *q, mblk_t *mp)
{
	struct spx *p = q->q_ptr;

	switch (mp->b_datap->db_type) {
	case M_FLUSH:
		if (mp->b_rptr[0] & FLUSHW) {
			if (mp->b_rptr[0] & FLUSHBAND)
				flushband(q, mp->b_rptr[1], FLUSHDATA);
			else
				flushq(q, FLUSHDATA);
			if (q->q_next) {
				putnext(q, mp);
				break;
			}
			mp->b_rptr[0] &= ~FLUSHW;
		}
		if (mp->b_rptr[0] & FLUSHR) {
			if (q->q_next) {
				putnext(q, mp);
				break;
			}
			if (mp->b_rptr[0] & FLUSHBAND)
				flushband(RD(q), mp->b_rptr[1], FLUSHDATA);
			else
				flushq(RD(q), FLUSHDATA);
			qreply(q, mp);
			break;
		}
		freemsg(mp);
		break;
	case M_PROTO:
		/* We go to some trouble here to make sure that we do not intercept M_PROTO
		   messages that are not for us.  This is because we want the stream to support
		   passing of M_PROTO and M_PCPROTO messages as well, regardless of whether it is
		   just a loop-back device or whether it is an unnamed pipe. */
		if (p->init == 0 && mp->b_wptr >= mp->b_rptr + sizeof(queue_t *)) {
			queue_t *oq = NULL;
			struct spx *x;

			/* not necessarily aligned */
			bcopy(mp->b_rptr, &oq, sizeof(oq));
			/* validate against list */
			spin_lock(&spx_lock);
			for (x = spx_list; x && x->q != oq; x = x->next) ;
			if (x && x->q == oq) {
				weldq(WR(q), oq, WR(oq), q, NULL, NULL, NULL);
				spin_unlock(&spx_lock);
				/* FIXME: welding is probably not enough.  We probably have to link 
				   the two stream heads together, pipe-style as well as setting
				   some stream head characteristics.  People would be better to use 
				   the pipe(4) device anyway. */
				break;
			}
			spin_unlock(&spx_lock);
		}
		/* fall through */
	default:
		if (q->q_next)
			putnext(q, mp);
		else
			qreply(q, mp);
		break;
	}
	if (p->init == 0)
		p->init = 1;
	return (0);
#if 0
      nak:
	{
		union ioctypes *ioc;

		mp->b_datap->db_type = M_IOCNAK;
		ioc = (typeof(ioc)) mp->b_rptr;
		ioc->iocblk.ioc_count = 0;
		ioc->iocblk.ioc_rval = -1;
		ioc->iocblk.ioc_error = -err;
		qreply(q, mp);
		return (0);
	}
#endif
}

/* 
 *  -------------------------------------------------------------------------
 *
 *  OPEN and CLOSE
 *
 *  -------------------------------------------------------------------------
 */
static streamscall int
spx_open(queue_t *q, dev_t *devp, int oflag, int sflag, cred_t *crp)
{
	struct spx *p, **pp = &spx_list;
	major_t cmajor = getmajor(*devp);
	minor_t cminor = getminor(*devp);

	if (q->q_ptr != NULL)
		return (0);	/* already open */
	if (sflag == MODOPEN || WR(q)->q_next)
		return (ENXIO);	/* can't open as module */
	if (!(p = kmem_alloc(sizeof(*p), KM_NOSLEEP)))	/* we could sleep */
		return (ENOMEM);	/* no memory */
	bzero(p, sizeof(*p));
	switch (sflag) {
	case CLONEOPEN:
		if (cminor < 1)
			cminor = 1;
		/* fall through */
	case DRVOPEN:
	{
		major_t dmajor = cmajor;

		if (cminor < 1)
			return (ENXIO);
		spin_lock(&spx_lock);
		for (; *pp && (dmajor = getmajor((*pp)->dev)) < cmajor; pp = &(*pp)->next) ;
		for (; *pp && dmajor == getmajor((*pp)->dev) &&
		     getminor(makedevice(cmajor, cminor)) != 0; pp = &(*pp)->next) {
			minor_t dminor = getminor((*pp)->dev);

			if (cminor < dminor)
				break;
			if (cminor == dminor) {
				if (sflag == CLONEOPEN)
					cminor++;
				else {
					spin_unlock(&spx_lock);
					kmem_free(p, sizeof(*p));
					return (EIO);	/* bad error */
				}
			}
		}
		if (getminor(makedevice(cmajor, cminor)) == 0) {
			spin_unlock(&spx_lock);
			kmem_free(p, sizeof(*p));
			return (EBUSY);	/* no minors left */
		}
		p->dev = *devp = makedevice(cmajor, cminor);
		p->init = 0;
		p->q = q;
		if ((p->next = *pp))
			p->next->prev = &p->next;
		p->prev = pp;
		*pp = p;
		q->q_ptr = OTHERQ(q)->q_ptr = p;
		spin_unlock(&spx_lock);
		qprocson(q);
		return (0);
	}
	}
	return (ENXIO);
}

static streamscall int
spx_close(queue_t *q, int oflag, cred_t *crp)
{
	struct spx *p;

	if ((p = q->q_ptr) == NULL)
		return (0);	/* already closed */
	qprocsoff(q);
	spin_lock(&spx_lock);
	if ((*(p->prev) = p->next))
		p->next->prev = p->prev;
	p->next = NULL;
	p->prev = &p->next;
	p->init = 0;
	p->q = NULL;
	q->q_ptr = OTHERQ(q)->q_ptr = NULL;
	spin_unlock(&spx_lock);
	/* FIXME: we need to do more than this...  If we are welded to another stream head we need
	   to initiate a close on that stream head as well or at least unweld things. */
	return (0);
}

static struct qinit spx_rqinit = {
	.qi_putp = spx_rput,
	.qi_qopen = spx_open,
	.qi_qclose = spx_close,
	.qi_minfo = &spx_minfo,
	.qi_mstat = &spx_rstat,
};

static struct qinit spx_wqinit = {
	.qi_putp = spx_wput,
	.qi_srvp = NULL,
	.qi_minfo = &spx_minfo,
	.qi_mstat = &spx_wstat,
};

#ifdef CONFIG_STREAMS_SPX_MODULE
static
#endif
struct streamtab spxinfo = {
	.st_rdinit = &spx_rqinit,
	.st_wrinit = &spx_wqinit,
};

static struct cdevsw spx_cdev = {
	.d_name = CONFIG_STREAMS_SPX_NAME,
	.d_str = &spxinfo,
	.d_flag = D_CLONE | D_MP,
	.d_fop = NULL,
	.d_mode = S_IFCHR | S_IRUGO | S_IWUGO,
	.d_kmod = THIS_MODULE,
};

#ifdef CONFIG_STREAMS_SPX_MODULE
static int
#else
int __init
#endif
spxinit(void)
{
	int err;

#ifdef CONFIG_STREAMS_SPX_MODULE
	printk(KERN_INFO SPX_BANNER);
#else
	printk(KERN_INFO SPX_SPLASH);
#endif
	spx_minfo.mi_idnum = modid;
	if ((err = register_strdev(&spx_cdev, major)) < 0)
		return (err);
	if (major == 0 && err > 0)
		major = err;
	return (0);
};

#ifdef CONFIG_STREAMS_SPX_MODULE
static void
#else
void __exit
#endif
spxexit(void)
{
	unregister_strdev(&spx_cdev, major);
};

#ifdef CONFIG_STREAMS_SPX_MODULE
module_init(spxinit);
module_exit(spxexit);
#endif
