#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include "ISorted.hpp"
#include "DynamicArray.hpp"

#include <iostream>

template <class T>
class HeapSort : public ISorted<T> {
private:
    void SiftDown(int n, int i, Sequence<T>* sequence, int (*cmp)(const T&, const T&, bool), bool ascending) {
        int largest = i; // Индекс корня поддерева
        while (true) {
            int left = 2 * i + 1;  // Левый потомок
            int right = 2 * i + 2; // Правый потомок

            // Сравнение левого потомка с текущим "наибольшим" элементом
            if (left < n && cmp(sequence->GetElement(i), sequence->GetElement(left), ascending) < 0) {
                largest = left;
            }

            // Сравнение правого потомка с текущим "наибольшим" элементом
            if (right < n && cmp(sequence->GetElement(largest), sequence->GetElement(right), ascending) < 0) {
                largest = right;
            }

            // Если корень уже "наибольший",то выход из цикла
            if (largest == i) {
                break;
            }

            // Меняем местами текущий корень и "наибольший" элемент
            sequence->Swap(sequence->GetElement(i), sequence->GetElement(largest));

            // Продолжаем с нового "наибольшего" элемента
            i = largest;
        }
    }

public:
    // Метод сортировки
    void Sort(Sequence<T>& seq, int (*cmp)(const T&, const T&, bool), bool ascending) override {
        int n = seq.GetLength();

        // Построение кучи (heap)
        for (int i = n / 2 - 1; i >= 0; i--) {
            SiftDown(n, i, &seq, cmp, ascending);
        }

        // Извлечение элементов из кучи (сортировка)
        for (int i = n - 1; i > 0; i--) {
            // Меняем корень с последним элементом
            seq.Swap(seq.GetElement(0), seq.GetElement(i));

            // Восстанавливаем свойство кучи на оставшемся массиве
            SiftDown(i, 0, &seq, cmp, ascending);
        }
    }
};

#endif 
