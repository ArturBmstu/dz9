#include <iostream>
#include <stdexcept>
#include <stdlib.h>

using namespace std;

template<class Key, class Val>
struct _pair {
	Key key;
	Val value;

	_pair() {};
	_pair(Key _key, Val _val): key(_key), value(_val) {};
};

template <class Key, class Val>
class Multimap
{
	_pair<Key, Val> *KeyVal;
	int k;
	int size;
public:
	Multimap();
	Multimap(int);
	Multimap(const Multimap&);
	Val find(Key);
	void add(_pair<Key, Val>);
	void erase(Key);
	void bubbleSort();
	Multimap<Key, Val>& concat(Multimap&);
	Multimap<Key, Val>& intersection(Multimap&);
	Multimap<Key, Val>& operator=(Multimap&);
	Val operator[](Key);
	~Multimap();
	friend ostream& operator<<(ostream& out, const Multimap& map)
	{
		for (int i=0; i< map.k; i++)
		{
			cout << "\t( ";
			cout << map.KeyVal[i].key;
			cout << ": ";
			cout << map.KeyVal[i].value;
			cout << ")" << endl;
		}
		cout << endl;
	}

};

template <class Key, class Val>
Multimap<Key, Val>::Multimap()
{
	KeyVal = new _pair<Key, Val>[3];
	k = 0;
	size = 3;
}

template <class Key, class Val>
Multimap<Key, Val>::Multimap(int _k)
{
	KeyVal = new _pair<Key, Val>[_k];
	k = 0;
	size = _k;
}

template <class Key, class Val>
Multimap<Key, Val>::Multimap(const Multimap& map)
{
	k = map.k;
	size = k;
	KeyVal = new _pair<Key, Val>[size];
	for (int i=0; i<k; i++)
	{
		KeyVal[i].key = map.KeyVal[i].key;
		KeyVal[i].value = map.KeyVal[i].value;
	}
}

template <class Key, class Val>
Val Multimap<Key, Val>::find(Key _key)
{
	int first = 0;
	int avg = 0;
	int last = k-1;
	
	if (last == -1)
		cout << "\nMap is empty" << endl;
	else
	{
		while (first < last)
		{
			avg = first + (last - first)/2;
			(_key <= KeyVal[avg].key) ? last = avg : first = avg + 1;
		}
		if (KeyVal[last].key == _key)
			return KeyVal[last].value;
	}
}

//...................Bubble Sort for not long arrays.................//
template <class Key, class Val>
void Multimap<Key, Val>::bubbleSort()
{
	_pair<Key, Val> temp;
	bool exit = false;
	
	while (!exit)
	{
		exit = true;
		for (int i=0; i<k-1; i++)
			if (KeyVal[i].key > KeyVal[i+1].key)
			{
				temp.key = KeyVal[i].key;
				temp.value = KeyVal[i].value;

				KeyVal[i].key = KeyVal[i+1].key;
				KeyVal[i].value = KeyVal[i+1].value;

				KeyVal[i+1].key = temp.key;
				KeyVal[i+1].value = temp.value;
				
				exit = false;
			}
	}
}

template <class Key, class Val>
void Multimap<Key, Val>::add(_pair<Key, Val> _keyval)
{
	if (k == size)
	{
		size *= 2;

		_pair<Key, Val>* temp = new _pair<Key, Val>[k];

		for (int i=0; i<k; i++)
		{
			temp[i].key = KeyVal[i].key;
			temp[i].value = KeyVal[i].value;
		}
		delete KeyVal;

		KeyVal = new _pair<Key, Val>[size];		

		for (int i=0; i<k; i++)
		{
			KeyVal[i].key = temp[i].key;
			KeyVal[i].value = temp[i].value;
		}
	}
	KeyVal[k].key = _keyval.key;
	KeyVal[k].value = _keyval.value;
	k++;
	bubbleSort();
}

template <class Key, class Val>
void Multimap<Key, Val>::erase(Key _key)
{
	for (int i=0; i<k; i++)
		if (KeyVal[i].key == _key)
		{
			for (int j=i; j<k-1; j++)
			{
				KeyVal[j].key = KeyVal[j+1].key;
				KeyVal[j].value = KeyVal[j+1].value;
			}
			i--;
			k--;
		}
}

template <class Key, class Val>
Multimap<Key, Val>& Multimap<Key, Val>::concat(Multimap& map)
{
	for (int i=0; i<map.k; i++)
	{
		Key _key = map.KeyVal[i].key;
		Val _val = map.KeyVal[i].value;
		add(_pair<Key, Val> (_key, _val));
	}
	return *this;
}

template <class Key, class Val>
Multimap<Key, Val>& Multimap<Key, Val>::intersection(Multimap& map)
{
	Multimap<Key, Val> multimap;

	for (int i=0; i<k; i++)
	{
		Key _key = KeyVal[i].key;
		Val _val = map.find(_key);
		if (_val == KeyVal[i].value)
		{
			multimap.add(_pair<Key, Val> (_key, _val));
		}
	}
	return (*this = multimap);
}

template <class Key, class Val>
Multimap<Key, Val>& Multimap<Key, Val>::operator=(Multimap& map)
{	
	if (size)
		delete KeyVal;
	k = map.k;
	size = map.size;
	KeyVal = new _pair<Key, Val>[size];
	for (int i=0; i<k; i++)
	{
		KeyVal[i].key = map.KeyVal[i].key;
		KeyVal[i].value = map.KeyVal[i].value;
	}
	return *this;
}

template <class Key, class Val>
Val Multimap<Key, Val>::operator[](Key _key)
{
	return find(_key);
}

template <class Key, class Val>
Multimap<Key, Val>::~Multimap()
{
	delete KeyVal;
}











