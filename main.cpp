#include <iostream>
#include <stdexcept>
#include "multimap.h"

using namespace std;

int main()
{
	Multimap <int, int> map(3);
	Multimap <char, int> map1(2);
	Multimap <char, int> map2(2);
	cout << "1." << map;
	try {
		map.add(_pair<int, int>(2,2));
		map.add(_pair<int, int>(1,4));
		cout << "2." << map;

		map.add(_pair<int, int>(4,2));
		map.add(_pair<int, int>(3,1));
		cout << "3." << map;
		
		map1.add(_pair<char, int> ('c',1));
		map1.add(_pair<char, int> ('b',2));
		map2.add(_pair<char, int> ('b',2));
		map2.add(_pair<char, int> ('a',3));
		
		map1.concat(map2);
		cout << "4." << map1;
		
		map1.erase('b');
		cout << "5." << map1;
	} 
	catch (bad_alloc) {
		cerr << "Allocation error" << endl;
	}
	cout << map[3] << endl;
}
