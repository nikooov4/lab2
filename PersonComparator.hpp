#ifndef PERSON_COMPARATOR_HPP
#define PERSON_COMPARATOR_HPP

#include "Person.hpp"
#include "Comparator.hpp"

int comparePersonFirstName(const Person& a, const Person& b, bool ascending);
int comparePersonLastName(const Person& a, const Person& b, bool ascending);
int comparePersonPatronymic(const Person& a, const Person& b, bool ascending);
int comparePersonYearOfBirth(const Person& a, const Person& b, bool ascending);
int comparePersonHeight(const Person& a, const Person& b, bool ascending);
int comparePersonWeight(const Person& a, const Person& b, bool ascending);
int comparePersonFullName(const Person& a, const Person& b, bool ascending);

#endif 