#include "ISorted.hpp"
#include "PersonComparator.hpp"
#include "dataCreator.hpp"   
#include "DynamicArray.hpp"  
#include "tests.hpp"     
#include "QuickSort.hpp"   
#include "HeapSort.hpp"      
#include "MergeSort.hpp"     

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <sstream> // Для std::stringstream
#include <algorithm> // Для std::remove_if

namespace fs = std::filesystem;

// Функция для получения числового ввода
int getInput(const std::string& prompt) {
    std::string input;
    int value = 0;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);  // Считываем строку целиком

        // Удаляем пробелы из строки
        input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

        // Пробуем преобразовать строку в число
        std::istringstream iss(input);
        if (iss >> value) {
            break; // Успешно преобразовано
        } else {
            std::cout << "Ошибка: введите корректное число.\n";
        }
    }
    return value;
}

// Функция для получения строкового ввода
std::string getInput(const std::string& prompt, bool isString) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);  // Считываем строку целиком

    // Удаляем пробелы из строки
    value.erase(std::remove(value.begin(), value.end(), ' '), value.end());

    return value;
}

// Функция для выбора папки
std::string selectFolder() {
    while (true) {
        std::cout << "\n=== Выберите папку ===\n";
        std::cout << "1. files (исходные данные)\n";
        std::cout << "2. sorted_files (отсортированные данные)\n";
        std::cout << "0. Назад\n";

        int choice = getInput("Выберите папку: ");
        switch (choice) {
            case 1:
                return "files";
            case 2:
                return "sorted_files";
            case 0:
                return ""; // Возврат без выбора
            default:
                std::cout << "Неверный ввод. Попробуйте снова.\n";
        }
    }
}

// Функция выбора файла из папки
std::string selectFileFromFolder(const std::string& folder) {
    DynamicArray<std::string> files;
    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.path().extension() == ".txt") {
            files.Append(entry.path().filename().string());
        }
    }

    if (files.GetLength() == 0) {
        std::cout << "Нет файлов для сортировки в папке: " << folder << ".\n";
        return "";
    }

    std::cout << "Доступные файлы (0 - Назад):\n";
    for (int i = 0; i < files.GetLength(); ++i) {
        std::cout << i + 1 << ". " << files[i] << "\n";
    }

    int fileChoice = getInput("Выберите файл для сортировки (номер): ");
    if (fileChoice < 1 || fileChoice > files.GetLength()) {
        std::cout << "Неверный выбор файла.\n";
        return "";
    } else if (fileChoice == 0) { return ""; }

    return folder + "/" + files[fileChoice - 1]; // Возвращаем полный путь к выбранному файлу
}

// Функция для выбора типа сортировки
int selectSortType() {
    while (true) {
        std::cout << "\n=== Выберите тип сортировки ===\n";
        std::cout << "1. QuickSort\n";
        std::cout << "2. HeapSort\n";
        std::cout << "3. MergeSort\n";
        std::cout << "0. Назад\n";

        int choice = getInput("Выберите тип сортировки: ");
        if (choice == 1 || choice == 2 || choice == 3) {
            return choice; // Возвращаем выбранный тип сортировки
        } else if (choice == 0) {
            return -1; // Возврат по умолчанию
        } else {
            std::cout << "Неверный ввод. Попробуйте снова.\n";
        }
    }
}

// Функция для выбора параметра сортировки
int selectParameter() {
    while (true) {
        std::cout << "\n=== Выберите параметр сортировки ===\n";
        std::cout << "1. ФИО\n";
        std::cout << "2. Год рождения\n";
        std::cout << "3. Рост\n";
        std::cout << "4. Вес\n";
        std::cout << "0. Назад\n";

        int choice = getInput("Выберите параметр сортировки: ");
        if (choice == 1 || choice == 2 || choice == 3 || choice == 4) {
            return choice; // Возвращаем выбранный параметр
        } else if (choice == 0) {
            return -1; // Возврат по умолчанию
        } else {
            std::cout << "Неверный ввод. Попробуйте снова.\n";
        }
    }
}

// Функция для выбора порядка сортировки
int selectOrder() {
    while (true) {
        std::cout << "\n=== Выберите порядок сортировки ===\n";
        std::cout << "1. По возрастанию\n";
        std::cout << "2. По убыванию\n";
        std::cout << "0. Назад\n";

        int choice = getInput("Выберите порядок сортировки: ");
        if (choice == 1) return 1; // По возрастанию
        if (choice == 2) return 0; // По убыванию
        if (choice == 0) return -1; // Назад
        std::cout << "Неверный ввод. Попробуйте снова.\n";
    }
}

//Функция для создания файла с персонами
void createPersonsFile() {
    try {
        int numberOfPersons = getInput("Введите количество персон для генерации: ");
        std::string filename = getInput("Введите имя файла для сохранения (без .txt): ", true);
        createPerson(numberOfPersons, "files/" + filename + ".txt");
        std::cout << "Файл с персонами успешно создан: " << filename + ".txt" << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << "\n";
    }
}

// Функция для сортировки файла
void sortFile(const std::string& inputFile, const std::string& outputFile, int sortType, int parameter, bool ascending) {
    // Считываем данные из файла в DynamicArray
    DynamicArray<Person> persons;
    std::ifstream inFile(inputFile);

    if (!inFile.is_open()) {
        throw std::runtime_error("Ошибка открытия файла: " + inputFile);
    }

    std::string lastName, firstName, patronymic;
    int yearOfBirth;
    double height, weight;

    while (inFile >> lastName >> firstName >> patronymic >> yearOfBirth >> height >> weight) {
        Person person = {firstName, lastName, patronymic, yearOfBirth, height, weight};
        persons.Append(person);
    }

    inFile.close();

    // Выбор алгоритма сортировки
    if (sortType == 1) {
        QuickSort<Person> sorter;
        switch (parameter) {
            case 1: // ФИО
                sorter.Sort(persons, comparePersonFullName, ascending);
                break;
            case 2: // Год рождения
                sorter.Sort(persons, comparePersonYearOfBirth, ascending);
                break;
            case 3: // Рост
                sorter.Sort(persons, comparePersonHeight, ascending);
                break;
            case 4: // Вес
                sorter.Sort(persons, comparePersonWeight, ascending);
                break;
            default:
                throw std::invalid_argument("Неверный параметр сортировки.");
        }
    } else if (sortType == 2) {
        HeapSort<Person> sorter;
        switch (parameter) {
            case 1: // ФИО
                sorter.Sort(persons, comparePersonFullName, ascending);
                break;
            case 2: // Год рождения
                sorter.Sort(persons, comparePersonYearOfBirth, ascending);
                break;
            case 3: // Рост
                sorter.Sort(persons, comparePersonHeight, ascending);
                break;
            case 4: // Вес
                sorter.Sort(persons, comparePersonWeight, ascending);
                break;
            default:
                throw std::invalid_argument("Неверный параметр сортировки.");
        }
    } else if (sortType == 3) {
        MergeSort<Person> sorter;
        switch (parameter) {
            case 1: // ФИО
                sorter.Sort(persons, comparePersonFullName, ascending);
                break;
            case 2: // Год рождения
                sorter.Sort(persons, comparePersonYearOfBirth, ascending);
                break;
            case 3: // Рост
                sorter.Sort(persons, comparePersonHeight, ascending);
                break;
            case 4: // Вес
                sorter.Sort(persons, comparePersonWeight, ascending);
                break;
            default:
                throw std::invalid_argument("Неверный параметр сортировки.");
        }
    } else {
        throw std::invalid_argument("Неверный тип сортировки.");
    }

    // Сохраняем отсортированные данные в выходной файл
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        throw std::runtime_error("Ошибка открытия файла для записи: " + outputFile);
    }

    outFile << std::fixed << std::setprecision(1); // Устанавливаем формат вывода

    for (int i = 0; i < persons.GetLength(); ++i) {
        const Person& person = persons.GetElement(i);
        outFile << person.lastName << " " << person.firstName << " "
                << person.patronymic << " " << person.yearOfBirth << " "
                << person.height << " " << person.weight << "\n";
    }

    outFile.close();
}

// Основное меню
int showMenu() {
    ensureDirectories();
    while (true) {
        std::cout << "\n=== Главное меню ===\n";
        std::cout << "1. Создать файл с персонами\n";
        std::cout << "2. Сортировка\n";
        std::cout << "3. Тесты\n"; 
        std::cout << "0. Выход\n";

        int mainChoice = getInput("Выберите действие: ");
        switch (mainChoice) {
            case 1:
                createPersonsFile();
                break;
            case 2: {
                std::string folder = selectFolder();
                if (folder.empty()) continue; // Если пользователь выбрал "Назад"

                std::string file = selectFileFromFolder(folder);
                if (file.empty()) continue; // Если пользователь выбрал "Назад"

                int sortType = selectSortType();
                if (sortType == -1) continue; // Если пользователь выбрал "Назад"

                int parameter = selectParameter();
                if (parameter == -1) continue; // Если пользователь выбрал "Назад"

                int ascending = selectOrder();
                if (ascending == -1) continue; // Если пользователь выбрал "Назад"

                // Выполняем сортировку
                std::string outputFile = "sorted_files/sorted_" + fs::path(file).filename().string();
                sortFile(file, outputFile, sortType, parameter, ascending);

                std::cout << "Файл отсортирован и сохранен в: " << outputFile << "\n";
                break;
            }
            case 3: // Вызов функции для тестов
                tests();
                break;
            case 0:
                return 0; // Выход из программы
            default:
                std::cout << "Неверный ввод. Попробуйте снова.\n";
        }
    }
    return 0;
}