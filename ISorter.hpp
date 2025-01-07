#ifndef ISORTER_HPP
#define ISORTER_HPP

#include "Sequence.hpp"

template <typename T>
class ISorter {
public:
    virtual void Sort(Sequence<T>& seq, int (*cmp)(const T&, const T&, bool), bool ascending) = 0; 
};

#endif 

