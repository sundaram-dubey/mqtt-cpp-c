#include "mbedtls/blowfish.h"
#include <stdio.h>
#include <string.h>
	int main() {
	mbedtls_blowfish_context aes;
	unsigned char key[32];
	//unsigned char iv[16];

	unsigned char input [128]="Stop";
	unsigned char output[8];
	unsigned char original[28];

	printf("%s", "Enter string for encryption: ");
	fgets(input, sizeof(input), stdin);  // read string

	input[strcspn(input, "\n")] = 0; // ignoring new line while reading input using fgets
	mbedtls_blowfish_crypt_ecb( &aes, MBEDTLS_BLOWFISH_ENCRYPT, input, output );
	int i=0;
	printf("%s", "BLOWFISH : ");
	for( i = 0; i < 8; i++ )
	        printf( "%02x", output[i] );
	printf("\n");

	return 0;
}