ROOT=..
include ../Make.config
LIB=libgui.a

PROTO_DIR=`pkg-config --variable=pkgdatadir wayland-protocols`
XDG_SHELL=$(PROTO_DIR)/stable/xdg-shell/xdg-shell.xml
XDG_DECO=$(PROTO_DIR)/unstable/xdg-decoration/xdg-decoration-unstable-v1.xml
XDG_PRIMSEL=$(PROTO_DIR)/unstable/primary-selection/primary-selection-unstable-v1.xml
WP_POINTER_CONSTRAINTS=$(PROTO_DIR)/unstable/pointer-constraints/pointer-constraints-unstable-v1.xml

HFILES=\
	xdg-shell-protocol.h\
	xdg-decoration-protocol.h\
	xdg-primary-selection-protocol.h\
	wp-pointer-constraints.h\
	wl-inc.h\

OFILES=\
	xdg-shell-protocol.$O\
	xdg-decoration-protocol.$O\
	xdg-primary-selection-protocol.$O\
	wp-pointer-constraints.$O\
	wl-cb.$O\
	wl-screen.$O\
	wl-util.$O\

wp-pointer-constraints.c:
	wayland-scanner private-code < $(WP_POINTER_CONSTRAINTS) > $@ || { rm -f $@; exit 1; }

wp-pointer-constraints.h:
	wayland-scanner client-header < $(WP_POINTER_CONSTRAINTS) > $@ || { rm -f $@; exit 1; }

xdg-shell-protocol.c:
	wayland-scanner private-code < $(XDG_SHELL) > $@ || { rm -f $@; exit 1; }

xdg-shell-protocol.h:
	wayland-scanner client-header < $(XDG_SHELL) > $@ || { rm -f $@; exit 1; }

xdg-decoration-protocol.c:
	wayland-scanner private-code < $(XDG_DECO) > $@ || { rm -f $@; exit 1; }

xdg-decoration-protocol.h:
	wayland-scanner client-header < $(XDG_DECO) > $@ || { rm -f $@; exit 1; }

xdg-primary-selection-protocol.c:
	wayland-scanner private-code < $(XDG_PRIMSEL) > $@ || { rm -f $@; exit 1; }

xdg-primary-selection-protocol.h:
	wayland-scanner client-header < $(XDG_PRIMSEL) > $@ || { rm -f $@; exit 1; }

wl-cb.$O: $(HFILES)

default: $(LIB)
$(LIB): $(HFILES) $(OFILES)
	$(AR) r $(LIB) $(OFILES)
	$(RANLIB) $(LIB)

