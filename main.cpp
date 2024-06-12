#include <iostream>
#include <cmath>
#include <tuple>
#include <fstream>
#include <vector>
#include <sstream>
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

void write_to_file(string file_path, string message){
    ofstream FileWriter(file_path);
    if(FileWriter.is_open()){
        FileWriter << message;
        FileWriter.close();
    }
    else{
        cout<<"error file writer not open\n";
    }    
}

long long int encrypt_char(char character, int public_key, int n)
{
    long long int e = 1;
    double message = double(character);
    while(public_key--){
        e *= message;
        e %= n;
    }
    return e;
}
void encrypt_file(string file_path, int public_key, int n){
    string line = "";
    ifstream FileReader(file_path);
    vector<long long int> encrypted_chars;
    if(FileReader.is_open()){
        while (getline (FileReader, line)) {
            for (char& c : line){
                encrypted_chars.push_back(encrypt_char(int(c), public_key, n));
            }
            encrypted_chars.push_back(encrypt_char(int('\n'), public_key, n));
        }
        FileReader.close();
    }else{
        cout<<"error file reader could not open \n";
    }
    string out;
    for(long long int& i : encrypted_chars){
        out += to_string(i) + " ";
    }
    
    write_to_file("encrypted_" + file_path, out);
}

char decrypt_char(long long int encrypted, int private_key, int n)
{
    long long int d = 1;
    while(private_key--){
        d *= encrypted;
        d %= n;
    }
    return char(d);
}
void decrypt_file(string file_path,int private_key, int n){
    string line = "";
    ifstream FileReader(file_path);
    vector<int> decrypted_chars;
    if(FileReader.is_open()){
        while (getline (FileReader, line)) {
            
            istringstream iss(line);
            string c;
            while(iss >> c){
                decrypted_chars.push_back(stoi(c));

            }
        }
        FileReader.close();
    }else{
        cout<<"error file reader could not open \n";
    }
    string out;
    for (int& i : decrypted_chars){
        
        out += decrypt_char(i, private_key, n);
    }
    write_to_file("decrypted_" + file_path, out);
}


int main(int argc, char const *argv[])
{
    char message = '2';
    tuple<int,int,int> result = generateKeys();
    int e = get<1>(result);
    int d = get<2>(result);
    int n = get<0>(result);
    long long int cypher = encrypt_char(message, e, n);
    int uncrypt = decrypt_char(cypher, d, n);

    cout<<get<0>(result)<<" n "<<endl;
    cout<<get<1>(result)<<" e "<<endl;
    cout<<get<2>(result)<<" d "<<endl;
    cout<<cypher<<" encrypted text"<<endl;
    cout<<char(uncrypt)<<" should be "<<message<<endl;
    
    encrypt_file("test.txt", e, n);
    decrypt_file("encrypted_test.txt", d, n);
    return 0;
}
