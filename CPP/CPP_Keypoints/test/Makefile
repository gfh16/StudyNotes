#############################################
#   Learn HOw to write my Makefile          #
#                                           #
#############################################


exec:
	    @cd ../../../../Daq/;pwd

clean:
	    rm -f *.o

foo = $(bar)
bar = $(ugh)
ugh = Huh?

all:
	   @echo $(foo)


x := foo
y := $(x) bar
x := later

all1:
	  @echo $(x)
		@echo $(y)

xx = yy
yy = zz
a :=$($(xx))

all2:
		@echo $(a)


all3:
fooo = 111
ifdef fooo
		frobozz = yes
else
		frobozz = no
endif
