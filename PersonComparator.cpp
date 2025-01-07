#include "PersonComparator.hpp"

#include <iostream>

int comparePersonFirstName(const Person& a, const Person& b, bool ascending) {
    return compareDefault(a.firstName, b.firstName, ascending);
}

int comparePersonLastName(const Person& a, const Person& b, bool ascending) {
    return compareDefault(a.lastName, b.lastName, ascending);
}

int comparePersonPatronymic(const Person& a, const Person& b, bool ascending) {
    return compareDefault(a.patronymic, b.patronymic, ascending);
}

int comparePersonYearOfBirth(const Person& a, const Person& b, bool ascending) {
    return compareDefault(a.yearOfBirth, b.yearOfBirth, ascending);
}

int comparePersonHeight(const Person& a, const Person& b, bool ascending) {
    return compareDefault(a.height, b.height, ascending);
}

int comparePersonWeight(const Person& a, const Person& b, bool ascending) {
    return compareDefault(a.weight, b.weight, ascending);
}

// Комплексное сравнение по ФИО
int comparePersonFullName(const Person& a, const Person& b, bool ascending) {
    // Сначала сравниваем фамилии
    int lastNameComparison = comparePersonLastName(a, b, ascending);
    if (lastNameComparison != 0) {
        return lastNameComparison;
    }

    // Если фамилии одинаковые, сравниваем имена
    int firstNameComparison = comparePersonFirstName(a, b, ascending);
    if (firstNameComparison != 0) {
        return firstNameComparison;
    }

    // Если фамилии и имена одинаковые, сравниваем отчества
    return comparePersonPatronymic(a, b, ascending);
}


