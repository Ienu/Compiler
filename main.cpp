/**
 * File: main.cpp
 * Env: GCC 8.2.0 GNU Make 3.82.90
 * Function:
 *  v0.5[10/06/2019][Wenyu]: add function judge and split functions into headers
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "file_reader.h"
#include "lexical_analysis.h"

//#define WORDS_ANALYSIS

using namespace std;

typedef struct {
	int idx;
	std::vector<Token> TOKENS;
}Block;

void _show_block(Block b) {
	std::cout << "----BLOCK\t";
	for (int i = 0; i < b.TOKENS.size(); ++i) {
		std::cout << b.TOKENS[i].VALUE << " ";
	}
	std::cout << std::endl;
}

typedef struct {
	int idx;
	std::vector<Token> TOKENS;
}Sentence;

void _show_sentence(Sentence s) {
	std::cout << "--------SENTENCE\t";
	for (int i = 0; i < s.TOKENS.size(); ++i) {
		std::cout << s.TOKENS[i].VALUE << " ";
	}
	std::cout << std::endl;
}

typedef struct{
	string TYPE;
	string NAME;
	string VALUE;
}variable;

void _show_var(variable v){
	cout << v.TYPE << " " << v.NAME << " = " << v.VALUE << endl;
}

typedef struct{
	vector<Token> tokens;
}expression;

void _show_exp(expression e){
	for(size_t i = 0; i < e.tokens.size(); ++i) {
		cout << e.tokens[i].VALUE << " ";
	}
	cout << endl;
}

typedef struct{
	string type;
	string name;
	vector<variable> params;
	vector<expression> expressions; 
}function;

void _show_func(function f){
	cout << "function: " << f.type << " " << f.name << " (";
	for(size_t i = 0; i < f.params.size(); ++i){
		_show_var(f.params[i]);
	}
	cout << ") {";
	for(size_t i = 0; i < f.expressions.size(); ++i){
		_show_exp(f.expressions[i]);
	}
	cout << "}" << endl;
}


int main(int argc, char* argv[]){

    char* file_name = arg_reader(argc, argv);
    vector<string> lines_src = file_reader(file_name);
    vector<Token> tokens = token_spliter(lines_src);

	_disp_split("grammer analysis");

	vector<function> functions;

	// find functions KEYWORDS(TYPE)+ID+(KEYWORDS(TYPE)+ID, ...){SENTENCE, ...}
	string key_type[] = {"void", "int", "float", "double", "long", "short", "bool", "char"};
	size_t i;
	for(i = 0; i < tokens.size(); ++i){
		function func;
		if(tokens[i].TYPE == "KEYWORD"){
			bool b_key_type = false;
			for(size_t j = 0; j < 8; ++j){
				if(tokens[i].VALUE == key_type[j]){
					b_key_type = true;
					func.type = tokens[i].VALUE;
					i++;
					break;
				}
			}
			if(b_key_type){
				if(i < tokens.size()){
					if(tokens[i].TYPE == "IDENTIFIER"){
						func.name = tokens[i].VALUE;
						i++;
						if(i < tokens.size()){
							if(tokens[i].VALUE == "("){
								i++;
								while(i < tokens.size()){
									// TODO: judge params
									// func.params
									//
									if(tokens[i].VALUE == ")"){
										break;
									}
									i++;
								}
								i++;
								if(tokens[i].VALUE == "{"){
									i++;
									while(i < tokens.size()){
										// TODO: judge sentences
										// func.sentences
										//
										if(tokens[i].VALUE == "}"){
											functions.push_back(func);
											break;
										}
										i++;
									}
								}
							}
						}
					}			
				}
			}
		}
	}
	for(size_t i = 0; i < functions.size(); ++i){
		_show_func(functions[i]);
	}


    /* 
	std::vector<Block> block;
	for (i = 0; i < token.size(); ++i) {
		// find block
		Block b;
		if (token[i].TYPE == "BOUND" && token[i].VALUE == "{") {
			i++;
			while (token[i].TYPE != "BOUND" || token[i].VALUE != "}") {
				b.TOKENS.push_back(token[i]);
				i++;
			}
			i--;
		}
		if (b.TOKENS.size() > 0) {
			block.push_back(b);
		}
	}
	for (i = 0; i < block.size(); ++i) {
		_show_block(block[i]);
		for (j = 0; j < block[i].TOKENS.size(); ++j) {
			Sentence s;
			while (block[i].TOKENS[j].VALUE != ";" && j < block[i].TOKENS.size()) {
				s.TOKENS.push_back(block[i].TOKENS[j]);
				j++;
			}
			_show_sentence(s);
		}
	}
    source_stream.close();*/
	_disp_split();
    return 0;
}