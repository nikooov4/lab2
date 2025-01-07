#include "dataCreator.hpp" 
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "PersonComparator.hpp"
#include "interface.hpp"
#include "QuickSort.hpp"     
#include "HeapSort.hpp"      
#include "MergeSort.hpp"     

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip> 
#include <cassert>

namespace fs = std::filesystem;

// Функция для генерации массива персон в памяти
void generatePersonsInMemory(int numberOfPersons, DynamicArray<Person>& persons,
                              const DynamicArray<std::string>& maleFirstNames,
                              const DynamicArray<std::string>& femaleFirstNames,
                              const DynamicArray<std::string>& maleLastNames,
                              const DynamicArray<std::string>& femaleLastNames,
                              const DynamicArray<std::string>& malePatronymics,
                              const DynamicArray<std::string>& femalePatronymics) {
    for (int i = 0; i < numberOfPersons; ++i) {
        persons.Append(generateRandomPerson(maleFirstNames, femaleFirstNames,
                                             maleLastNames, femaleLastNames,
                                             malePatronymics, femalePatronymics));
    }
}

// Функциональное тестирование DynamicArray
void functionalTestDynamicArray() {
    std::cout << "\n=== Тестирование DynamicArray ===\n";

    // Создание динамического массива
    DynamicArray<int> array;

    // Тестирование добавления элементов
    for (int i = 0; i < 10; ++i) {
        array.Append(i);
    }

    // Проверка добавленных элементов
    for (int i = 0; i < 10; ++i) {
        assert(array.GetElement(i) == i);
    }

    // Проверка длины массива
    assert(array.GetLength() == 10);

    // Тестирование доступа к первому и последнему элементу
    assert(array.GetFirstElement() == 0);
    assert(array.GetLastElement() == 9);

    // Тестирование вставки элемента
    array.InsertAt(100, 5);
    assert(array.GetElement(5) == 100);
    assert(array.GetLength() == 11);

    // Тестирование замены элемента
    array.Set(5, 200);
    assert(array.GetElement(5) == 200);

    // Тестирование удаления элемента
    array.InsertAt(300, 0); // Вставляем в начало
    assert(array.GetFirstElement() == 300);
    array.InsertAt(400, 1); // Вставляем во второй элемент
    assert(array.GetElement(1) == 400);
    array.InsertAt(500, 2); // Вставляем в третий элемент
    assert(array.GetElement(2) == 500);

    // Проверка длины после вставок
    assert(array.GetLength() == 14);

    // Тестирование получения подпоследовательности
    if (array.GetLength() >= 4) { // Проверяем, что в массиве достаточно элементов
        DynamicArray<int>* subArray = dynamic_cast<DynamicArray<int>*>(array.GetSubsequence(0, 4)); 
        if (!subArray) {
            throw std::runtime_error("Функция GetSubsequence() вернула объект, который не является DynamicArray.");
        }
        assert(subArray->GetLength() == 4);
        assert(subArray->GetElement(0) == 300);
        assert(subArray->GetElement(1) == 400);
        assert(subArray->GetElement(2) == 500);
        assert(subArray->GetElement(3) == 0);
        delete subArray; // Освобождаем память
    } else {
        std::cout << "Недостаточно элементов в массиве для тестирования подпоследовательности.\n";
    }
    // Тестирование объединения массивов
    DynamicArray<int> otherArray;
    otherArray.Append(10);
    otherArray.Append(11);
    array.Union(&otherArray);
    assert(array.GetLength() == 16);
    assert(array.GetElement(14) == 10);
    assert(array.GetElement(15) == 11);

    std::cout << "Тест DynamicArray пройден успешно.\n";
}


void functionalTestLinkedList() {
    std::cout << "\n=== Тестирование LinkedList ===\n";

    // Создание связного списка
    LinkedList<int> list;

    // Тестирование добавления элементов
    for (int i = 0; i < 10; ++i) {
        list.Append(i);
    }

    // Проверка добавленных элементов
    for (int i = 0; i < 10; ++i) {
        assert(list.GetElement(i) == i);
    }

    // Проверка длины списка
    assert(list.GetLength() == 10);

    // Тестирование доступа к первому и последнему элементу
    assert(list.GetFirstElement() == 0);
    assert(list.GetLastElement() == 9);

    // Тестирование вставки элемента
    list.InsertAt(100, 5);
    assert(list.GetElement(5) == 100);
    assert(list.GetLength() == 11);

    // Тестирование замены элемента
    list.Set(5, 200);
    assert(list.GetElement(5) == 200);

    // Тестирование удаления элемента
    list.InsertAt(300, 0); // Вставляем в начало
    assert(list.GetFirstElement() == 300);
    list.InsertAt(400, 1); // Вставляем во второй элемент
    assert(list.GetElement(1) == 400);
    list.InsertAt(500, 2); // Вставляем в третий элемент
    assert(list.GetElement(2) == 500);

    // Проверка длины после вставок
    assert(list.GetLength() == 14);

    // Тестирование получения подпоследовательности
    if (list.GetLength() >= 4) { // Проверяем, что в списке достаточно элементов
        LinkedList<int>* subList = list.GetSubsequence(0, 3);
        assert(subList->GetLength() == 4);
        assert(subList->GetElement(0) == 300);
        assert(subList->GetElement(1) == 400);
        assert(subList->GetElement(2) == 500);
        assert(subList->GetElement(3) == 0);
        delete subList; // Освобождаем память
    } else {
        std::cout << "Недостаточно элементов в списке для тестирования подпоследовательности.\n";
    }

    // Тестирование объединения списков
    LinkedList<int> otherList;
    otherList.Append(10);
    otherList.Append(11);
    list.Union(&otherList);
    assert(list.GetLength() == 16);
    assert(list.GetElement(14) == 10);
    assert(list.GetElement(15) == 11);

    std::cout << "Тест LinkedList пройден успешно.\n";
}

// Функция для тестирования DynamicArray с персонами
void testPersonsDynamicArray(int maxElements, int step,
                          const DynamicArray<std::string>& maleFirstNames,
                          const DynamicArray<std::string>& femaleFirstNames,
                          const DynamicArray<std::string>& maleLastNames,
                          const DynamicArray<std::string>& femaleLastNames,
                          const DynamicArray<std::string>& malePatronymics,
                          const DynamicArray<std::string>& femalePatronymics) {

    std::cout << "\n=== Тест производительности DynamicArray с использованием Person ===\n";

    ensureDirectories();
    std::string resultsFile = "graph/dynamic_array.dat";

    std::ofstream dataFile(resultsFile);
    dataFile << "# Количество элементов\tВремя (мс)\n";

    // Запись начального значения (0 элементов, 0 времени)
    dataFile << 0 << "\t" << 0 << "\n";

    std::cout << std::setw(20) << "Количество элементов" << std::setw(20) << "Время (мс)" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    // Запись для 0 элементов
    std::cout << std::setw(20) << 0 << std::setw(20) << 0 << std::endl;

    for (int numElements = step; numElements <= maxElements; numElements += step) {
        DynamicArray<Person> dynamicArray;

        auto start = std::chrono::high_resolution_clock::now();

        // Добавление элементов типа Person
        for (int i = 0; i < numElements; ++i) {
            dynamicArray.Append(generateRandomPerson(maleFirstNames, femaleFirstNames,
                                                     maleLastNames, femaleLastNames,
                                                     malePatronymics, femalePatronymics));
        }

        // Доступ к элементам
        for (int i = 0; i < numElements; ++i) {
            volatile Person person = dynamicArray.GetElement(i);
            (void)person; // Убираем предупреждение о неиспользуемой переменной
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << std::setw(20) << numElements << std::setw(20) << duration.count() << std::endl;
        dataFile << numElements << "\t" << duration.count() << "\n";
    }

    dataFile.close();

    // Генерация gnuplot-скрипта
    std::ofstream plotFile("graph/dynamic_array.plt");
    plotFile << "set terminal png size 800,600\n";
    plotFile << "set output 'graph/dynamic_array.png'\n";
    plotFile << "set title 'Performance of DynamicArray with Person'\n";
    plotFile << "set xlabel 'Number of Elements'\n";
    plotFile << "set ylabel 'Time (ms)'\n";
    plotFile << "set xrange [0:*]\n"; // График из 0
    plotFile << "set yrange [0:*]\n"; // График из 0
    plotFile << "plot '" << resultsFile << "' using 1:2 with linespoints title 'DynamicArray'\n";
    plotFile.close();

    // Запуск gnuplot
    if (std::system("gnuplot graph/dynamic_array.plt") == 0) {
        std::cout << "График сохранён как graph/dynamic_array.png.\n";
    } else {
        std::cerr << "Ошибка при построении графика DynamicArray.\n";
    }
}

// Тест производительности всех сортировок
void runSortPerformanceTest(int maxPersons, int step,
                             const DynamicArray<std::string>& maleFirstNames,
                             const DynamicArray<std::string>& femaleFirstNames,
                             const DynamicArray<std::string>& maleLastNames,
                             const DynamicArray<std::string>& femaleLastNames,
                             const DynamicArray<std::string>& malePatronymics,
                             const DynamicArray<std::string>& femalePatronymics) {
    std::cout << "\n=== Тест производительности сортировок ===\n";

    std::cout << std::setw(20) << "Количество элементов"
              << std::setw(20) << "MergeSort (мс)"
              << std::setw(20) << "QuickSort (мс)"
              << std::setw(20) << "HeapSort (мс)" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    // Открываем файл для записи результатов
    std::ofstream dataFile("graph/sort_performance.dat");
    dataFile << "# Количество элементов\tMergeSort\tQuickSort\tHeapSort\n";

    // Запись начального значения (0 элементов, 0 времени)
    dataFile << 0 << "\t" << 0 << "\t" << 0 << "\t" << 0 << "\n";
    std::cout << std::setw(20) << 0 << std::setw(20) << 0 << std::setw(20) << 0 << std::setw(20) << 0 << std::endl;

    for (int numPersons = step; numPersons <= maxPersons; numPersons += step) {
        DynamicArray<Person> persons;
        generatePersonsInMemory(numPersons, persons, maleFirstNames, femaleFirstNames,
                                 maleLastNames, femaleLastNames, malePatronymics, femalePatronymics); // Генерация данных в массиве

        // Измерение времени для MergeSort
        auto startMerge = std::chrono::high_resolution_clock::now();
        MergeSort<Person>().Sort(persons, comparePersonFullName, true);
        auto endMerge = std::chrono::high_resolution_clock::now();
        auto mergeSortTime = std::chrono::duration_cast<std::chrono::milliseconds>(endMerge - startMerge).count();

        // Измерение времени для QuickSort
        auto startQuick = std::chrono::high_resolution_clock::now();
        QuickSort<Person>().Sort(persons, comparePersonFullName, true);
        auto endQuick = std::chrono::high_resolution_clock::now();
        auto quickSortTime = std::chrono::duration_cast<std::chrono::milliseconds>(endQuick - startQuick).count();

        // Измерение времени для HeapSort
        auto startHeap = std::chrono::high_resolution_clock::now();
        HeapSort<Person>().Sort(persons, comparePersonFullName, true);
        auto endHeap = std::chrono::high_resolution_clock::now();
        auto heapSortTime = std::chrono::duration_cast<std::chrono::milliseconds>(endHeap - startHeap).count();

        // Вывод результатов
        std::cout << std::setw(20) << numPersons
                  << std::setw(20) << mergeSortTime
                  << std::setw(20) << quickSortTime
                  << std::setw(20) << heapSortTime << std::endl;

        // Записываем результаты в файл
        dataFile << numPersons << "\t" << mergeSortTime << "\t" << quickSortTime << "\t" << heapSortTime << "\n";
    }

    dataFile.close();

    // Генерация gnuplot-скрипта
    std::ofstream plotFile("graph/sort_performance.plt");
    plotFile << "set terminal png size 800,600\n";
    plotFile << "set output 'graph/sort_performance.png'\n";
    plotFile << "set title 'Performance of Sorting Algorithms'\n";
    plotFile << "set xlabel 'Number of Elements'\n";
    plotFile << "set ylabel 'Time (ms)'\n";
    plotFile << "set xrange [0:*]\n"; // График из 0
    plotFile << "set yrange [0:*]\n"; // График из 0
    plotFile << "plot 'graph/sort_performance.dat' using 1:2 with linespoints title 'MergeSort', \\\n";
    plotFile << "     '' using 1:3 with linespoints title 'QuickSort', \\\n";
    plotFile << "     '' using 1:4 with linespoints title 'HeapSort'\n";
    plotFile.close();

    // Запуск gnuplot
    if (std::system("gnuplot graph/sort_performance.plt") == 0) {
        std::cout << "График сохранён как graph/sort_performance.png.\n";
    } else {
        std::cerr << "Ошибка при построении графика сортировок.\n";
    }
}

// Основное меню 
void tests() {
    ensureDirectories(); 

    // Загрузка имен из файлов
    DynamicArray<std::string> maleFirstNames = readNamesFromFile("names/male_first_names.txt");
    DynamicArray<std::string> femaleFirstNames = readNamesFromFile("names/female_first_names.txt");
    DynamicArray<std::string> maleLastNames = readNamesFromFile("names/male_last_names.txt");
    DynamicArray<std::string> femaleLastNames = readNamesFromFile("names/female_last_names.txt");
    DynamicArray<std::string> malePatronymics = readNamesFromFile("names/male_patronymics.txt");
    DynamicArray<std::string> femalePatronymics = readNamesFromFile("names/female_patronymics.txt");

    while (true) {
        std::cout << "\n=== Нагрузочные тесты ===\n";
        std::cout << "1. Тест производительности DynamicArray\n";
        std::cout << "2. Тест производительности сортировок\n";
        std::cout << "3. Функциональные тесты\n";
        std::cout << "0. Назад\n";

        int choice = getInput("Выберите действие: ");

        switch (choice) {
            case 1: {
                int numElements = getInput("Введите количество элементов для DynamicArray: ");
                int step = getInput("Введите шаг элементов для DynamicArray: ");

                if (step <= 0 || numElements <= 0) {
                    std::cerr << "Ошибка: количество элементов и шаг должны быть больше нуля.\n";
                    break;
                }

                testPersonsDynamicArray(numElements, step, maleFirstNames, femaleFirstNames,
                                    maleLastNames, femaleLastNames, malePatronymics, femalePatronymics);
                break;
            }
            case 2: {
                int numPersons = getInput("Введите количество рандомно создаваемых персон: ");
                int step = getInput("Введите шаг для рандомно создаваемых персон : ");

                if (step <= 0 || numPersons <= 0) {
                    std::cerr << "Ошибка: количество персон и шаг должны быть больше нуля.\n";
                    break; 
                }

                runSortPerformanceTest(numPersons, step, maleFirstNames, femaleFirstNames,
                                       maleLastNames, femaleLastNames, malePatronymics, femalePatronymics);
                break;
            }
            case 3: 
                functionalTestDynamicArray();
                functionalTestLinkedList();
                break;
            case 0:
                return;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}