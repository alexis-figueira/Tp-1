#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "estructuras.h"


usuario cargar_usuario ();
int validar_codigo (int);
int validar_fecha(int, int, int);
int validar_edad (int, int, int, int);
void validar_nombre(char [], int);
bool guardar_usuario (usuario);
bool guardar_usuario(usuario,int);
usuario leer_usuario (int);
void mostrar_registro (usuario);
void mostrar_usuarios ();
void mostrar_un_usuario (int);
int buscar_usuario (int);
bool modificar_usuario ();
int baja_usuario ();
int alta_usuario ();
int cantidad_usuarios ();


#endif // FUNCIONES_H_INCLUDED

