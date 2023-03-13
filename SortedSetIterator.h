#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	//TODO - Representation
     int currentElement;
;
public:
	void first();
    void last();
	void next();
    void prev();
	TElem getCurrent();
	bool valid() const;
};

