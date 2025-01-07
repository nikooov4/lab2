#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "Sequence.hpp"
#include "DynamicArray.hpp"

template <class T>
class LinkedList : public Sequence<T>
{
private:
    struct Node
    {
        T data;
        Node* next;

        Node(T data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head;
    Node* tail;
    int length;

public:
    class LinkedListIterator : public Sequence<T>::Iterator {
    private:
        Node* current;
    public:
        LinkedListIterator(Node* start) : current(start) { }

        bool operator==(const typename Sequence<T>::Iterator& other) const override
        {
            const LinkedListIterator* otherIterator = dynamic_cast<const LinkedListIterator*>(&other);
            return otherIterator && current == otherIterator->current;
        }

        bool operator!=(const typename Sequence<T>::Iterator& other) const override
        {
            return !(*this == other);
        }

        T& operator*() override
        {
            return current->data;
        }

        typename Sequence<T>::Iterator& operator++() override
        {
            if (current)
            {
                current = current->next;
            }

            return *this;
        }
    };

    typename Sequence<T>::Iterator* ToBegin() override
    {
        return new LinkedListIterator(head);
    }

    typename Sequence<T>::Iterator* ToEnd() override
    {
        return new LinkedListIterator(nullptr);
    }

    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    LinkedList(T* items, int count) : head(nullptr), tail(nullptr), length(0)
    {
        for (int i = 0; i < count; ++i)
        {
            Append(items[i]);
        }
    }

    LinkedList(LinkedList<T>& list) : head(nullptr), tail(nullptr), length(0)
    {
        Node* current = list.head;

        while (current != nullptr)
        {
            Append(current->data);
            current = current->next;
        }
    }

    LinkedList(DynamicArray<T>& dynamicArray) : head(nullptr), tail(nullptr), length(0)
    {
        for (int i = 1; i < dynamicArray.GetLength(); i++)
        {
            Append(dynamicArray.GetElement(i));
        }
    }

    ~LinkedList()
    {
        Clear();
    }

    T& GetFirstElement() override
    {
        if (length == 0) throw std::out_of_range("List is empty");
        return head->data;
    }

    T& GetLastElement() override
    {
        if (length == 0) throw std::out_of_range("List is empty");
        return tail->data;
    }

    T& GetElement(int index) override
    {
        return GetNode(index)->data;
    }

    const T& GetElement(int index) const override
    {
        return GetNode(index)->data;
    }

    Node* GetNode(int index)
    {
        Node* current = head;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        return current;
    }

    const Node* GetNode(int index) const
    {
        Node* current = head;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        return current;
    }

    void Swap(T& a, T& b) override
    {
        T temp = a;
        a = b;
        b = temp;
    }

    void Set(int index, T value)
    {
        Node* current = head;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        current->data = value;
    }

    LinkedList<T>* GetSubsequence(int startIndex, int endIndex) override
    {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex)
        {
            throw std::out_of_range("Invalid indices for GetSubsequence");
        }

        LinkedList<T>* sublist = new LinkedList<T>();
        Node* current = head;

        // Перемещаемся к началу подпоследовательности
        for (int i = 0; i < startIndex; i++)
        {
            current = current->next;
        }

        // Добавляем элементы в подпоследовательность
        for (int i = startIndex; i <= endIndex; i++)
        {
            sublist->Append(current->data);
            current = current->next;
        }

        return sublist;
    }

    int GetLength() const override
    {
        return length;
    }

    void Append(T item) override
    {
        Node* newNode = new Node(item);

        if (length == 0)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        length++;
    }

    void Append(T* data, int dataSize) override
    {
        int i = 0;

        while (i < dataSize)
        {
            Append(data[i]);
            i++;
        }
    }

    void Prepend(T item) override
    {
        Node* newNode = new Node(item, head);

        if (length == 0)
        {
            head = tail = newNode;
        }
        else
        {
            head = newNode;
        }

        length++;
    }

    void InsertAt(T item, int index) override
    {
        if (index == 0)
        {
            Prepend(item);
        }
        else if (index == length)
        {
            Append(item);
        }
        else
        {
            Node* current = head;

            for (int i = 0; i < index - 1; ++i)
            {
                current = current->next;
            }

            Node* newNode = new Node(item, current->next);
            current->next = newNode;
            length++;
        }
    }

    void Union(Sequence<T>* list) override
    {
        int length = list->GetLength();

        for (int i = 0; i < length; i++)
        {
            Append(list->GetElement(i));
        }
    }

    void Clear() override
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        length = 0;
    }

};

#endif