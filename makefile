all: compiler generate_keywords

compiler: main.cpp
	g++ -o compiler main.cpp

generate_keywords: generate_keywords.cpp
	g++ -o generate_keywords generate_keywords.cpp