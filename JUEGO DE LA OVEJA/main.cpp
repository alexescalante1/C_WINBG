#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <winbgim.h>
#include <cmath>

#define IZQUIERDA 97
#define DERECHA   100
#define ARRIBA    119
#define ABAJO     115
#define IZQUIERDAABAJO   122
#define IZQUIERDAARRIBA  113
#define DERECHAABAJO     120
#define DERECHAARRIBA    101


#define INTRO     13
#define ESC       27

using namespace std;

bool GAMEOVER;

string DIRECCIONES[8] = {"IZQUIERDA","DERECHA","ARRIBA","ABAJO"
                        ,"IZQUIERDA-ABAJO","IZQUIERDA-ARRIBA"
                        ,"DERECHA-ABAJO","DERECHA-ARRIBA"};

class NODO;
class EDITORDEMAPA;

int LMAYUS(int TCLA){
    if(TCLA == 65){
        return IZQUIERDA;
    }
    if(TCLA == 68){
        return DERECHA;
    }
    if(TCLA == 87){
        return ARRIBA;
    }
    if(TCLA == 83){
        return ABAJO;
    }
    return TCLA;
}

int CONCATENAR(string A,string B,char **R){int TAM=0,i=0;
    for(;A[TAM];TAM++);
    for(;B[i];i++,TAM++);TAM+=1;
    *R = new char [TAM];TAM=0;
    for(i=0;A[i];i++,TAM++){
        *(*(R)+TAM)=A[i];
    }
    for(i=0;B[i];i++,TAM++){
        *(*(R)+TAM)=B[i];
    }*(*(R)+TAM) = '\0';
    return TAM;
}

int CONVERTIR_INT_A_CAD(char **R,long long NUM){int TAM=0,i=0;
    for(long long AUX=NUM;AUX!=0;i++,AUX/=10);
    *R = new char [i];TAM=i;*(*(R)+i)='\0';i-=1;
    for(;i>=0;i--,NUM/=10){
        *(*(R)+i)=(char)(NUM%10+48);
    }
    return TAM;
}

class NODO{
    public:
    int PX,PY;
    int OCUPADO;
    bool LUGAR_SEGURO;
    NODO *SIG,*DR[8];
    NODO(int x,int y,bool LS){
        PX  = x;
        PY  = y;
        LUGAR_SEGURO = LS;
        SIG = NULL;
        OCUPADO = 0;
        for(int i=0;i<8;i++){
            DR[i] = NULL;
        }
    }
};

class EDITORDEMAPA{
    public:
    NODO *RAIZ;
    bool PLAYER,SELECCION;
    int PMOVEX[2],PMOVEY[2];
    EDITORDEMAPA(){
        RAIZ=NULL;
    }
    void INICIALIZACION(){
        PLAYER    = 0;
        SELECCION = 0;
        PMOVEX[0] = 3;
        PMOVEY[0] = 3;
        PMOVEX[1] = 3;
        PMOVEY[1] = 6;
    }
    void INSERTAR_NODO(double x,double y,bool LS){
        INS(x,y,LS,RAIZ);
    }
    void INS(double x,double y,bool LS,NODO *&R){
        if(R){
            INS(x,y,LS,R->SIG);
        }else{
            R = new NODO(x,y,LS);
        }
    }
    void DIRECCION_NODO(int xa,int ya,int xb,int yb){
//        cout<<"("<<xa<<","<<ya<<");("<<xb<<","<<yb<<")\n";
        if(xa!=xb||ya!=yb){
            if(ya==yb){
                if(xa<xb){
//                    cout<<"DERECHA\n";
                    ENLACE(xa,ya,xb,yb,1);
                    ENLACE(xb,yb,xa,ya,0);
                }else{
//                    cout<<"IZQUIERDA\n";
                    ENLACE(xa,ya,xb,yb,0);
                    ENLACE(xb,yb,xa,ya,1);
                }
            }
            if(xa==xb){
                if(ya<yb){
//                    cout<<"ARRIBA\n";
                    ENLACE(xa,ya,xb,yb,2);
                    ENLACE(xb,yb,xa,ya,3);
                }else{
//                    cout<<"ABAJO\n";
                    ENLACE(xa,ya,xb,yb,3);
                    ENLACE(xb,yb,xa,ya,2);
                }
            }
            if(xa<xb&&ya<yb){
//                cout<<"DERECHA-ARRIBA\n";
                ENLACE(xa,ya,xb,yb,7);
                ENLACE(xb,yb,xa,ya,4);
            }
            if(xa>xb&&ya>yb){
//                cout<<"IZQUIERDA-ABAJO\n";
                ENLACE(xa,ya,xb,yb,4);
                ENLACE(xb,yb,xa,ya,7);
            }
            if(xa>xb&&ya<yb){
//                cout<<"IZQUIERDA-ARRIBA\n";
                ENLACE(xa,ya,xb,yb,5);
                ENLACE(xb,yb,xa,ya,6);
            }
            if(xa<xb&&ya>yb){
//                cout<<"DERECHA-ABAJO\n";
                ENLACE(xa,ya,xb,yb,6);
                ENLACE(xb,yb,xa,ya,5);
            }
        }else{
            cout<<"PUNTO INMUTADO\n";
        }
    }

    void ENLACE(int xa,int ya,int xb,int yb,int DIR){
        E(RAIZ,xa,ya,xb,yb,DIR);
    }
    void E(NODO *R,int xa,int ya,int xb,int yb,int DIR){
        while(R){
            if(R->PX==xa&&R->PY==ya){
                F(RAIZ,xb,yb,R,DIR);
                break;
            }
            R=R->SIG;
        }
    }
    void F(NODO *R,int xb,int yb,NODO *S,int DIR){
        while(R){
            if(R->PX==xb&&R->PY==yb){
                if(!S->DR[DIR]){
                    S->DR[DIR] = R;
                }
                return;
            }
            R=R->SIG;
        }
    }

    bool KEYCONTROL(){
        SELECCION = 1; //PORQUE PLAYER ES LOBO
        while(1){

            bool MOVIMIENTOEXITOSO = 0;

            GRAFICAR(40,0,100);

            switch(LMAYUS(getch())){

                case IZQUIERDA:
                    MOVIMIENTOEXITOSO = VERIFICARMOV(PMOVEX[PLAYER],PMOVEY[PLAYER],0);
                    break;
                case DERECHA:
                    MOVIMIENTOEXITOSO = VERIFICARMOV(PMOVEX[PLAYER],PMOVEY[PLAYER],1);
                    break;
                case ARRIBA:
                    MOVIMIENTOEXITOSO = VERIFICARMOV(PMOVEX[PLAYER],PMOVEY[PLAYER],2);
                    break;
                case ABAJO:
                    MOVIMIENTOEXITOSO = VERIFICARMOV(PMOVEX[PLAYER],PMOVEY[PLAYER],3);
                    break;
                case IZQUIERDAABAJO:
                    MOVIMIENTOEXITOSO = VERIFICARMOV(PMOVEX[PLAYER],PMOVEY[PLAYER],4);
                    break;
                case IZQUIERDAARRIBA:
                    MOVIMIENTOEXITOSO = VERIFICARMOV(PMOVEX[PLAYER],PMOVEY[PLAYER],5);
                    break;
                case DERECHAABAJO:
                    MOVIMIENTOEXITOSO = VERIFICARMOV(PMOVEX[PLAYER],PMOVEY[PLAYER],6);
                    break;
                case DERECHAARRIBA:
                    MOVIMIENTOEXITOSO = VERIFICARMOV(PMOVEX[PLAYER],PMOVEY[PLAYER],7);
                    break;
                case INTRO:
                    if(SELECCION){
                        SELECCION = 0;
                    }else{
                        SELECCION = 1;
                    }

                    break;
                case ESC:
                    return 0;
            }
            if(MOVIMIENTOEXITOSO){SELECCION = 0;
                if(PLAYER){
                    PLAYER = 0;
                    SELECCION = 1; //PORQUE PLAYER ES LOBO
                }else{
                    PLAYER = 1;
                }
            }

            cleardevice();
        }
    }
    bool VERIFICARMOV(int BX,int BY,int DIRMOV){
        return VRMOV(RAIZ,BX,BY,DIRMOV);
    }
    bool VRMOV(NODO *R,int BX,int BY,int DIRMOV){NODO *AUX;
        while(R){
            if(R->PX==BX&&R->PY==BY){
                for(int i=0;i<8;i++){
                    if(R->DR[i]){
                      if(i==DIRMOV){
                        if(PLAYER==0){

                            if(R->DR[i]->OCUPADO == 2){AUX = R->DR[i];
                                if(AUX->DR[i]){
                                    if(AUX->DR[i]->OCUPADO==0){
                                        PMOVEX[PLAYER] = AUX->DR[i]->PX;PMOVEY[PLAYER] = AUX->DR[i]->PY;
                                        AUX->DR[i]->OCUPADO = PLAYER+1;
                                        R->DR[i]->OCUPADO   = 0;
                                        BUSCARNUEVAPOSANIMAL();
                                        //SELECCION
                                        R->OCUPADO          = 0;
                                        cout<<"COMIDO\n";

                                        PlaySound("OBJC.wav", NULL,SND_ASYNC);
                                        return 1;
                                    }
                                }
                            }else{
                                PMOVEX[PLAYER] = R->DR[i]->PX;PMOVEY[PLAYER] = R->DR[i]->PY;
                                R->DR[i]->OCUPADO = PLAYER+1;
                                R->OCUPADO        = 0;
                                return 1;
                            }
                        }else{
                            if(!SELECCION){
                                while(1){//RECORRE HASTA ENCONTRAR UNO
                                    if(R->DR[i]==NULL){return 0;}
                                    if(R->DR[i]->OCUPADO==2){
                                        PMOVEX[PLAYER] = R->DR[i]->PX;
                                        PMOVEY[PLAYER] = R->DR[i]->PY;
                                        return 0;
                                    }
                                    R=R->DR[i];
                                }
                            }else{
                                if(R->DR[i]->OCUPADO!=1&&R->DR[i]->OCUPADO!=2){
                                    PMOVEX[PLAYER] = R->DR[i]->PX;PMOVEY[PLAYER] = R->DR[i]->PY;
                                    R->DR[i]->OCUPADO = PLAYER+1;
                                    R->OCUPADO        = 0;
                                    return 1;
                                }
                            }
                        }
                      }
                    }
                }
            }
            R=R->SIG;
        }return 0;
    }
    bool BUSCARNUEVAPOSANIMAL(){
        return BUSQNPANIMAL(RAIZ);
    }
    bool BUSQNPANIMAL(NODO *R){
        while(R){
            if(R->OCUPADO==2){
                PMOVEX[1] = R->PX;
                PMOVEY[1] = R->PY;
                return 1;
            }
            R=R->SIG;
        }return 0;
    }
    void GRAFICAR(int LX,int LY,int e){
        GRAFMAP(RAIZ,LX,LY,e);
        GRAFOBJ(RAIZ,LX,LY,e);
    }
    void GRAFMAP(NODO *R,int LX,int LY,int e){
        while(R){
            setcolor(10);
            for(int i=0;i<8;i++){
                if(R->DR[i]){
                    setlinestyle(SOLID_LINE,1,e/25);
                    line(LX+R->PX*e,LY+R->PY*-e+750,LX+R->DR[i]->PX*e,LY+R->DR[i]->PY*-e+750);
                }
            }
            R=R->SIG;
        }
    }
    void GRAFOBJ(NODO *R,int LX,int LY,int e){
        if(SELECCION){
            setcolor(14);
        }else{
            setcolor(3);
        }
        sector(LX+PMOVEX[PLAYER]*e,LY+PMOVEY[PLAYER]*-e+750,0,360,e/4,e/4);
        while(R){
            if(R->OCUPADO==1){setcolor(15);}
            else if(R->OCUPADO==2){setcolor(5);}
            else{setcolor(10);}
            sector(LX+R->PX*e,LY+R->PY*-e+750,0,360,e/10,e/10);
            R=R->SIG;
        }
    }

    bool BUSCAR(int BX,int BY){
        return BSC(RAIZ,BX,BY);
    }

    bool BSC(NODO *R,int BX,int BY){
        while(R){
            if(R->PX==BX&&R->PY==BY){
//                for(int i=0;i<8;i++){
//                    if(R->DR[i]){
//                    cout<<DIRECCIONES[i]<<" ";
//                    }
//                }
                return 1;
            }
            R=R->SIG;
        }return 0;
    }

    bool MODIFICAR(int BX,int BY,int V){
        return MODF(RAIZ,BX,BY,V);
    }

    bool MODF(NODO *R,int BX,int BY,int V){
        while(R){
            if(R->PX==BX&&R->PY==BY){
                R->OCUPADO = V;
                return 1;
            }
            R=R->SIG;
        }return 0;
    }

    int MOSTRARNODOS(){
        return MOSN(RAIZ);
    }

    int MOSN(NODO *R){int CONT = 0;
        while(R){
//            cout<<":("<<R->PX<<","<<R->PY<<")\n";
            R=R->SIG;CONT++;
        }return CONT;
    }

}A;

void CREARGRANJA(int LX,int LY,int V){
    if(!A.BUSCAR(LX,LY)){
        A.INSERTAR_NODO(LX,LY,0);
    }
    for(int i = 1; i< V;i++){
        A.INSERTAR_NODO(LX,LY-i,1);
        A.INSERTAR_NODO(LX+i,LY-i,1);
        A.INSERTAR_NODO(LX-i,LY-i,1);

        A.DIRECCION_NODO(LX,LY-i,LX+i,LY-i);
        A.DIRECCION_NODO(LX,LY-i,LX-i,LY-i);
    }
    if(A.BUSCAR(LX,LY)){
        A.DIRECCION_NODO(LX,LY,LX,LY-1);
        A.DIRECCION_NODO(LX,LY,LX+1,LY-1);
        A.DIRECCION_NODO(LX,LY,LX-1,LY-1);
    }
    for(int i = 2; i< V;i++){
        A.DIRECCION_NODO(LX,LY-i,LX,LY-i+1);
        A.DIRECCION_NODO(LX+i,LY-i,LX+i-1,LY-i+1);
        A.DIRECCION_NODO(LX-i,LY-i,LX-i+1,LY-i+1);
    }
}

void CREARPISTA(int LX,int LY){

    A.INSERTAR_NODO(LX,LY,0);

    if(!A.BUSCAR(LX,LY+1)){A.INSERTAR_NODO(LX,LY+1,0);}
    if(!A.BUSCAR(LX,LY-1)){A.INSERTAR_NODO(LX,LY-1,0);}
    if(!A.BUSCAR(LX+1,LY)){A.INSERTAR_NODO(LX+1,LY,0);}
    if(!A.BUSCAR(LX-1,LY)){A.INSERTAR_NODO(LX-1,LY,0);}

    if(!A.BUSCAR(LX-1,LY-1)){A.INSERTAR_NODO(LX-1,LY-1,0);}
    if(!A.BUSCAR(LX-1,LY+1)){A.INSERTAR_NODO(LX-1,LY+1,0);}
    if(!A.BUSCAR(LX+1,LY-1)){A.INSERTAR_NODO(LX+1,LY-1,0);}
    if(!A.BUSCAR(LX+1,LY+1)){A.INSERTAR_NODO(LX+1,LY+1,0);}

    A.DIRECCION_NODO(LX-1,LY-1,LX,LY-1);
    A.DIRECCION_NODO(LX+1,LY-1,LX,LY-1);
    A.DIRECCION_NODO(LX,LY+1,LX+1,LY+1);
    A.DIRECCION_NODO(LX,LY+1,LX-1,LY+1);
    A.DIRECCION_NODO(LX,LY,LX+1,LY);
    A.DIRECCION_NODO(LX,LY,LX-1,LY);

    A.DIRECCION_NODO(LX,LY,LX,LY-1);
    A.DIRECCION_NODO(LX,LY,LX,LY+1);
    A.DIRECCION_NODO(LX+1,LY,LX+1,LY+1);
    A.DIRECCION_NODO(LX+1,LY,LX+1,LY-1);
    A.DIRECCION_NODO(LX-1,LY,LX-1,LY+1);
    A.DIRECCION_NODO(LX-1,LY,LX-1,LY-1);

    A.DIRECCION_NODO(LX,LY,LX-1,LY-1);
    A.DIRECCION_NODO(LX,LY,LX+1,LY+1);
    A.DIRECCION_NODO(LX,LY,LX-1,LY+1);
    A.DIRECCION_NODO(LX,LY,LX+1,LY-1);

}

int DEFINIRMAPA(){

    CREARPISTA(2,4);
    CREARPISTA(4,4);
    CREARPISTA(2,6);
    CREARPISTA(4,6);

    CREARGRANJA(3,3,3);

    A.MODIFICAR(3,3,1); //LOBO

    A.MODIFICAR(1,6,2);
    A.MODIFICAR(1,7,2);
    A.MODIFICAR(1,5,2);

    A.MODIFICAR(2,6,2);
    A.MODIFICAR(2,7,2);

    A.MODIFICAR(3,6,2);
    A.MODIFICAR(3,7,2);

    A.MODIFICAR(4,6,2);
    A.MODIFICAR(4,7,2);

    A.MODIFICAR(5,6,2);
    A.MODIFICAR(5,7,2);
    A.MODIFICAR(5,5,2);

//    A.MODIFICAR(3,4,2);
//    A.MODIFICAR(2,4,2);

//    cout<<"\n";
//    cout<<"\n";
//    A.BUSCAR(5,1);
//    cout<<"\n";
//    cout<<"\n";
//    cout<<"\nCANTIDA DE NODOS: "<<A.MOSTRARNODOS();
    return 0;
}

int main(){

    DEFINIRMAPA();
    A.INICIALIZACION();

    initwindow(720,720);

    while(A.KEYCONTROL()){

        switch(getch()){
            case ESC:
                closegraph();
                return 0;
            default:
                cleardevice();
                A.INICIALIZACION();
        }
    }
}
