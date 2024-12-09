all: all2

CFLAGS := -Wall -Wextra

include day-01/Makefile
include day-02/Makefile
include day-03/Makefile
include day-04/Makefile
include day-06/Makefile
include day-07/Makefile
include day-08/Makefile
include day-09/Makefile

01: all_01
02: all_02
03: all_03
04: all_04
06: all_06
07: all_07
08: all_08
09: all_09

all2: 01 02 03 04 06 07 08 09
