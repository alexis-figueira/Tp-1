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
#include "reportes.h"
const int tam_formato = 40, alto_formato=25;
const char arch [50]= "ListaUsuarios.dat" ;


int main(){
    initUI();
    FILE *f ;
    f = fopen (arch, "ab");
    fclose(f);
    bool menu_prin = true ;
    int opcion_menu ;
    while (menu_prin==true ){
        opcion_menu = menu_principal ();
        switch (opcion_menu){
        case 1 :
            menu_usuarios ();
            break;
        case 2 :
            menu_entrenamientos();
            break;
        case 3:
            menu_reportes();
            break ;
        case 4:
            menu_configuracion();
            break ;
        case 0:
            menu_prin =false ;
            break ;
        default :
            gotoxy(1,25);
            devolucion("OPCION INCORRECTA", "ROJO", tam_formato, alto_formato) ;
            anykey();
            break ;
        }
    }

    return 0;
}
