#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <strings.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


void go_to_mono(unsigned char* image, unsigned char* data, int sizeW, int sizeH, int n) {
    int size = sizeW * sizeH * n;
    int k = 0;
    for (int i = 0; i < size; i +=  n) {
        data[k] = 0.299*image[i] + 0.587*image[i + 1] + 0.114*image[i + 2];
        k++;
    }

}

void high_contrast(unsigned char* data, int sizeW, int sizeH, int black, int white) {
    for (int i = 2; i < sizeH-1; i++) {
        for (int j = 2; j < sizeW-1; j++) {
            if (data[sizeW*i+j] < black) 
                data[sizeW*i+j] = 0;
            if (data[sizeW*i+j] > white) 
                data[sizeW*i+j] = 255;
        }
    }
}

void MEGA_ULTRA_HARD_INCREDIBLE_DFS(int i, int j, int w, int h, unsigned char* data, int* v, int num){
    v[w*i+j] = num;
    if((i>=1) && (i<=h-1) && (j-2>=1) && (j-2<=w-1))
        if((abs(data[w*i+j]-data[w*i+(j-2)]) <= 60) && (v[w*i+(j-2)] == 0))
            MEGA_ULTRA_HARD_INCREDIBLE_DFS(i, j-2, w, h, data, v, num);
        
    if((i-2>=1) && (i-2<=h-1) && (j+1>=1) && (j+1<=w-1))
        if((abs(data[w*i+j]-data[w*(i-2)+(j+1)]) <= 60) && (v[w*(i-2)+(j+1)] == 0))
            MEGA_ULTRA_HARD_INCREDIBLE_DFS(i-2, j+1, w, h, data, v, num);
    
    if((i+1>=1) && (i+1<=h-1) && (j+1>=1) && (j+1<=w-1))
        if((abs(data[w*i+j]-data[w*(i-2)+(j+1)]) <= 60) && (v[w*(i-2)+(j+1)] == 0))
            MEGA_ULTRA_HARD_INCREDIBLE_DFS(i-2, j+1, w, h, data, v, num);

    
    if((i+2>=1) && (i+2<=h-1) && (j+1>=1) && (j+1<=w-1))
        if((abs(data[w*i+j]-data[w*(i+2)+(j+1)]) <= 60) && (v[w*(i+2)+(j+1)] == 0))
            MEGA_ULTRA_HARD_INCREDIBLE_DFS(i+2, j+1, w, h, data, v, num);
}


int main() {
    char* inputPath = "hamster.png";
    int iw, ih, n; //width, height and number of channels of image
    int i=0, j=0, k=0, num=0;

    //load image and get information of it
    unsigned char *input_image = stbi_load(inputPath, &iw, &ih, &n, 0);
    if (input_image == NULL) {
        printf("ERROR: can't read file %s\n", inputPath );
        return 0;
    }
    
    unsigned char* data = (unsigned char*)malloc(ih*iw*sizeof(unsigned char));
    int* vertexes = (int*) malloc(iw*ih*sizeof(int));
    if (data == NULL || vertexes == NULL) {
            printf("Memory allocation error at main()" );
            return 0;
        }
    //convert RGB to gray picture (to one-channel image) 
    go_to_mono(input_image, data, iw, ih, n);
    //raise contrast
    int black = 100;
    int white = 150;
    high_contrast(data, iw, ih, black, white);

    //array of vertexes with color-codes
    for(i=0;i<iw*ih;i++)
        vertexes[i] = 0;

    //make DFS
    for (i=1;i<=ih-1;i++){
        for (j=1;j<=iw-1;j++){
            if(vertexes[iw*i+j]==0){
                num++;
                MEGA_ULTRA_HARD_INCREDIBLE_DFS(i, j, iw, ih, data, vertexes, num);
            }
        }
    } 

    //color to RGB 
    unsigned char* odata=(unsigned char*)malloc(iw*ih*n*sizeof(unsigned char));
    int c;
    for (i = 0; i < ih*iw*n; i += n){ 
        c = vertexes[k]%50 + vertexes[k]%15;
        odata[i] = 3*c - 25;
        odata[i+1] = 4*c + 40;
        odata[i+2] = 5*c + 50;
        odata[i+3] = 255;
        k++;  
    }


    char* outputPath = "output.png";
    stbi_write_png(outputPath, iw, ih, n, odata, 0);
    free(data);
    stbi_image_free(input_image);
    return 0;
}