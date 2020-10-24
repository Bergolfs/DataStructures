#include <iostream>
#include <string>
#include <algorithm>
#include "HashMap.h"
#include "test.h"
using HashMap::entry;

int main(){
    using HashMap::HashMap;
    HashMap<std::string, int> hm;
    // hm.insert("Hello", 5);
    // for (int i = 0; i < 512; ++i){
    //     hm.insert(random_string((i % 6) + 5), i);
    // }
    // hm.print();
    fill_with_random_strings(hm, 512);
    hm.print();
}

    