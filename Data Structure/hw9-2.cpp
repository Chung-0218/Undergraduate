#include <stdio.h>
#include <stdlib.h>

void read_file(float* input, int heigth, int width, char filename[]) {
	int x, y;
	FILE* fp;

	fp = fopen(filename, "r");

	for (y = 0; y < heigth; y++) {
		for (x = 0; x < width; x++) {
			fscanf(fp, "%f", &input[y * width + x]);
		}
		fscanf(fp, "\n");
	}
	fclose(fp);
}

void meadian_filtering(float *, float *, int, int) {}

int main() {

	int heigth = 44, width = 45;
	read_file();

	return 0;
}