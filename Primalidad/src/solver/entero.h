#ifndef ENTERO
#define ENTERO

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/** Estructura entero*/
struct entero
{
  /** Puntero a arreglo de digitos*/
  uint8_t* digitos;

  /** Numero de digitos en el entero*/
  int n_digitos;

  /** Tamaño del arreglo de digitos*/
  int t_arreglo;

  /** Bool que dice si el dato es cero*/
  bool cero;
};

//Funciones
typedef struct entero Entero;

//Variables globales
Entero* uno;
Entero* dos;

/** Inicializa el entero*/
Entero*   entero_init(uint8_t* digitos, int n_digitos, int t_arreglo);

/** Inicializa el entero desde un string*/
Entero*   entero_string_init(char* string);

/** Inicializa un entero como 0*/
Entero*   entero_cero();

/** Retorna la suma, y guarda en d3 el carry*/
uint8_t   digito_suma(uint8_t d1, uint8_t d2, uint8_t carryIn, uint8_t* carryOut);

/** Imprime el entero*/
void      entero_imprimir(Entero* e);

/** Separa el entero 'a' en 'a1' y 'a2' donde a1 tiene techo(n/2) digitos*/
void      entero_separar(Entero* a, Entero* a1, Entero* a2, int n2);

/** Retorna -1 (e1 < e2), 0 (=) o 1 (e1 > e2)*/
int       entero_comparar(Entero* e1, Entero* e2);

/** Retorna -1 (e1 < e2), 0 (=) o 1 (e1 > e2)*/
int       entero_digito_comparar(Entero* e, uint8_t i);

/** Guarda en resp el entero nuevo e1 + e2*/
void      entero_suma(Entero* e1, Entero* e2, Entero* resp);

/** Guarda en resp el entero nuevo e1 - e2 (e1 > e2)*/
void      entero_resta(Entero* e1, Entero* e2, Entero* resp);

/** Multiplica a por 10 n veces y guarda en resp a*10^n*/
void      entero_agregar_ceros(Entero* a, Entero* resp, int n);

/** Guarda en resp un entero nuevo e1 * e2*/
void      entero_multiplicacion(Entero* e1, Entero* e2, Entero* resp);

/** Retorna un enetro nuevo e1 ^ e2*/
void      entero_potencia(Entero* a, int n, Entero* resp);

/** Retorna True si e < a[i,j] con misma cantida de digitos*/
bool      menor_igual(Entero* e, uint8_t* a, int i, int j);

/** Retorna cuantas veces cabe e en a[i,j] y disminuye a[i:j]*/
uint8_t   entero_cabe(Entero* e, uint8_t* a, int i, int j);

/** Guarda en divi un entero nuevo e1 // e2 y en mod e1 % e2*/
void      entero_division(Entero* e1, Entero* e2, Entero* divi, Entero* mod);

/** Guarda en resp un entero nuevo (a ** b) mod n*/
void      entero_potencia_mod(Entero* a, Entero* b, Entero* n, Entero* resp);

/** Guarda en resp maximo comun divisor entre a y b*/
void      entero_mcd(Entero* a, Entero* b, Entero* resp);

/** Retirna un entero nuevo con la suma de los digitos de n*/
Entero*   entero_suma_digitos(Entero* n);

/** Destruye el entero*/
void      entero_destroy(Entero* entero);

#endif
