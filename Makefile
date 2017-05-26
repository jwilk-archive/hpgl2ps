# 1.0 dxy2ps and hpgl2ps (Copyright) D McCormick
# Commercial reproduction prohibited.
#
FILTER1=	dxy2ps
FILTER2=	hpgl2ps
INSDIR=		/usr/local/bin
INCLUDE=	defn.h
LOCALLIB=	libroland.a
AR=		ar
ARFLAGS=	ru
LOADLIBES=	-lm 
CFLAGS= 	-g

OBJ1=	dxy2ps.o

OBJ2=	hpgl2ps.o

OBJC=	changesizes.o circle.o      defcoords.o   dxycom.o\
	end_draw.o    getval.o      hpglcom.o     linesize.o\
	linetype.o    manualfeed.o  plotdot.o     plotinit.o\
	plotps.o      ps_macros.o   rectangle.o   textps.o\
	viewport.o    window.o

all:		$(FILTER1) $(FILTER2)

$(FILTER1):	$(LOCALLIB) $(OBJ1)
		$(CC) $(CFLAGS) -o $@ $(OBJ1) $(LOCALLIB) $(LOADLIBES)

$(FILTER2):	$(LOCALLIB) $(OBJ2)
		$(CC) $(CFLAGS) -o $@ $(OBJ2) $(LOCALLIB) $(LOADLIBES)

$(LOCALLIB):	$(OBJC)
		$(AR) $(ARFLAGS) $@ $(OBJC)
		ranlib $(LOCALLIB)

$(OBJC):	$(INCLUDE)

$(OBJ1):	$(INCLUDE)

$(OBJ2):	$(INCLUDE)

install:	$(FILTER1) $(FILTER2)
		install -s $(FILTER1) $(INSDIR)
		install -s $(FILTER2) $(INSDIR)

clean:
		-rm -f *.o a.out core libroland.a
