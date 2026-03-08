/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	int rows = (int)image->rows;
	int cols = (int)image->cols;
	Color *pixel = malloc(sizeof(Color));
	pixel->R = 0;
	pixel->G = 0;
	pixel->B = 0;
	for(int bit = 0; bit < 8; bit++){
		int cntR = 0;
		int cntG = 0;
		int cntB = 0;
		for(int i = -1; i <= 1; i++){
			for(int j = -1; j <= 1; j++){
				if(i==0 && j==0){continue;}
				int new_row = (row + i + rows) % rows;
				int new_col = (col + j + cols) % cols;
				cntR += ((image->image[new_row][new_col].R)>>bit) & 1;
				cntG += ((image->image[new_row][new_col].G)>>bit) & 1;
				cntB += ((image->image[new_row][new_col].B)>>bit) & 1;
			}
		}
		if(((image->image[row][col].R)>>bit) & 1){
			int newstate = (rule >> (cntR+9)) & 1;
			pixel->R = (pixel->R & ~(1 << bit)) | (newstate << bit);
		}
		else {
			int newstate = (rule >> cntR) & 1;
			pixel->R = (pixel->R & ~(1 << bit)) | (newstate << bit);
		}
		if(((image->image[row][col].G)>>bit) & 1){
			int newstate = (rule >> (cntG+9)) & 1;
			pixel->G = (pixel->G & ~(1 << bit)) | (newstate << bit);
		}
		else {
			int newstate = (rule >> cntG) & 1;
			pixel->G = (pixel->G & ~(1 << bit)) | (newstate << bit);
		}
		if(((image->image[row][col].B)>>bit) & 1){
			int newstate = (rule >> (cntB+9)) & 1;
			pixel->B = (pixel->B & ~(1 << bit)) | (newstate << bit);
		}
		else {
			int newstate = (rule >> cntB) & 1;
			pixel->B = (pixel->B & ~(1 << bit)) | (newstate << bit);
		}
	}
	return pixel;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	Image* new_image = malloc(sizeof(Image));
	new_image->rows = image->rows;
	new_image->cols = image->cols;
	new_image->image = (Color**) malloc(new_image->rows*sizeof(Color*));
	for(int i=0;i<new_image->rows;i++){new_image->image[i] = (Color*)malloc(new_image->cols*sizeof(Color));}
	for(int i=0;i<new_image->rows;i++){
		for(int j=0;j<new_image->cols;j++){
			Color *pixel = evaluateOneCell(image,i,j,rule);
			new_image->image[i][j].R = pixel->R;
			new_image->image[i][j].G = pixel->G;
			new_image->image[i][j].B = pixel->B;
			free(pixel);
		}
	}
	return new_image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	if(argc!=3){
		exit(-1);
	}
	char *filename = argv[1];
	uint32_t rule = strtol(argv[2],NULL,16);
	Image* image = readData(filename);
	if(image==NULL){
		printf("Failed to read image\n");
		exit(-1);
	}
	Image* new_image = life(image,rule);
	if(new_image==NULL){
		printf("Failed to create new image\n");
		exit(-1);
	}
	writeData(new_image);
	freeImage(image);
	freeImage(new_image);
	return 0;
}
