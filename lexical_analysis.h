/**
 * File: lexical_analysis.h
 * Env: GCC 8.2.0 GNU Make 3.82.90
 * Function:
 *  v0.0[10/06/2019][Wenyu]: split lines into tokens
 */
#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "file_reader.h"

typedef struct{
    string TYPE;
    string VALUE;
}Token;

bool _is_separator(char c){
    return c == ' ' || c == '\t' || c == '\n';
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

bool _is_operator(char c){
    char ops[] = "+-*/%!<>=&|~^";
    for(size_t i = 0; i < 13; ++i){
        if(ops[i] == c){
            return true;
        }
    }
    return false;
}

bool _is_bin_operator(char c1, char c2){
    // operator @=
    if(c2 == '='){
        return true;
    }
    // operator ++ -- << >> && ||
    if(c1 == c2){
        char b_ops[] = "+-<>&|";
        for(size_t i = 0; i < 6; ++i){
            if(b_ops[i] == c2){
                return true;
            }
        }
    }
    return false;
}

bool _is_letter(char c){
    return c == '_' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

bool _is_digit(char c){
    return c >= '0' && c <= '9';
}

bool _is_keyword(string str){
    string keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", 
        "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", 
        "long", "register", "return", "short", "signed", "sizeof", "static", "struct", 
        "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
    };
    for(int i = 0; i < 32; ++i){
        if(str == keywords[i]){
            return true;
        }
    }
    return false;
}

vector<Token> token_spliter(vector<string> lines_src){
    _disp_split("split tokens");
    // record all the tokens
    vector<Token> token;
    for(int i = 0; i < lines_src.size(); ++i){
        // read one line
        string line = lines_src[i];
        char str[255] = "";
        int j, c_idx = 0;
        for(j = 0; j < line.size(); ++j){
            if(_is_separator(line[j])){
                continue;
            }
            if(_is_bound(line[j])){
                token.push_back({"BOUND", string(1, line[j])});
                continue;
            }
            if(_is_operator(line[j])){
                // judge bin operator
                if(j + 1 < line.size()){
                    if(_is_bin_operator(line[j], line[j + 1])){
                        string b_op = "@@";
                        b_op[0] = line[j];
                        b_op[1] = line[j + 1];
                        token.push_back({"OPERATOR", b_op});
                        j++;
                        continue;
                    }
                }
                token.push_back({"OPERATOR", string(1, line[j])});
                continue;
            }
            if(_is_letter(line[j])){
                int k = j + 1;
                while(k < line.size()){
                    if(_is_letter(line[k]) || _is_digit(line[k])){
                        k++;
                    }
                    else{
                        break;
                    }
                }
                char c_id[255] = "";
                size_t l;
                for(l = 0; l < k - j; ++l){
                    c_id[l] = line[j + l];
                }
                c_id[l] = '\0';
                if(_is_keyword(c_id)){
                    token.push_back({"KEYWORD", c_id});
                }
                else{
                    token.push_back({"IDENTIFIER", c_id});
                }
                j = k - 1;
                continue;              
            }
            if(_is_digit(line[j])){
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
                token.push_back({"CONSTANT", c_number});
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
                token.push_back({"CONSTANT", c_str});
                j = k;
                continue;
            }
            if(line[j] == '\''){
                // suppose correct grammer
                token.push_back({"CONSTANT", string(1, line[j + 1])});
                j += 2;
                continue;
            }
        }
    }
    for(size_t i = 0; i < token.size(); ++i){
        cout << token[i].TYPE << ", \t" << token[i].VALUE << endl;
    }
    return token;
}

#endif