#include <conio.h>
#include <iostream>
#include <winbgim.h>
#include <math.h>
#include <time.h>

using namespace std;
int ancho=50;

void dib_muro(int x,int y,int color){
    setcolor(color);
    rectangle(x+1,y+1,x+ancho-1,y+ancho-1);
}
void dib_personita(int x,int y,int color){
    setcolor(color);
    circle(x+ancho/2,y+ancho/2,ancho/2-1);
}
void borrar(int x,int y){
    setcolor(0);
    rectangle(x,y,x+ancho,y+ancho);
    circle(x+ancho/2,y+ancho/2,ancho/2-1);
}
void dib_matriz(int x,int y,int mat[10][10]){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(mat[i][j]==0){
                borrar(x+ancho*j,y+ancho*i);
            }
            if(mat[i][j]==1){
                dib_muro(x+ancho*j,y+ancho*i,14);
            }
            if(mat[i][j]==2){
                dib_personita(x+ancho*j,y+ancho*i,3);
            }
        }
    }
}

int main(){
    int iPer=3;
    int jPer=5;

    int iMur=0;
    int jMur=0;

    int salir=false;
    int tecla;
    int cont=0;
    char cadena[100];
    int mat[10][10]={
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1,0,1},
        {1,0,0,0,1,0,0,1,0,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,1,1,1,0,0,1,1,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,0,0,0,0,0,1,0,1},
        {1,1,1,1,1,1,1,1,1,1},
    };
    initwindow(800,600);
    mat[iPer][jPer]=2;
    dib_matriz(20,20,mat);
    srand(time(NULL));//time.h
    while(!salir){ //salir==false
        tecla=getch();
        cont++;
        if(cont%10==0){
            while(1){
                iMur=rand()%10;
                jMur=rand()%10;
                if(mat[iMur][jMur]==0 || mat[iMur][jMur]==2){
                    break;
                }
            }
            mat[iMur][jMur]=1;
        }
        if(tecla==72){//arriba
            if(mat[iPer-1][jPer]==0){
                mat[iPer][jPer]=0;
                iPer--;
                mat[iPer][jPer]=2;
            }
        }
        if(tecla==80){//arriba
            if(mat[iPer+1][jPer]==0){
                mat[iPer][jPer]=0;
                iPer++;
                mat[iPer][jPer]=2;
            }
        }
        if(tecla==75){//izquierda
            if(mat[iPer][jPer-1]==0){
                mat[iPer][jPer]=0;
                jPer--;
                mat[iPer][jPer]=2;
            }
        }
        if(tecla==77){//derecha
            if(mat[iPer][jPer+1]==0){
                mat[iPer][jPer]=0;
                jPer++;
                mat[iPer][jPer]=2;
            }
        }
        if(iPer==iMur && jPer==jMur){
//            sprintf(cadena,"PERDISTE: %d");
        }
        dib_matriz(20,20,mat);
//        sprintf(cadena,"CONTADOR: %d",cont);
        outtextxy(10,10,cadena);
    }

    getch();
}
