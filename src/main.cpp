#include <iostream>
#include <string>
#include "helper.h"
#include "echo.h"
#include "type.h"

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string x;
 
  while(1){
  std::cout << "$ ";

  if(std::getline(std::cin, x)){
    std::vector<std::string> temp_vector = helper::splitter(x);

    if(temp_vector[0]=="exit"){
      break;
    }
    else if(temp_vector[0]=="echo"){
      echo(x);
      continue;
    }
    else if(temp_vector[0]=="type"){
      type::type(temp_vector[1],temp_vector);
      continue;
    }
    
    std::cout << x << ": command not found" << std::endl;
  }
  else{
    break;
  }
  
  }
}
