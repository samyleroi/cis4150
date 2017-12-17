#
# Makefile to build the library only
#

CC			= gcc
INCLUDES	= -I./include
CFLAGS		= -g -Wall $(INCLUDES)

OBJS	= \
			src/gpacalc.o \
			src/gpaconv.o

TARGET	= lib/libgpacalc.a


$(TARGET) : $(OBJS)
	ar rv $(TARGET) $(OBJS)
	ranlib $(TARGET)

clean :
	- rm -f $(OBJS)
	- rm -f $(TARGET)

test :
	(cd test ; make ; make test )
