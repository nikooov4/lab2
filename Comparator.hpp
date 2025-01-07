#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP

template <typename T>
int compareDefault(const T& a, const T& b, bool ascending) {
    if (a < b) return ascending ? -1 : 1;
    if (a > b) return ascending ? 1 : -1;
    return 0;
}

#endif 