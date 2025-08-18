ROOT=..
include ../Make.config
LIB=libexportfs.a

HFILES=exportfs.h

OFILES=\
	exportfs.$O\
	exportsrv.$O\
	io.$O\

default: $(LIB)
$(LIB): $(OFILES)
	$(AR) r $(LIB) $(OFILES)
	$(RANLIB) $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

