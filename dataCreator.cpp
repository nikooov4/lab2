#include "DynamicArray.hpp"
#include "Person.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

// Проверка и создание директорий
void ensureDirectories() {
    if (!fs::exists("files")) {
        fs::create_directory("files");
    }
    if (!fs::exists("sorted_files")) {
        fs::create_directory("sorted_files");
    }
    if (!fs::exists("graph")) {
        fs::create_directory("graph");
    }
    if (!fs::exists("names")) {
        fs::create_directories("names");
    }
}

// Функция для генерации случайных строк (имен)
std::string generateRandomName(const DynamicArray<std::string>& names) {
    if (names.GetLength() == 0) {
        throw std::runtime_error("Ошибка: массив имён пуст.");
    }

    static std::mt19937 generator(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<size_t> dist(0, names.GetLength() - 1);
    return names.GetElement(dist(generator));
}

// Функция для чтения Фамилий, Имен, Отчеств из файла
DynamicArray<std::string> readNamesFromFile(const std::string& filename) {
    DynamicArray<std::string> names;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    std::string name;
    while (std::getline(file, name)) {
        if (!name.empty()) {  // Игнорируем пустые строки
            names.Append(name);
        }
    }

    if (names.GetLength() == 0) {
        std::cerr << "Файл пуст: " << filename << std::endl;
        throw std::runtime_error("Файл пуст: " + filename);
    }

    return names;
}

// Функция для генерации случайного человека
Person generateRandomPerson(const DynamicArray<std::string>& maleFirstNames,
                            const DynamicArray<std::string>& femaleFirstNames,
                            const DynamicArray<std::string>& maleLastNames,
                            const DynamicArray<std::string>& femaleLastNames,
                            const DynamicArray<std::string>& malePatronymics,
                            const DynamicArray<std::string>& femalePatronymics) {
    // Проверка массивов
    if (maleFirstNames.GetLength() == 0 || femaleFirstNames.GetLength() == 0 ||
        maleLastNames.GetLength() == 0 || femaleLastNames.GetLength() == 0 ||
        malePatronymics.GetLength() == 0 || femalePatronymics.GetLength() == 0) {
        throw std::runtime_error("Ошибка: один или несколько массивов ФИО пусты.");
    }

    static std::mt19937 generator(static_cast<unsigned>(std::time(nullptr)));

    // Генерация случайного пола
    std::uniform_int_distribution<int> genderDist(0, 1);
    bool isFemale = genderDist(generator) == 1;

    // Генерация ФИО
    std::string firstName = isFemale ? generateRandomName(femaleFirstNames) : generateRandomName(maleFirstNames);
    std::string lastName = isFemale ? generateRandomName(femaleLastNames) : generateRandomName(maleLastNames);
    std::string patronymic = isFemale ? generateRandomName(femalePatronymics) : generateRandomName(malePatronymics);

    // Генерация других данных
    std::uniform_int_distribution<int> yearDist(1950, 2010);
    std::uniform_real_distribution<double> heightDist(150.0, 200.0);
    std::uniform_real_distribution<double> weightDist(50.0, 120.0);

    return {
        firstName,
        lastName,
        patronymic,
        yearDist(generator),
        heightDist(generator),
        weightDist(generator)
    };
}

// Функция записи в файл пакетами
void writePersonsToFile(const DynamicArray<Person>& persons, const std::string& filename, int batchSize = 1000) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    outFile << std::fixed << std::setprecision(1);

    for (int i = 0; i < persons.GetLength(); i += batchSize) {
        for (int j = i; j < i + batchSize && j < persons.GetLength(); ++j) {
            const auto& person = persons.GetElement(j);
            outFile << person.lastName << " " << person.firstName << " "
                    << person.patronymic << " " << person.yearOfBirth << " "
                    << person.height << " " << person.weight << std::endl;
        }
    }

    outFile.close();
}

void createPerson(int numberOfPersons, const std::string& filename) {

    // Чтение данных из файлов
    DynamicArray<std::string> maleFirstNames = readNamesFromFile("names/male_first_names.txt");
    DynamicArray<std::string> femaleFirstNames = readNamesFromFile("names/female_first_names.txt");
    DynamicArray<std::string> maleLastNames = readNamesFromFile("names/male_last_names.txt");
    DynamicArray<std::string> femaleLastNames = readNamesFromFile("names/female_last_names.txt");
    DynamicArray<std::string> malePatronymics = readNamesFromFile("names/male_patronymics.txt");
    DynamicArray<std::string> femalePatronymics = readNamesFromFile("names/female_patronymics.txt");
    DynamicArray<Person> persons;

    // Генерация людей
    for (int i = 0; i < numberOfPersons; ++i) {
        persons.Append(generateRandomPerson(maleFirstNames, femaleFirstNames,
                                            maleLastNames, femaleLastNames,
                                            malePatronymics, femalePatronymics));
    }

    // Запись в файл
    writePersonsToFile(persons, filename);
    std::cout << "Файл успешно записан: " << filename << "\n";
}




