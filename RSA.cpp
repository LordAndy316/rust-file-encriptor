#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

class RSA
{
private:
    /* data */
    int p,q,n,d,e;
    bool isPrime(int);
    int randPrime();
    int makeE(int, int);
    
    
public:
    RSA(/* args */);
    ~RSA();
    int encrypt(int);
    int decrypt(int,int,int);
    int getPublicKey();
    int carmicael(int,int);
    //long nBitRandom(int);
};

RSA::RSA(/* args */)
{
// p = randPrime();
// q = randPrime();
p = 2;
q=7;
n = p*q;
e = makeE(p,q);
d= 11;
cout<<q<<"  "<<p;

}

RSA::~RSA()
{
}
int RSA::randPrime(){
    while(true) {
        int r = rand();
        if(isPrime(r)) return r;
    }
}
bool RSA::isPrime(int number ){
    for (int a = 2; a < number; a++) {
        if (number % a == 0) {
            return false;
        }
    }
    return true;
}
int RSA::carmicael(int p, int q){
        return ((p-1)*(q-1));
}
int RSA::encrypt(int message){
    long crypt = (pow(message,e));
    cout<<crypt<<endl;
    crypt = crypt % n ;
    
    return crypt;
}
int RSA::decrypt(int crypt,int public_key,int Private_key){
    double message = (pow(10,11));
    message = fmod(message,n);
    return message;
}




int RSA::getPublicKey(){
    return n;
}










int decrypt(int crypt,int public_key,int Private_key){
    double message = (pow(10,11));
    message = fmod(message,public_key);
    return message;
}

int main()
{
    
    RSA rr = RSA();
    cout<<"test ing"<<endl;
    //cout<<rr.nBitRandom(1000000000)<<" this is a random long"<<endl;
    int crypted = rr.encrypt(12);
    cout<<"crypt "<<crypted<<endl;
    int decrypted= rr.decrypt(crypted,rr.getPublicKey(),11);
    cout<<"decrypt "<<decrypted<<endl;
    return 0;
}


 
