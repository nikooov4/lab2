#ifndef DATA_CREATOR_HPP
#define DATA_CREATOR_HPP

#include "DynamicArray.hpp"
#include "Person.hpp"

#include <string>

void ensureDirectories();
Person generateRandomPerson(const DynamicArray<std::string>& maleFirstNames,
                            const DynamicArray<std::string>& femaleFirstNames,
                            const DynamicArray<std::string>& maleLastNames,
                            const DynamicArray<std::string>& femaleLastNames,
                            const DynamicArray<std::string>& malePatronymics,
                            const DynamicArray<std::string>& femalePatronymics);
void createPerson(int numberOfPersons, const std::string& filename);
DynamicArray<std::string> readNamesFromFile(const std::string& filename);

#endif 