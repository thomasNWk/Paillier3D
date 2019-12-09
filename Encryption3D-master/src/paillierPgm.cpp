#include <stdio.h>
#include "image_ppm.h"
#include<stdlib.h>
#include<iostream>
#include <vector> 
#include <bitset>
#include <time.h>  

using namespace std;
  
int power(int x, unsigned int y, int p) 
{ 
    int res = 1;      
    x = x % p;  
                
    while (y > 0) { 
       
        if (y & 1) 
            res = (res*x) % p;   
      
        y = y>>1;  
        x = (x*x) % p; 
    } 
    return res; 
} 
  
bool millerTest(int d, int n) 
{ 
    int a = 2 + rand() % (n - 4); 
  
    int x = power(a, d, n); 
  
    if (x == 1  || x == n-1) 
       return true; 
  
    while (d != n-1) 
    { 
        x = (x * x) % n; 
        d *= 2; 
  
        if (x == 1)      return false; 
        if (x == n-1)    return true; 
    } 
  
    // Return composite 
    return false; 
} 
  
// It returns false if n is composite and returns true if n 
// is probably prime.  k is an input parameter that determines 
// accuracy level. Higher value of k indicates more accuracy. 
bool isPrime(int n, int k) 
{ 
    if (n <= 1 || n == 4)  return false; 
    if (n <= 3) return true; 
  
    int d = n - 1; 
    while (d % 2 == 0) 
        d /= 2; 
  
    for (int i = 0; i < k; i++) 
         if (!millerTest(d, n)) 
              return false; 
  
    return true; 
} 

int gcd(int a, int b)  { 
  if (a == 0 || b == 0) 
      return 0; 
    
  if (a == b) 
      return a; 
    
  if (a > b) 
      return gcd(a-b, b); 
            
  return gcd(a, b-a); 
} 

bool coprime(int a, int b) {       
    if (gcd(a, b) == 1) 
        return true;
    else
       return false;
} 

int gcdExtended(int a, int b, int *x, int *y)  
{  
    // Base Case  
    if (a == 0)  
    {  
        *x = 0;  
        *y = 1;  
        return b;  
    }  
  
    int x1, y1; 
    int gcd = gcdExtended(b%a, a, &x1, &y1);  
  
    *x = y1 - (b/a) * x1;  
    *y = x1;  
  
    return gcd;  
}  





int main(int argc, char* argv[])
{
  srand (time(NULL));
  char cNomImgLue[250], cNomImgEcrite[250]/*, cNomImgEcrite2[250]*/;
  int nH, nW, nTaille, S;

  if (argc != 3)
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n");
       exit (1) ;
     }

   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);   
  // sscanf (argv[3],"%s",cNomImgEcrite2);

   OCTET *ImgIn, *ImgOut, *ImgOut2;

   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   int newNTaille = nTaille * 2;
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille*2);
  // allocation_tableau(ImgOut2, OCTET, nTaille);


   int l = 2; // pixel per block
   int k = l;
   int mpv = pow(2,16) - 1;
   int p = 233, q = 271;   
   int n = p * q;
   unsigned long long int nSqur = pow(n,2);
   int g = n+1;   // (n,g) encryption key (public)
   int lambda = (p-1)*(q-1);
   int mu = 0;

   unsigned long long int gPowAlpha = g;        
    for(int x = 1; x < gPowAlpha/2; x++) {          
      gPowAlpha = (gPowAlpha * g) % nSqur;   
      cout << "Lx = " << gPowAlpha << endl;             
     }  
    // cout << "Lx = " << gPowAlpha << endl; 
   double Lx = (double)(gPowAlpha-1) / n; 
  // cout << "Lx = " << Lx << endl; 



   int mSize = 262144;
   bitset<262144> message(0);
   for(int i = 0; i < 262144; i++) {
      message[i] = (rand() % 2);
   }

   cout << "p = " << p << '\n' << "q = " << q << '\n' << "n = " << n << '\n' << "nSqur = " << nSqur << '\n' <<"mpv = " << mpv << '\n';

    int currentPix = 0;
    for (int i=0; i < nH; i++) {
     for (int j=0; j < nW; j+=l) {     // Each block of 2 pixels
        // Reorganize
        bitset<8> firstPixel(ImgIn[i*nW+j]);  // firstPixel[0] => LSB  firstPixel[7] => MSB 
        bitset<8> secondPixel(ImgIn[i*nW+j+1]);
        bitset<16> orderedBlock(0);

        for(int x = 0; x < 8; x++) {
          orderedBlock[x*2] = secondPixel[x];
          orderedBlock[x*2+1] = firstPixel[x];
        }

        unsigned short encryptedBlock = (unsigned short)orderedBlock.to_ulong();        

        // Shrink
        encryptedBlock = (double)encryptedBlock / mpv * (n-1);        

        // Remove k LSB
        bitset<16> encryptedBitSet(encryptedBlock);
        
        for(int x = 0; x < k; x++) {
          encryptedBitSet[x] = 0;          
        }

        encryptedBlock = (unsigned short)encryptedBitSet.to_ulong();


        // Generate r to have different encryption of identical blocks
        unsigned int r = (rand() % (n-1)) + 1;

        // Final block encryption
        // Compute g^m 
        unsigned long long int gPowM = g;        
        for(int x = 1; x < encryptedBlock; x++) {          
          gPowM = (gPowM * g) % nSqur;               
         }  

        // Compute r^n
         unsigned long long int rPowN = r;
         for(int x = 1; x < n; x++) {
          rPowN = (rPowN * r) % nSqur; 
          //cout << rPowN << endl << endl;         
         }  
        
        unsigned long long int encryptedImageBlock = (gPowM * rPowN ) % nSqur;    


        // Message encryption ==================================
        // Message block   
        bitset<8> bitMessageBlock(0);  
        bitMessageBlock[1] = message[ImgIn[i*nW+j]];
        bitMessageBlock[0] = message[ImgIn[i*nW+j]+1];   

        unsigned int messageBlock = (unsigned int)bitMessageBlock.to_ulong();

        // Compute g^m 
        gPowM = g;        
        for(int x = 1; x < encryptedBlock; x++) {          
          gPowM = (gPowM * g) % nSqur;               
         }  

        // Compute r^n
        rPowN = r;
        for(int x = 1; x < n; x++) {
          rPowN = (rPowN * r) % nSqur; 
          //cout << rPowN << endl << endl;         
        }  

        unsigned long long int encryptedMessageBlock = (gPowM * rPowN ) % nSqur;    

        unsigned long long int embeddedImageBlock = (encryptedImageBlock * encryptedMessageBlock) % nSqur;

        // Message embedding =====================================
      
        bitset<8> nfirstPixel(0);  
        bitset<8> nsecondPixel(0);
        bitset<8> n3Pixel(0);
        bitset<8> n4Pixel(0);
        bitset<32> norderedBlock(embeddedImageBlock);     

        for(int x = 0; x < 8; x++) {
          nfirstPixel[x] = norderedBlock[x*2];
          nsecondPixel[x] = norderedBlock[x*2+1];
          n3Pixel[x] = norderedBlock[x*2+2];
          n4Pixel[x] = norderedBlock[x*2+3];
        }

        ImgOut[currentPix] = (char)nfirstPixel.to_ulong();
        ImgOut[currentPix+1] = (char)nsecondPixel.to_ulong();
        ImgOut[currentPix+2] = (char)n3Pixel.to_ulong();
        ImgOut[currentPix+3] = (char)n4Pixel.to_ulong();
        currentPix += 4;        

        //cout << encryptedBlock << endl;       
     
       }
      cout << i << endl;
   }  

   // Message decryption
   for (int i = 0; i < newNTaille; i+=4) {
      bitset<8> n1Pixel(ImgOut[i]);  
      bitset<8> n2Pixel(ImgOut[i+1]);
      bitset<8> n3Pixel(ImgOut[i+2]);
      bitset<8> n4Pixel(ImgOut[i+3]);
      bitset<32> imageBlock(0);  

      /*for(int x = 0; x < 8; x++) {
          imageBlock[x] = norderedBlock[x*2];
          nsecondPixel[x] = norderedBlock[x*2+1];
          n3Pixel[x] = norderedBlock[x*2+2];
          n4Pixel[x] = norderedBlock[x*2+3];
        }   
*/
   }

  /*

  double entropie = 0;
  double entropie2 = 0;
  for (int i = 0; i < 256; i++) {    
    if(v[i] != 0) {
      double pai = (double)v[i] / nTaille;
      entropie = entropie + (pai * log2(pai));
    }
    if(v2[i] != 0) {
      double pai2 = (double)v2[i] / nTaille;
    }    
  }

  cout << "Entropie image cryptee = " << -entropie << endl;  */
  
   

  ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
  free(ImgIn);
  return 1;
}
