PLIC      ?= plic
CC        ?= gcc
AR        ?= ar
PLIFLAGS  ?= -C -dELF -ew -O
CFLAGS    ?= -m32
LDFLAGS   ?= -m32 -no-pie -z muldefs -Wl,--oformat=elf32-i386
LIBS      ?= -lprf
PREFIX    ?= /usr/local
INCDIR    ?= $(PREFIX)/include
LIBDIR    ?= $(PREFIX)/lib
PKGDIR    ?= $(LIBDIR)/pkgconfig

INC        = -i include
OBJS       = net_bridge.o net.o net_server.o
DIST_INC   = dist/net.inc
DIST_PC    = dist/net.pc

.PHONY: all install uninstall clean distclean

all: libnet.a $(DIST_INC) $(DIST_PC)

net_bridge.o: source/net_bridge.c
	$(CC) $(CFLAGS) -c $< -o $@

net.o: source/net.pli include/net_bridge.inc include/net_errors.inc include/type_defs.inc
	$(PLIC) $(PLIFLAGS) $< $(INC) -o $@

net_server.o: source/net_server.pli include/net_bridge.inc include/net_errors.inc include/type_defs.inc
	$(PLIC) $(PLIFLAGS) $< $(INC) -o $@

libnet.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

$(DIST_INC): include/type_defs.inc include/net_bridge.inc include/net_errors.inc include/net_base.inc include/net_server.inc
	mkdir -p dist
	> $@
	for f in $^; do \
	  sed '/^[[:space:]]*%include/d' $$f >> $@; \
	done

$(DIST_PC): Makefile
	mkdir -p dist
	echo 'prefix=$(PREFIX)' > $@
	echo 'exec_prefix=$${prefix}' >> $@
	echo 'libdir=$(LIBDIR)' >> $@
	echo 'includedir=$(INCDIR)' >> $@
	echo '' >> $@
	echo 'Name: net' >> $@
	echo 'Description: PL/I socket library with C bridge' >> $@
	echo 'Version: 1.0.0' >> $@
	echo 'Libs: -L$${libdir} -lnet -lprf' >> $@
	echo 'Cflags: -i$${includedir}' >> $@

install: libnet.a $(DIST_INC) $(DIST_PC)
	install -d $(DESTDIR)$(INCDIR)
	install -d $(DESTDIR)$(LIBDIR)
	install -d $(DESTDIR)$(PKGDIR)
	install -m 644 $(DIST_INC) $(DESTDIR)$(INCDIR)/
	install -m 644 libnet.a $(DESTDIR)$(LIBDIR)/
	install -m 644 $(DIST_PC) $(DESTDIR)$(PKGDIR)/

uninstall:
	rm -f $(DESTDIR)$(INCDIR)/net.inc
	rm -f $(DESTDIR)$(LIBDIR)/libnet.a
	rm -f $(DESTDIR)$(PKGDIR)/net.pc

clean:
	rm -f $(OBJS) libnet.a
	rm -rf dist

distclean: clean uninstall
