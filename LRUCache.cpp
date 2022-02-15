#include <map>
#include <iostream>
#include "LRUDataBase.cpp"
#include <list>

#define key first
#define val second

using namespace std;

class LRUCache {
    int capacity;           //Just for simplicity this LRU is capacity based but 
                            //in real life it varies based on memory usage
    map<int, list<pair<int, string> >::iterator> mp;  //Hashmap to do the constant lookup
    list<pair<int, string> > lru; //List to maintain the order of item in order they got accessed
    LRUDataBase sqldb;      // SQLite3 db instance

public:
    /*
    Method name         : LRUCache constructor
    Description         : Setup of capacity and DB creation
    */
    LRUCache(int capacity) {
        this->capacity = capacity;
        sqldb.createTable();
    }

    /*
    Method name         : get
    Description         : method to get the item from lru
    Input parameters    : key
    Output parameters   : None
    Return value        : string
    */
    string get(int key) {
        if(mp.find(key) != mp.end()) {
            lru.push_front(*mp[key]);
            lru.erase(mp[key]);
            mp[key] = lru.begin();
            return mp[key]->val;
        }
        else
            return "";
    }

    /*
    Method name         : put
    Description         : method to put the item in lru
    Input parameters    : key, value
    Output parameters   : None
    Return value        : None
    */
    void put(int key, string val) {
        if(mp.find(key) != mp.end()) {
            mp[key]->key = key;
            mp[key]->val = val;
        }
        else {
            lru.push_front(pair<int, string>(key, val));
            mp[key] = lru.begin();
            if(lru.size() > capacity) {
                mp.erase(lru.back().key);
                lru.pop_back();
            }
        }
        sqldb.insertData(key, val);
    }

    /*
    Method name         : Destructor
    Description         : To cleanup the app exit
    Input parameters    : None
    Output parameters   : None
    Return value        : None
    */
    ~LRUCache() {
        sqldb.closeDB();
    }
};
