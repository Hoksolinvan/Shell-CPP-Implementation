#pragma once
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "type.h"


namespace helper{   
    inline std::vector<std::string> splitter(std::string input,char delimiter=' ');
}

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
     
      if (std::filesystem::exists(full)) {
        
        if (!access(full.c_str(), X_OK)) {

         // std::cout << input << " is " << path << "/" << input << std::endl;
          
          return true;
        }

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


            if(temp!=": not found"){
              std::cout << input << temp << std::endl;
              return true;
            }
            else if(is_executable(input)){

              // "/vcpkg:/cmake/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
             
              return true;
            }
            else{
              std::cout << input << ": not found" << std::endl;
            }
            
            
          
            return (temp == ": not found") ? false : true;
    }
}



namespace helper{
inline std::vector<std::string> splitter(std::string input,char delimiter){


    std::vector<std::string> result;
    std::string word;
    bool quote_on = false;
    bool double_quote_on = false;
    bool backslash = false;
    bool inner_backslash = false;
    bool redirection = false;

    std::string previous ="";
    
    
    for(char c : input){



        



        if(inner_backslash){
             if(c=='\'' && quote_on){
                continue;
            }
            word+=c;
            inner_backslash = !inner_backslash;
            continue;
        }

         if(backslash){
           
            word+=c;
            backslash = !backslash;
            continue;
        }

        if(!quote_on && !double_quote_on && c=='\\'){
            backslash = !backslash;
            continue;
        }
        // else if(!quote_on && double_quote_on && c=='\\'){

        // }
        else if((quote_on || double_quote_on) && c=='\\'){

            if(quote_on){
            word+=c;
            }
            inner_backslash = !inner_backslash;
            continue;
        }

        
        // if(c=='>'){
        //     std::string executable = result[result.size()-2];

        //     if(!type::is_executable(executable)){
        //         result.clear();
        //         result.push_back(executable + ": No such file or directory");
        //         break;
        //     }
            
        //     previous=executable;
        //     redirection = !redirection;
        //     continue;
        // }
       
        
        
        if(c=='\"'){
            if(inner_backslash){


                if(quote_on || double_quote_on){
                    word+='\\';
                }
                word+=c;
                inner_backslash = !inner_backslash;
                continue;
            }


            if(quote_on){
                word+='\"';
            }
            double_quote_on = !double_quote_on;
            continue;
        }
        
        if(c=='\''){
            if(double_quote_on){
                word+=c;
                continue;
            }
            quote_on = !quote_on;

            
           continue;
        }
        
        
        if(c==delimiter){
            if(quote_on || double_quote_on){
                word+=" ";
            }
            else if(!word.empty()){
                result.push_back(word);
                // if(redirection){
                //     int saved = dup(STDOUT_FILENO);
                //     int fd[2];
                //     pipe(fd);
                //     pid_t pid = fork();

                //     if(pid==0){
                        
                       
                //         close(fd[0]);

                //         dup2(fd[1],STDOUT_FILENO);
                //         close(fd[1]);

                //         char* args[] = { (char*)previous.c_str(), NULL };
                //         execvp(args[0], args);
                        

                //         perror("exevp failed");
                //         _exit(1);
                //     }
                //     else {
                //         close(fd[1]);

                //         char buffer[4096];
                //         std::string output;
                //         int n;

                //         while((n = read(fd[0],buffer,sizeof(buffer)))>0){
                //             output.append(buffer,n);
                //         }
                        

                //         close(fd[0]);
                //         waitpid(pid, NULL, 0);

                //         std::ofstream Myfile(word);
                //         Myfile << output;
                //         dup2(saved, STDOUT_FILENO);
                //         close(saved);
                //     }

                    

                // }
                
                word.clear();
                result.push_back(" ");
            }
            
            
        }
        else{
            
            word+=c;
        }
    }
    
    
    if(!word.empty()){
    result.push_back(word);
    }
    
    
    return result;
}
}
