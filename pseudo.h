#ifndef _PSEUDO_H 
#define _PSEUDO_H
#include<list>
using namespace std;
#define vercode "xfdfdksjnh"
class Pseudo{
    list<int> List;
    char pass[20];
    int size;
    int token;
    int pass_size;
    public:
    Pseudo(char [],int);
    void make();
    int get_random();
    ~Pseudo(){};
        };
#endif
