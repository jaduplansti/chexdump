#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
MIT License

Copyright (c) 2026 jaduplansti

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 
*/

int READ_SIZE = 16;
char *FILE_NAME = NULL;

FILE *openBin(const char *file_name) {
	// Helper Function To Open Files 
	FILE *bin = fopen(file_name, "rb");
	return bin;
}

void closeBin(FILE *bin) {
	// Helper Function To Close Files
	fclose(bin);
}

void printString(unsigned char bytes[]) {
	printf(" |");
	for (int i = 0; i < READ_SIZE; i++) {
		if (isprint(bytes[i]) && bytes[i] != ' ') printf("%c", bytes[i]);
		else printf(".");
	}
	printf("|");
}

void printBytes(unsigned char bytes[], int address) {
	// Prints The Bytes And Address
	printf("%07X ", address); // Prints The Address
	for (int i = 0; i < READ_SIZE; i++) {
		if (i % 2 == 0 && i != 0) printf(" "); // Creates A Gap Every 2 Bytes
		printf("%02X", bytes[i]); 
	}
	printString(bytes);
	printf("\n");
}

void dumpBin(FILE *bin) {
	// Reads And Dumps Bin
	unsigned char bytes[READ_SIZE]; // Buffer To Hold READ_SIZE Bytes
	int address = 0; // Starting Offset
	while (feof(bin) == 0) { // Reading Loop
		fread(&bytes, sizeof(unsigned char), READ_SIZE, bin);
		printBytes(bytes, address);
		address += READ_SIZE;
	}
}

int readArgs(int argc, char **argv) {
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0 && (i + 1 < argc)) {
			int read_size = atoi(argv[++i]); // erm make this safer
			if (read_size > 64) {
				printf("usage (read size must not exceed 64): ./chexdump -d (bytes=16) [bin]\n");
				return -1;
			}
			READ_SIZE = read_size;
		}
		else FILE_NAME = argv[i];
	}
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("usage (empty args): ./chexdump -d (bytes=16) [bin]\n");
		return -1;
	}
	
	if (readArgs(argc, argv) == -1) return -1;
	
	if (FILE_NAME == NULL) {
		printf("usage (no file specified): ./chexdump -d (bytes=16) [bin]\n");	
		return -1;
	}
	
	FILE *bin = openBin(FILE_NAME);
	
	if (bin == NULL) {
		printf("error (failed to open file): ./chexdump -d (bytes=16) [bin]\n");
		return -1;
	}
	dumpBin(bin);	
	closeBin(bin);
	return 0;
}
