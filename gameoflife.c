/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				xgyy
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
	//YOUR CODE HERE
	Color *p = (Color*)malloc(sizeof(Color));
	int height = image->rows, width = image->cols;
	/* Calculate alive neighbors. */
	int aliveR = 0, aliveG = 0, aliveB = 0;
	for(int i=-1;i<2;i++) {
		for(int j=-1;j<2;j++) {
			int rowid = (row + i + height) % height, colid = (col + j + width) % width;
			if(rowid == row && colid == col)
				continue;
			if(image->image[rowid*width+colid]->R == 255) aliveR++;
			if(image->image[rowid*width+colid]->G == 255) aliveG++;
			if(image->image[rowid*width+colid]->B == 255) aliveB++;
		}
	}
	uint32_t aliverule;
	if(image->image[row*width+col]->R == 255)
		aliverule = rule >> 9;
	if(image->image[row*width+col]->R == 0)
		aliverule = rule;
	aliverule >>= aliveR;
	aliverule &= 1;
	if(aliverule == 1) {// next state will be alive
		p->R = 255;
	}
	else { // next state will be dead
		p->R = 0;
	}

	if(image->image[row*width+col]->G == 255)
		aliverule = rule >> 9;
	if(image->image[row*width+col]->G == 0)
		aliverule = rule;
	aliverule >>= aliveG;
	aliverule &= 1;
	if(aliverule == 1) {// next state will be alive
		p->G = 255;
	}
	else { // next state will be dead
		p->G = 0;
	}

	if(image->image[row*width+col]->B == 255)
		aliverule = rule >> 9;
	if(image->image[row*width+col]->B == 0)
		aliverule = rule;
	aliverule >>= aliveB;
	aliverule &= 1;
	if(aliverule == 1) {// next state will be alive
		p->B = 255;
	}
	else { // next state will be dead
		p->B = 0;
	}

	return p;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *p = (Image*)malloc(sizeof(Image));
	p->cols = image->cols; p->rows = image->rows;
	p->image = (Color**)malloc(sizeof(Color*)*image->cols*image->rows);
	for(int i = 0; i < image->rows; i++) {
		for(int j = 0; j < image->cols; j++) {
			p->image[i*image->cols+j] = evaluateOneCell(image, i, j, rule);
		}
	}
	return p;
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
	//YOUR CODE HERE
	if(argc != 3) {
		printf("    usage: ./gameOfLife filename rule\n");
		printf("    filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		printf("    rule is a hex number beginning with 0x; Life is 0x1808.\n");
		return -1;
	}
	Image *p = readData(argv[1]);
	Image *q = life(p, strtol(argv[2], NULL, 0));
	writeData(q);
	freeImage(p);
	freeImage(q);
	return 0;
}
