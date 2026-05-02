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

    std::string previous ="";
    
    
    for(char c : input){
        
        
        if(c=='\"'){
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
