#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include "Sequence.hpp"

#include <stdexcept>

template <class T>
class DynamicArray : public Sequence<T>
{
private:
    T* data;       // Указатель на массив данных
    int size;      // Текущий размер массива
    int capacity;  // Вместимость массива

    void Resize(int newSize)
    {
        if (newSize > capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[capacity];
            if (!newData) {
                throw std::bad_alloc(); // Обработка ошибки выделения памяти
            }
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i]; 
            }
            delete[] data; 
            data = newData;
        }
        size = newSize; 
    }

public:
    class DynamicArrayIterator : public Sequence<T>::Iterator {
    private:
        T* current;

    public:
        DynamicArrayIterator(T* current) : current(current) { }

        bool operator==(const typename Sequence<T>::Iterator& other) const override
        {
            const DynamicArrayIterator* otherIterator = dynamic_cast<const DynamicArrayIterator*>(&other);
            return otherIterator && current == otherIterator->current;
        }

        bool operator!=(const typename Sequence<T>::Iterator& other) const override
        {
            return !(*this == other);
        }

        T& operator*() override
        {
            return *current;
        }

        typename Sequence<T>::Iterator& operator++() override
        {
            current++;
            return *this;
        }
    };

    typename Sequence<T>::Iterator* ToBegin() override
    {
        return new DynamicArrayIterator(data);
    }

    typename Sequence<T>::Iterator* ToEnd() override
    {
        return new DynamicArrayIterator(data + size);
    }

    DynamicArray() : size(0), capacity(1) {
    data = new T[capacity];
    if (!data) {
        throw std::bad_alloc(); // Обработка ошибки выделения памяти
        }
    }   

    DynamicArray(int initialCapacity) : size(0), capacity(initialCapacity) {
        if (capacity < 0) {
            throw std::invalid_argument("Capacity cannot be negative.");
        }
        data = new T[capacity]; // Выделяем память под массив
    }

    DynamicArray(T* items, int dataSize) : size(dataSize), capacity(dataSize) {
        data = new T[capacity]; // Выделяем память под массив
        for (int i = 0; i < size; ++i) {
            data[i] = items[i]; // Копируем данные
        }
    }

    DynamicArray(const DynamicArray<T>& dynamicArray) : size(dynamicArray.size), capacity(dynamicArray.capacity) {
        data = new T[capacity]; // Выделяем память под новый массив
        for (int i = 0; i < size; ++i) {
            data[i] = dynamicArray.data[i]; // Копируем данные
        }
    }

    ~DynamicArray()
    {
        delete[] data; 
    }

    T& operator[](int index)
    {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds in operator[]");
        }
        return data[index];
    }

    T& GetFirstElement() override
    {
        if (size == 0) {
            throw std::out_of_range("Array is empty in GetFirstElement");
        }
        return data[0];
    }

    T& GetLastElement() override
    {
        if (size == 0) {
            throw std::out_of_range("Array is empty in GetLastElement");
        }
        return data[size - 1];
    }

    T& GetElement(int index) override
    {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds in GetElement");
        }
        return data[index];
    }

    const T& GetElement(int index) const override
    {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds in GetElement const");
        }
        return data[index];
    }

    void Append(T item) override
    {
        Resize(size + 1); // Увеличиваем размер массива
        data[size - 1] = item; // Добавляем новый элемент
        if (size <= 0 || size > capacity) {
        throw std::runtime_error("Invalid size after resizing in Append.");
        }
    }

    void Clear() override
    {
        size = 0; 
    }

    void Swap(T& a, T& b) override
    {
        T temp = a;
        a = b;
        b = temp; 
    }

    void Set(int index, T value) override
    {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds in Set");
        }
        data[index] = value; // Устанавливаем значение по индексу
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) override
    {
        if (startIndex < 0 || endIndex > size || startIndex >= endIndex) {
            throw std::out_of_range("Invalid indices for GetSubsequence");
        }
        DynamicArray<T>* subsequence = new DynamicArray<T>(endIndex - startIndex);
        for (int i = startIndex; i < endIndex; ++i) {
            subsequence->Append(data[i]); // Копируем элементы в новый массив
        }
        return subsequence;
    }

    int GetLength() const override
    {
        return size; // Возвращаем текущий размер массива
    }

    void Append(T* data, int dataSize) override
    {
        for (int i = 0; i < dataSize; ++i) {
            Append(data[i]); // Добавляем каждый элемент
        }
    }

    void Prepend(T item) override
    {
        Resize(size + 1); // Увеличиваем размер массива
        for (int i = size - 1; i > 0; --i) {
            data[i] = data[i - 1]; // Сдвигаем элементы вправо
        }
        data[0] = item; // Добавляем новый элемент в начало
    }

    void InsertAt(T item, int index) override
    {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of bounds in InsertAt");
        }
        Resize(size + 1); // Увеличиваем размер массива
        for (int i = size - 1; i > index; --i) {
            data[i] = data[i - 1]; // Сдвигаем элементы вправо
        }
        data[index] = item; // Вставляем элемент по индексу
    }

    void Union(Sequence<T>* list) override
    {
        for (int i = 0; i < list->GetLength(); ++i) {
            Append(list->GetElement(i)); // Добавляем элементы из другого списка
        }
    }
};

#endif 