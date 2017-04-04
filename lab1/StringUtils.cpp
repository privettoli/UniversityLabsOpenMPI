//
// Created by Anatoly Papenko on 4/3/17.
//

#include "StringUtils.h"
#include "Constants.h"

using std::string;
using std::to_string;

string *StringUtils::intArrayToString(int *array, int size) {
    auto str = new string("[");
    for (auto i = 0; i < size; ++i) {
        str->append($int(array[i]));
        auto hasMoreElements = i + 1 < size;
        if (hasMoreElements) {
            str->append(", ");
        }
    }
    str->append("]");
    return str;
}
