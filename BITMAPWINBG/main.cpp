#include <iostream>
#include <fstream>
#include <winbgim.h>

using namespace std;

int ***ReadBMP(char* filename,int *width,int *height)
{
        int ***IMAGENMATRIZ;
       FILE* f = fopen(filename, "rb");

       if(f == NULL)
           throw "Argument Exception";

       unsigned char info[54];
       fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

       // extract image height and width from header
       *width = *(int*)&info[18];
       *height = *(int*)&info[22];

        IMAGENMATRIZ = new int **[*width];
        for(int i=0;i<*width;i++){
            IMAGENMATRIZ[i] = new int*[*height];
        }
        for(int i=0;i<*width;i++){
            for(int j=0;j<*height;j++){
                IMAGENMATRIZ[i][j] = new int[3];
            }
        }

       int row_padded = (*width*3 + 3) & (~3);
       unsigned char* data = new unsigned char[row_padded];
       unsigned char tmp;
       int k = 0;

       for(int i = 0; i < *height; i++)
       {
           fread(data, sizeof(unsigned char), row_padded, f);
           for(int j = 0,m = 0 ; j < *width*3; j += 3 , k += 3,m++)
           {
               // Convert (B, G, R) to (R, G, B)

               tmp = data[j];
               data[j] = data[j+2];
               data[j+2] = tmp;
                IMAGENMATRIZ[m][i][0] = (int)data[j];
                IMAGENMATRIZ[m][i][1] = (int)data[j+1];
                IMAGENMATRIZ[m][i][2] = (int)data[j+2];

//               cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< endl;
           }
       }

       fclose(f);
       return IMAGENMATRIZ;
}

void MARIOSORPRESA(int x,int y,int e,int color){

    setfillstyle(1,COLOR(255,150,0));//CUBO BASE
    bar(x-6*e,y-6*e,x+6*e,y+6*e);

    setfillstyle(1,COLOR(255,100,0));//BORDE NARANJA
    bar(x-6*e,y-7*e,x+6*e,y-6*e);
    bar(x-7*e,y-6*e,x-6*e,y+6*e);

    setfillstyle(1,COLOR(80,80,80));//BORDE NEGRO
    bar(x-7*e,y+7*e,x+6*e,y+6*e);
    bar(x+7*e,y-6*e,x+6*e,y+7*e);

    setfillstyle(1,COLOR(0,0,0));//PUNTOS
    bar(x-5*e,y-5*e,x-4*e,y-4*e);
    bar(x+5*e,y+5*e,x+4*e,y+4*e);
    bar(x+5*e,y-5*e,x+4*e,y-4*e);
    bar(x-5*e,y+5*e,x-4*e,y+4*e);

    setfillstyle(1,COLOR(0,0,0));//PREGUNTA SOMBRA
    bar(x-e*1.5,y-4*e,x,y-e);
    bar(x,y-e*3,x+e*2.5,y-e*2);
    bar(x+e*1.5,y-e*2,x+e*3.2,y+e*0.75);
    bar(x,y,x+e*1.5,y+e*2);
    bar(x,y+e*2.5,x+e*1.5,y+e*4);

    setfillstyle(1,COLOR(255,100,0));//PREGUNTA
    bar(x,y-e,x+e*2.5,y);
    bar(x+e,y,x+e*2.5,y-3*e);
    bar(x-e*1.5,y-4*e,x+2*e,y-3*e);
    bar(x-2*e,y-3*e,x-e*0.75,y-e*1.5);

    bar(x-e*0.75,y,x+e*0.75,y+1.5*e);
    bar(x-e*0.75,y+e*2,x+e*0.75,y+3.5*e);
}

void PINTARIMAGEN(int ***IMAGENMATRIZ,int xi,int yi,int xf,int yf,int increx,int increy){
    xi=-30;
    for(int i = 30; i < xf ; i+=increx)
    {

           for(int j = yi; j < yf; j+=increy)
           {

                putpixel(i+xi,yf-j-1,COLOR(IMAGENMATRIZ[i][j][0],IMAGENMATRIZ[i][j][1],IMAGENMATRIZ[i][j][2]));
//                setfillstyle(1,COLOR(IMAGENMATRIZ[i][j][0],IMAGENMATRIZ[i][j][1],IMAGENMATRIZ[i][j][2]));
//                bar(i+xi,yf-j,i+increx,yf-j+increy);

           }

    }
}

int main(){

    initwindow(1250,720);

    MARIOSORPRESA(100,400,5,14);

    char FILEIMG[] = "IMG.bmp";
    int ***IMAGENMATRIZ;
    int alto, ancho;
    IMAGENMATRIZ=ReadBMP(FILEIMG,&alto,&ancho);

    PINTARIMAGEN(IMAGENMATRIZ,0,0,alto,ancho,10,10);
    PINTARIMAGEN(IMAGENMATRIZ,0,0,alto,ancho,5,5);
    PINTARIMAGEN(IMAGENMATRIZ,0,0,alto,ancho,3,3);
    PINTARIMAGEN(IMAGENMATRIZ,0,0,alto,ancho,2,2);
//    PINTARIMAGEN(IMAGENMATRIZ,0,0,alto,ancho,1,1);

    getch();
    closegraph();
    return 0;
}
