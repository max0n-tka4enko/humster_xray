#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <strings.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


//convert RGB to gray picture (to one-channel image)
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




void dfs(int v, int color, int iw, int ih, int* col, unsigned char* mat) {
  //TODO Найти компоненты связности в  графе при помощи поиска в глубину
}


int main() {
    // строка, путь к файлу
    char* inputPath = "hamster.png";
    int iw, ih, n; //ширина, высота и количество цветовых каналов
    int i, j, k;

    // Загружаем изображение, чтобы получить информацию о ширине, высоте и цветовом канале
    unsigned char *input_image = stbi_load(inputPath, &iw, &ih, &n, 0);
    if (input_image == NULL) {
        printf("ERROR: can't read file %s\n", inputPath );
        return 0;
    }
    
    unsigned char* data = (unsigned char*)malloc(ih*iw*sizeof(unsigned char));
    if (data == NULL) {
            printf("Memory allocation error at main()" );
            return 0;
        }

    go_to_mono(input_image, data, iw, ih, n);

    int black = 100;
    int white = 160;
    high_contrast(data, iw, ih, black, white);


    
    
    /*
    // Implement these functions yourself if need!
    MyImage = bw_gauss(MyImage, iw, ih, t_black, t_white);
    MyImage = bw_sobel(MyImage, iw, ih, t_black, t_white);
    */
    
    /*
     Let's colorize different connectivity components on the picture
    */
    /*int col[iw*ih];
    for (i = 0; i < iw*ih; i++) { 
        col[i] = 0;
    }
    k = 55;
    //dfs making
    for (i = 0; i < iw*ih; i++) {
        if (col[i] == 0) {
            dfs(i, k, iw, ih, col, newImage);
            k = k + 50;
        }
    }
    
    //now have to color the colors from col
    for (i = 0; i < iw*ih; i++) {
        odata[i*n] = 78+col[i]+0.5*col[i-1];
        odata[i*n+1] = 46+col[i];
        odata[i*n+2] = 153+col[i];
        if (n == 4) odata[i*n+3] = 255;
    }
    */


    char* outputPath = "output.png";
    stbi_write_png(outputPath, iw, ih, 1, data, 0);
    free(data);
    stbi_image_free(input_image);
    return 0;
}