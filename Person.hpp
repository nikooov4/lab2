#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

struct Person {
    std::string firstName;
    std::string lastName;
    std::string patronymic;
    int yearOfBirth;
    double height;
    double weight;
};

#endif

