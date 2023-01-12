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
