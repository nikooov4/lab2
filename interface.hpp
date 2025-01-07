#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <string>

void showMenu();
int getInput(const std::string& prompt);
std::string getInput(const std::string& prompt, bool isString);
std::string selectFolder();
std::string selectFileFromFolder(const std::string& folder);

#endif