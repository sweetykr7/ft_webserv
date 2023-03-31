NAME = test

all:
	cmake -S . -B build
	cmake --build build
	cd build && ctest

log:
	cat $(PWD)/build/Testing/Temporary/LastTest.log	

.PHONY : all 
