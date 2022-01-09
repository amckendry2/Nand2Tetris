#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>
using namespace std;

class SymbolTable{
public:
    SymbolTable();
    bool contains(string symbol);
    void addEntry(string symbol);
    void addEntry(string symbol, int address);
    int getAddress(string symbol);
private:
    int currentAddress;
    unordered_map<string, int> table;
};

#endif
