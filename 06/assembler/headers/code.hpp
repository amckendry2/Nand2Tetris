#ifndef CODE_H
#define CODE_H

#include <string>
#include <map>
using namespace std;

class Code{
public:
    static int dest(string mnc);
    static int comp(string mnc);
    static int jump(string mnc);
private:
    static map<string, int> destTable;
    static map<string, int> jumpTable;
    static map<string, int> compTable;
};

#endif   
