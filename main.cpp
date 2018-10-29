#include <iostream>
#include <math.h>
#include "psnrLib.h"
using namespace std;
/**

 / \ / \ / \ / \ / \ / \ / \ / \ / \    / \ / \   / \ / \ / \ / \
( F | U | R | K | A | N | C | A | N )  ( B | . ) ( Y | U | C | E )
 \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/    \_/ \_/   \_/ \_/ \_/ \_/

            THIS PROJECT CAN BE USED AS A REFERANCE

**/
int main(int argc, char* argv[])
{
    //if(argc!=6){cout<< "\n***NOT ENOUGH INPUT ARGUMENTS!***\n";return 0;}
    /*PROGRAM.exe   file1.yuv   file2.yuv   width      height     chroma_subsampling*/
    /*ARGV[0]       ARGV[1]     ARGV[2]     ARGV[3]    ARGV[4]    ARGV[5]           */

    char ORG_FILENAME[50]    = "";  //FIRST FILE TO COMPARE
    char BLUR_FILENAME[50]   = "";  //SECOND FILE TO COMPARE
    strcat(ORG_FILENAME,argv[1]);
    strcat(BLUR_FILENAME,argv[2]);

    int  WIDTH               = atoi(argv[3]); // WIDTH OF FILE (YUV)
    int  HEIGHT              = atoi(argv[4]); // HEIGHT OF FILE (YUV)
    int  CHROMA_SUBSAMPLING  = atoi(argv[5]); // CHROMASUBSAMPLING MODE


    long int size_of_file;              // SIZE OF FILE AS BYTE
    int frame_number;                   // FRAME NUMBER OF YUV VIDEO
    uint8_t *ORG_buffer     = nullptr;  // BUFFER TO BE USED AS STORE DATA OF FIRST FILE
    uint8_t *BLUR_buffer    = nullptr;  // BUFFER TO BE USED AS STORE DATA OF SECOND FILE
    FILE* original_yuv_file;

    double *f_sizes = format_detector(CHROMA_SUBSAMPLING);
    double fwidth   = f_sizes[0];
    double fheight  = f_sizes[1];

    original_yuv_file   = fopen(ORG_FILENAME,"rb");

    size_of_file = filesize(original_yuv_file);
    frame_number = size_of_file / (WIDTH*HEIGHT*(1+2*fwidth*fheight));

    ORG_buffer = (uint8_t* )malloc(size_of_file+1);
    BLUR_buffer = (uint8_t* )malloc(size_of_file+1);

    readtoBuffer(ORG_buffer,ORG_FILENAME,size_of_file);
    readtoBuffer(BLUR_buffer,BLUR_FILENAME,size_of_file);

    cout<<endl<<"*************************************"<<endl;
    cout << "Size of file      : "<<size_of_file<<endl;
    cout << "Chroma Subsampling: "<<argv[5]<<endl;
    cout << "Frame Number      : "<< frame_number<<endl;
    cout<<endl<<"*************************************"<<endl;

    compareAndPrint(ORG_buffer,BLUR_buffer,WIDTH,HEIGHT, frame_number);

	return 0;
}
