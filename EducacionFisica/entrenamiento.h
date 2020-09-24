#ifndef ENTRENAMIENTO_H_INCLUDED
#define ENTRENAMIENTO_H_INCLUDED

#include "estructuras.h"

int cant_id ();
void cargar_entrenamiento ();
entrenamiento leer_entrenamiento (int) ;
void mostrar_lista_entrenamiento ();
void mostrar_un_entrenamiento (int);
void mostrar_entrenamiento (entrenamiento);
void mostrar_entrenamientos_usuario (int, int);

bool guardar_entrenamiento (entrenamiento);
bool guardar_entrenamiento (entrenamiento,int);

entrenamiento leer_entrenamiento (int) ;
int buscar_entrenamiento (int);
void modificar_entrenamiento ();
int baja_entrenamiento ();
int alta_entrenamiento ();

int validar_fecha_entrenamiento (int d, int m, int y, int ed);





#endif // ENTRENAMIENTO_H_INCLUDED
