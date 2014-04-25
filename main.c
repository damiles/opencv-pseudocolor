/*
 * main.c
 * Copyright (C) David Millán Escrivá 2010 <david@artresnet.com>
 * 
 * pseudocolor is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * pseudocolor is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include "pseudocolor.h"



int rp,ro,gp,go,bp,bo;
IplImage* img;
IplImage* img_result;

Pseudocolor psdata;

void changeParams(int pos)
{
	psdata.p[0]=(float)bp;
	psdata.p[1]=(float)gp;
	psdata.p[2]=(float)rp;
	
	
	psdata.t[0]=(float)bo/100.0;
	psdata.t[1]=(float)go/100.0;
	psdata.t[2]=(float)ro/100.0;
	
	generate_pseudocolorTable(&psdata);
	pseudocolor(img, img_result, &psdata);
	
}

int main(int argc, char* argv[] )
{
	char *use="<image> [<pseudo_file_load>]\n\n";
	char *help="\n\nPSEUDOCOLOR v0.1\nAuthor: David Millan Escriva <david@artresnet.com>\n\n\tPress key esc to exit\n\tPress key s to save pseudocolor data in pseudo_dat.xml\n\n";
	char *image_file;
	char *pseudo_colorFile;
	
	//Get inputs parameters
	if( argc <2 )
        {
                fprintf(stderr, "\nUse: %s %s", argv[0], use);
                exit(-1);
        }
	//Print help
	printf("%s",help);

	if( argc==3){
		
		pseudo_colorFile=argv[2];
		//Read file and set data
		read_pseudocolor(pseudo_colorFile, &psdata);
		//Set start data for track bar
		rp=(int)psdata.p[2];
		gp=(int)psdata.p[1];
		bp=(int)psdata.p[0];
		
		ro=(int)(100*psdata.t[2]);
		go=(int)(100*psdata.t[1]);
		bo=(int)(100*psdata.t[0]);
		
	}else{
		//Set start data for trackbar
		rp=bp=1;
		gp=2;
		ro=40;go=70;bo=80;
		//Init psdata from start data
		psdata.p[0]=(float)bp;
		psdata.p[1]=(float)gp;
		psdata.p[2]=(float)rp;
		
		
		psdata.t[0]=(float)bo/100.0;
		psdata.t[1]=(float)go/100.0;
		psdata.t[2]=(float)ro/100.0;
	}
	//Get parameters
	image_file=argv[1];
	
	//Create window
	cvNamedWindow( "Gray", 0 );
	cvResizeWindow("Gray",320,240);
	cvMoveWindow("Gray",0,0);

	cvNamedWindow( "Color", 0 );
	cvResizeWindow("Color",320,500);
	cvMoveWindow("Color",335,0);
	
	//Create trackbar
	cvCreateTrackbar("Red Periodical","Color", &rp,10,&changeParams);
	cvCreateTrackbar("Green Periodical","Color", &gp,10,&changeParams);
	cvCreateTrackbar("Blue Periodical","Color", &bp,10,&changeParams);
	
	cvCreateTrackbar("Red 0","Color", &ro,100,&changeParams);
	cvCreateTrackbar("Green 0","Color", &go,100,&changeParams);
	cvCreateTrackbar("Blue 0","Color", &bo,100,&changeParams);
	
	//Load image
	img= cvLoadImage(image_file,0);
	//Create image result
	img_result= cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	//Generate basic table and create pseudo image

	generate_pseudocolorTable(&psdata);
	pseudocolor(img, img_result, &psdata);
	
	
	for(;;)
    	{
		int c;
		cvShowImage( "Gray", img );
		cvShowImage( "Color", img_result );
		c = cvWaitKey(10);
		if( (char) c == 's' )
			save_pseudocolor("pseudo_data.xml",&psdata);	
        	if( (char) c == 27 )
            		break;
		}
	cvDestroyWindow("Gray");
	cvDestroyWindow("Color");

	return 0;
} 

