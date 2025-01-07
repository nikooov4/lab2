#ifndef ISORTED_HPP
#define ISORTED_HPP

#include "Sequence.hpp"

template <typename T>
class ISorted {
public:
    virtual void Sort(Sequence<T>& seq, int (*cmp)(const T&, const T&, bool), bool ascending) = 0; 
};

#endif 

