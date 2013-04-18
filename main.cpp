#include<bmp.h>
#include<pseudo.cpp>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<cstdio>
#include<unistd.h>
#include<cstring>
#include<cmath>
#include<exception>

using namespace std;
#define set(a,b) (a+=static_cast<byte>(0x01<<((b))))
#define isset(a,b) (static_cast<bool>(a&(0x01<<((b)))))
#define bit_count(a) (((a>>7)+(a>>6)+(a>>5)+(a>>4)+(a>>3)+(a>>2)+(a>>1)+(a>>0)))
/**************************************************************************************

                   FUNCTION TO READ BMP IMAGE

**************************************************************************************/
void read_bmp(byte *fline,const size_t msg_len,const char bmp[]){
	ifstream fin(bmp,ios::in|ios::binary);	
	if(!fin){
		char error[32];
		sprintf(error,"Unable to open file %s :",bmp);
		perror(error);
		exit(0);
		}
	size_t fbeg,flen;
	fin.seekg(0,ios::beg);
	size_t block_size;
	char pass[10];
	int rnd;
/*****compute the file size******************************************/	
	fbeg=fin.tellg();
	fin.seekg(0,ios::end);
	flen=fin.tellg();
	flen=flen-fbeg;
	block_size=flen/(msg_len*8);
/*********read password nd create the object Pseudo::p**********/
	cout<<"\nEnter the password   :";
	cin>>pass;
	Pseudo p(pass,msg_len*8);
	cout<<"\nPassword="<<pass<<"\n";
	cout<<"message length ="<<msg_len<<"\n";
	byte ch;
	for(int i=0;i<msg_len;i++){
		fline[i]=0x00;
		for(int j=0;j<8;j++){
			rnd=p.get_random();
			fin.seekg(block_size*(rnd+1/2),ios::beg);
			ch=fin.get();
			if((bit_count(ch)%2) ^ (rnd%2)){
			//	cout<<'1';/**for debugging only'**/
				set(fline[i],j);
					}
			else
			;//	cout<<'0';/**********debuggin*****/
			}
		cout<"\t";

	}
	fin.close();
	
}
/********************************************************************************

                    MAKE STEGO IMAGE [HERE KEYMAP]

********************************************************************************/

void makesteg(const char *msg,const char* infile,const char* outfile) throw(){
/*******allocating memory for message and encoded string***********************/
	size_t msg_len=strlen(msg);	
	byte *fline=new byte[msg_len];
	byte data;
	read_bmp(fline,msg_len,infile);
/***************Encoding the data ************/
	ofstream fout(outfile,ios::out|ios::binary);
	if(fout){}
	else{	perror("File write failed");
		exit(0);
		}

	for(int i=0;i<=msg_len;i++){
		data=msg[i]^fline[i];
		fout.write((char*)&data,sizeof(char));
				   }
	fout.close();/***out stream closed***/
	delete[] fline;
		}

/*********************************************************************
	  
	         FUNCTION TO EXTRACT THE MESSAGE FROM IMAGE

**********************************************************************/
void extract(const char *img,const char *key,size_t msg_len){
	byte *fline=new byte[msg_len];
	byte *data=new byte[msg_len];
	read_bmp(fline,msg_len,img);
	/**************************************************************
		---------DECODING SECTION-----
	**************************************************************/
	ifstream fin(key,ios::in|ios::binary);
	for(int i=0;i<=msg_len;i++){
		data[i]=0x00;
		fin.read((char*)&data[i],sizeof(char));
		}
	fin.close();
	/*****Decoding the data*****************************************/
	cout<<"\nDecoded Message is  ";
	for(int i=0;i<msg_len;i++){
		fline[i]=fline[i]^data[i];
		cout<<fline[i];	/***printing character wise***/
		}
	delete[] fline;
	delete[] data;

}

/***    MAIN FUNCTION   ********/
int main(int argv,char* argc[]){
	char msg[256],bmp[32];
	short choice;
	size_t msg_len;
	try{
	/******asking for choice*******************/
	if(argv ==2){
		strcpy(bmp,argc[1]);
	}
	else{
		cout<<"\nFILE NAME :";
		cin>>bmp;
	}
	cout<<"\nEnter your choice";
		cout<<"\n1.Encode";
		cout<<"\n2.Decode\n\n";
	cin>>choice;
	if(choice == 1){
		cout<<"STRING :";
		cin.ignore();
		cin.getline(msg,256);
		if(!strlen((msg)))strcpy(msg,"i dont suffer from insanity");
		makesteg(msg,bmp,"out.dat");
		  }
	else{
		cout<<"\nSTRING SIZE :";
		cin>>msg_len;
		extract(bmp,"out.dat",msg_len);
	    }
	}
	catch(exception &e){
		cout<<"\nException :"<<e.what();
		exit(0);
	}

	return 0;
}
