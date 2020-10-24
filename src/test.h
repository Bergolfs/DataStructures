#pragma once
#include <iostream>
#include "HashMap.h"

std::string random_string( size_t length );

void fill_with_random_strings(HashMap::HashMap<std::string, int>& map, size_t elem_number);