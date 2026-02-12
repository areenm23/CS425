/*
 * CS425 HW1 - CRC Code
 * To Run:
 * g++ crc.cpp -o crc
 * ./crc
 */
#include<iostream>
#include<string>
#include<vector>
using namespace std;

//XOR operation
string xorOp(string a,string b){
    string res="";
    for(int i=1;i<b.length();i++){
        if(a[i]==b[i])res+="0";
        else res+="1";
    }
    return res;
}

//CRC Division
string crcDiv(string data,string div){
    int pick=div.length();
    string tmp=data.substr(0,pick);
    int n=data.length();
    while(pick<n){
        if(tmp[0]=='1')tmp=xorOp(div,tmp)+data[pick];
        else tmp=xorOp(string(div.length(),'0'),tmp)+data[pick];
        pick++;
    }
    if(tmp[0]=='1')tmp=xorOp(div,tmp);
    else tmp=xorOp(string(div.length(),'0'),tmp);
    return tmp;
}

//Encode Data
string encode(string data,string div){
    int r=div.length()-1;
    string app=data+string(r,'0');
    string rem=crcDiv(app,div);
    return data+rem;
}

//Inject Error
string makeErr(string fr,int pos){
    string c=fr;
    if(pos>=0&&pos<c.length()){
        if(c[pos]=='0')c[pos]='1';
        else c[pos]='0';
    }
    return c;
}

//Demonstration Function
void runDemo(int id,string msg,string poly,int ePos){
    cout<<"\n=== TEST CASE "<<id<<" ==="<<endl;
    cout<<"1. Message: "<<msg<<endl;
    cout<<"2. Poly: "<<poly<<endl;
    string fr=encode(msg,poly);
    cout<<"3. Tx Frame: "<<fr<<endl;
    string rx=makeErr(fr,ePos);
    cout<<"4. Rx Frame (Err at "<<ePos<<"): "<<rx<<endl;
    string rem=crcDiv(rx,poly);
    bool bad=false;
    for(int i=0;i<rem.length();i++){
        if(rem[i]=='1'){
            bad=true; 
            break;
        }
    }
    cout<<"5. Status: ";
    if(bad)cout<<"DISCARDED (Error Detected)"<<endl;
    else cout<<"ACCEPTED (No Error)"<<endl;
}

int main(){
    //Demonstration 1: Assignment Q1 Requirement
    runDemo(1,"1010101101","110101",3);
    
    //Demonstration 2: Assignment Q7 Data
    runDemo(2,"10010011011","10011",7);
    
    return 0;
}