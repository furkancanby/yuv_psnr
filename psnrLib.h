#ifndef _PSNRLIB_H_
#define _PSNRLIB_H_

#include <iostream>
#include <string.h>
#include <math.h>
#include <iomanip>

using namespace std;

/**

 / \ / \ / \ / \ / \ / \ / \ / \ / \    / \ / \   / \ / \ / \ / \
( F | U | R | K | A | N | C | A | N )  ( B | . ) ( Y | U | C | E )
 \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/    \_/ \_/   \_/ \_/ \_/ \_/

            THIS PROJECT CAN BE USED AS A REFERANCE

**/

/** THIS FUNCTION DETECT CHROMA SUBSAMPLING MODE
    RETURNS F_WIDTH AND F_HEIGHT VALUES OF CURRENT FORMAT */
double* format_detector(int format){
    static double returnedvalue[2];
    if     (format==400){returnedvalue[0] =  0.0; returnedvalue[1] = 0.0; return returnedvalue;}
    else if(format==411){returnedvalue[0] = 0.25; returnedvalue[1] = 1.0; return returnedvalue;}
    else if(format==420){returnedvalue[0] =  0.5; returnedvalue[1] = 0.5; return returnedvalue;}
    else if(format==422){returnedvalue[0] =  0.5; returnedvalue[1] = 1.0; return returnedvalue;}
    else if(format==444){returnedvalue[0] =  1.0; returnedvalue[1] = 1.0; return returnedvalue;}
    else{                returnedvalue[0] =  1.0; returnedvalue[1] = 1.0; return returnedvalue;}
}

/** THIS FUNCTION RETURNS FILE SIZE AS BYTES*/
long int filesize(FILE *File){
    fseek (File, 0, SEEK_END);   // Sets the position indicator to end of file.
    long int size_of_file = ftell(File);
    fclose(File);
    return size_of_file;
}

/** THIS FUNTION STORES DATA OF FILE TO A BUFFER AS BINARY*/
void readtoBuffer(uint8_t *buffer,char filename[50],long int size_of_file){
    FILE* file;
    file = fopen(filename,"rb");
    fread(buffer,size_of_file,1,file);
    fclose(file);
}

/** THIS FUNCTION CAN BE USED TO WRITE A YUV FILE*/
void writeAsYUV(uint8_t* buffer, char filename[50],long int size_of_file){
    FILE* writable;
    writable = fopen(filename,"wb");
    fseek (writable, 0, SEEK_SET);
	for(int i=0;i<size_of_file;i++){
        fwrite(&buffer[i],1,1,writable);
	}
    fclose(writable);
}

/** THIS FUNCTION COMPARES 2 YUV FILES AND PRINTS TEST RESULTS */
void compareAndPrint(uint8_t* ORG_buffer,uint8_t* BLUR_buffer,int Width,int Height, int frame_number){


    int pos=0;                  // POSITION OF FILE POINTER
    double PSNR;
    double AVERAGE_LUM = 0.0;   // AVERAGE LUM PSNR
    double AVERAGE_CB  = 0.0;   // AVERAGE CB  PSNR
    double AVERAGE_CR  = 0.0;   // AVERAGE CR  PSNR

    for(int n=0;n<frame_number;n++){
        cout<<endl;

        double SUM=0.0;
        int i=0;

        /********OPERATIONS FOR Y LAYER**********/
        for(i=0;i<Width*Height*1;i++){
                double diff = (double)((int)ORG_buffer[i+pos]-(int)BLUR_buffer[i+pos]);
                SUM = SUM + (diff*diff);
        }
        SUM = SUM / (Width*Height); // MEAN SQUARED ERROR VALUE
        pos=pos+i;
        PSNR = 10*log10((255*255)/SUM );
        AVERAGE_LUM+=PSNR;
        cout <<setw(4)<<n<<"(th)Frame --> Y-PSNR:  "<< fixed<<setprecision(2)<<PSNR<<" dB";

        /********OPERATIONS FOR U LAYER**********/
        SUM=0.0;
        for(i=0;i<Width*Height*0.25;i++){
                double diff = (double)((int)ORG_buffer[i+pos]-(int)BLUR_buffer[i+pos]);
                SUM = SUM + (diff*diff);
        }
        SUM = SUM / (Width*Height*0.25);
        pos=pos+i;
        PSNR = 10*log10((255*255)/SUM );
        AVERAGE_CB+=PSNR;
        cout <<"  U-PSNR:"<< fixed<<setprecision(2)<<PSNR<<" dB";;


        /********OPERATIONS FOR V LAYER**********/
        SUM=0.0;
        for(i=0;i<Width*Height*0.25;i++){
                double diff = (double)((int)ORG_buffer[i+pos]-(int)BLUR_buffer[i+pos]);
                SUM = SUM + (diff*diff);
        }
        SUM = SUM / (Width*Height*0.25);
        pos=pos+i;
        PSNR = 10*log10((255*255)/SUM );
        AVERAGE_CR+=PSNR;
        cout <<"  V-PSNR:"<< fixed<<setprecision(2)<<PSNR<<" dB";
    }

    cout<<endl<<"*************************************"<<endl;
    cout<<endl<<"AVERAGE LUM PSNR: "<<AVERAGE_LUM/112;
    cout<<endl<<"AVERAGE CB  PSNR: "<<AVERAGE_CB/112;
    cout<<endl<<"AVERAGE CR  PSNR: "<<AVERAGE_CR/112;
    cout<<endl<<"*************************************"<<endl;
}

#endif
