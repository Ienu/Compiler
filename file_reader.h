/**
 * File: file_reader.h
 * Env: GCC 8.2.0 GNU Make 3.82.90
 * Function:
 *  v0.0[10/06/2019][Wenyu]: read .c file into lines
 */
#ifndef FILE_READER_H
#define FILE_READER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void _disp_split(string title = ""){
    int i, num = 80 - title.size() - 2;
    for(i = 0; i < num / 2; ++i){
        cout << "=";
    }
    if(title != ""){
        cout << " " << title << " ";
    }
    else{
        cout << "==";
    }
    for(i = 0; i < num / 2; ++i){
        cout << "=";
    }
    cout << endl;
}

char* arg_reader(int argc, char* argv[]){
    _disp_split("read arguments");

    cout << "argc = " << argc << endl;
    int i, j;
    for(i = 0; i < argc; ++i){
        cout << "argv[" << i << "] = " << argv[i] << endl;
    }

    _disp_split("read source file");

    if(argc > 0){
        cout << "File name = " << argv[1] << endl;
    }
    else{
        return NULL;
    }
    return argv[1];
}

vector<string> file_reader(char* file_name){
    vector<string> lines_src;
    ifstream source_stream(file_name);

    _disp_split("read lines");

    int line_idx = 0;
    while(!source_stream.eof()){
        char str_line[256];
        source_stream.getline(str_line, 255, '\n');

		// read each line
        cout << "Line: " << line_idx++ << ": " << str_line << endl;

		// put lines into vector<string>
        lines_src.push_back(string(str_line));
    }
    return lines_src;
}

#endif