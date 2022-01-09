#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <regex>
#include <queue>
#include <string>
using namespace std;

enum CommandType {A_COMMAND, C_COMMAND, L_COMMAND, ERROR};

class Parser{
public:
    Parser(string filePath);
    CommandType getCommandType();
    string getDest();
    string getSymbol();
    string getComp();
    string getJump();
    bool hasMoreCommands();
    void advance();
    void reset();
private:
    smatch matches;
    regex command_regex;
    regex a_regex;
    regex c_regex;
    regex l_regex;
    regex comp_regex;
    regex jump_regex;
    regex sym_regex;
    regex dest_regex;
    string current;
    queue<string> commands;
    queue<string> commandsCache;
};

#endif    
