# Makefile for CPE-2600 Lab 10 - Signals
# Jim Luzano-Belfield
#
#   make         build all programs
#   make clean   remove executables

CC = gcc
CFLAGS = -Wall -Wextra -g

PROGRAMS = signal_handler signal_alarm signal_segfault signal_sigaction \
           recv_signal send_signal

all: $(PROGRAMS)

# Each program is built from the .c file of the same name
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROGRAMS)

.PHONY: all clean
