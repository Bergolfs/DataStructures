#include <iostream>
#include <string>
#include <algorithm>
#include "HashMap.h"
#include "test.h"

std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "йцукенгшщзхъфываролджэячсмитьбю"
        "ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ"
        ;
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

void fill_with_random_strings(HashMap::HashMap<std::string, int>& map, size_t elem_number){
    for (size_t i = 0; i < elem_number; ++i){
        map.insert(random_string((i % 6) + 5), i);
    }
}