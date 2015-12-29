#include <stdio.h>
typedef char uint8_t;

#include "ConfigEncrypt.h"

void encryptfile()
{
	FILE *infile;
	FILE *outfile;
	infile = fopen("test.ini", "r");
	outfile = fopen("encrypted-test.ini", "w+");

	char file_read_buff[1024];
	char write_buff[1024] = {'\0'};

	printf("encryptfile():\n\n");
	while ( fgets( file_read_buff, sizeof(file_read_buff), infile ) != NULL )
	{
		char line_buff[sizeof(file_read_buff)];
		sscanf(file_read_buff, " %[^\n]", line_buff);
		printf("\n  Plain Text Line:\t%s\n", line_buff);

		encrypt( write_buff, line_buff );
		printf( "\n  Encrypted Line:\t%s\n", write_buff );

		fputs(write_buff, outfile);
		fputs("\n", outfile);
	}
	fclose(infile);
	fclose(outfile);
}

void decryptfile()
{
	FILE *infile;
	FILE *outfile;
	infile = fopen("encrypted-test.ini", "r");
	outfile = fopen("decrypted-test.ini", "w+");

	char file_read_buff[1024] = {'\0'};
	char write_buff[1024] = {'\0'};

	printf("\n\ndecryptfile():\n\n");
	while( fgets( file_read_buff, sizeof(file_read_buff), infile) != NULL )
	{
		char line_buff[sizeof(file_read_buff)] = {'\0'};
		sscanf(file_read_buff, " %[^\n]", line_buff);
		printf("\n  Plain Text Line:\t%s\n", line_buff);

		decrypt(write_buff, line_buff);
		printf("  Decrypted Line:\t%s\n", write_buff);
		fputs(write_buff, outfile);
		fputs("\n", outfile);
	}
	fclose(infile);
	fclose(outfile);
}

int main( int argc, const char* argv[] )
{
	encryptfile();
	decryptfile();
	return 0;
}
