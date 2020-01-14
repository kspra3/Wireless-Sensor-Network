//reference https://stackoverflow.com/questions/58306875/scrambled-output-when-using-openmp-for-xor-cipher
#include "master.h"


// Basic XOR encryption algorithm.
void encrypt_decrypt(int inp[],size_t len) 
{ 
    // Define XOR key 
    // Any character value will work 
    int xorKey = 32; 

    // perform XOR operation of key 
    #pragma omp parallel for 
    for (int i = 0; i <= len; i++) 
    {
        inp[i] = inp[i] ^ xorKey; 
    } 
}