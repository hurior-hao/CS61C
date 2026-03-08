/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	FILE* fp;
	fp = fopen(filename,"r");
	if(fp==NULL){
		printf("Failed to open file\n");
		exit(-1);
	}
	char * type = malloc(3*sizeof(char));
	if(fscanf(fp,"%s",type)!=1){
		printf("Failed to read file type\n");
		exit(-1);
	}
	if(strcmp(type,"P3")!=0){
		printf("Invalid file type\n");
		exit(-1);
	}
	free(type);
	Image* img = malloc(sizeof(Image));
	int max_value;
	if(fscanf(fp,"%d %d %d",&img->cols,&img->rows,&max_value)!=3){
		printf("Failed to read image dimensions\n");
		exit(-1);
	}
	if(max_value!=255){
		printf("Invalid max value\n");
		exit(-1);
	}
	img->image = (Color**) malloc(img->rows*sizeof(Color*));
	for(int i=0;i<img->rows;i++){img->image[i] = (Color*)malloc(img->cols*sizeof(Color));}
	for(int i=0;i<img->rows;i++){
		for(int j=0;j<img->cols;j++){
			fscanf(fp,"%hhu %hhu %hhu",&img->image[i][j].R,&img->image[i][j].G,&img->image[i][j].B);
		}
	}
	fclose(fp);
	return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	printf("P3\n%d %d\n%d\n",image->cols,image->rows,255);
	for(int i=0;i<image->rows;i++){
		for(int j=0;j<image->cols;j++){
			printf("%3d %3d %3d",image->image[i][j].R,image->image[i][j].G,image->image[i][j].B);
			if(j!=image->cols-1){
				printf("   ");
			}
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	for(int i=0;i<image->rows;i++){
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}
