#include "echo.h"
#include "helper.h"

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string x;
  while (1) {
    std::cout << "$ ";
    if (std::getline(std::cin, x)) {
      std::vector<std::string> temp_vector = helper::splitter(x);
      if (temp_vector[0] == "exit") {
        break;
      } else if (temp_vector[0] == "echo") {
        echo(x);
        continue;

      } else if (temp_vector[0] == "type") {
        std::vector<std::string> parts = helper::splitter(x, ' ');
        if (temp_vector.size() < 2) {
          std::cout << "type: missing argument" << std::endl;
          continue;
        }


         type::type(temp_vector[2]);
      
        continue;

      } else if (type::is_executable(temp_vector[0])) {
        pid_t pid = fork();
        if (pid < 0) {
          perror("fork failed");
          continue;
        }
        if (pid == 0) {
          std::vector<char *> argv;
          for (size_t i = 0; i < temp_vector.size(); i++){
            if(temp_vector[i]!=" "){
            argv.push_back(temp_vector[i].data());
            }
          }
          argv.push_back(nullptr);
          execvp(argv[0], argv.data());
          perror("exec failed");
          _exit(1);
        } else {
          int status;
          wait(&status);
        }
      }
      else if(temp_vector[0]=="pwd"){

        
            std::cout << std::filesystem::current_path().c_str() << std::endl;
       
      }
      else if(temp_vector[0]=="cd"){

        if(temp_vector[2] != "~" && !std::filesystem::exists(temp_vector[2])){
          std::cerr << "cd: " << temp_vector[2] << ": No such file or directory" << std::endl;
          continue;
        }
     

       if (temp_vector.size() < 3 || temp_vector[2] == "~") {
        auto x = std::getenv("HOME");
        try {
            std::filesystem::current_path(x);
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "cd: " << x << ": No such file or directory" << std::endl;
        }
        continue;
    }
    else {
        try {
            std::filesystem::current_path(temp_vector[2]);
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "cd: " << temp_vector[1] << ": No such file or directory" << std::endl;
        }
    }
      }
    
      else {
        std::cout << temp_vector[0] << ": command not found" << std::endl;
      }
    } else {
      break;
    }
  }
}
