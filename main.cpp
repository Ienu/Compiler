/**
 * File: main.cpp
 * Author: Wenyu
 * Version 0.2
 * Env: GCC 6.3.0 GNU Make 3.82.90
 * Function:
 *  v0.0[04/12/2019][Wenyu]: init and test read .c file
 *  v0.1[04/13/2019][Wenyu]: read .c file by line and split into tokens
 *  v0.2[04/14/2019][Wenyu]: correct errors of split symbols
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef struct{
    int idx;
    std::string TYPE;
    std::string VALUE;
}Token;

int main(int argc, char* argv[]){
    std::cout << "################################### Compiler ##################################" << std::endl;
    std::cout << "================================ read arguments ===============================" << std::endl;
    std::cout << "argc = " << argc << endl;
    int i, j;
    for(i = 0; i < argc; ++i){
        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
    }
    std::cout << "=============================== read source file ==============================" << std::endl;
    if(argc > 0){
        std::cout << "File name = " << argv[1] << std::endl;
    }
    else{
        return 0;
    }
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    std::ifstream source_stream(argv[1]);

    int line_idx = 0;
    std::vector<string> src_line;
    while(!source_stream.eof()){
        char str_line[256];
        source_stream.getline(str_line, 255, '\n');
        std::cout << "Line: " << line_idx << ": " << str_line << std::endl;

        std::string str(str_line);
        src_line.push_back(str);
        line_idx++;
    }
    std::cout << "================================ read keywords ================================" << std::endl;
    std::vector<Token> _keywords;
    std::vector<Token> _types;
    std::vector<Token> _symbols;

    std::ifstream source_keywords("keywords");
    while(!source_keywords.eof()){
        int idx;
        std::string str_type, str_word;
        source_keywords >> idx >> str_type >> str_word;
        if(str_type == "TYPE"){
            _types.push_back({idx, str_type, str_word});
        }
        else if(str_type == "KEYWROD"){
            _keywords.push_back({idx, str_type, str_word});
        }
        else if(str_type == "SYMBOL"){
            _symbols.push_back({idx, str_type, str_word});
        }
        std::cout << idx << ": " << str_type << " --> " << str_word << std::endl;
    }
    source_keywords.close();
    std::cout << "================================ split tokens =================================" << std::endl;
    std::vector<Token> token;
    for(i = 0; i < src_line.size(); ++i){
        string line = src_line[i];
        std::cout << "# Line str: " << line << std::endl;
        for(j = 0; j < line.size(); ++j){
            for(int k = 0; k < _symbols.size(); ++k){
                int n_match = 0;
                for(int l = 0; l < _symbols[k].VALUE.size(); ++l){
                    if(line[j + l] == _symbols[k].VALUE[l]){
                        n_match++;
                    }
                }
                if(n_match == _symbols[k].VALUE.size()){
                    if(j == 0){
                        token.push_back({0, _symbols[k].VALUE, _symbols[k].VALUE});
                        line = line.substr(n_match);
                    }
                    else{
                        string head = line.substr(0, j);
                        token.push_back({0, head, head});
                        token.push_back({0, _symbols[k].VALUE, _symbols[k].VALUE});
                        line = line.substr(j + n_match);
                    }
                    j = 0;
                    std::cout << "\tsub_str: " << line << std::endl;
                }
            }
        }
        if(line.size() > 0){
            token.push_back({0, line, line});
        }
    }
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    for(i = 0; i < token.size(); ++i){
        std::cout << token[i].VALUE << std::endl;
    }
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    source_stream.close();
    return 0;
}