#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include "ISorted.hpp"
#include "DynamicArray.hpp"

template <class T>
class MergeSort : public ISorted<T> {
private:
    void Merge(Sequence<T>& seq, int left, int mid, int right, int (*cmp)(const T&, const T&, bool), bool ascending) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        DynamicArray<T> L; 
        DynamicArray<T> R; 

        // Заполняем L
        for (int i = 0; i < n1; i++) {
            L.Append(seq.GetElement(left + i)); 
        }
        // Заполняем R
        for (int j = 0; j < n2; j++) {
            R.Append(seq.GetElement(mid + 1 + j)); 
        }

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (cmp(L.GetElement(i), R.GetElement(j), ascending) <= 0) {
                seq.Set(k++, L.GetElement(i++));
            } else {
                seq.Set(k++, R.GetElement(j++));
            }
        }

        while (i < n1) {
            seq.Set(k++, L.GetElement(i++));
        }

        while (j < n2) {
            seq.Set(k++, R.GetElement(j++));
        }
    }

    void MergeSortRecursive(Sequence<T>& seq, int left, int right, int (*cmp)(const T&, const T&, bool), bool ascending) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            MergeSortRecursive(seq, left, mid, cmp, ascending);
            MergeSortRecursive(seq, mid + 1, right, cmp, ascending);
            Merge(seq, left, mid, right, cmp, ascending);
        }
    }

public:
    void Sort(Sequence<T>& seq, int (*cmp)(const T&, const T&, bool), bool ascending) override {
        MergeSortRecursive(seq, 0, seq.GetLength() - 1, cmp, ascending);
    }
};

#endif 