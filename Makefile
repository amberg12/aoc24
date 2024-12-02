all: all2

include day-01/Makefile
include day-02/Makefile

01: all_01
02: all_02

all2: 01 02
