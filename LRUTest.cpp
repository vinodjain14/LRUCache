#include <iostream>
#include "LRUCache.cpp"
using namespace std;

int main() {
	LRUCache cache(3);	// cache capacity 3

	cache.put(1,"John"); // John will be added to LRU and DB
	cache.put(2,"David");// David will be added to LRU and DB
	cache.put(3,"Alex"); // Alex will be added to LRU and DB
	cache.put(4,"Ryan"); //Ryan will be added to LRU and DB and John will be evicted here from LRU
	cache.put(5,"Steve"); //Steve will be added to LRU and DB and David will be evicted here from LRU

	//Current LRU contains -> (5, Steve), (4, Ryan), (3, Alex)

    cout << cache.get(2) << endl; // No output because key=2 not in LRU
	cout << cache.get(3) << endl; // Alex
	cout << cache.get(4) << endl; // Ryan
	cout << cache.get(5) << endl; // Steve
	cache.put(1,"Harry"); //Harry will be added to LRU, will be updated to DB and Alex will be evicted here from LRU

	//Current LRU contains -> (1, Harry), (5, Steve), (4, Ryan)
	cout << cache.get(1) << endl; // Harry

    return 0;
}