/* 
 * File:   main.cpp
 * Author(s): Josh McIntyre 862054277
 *            Cody Steimle 862137374
 * Created on February 3, 2020, 6:06 PM
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

bool isPrime( int );
int* getPQ( int );
int findGCD( int , int );

// Main Program
int main(int argc, char** argv) {
    
    int e, n, phiN, d;
    int* pq;
    bool isEnc;
    string choice;
    string fileN;
    
    e = atoi(argv[1]);
    n = atoi(argv[2]);
    choice = argv[3];
    fileN = argv[4];
    
    (choice == "e") ? isEnc = true : isEnc = false;
    
    pq = getPQ(n);
    cout<<"p is "<<pq[0]<<endl;
    cout<<"q is "<<pq[1]<<endl;
    cout<<pq[0]<<" is "<<(isPrime(pq[0])==1?"prime":"nonprime")<<endl;
    cout<<pq[1]<<" is "<<(isPrime(pq[1])==1?"prime":"nonprime")<<endl;
    
    phiN = ((pq[0]-1) * (pq[1]-1));
    cout<<"phiN is "<<phiN<<endl;
    
    // Attempt to find d (bruteforce integer guessing), WILL NOT WORK IF d > MAX_D
    int MAX_D = 10000000;
    for(int i = 1; i < MAX_D; i++) {
        
        int tmp = (i*e);
        
        if(tmp > phiN) tmp %= phiN;
        
        if(tmp == 1) {
            d = i;
            i = 10000000;
        }
        
    }
    
    cout<<"d is "<<d<<endl;
    
    // Decryption
    if(!isEnc) {
        // Read from input file
        ifstream file(fileN);
        vector<int> array;
        int number;
        while(file >> number) {
            array.push_back(number);
        }
    
        string output = "";
        for(int i = 0; i < array.size(); i++) {
            long int tmp = d;
            long int tmp2 = array[i];
            long int product = 1;

            // Exponentiation by squaring algorithm
            while(tmp > 0) {
                if(tmp%2 == 1) {
                    product = ((product * tmp2) % n);
                }
                tmp /= 2;

                tmp2 = pow(tmp2, 2);
                tmp2 %= n;
            }

            /* Compute final modular calculation
            long int tmp3 = pow(tmp2, tmp);

            char M;
            tmp2 = ((tmp3 * product) % n);*/
            char M;
            if(product == 28) M = ' ';             // Handles SPACE encoding to ASCII conversion
            else M = product + '?';                // Handles all other character encoding to ASCII conversion
            output+=M;                          // Builds upon decoded message string
        }

        ofstream out;
        out.open("decrypted.txt");
        out<<output;
        out.close();
    }
    
    // Encryption
    else {
        vector<int> cipher;
        
        ifstream file;
        file.open(fileN);
        string text;
        getline(file, text);
        file.close();
        
        for(int i = 0; i < text.size(); i++) {
            
            // Encode characters (A=2, B=3, ..., Z=27, SPACE=28)
            if(text[i] == ' ') text[i] = 28;
            else text[i] -= '?';
            
            long int tmp = e;
            long int tmp2 = text[i];
            long int product = 1;
            
            // Exponentiation by squaring algorithm
            while(tmp > 0) {
                if(tmp%2 == 1) {
                    product = ((product * tmp2) % n);
                }
                tmp /= 2;

                tmp2 = pow(tmp2, 2);
                tmp2 %= n;
            }
            
            /* Compute final modular calculation
            long int tmp3 = pow(tmp2, tmp);
            
            tmp2 = (tmp3 % n);*/
            
            //unsigned long long int tmp = pow(static_cast<int>(chars[i]), e);
            cipher.push_back(product);
        }
        
        ofstream out;
        out.open("incrypted.txt");
        for(int i = 0; i < cipher.size(); i++) {
            out<<cipher[i]<<' ';
        }
        out.close();
    }
    
    delete [] pq;

    return 0;
}

// Utility function for primality testing
bool isPrime(int num) {
    
    for(int i = 1; i <= sqrt(num); i++) {
        for(int j = 1; j <=  num; j++) {
            int product = i * j;
            if(i != 1 && j != 1 && product == num) return false;
        }
    }
    
    return true;
}

// Utility function for finding prime numbers p and q such that n = pq
int* getPQ(int num) {
    int* pq = new int[2];
    
    int i , j;
    
    for(i = 1; i <= sqrt(num); i++) {
        for(j = 1; j <=  num; j++) {
            int product = i * j;
            if(i > 1 && j > 1 && (product == num) && isPrime(i) && isPrime(j)) {
                
                if(i != j) {
                    pq[0] = i;
                    pq[1] = j;
                }
                
                return pq;
            }
        }
    }
    
    return pq;
}

// Utility function for finding GCD of 2 numbers (Euclidean Algorithm)
int findGCD(int n1, int n2) {
    if(n1 == n2) return n1;
    if(n1 < n2) {
        int tmp = n1;
        n1 = n2;
        n2 = tmp;
    }
    return findGCD(n1 - n2, n2);
}

