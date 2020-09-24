#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include "estructuras.h"
#include "interfaz.h"
#include "entrenamiento.h"
#include "Funciones.h"
const int tam_formato = 40, alto_formato=25 ;
const char arch_entrenamiento [50]= "ListaEntrenamientos.dat" ;


int validar_fecha_entrenamiento (int d, int m, int y, int ed){
    int edad ;
    if (validar_fecha(d,m,y)!=0){
        return -1 ; /// fecha invalida
    }
    time_t tiempo;
    char cad[80];
    struct tm *tmPtr;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);
    edad = 1900+tmPtr->tm_year - y ;

    if (1900+tmPtr->tm_year<y){
        return - 1 ; /// fecha invalida
    }
    if (1900+tmPtr->tm_year==y){
        if (m>tmPtr->tm_mon+1){
            return -1 ; /// fecha invalilda
        }
        if (m==tmPtr->tm_mon+1){
            if (d>tmPtr->tm_mday){
                return -1 ; /// fecha invalida
            }
        }
    }
    if (edad>ed){
        return -2 ; /// mas de la edad
    }
    return 0 ; /// fecha valida
}

int cant_id (){
    int id_auto ;
    FILE *f;
    f = fopen (arch_entrenamiento, "ab");
    if (f==NULL){
        devolucion("ERROR DE ARCHIVO","ROJO", tam_formato, alto_formato);
        anykey();
    }
    fseek(f, 0, SEEK_END) ;
    id_auto = ftell (f);
    id_auto = id_auto / sizeof (entrenamiento);
    fclose (f);
    return id_auto ;
}

void cargar_entrenamiento (){
    entrenamiento persona ;
    usuario reg;
    bool grabo ;
    int IDusuario, pos, d, m, a ;
    system("cls");
    devolucion("CARGA DE ENTRENAMIENTO", "AZUL", tam_formato, alto_formato);
    guiones (tam_formato,9);
    titulo("CARGA DE ENTRENAMIENTO", tam_formato);
    guiones (tam_formato);
    persona.id = cant_id () + 1;
    msj ("ID ENTRENAMIENTO: ", 2,tam_formato); cout << persona.id << endl ;
    msj ("INGRESE ID DE USUARIO: ", 2,tam_formato);
    cin >> IDusuario ;
    pos=buscar_usuario(IDusuario);
    while (pos<0){
        if (pos==-1){
            devolucion ("USUARIO INEXISTENTE","ROJO",tam_formato, alto_formato);
            anykey();
            devolucion("CARGA DE ENTRENAMIENTO", "AZUL", tam_formato, alto_formato);
            borrar_renglon (4);
            msj ("INGRESE ID DE USUARIO: ", 2,tam_formato);
            cin >> IDusuario ;
            pos=buscar_usuario(IDusuario);
        }
        else {
            cout << "NO SE LEYÓ EL ARCHIVO" << endl ; anykey ();
            return ;
        }
    }
    persona.idUsuario=IDusuario;
    reg = leer_usuario (pos) ;
    msj ("FECHA ENTRENAMIENTO: ", 2, tam_formato);
    gotoxy (((tam_formato-22)/2)+21,5);
    cin >> d ;
    gotoxy (((tam_formato-22)/2)+23,5);
    cout << "/" ;
    gotoxy (((tam_formato-22)/2)+24,5);
    cin >> m ;
    gotoxy (((tam_formato-22)/2)+26,5);
    cout << "/";
    gotoxy (((tam_formato-22)/2)+27,5);
    cin  >> a ;
    int k= validar_fecha_entrenamiento(d, m, a, 15);
    while (k!=0){
        if (k==-1){
            devolucion ("FECHA INVÁLIDA", "ROJO",tam_formato,alto_formato);
        }
        else {
            devolucion ("FECHA MUY ANTIGUA", "ROJO",tam_formato,alto_formato);
        }
        anykey();
        devolucion("CARGA ENTRENAMIENTO", "AZUL", tam_formato, alto_formato);
        borrar_renglon(5);
        msj ("FECHA ENTRENAMIENTO: ", 2, tam_formato);
        gotoxy (((tam_formato-22)/2)+21,5);
        cin >> d ;
        gotoxy (((tam_formato-22)/2)+23,5);
        cout << "/" ;
        gotoxy (((tam_formato-22)/2)+24,5);
        cin >> m ;
        gotoxy (((tam_formato-22)/2)+26,5);
        cout << "/";
        gotoxy (((tam_formato-22)/2)+27,5);
        cin  >> a ;
        k= validar_fecha_entrenamiento(d, m, a, 15);
    }
    persona.fent.dia = d;
    persona.fent.mes = m;
    persona.fent.anio = a;
    gotoxy (1, alto_formato-3);
    msj("1.CAMINATA/2.CORRER/3.BICICLETA",2,tam_formato);
    gotoxy (1, alto_formato-2);
    msj("4.NATACION/5.PESAS",2,tam_formato);
    gotoxy(1,6);
    msj( "ACTIVIDAD: ", 2, tam_formato);
    cin >> persona.act ;
    borrar_renglon(alto_formato-3);
    borrar_renglon(alto_formato-2);
    while (persona.act!=1 && persona.act!=2 &&persona.act!=3 &&persona.act!=4 &&persona.act!=5){
        devolucion("OPCIÓN INVÁLIDA","ROJO", tam_formato, alto_formato);
        anykey();
        devolucion("CARGA ENTRENAMIENTO", "AZUL", tam_formato, alto_formato);
        gotoxy (1, alto_formato-3);
        msj("1.CAMINATA/2.CORRER/3.BICICLETA",2,tam_formato);
        gotoxy (1, alto_formato-2);
        msj("4.NATACION/5.PESAS",2,tam_formato);
        borrar_renglon(6);
        msj( "ACTIVIDAD: ", 2, tam_formato);
        cin >> persona.act ;
        borrar_renglon(alto_formato-3);
        borrar_renglon(alto_formato-2);
    }
    if (persona.act == 4 || persona.act ==5){
        if (reg.apto == false){
            devolucion ("SE REQUIERE APTO FISICO", "ROJO", tam_formato,alto_formato);
            anykey ();
            return ;
        }
    }
    gotoxy (1,7);
    msj ("CALORIAS: ", 2 , tam_formato);
    cin >> persona.cal ;
    while (persona.cal<=0){
        devolucion ("VALOR DE CALORIAS INCORRECTO", "ROJO", tam_formato, alto_formato);
        anykey ();
        devolucion("CARGA ENTRENAMIENTO", "AZUL", tam_formato, alto_formato);
        borrar_renglon (7);
        msj ("CALORIAS: ", 2 , tam_formato);
        cin >> persona.cal ;
    }
    msj ("MINUTOS ENTRENANDO: ", 2, tam_formato);
    cin >> persona.time ;
    while (persona.time<=0){
        devolucion ("TIEMPO INVALIDO", "ROJO", tam_formato, alto_formato);
        anykey ();
        devolucion("CARGA ENTRENAMIENTO", "AZUL", tam_formato, alto_formato);
        borrar_renglon (8);
        msj ("MINUTOS ENTRENANDO: ", 2 , tam_formato);
        cin >> persona.cal ;
    }
    gotoxy (1, alto_formato/2);
    msj ("DESEA GUARDAR EL ENTRENAMIENTO(S/N): ", 2 , tam_formato);
    char guar ;
    cin >> guar ;
    while (guar!='s' && guar!='S' && guar!='n' && guar!='N' ){
        devolucion ("CARACTER INCORRECTO", "ROJO", tam_formato,alto_formato);
        anykey ();
        devolucion("CARGA ENTRENAMIENTO", "AZUL", tam_formato, alto_formato);
        borrar_renglon(alto_formato/2);
        msj ("DESEA GUARDAR EL ENTRENAMIENTO(S/N): ", 2 , tam_formato);
        cin >> guar ;
    }
    if (guar == 's' || guar == 'S'){
        grabo=guardar_entrenamiento (persona);
        if (grabo == true){
            devolucion ("SE GRABÓ EL ENTRENAMIENTO", "VERDE", tam_formato,alto_formato);
            anykey ();
        }
    }
    else {
        devolucion ("ENTRENAMIENTO CANCELADO", "VERDE", tam_formato,alto_formato);
        anykey ();
    }
}

bool guardar_entrenamiento (entrenamiento persona){
    FILE *f ;
    f = fopen (arch_entrenamiento, "ab");
    if (f==NULL){
        devolucion ("ERROR CON EL ARCHIVO", "ROJO", tam_formato,alto_formato);
        anykey ();
        return false ;
    }
    fwrite (&persona, sizeof (entrenamiento),1,f);
    fclose (f);
    return true ;
}

bool guardar_entrenamiento (entrenamiento persona,int pos){
    FILE *f ;
    f = fopen(arch_entrenamiento, "rb+");
    if (f==NULL){
        devolucion("ERROR CON EL ARCHIVO", "ROJO",tam_formato, alto_formato) ;
        anykey ();
        return 0 ;
    }
    fseek(f, pos*sizeof(entrenamiento),SEEK_SET);
    fwrite(&persona, sizeof(entrenamiento),1,f);
    fclose(f);
    return 1 ;
}

int buscar_entrenamiento (int id){ ///revisar
    int pos=0;
    entrenamiento reg ;
    FILE *f ;
    f=fopen (arch_entrenamiento, "rb");
    if (f==NULL){
        devolucion ("ERROR DE ARCHIVO", "ROJO", tam_formato, alto_formato);
        anykey ();
        return -2 ;/// error de archivo
    }
    while (fread(&reg,sizeof(entrenamiento),1,f)==1){
        if (reg.id ==id){
            fclose(f);
            return pos ; /// DEVUELVE LA POSICION QUE LO ENCONTRO
        }
        pos ++ ;
    }
    fclose (f);
    return - 1 ; /// no encontro el id
}

entrenamiento leer_entrenamiento (int pos){ /// revcisar
    entrenamiento reg;
    FILE *f ;
    f = fopen (arch_entrenamiento, "rb");
    if (f == NULL){
        devolucion ("ERROR DE ARCHIVO", "ROJO",tam_formato, alto_formato);
        anykey ();
        reg.id=0;
        return reg;
    }
    fseek (f, pos* sizeof (entrenamiento), SEEK_SET);
    fread (&reg, sizeof (entrenamiento),1, f);
    fclose (f);
    return reg ;
}

void mostrar_entrenamientos_usuario (int id, int pos){
    usuario reg ;
    entrenamiento persona ;
    reg = leer_usuario (pos);
    if (reg.estado==false){
        devolucion ("USUARIO INACTIVO", "ROJO", tam_formato,alto_formato);
        anykey ();
        return ; /// USUARIO INACTIVO
    }
    FILE *f ;
    f = fopen (arch_entrenamiento, "rb");
    if (f==NULL){
        devolucion ("ERROR DE ARCHIVO", "ROJO", tam_formato,alto_formato);
        anykey();
        return ; /// ERROR DE ARCHIVO
    }
    while (fread (&persona, sizeof(entrenamiento),1, f)==1){
        if (persona.idUsuario==id){
            mostrar_entrenamiento (persona);
        }
    }
    fclose (f);
}

void mostrar_entrenamiento (entrenamiento reg){ ///ya esta ... revisar
    system ("cls");
    devolucion ("ENTRENAMIENTO", "AZUL",tam_formato,alto_formato);
    titulo ("ENTRENAMIENTO", tam_formato);
    guiones(tam_formato);
    msj ("ID: ", 2, tam_formato); cout << reg.id << endl ;
    msj ("IDusuario: ", 2, tam_formato); cout << reg.idUsuario << endl ;
    msj ("FECHA ENTRENAMIENTO: ",2, tam_formato); cout << reg.fent.dia << "/" << reg.fent.mes << "/" << reg.fent.anio << endl ;
    msj ("ACTIVIDAD: ",2,tam_formato);
    switch (reg.act){
    case 1:
        cout << "CAMINATA(1)" << endl ;
        break;
    case 2:
        cout << "CORRER(2)" << endl ;
        break;
    case 3:
        cout << "BICICLETA(3)" << endl ;
        break;
    case 4 :
        cout << "NATACIÓN(4)" << endl ;
        break;
    case 5 :
        cout << "PESAS(5)" << endl ;
        break;
    }
    msj ("CALORÍAS: ",2, tam_formato-1); cout << reg.cal << endl;
    msj ("TIEMPO: ", 2, tam_formato-3); cout << reg.time << " min" <<endl ;
    guiones (tam_formato);
    anykey ();
}

void mostrar_un_entrenamiento (int pos){ /// trabaja sobre entrenamientos
    FILE *f ;
    entrenamiento reg ;
    if (pos == -1){
        devolucion( "USUARIO INEXISTENTE", "ROJO", tam_formato, alto_formato);
        anykey ();
        return ;
    }
    f = fopen(arch_entrenamiento, "rb");
    if (f==NULL){
        devolucion("ERROR CON EL ARCHIVO", "ROJO", tam_formato,alto_formato);
        anykey ();
        return ;
    }
    fseek(f, pos*sizeof(entrenamiento),SEEK_SET);
    fread(&reg , sizeof(entrenamiento),1,f);
    mostrar_entrenamiento(reg);
    fclose(f);
}

void mostrar_lista_entrenamiento (){ /// ya esta...revisar
    entrenamiento reg ;
    FILE *f ;
    f = fopen (arch_entrenamiento, "rb");
    if (f==NULL){
        devolucion ("ERROR CON EL ARHICO", "ROJO", tam_formato, alto_formato);
        anykey ();
        return ;
    }
    while (fread(&reg, sizeof(entrenamiento), 1, f)==1){
        mostrar_entrenamiento (reg);
    }
    fclose(f);
}

void modificar_entrenamiento (){ /// TERMINAR
    int id, pos;
    char dec ;
    bool grabo=false ;
    entrenamiento reg ;
    system("cls");
    devolucion("MODIFICAR ENTRENAMIENTO", "AZUL",tam_formato,alto_formato);
    titulo("MODIFICAR ENTRENAMIENTO", tam_formato);
    guiones (tam_formato);
    gotoxy(1,alto_formato/2);
    msj ("INGRESE ID DE ENTRENAMIENTO: ", 2, tam_formato);
    cin >> id ;
    pos = buscar_entrenamiento (id) ;
    if (pos<0){
        if (pos==-1){
            devolucion("USUARIO INEXISTENTE","ROJO",tam_formato, alto_formato);
        }
        anykey ();
        return ;
    }
    cout << endl ;
    msj ("USUARIO A MODIFICAR...", 2,tam_formato);
    anykey ();
    reg = leer_entrenamiento (pos);
    mostrar_un_entrenamiento (pos);
    borrar_renglon (7);
    msj ("CALORÍAS: ",2, tam_formato-1);
    cin >> reg.cal ;
    borrar_renglon (8);
    msj ("TIEMPO: ", 2, tam_formato-3);
    cin >> reg.time ;
    gotoxy (1, alto_formato/2) ;
    msj ("MODIFICAR USUARIO?(S/N): ", 2, tam_formato);
    cin >> dec ;
    while (dec != 'n' && dec != 'N' && dec != 's' && dec != 'S'){
        devolucion("CARACTER INCORRECTO", "ROJO", tam_formato, alto_formato);
        anykey ();
        devolucion("MODIFICAR ENTRENAMIENTO", "AZUL",tam_formato,alto_formato);
        borrar_renglon (alto_formato/2);
        msj ("MODIFICAR USUARIO?(S/N): ", 2, tam_formato);
        cin >> dec ;
    }
    if (dec == 's' || dec == 'S'){
        grabo=guardar_entrenamiento (reg,pos);
        if (grabo ==true){
            devolucion ("MODIFICACIÓN REALIZADA", "VERDE", tam_formato,alto_formato);
            anykey ();
        }
        else {
            devolucion ("OCURRIÓ UN ERROR", "ROJO", tam_formato,alto_formato);
            anykey ();
        }
    }else {
        devolucion ("MODIFICACIÓN CANCELADA", "VERDE", tam_formato, alto_formato);
        anykey ();
    }
}
