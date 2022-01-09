#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include <fstream>
#include <regex>
#include <string>
#include "parser.hpp"
using namespace std;

class CodeWriter{
public:
    CodeWriter(string filePath);
    void setFileName(string filePath);
    void writeArithmetic(string command);
    void writePushPop(CommandType cType, string segment, int index);
    void close();
private:
    int nextLabel;
    ofstream fout;
    string fname;
};
    
#endif
