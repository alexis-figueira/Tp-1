#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include "Funciones.h"
#include "estructuras.h"
#include "menu.h"
#include "interfaz.h"
const int tam_formato = 40, alto_formato=25 ;



void initUI() {

    system("mode con: cols=40 lines=25");
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    setlocale(LC_ALL, "spanish");

}

void func_hora(){
    time_t tiempo;
    char cad[80];
    struct tm *tmPtr;

    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);

    printf("FECHA ACTUAL \n%d/%d/%d %d:%d:%d", tmPtr->tm_mday, tmPtr->tm_mon+1, 1900+tmPtr->tm_year, tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec);
    strftime(cad, 80, "%A %d de %B de %Y", tmPtr);
    printf("\n\n%s", cad);

    ///       tmPtr->tm_mday // dia
    ///       tmPtr->tm_mon+1 // mes
    ///       1900+tmPtr->tm_year // anio
    ///       tmPtr->tm_hour // hora
    ///       tmPtr->tm_min // min
    ///       tmPtr->tm_sec // seg


}

void borrar_restopantalla(int y){
    int xx=tam_formato, yy=alto_formato;
    int a, b ;
    for (a=0; a<xx; a++){
        for (b=y ; b<yy ; b++){
            gotoxy (a,b);
            cout << " " ;
        }
    }
    gotoxy (1,y);
}

void borrar_restorenglon(int x, int y){
    int i ;
    for (i=x ; i<tam_formato; i++){
        gotoxy(i, y);
        cout << " " ;
    }
    gotoxy(x,y);
}

void borrar_renglon(int y){
    int x ;
    for (x=1 ; x<=tam_formato; x++){
        gotoxy(x, y);
        cout << " " ;
    }
    gotoxy(1,y);
}

void devolucion(const char * msj, const char *color, int ancho, int renglon){
    const char *rojo = "ROJO", *azul = "AZUL", *verde="VERDE" ;
    int tam ;
    {
        guiones (ancho,renglon-1);
    }


    gotoxy (1,renglon);
    if (strcmp(color, rojo) == 0 ){
        setBackgroundColor(RED);
    }else {
        if (strcmp(color, azul)==0){
            setBackgroundColor(BLUE);
        }else {
            if(strcmp(color, verde)==0){
                setBackgroundColor(GREEN);
            }else {
                cout << "color invalido" << endl ;
            }
        }
    }
    int x ;
    for (x=1 ; x<=ancho ; x++){
        gotoxy (x,renglon);
        cout << " " ;
    }
    tam =strlen (msj);
    tam = (ancho-tam)/2;
    gotoxy (tam,renglon);
    cout << msj;
    setBackgroundColor(BLACK);
}

void titulo(const char * msj, int ancho){
    setBackgroundColor(BLUE);
    int x, pos , tam;
    for (x=1 ; x<=ancho ; x++){
        gotoxy (x,1);
        cout << " " ;
    }
    tam= strlen (msj);
    pos =(ancho-tam)/2 ;
    gotoxy (pos,1);
    cout << msj ;
    setBackgroundColor(BLACK);
    cout << endl ;
}

void guiones(int ancho){
    int x;
    for (x=1 ; x <=ancho ; x++ ){
        cout << "-" ;
    }
    cout << endl ;
}

void guiones(int ancho, int renglon){
    gotoxy(1,renglon);
    int x;
    for (x=1 ; x <=ancho ; x++ ){
        cout << "-" ;
    }
    cout << endl ;
}

void msj (const char *m, int ubicacion , int ancho){
    int x, pos , tam;
    switch (ubicacion){
    case 1 :
        cout << m ;
        break ;
    case 2 :
        tam = strlen (m);
        pos =(ancho-tam)/2 ;
        for (x=1 ; x<pos ; x++){
        cout << " " ;
        }
        cout << m ;
        break;
    case 3 :
        tam = strlen (m);
        pos = (ancho-tam);
        for (x=1 ; x<pos ; x++){
        cout << " " ;
        }
        cout << m ;
        break;
    }
}

void msj (const char *m, int ubicacion , int ancho, const char* color){
    int x, pos , tam;
    const char *rojo = "ROJO", *azul = "AZUL", *verde="VERDE" ;
    if (strcmp(color, rojo) == 0 ){
        setBackgroundColor(RED);
    }else {
        if (strcmp(color, azul)==0){
            setBackgroundColor(BLUE);
        }else {
            if(strcmp(color, verde)==0){
                setBackgroundColor(GREEN);
            }else {
                cout << "color invalido" << endl ;
            }
        }
    }
    tam = strlen (m);
    switch (ubicacion){
    case 1 :
        cout << m ;
        for (x=tam ; x<tam_formato; x++){
            cout << " ";
        }
        break ;
    case 2 :
        pos =(ancho-tam)/2 ;
        for (x=1 ; x<pos ; x++){
        cout << " " ;
        }
        cout << m ;
        for (x=pos+tam;x<=tam_formato;x++){
            cout << " " ;
        }



        break;
    case 3 :
        pos = (ancho-tam);
        for (x=1 ; x<=pos ; x++){
        cout << " " ;
        }
        cout << m ;
        break;
    }
    setBackgroundColor(BLACK);
}
