#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include "ISorted.hpp"
#include "DynamicArray.hpp"

template <class T>
class QuickSort : public ISorted<T> {
private:
    int Separation(Sequence<T>& sequence, int low, int high, int (*cmp)(const T&, const T&, bool), bool ascending) {
        // Выбор опорного элемента (медиана из трех)
        int mid = low + (high - low) / 2;
        T pivot = sequence.GetElement(mid);
        sequence.Swap(sequence.GetElement(mid), sequence.GetElement(high)); // Перемещаем опорный элемент в конец

        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (cmp(sequence.GetElement(j), pivot, ascending) < 0) {
                i++;
                sequence.Swap(sequence.GetElement(i), sequence.GetElement(j));
            }
        }

        // Перемещаем опорный элемент на его окончательную позицию
        i++;
        sequence.Swap(sequence.GetElement(i), sequence.GetElement(high));
        return i;
    }

    void QuickSortRecursive(Sequence<T>& sequence, int low, int high, int (*cmp)(const T&, const T&, bool), bool ascending) {
        while (low < high) {
            int pivot = Separation(sequence, low, high, cmp, ascending);
            // Рекурсивно сортируем меньшую часть
            if (pivot - low < high - pivot) {
                QuickSortRecursive(sequence, low, pivot - 1, cmp, ascending);
                low = pivot + 1; // Сортируем большую часть
            } else {
                QuickSortRecursive(sequence, pivot + 1, high, cmp, ascending);
                high = pivot - 1; // Сортируем меньшую часть
            }
        }
    }

public:
    void Sort(Sequence<T>& seq, int (*cmp)(const T&, const T&, bool), bool ascending) override {
        if (seq.GetLength() < 2) return; // Если массив пуст или содержит один элемент, ничего не делаем
        QuickSortRecursive(seq, 0, seq.GetLength() - 1, cmp, ascending);
    }
};

#endif 