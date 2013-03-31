#include<pseudo.h>
#include<cstring>
#include<list>
#include<algorithm>
#include<iostream>
/***********member functions ************************/
using namespace std;
Pseudo::Pseudo(char password[],int s):size(s){
    strcpy(pass,password);
    make();
    token=0;
}

void Pseudo::make(){
    int i;
    for(i=0;vercode[i];i++){
     pass[i]=static_cast<char>(((vercode[i])+pass[i%strlen(pass)])%26+'a');
     if(vercode[i]%3)pass[i]=static_cast<char>(((vercode[i])+pass[i%strlen(pass)])%26+'A');
        }
        pass[i]='\0';
    pass_size=strlen(pass);
    for(i=0;i<size;i++){
    List.push_back(i);
                       }
    }


int Pseudo::get_random(){
    int totake=pass[token++];
    token%=pass_size;
    totake%=List.size();
    auto p=List.begin();
    auto q=List.end();
    for(int i=1;i<totake;i++,p++);
    totake=*p;
    List.erase(p);
    return totake;
}

