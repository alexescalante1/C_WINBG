#include <conio.h>
#include <iostream>
#include <winbgim.h>
using namespace std;
/*************************/
class Circulo{
    private:
        double x,y;
        int color;
        int radio;
        double BOCA_INIT,BOCA_FIN,BOCA_LAPSO;
        bool BOCA,BOCA_DIR;
    public:
        Circulo(int px,int py,int RD){
            x=px;
            y=py;
            radio=RD;
            BOCA_LAPSO = 50;
            BOCA_INIT = 310;
            BOCA_FIN = 50;
            BOCA = 0;
            BOCA_DIR = 1;
            color=14;
        }
        void dibujar(){

            setcolor(color);
            sector(x,y,BOCA_FIN+1,BOCA_INIT+1,radio,radio);
            setcolor(0);
            if(BOCA_DIR){
                sector(x+5,y-17,0,360,4,4);
            }else{
                sector(x-5,y-17,0,360,4,4);
            }
            if(BOCA){
                BOCA_FIN++;
                BOCA_INIT--;
                BOCA_LAPSO--;

                if(BOCA_LAPSO<2){
                    BOCA = 0;
                    BOCA_LAPSO = 50;
                }
            }else{
                BOCA_FIN--;
                BOCA_INIT++;
                BOCA_LAPSO--;

                if(BOCA_LAPSO<2){
                    BOCA = 1;
                    BOCA_LAPSO = 50;
                }
            }
            sector(x,y,BOCA_INIT,BOCA_FIN,radio,radio);
        }
        void borrar(){
            setcolor(0);
            setlinestyle(SOLID_LINE,1,4);
            circle(x,y,radio+3);
        }
        void setX(int XX){
            x = XX;
        }
        void setRadio(int r){
            radio=r;
        }
        void setDir(bool BC_DIR){
            BOCA_DIR = BC_DIR;
            if(BC_DIR){
                BOCA_INIT = 310;
                BOCA_FIN = 50;
            }else{
                BOCA_INIT = 130;
                BOCA_FIN = 230;
            }
            BOCA_LAPSO = 50;
            BOCA = 0;
        }
        void Avanzar(double Xv,double Yv){
            x = Xv;
            y = Yv;
        }
        int getX(){
            return x;
        }
        bool getBOCA_DIR(){
            return BOCA_DIR;
        }
};
int main(){
    initwindow(1200,800);

    double MOV_X = 350,MOV_Y = 300;
    int DIR = 1;
    Circulo a(MOV_X,MOV_Y,30);

    while(1){
        a.dibujar();
        delay(1);
        a.borrar();

        if(DIR == 0){
            MOV_X-=3;
        }else if(DIR == 1){
            MOV_X+=3;
        }else if(DIR == 2){
            MOV_Y-=3;
        }else if(DIR == 3){
            MOV_Y+=3;
        }

        a.Avanzar(MOV_X,MOV_Y);

        if(kbhit()){
            int tecla=getch();
            if(tecla == 97){
                DIR = 0;
                if(a.getBOCA_DIR()!=0){
                    a.setDir(0);
                }
            }else if(tecla == 100){
                DIR = 1;
                if(a.getBOCA_DIR()!=1){
                    a.setDir(1);
                }
            }else if(tecla == 119){
                DIR = 2;
            }else if(tecla == 115){
                DIR = 3;
            }
        }
    }
    return 1;
}
