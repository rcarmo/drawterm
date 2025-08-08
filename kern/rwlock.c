#include "u.h"
#include "lib.h"
#include "dat.h"
#include "fns.h"
#include "error.h"

void
rlock(RWLock *l)
{
	qlock(&l->x);		/* wait here for writers and exclusion */
	lock(&l->lk);
	l->readers++;
	canqlock(&l->k);	/* block writers if we are the first reader */
	unlock(&l->lk);
	qunlock(&l->x);
}

void
runlock(RWLock *l)
{
	lock(&l->lk);
	if(--l->readers == 0)	/* last reader out allows writers */
		qunlock(&l->k);
	unlock(&l->lk);
}

void
wlock(RWLock *l)
{
	qlock(&l->x);		/* wait here for writers and exclusion */
	qlock(&l->k);		/* wait here for last reader */
}

void
wunlock(RWLock *l)
{
	qunlock(&l->k);
	qunlock(&l->x);
}
