CPPSTATIC=$(shell find -name "*.cpp"|sed 's/.cpp/.o/g'|sed 's/^\.\///g')
CSTATIC=$(shell find -name "*.c"|sed 's/.cpp/.o/g'|sed 's/^\.\///g')
HEADERS=$(shell find -name "*.h"|sed 's/^\.\///g')


all:	target
	g++ --std="c++14" $(shell pkg-config --cflags glibmm-2.4 gtkmm-3.0) -Bstatic $(CPPSTATIC) $(CSTATIC) $(shell pkg-config --libs glibmm-2.4 gtkmm-3.0) -o main
target:	$(CSTATIC) $(CPPSTATIC)
.SUFFIXES:	.o .cpp .c .h


.cpp.o:
	g++ -c --std="c++14" $(shell pkg-config --cflags glibmm-2.4 gtkmm-3.0) $< -o $@ $(shell pkg-config --libs glibmm-2.4 gtkmm-3.0)

.c.o:
	gcc -c $< -o $@

clearo:
	rm $(CPPSTATIC)

clear: clearo
	rm main
