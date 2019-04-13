/**
 * File: generate_keywords.cpp
 * Author: Wenyu
 * Version 0.1
 * Env: GCC 6.3.0 GNU Make 3.82.90
 * Function:
 *  v0.0[04/13/2019][Wenyu]: generate C language keywords and types
 *  v0.1[04/14/2019][Wenyu]: add "[", "]", "char", "=", "+="
 */

#include <iostream>
#include <fstream>

int main(){
    const int amount = 14;
    char keywords[][255] = {
        "TYPE", "int",
        "TYPE", "char",
        "TYPE", "void",
        "KEYWORD", "return",
        "KEYWORD", "main",
        "SYMBOL", "(",
        "SYMBOL", ")",
        "SYMBOL", "[",
        "SYMBOL", "]",
        "SYMBOL", "{",
        "SYMBOL", "}",
        "SYMBOL", ";",
        "SYMBOL", "=",
        "SYMBOL", "+="
    };
    std::ofstream out_keywords("keywords");
    for(int i = 0; i < amount; ++i){
        out_keywords << i << "\t" << keywords[i * 2] << "\t" << keywords[i * 2 + 1];
        if(i < amount - 1){
            out_keywords << std::endl;
        }
    }
    out_keywords.close();
    return 0;
}