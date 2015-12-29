#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes.h"
#include "base64.h"

#ifdef WIN32
    #include <Windows.h>
    #include <tchar.h>
#else
    #include <unistd.h>
#endif

void __getmachinename(char* machineName)
{
    char Name[150];
    int i=0;

    #ifdef WIN32
        TCHAR infoBuf[150];
        DWORD bufCharCount = 150;
        memset(Name, 0, 150);
        if( GetComputerName( infoBuf, &bufCharCount ) )
        {
            for(i=0; i<150; i++)
            {
                Name[i] = infoBuf[i];
            }
        }
        else
        {
            strcpy(Name, "Unknown_Host_Name");
        }
    #else
        memset(Name, 0, 150);
        gethostname(Name, 150);
    #endif
    strncpy(machineName,Name, 150);
}

void __getusername(unsigned char* username)
{
	char Name[150];
	#ifdef WIN32
		strncpy(Name, getenv("USERNAME"), 150);
	#else
		printf("Encryption support not yet implemented for non-windows systems.");
	#endif // WIN32
		strncpy(username, Name, 150);
}

void strInsert(char *dest, char *source, int offset, int sourceLength){
	int i;
	for (i= 0; i < sourceLength; i++)
	{
			dest[i + offset] = source[i];
	}
}

void genKey(unsigned char *key, int size)
{
    unsigned char hostname[1024];
    unsigned char username[1024];

	memset( key, '0', size );

    __getusername(username);
    __getmachinename(hostname);

	strInsert(key, hostname, 0, strlen(hostname));
	strInsert(key, "::", strlen(hostname), 2);
	strInsert(key, username, strlen(hostname) + 2, strlen(username));
	key[size] = '\0';
}

void decrypt(char *output, char *input)
{
	printf("\n    decrypt()\n");

	// set the key length -- remaining characters will be 0'd to ensure key length
	int keyLength = 32;

	// instantiate the key
	char key[keyLength];

	// generate the key and dump it onto the zero mask
    genKey(key, keyLength);

	// dumping ground for base64-decoded encrypted input
	char decoded_encrypted_message[1024] = {'\0'};
	char decoded_decrypted_encoded_message[1024] = {'\0'};
	printf("      Decrypt Input Test:\t%s\n", input);

	// decode input and dump to dumping ground
    base64_decode( decoded_encrypted_message, input );

	// decrypt the raw encrypted message
	AES128_CBC_decrypt_buffer( decoded_decrypted_encoded_message, decoded_encrypted_message, key );

	// base64 the encrypted input, dump it to output
    base64_decode( output, decoded_decrypted_encoded_message);
}
void encrypt(char *output, char *input[])
{
	printf("\n    encrypt()\n");

	// set the key length -- remaining characters will be 0'd to ensure key length
	int keyLength = 32;

	// initialize the key char array
	char key[keyLength];

	// generate the key and dump it onto the zero mask
    genKey(key, keyLength);

	// create a dumping ground for the encryption of the input
	char encrypted_message[1024] = {'0'};
	char encoded_message[1024] = {'0'};
	printf("      Encrypt Input Test:\t%s\n", input);

	// base64 the raw input, dump it to encoded_message
    base64_encode(encoded_message, input);

	printf("      Encrypt Base64 Encoded Input:\t%s\n", encoded_message);
	// encrypt input and dump to encrypted_message
	AES128_CBC_encrypt_buffer(encrypted_message, encoded_message, key);

	// base64 the encrypted input, dump it to output
   base64_encode(output, encrypted_message);
}

int demo( void )
{
	char input[1024] = "this is a test message";
	char output[1024];

	encrypt(input, output);
	printf("ENCRYPTION RESULT:\t%s\n", output);
	decrypt(output, input);
	printf("\DECRYPTION RESULT:\t%s\n", input);

    return 1;
}

