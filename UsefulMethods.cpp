//
// Created by istra on 1/12/23.
//

#include "UsefulMethods.h"


void UsefulMethods::removeDuplicates(std::vector<std::string> &v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }
    v.erase(end, v.end());
}

std::vector<std::string> UsefulMethods::unionVector(std::vector<std::string> v1, std::vector<std::string> v2) {
    std::vector<std::string> unifiedVector;
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(unifiedVector));
    return unifiedVector;
}

bool UsefulMethods::isValidRegex(const std::string &regex) {
    for (char c : regex)
    {
        bool ok = false;
        if (isalpha(c) || isdigit(c) || c == '|' || c == '.' || c == '*' || c == '(' || c == ')') {
            ok = true;
        }
        if (!ok) {
            return false;
        }
    }
    for (int i = 1; i < regex.length(); i++)
    {
        if (regex[i - 1] == regex[i] || (isalpha(regex[i-1]) && isalpha(regex[i])) || (isdigit(regex[i - 1]) && isdigit(regex[i])))
            return false;
    }

    if (count(regex.begin(), regex.end(), '(') != count(regex.begin(), regex.end(), ')')) {
        return false;
    }
    return true;
}

std::string UsefulMethods::convertVectorOfStatesToString(const std::vector<std::string> &states) {
    std::string result = "{";
    for(const auto & state: states){
        result += state;
        result += ",";
    }
    result += "}";
}

bool UsefulMethods::equalSets(const std::unordered_set<std::string> &a, const std::unordered_set<std::string> &b) {
    if(a.size() != b.size())
        return false;
    for(const auto & el: a)
        if(b.find(el) == b.end())
            return false;
    return true;
}
