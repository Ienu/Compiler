/**
 * File: main.cpp
 * Author: Wenyu
 * Version 0.3
 * Env: GCC 6.3.0 GNU Make 3.82.90
 * Function:
 *  v0.0[04/12/2019][Wenyu]: init and test read .c file
 *  v0.1[04/13/2019][Wenyu]: read .c file by line and split into tokens
 *  v0.2[04/14/2019][Wenyu]: correct errors of split symbols
 *  v0.3[04/14/2019][Wenyu]: use function and scan line to split words
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool _is_letter(char c){
    return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool _is_digit(char c){
    return (c >= '0' && c <= '9');
}

bool _is_operator(char c){
    char ops[] = "+-*/%!<>=&|~^";
    for(size_t i = 0; i < 13; ++i){
        if(ops[i] == c){
            return true;
        }
    }
    return false;
}

bool _is_bound(char c){
    char ops[] = "()[]{};,";
    for(size_t i = 0; i < 8; ++i){
        if(ops[i] == c){
            return true;
        }
    }
    return false;
}

bool _is_separator(char c){
    char ops[] = " \t\n";
    for(size_t i = 0; i < 3; ++i){
        if(ops[i] == c){
            return true;
        }
    }
    return false;
}

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
    std::vector<Token> _symbols;

    std::ifstream source_keywords("keywords");
    while(!source_keywords.eof()){
        int idx;
        std::string str_type, str_word;
        source_keywords >> idx >> str_type >> str_word;
        _symbols.push_back({idx, str_type, str_word});
        std::cout << idx << ": " << str_type << " --> " << str_word << std::endl;
    }
    source_keywords.close();
    std::cout << "================================ split tokens =================================" << std::endl;
    std::vector<Token> token;
    for(i = 0; i < src_line.size(); ++i){
        // read one line
        string line = src_line[i];
        std::cout << "# Line str: " << line << std::endl;

        char str[255] = "";
        int c_idx = 0;
        for(j = 0; j < line.size(); ++j){
            if(true == _is_separator(line[j])){
                //std::cout << "[sep]" << std::ends;
                continue;
            }
            if(true == _is_bound(line[j])){
                token.push_back({0, "BOUND", string(1, line[j])});
                std::cout << "[bound]" << std::ends;
                continue;
            }
            if(true == _is_operator(line[j])){
                if(j + 1 < line.size()){
                    if(line[j + 1] == '='){
                        char cop[3] = "@=";
                        cop[0] = line[j];
                        token.push_back({0, "OPERATOR", string(cop)});
                        std::cout << "[D-op]" << std::ends;
                        j++;
                        continue;
                    }
                    if(line[j] == '+' && line[j + 1] == '+'){
                        token.push_back({0, "OPERATOR", "++"});
                        std::cout << "[D-op]" << std::ends;
                        j++;
                        continue;
                    }
                    if(line[j] == '-' && line[j + 1] == '-'){
                        token.push_back({0, "OPERATOR", "--"});
                        std::cout << "[D-op]" << std::ends;
                        j++;
                        continue;
                    }
                }
                token.push_back({0, "OPERATOR", string(1, line[j])});
                std::cout << "[op]" << std::ends;
                continue;
            }
            if(true == _is_letter(line[j]) || line[j] == '_'){
                if(j + 1 < line.size()){
                    int k = j + 1;
                    while(k < line.size()){
                        if(_is_letter(line[k]) || line[k] == '_' || _is_digit(line[k])){
                            k++;
                        }
                        else{
                            break;
                        }
                    }
                    char c_id[255] = "";
                    int l;
                    for(l = 0; l < k - j; ++l){
                        c_id[l] = line[j + l];
                    }
                    c_id[l] = '\0';
                    token.push_back({0, "IDENTIFIER", c_id});
                    std::cout << "[id]" << std::ends;
                    j = k - 1;
                    continue;
                }                
            }
            if(true == _is_digit(line[j])){
                int k = j + 1;
                bool b_dot = false;
                while(k < line.size()){
                    if(_is_digit(line[k])){
                        k++;
                    }
                    else if(!b_dot && line[k] == '.'){
                        k++;
                        b_dot = true;
                    }
                    else{
                        break;
                    }
                }
                char c_number[255] = "";
                int l;
                for(l = 0; l < k - j; ++l){
                    c_number[l] = line[j + l];
                }
                c_number[l] = '\0';
                token.push_back({0, "CONSTANT", c_number});
                std::cout << "[number]" << std::ends;
                j = k - 1;
                continue;
            }
            if(line[j] == '\"'){
                int k = j + 1;
                while(k < line.size()){
                    if(line[k] == '\"' && line[k - 1] != '\\'){
                        break;
                    }
                    k++;
                }
                // suppose to be found
                char c_str[255] = "";
                int l;
                for(l = 0; l < k - j - 1; ++l){
                    c_str[l] = line[j + l + 1];
                }
                c_str[l] = '\0';
                token.push_back({0, "CONSTANT", c_str});
                std::cout << "[string]" << std::ends;
                j = k;
                continue;
            }
            if(line[j] == '\''){
                // suppose correct grammer
                token.push_back({0, "CONSTANT", string(1, line[j + 1])});
                std::cout << "[char]" << std::ends;
                j += 2;
                continue;
            }
        }
        std::cout << std::endl << std::endl;
    }
    
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    for(i = 0; i < token.size(); ++i){
        std::cout << "[ " << token[i].TYPE << ", " << token[i].VALUE << " ]" << std::endl;
    }
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    source_stream.close();
    return 0;
}