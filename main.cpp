#include <iostream>
#include <cmath>
#include <tuple>
using namespace std;



tuple<int, int> generatePrimes()
{
    return make_tuple(227, 229);
}

int carmicael(int p, int q)
{
    return ((p - 1) * (q - 1));
}
int gcd(int a, int b)
{
    int temp;
    while (1) {
        temp = a % b;
        if (temp == 0){
            return b;
            }
        a = b;
        b = temp;
    }
}
int findE(int cm, int p, int q){
    int e = 3;
    while(e < cm){
        if (gcd(cm, e) == 1 && e != p && e != q){
            return e;
        }
        e++;
    }
    return 0;
}
int findD(int e, int cm){
    int d = 2;
    while(1){
        if ((d*e)%cm ==1 && d != e){
            return d;
        }
        d++;
    }
    return 0;
}
tuple<int, int, int> generateKeys()
{
    tuple<int,int> primes = generatePrimes();
    int n = get<0>(primes) * get<1>(primes); 
    int cm = carmicael(get<0>(primes),get<1>(primes));
    int e = findE(cm, get<0>(primes), get<1>(primes));
    int d = findD(e, cm);
    return make_tuple(n, e, d);
}

long long int encrypt(double message, int public_key, int n)
{
    long long int e = 1;
    while(public_key--){
        e *= message;
        e %= n;
    }
    return e;
    /*unsigned long crypt = (pow(message, public_key));

    crypt = crypt % n;

    return crypt;*/
}

long long int decrypt(int encrypted, int n, int private_key)
{
    long long int d = 1;
    while(private_key--){
        d *= encrypted;
        d %= n;
    }
    return d;
    /*
    long double message = (pow(encrypted, private_key));
    message = fmod(message, n);
    return message;*/
    
}
int main(int argc, char const *argv[])
{
    int message = 10;
    tuple<int,int,int> result = generateKeys();
    int e = get<1>(result);
    int d = get<2>(result);
    int n = get<0>(result);
    int cypher = encrypt(message,e, n);
    int uncrypt = decrypt(cypher, n, d);

    cout<<get<0>(result)<<" n "<<endl;
    cout<<get<1>(result)<<" e "<<endl;
    cout<<get<2>(result)<<" d "<<endl;
    cout<<cypher<<" encrypted text"<<endl;
    cout<<uncrypt<<" should be "<<message<<endl;
    
    return 0;
}
