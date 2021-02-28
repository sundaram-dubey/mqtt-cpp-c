#include "mbedtls/aes.h"
#include <stdio.h>
#include <string.h>
FILE *fp;
int main() 
{
mbedtls_aes_context aes;
mbedtls_aes_context aes1;
unsigned char key[32];
unsigned char iv[16];

unsigned char input [128]="Stop";
unsigned char output[256];
unsigned char original[256];

printf("%s", "Enter string for encryption: ");
//fgets(input, sizeof(input), stdin);  // read string

fp = fopen("file.txt" , "r");
if(fp == NULL) 
{
      perror("Error opening file");
      
}
if( fgets (input, sizeof(input), fp)!=NULL ) 
{
  /* writing content to stdout */
  puts(input);
}

input[strcspn(input, "\n")] = 0; // ignoring new line while reading input using fgets
// int input_len = 40;
// int output_len = 0;
// mbedtls_aes_setkey_enc( &aes, key, 256 );
// mbedtls_aes_crypt_cbc( &aes, MBEDTLS_AES_ENCRYPT, 48, iv, input, output );
mbedtls_aes_setkey_enc( &aes, key, 256 );
mbedtls_aes_setkey_enc( &aes1, key, 256 );
mbedtls_aes_crypt_ecb( &aes, MBEDTLS_AES_ENCRYPT, input, output );
int i=0;
printf("%s", "AES : ");

fp = fopen("encrypted_aes.txt", "w");
if (fp == NULL)  printf("Error!");

for( i = 0; i < 128; i++ )
{
	fprintf(fp, "%02x", output[i]);
        printf( "%02x", output[i] );
}
printf("\n");


// mbedtls_aes_setkey_enc( &aes, key, 256 );
// mbedtls_aes_crypt_cbc( &aes, MBEDTLS_AES_ENCRYPT, 48, iv, input, output );
// mbedtls_aes_crypt_ecb( &aes1, MBEDTLS_AES_DECRYPT, output, output );
// for( i = 0; i < 16; i++ )
//     output[i] = (unsigned char)( output[i] ^ iv[i] );
// i=0;
// printf("%s\n", output);
// for( i = 0; i < 128; i++ )
//         printf( "%02x", output[i] );
// printf("\n");

return 0;
}