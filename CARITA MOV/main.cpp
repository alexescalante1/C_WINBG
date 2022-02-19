#include <winbgim.h>
#include <iostream>
#include <windows.h>

#define IZQUIERDA 97
#define DERECHA   100
#define ENTER     13

using namespace std;

void CARAFELIZPINTADA(int x, int y, int e,int color){
    setcolor(color);
    sector(x,y,0,360,3*e,3*e);
    setcolor(15);
    sector(x-(e/2)*3,y,0,180,e/2,2*e);
    sector(x+(e/2)*3,y,0,180,e/2,2*e);

    setcolor(4);
    sector(x,y+e/2,0,360,e/2,e/2);
    setcolor(0);
    sector(x-(e/2)*3,y-e,0,360,e/4,e*0.75);
    sector(x+(e/2)*3,y-e,0,360,e/4,e*0.75);

    setcolor(15);
    circle(x,y,3*e);
    circle(x,y+e/2,e/2);
    ellipse(x,y+e,180,360,2*e,e);
    line(x-e/2,y,x-(e/2)*5,y);
    line(x+e/2,y,x+(e/2)*5,y);
    ellipse(x+(e/2)*3,y,0,180,e/2,2*e);
    ellipse(x-(e/2)*3,y,0,180,e/2,2*e);
}

int main()
{
    initwindow(800,600);

    int KEY=0,DIR = 0,i=0;

    while(KEY!=27){
        CARAFELIZPINTADA(i+150,300,20,3);
        if(kbhit()){
            KEY=getch();
            if(KEY == IZQUIERDA){
                DIR = 0;
            }else if(KEY == DERECHA){
                DIR = 1;
            }
            else if(KEY == ENTER){
                if(DIR == 0){
                    DIR = 1;
                }else{
                    DIR = 0;
                }
            }
        }else{
            if(DIR == 0){
                i--;
            }else{
                i++;
            }
        }
        delay(10);
        cleardevice();
    }
    closegraph();
    return 1;
}
