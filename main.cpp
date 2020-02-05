/* 
 * File:   main.cpp
 * Author: Josh McIntyre
 * Created on February 3, 2020, 6:06 PM
 */

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
    char choice;
    
    cout<<"Please input e: ";
    cin>>e;
    
    cout<<"Please input n: ";
    cin>>n;
    
    cout<<"Type 'e' for encryption or 'd' for decryption. Input is read from 'input.txt' file.\n";
    cin>>choice;
    
    (choice == 'e') ? isEnc = true : isEnc = false;
    
    pq = getPQ(n);
    
    cout<<"p is "<<pq[0]<<"\nq is "<<pq[1]<<endl;
    
    phiN = ((pq[0]-1) * (pq[1]-1));
    
    cout<<"phi(n) is "<<phiN<<endl;
    
    cout<<"e and phi(n) are "<<((findGCD(e, phiN) == 1)?"coprime\n":"not coprime so e and n are invalid!\n");
    if((findGCD(e, phiN) != 1)) return 0;
    
    // Attempt to find d (bruteforce integer guessing)
    for(int i = 0; i < 100000; i++) {
        int tmp = (i*e)%phiN;
        if(tmp == 1) {
            d = i;
            i = 100000;
        }
        else d = -1;
    }
    
    cout<<"d is "<<d<<endl;
    
    if(!isEnc) {
        // Read from input file
        ifstream file("input.txt");
        vector<int> array;
        int number;
        while(file >> number) {
            array.push_back(number);
        }
    
        string output = "";
        for(int i = 0; i < array.size(); i++) {
            // Attempts to calculate exponentiation if exponent is less than or equal to 4
            // (to decrease chance of overflow)
            if(d <= 4) {
                unsigned long long int tmp = pow(array[i], d);
                tmp %= n;
                char M = tmp + '?';
                cout<<tmp<<endl;
                output+=M;
            }

            // Utilizes method of exponentiation by squaring if d > 4
            else if(d > 4) {
                int tmp = d;
                unsigned long long int tmp2;
                int product = 1;

                if(tmp%2 == 1) product *= array[i];
                tmp /= 2;

                tmp2 = pow(array[i], 2);
                tmp2 %= n;

                // Exponentiation by squaring algorithm
                while(tmp > 1) {
                    if(tmp%2 == 1) product *= tmp2;
                    tmp /= 2;

                    tmp2 = pow(tmp2, 2);
                    tmp2 %= n;
                }

                // Compute final modular calculation
                unsigned long long int tmp3 = pow(tmp2, tmp);

                if(i == 0) cout<<"Raw output: ";

                char M;
                tmp2 = ((tmp3 * product) % n);
                if(tmp2 == 28) M = ' ';             // Handles SPACE encoding to ASCII conversion
                else M = tmp2 + '?';                // Handles all other character encoding to ASCII conversion
                cout<<M;                            // Displays raw output
                output+=M;                          // Builds upon decoded message string
            }
        }

        cout<<"\nDecoded Message -> "<<output<<endl;

        ofstream out;
        out.open("output.txt");
        out<<output<<endl;
        out.close();
    }
    else {
        vector<unsigned long long int> cipher;
        
        ifstream file;
        file.open("input.txt");
        string text;
        getline(file, text);
        // cout<<"Text: "<<text<<endl;
        file.close();
        
        char chars[text.size()] = {};
        for(int i = 0; i < text.size(); i++)
            chars[i] = text[i];
        // cout<<"Chars: "<<text<<endl;
        for(int i = 0; i < text.size(); i++) {
            
            // Encode characters (A=2, B=3, ..., Z=27, SPACE=28)
            if(chars[i] == ' ') chars[i] = 28;
            else chars[i] -= '?';
            
            // cout<<static_cast<int>(chars[i])<<' '<<endl;
            
            unsigned long long int tmp = pow(static_cast<int>(chars[i]), e);
            cipher.push_back(tmp % n);
            cout<<cipher[i]<<' ';
        }
        
        ofstream out;
        out.open("output.txt");
        for(int i = 0; i < cipher.size(); i++) {
            out<<cipher[i]<<' ';
            if(i > 0 && i % 6 == 0) out<<endl;
        }
        out.close();
    }
    
    delete [] pq;

    return 0;
}

// Utility function for primality testing
bool isPrime(int num) {
    
    for(int i = 1; i <=  sqrt(num); i++) {
        for(int j = 1; j <=  num; j++) {
            int product = i * j;
            // Uncomment for debug message to view i and j
            // cout<<i<<" * "<<j<<" = "<<product<<endl;
            if(i != 1 && j != 1 && product == num) return false;
        }
    }
    
    return true;
}

// Utility function for finding prime numbers p and q such that n = pq
int* getPQ(int num) {
    int* pq = new int[2];
    
    if(isPrime(num)) {
        pq[0] = -1;
        pq[1] = -1;
        cout<<"n should not be a prime number!\n";
        return pq;
    }
    
    int i , j;
    
    bool found = false;
    for(i = 1; i <=  sqrt(num); i++) {
        for(j = 1; j <=  num; j++) {
            int product = i * j;
            // Uncomment for debug message to view i and j
            // cout<<i<<" * "<<j<<" = "<<product<<endl;
            if(i != 1 && j != 1 && product == num && isPrime(i) && isPrime(j)) {
                
                found = true;
                
                if(i == j) {
                    pq[0] = -1;
                    pq[1] = -1;
                    cout<<"ERROR: n is invalid due to p and q being the same value!\n";
                } else {
                    pq[0] = i;
                    pq[1] = j;
                }
                
                return pq;
            }
        }
    }
    
    if(!found) {
        pq[0] = -1;
        pq[1] = -1;
        cout<<"p and q could not be found, possibly due to overflow (try a smaller n)!\n";
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

