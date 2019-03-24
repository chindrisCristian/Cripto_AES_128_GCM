# Cripto_AES_128_GCM

The project contains the following pieces:
  - A parameterized entry point specifying the necessesary details for the program 
  - Two classes, one that resolv the input parameters, and the other, that work with OpenSSL's EVP functions to encrypt/ decrypt
  - The exemple files I've worked with
  
Input parameters: -in, -out, -key, -iv, -aad.
  - -in specifies that the following parameter represents the name of the input file.
  - -out specifies that the following parameter represents the name of the output file.
  - -key specifies that the following parameter represents the name of the file that contains the key.
  - -iv specifies that the following parameter represents the name of the file that contains the IV.
  - -aad specifies that the following parameter represents the name of the file that contains the AAD.
  
Implementation details:
 - If the -in is omitted, the program requires user input (from STD_IN);
 - If the -out is omitted, the program will save the output in a file called data.enc (Was given while thinking about the encryption procces, but is the same for decryption too...)
 - If the -key is omitted, the program requires input from STD_IN, also for -iv.
 - If the -aad is omitted, the program encrypt/decrypt data without AAD.
 
