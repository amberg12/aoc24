all: all2

CFLAGS := -Wall -Wextra
LDFLAGS := -lm

include day-01/Makefile
include day-02/Makefile
include day-03/Makefile
include day-04/Makefile
include day-06/Makefile
include day-07/Makefile
include day-08/Makefile
include day-09/Makefile
include day-10/Makefile
include day-11/Makefile
include day-12/Makefile
include day-13/Makefile
include day-14/Makefile
include day-15/Makefile
include day-16/Makefile

01: all_01
02: all_02
03: all_03
04: all_04
06: all_06
07: all_07
08: all_08
09: all_09
10: all_10
11: all_11
12: all_12
13: all_13
14: all_14
15: all_15
16: all_16

all2: 01 02 03 04 06 07 08 09 10 11 12 13 14 15 16
