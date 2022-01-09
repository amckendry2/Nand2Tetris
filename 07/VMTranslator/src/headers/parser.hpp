#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <regex>
#include <queue>
#include <string>
using namespace std;

enum CommandType { C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL, C_NULL };

class Parser{
public:
    Parser(string filePath);
    bool hasMoreCommands();
    void advance();
    CommandType commandType();
    string arg1();
    string arg2();    
private:
    queue<string> commands;
    string current;
    vector<string> currentArgs;
};

#endif
