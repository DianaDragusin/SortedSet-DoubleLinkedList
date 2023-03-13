#include "SortedSet.h"
#include "SortedSetIterator.h"
///Best case : θ(n), n= cap
///Worse case : θ(n), n= cap
/// Average case : θ(n), n= cap
// == operator
bool SortedSet:: operator == (const SortedSet & ss)
{
   if( this->head != ss.head)
       return false;
    if( this->tail != ss.tail)
        return false;
    if( this->nrelem != ss.nrelem)
        return false;
    if( this->cap != ss.cap)
        return false;
    if( this->rel != ss.rel)
        return false;
    for (int i =0;i<ss.cap-1;i++)
    {
        if (  this->elements[i].info != ss.elements[i].info)
            return false;
        if (  this->elements[i].next != ss.elements[i].next)
            return false;
        if (  this->elements[i].prev != ss.elements[i].prev)
            return false;

    }
    return true;

}
///Best case : θ(n), n= cap
///Worse case : θ(n), n= cap
/// Average case : θ(n), n= cap
//copy constructor
SortedSet::SortedSet(const SortedSet &original) {
    this->head = original.head;
    this->tail = original.tail;
    this->nrelem =original.nrelem;
    this->cap = original.cap;
    this->firstempty =original.firstempty;
    this->rel = original.rel;
    for (int i =0;i<original.cap-1;i++)
    {
        this->elements[i].info = original.elements[i].info;
        this->elements[i].next = original.elements[i].next;
        this->elements[i].prev = original.elements[i].prev;
    }

}
///Best case : θ(n), n= cap
///Worse case : θ(n), n= cap
/// Average case : θ(n), n= cap
SortedSet::SortedSet(Relation r) {
	this->head =-1;
    this->tail = -1;
    this->nrelem =0;
    this->cap = 10;
    this->firstempty =0;
    this->rel = r;
    this->elements  = new DLLNode [cap];
    for (int i =0;i<cap-1;i++)
    {
        this->elements[i].next = i+1;
    }
    this->elements[cap-1].next = -1;

    for (int i =cap-1;i>0;i--)
    {
        this->elements[i].prev = i-1;
    }
    this->elements[cap-1].next = -1;
    this->elements[0].prev = -1;
}

///Best case : θ(1),
///Worse case : θ(n),
/// Average case : θ(n), n= cap
bool SortedSet::add(TComp elem) {

    if (nrelem== cap || firstempty == -1 )
    {
        //resize
         this->cap = this->cap*2;
         DLLNode * newElems = new DLLNode [cap];

         // bis cap /2 bleibt alles unverandert
         for (int i =0;i< this->cap/2;i++)
         {
             newElems[i].info = this->elements[i].info;
             newElems[i].next = this->elements[i].next;
             newElems[i].prev = this->elements[i].prev;

         }
         // wir machen die verbindungen  von firstempty und danach stellen wir die next und previous
         firstempty = cap/2;
        newElems[cap/2].next = cap/2+1;
        newElems[cap/2].prev = -1 ;

        for (int i = this->cap/2 +1 ;i< this->cap-1;i++)
        {
            newElems[i].next = i+1;
            newElems[i].prev = i-1;

        }
        // am ende sichern wir die letzten verbindungen
        newElems[cap -1].next = -1;
        newElems[cap -1].prev = cap -2;

        //free memory
        delete [] this->elements;
        this->elements = newElems;


    }
        /// wir haben keinen element in sorted set
        if (this->head == -1)
        {
            int newpos = firstempty;
            this->firstempty = this->elements[this->firstempty].next;
            this->head = newpos;
            this->elements[newpos].info = elem;
            this->elements[newpos].next = -1;
            this->elements[newpos].prev = -1;
            this->tail = this->head;
            nrelem ++;
            return true;
        }

        if (!rel (this->elements[head].info, elem))
        {
            if (this->elements[head].info == elem)
                return false;
           // add in front of head
            int newpos = firstempty;
            firstempty = this->elements[firstempty].next;
            this->elements[newpos].info = elem;
            this->elements[newpos].next = head;
            this->elements[newpos].prev = -1;
            this->elements[head].prev = newpos;
            head = newpos;
            nrelem++;
            return true;

        }
        if (rel (this->elements[tail].info, elem) )
        {
            // add after tail
            if (this->elements[tail].info == elem)
                return false;
            int newpos = firstempty;
            firstempty = this->elements[firstempty].next;
            this->elements[newpos].info = elem;
            this->elements[newpos].next = -1;
            this->elements[newpos].prev = tail;
            this->elements[tail].next = newpos;
            tail = newpos;
            nrelem ++;
            return true;


        }
        else
        {
            // wir addieren in dem mitten des sorted sets
            SortedSetIterator iterator = this->iterator() ;
            iterator.first();

            while (this->rel (this->elements[iterator.currentElement].info,elem) and this->elements[iterator.currentElement].info !=elem )
            {
                iterator.next();
            }



            if (this->elements[iterator.currentElement].info != elem  )
            {


                    int newElem = firstempty;
                    firstempty =  this->elements[firstempty].next;
                    this->elements[newElem].info = elem;
                    this->elements[newElem].prev = this->elements[iterator.currentElement].prev;
                    this->elements[newElem].next =this->elements[this->elements[iterator.currentElement].prev].next;
                    this->elements[iterator.currentElement].prev =  newElem;
                    this->elements[this->elements[this->elements[iterator.currentElement].prev].prev].next = newElem;
                    this->nrelem ++;

                    return true;


            }
             return false;
        }



}

///Best case : θ(1),
///Worst case : θ(n)
/// Average case : θ(n), n= cap
bool SortedSet::remove(TComp elem) {

	SortedSetIterator iterator = this->iterator();
    iterator.first();

    ///delete the only element
    if (nrelem == 1 && this->elements[iterator.currentElement].info == elem)
    {
        this->elements[iterator.currentElement].info = NULL_TELEM;
        this->elements[iterator.currentElement].next = firstempty;
        this->elements[firstempty].prev = iterator.currentElement;
        tail = head = -1;
        firstempty = iterator.currentElement;
        nrelem --;
        return true;
    }
    ///delete first element
    if (this->elements[iterator.currentElement].info == elem)
    {

        int node;
        node = head;
        head = this->elements[head].next;
        this->elements[head].prev = -1;
        this->elements[node].info =NULL_TELEM;
        nrelem --;
        this->elements[node].next = firstempty;
        this->elements[firstempty].prev = node;
        this->elements[node].prev = -1;
        firstempty = node;
        return  true;
    }
    // wir loschen den tail
    if (this->elements[tail].info == elem)
    {

        int node;
        node = tail;
        tail = this->elements[tail].prev;
        this->elements[tail].next = -1;
        this->elements[node].info =NULL_TELEM;
        nrelem --;
        this->elements[node].next = firstempty;
        this->elements[firstempty].prev = node;
        this->elements[node].prev = -1;
        firstempty = node;
        return  true;
    }
    else
    {
        //if we want to delete an elem from the middle
        while (iterator.valid() && rel(this->elements[iterator.currentElement].info, elem) && this->elements[iterator.currentElement].info !=  elem)
        {

            iterator.next();
        }

        //case 1 : we find the element we are looking for right after the while
        if (this->elements[iterator.currentElement].info == elem)
        {
            this->elements[this->elements[iterator.currentElement].prev].next = this->elements[iterator.currentElement].next;
            this->elements[this->elements[iterator.currentElement].next].prev = this->elements[iterator.currentElement].prev;
            this->elements[iterator.currentElement].info = 0;
            this->elements[iterator.currentElement].next = firstempty;
            this->elements[iterator.currentElement].prev = -1;
            firstempty = iterator.currentElement;
            nrelem--;
            return true;
        }
        //  case 2 if we did not find it then we are sure that we will no longer find it further
    }
	return false;
}

///Best case : θ(1),
///Worse case : θ(n)
/// Average case : θ(n)
bool SortedSet::search(TComp elem) const {
    SortedSetIterator iterator = this->iterator();
    iterator.first();
    /// cautam atata timp cat relatia  si iteratorul sunt valide

    while (iterator.valid() && rel(this->elements[iterator.currentElement].info, elem) )
    {
        if (this->elements[iterator.currentElement].info ==  elem)
            return true;
        iterator.next();
    }
    if (this->elements[iterator.currentElement].info ==  elem)
        return true;

	return false;
}

///Best case : θ(1),
///Worse case : θ(1),
/// Average case : θ(1),
int SortedSet::size() const {
	return nrelem;
}


///Best case : θ(1),
///Worse case : θ(1),
/// Average case : θ(1),
bool SortedSet::isEmpty() const {
	//TODO - Implementation
    if (this->nrelem == 0)
        return true;
	return false;
}
///Best case : θ(1),
///Worse case : θ(1),
/// Average case : θ(1),
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

///Best case : θ(1),
///Worse case : θ(1),
/// Average case : θ(1),
SortedSet::~SortedSet() {
	delete [] this->elements;
}
//Facem addul intr-un while si de aceea  complexitatile sunt de n la patrat
///Best case : θ(n*n),
///Worse case : θ(n*n),
/// Average case : θ(n*n),
SortedSet SortedSet::difference(const SortedSet & ss, const Relation & rel) {

    SortedSet set(rel);
    int current = head;
    int current_new = ss.head;
    while (current != -1 and  current_new != -1)
    {
          // compare

            if (elements[current].info != ss.elements[current_new].info)
            {
                //add element
                //add
                if (set.nrelem== set.cap || set.firstempty == -1 )
                {
                    //resize
                    set.cap = set.cap*2;
                    DLLNode * newElems = new DLLNode [set.cap];


                    for (int i =0;i< set.cap/2;i++)
                    {
                        newElems[i].info = set.elements[i].info;
                        newElems[i].next = set.elements[i].next;
                        newElems[i].prev = set.elements[i].prev;

                    }

                    set.firstempty = set.cap/2;
                    newElems[set.cap/2].next = set.cap/2+1;
                    newElems[set.cap/2].prev = -1 ;

                    for (int i = set.cap/2 +1 ;i< set.cap-1;i++)
                    {
                        newElems[i].next = i+1;
                        newElems[i].prev = i-1;

                    }

                    newElems[set.cap -1].next = -1;
                    newElems[set.cap -1].prev = set.cap -2;

                    //free memory
                    delete [] set.elements;
                    set.elements = newElems;


                }

                if (set.head == -1)
                {
                    int newpos = set.firstempty;
                    set.firstempty = set.elements[set.firstempty].next;
                    set.head = newpos;
                    set.elements[newpos].info = elements[current].info;
                    set.elements[newpos].next = -1;
                    set.elements[newpos].prev = -1;
                    set.tail =  set.head;
                    set.nrelem ++;

                }

                if (!set.rel ( set.elements[set.head].info,elements[current].info))
                {

                    // add in front of head
                    int newpos = set.firstempty;
                    set.firstempty = set.elements[set.firstempty].next;
                    set.elements[newpos].info = elements[current].info;
                    set.elements[newpos].next = set.head;
                    set.elements[newpos].prev = -1;
                    set.elements[set.head].prev = newpos;
                    set.head = newpos;
                    set.nrelem++;


                }
                if (set.rel (set.elements[set.tail].info,elements[current].info) )
                {
                    // add after tail

                    int newpos = set.firstempty;
                    set. firstempty =set.elements[set.firstempty].next;
                    set.elements[newpos].info = elements[current].info;
                    set.elements[newpos].next = -1;
                    set.elements[newpos].prev = set.tail;
                    set.elements[set.tail].next = newpos;
                    set.tail = newpos;
                    set.nrelem ++;



                }
                else
                {
                    SortedSetIterator iterator = set.iterator() ;
                    iterator.first();

                    while (set.rel (set.elements[iterator.currentElement].info,elements[current].info)  )
                    {
                        iterator.next();
                    }



                        int newElem = set.firstempty;
                         set.firstempty =  set.elements[set.firstempty].next;
                        set.elements[newElem].info = elements[current].info;
                         set.elements[newElem].prev = set.elements[iterator.currentElement].prev;
                        set.elements[newElem].next =set.elements[set.elements[iterator.currentElement].prev].next;
                       set.elements[iterator.currentElement].prev =  newElem;
                       set.elements[set.elements[set.elements[iterator.currentElement].prev].prev].next = newElem;
                       set.nrelem ++;



                }
                if (current_new != -1)
                {
                    current_new = ss.elements[current_new].next;
                }

            }
            else
            {
                if (current != -1)
                {
                    current = elements[current].next;
                }
                if (current_new != -1)
                {
                    current_new = ss.elements[current_new].next;
                }


            }






    }
    if (current != -1)
    {
        while (current != -1)
        {
            // add

            current = elements[current].next;
        }

    }
    return set;
}


