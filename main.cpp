/**
 * File: main.cpp
 * Author: Wenyu
 * Version 0.0
 * Env: 
 * Function:
 *  v0.0[04/12/2019][Wenyu]: init and test read .c file
 */

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    std::cout << "================================================================" << std::endl;
    std::cout << "argc = " << argc << endl;
    int i, j;
    for(i = 0; i < argc; ++i){
        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
    }
    std::cout << "----------------------------------------------------------------" << std::endl;
    if(argc > 0){
        std::cout << "File name = " << argv[1] << std::endl;
    }
    return 0;
}