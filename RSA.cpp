/* 
 * File:   main.cpp
 * Author(s): Josh McIntyre 862054277
 *            Cody Steimle 862137374
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
    string choice;
    string fileN;
    
    e = atoi(argv[1]);
    n = atoi(argv[2]);
    choice = argv[3];
    fileN = argv[4];
    
    (choice == "e") ? isEnc = true : isEnc = false;
    
    pq = getPQ(n);
    
    phiN = ((pq[0]-1) * (pq[1]-1));
    
    // Attempt to find d (bruteforce integer guessing), WILL NOT WORK IF d > MAX_D
    int MAX_D = 10000000;
    for(int i = 0; i < MAX_D; i++) {
        int tmp = (i*e) % phiN;
        if(tmp == 1) {
            d = i;
            i = 10000000;
        }
    }
    
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
            int tmp = d;
            int tmp2;
            int product = 1;

            if(tmp%2 == 1) {
                product %= n;
                product *= array[i];
            }
            tmp /= 2;

            tmp2 = pow(array[i], 2);
            tmp2 %= n;

            // Exponentiation by squaring algorithm
            while(tmp > 1) {
                if(tmp%2 == 1) {
                    tmp2 %= n;
                    product *= tmp2;
                }
                tmp /= 2;

                tmp2 = pow(tmp2, 2);
                tmp2 %= n;
            }

            // Compute final modular calculation
            int tmp3 = pow(tmp2, tmp);

            char M;
            tmp2 = ((tmp3 * product % n));
            if(tmp2 == 28) M = ' ';             // Handles SPACE encoding to ASCII conversion
            else M = tmp2 + '?';                // Handles all other character encoding to ASCII conversion
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
        
        char chars[text.size()] = {};
        for(int i = 0; i < text.size(); i++)
            chars[i] = text[i];
        
        for(int i = 0; i < text.size(); i++) {
            
            // Encode characters (A=2, B=3, ..., Z=27, SPACE=28)
            if(chars[i] == ' ') chars[i] = 28;
            else chars[i] -= '?';
            
            int tmp = e;
            int tmp2;
            int product = 1;

            if(tmp%2 == 1) product *= chars[i];
            tmp /= 2;

            tmp2 = pow(chars[i], 2);
            tmp2 %= n;

            // Exponentiation by squaring algorithm
            while(tmp > 1) {
                if(tmp%2 == 1) product *= tmp2;
                tmp /= 2;

                tmp2 = pow(tmp2, 2);
                tmp2 %= n;
            }

            // Compute final modular calculation
            int tmp3 = pow(tmp2, tmp);

            tmp2 = ((tmp3 * product) % n);
            
            //unsigned long long int tmp = pow(static_cast<int>(chars[i]), e);
            cipher.push_back(tmp2);
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
    
    for(int i = 1; i <=  sqrt(num); i++) {
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
    
    if(isPrime(num)) {
        pq[0] = 1;
        pq[1] = 1;
        return pq;
    }
    
    int i , j;
    
    bool found = false;
    for(i = 1; i <=  sqrt(num); i++) {
        for(j = 1; j <=  num; j++) {
            int product = i * j;
            if(i != 1 && j != 1 && product == num && isPrime(i) && isPrime(j)) {
                
                found = true;
                
                if(i == j) {
                    pq[0] = 1;
                    pq[1] = 1;
                } else {
                    pq[0] = i;
                    pq[1] = j;
                }
                
                return pq;
            }
        }
    }
    
    if(!found) {
        pq[0] = 1;
        pq[1] = 1;
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

