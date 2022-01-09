#include "symbolTable.hpp"
#include "parser.hpp"
#include "code.hpp"

#include <fstream>
#include <filesystem>
#include <regex>
#include <bitset>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){

    if(argc < 2){
	cout << "Please provide file path as argument" << endl;
	return 0;
    }
    
    SymbolTable sTable;
    Parser parser(argv[1]);
    filesystem::path path = argv[1];
    string foutPath = path.replace_extension(".hack");
    ofstream fout{foutPath};
    regex isNumber("^[0-9]+$");
    int romAddress = 0;

    while (parser.hasMoreCommands()){	
	parser.advance();
	if(parser.getCommandType() == L_COMMAND){
	    string sym = parser.getSymbol();
	    if(!sTable.contains(sym)){
		sTable.addEntry(sym, romAddress);
	    }
	} else romAddress++;
    }
    
    parser.reset();

    int output_lines = 0;
    
    while (parser.hasMoreCommands()){
	parser.advance();
	CommandType ct = parser.getCommandType();
	int res = 0b0;
	    
	if(ct == A_COMMAND){
	    string sym = parser.getSymbol();
	    if(regex_search(sym, isNumber)){
		res = stoi(sym);
	    } else {
		if(!sTable.contains(sym))
		    sTable.addEntry(sym);
		res |= sTable.getAddress(sym);
	    }
	    output_lines++;
	    fout << bitset<16>(res) << endl;
	}
	if(ct == C_COMMAND){
	    res = (0b111 << 13);
	    res |= Code::comp(parser.getComp());
	    res |= Code::dest(parser.getDest());
	    res |= Code::jump(parser.getJump());
	    output_lines++;
	    fout << bitset<16>(res) << endl;
	}
    }
    cout << "Wrote " << output_lines << " lines to " << foutPath << endl;
    return 0;
}
