all: all2

include day-01/Makefile
include day-02/Makefile
include day-03/Makefile

01: all_01
02: all_02
03: all_03

all2: 01 02 03
