// bmptoc.c
// Name: Daniel Kim

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

// This is the array into which you will load the raw data from the file
// You don't have to use this array if you don't want to, but you will be responsible
// for any errors caused by erroneously using the stack or malloc if you do it a
// different way, incorrectly!
char data_arr[0x36 + 240 * 160 * 4];

int main(int argc, char *argv[]) {

	// 1. Make sure the user passed in the correct number of arguments
	if (argc != 2) {
		printf("You have entered the wrong number of arguments.\n");
		return 0;
	}

	// 2. Open the file. If it doesn't exist, tell the user and then exit
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("File does not exist.\n");
		return 0;
	}

	// 3. Read the file into the buffer then close it when you are done
	//int bytes_read = 
	fread(data_arr, 1, sizeof(data_arr), fp);
	fclose(fp);


	// 4. Get the width and height of the image
	unsigned int width = *(unsigned int*) (data_arr + 0x12);
	//printf("%d\n", width);
	unsigned int height = *(unsigned int*) (data_arr + 0x16);
	//printf("%d", height);


	// 5. Create header file, and write header contents. Close it
	char headername[strlen(argv[1])- 4];
	char caps[strlen(argv[1]) - 4];
	char headerfile[strlen(argv[1]) - 2];
	strncpy(headername, argv[1], strlen(argv[1]) - 4);
	headername[strlen(argv[1]) - 4] = '\0';
	//printf("%s", headername);
	strcpy(caps, headername);
	sprintf(headerfile, "%s.h", headername);
	FILE *fph = fopen(headerfile, "w");
	for (unsigned int i = 0; i < strlen(caps); i++) {
		caps[i] = toupper(caps[i]);
	}
	//printf("%s", caps);
	fprintf(fph, "#define %s_WIDTH %d\n", caps, width);
	fprintf(fph, "#define %s_HEIGHT %d\n", caps, height);
	fprintf(fph, "const unsigned short %s_data[%d];", headername, width * height);
	fclose(fph);


	// 6. Create C file, and write pixel data. Close it
	char cfile[strlen(argv[1]) - 2];
	sprintf(cfile, "%s.c", headername);
	//printf("%s", cfile);
	FILE *fpc = fopen(cfile, "w");
	fprintf(fpc, "const unsigned short %s_data[%d] = {\n", headername, width * height);
	unsigned int* pixelArray = (unsigned int*) (data_arr + 0x36);
	for (int i = height - 1; i >= 0; i--) {
		for (unsigned int j = 0; j < width; j++) {
			unsigned int pixel = pixelArray[i * width + j];
			unsigned char red = ((pixel >> 0x10) & 0xFF) >> 0x3;
			unsigned char green = ((pixel >> 0x8) & 0xFF) >> 0x3;
			unsigned char blue = (pixel & 0xFF) >> 0x3;
			unsigned short gbaPixel = (blue << 10) | (green << 5) | (red);
			fprintf(fpc, "0x%x, ", gbaPixel);
		}
	}
	fprintf(fpc, "\n};");
	fclose(fpc);
	return 0;
}

