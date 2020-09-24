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
#include "entrenamiento.h"
#include "reportes.h"
const int tam_formato = 40, alto_formato=25;
const char arch [50]= "ListaUsuarios.dat" ;


int menu_principal (){
    int opcion_menu;
    system("cls");
    titulo("MENÚ PRINCIPAL",tam_formato);
    guiones(tam_formato);
    msj ("1.USUARIOS", 2 , tam_formato); cout << endl ;
    msj ("2.ENTRENAMIENTOS", 2 , tam_formato); cout << endl ;
    msj ("3.REPORTES", 2 , tam_formato); cout << endl ;
    msj ("4.CONFIGURACIóN", 2 , tam_formato); cout << endl ;
    guiones (tam_formato);
    msj ("0.SALIR DEL PROGRAMA", 2 , tam_formato); cout << endl ;
    guiones (tam_formato);
    devolucion ("MENÚ PRINCIPAL", "AZUL", tam_formato,alto_formato);
    gotoxy(1,alto_formato-7);
    msj ("ELIJA UNA OPCIÓN: ", 2, tam_formato);
    cin >> opcion_menu ;
    return opcion_menu;
}

void menu_usuarios (){
    int menu = 1, id;
    while (menu!=0){
        int dev ;
        system ("cls");
        titulo ("MENÚ USUARIOS",tam_formato);
        guiones (tam_formato);
        msj ("1. NUEVO USUARIO" , 2, tam_formato); cout << endl ;
        msj ("2. MODIFICAR USUARIO" , 2, tam_formato);cout << endl ;
        msj ("3. LISTAR USUARIO POR ID", 2, tam_formato);cout << endl ;
        msj ("4. LISTAR TODOS LOS USUARIOS", 2, tam_formato);cout << endl ;
        msj ("5. ELIMINAR USUARIO" , 2, tam_formato);cout << endl ;
        msj ("6. DAR USUARIO DE ALTA", 2, tam_formato);cout << endl ;
        guiones (tam_formato);
        msj ("0. VOLVER AL MENÚ PRINCIPAL",2,tam_formato); cout << endl ;
        guiones (tam_formato);
        devolucion ("MENÚ USUARIO", "AZUL", tam_formato, alto_formato);
        gotoxy (1,alto_formato-7);
        msj("ELIJA UNA OPCIÓN: ", 2 , tam_formato);
        cin >> menu ;
        switch (menu){
        case 1 : /// nuevo usuario
            cargar_usuario () ;
            break ;
        case 2 : /// modificar usuario
            modificar_usuario ();
            break ;
        case 3 : /// listar usuario por id
            int pos ;
            system ("cls");
            devolucion("BÚSQUEDA DE USUARIO", "AZUL", tam_formato,alto_formato);
            titulo ("BÚSQUEDA DE USUARIO", tam_formato);
            guiones (tam_formato);
            gotoxy (1,alto_formato/2);
            msj ("INGRESE EL ID DEL USUARIO: ",2,tam_formato);
            cin >> id ;
            pos=buscar_usuario (id);
            mostrar_un_usuario (pos);
            break ;
        case 4 : ///  listar todos los usuario
            mostrar_usuarios();
            break ;
        case 5 : /// eliminar usuario
            dev = baja_usuario ();
            system ("cls");
            titulo (" ",tam_formato);
            devolucion (" ","AZUL",tam_formato, alto_formato);
            gotoxy (1,alto_formato/2) ;
            if (dev==0){
                msj ("USUARIO ELIMINADO", 2,tam_formato);
            }else {
                if (dev==-2){
                    msj("EL USUARIO YA ESTABA DADO DE BAJA",2,tam_formato);
                } else {
                    if (dev == -1){
                        msj("NO SE ENCONTRÓ EL USUARIO",2,tam_formato);
                    }else {
                        if (dev==1){
                            msj ("BAJA DE USUARIO CANCELADA",2, tam_formato);
                        }else {
                        setBackgroundColor(RED);
                        msj("OCURRIÓ UN ERROR",2,tam_formato);
                        setBackgroundColor(BLACK);
                        }
                    }
                }
            }
            anykey();
            break ;
        case 6 : /// dar usuario de alta
            dev = alta_usuario ();
            system ("cls");
            titulo (" ",tam_formato);
            devolucion (" ","AZUL",tam_formato, alto_formato);
            gotoxy (1,alto_formato/2) ;
            if (dev==0){
                msj ("USUARIO DADO DE ALTA", 2,tam_formato);
            }else {
                if (dev==-2){
                    msj("EL USUARIO YA ESTABA DADO DE ALTA",2,tam_formato);
                } else {
                    if (dev == -1){
                        msj("NO SE ENCONTRÓ EL USUARIO",2,tam_formato);
                    }else {
                        if (dev==1){
                            msj("ALTA DE USUARIO CANCELADA",2,tam_formato);
                        }else {
                            setBackgroundColor (RED);
                            msj("OCURRIÓ UN ERROR",2,tam_formato);
                            setBackgroundColor(BLACK);
                        }
                    }
                }
            }
            anykey();
            break ;
        case 0 :
            return ;
            break ;
        default :
            devolucion ("OPCIÓN INCORRECTA", "ROJO", tam_formato, alto_formato);
            anykey();
            break ;
        }
    }
}

void menu_entrenamientos (){
    int menu = 1, id, pos;
    while (menu!=0){
        int dev;
        system ("cls");
        titulo ("MENÚ ENTRENAMIENTO",tam_formato);
        guiones (tam_formato);
        msj ("1. NUEVO ENTRENAMIENTO" , 2, tam_formato); cout << endl ;
        msj ("2. MODIFICAR ENTRENAMIENTO" , 2, tam_formato);cout << endl ;
        msj ("3. LISTAR ENTRENAMIENTO POR ID", 2, tam_formato);cout << endl ;
        msj ("4. LISTAR ENTRENAMIENTO POR USUARIO", 2, tam_formato);cout << endl ;
        msj ("5. LISTAR LOS ENTRENAMIENTOS" , 2, tam_formato);cout << endl ;
        guiones (tam_formato);
        msj ("0. VOLVER AL MENÚ PRINCIPAL",2,tam_formato); cout << endl ;
        guiones (tam_formato);
        devolucion ("MENÚ ENTRENAMIENTO", "AZUL", tam_formato, alto_formato);
        gotoxy (1,alto_formato-7);
        msj("ELIJA UNA OPCIÓN: ", 2 , tam_formato);
        cin >> menu ;
        switch (menu){
        case 1 : ///nuevo entrenamiento
            cargar_entrenamiento ();
            break ;
        case 2 : ///modificar entrenamiento
            modificar_entrenamiento();
            break ;
        case 3 :/// listar entrenamiento por ID
            system ("cls");
            devolucion("LISTA DE ENTRENAMIENTOS", "AZUL", tam_formato, alto_formato);
            titulo("LISTA DE ENTRENAMIENTOS", tam_formato);
            guiones (tam_formato);
            gotoxy (1,alto_formato/2);
            msj ("INGRESE ID DE ENTRENAMIENTO: ", 2, tam_formato);
            cin >> id ;
            pos=buscar_entrenamiento (id);
            mostrar_un_entrenamiento (pos);
            break ;
        case 4 : /// Listar entrenamiento por ID usuario
            system ("cls");
            devolucion ("ENTRENAMIENTO POR USUARIO", "AZUL", tam_formato,alto_formato);
            titulo ("ENTRENAMIENTO POR USUARIO", tam_formato);
            guiones (tam_formato);
            gotoxy (1,alto_formato/2);
            msj ("INGRESE ID DE USUARIO: ", 2, tam_formato);
            cin >> id ;
            pos = buscar_usuario (id);
            if (pos < 0){
                devolucion ("USUARIO INEXISTENTE", "ROJO", tam_formato,alto_formato);
                anykey ();
            }else {
                mostrar_entrenamientos_usuario (id, pos); ///id y posicion DEL USUARIO
            }
            break ;
        case 5 : /// Listar todos los entrenamientos
            mostrar_lista_entrenamiento ();
            break ;
        case 0 :
            return ;
            break ;
        default :
            devolucion ("OPCIÓN INCORRECTA", "ROJO", tam_formato, alto_formato);
            anykey();
            break ;
        }
    }
}

void menu_configuracion (){
    system ("cls");
    devolucion("CONFIGURACIÓN", "AZUL", tam_formato,alto_formato);
    titulo ("CONFIGURACIÓN",tam_formato);
    anykey();
}
