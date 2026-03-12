#include <stdio.h>
#include <stdlib.h>

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

FILE *openBin(const char *file_name) {
	// Helper Function To Open Files 
	FILE *bin = fopen(file_name, "rb");
	return bin;
}

void closeBin(FILE *bin) {
	// Helper Function To Close Files
	fclose(bin);
}

void printBytes(unsigned char bytes[], int address) {
	// Prints The Bytes And Address
	printf("%08X ", address); // Prints The Address
	for (int i = 0; i < 16; i++) {
		if (i % 2 == 0 && i != 0) printf(" "); // Creates A Gap Every 2 Bytes
		printf("%02X", bytes[i]); 
	}
	printf("\n");
}

void dumpBin(FILE *bin) {
	// Reads And Dumps Bin
	unsigned char bytes[16]; // Buffer To Hold 16 Bytes
	int address = 0; // Starting Offset
	while (feof(bin) == 0) { // Reading Loop
		fread(&bytes, sizeof(unsigned char), 16, bin);
		printBytes(bytes, address);
		address += 16;
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("usage (no file specified): ./chexdump [bin]\n");
		return -1;
	}

	FILE *bin = openBin(argv[1]);
	
	if (bin == NULL) {
		printf("error (failed to open file): ./chexdump [bin]\n");
		return -1;
	}
	dumpBin(bin);	
	closeBin(bin);
	return 0;
}
