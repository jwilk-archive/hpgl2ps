# dxy2ps and hpgl2ps (Copyright) D McCormick
# Commercial reproduction prohibited.
#
# Obtained from UUCP Newsgroup comp.sources.unix
# Spring 1988
#
# Modified by Gordon Jacobs, July 1989
#
# Modified by Michael L. Brown, June, 1990
#
# Modified by Jeffrey A. Stern, Nov, 1994. Called v2.1.
#
# Modified by Egil Kvaleberg, Feb, 1997. Called v2.2.
#
# SETUP:
#
# 1) Check that you have the 'ar' and 'install' commands on your
# system, and that CC, INSTALLFLAGS, INSTALLMANFLAGS are set to your
# compiler/preferences.  

PACKAGE=	hpgl2ps
VERSION=	2.2

CC=		gcc
SHELL=		/bin/sh
TAR=		tar

CDEFS=		-DVERSION=\"${VERSION}\"

FILTER1=	dxy2ps.in
FILTER2=	hpgl2ps.in
FILTER1.C=	dxy2ps.c dxycom.c
FILTER2.C=	hpgl2ps.c hpglcom.c hplib.c
INSTALLFLAGS=	-s -o root -g root -m 755
MANFILTER1=	dxy2ps.1
MANFILTER2=	hpgl2ps.1
INSTALLMANFLAGS=-o man -g root -m 444
TESTFILES=	test1h.ps1 test2h.ps1 test3h.ps1 \
		test1h.hpgl test2h.hpgl test3h.hpgl \
		test1d.ps1 test1d.dxy
HFILES= 	defn.h
MISCFILES=	Makefile README

DISTFILES=	${FILTER1.C} ${FILTER2.C} \
		${MANFILTER} ${MANFILTER2} \
		${HFILES} ${TESTFILES} ${MISCFILES}
TESTOUTPUT=	test1h.ps test2h.ps test3h.ps test1d.ps 

# 3) Make sure this is where you want the man pages to go.
# This complies with the Linux FSSTND (File System Standard).

prefix= 	/usr/local
INSDIR= 	${prefix}/bin
INSMANDIR=	${prefix}/man/man1

distdir=	$(PACKAGE)-$(VERSION)

# 4) Find your system below and uncomment the lines.  Default is
# Linux.  So far, Sun, MIPS, Linux supported, but it 'shouldn't"
# be much to adapt these variables to your system.
#
# For the CFLAGS variable below:
#
# Add -DNOTIMP to list the non-implemented HPGL commands out to the stderr.
#
# Add -DDEBUG for listing the HPGL implemented commands and the PostScript
# output that goes with it.
#

# For Sun using GNU, activate the following lines, and deactivate the
# other machines'.

# LOADLIBES=	-lieee -lm 
# CFLAGS=	-O -Wall -DNOTIMP -ansi -pedantic
# FILTER1A=	dxy2ps
# FILTER2A=	hpgl2ps
# ACONVERT1=	cp $(FILTER1) $(FILTER1A); strip $(FILTER1A)
# ACONVERT2=	cp $(FILTER2) $(FILTER2A); strip $(FILTER2A)

# For MIPS or Linux, activate the following lines, and deactivate the
# other machines'.
# I originally needed the -lieee flag for the libraries.  I kept
# getting 'Floating Exception' when I ran hpgl2ps. This was reputedly
# caused by a bug in strtod or floatconv.c (which manifests as _IO_dtoa
# in gdb output).  Apparently strtod will die after too many calls to
# itself, or something like that.  Later, I found that with a lot of
# cleanup using 'gcc -Wall', and no dependence up math.h for rint, and
# a bunch of other stuff to get the programs into strict ANSI
# compliance and compile without error, the -lieee was not needed.  A
# phantom, I guess.  But one heck of an ugly one. :) Anyway, if you get
# the error mentioned above and you're compiling on linux, try adding
# the -lieee back into LOADLIBES.  For reference, I have libc 4.5.26,
# and gcc 2.5.8. -jas. 

LOADLIBES=	-lm 
CFLAGS= 	-g -O -Wall -DNOTIMP
FILTER1A=	dxy2ps
FILTER2A=	hpgl2ps
ACONVERT1=	cp $(FILTER1) $(FILTER1A); strip $(FILTER1A)
ACONVERT2=	cp $(FILTER2) $(FILTER2A); strip $(FILTER2A)

# 5) You're done.  Now just type 'make' and with any luck...

##############################################################################
# YOU SHOULDN'T HAVE TO EDIT BELOW HERE.
##############################################################################

# .c.o: 	$(INCLUDE)
#		$(CC) $(CDEFS) $(CFLAGS) -c $< -o $@

all:		$(FILTER1A) $(FILTER2A) $(TESTPOUTPUT)

$(FILTER1A):	$(FILTER1)
		$(ACONVERT1)

$(FILTER2A):	$(FILTER2)
		$(ACONVERT2)

$(FILTER1):	$(FILTER1.C)
		$(CC) $(CDEFS) $(CFLAGS) $< -o $@ $(LOADLIBES)

$(FILTER2):	$(FILTER2.C)
		$(CC) $(CDEFS) $(CFLAGS) $< -o $@ $(LOADLIBES)


test1d.ps: $(FILTER1A) test1d.dxy
	$(FILTER1A) test1d.dxy > test1d.ps

test1h.ps: $(FILTER2A) test1h.hpgl
	$(FILTER2A) test1h.hpgl > test1h.ps

test2h.ps: $(FILTER2A) test2h.hpgl
	$(FILTER2A) test2h.hpgl > test2h.ps

test3h.ps: $(FILTER2A) test3h.hpgl
	$(FILTER2A) test3h.hpgl > test3h.ps

install:	install1 install2 installman

install1:	$(FILTER1A)
		install $(INSTALLFLAGS) $(FILTER1A) $(INSDIR)

install2:	$(FILTER2A)
		install $(INSTALLFLAGS) $(FILTER2A) $(INSDIR)

installman:	$(MANFILTER1) $(MANFILTER2)
		install $(INSTALLMANFLAGS) $(MANFILTER1) $(INSMANDIR)
		install $(INSTALLMANFLAGS) $(MANFILTER2) $(INSMANDIR)

clean:
	rm -f *~* *.o *.ps a.out core hpgl2ps dxy2ps *.in

uninstall:
		rm -f $(INSDIR)/$(FILTER1A)
		rm -f $(INSDIR)/$(FILTER2A)
		rm -f $(INSMANDIR)/$(MANFILTER1)
		rm -f $(INSMANDIR)/$(MANFILTER2)

dist: distdir
	chmod -R a+r $(distdir)
	$(TAR) chozf $(distdir).tar.gz $(distdir)
	rm -rf $(distdir)
distdir: 
	rm -rf $(distdir)
	mkdir $(distdir)
	chmod 777 $(distdir)
	distdir=`cd $(distdir) && pwd` \
	  && cd $(srcdir)
	@for file in `cd $(srcdir) && echo $(DISTFILES)`; do \
	  test -f $(distdir)/$$file \
	  || ln $$file $(distdir)/$$file 2> /dev/null \
	  || cp -p $$file $(distdir)/$$file; \
	done

arcps.obj:	arcps.c
	$(CC) -c $.

changesizes.obj: changesizes.c
	$(CC) -c $.

circle.obj: circle.c
	$(CC) -c $.

dxycom.obj: dxycom.c
	$(CC) -c $.

end_draw.obj: end_draw.c
	$(CC) -c $.

getval.obj: getval.c
	$(CC) -c $.

hpglcom.obj: hpglcom.c
	$(CC) -c $.

linesize.obj: linesize.c
	$(CC) -c $.

linetype.obj: linetype.c
	$(CC) -c $.

manualfeed.obj: manualfeed.c
	$(CC) -c $.

plotdot.obj: plotdot.c
	$(CC) -c $.

plotinit.obj: plotinit.c
	$(CC) -c $.

plotps.obj: plotps.c
	$(CC) -c $.

userdefchar.obj: userdefchar.c
	$(CC) -c $.

ps_macros.obj: ps_macros.c
	$(CC) -c $.

rectangle.obj: rectangle.c
	$(CC) -c $.

textps.obj: textps.c
	$(CC) -c $.

viewport.obj: viewport.c
	$(CC) -c $.

plotcoords.obj: plotcoords.c
	$(CC) -c $.

tick.obj: tick.c
	$(CC) -c $.
