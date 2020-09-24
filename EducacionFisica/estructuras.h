#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

struct fecha {
    int dia ;
    int mes ;
    int anio ;
};

struct usuario {
    int id ;
    char nombre [50];
    char apellido [50]  ;
    fecha fnac ;
    float peso ;
    float altura ;
    char perfil ;
    bool apto ;
    bool estado ;
};

struct entrenamiento{
    int id ;
    int idUsuario ;
    fecha fent ;
    int act ;
    float cal ;
    int time ;
};

#endif // ESTRUCTURAS_H_INCLUDED
