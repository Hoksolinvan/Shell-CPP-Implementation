#pragma once
#include <string>
#include <iostream>
#include <set>
#include <filesystem>
#include <string_view>
#include <unistd.h>
#include "helper.h"

namespace type{

    const std::set<std::string> cur_set = {"echo","exit","type","pwd"};


    std::string file_traversal(std::string_view input){
        auto x = std::getenv("PATH");
        if(!x) return ": not found";

        std::string env(x);

        std::vector<std::string> paths = helper::splitter(env,':');


        for(const auto& path: paths){

            std::filesystem::path full = std::filesystem::path(path) / input;

            
            if(std::filesystem::exists(full)){

                if(!access(full.c_str(),X_OK)){

                return " is " + std::string(full);

                    
                }
            }


        }
        return ": not found";
    }

    inline bool is_executable(std::string_view input) {
    auto x = std::getenv("PATH");
    if (!x)
      return false;
    std::string env(x);
    std::vector<std::string> paths = helper::splitter(env, ':');
    for (const auto &path : paths) {
      std::filesystem::path full = std::filesystem::path(path) / input;
     
      if (std::filesystem::exists(full) && !access(full.c_str(),X_OK)) {
        
        // if (!access(full.c_str(), X_OK)) {

        //   // std::cout << input << "is" << " " << path << std::endl;
          
        //   return true;
        // }

        std::cout << "pp" << std::endl;
        return true;

      }
    }
    
    return false;
  }

    

    inline bool type(std::string input){
      

            if(cur_set.find(input)!=cur_set.end()){

                std::cout << input << " is a shell builtin" << std::endl;
                return true;
            }
            std::string temp = file_traversal(input);
            if(temp ==": not found"){
              // "/vcpkg:/cmake/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
              if(is_executable(input)){

                return true;
              }
              else{
               
                std::cout << input << temp << std::endl;
              }
              
            }
            
            
          
            return (temp == ": not found") ? false : true;
    }
}
