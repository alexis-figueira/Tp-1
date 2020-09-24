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
const char arch [50]= "ListaUsuarios.dat" ;


/// ------------------------------------------------VALIDACIONES---------------------------------------------------------

int validar_codigo (int id){
    FILE *f ;
    usuario reg ;
    if (id<=0){
        devolucion("CODIGO INCORRECTO", "ROJO", tam_formato, alto_formato);
        anykey();
        return -2 ;   /// CODIGO INCORRECTO
    }
    f = fopen (arch, "rb");
    if (f==NULL){
        devolucion("ERROR AL LEER ARCHIVO", "ROJO",tam_formato, alto_formato);
        anykey();
        fclose(f);
        return -3 ; /// ERROR CON EL ARCHIVO
    }
    while (fread (&reg, sizeof (usuario), 1, f)==1){
        if (id == reg.id){
            devolucion("CODIGO REPETIDO", "ROJO", tam_formato, alto_formato);
            anykey();
            fclose(f);
            return -1 ; /// CODIGO REPETIDO
        }
    }
    fclose (f);
    return 1 ;
}

char validar_perfil (char perfil){
    while (!(perfil == 'a' || perfil == 'A' || perfil =='b' || perfil == 'B' || perfil == 'c' || perfil == 'C')){
        devolucion("PERFIL INCORRECTO", "ROJO",tam_formato, alto_formato);
        anykey();
        devolucion("CARGA DE USUARIO", "AZUL", tam_formato, alto_formato);
        borrar_renglon(9);
        msj("PERFIL DE ACT(A/B/C): ", 2 , tam_formato);
        cin >> perfil ;
    }
    return perfil ;
}

void validar_nombre(char nombre[],int tipo){
    while (nombre[0]== ' ' || nombre[0]==NULL){
        devolucion ("FORMATO INCORRECTO","ROJO", tam_formato, alto_formato);
        anykey();
        devolucion("CARGA DE USUARIO", "AZUL", tam_formato, alto_formato);
        if (tipo==1){
        borrar_renglon(4);
        msj ("NOMBRE: ", 2, tam_formato-6);
        }
        else {
            borrar_renglon(5);
            msj ("APELLIDO: ", 2, tam_formato-7);
        }
        cin.getline (nombre,50) ;
    }
}

bool validar_apto (char apto){
    bool apto_fisico ;
    while (apto != 's' && apto != 'S' && apto != 'n' && apto != 'N'){
        devolucion ("ERROR", "ROJO", tam_formato, alto_formato);
        anykey();
        devolucion("CARGA DE USUARIO", "AZUL", tam_formato, alto_formato);
        borrar_renglon (10);
        msj ("APTO MÉDICO (S/N): ", 2 , tam_formato);
        cin >> apto ;
    }
    switch (apto){
    case 's':
    case 'S':
        apto_fisico = true ;
        break;
    case 'n':
    case 'N':
        apto_fisico = false ;
        break;
    }
    return apto_fisico ;
}

int validar_fecha(int d, int m, int y){
    int i;
    bool bisiesto = false;
    //comprobamos si el año es bisiesto
    if(y%4==0 && y%100!=100 || y%400==0){
        bisiesto = true;
    }
    //comprobamos que los datos ingresados esten en un rango valido
    if(d>0 && d<32 && m>0 && m<13 && y>0){
        if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12){
           return 0 ;        // Fecha valida
        }else{
            if(m==2 && d<30 && bisiesto)
                return 0 ;   // Fecha valida
            else if(m==2 && d<29 && !bisiesto)
                return 0 ;   // Fecha valida
            else if(m!=2 && d<31)
                return 0 ;   // Fecha valida
            else
                return -1 ;  // Fecha no valida
        }
    }
    else {
        return - 1 ;// Fecha no valida
    }
}

int validar_edad (int d, int m, int y, int ed){
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
    if (m>tmPtr->tm_mon+1){
        edad -- ;
    }else {
        if(m==tmPtr->tm_mon+1){
            if(d>tmPtr->tm_mday){
                edad -- ;
            }
        }
    }
    if (edad>=ed && edad < 100 ){
        return 0 ; /// fecha y edad valida
    }
    else {
        if (edad<=0 || edad>100){
            return -1 ; /// edad menor a 0 años
        }
        return -2 ; /// edad menor
    }
}

/// -------------------------------------------FUNCIONES DE USUARIOS-----------------------------------------------------

usuario cargar_usuario (){
    /// TODO: Para un id auto numerico uso la func cantidad participantes + 1
    system ("cls") ;
    usuario persona ;
    int id, d,m,a;
    char apto ;
    char seg ;
    devolucion("CARGA DE USUARIO", "AZUL", tam_formato, alto_formato);
    guiones (tam_formato,11);
    titulo ("CARGA DE USUARIO",tam_formato) ;
    guiones (tam_formato);
    msj ("ID: ", 2, tam_formato);
    cin >> id ;
    while (validar_codigo(id)!=1){
        system("cls");
        devolucion("CARGA DE USUARIO", "AZUL", tam_formato, alto_formato);
        titulo("CARGA DE USUARIO",tam_formato) ;
        guiones (tam_formato);
        msj ("ID: ", 2, tam_formato);
        cin >> id ;
    }
    persona.id = id ;
    msj ("NOMBRE: ", 2, tam_formato-6);
    cin.ignore();
    cin.getline(persona.nombre,50);
    validar_nombre (persona.nombre,1);
    msj ("APELLIDO: " , 2 , tam_formato-7);
    cin.getline(persona.apellido, 50);
    validar_nombre(persona.apellido,2);
    msj ("FECHA NAC(dd/mm/aaaa): ", 2, tam_formato-5);
    gotoxy (((tam_formato-23)/2)+20,6);
    cin >> d ;
    gotoxy (((tam_formato-23)/2)+22,6);
    cout << "/" ;
    gotoxy (((tam_formato-23)/2)+23,6);
    cin >> m ;
    gotoxy (((tam_formato-23)/2)+25,6);
    cout << "/";
    gotoxy (((tam_formato-23)/2)+26,6);
    cin  >> a ;
    int k= validar_edad(d, m, a, 13);
    while (k!=0){
        if (k==-1){
            devolucion ("FECHA INVÁLIDA", "ROJO",tam_formato,alto_formato);
        }
        else {
            devolucion ("ERROR: DEBE SER MAYOR A 13 AÑOS", "ROJO",tam_formato,alto_formato);
        }
        anykey();
        devolucion("CARGA DE USUARIO", "AZUL", tam_formato, alto_formato);
        borrar_renglon(6);
        msj ("FECHA NAC(dd/mm/aaaa): ", 2, tam_formato-5);
        gotoxy (((tam_formato-23)/2)+20,6);
        cin >> d ;
        gotoxy (((tam_formato-23)/2)+22,6);
        cout << "/" ;
        gotoxy (((tam_formato-23)/2)+23,6);
        cin >> m;
        gotoxy (((tam_formato-23)/2)+25,6);
        cout << "/";
        gotoxy (((tam_formato-23)/2)+26,6);
        cin  >> a;
        k= validar_edad(d, m, a, 13);
    }
    persona.fnac.dia = d;
    persona.fnac.mes = m;
    persona.fnac.anio = a;
    msj("ALTURA: ", 2, tam_formato-1);
    cin >> persona.altura ;
    while(persona.altura<=0){
        devolucion("ALTURA INCORRECTA", "ROJO", tam_formato, alto_formato);
        anykey();
        devolucion("CARGA DE USUARIO", "AZUL", tam_formato, alto_formato);
        borrar_renglon(7);
        msj("ALTURA: ", 2, tam_formato-1);
        cin >> persona.altura ;
    }
    msj ("PESO: ", 2, tam_formato-2);
    cin >> persona.peso ;
    while(persona.peso<=0){
        devolucion ("PESO INCORRECTO", "ROJO", tam_formato, alto_formato);
        anykey();
        devolucion("CARGA DE USUARIO", "AZUL", tam_formato, alto_formato);
        borrar_renglon(8);
        msj ("PESO: ", 2, tam_formato-2);
        cin >> persona.peso ;
    }
    msj ("PERFIL DE ACT(A/B/C): ", 2, tam_formato);
    cin >> persona.perfil;
    persona.perfil=validar_perfil (persona.perfil);
    msj ("APTO MÉDICO(S/N): ",2 ,tam_formato);
    cin >> apto ;
    persona.apto = validar_apto (apto);
    persona.estado = true ;
    titulo(" ", tam_formato);
    devolucion(" ","AZUL", tam_formato, alto_formato);
    gotoxy (1,alto_formato-5);
    msj("DESEA GUARDAR EL USUARIO? (S/N): ",2, tam_formato);
    cin >> seg ;
    while (seg!= 'N'&& seg!= 'n'&& seg!= 'S'&& seg!= 's'){
        devolucion("CARACTER INVÁLIDO", "ROJO", tam_formato,alto_formato);
        anykey ();
        devolucion(" ","AZUL", tam_formato, alto_formato);
        borrar_renglon (alto_formato-5);
        msj("DESEA GUARDAR EL USUARIO? (S/N): ",2, tam_formato);
        cin >> seg ;
    }

    if (seg== 's' || seg == 'S'){
        guardar_usuario(persona);
        gotoxy (1,1);
        msj ("CONTACTO GUARDADO",2,tam_formato,"VERDE");
        devolucion("CONTACTO GUARDADO","VERDE", tam_formato, alto_formato);
        anykey();
    }else {
        if (seg== 'n' || seg == 'N'){
        devolucion("CARGA DE USUARIO CANCELADA","ROJO", tam_formato, alto_formato);
        anykey();
        }
    }
    return persona ;
}

bool guardar_usuario (usuario persona){
    FILE *f ;
    f = fopen(arch, "ab");
    if (f==NULL){
        cout << "No se pudo abrir el archivo" ;
        return 0 ;
    }
    fwrite(&persona, sizeof(usuario),1,f);
    fclose(f);
    return 1 ;
}

bool guardar_usuario(usuario persona,int pos){
    FILE *f ;
    f = fopen(arch, "rb+");
    if (f==NULL){
        cout << "No se pudo abrir el archivo" ;
        return 0 ;
    }
    fseek(f, pos*sizeof(usuario),SEEK_SET);
    fwrite(&persona, sizeof(usuario),1,f);
    fclose(f);
    return 1 ;
}

void mostrar_registro (usuario persona){
    system ("cls");
    titulo ("USUARIO", tam_formato);
    guiones (tam_formato);
    msj ("ID: ", 2, tam_formato-6); cout << persona.id << endl ;
    msj ("NOMBRE: ", 2, tam_formato-6); cout << persona.nombre <<endl ;
    msj ("APELLIDO: ", 2, tam_formato-6); cout << persona.apellido <<endl ;
    msj ("NACIMIENTO:", 2, tam_formato-6); cout << persona.fnac.dia << "/" << persona.fnac.mes<< "/"<< persona.fnac.anio <<  endl ;
    msj ("ALTURA: ", 2, tam_formato-6); cout << persona.altura << "cm" <<endl ;
    msj ("PESO: ", 2, tam_formato-6); cout << persona.peso << "kg" << endl ;
    msj ("PERFIL: ", 2, tam_formato-6); cout << persona.perfil << endl ;
    guiones (tam_formato);
    if (persona.estado==true){
        devolucion("ACTIVO", "VERDE",tam_formato,alto_formato);
    }else {
        devolucion ("INACTIVO", "ROJO",tam_formato, alto_formato);
    }
    anykey();
}

void mostrar_usuarios (){
    int tam ;
    FILE *f ;
    usuario reg ;
    f = fopen(arch, "rb");
    if (f==NULL){
        cout << "Problema con el archivo de usuarios" ;
        return ;
    }
    fseek(f, 0, SEEK_END);
    tam=ftell(f) ;
    if (tam == 0){
        system ("cls");
        titulo(" ",tam_formato);
        devolucion(" ", "AZUL",tam_formato, alto_formato);
        gotoxy(1,alto_formato/2);
        msj ("NO HAY REGISTROS GUARDADOS",2,tam_formato);
        anykey ();
        return ;
    }
    fseek(f,0,SEEK_SET);
    while (fread(&reg,sizeof(usuario),1,f)==1){
        if (reg.estado == true){
            system ("cls");
            mostrar_registro (reg);
        }
    }
    fclose(f);
}

void mostrar_un_usuario (int pos){
    FILE *f ;
    usuario reg ;
    f = fopen(arch, "rb");
    if (f==NULL){
        cout << "Problema con el archivo de usuarios" ;
        return ;
    }
    if (pos == -1){
    devolucion( "USUARIO INEXISTENTE", "ROJO", tam_formato, alto_formato);
    anykey ();
    }else {
        fseek(f, pos*sizeof(usuario),SEEK_SET);
        fread(&reg , sizeof(usuario),1,f);
        mostrar_registro(reg);
    }
    fclose(f);
}

int buscar_usuario (int id) {
    FILE *f ;
    usuario reg ;
    int pos=0;
    f = fopen(arch, "rb");
    if (f==NULL){
        devolucion( "ERROR CON ARCHIVO", "ROJO", tam_formato, alto_formato);
        anykey();
        return -2;
    }
    while (fread(&reg,sizeof(usuario),1,f)==1){
        if (reg.id==id){
        fclose(f);
        return pos ; /// DEVUELVE LA POSICION QUE LO ENCONTRO
        }
        pos ++ ;
    }
    fclose(f);
    return -1 ; /// NO ENCONTRO EL ID
}

usuario leer_usuario (int pos){
    usuario reg ;
    FILE *f ;
    f = fopen (arch, "rb");
    if (f == NULL){
        devolucion("ERROR DE ARCHIVO","ROJO", tam_formato,alto_formato);
        reg.id = 0;
        return reg ;
    }
    fseek (f, pos*sizeof(usuario), SEEK_SET);
    fread (&reg,sizeof(usuario),1,f);
    fclose (f);
    return reg ;
}

bool modificar_usuario (){
    bool dev = true ;
    int id, pos ;
    char apto , seg, perfil;
    usuario reg ;
    system("cls");
    devolucion("MODIFICACIONES", "AZUL", tam_formato, alto_formato);
    titulo ("MODIFICACIONES", tam_formato);
    guiones (tam_formato);
    msj ("USUARIO A MODIFICAR: ", 2 , tam_formato);
    cin >> id ;
    pos=buscar_usuario (id);
    if (pos>0){
        reg = leer_usuario (pos);
        mostrar_registro (reg);
        devolucion("MODIFICADIONES","AZUL",tam_formato,alto_formato);
        gotoxy (1,14);
        msj ("USUARIO A MODIFICAR.. ", 2,tam_formato) ; cout << endl ;
        anykey();
        titulo ("NUEVOS DATOS", tam_formato);
        guiones (tam_formato);
        borrar_renglon(8);
        borrar_renglon(9);
        borrar_renglon(10);
        borrar_renglon (14);
        borrar_renglon(16);
        gotoxy (1,11);
        guiones(tam_formato);
        gotoxy (1,8);
        msj ("PESO: ", 2 , tam_formato);
        cin >> reg.peso ;
        while(reg.peso<=0){
        devolucion ("PESO INCORRECTO", "ROJO", tam_formato, alto_formato);
        anykey ();
        borrar_renglon(8);
        borrar_renglon(alto_formato);
        gotoxy(1,8);
        msj ("PESO: ", 2, tam_formato);
        cin >> reg.peso ;
        }
        gotoxy (1,9);
        msj ("PERFIL (A/B/C): ", 2, tam_formato);
        cin >> perfil ;
        while (!(perfil == 'a' || perfil == 'A' || perfil =='b' || perfil == 'B' || perfil == 'c' || perfil == 'C')){
            devolucion("PERFIL INCORRECTO", "ROJO",tam_formato, alto_formato);
            anykey();
            devolucion ("MODIFICACIONES", "AZUL", tam_formato,alto_formato);
            borrar_renglon(9);
            gotoxy (1,9);
            msj ("PERFIL (A/B/C): ", 2, tam_formato);
            cin >> perfil ;
        }
        reg.perfil=perfil;
        gotoxy (1,10);
        msj ("APTO MÉDICO (S/N): ", 2, tam_formato);
        cin >> apto ;
        while (apto != 's' && apto != 'S' && apto != 'n' && apto != 'N'){
            devolucion ("CARACTER INCORRECTO", "ROJO", tam_formato, alto_formato);
            anykey();
            devolucion ("MODIFICACIONES", "AZUL", tam_formato,alto_formato);
            borrar_renglon (10);
            gotoxy (1,10);
            msj ("APTO MÉDICO (S/N): ", 2, tam_formato);
            cin >> apto ;
        }
        if (apto == 's' || apto =='S'){
            reg.apto =true ;
        }
        else {
            reg.apto =false ;
        }
        gotoxy(1, alto_formato-7);
        msj ("DESEA HACER EL CAMBIO?(S/N): ", 2, tam_formato);
        cin >> seg ;
        while (seg != 'S' && seg != 's' && seg != 'N' && seg != 'n'  ){
            devolucion("CARACTER INVÁLIDO","ROJO",tam_formato,alto_formato);
            anykey ();
            devolucion("MODIFICACIONES","AZUL",tam_formato,alto_formato);
            borrar_renglon(alto_formato-7);
            msj ("DESEA HACER EL CAMBIO?(S/N): ", 2, tam_formato);
            cin >> seg ;
        }
        switch (seg){
        case 's':
        case 'S':
            if (guardar_usuario(reg,pos)==1){
                devolucion("CAMBIO GUARDADO","VERDE",tam_formato,alto_formato);
                anykey ();
                return dev=true;
            }else {
                devolucion ("ERROR AL GUARDAR", "ROJO", tam_formato, alto_formato);
                anykey();
                return dev=true;
            }
            break ;
        case 'n':
        case 'N':
            devolucion ("CAMBIO NO REALIZADO", "VERDE",tam_formato, alto_formato);
            anykey();
            break ;
        }
    }else {
        devolucion("USUARIO INEXISTENTE","ROJO", tam_formato, alto_formato);
        anykey ();
        dev = false ;
        return dev ;
    }
    anykey ();
}

int cantidad_usuarios (){

    FILE *f ;
    int cantidad, bytes ;
    f = fopen(arch, "rb");

    if (f==NULL){
        return 0 ; /// No abrio el archivo
    }

    fseek (f, 0, SEEK_END); // NOS UBICAMOS ALFINAL DEL ARCHIVO

    bytes = ftell(f);
    cantidad = bytes / sizeof(usuario);

    fclose (f);

    return cantidad ;
}

int baja_usuario (){
    usuario reg;
    int pos, id;
    char elim ;
    system ("cls");
    devolucion("   ", "AZUL", tam_formato,alto_formato);
    titulo ("BAJA USUARIO", tam_formato);
    guiones(tam_formato);
    msj("INGRESE ID: ", 2 , tam_formato);
    cin >> id ;
    pos = buscar_usuario (id);
    if (pos<0){
        devolucion ("NO SE ENCONTRÓ EL CÓDIGO","ROJO", tam_formato,alto_formato);
        anykey ();
        return -1;
    }
    reg = leer_usuario (pos);
    mostrar_registro (reg);
    if (reg.estado==true){
        gotoxy (1,18);
        msj ("ELIMINAR REGISTRO?(S/N): ",2,tam_formato);
        cin >> elim ;
        while (elim != 's' && elim != 'S' && elim != 'n' && elim != 'N'){
            devolucion ("CARACTER INVÁLIDO","ROJO", tam_formato, alto_formato);
            anykey ();
            devolucion("   ", "AZUL", tam_formato,alto_formato);
            borrar_renglon (18);
            msj ("ELIMINAR REGISTRO? S/N: ", 2, tam_formato);
            cin >> elim ;
        }
        if (elim=='s' || elim =='S'){
            reg.estado = false ;
            guardar_usuario(reg, pos);
            anykey ();
            return 0 ;
        }else {
            return 1 ;
        }
    }else {
        return -2 ;
    }
}

int alta_usuario (){
    usuario reg;
    int pos, id;
    char elim ;
    system ("cls");
    devolucion("   ", "AZUL", tam_formato,alto_formato);
    titulo ("ALTA USUARIO", tam_formato);
    guiones(tam_formato);
    msj("INGRESE ID: ", 2 , tam_formato);
    cin >> id ;
    pos = buscar_usuario (id);
    if (pos<0){
        devolucion ("NO SE ENCONTRÓ EL CÓDIGO","ROJO", tam_formato,alto_formato);
        anykey ();
        return -1;
    }
    reg = leer_usuario (pos);
    mostrar_registro (reg);
    if (reg.estado==true){
        return -2 ;
    }else {
        gotoxy (1,18);
        msj ("DAR USUARIO DE ALTA?(S/N): ",2,tam_formato);
        cin >> elim ;
        while (elim != 's' && elim != 'S' && elim != 'n' && elim != 'N'){
            devolucion ("CARACTER INVÁLIDO","ROJO", tam_formato, alto_formato);
            anykey ();
            devolucion("   ", "AZUL", tam_formato,alto_formato);
            borrar_renglon (18);
            msj ("DAR USUARIO DE ALTA? S/N: ", 2, tam_formato);
            cin >> elim ;
        }
        if (elim=='s' || elim =='S'){
            reg.estado=true ;
            guardar_usuario(reg, pos);
            anykey ();
            return 0 ;
        }else {
            return 1 ;
        }
    }
}
