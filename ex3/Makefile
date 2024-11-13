GXX ?= g++
GXXFLAGS ?= -g -Wall

ex3: cipher.cpp ex3.cpp
	$(GXX) $(FXXFLAGS) -o ex3 ex3.cpp cipher.cpp

test: cipher.cpp test.cpp
	$(GXX) $(FXXFLAGS) -o test test.cpp cipher.cpp
	./test