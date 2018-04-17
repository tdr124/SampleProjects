/*Name: Michael Briden
 *02/09/18
 *Project02
 *I wanted to include functions and pointers but I designed and programmed this assignment
 * before we learned about pointers and functions. If the user puts in values for height and
 * width other than the the image's actual height and width then outputs will end up being funny.
 * Compiled on cssgate.
 */

#include<stdio.h>
#include<string.h>


int main(void){
	int imgwidth = -1;
	int imgheight = -1;
	const int HEADER_SIZE = 54;
	const int ratio = 2.9695;
	char filename[54];

	/*prompt user for for file name*/
	printf("Enter the filename:");
	scanf("%49s", filename);
	strcat(filename, ".bmp\0");

	/*prompt user for image dimensions*/
	printf("Enter height and width (in pixels)");
	scanf("%d %d", &imgheight, &imgwidth);

	/*read in file declare outfiles*/
	char header[HEADER_SIZE];
	unsigned char imgarr[imgheight][3 * imgwidth];
	unsigned char cpyarr[imgheight][3 * imgwidth];
	FILE *infile = fopen(filename, "rb");
	FILE *outfile = fopen("copy1.bmp", "wb");
	FILE *outfile1 = fopen("copy2.bmp", "wb");
	FILE *outfile2 = fopen("copy3.bmp", "wb");
	FILE *outfile3 = fopen("copy4.bmp", "wb");

	fread(header, 1, HEADER_SIZE, infile);
	fread(imgarr, 1, imgheight * imgwidth * 3, infile);

	/*invert colors*/
	int row, col;
	for(row =0; row < imgheight; row++){
		for(col = 0; col < imgwidth*3; col++){
			cpyarr[row][col]= 255 - imgarr[row][col];
		}/*for*/
	}/*for*/

	/*save output file with inverted colors*/
	fwrite(header, sizeof(char), HEADER_SIZE, outfile);
	fwrite(cpyarr, sizeof(char), imgheight * imgwidth * 3, outfile);

	/*change contrast rewrite cpyarr*/
	for(row = 0; row < imgheight; row++){
		for(col = 0; col < imgwidth*3; col += 3){

			/*if resulting blue >255*/
			if( ratio * (imgarr[row][col]-128) + 128 > 255 )
				cpyarr[row][col] = 255;
			/*else if resulting blue < 0*/
			else if( ratio * (imgarr[row][col]-128) + 128 < 0  )
				cpyarr[row][col] = 0;
			else
				cpyarr[row][col] = ratio * (imgarr[row][col]-128) + 128;

			/*if resulting green >255*/
			if( ratio * (imgarr[row][col+1]-128) + 128 > 255  )
				cpyarr[row][col+1] = 255;
			/*else if resulting green <0*/
			else if(ratio * (imgarr[row][col+1]-128) + 128 < 0)
				cpyarr[row][col+1] = 0;
			else
				cpyarr[row][col+1] = ratio * (imgarr[row][col+1]-128)+128;

			/*if resulting red >255*/
			if( ratio * (imgarr[row][col+2]-128) + 128 > 255  )
				cpyarr[row][col+2] = 255;
			/*else if resulting red <0*/
			else if( ratio * (imgarr[row][col+2] - 128) + 128 < 0 )
				cpyarr[row][col+2] = 0;
			else
				cpyarr[row][col+2] = ratio * (imgarr[row][col+2]-128)+128;
		}/*col*/
	}/*row*/

	/*save file with altered contrast*/
	fwrite(header, sizeof(char), HEADER_SIZE, outfile1);
	fwrite(cpyarr, sizeof(char), imgheight * imgwidth * 3, outfile1);

	/*create mirrored image and save to cpyarr*/
	for(row = 0; row < imgheight; row++){
		for(col = 0; col < (3 * imgwidth) / 2; col+=3){
			cpyarr[row][col] = imgarr[row][col];
			cpyarr[row][col+1] = imgarr[row][col+1];
			cpyarr[row][col+2] = imgarr[row][col+2];
			cpyarr[row][3*imgwidth - 1 - (col+2)] = imgarr[row][col];
			cpyarr[row][3*imgwidth - 1 - (col+1)] = imgarr[row][col+1];
			cpyarr[row][3*imgwidth - 1 - col] = imgarr[row][col+2];
		}/*col*/
	}/*row*/

	/*invert mirrored image*/
	int tmp = -1;
	for(row = 0; row < imgheight/2; row++){
		for(col = 0; col < (3*imgwidth); col++){
			tmp = cpyarr[row][col];
			cpyarr[row][col] = cpyarr[imgheight-1-row][col];
			cpyarr[imgheight-1-row][col] = tmp;
		}/*col*/
	}/*row*/

	/*save mirror and flipped image*/
	fwrite(header, sizeof(char), HEADER_SIZE, outfile2);
	fwrite(cpyarr, sizeof(char), imgheight * imgwidth * 3, outfile2);

	/*create scaled down original image*/
	int j;
	for(row = 0; row < imgheight; row++){
		for(col = 0; col < imgwidth; col++){
			cpyarr[row/2][3* (col/2) ] = imgarr[row][3*col];
			cpyarr[row/2][3 * (col/2) + 1] = imgarr[row][3*col+1];
			cpyarr[row/2][3 * (col/2) + 2 ] = imgarr[row][3*col+2];
		}/*col*/
	}/*row*/

	/*copy scaled down image to upper left corner*/
	for(row = 0; row <imgheight/2; row++){
		for(col = 1; col <= 3 * (imgwidth/2); col++){
			/*change color to red only*/
			if(col % 3 == 0)
				cpyarr[imgheight/2+row][col-1] = cpyarr[row][col-1];
			else
				cpyarr[imgheight/2+row][col-1] = 0;
		}/*col*/
	}/*row*/

	/*copy scaled down image to upper right corner*/
	for(row = 0; row <imgheight/2; row++){
		for(col = 2; col <= 3 * (imgwidth/2)+1; col++){
			/*change color to green only*/
			if(col % 3 == 0)
				cpyarr[imgheight/2+row][3 * (imgwidth/2) + col-2] = cpyarr[row][col-2];
			else
				cpyarr[imgheight/2+row][3 * (imgwidth/2) + col-2] = 0;
		}/*col*/
	}/*row*/

	/*copy scaled down image to lower right corner*/
	for(row = 0; row <imgheight/2; row++){
		for(col = 1; col <= 3 * (imgwidth/2); col++){
				cpyarr[row][3 * (imgwidth)/2 + col-1] = cpyarr[row][col-1];
		}/*col*/
	}/*row*/

	/*change lower left corner to blue only*/
	for(row = 0; row <imgheight/2; row++){
		for(col = 3; col <= 3 * (imgwidth/2)+2; col++){
			/*change color to green only*/
			if(col % 3 == 0)
				cpyarr[row][col-3] = cpyarr[row][col-3];
			else
				cpyarr[row][col-3] = 0;
		}/*col*/
	}/*row*/

	/*save scaled image*/
	fwrite(header, sizeof(char), HEADER_SIZE, outfile3);
	fwrite(cpyarr, sizeof(char), imgheight * imgwidth * 3, outfile3);

	printf("Done. Check the generated images.\n");

}/*main*/


