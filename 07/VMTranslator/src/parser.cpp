#include <fstream>
#include <regex>
#include <string>
#include <sstream>
#include <iostream>

#include "parser.hpp"
using namespace std;

Parser::Parser(string filePath){
    ifstream inputStream{filePath};
    if(inputStream.is_open()){
	cout << "Successfully opened file: " << filePath << endl;
	regex lineRegex(R"(^\s*([^/]+[^/\s]))");
	string line;
	smatch matches;
	while(getline(inputStream, line)){
	    if(regex_search(line, matches, lineRegex)){
		commands.push(matches[1]);
	    }
	}
    }
};

bool Parser::hasMoreCommands(){
    return commands.size() > 0;
}

void Parser::advance(){
    current = commands.front();
    commands.pop();
    currentArgs.clear();
    istringstream iss(current);
    do {
	string sub;
	iss >> sub;
        if(sub != "")
	    currentArgs.push_back(sub);
    } while(iss);
}

CommandType Parser::commandType(){
    string command = currentArgs[0];
    if(command == "push")
	return C_PUSH;
    if(command == "pop")
	return C_POP;
    if(
	command == "add" ||
	command == "sub" ||
	command == "neg" ||
	command == "eq" ||
	command == "gt" ||
	command == "lt" ||
	command == "and" ||
	command == "or" ||
	command == "not"){

	return C_ARITHMETIC;
    }
    return C_NULL;
}

string Parser::arg1(){
    return commandType() == C_ARITHMETIC ? currentArgs[0] : currentArgs[1];
}

string Parser::arg2(){
    return currentArgs[2];
}


