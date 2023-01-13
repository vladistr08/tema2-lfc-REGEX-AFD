//
// Created by istra on 1/12/23.
//

#ifndef TEMA2_LFC_REGEX_AFD_USEFULMETHODS_H
#define TEMA2_LFC_REGEX_AFD_USEFULMETHODS_H

#include <string>
#include <vector>
#include <algorithm>

class UsefulMethods {
public:
    UsefulMethods() = delete;
    UsefulMethods(const UsefulMethods &) = delete;
    ~UsefulMethods() = delete;

    void operator=(const UsefulMethods&) = delete;

    static void removeDuplicates(std::vector<std::string> &v);
    static std::vector<std::string> unionVector(std::vector<std::string> v1, std::vector<std::string> v2);
    static bool isValidRegex(const std::string &regex);
    static std::string convertVectorOfStatesToString(const std::vector<std::string> &states);

};


#endif //TEMA2_LFC_REGEX_AFD_USEFULMETHODS_H
