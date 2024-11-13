GXX ?= g++
GXXFLAGS ?= -g -Wall
SOURCE ?= p2.cpp recursive.cpp

list: list.cpp $(SOURCE)
	$(GXX) $(GXXFLAGS) list.cpp $(SOURCE) -o list
	./list

tree: tree.cpp $(SOURCE)
	$(GXX) $(GXXFLAGS) tree.cpp $(SOURCE) -o tree
	./tree