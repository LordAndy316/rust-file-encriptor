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
p = randPrime();
q = randPrime();
n = q*p;
e = 3;
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
    long message = pow(crypt,1);

    message = message % n;
    
    return message;
}
int RSA::getPublicKey(){
    return n;
}
// long RSA::nBitRandom(int n)
// {
//     // Returns a random number
//     // between 2**(n-1)+1 and 2**n-1'''
//     long max = (long)powl(2, n) - 1;
//     long min = (long)powl(2, n - 1) + 1;
//     return min + (rand() % ( max - min + 1 ) );
// }
int main()
{
    
    RSA rr = RSA();
    cout<<"test ing"<<endl;
    //cout<<rr.nBitRandom(1000000000)<<" this is a random long"<<endl;
    int crypted = rr.encrypt(12);
    cout<<"crypt "<<crypted<<endl;
    int decrypted= rr.decrypt(crypted,rr.getPublicKey(),1);
    cout<<"decrypt "<<decrypted<<endl;
    return 0;
}


 
