#include <fstream>
#include <regex>
#include <string>
#include <iostream>

#include "parser.hpp"
using namespace std;

Parser::Parser(string filePath){
    
    command_regex.assign("^\\s*([^\\s/]+)");
    a_regex.assign("@[\\w.?$:]+");
    c_regex.assign("^(?:[ADM]{1,3}=)?(?:[01ADM\\-+!\\|&]{1,3})(?:;[JMPEQGLTN]{3})?$");
    l_regex.assign("\\([a-zA-Z.?$:][\\w.?$:]*\\)");
    comp_regex.assign("(?:.+=)?([^;=]+)(?:;.+)?");
    jump_regex.assign(";(.{3})");
    sym_regex.assign("[@|\\(]([^\\)]+)");
    dest_regex.assign("(.+)=.+");
    
    ifstream asmFile{filePath};
	if(asmFile.is_open()){
	    cout << "Successfully opened file: " << filePath << endl;
	    string line;
	    while(getline(asmFile, line)){
		if(regex_search(line, matches, command_regex)){
		    commands.push(matches[1]);
		}
	    }
	} else {
	    cout << "Couldn't open file: " << filePath<< endl;
	}
	commandsCache = commands;
	cout << "Parsing " << commands.size() << " lines..." << endl;
}

CommandType Parser::getCommandType(){
    if(regex_search(current, a_regex))
	return A_COMMAND;
    if(regex_search(current, c_regex))
	return C_COMMAND;
    if(regex_search(current, l_regex))
	return L_COMMAND;
    return ERROR;
}

string Parser::getDest(){
    if(regex_search(current, matches, dest_regex))
	return matches[1].str() == "" ? "none" : matches[1].str();
    return "none";
}

string Parser::getSymbol(){
    if(regex_search(current, matches, sym_regex))
	return matches[1].str() == "" ? "none" : matches[1].str();
    return "none";
}

string Parser::getComp(){
    if(regex_search(current, matches, comp_regex))
	return matches[1].str() == "" ? "none" : matches[1].str();
    return "none";
}

string Parser::getJump(){
    if(regex_search(current, matches, jump_regex))
	return matches[1].str() == "" ? "none" : matches[1].str();
    return "none";
}

bool Parser::hasMoreCommands(){
    return commands.size() > 0;
}

void Parser::advance(){
    current = commands.front();
    commands.pop();
}

void Parser::reset(){
    commands = commandsCache;
}

