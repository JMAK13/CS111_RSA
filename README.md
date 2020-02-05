# CS111_RSA
## CS/MATH111 EXTRA CREDIT ASSIGNMENT
For this assignment, you need to implement the RSA public-key cryptosystem in C++.  
### Input:  
a) A public key (e, n) (you need to check whether the input is valid);  
b) Choice of encryption or decryption (”e” for encryption and ”d” for decryption);

Additional input for encryption:  
c1) English text (in a text file). You can use well known quotes.  
Additional input for decryption:  

c2) Cipher text (in a text file).  
Note: in this part, you need to break RSA (follow your homework 2 (problem 2) instructions).  

### Output:  
For encryption: cipher text (written into a text file).  
For decryption: decoded message (written into a text file).  

You can reuse the character - integer encoding schema from your Homework 2 (A is 2, B is 3, ..., Z is 27,  
and blank is 28) and append it with other characters if needed.  

Submission/Demo Instructions. The project is due Sunday, February 9, 11:50pm (on Gradescope).  
The details about the submission will be posted later  

## Problem 2:  
Alice’s RSA public key is P = (e, n) = (13, 77). Bob sends Alice the message by encoding it  
as follows. First he assigns numbers to characters: A is 2, B is 3, ..., Z is 27, and blank is 28. Then he uses  
RSA to encode each number separately.  

Bob’s encoded message is:  
10 7 58 30 23 62  
7 64 62 23 62 61  
7 41 62 21 7 49  
75 7 69 53 58 37  
37 41 10 64 50 7  
10 64 21 62 61 35  
62 61 62 7 52 10  
21 58 7 49 75 7  
62 26 22 53 30 21  
10 37 64  

Decode Bob’s message. Notice that you don’t have Bob’s secrete key, so you need to “break” RSA to
decrypt his message.  

For the solution, you need to provide the following:  
• Describe step by step how you arrived at the solution. In particular, explain how you determined p, q,
φ(n), and d.  
• Show the calculation that determine the letters in the message from the first 3 numbers in ciphertext.  
• Give Bob’s message in plaintext. The message is a quote. Who said it? What does it mean?  
• (SKIP IF YOU CHOSE THE PROJECT.) If you wrote a program, attach your code to the hard copy.  
If you solved it by hand (not recommended), attach your scratch paper with calculations.  
