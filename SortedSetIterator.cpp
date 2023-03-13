#include "SortedSetIterator.h"
#include <exception>

using namespace std;
///Best case : θ(1),
///Worse case : θ(1),
/// Average case : θ(1),
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m){this->currentElement= multime.head;}

///Best case : θ(1),
///Worse case : θ(1),
/// Average case : θ(1),
void SortedSetIterator::first() {
	currentElement = multime.head;
}
///Best case : θ(1),
///Worse case : θ(1),
/// Average case : θ(1),
void SortedSetIterator::last() {
    currentElement = multime.tail;
}

///Best case : θ(1),
///Worse case : θ(1),
/// Average case : θ(1),
void SortedSetIterator::next() {
    if (valid())
    {
        currentElement = multime.elements[currentElement].next;
    }else{
        throw exception();
    }

}
///Best case : θ(1),
///Worse case : θ(1),
/// Average case : θ(1),
void SortedSetIterator::prev() {
    if (valid() )
    {
        currentElement = multime.elements[currentElement].prev;
    }
    else throw exception();
}

///Best case : θ(1),
///Worse case : θ(1),
/// Average case : θ(1),
TElem SortedSetIterator::getCurrent()
{
    if (valid ())
    {
        return multime.elements[currentElement].info;
    }
    else throw exception();
	//return NULL_TELEM;
}
///Best case : θ(1),
///Worse case : θ(1),
/// Average case : θ(1),
bool SortedSetIterator::valid() const {
    if (currentElement<0 || currentElement > multime.cap-1 )
	    return false;
    return true;
}

