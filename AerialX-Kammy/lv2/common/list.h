#pragma once

#include "lv2.h"

#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

template<typename T> class List
{
public:
	typedef T* Iterator;
	typedef T& Reference;
protected:
	u64 size;
	u64 allocated;
	T* Internal;
public:
	List() : size(0), allocated(0), Internal(NULL) { }
	List(u64 size) : size(0), allocated(0), Internal(NULL) { Allocate(size); }
	~List() { Clear(); }

	List(const List& list) { Add(list.Begin(), list.End()); }

	List& operator =(const List& list)
	{
		Clear();
		Add(list.Begin(), list.End());
		return *this;
	}
	List& operator =(List list)
	{
		Clear();
		Add(list.Begin(), list.End());
		return *this;
	}

	void Allocate(u64 newsize) {
		if (newsize > allocated) {
			T* newinternal = new T[newsize];
			if (Internal) {
				for (u64 i = 0; i < MIN(size, newsize); i++)
					newinternal[i] = Internal[i];
				delete[] Internal;
			}
			Internal = newinternal;

			allocated = newsize;
		}
	}

	Iterator Begin() { return Internal; }
	Iterator End() { return Internal + size; }
	Iterator Add(const T& item) { Allocate(size + 1); Internal[size] = item; size++; return End() - 1; }
	Iterator Add(Iterator begin, Iterator end) {
		for (; begin != end; begin++)
			Add(*begin);
	}
	void Remove(Iterator, Iterator);
	void Remove(Iterator);
	void Remove(u64 index);

	void Clear() { if (Internal) delete[] Internal; size = 0; allocated = 0; Internal = NULL; }

	u64 Size() { return size; }

	Reference operator [](u64 index) { return Internal[index]; }
};

template<typename K, typename V> class Pair
{
public:
	K Key;
	V Value;

	Pair() { }
	Pair(const K& key, const V& value) : Key(key), Value(value) { }
};

