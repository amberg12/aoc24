all: all2

include day-01/Makefile
include day-02/Makefile
include day-03/Makefile
include day-04/Makefile

01: all_01
02: all_02
03: all_03
04: all_04

all2: 01 02 03 04
