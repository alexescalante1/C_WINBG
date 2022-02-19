#include <conio.h>
#include <iostream>
#include <winbgim.h>
#include <math.h>
#include <ctime>

#define PI 3.141516

using namespace std;

struct Punto{
    float X,Y;
};

class Manecilla{
    private:
        Punto P1,P2;
        int Radio,Grosor,Color;
    public:
        void SetRadioGrosorColor(int R,int G,int C){
            Radio = R;
            Grosor = G;
            Color = C;
        }
        void SetPuntoInicial(float X,float Y){
            P1.X = X;
            P1.Y = Y;
        }
        void DefinePuntFinal(int alfa){
            P2.X = P1.X+Radio*cos(alfa*PI/180);
            P2.Y = P1.Y+Radio*sin(alfa*PI/180);
        }
        void Graficar(){
            setcolor(Color);
            setlinestyle(SOLID_LINE,1,Grosor);
            line(P1.X,P1.Y,P2.X,P2.Y);
        }
};

class Reloj{
    private:
        Manecilla Hora,Minuto,Segundo;
        float X,Y,R;
    public:
        Reloj(float Px,float Py,float Rad){
            Hora.SetRadioGrosorColor(Rad*0.5,Rad*0.04,12);
            Hora.SetPuntoInicial(Px,Py);
            Minuto.SetRadioGrosorColor(Rad*0.7,Rad*0.02,10);
            Minuto.SetPuntoInicial(Px,Py);
            Segundo.SetRadioGrosorColor(Rad*0.86,Rad*0.01,15);
            Segundo.SetPuntoInicial(Px,Py);
            X = Px;
            Y = Py;
            R = Rad;
        }

        void HoraActual(){
            time_t now = time(0);
            tm *time = localtime(&now);
            int Hra = time->tm_hour;
            int Min = time->tm_min;
            int Seg = time->tm_sec;
            Hora.DefinePuntFinal((Hra*30+Min/2)-90);
            Minuto.DefinePuntFinal((Min*6)-90);
            Segundo.DefinePuntFinal((Seg*6)-90);
        }

        void GraficarFondo(){
            setlinestyle(SOLID_LINE,1,R*0.02);
            for(int i = 0; i < 360; i+=6){
                if(i%30){
                    setcolor(10);
                    line(X+R*0.95*cos(i*PI/180),Y+R*0.95*sin(i*PI/180),X+R*cos(i*PI/180),Y+R*sin(i*PI/180));
                }else{
                    setcolor(15);
                    line(X+R*0.9*cos(i*PI/180),Y+R*0.9*sin(i*PI/180),X+R*cos(i*PI/180),Y+R*sin(i*PI/180));
                }
            }
            setlinestyle(SOLID_LINE,1,R*0.035);
            circle(X,Y,R);
        }

        void Graficar(){
            GraficarFondo();
            HoraActual();
            Segundo.Graficar();
            Minuto.Graficar();
            Hora.Graficar();
        }

};

int main(){
    initwindow(1050,800);

    Reloj R1(700,400,300);
    Reloj R2(200,600,100);
    Reloj R3(200,300,50);
    Reloj R4(200,100,20);

    while(!kbhit()){
        R1.Graficar();
        R2.Graficar();
        R3.Graficar();
        R4.Graficar();

        settextstyle(2, HORIZ_DIR, 15);
        outtextxy(540,20,"BY ALEX ESCALANTE");

        delay(100);
        cleardevice();
    }

    closegraph();
    return 1;
}
