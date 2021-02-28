#include "mbedtls/arc4.h"
#include <stdio.h>
#include <string.h>
#define mbedtls_printf printf
FILE *fp;
static const unsigned char arc4_test_key[3][8] =
{
    { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF },
    { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

static const unsigned char arc4_test_pt[3][8] =
{
    { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

static const unsigned char arc4_test_ct[3][8] =
{
    { 0x75, 0xB7, 0x87, 0x80, 0x99, 0xE0, 0xC5, 0x96 },
    { 0x74, 0x94, 0xC2, 0xE7, 0x10, 0x4B, 0x08, 0x79 },
    { 0xDE, 0x18, 0x89, 0x41, 0xA3, 0x37, 0x5D, 0x3A }
};


int main() {
	int i, ret = 0;
    unsigned char ibuf[128]="See-ya";
    unsigned char obuf[8];
    mbedtls_arc4_context ctx;

	printf("%s", "Enter string for encryption (arc4): ");
	//fgets(ibuf, sizeof(ibuf), stdin);  // read string

	//*************************************************************************
    fp = fopen("file.txt" , "r");
	if(fp == NULL) 
	{
	      perror("Error opening file");
	      
	}
    if( fgets (ibuf, sizeof(ibuf), fp)!=NULL ) 
    {
      /* writing content to stdout */
      puts(ibuf);
    }
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	ibuf[strcspn(ibuf, "\n")] = 0; // ignoring new line while reading input using fgets
    mbedtls_arc4_init( &ctx );
    
    fp = fopen("encrypted_rc4.txt", "w");
    if (fp == NULL)  printf("Error!");

    for( i = 0; i < 3; i++ ) {        
	    //memcpy( ibuf, arc4_test_pt[i], 8 );

	    mbedtls_arc4_setup( &ctx, arc4_test_key[i], 8 );
	    mbedtls_arc4_crypt( &ctx, 8, ibuf, obuf );
		for( i = 0; i < 8; i++ )
		{
			fprintf(fp, "%02x", obuf[i]);
	    	printf( "%02x", obuf[i] );
		}
		printf("\n");
	}


}