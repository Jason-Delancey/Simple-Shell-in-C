#
# Typing 'make' or 'make count' will create the executable file.
# Remember to adjust the tabs when using your text editor like emacs/vim/pico/nano/etc

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = gcc
CFLAGS = -g -Wall

# typing 'make' will invoke the first target entry in the file
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: w4118_sh

# To create the executable file w4118_sh we need the object files
# shell.o:
#
w4118_sh: shell.o
$(CC) $(CFLAGS) -o w4118_sh shell.o

# To create the object files shell.o, we need the source
# files shell.c shell.h:
#
shell.o: shell.c shell.h
$(CC) $(CFLAGS) -c shell.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean:
$(RM) w4118_sh *.o *~
