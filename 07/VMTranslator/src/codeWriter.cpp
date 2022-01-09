#include <fstream>
#include <string>
#include <iostream>
#include "codeWriter.hpp"
using namespace std;

CodeWriter::CodeWriter(string filePath) :
    fout{filePath},
    nextLabel{0}
{}

void CodeWriter::setFileName(string fileName){
    fname = fileName;
}

void CodeWriter::writeArithmetic(string command){   
    auto write = [this](auto... args){((fout << args << endl), ...);};
    
    if(command == "add" || command == "sub" || command == "and" || command == "or"){
	
	write(
	    "@SP",
	    "M=M-1",
	    "A=M",
	    "D=M",
	    "M=0",
	    "A=A-1");
	
	if(command == "add")
	    write("M=M+D");
	
	if(command == "sub")
	    write("M=M-D");
	
	if(command == "and")
	    write("M=M&D");
	
	if(command == "or")
	    write("M=M|D");
    }
   
    if(command == "neg" || command == "not"){
	
	write(
	    "@SP",
	    "A=M-1");
	
	if(command == "neg")
	    write("M=-M");
	
	if(command == "not")
	    write("M=!M");
    }
    
    if(command == "eq" || command == "gt" || command == "lt"){

	string label = to_string(nextLabel++);
	
	write(
	    "@SP",
	    "M=M-1",
	    "A=M",
	    "D=M",
	    "M=0",
	    "A=A-1",
	    "D=M-D",
	    "M=-1",
	    "@COND"+label);
	
	if(command == "eq")
	    write("D;JEQ");
	
	if(command == "gt")
	    write("D;JGT");
	
	if(command == "lt")
	    write("D;JLT");
	
	write(
	    "@SP",
	    "A=M-1",
	    "M=0",
	    "(COND"+label+")");
    }
}

void CodeWriter::writePushPop(CommandType cType, string segment, int index){
    auto write = [this](auto... args){((fout << args << endl), ...);};
    auto writeLoadAddress = [this, write, segment, index]() {
				
				if(segment == "pointer"){
				    write(index == 0 ? "@THIS" : "@THAT");
				    
				} else if(segment == "temp") {
				    write(
				        "@R5",
					"D=A",
					"@"+to_string(index),
					"A=D+A");
				    
				} else if(segment == "static") {
				    write("@" + fname + "." + to_string(index));
				    
				} else {
				    
				    string segstr = "";
				    
				    if(segment == "local")
					segstr = "LCL";
				    
				    if(segment == "argument")
					segstr = "ARG";
				    
				    if(segment == "this")
					segstr = "THIS";
				    
				    if(segment == "that")
					segstr = "THAT";
				    
				    write(
					"@"+segstr,
					"D=M",
					"@"+to_string(index),
					"A=D+A");
				} 
			    };
 
    if(cType == C_POP){
	
	writeLoadAddress();
	
	write(
	    "D=A",
	    "@SP",
	    "A=M",
	    "M=D",
	    "A=A-1",
	    "D=M",
	    "M=0",
	    "@SP",
	    "A=M",
	    "A=M",
	    "M=D",
	    "@SP",
	    "M=M-1",
	    "A=M+1",
	    "M=0");
    }
    
    if(cType == C_PUSH){
	
	if(segment == "constant"){
	    write(
		"@"+to_string(index),
		"D=A");
	    
	} else {	    
	    writeLoadAddress();
	    write("D=M");
	}
	
	write(
	    "@SP",
	    "A=M",
	    "M=D",
	    "@SP",
	    "M=M+1");
    }
}
