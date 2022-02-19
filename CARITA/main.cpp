#include <winbgim.h>
#include <iostream>
#include <windows.h>
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

    setcolor(15); //LINEAS
    circle(x,y,3*e);
    circle(x,y+e/2,e/2);
    ellipse(x,y+e,180,360,2*e,e);
    line(x-e/2,y,x-(e/2)*5,y);
    line(x+e/2,y,x+(e/2)*5,y);
    ellipse(x+(e/2)*3,y,0,180,e/2,2*e);
    ellipse(x-(e/2)*3,y,0,180,e/2,2*e);

//    ellipse(x-(e/2)*3,y-e,0,360,e/4,e*0.75);
//    ellipse(x+(e/2)*3,y-e,0,360,e/4,e*0.75);
}

int main()
{
    initwindow(800,600);

    CARAFELIZPINTADA(150,300,20,3);
    CARAFELIZPINTADA(350,300,30,5);
    CARAFELIZPINTADA(600,300,40,10);

    getch();
    closegraph();
    return 1;
}
