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

const int tam_formato = 40, alto_formato=25;
const char arch [50]= "ListaUsuarios.dat" ;
const char arch_entrenamiento [50]= "ListaEntrenamientos.dat" ;

void menu_reportes(){
    int m ;
    while (true){
        system ("cls");
        devolucion("REPORTES", "AZUL", tam_formato,alto_formato);
        titulo ("REPORTES",tam_formato);
        guiones (tam_formato);
        msj ("01. REPORTE 1", 2, tam_formato); cout << endl ;
        msj ("02. REPORTE 2", 2, tam_formato); cout << endl ;
        guiones (tam_formato);
        msj ("00. VOLVER AL MENÚ PRINCIPAL", 2 , tam_formato); cout << endl ;
        guiones (tam_formato);
        gotoxy (1, tam_formato/2);
        msj ("INGRESE LA OPCIÓN: ",2 ,tam_formato);
        cin >> m ;
        switch (m){
        case 1:
            system ("cls");
            devolucion ("REPORTE 1", "AZUL", tam_formato, alto_formato);
            titulo("REPORTE 1", tam_formato);
            anykey ();
            break;
        case 2 :
            system ("cls");
            devolucion ("REPORTE 2", "AZUL", tam_formato, alto_formato);
            titulo("REPORTE 2", tam_formato);
            anykey ();
            break;
        case 0:
            return ;
            break;
        default:
            system ("cls");
            msj ("OPCIÓN INCORRECTA", 2,tam_formato,"ROJO");
            devolucion ("OPCIÓN INCORRECTA", "ROJO", tam_formato, alto_formato);
            anykey ();
            break ;
        }
    }

}

void reporte1 (){

}

void reporte2 (){


}
