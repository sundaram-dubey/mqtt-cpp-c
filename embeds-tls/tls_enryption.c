/*
 *  Classic "Hello, world" demonstration program
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <string.h>
#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdlib.h>
#include <stdio.h>

#define mbedtls_printf       printf
#define mbedtls_exit         exit
#define MBEDTLS_EXIT_SUCCESS EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE EXIT_FAILURE
#endif

#if defined(MBEDTLS_MD5_C)
#include "mbedtls/md5.h"
#include "mbedtls/sha512.h"
#include "mbedtls/sha256.h"

#endif

#if !defined(MBEDTLS_MD5_C)
int main( void )
{
    mbedtls_printf("MBEDTLS_MD5_C not defined.\n");
    mbedtls_exit( 0 );
}
#else


static void dump_buf( const char *title, unsigned char *buf, size_t len )
{
    size_t i;

    mbedtls_printf( "%s", title );
    for( i = 0; i < len; i++ )
        mbedtls_printf("%c%c", "0123456789ABCDEF" [buf[i] / 16],
                       "0123456789ABCDEF" [buf[i] % 16] );
    mbedtls_printf( "\n" );
}



int main( void )
{
    int i, ret;
    unsigned char digest[16];
    unsigned char hash[32];
    char str[1000] = "I";
    printf("%s\n", "Enter string for encryption: ");
    fgets(str, sizeof(str), stdin);  // read string

    str[strcspn(str, "\n")] = 0; // ignoring new line while reading input using fgets

    mbedtls_printf( "MD5(\"%s\") = ", str );

   //md5 encryption using tls

    if( ( ret = mbedtls_md5_ret( (unsigned char *) str, 1000, digest ) ) != 0 )
        mbedtls_exit( MBEDTLS_EXIT_FAILURE );

    for( i = 0; i < 16; i++ )
        mbedtls_printf( "%02x", digest[i] );

    mbedtls_printf( "\n" );


    //sha-256 encryption using tls

     if( ( ret = mbedtls_sha256_ret( str, sizeof( str ), hash, 0 ) ) != 0 )
    {
        mbedtls_printf( " failed\n  ! mbedtls_sha256_ret returned %d\n", ret );
    }

    dump_buf( "SHA-256: ", hash, sizeof( hash ) );

    // sha-512 encryption using tls

    if( ( ret = mbedtls_sha512_ret( str, sizeof( str ), hash, 0 ) ) != 0 )
    {
        mbedtls_printf( " failed\n  ! mbedtls_sha512_ret returned %d\n", ret );
    }

    dump_buf( "SHA-512: ", hash, sizeof( hash ) );

    mbedtls_exit( MBEDTLS_EXIT_SUCCESS );

}
#endif /* MBEDTLS_MD5_C */
