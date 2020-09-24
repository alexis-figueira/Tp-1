#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED

void initUI();
void borrar_renglon (int);
void borrar_restorenglon(int, int);
void borrar_restopantalla (int);
void titulo(const char *, int);
void devolucion(const char *, const char *, int , int);
void guiones(int);
void guiones(int ancho, int renglon);
void msj (const char *, int, int);
void msj (const char *, int , int, const char*);

#endif // INTERFAZ_H_INCLUDED
