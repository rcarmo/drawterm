/*
 * exportfs - Export a plan 9 name space across a network
 */
#include <u.h>
#include <libc.h>
#include <fcall.h>
#include <libsec.h>
#include "drawterm.h"
#define Extern extern
#include "exportfs.h"

int
exportfs(int rfd, int wfd)
{
	DEBUG("exportfs: started\n");

	messagesize = iounit(rfd);
	if(messagesize == 0)
		messagesize = IOUNIT+IOHDRSZ;

	fhash = emallocz(sizeof(Fid*)*FHASHSIZE);

	fmtinstall('F', fcallfmt);

	initroot();

	io(rfd, wfd);

	return 0;
}
