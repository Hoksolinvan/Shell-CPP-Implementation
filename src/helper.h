#pragma once
#include <vector>
#include <sstream>
#include <string>

namespace helper{
inline std::vector<std::string> splitter(std::string input,char delimiter=' '){

    // std::vector<std::string> result;
    // std::string word;
    // bool quote_on = false;
    // std::stringstream ss(input);

    // while(std::getline(ss,word,delimiter)){

    //     if(word=="\'"){
    //         quote_on = !quote_on;
    //         continue;
    //     }


    //     if(word==" " && !quote_on){
    //         continue;
    //     }

    //     result.push_back(word);
    // }
   
    // return result;



    // std::vector<std::string> result;
    // std::string word;
    // bool quote_on = false;
    // std::string previous ="";
    
    
    // for(char c : input){
        
    //     if(c=='\''){
    //         quote_on = !quote_on;
    //         continue;
    //     }
        
        
    //     if(c==' '){
    //         if(!word.empty()){
    //             result.push_back(word.c_str());
    //             word.clear();
    //             result.push_back(" ");
    //         }
    //         else if(quote_on){
    //             result.push_back(" ");
    //         }
            
    //     }
    //     else{
           
    //         word+=c;
    //     }
    // }
    
    // if(!word.empty()){
    // result.push_back(word);
    // }
    
    
    // return result;

    std::vector<std::string> result;
    std::string word;
    bool quote_on = false;
    bool double_quote_on = false;
    bool backslash = false;
    bool inner_backslash = false;

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
