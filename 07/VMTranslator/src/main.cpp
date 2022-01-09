#include <iostream>
#include <filesystem>
#include "parser.hpp"
#include "codeWriter.hpp"
using namespace std;

int main(int argc, char* argv[]){
    
    if(argc < 2){
	cout << "Please provide file path as argument" << endl;
	return 0;
    }
    
    filesystem::path path{argv[1]};
    filesystem::path outputPath = path;
    string filename = path.filename();
    vector<filesystem::path> filesToTranslate;
    
    if(is_directory(path)){
        outputPath.replace_filename(filename + "/" + filename);
	for(auto& p : filesystem::recursive_directory_iterator(path)){
	    if(p.path().extension() == ".vm"){
		filesToTranslate.push_back(p.path());
	    }
	}
	
    } else {
	if(path.extension() == ".vm"){
	    filesToTranslate.push_back(path);
	}
    }
    
    outputPath.replace_extension(".asm");
    
    if(filesToTranslate.size() == 0){
	cout << path << " is not a .vm file/directory!" << endl;
	return 0;
    }
    
    CodeWriter codeWriter{outputPath};

    for(auto f : filesToTranslate){
	Parser parser{f};
	codeWriter.setFileName(f.filename());
	int lineCount = 0;
	while(parser.hasMoreCommands()){
	    parser.advance();
	    CommandType cType = parser.commandType();
	    if(cType == C_ARITHMETIC){
		codeWriter.writeArithmetic(parser.arg1());
		lineCount++;
	    }
	    if(cType == C_PUSH || cType == C_POP){
		codeWriter.writePushPop(cType, parser.arg1(), stoi(parser.arg2()));
		lineCount++;
	    }
	}

	cout << "Wrote " << lineCount << " lines to " << outputPath << endl;
	
	return 0;
    }
}
