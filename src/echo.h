#pragma once
#include <string>
#include "helper.h"
#include <iostream>



inline void echo(std::string x){
    auto ret_val = helper::splitter(x.substr(5));

    
    for(const auto& word: ret_val){
        std:: cout << word;
    }
    std::cout << std::endl;

    return;
}
