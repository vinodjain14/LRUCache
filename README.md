
This is an implementation for persistent local storage class LRUDataBase which uses SQLite3 DB and supplemented by LRU cache.

LRU Cache - least recently used item

Files used in this application:
    1. LRUCache.cpp - Implementation of LRU cache with Doubly Linked List and Hash map classes.
    2. LRUDatabase.cpp - Class to store the data in persistent sqlite3 database.
    3. LRUTest.cpp - Test cases in main function and explanation.
    4. Makefile - to build code

Design and Implementation:

We need to consider a few things while implementing LRU cache. The data structure/structures that we choose to implement LRU cache should have the following properties:
    1. We should be able to store a list of items in cache.
    2. We should be able to keep track of items in the cache. Items should be stored in cache in the order in which they were accessed or requested.
    3. When an item is accessed from cache (new item or item already in cache) we should be able to efficiently move it to the front of cache.
    4. When an item is requested from cache we should be able to retrieve that item in constant time, O(1).
    5. We should be able to efficiently evict the least recently used item from cache when the cache is full.

Hashmap - constant time access (enables fast access to items in cache) 
Doubly Linked List - can remove the item from front and rear (keeps track of the order in which the items in the cache were accessed)

Classes used
------------

class LRUCache :
    capacity        -> capacity of lru
    lru             -> lru list
    Hashmap         -> hash map
    get(key)        -> get function
    put(key, value) -> put function

class LRUDataBase :
    LRUDataBase()
    createTable()
    insertData()
    updateData()
    getData()
    closeDB()


Compiling and execution of code -
Dependecny: SQLite3 and g++

$make
$./LRUCache (it will create a LRU.db file to store the data on persistent and LRUCahe executable to run the application)

