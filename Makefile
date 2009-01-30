.PHONY: ALL

.cc.o:
	g++ -c $< -o $@

ALL: memset memget

memset: memset.o
	g++ $^ -o $@ -lmemcached
	
memget: memget.o
	g++ $^ -o $@ -lmemcached

memset.o: memset.cc mem.h

memget.o: memset.cc mem.h
