
output: LRUCache.o LRUDataBase.o LRUTest.o
	g++ LRUCache.o LRUDataBase.o LRUTest.o -o LRUCache -l sqlite3

LRUCache.o: LRUCache.cpp
	g++ -c 	LRUCache.cpp

LRUDataBase.o: LRUDataBase.cpp
	g++ -c 	LRUDataBase.cpp

LRUTest.o: LRUTest.cpp
	g++ -c 	LRUTest.cpp

clean: 
	rm -rf *.o LRUCache LRU.db
