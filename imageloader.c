/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				Shi Yi
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
	FILE *fp = fopen(filename, "r");
	Image *res = (Image*)malloc(sizeof(Image));
	char buf[20];
	int width, height, ColorRange;
	fscanf(fp, "%s", buf);
	fscanf(fp, "%d %d", &width, &height);
	fscanf(fp, "%d", &ColorRange);
	Color **image = (Color**)malloc(sizeof(Color*)*width*height);
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			Color *p = (Color*)malloc(sizeof(Color));
			int r,g,b;
			fscanf(fp, "%d %d %d", &r, &g, &b);
			p->R = r; p->G = g; p->B = b;
			image[i*width+j] = p;
		}
	}
	fclose(fp);
	res->cols = width;
	res->rows = height;
	res->image = image;
	return res;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	printf("P3\n");
	printf("%d %d\n", image->cols, image->rows);
	printf("%d\n", 255);
	Color **p = image->image;
	for(int i = 0; i < image->rows; i++) {
		for(int j = 0; j < image->cols; j++) {
			if(j == 0) {
				int r = p[i*image->cols+j]->R, g = p[i*image->cols+j]->G, b = p[i*image->cols+j]->B;
				printf("%3d %3d %3d", r, g, b);
			}
			else {
				int r = p[i*image->cols+j]->R, g = p[i*image->cols+j]->G, b = p[i*image->cols+j]->B;
				printf("   %3d %3d %3d", r, g, b);
			}
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	for(int i = 0; i < image->rows*image->cols; i++) {
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}