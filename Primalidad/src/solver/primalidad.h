#ifndef PRIMALIDAD
#define PRIMALIDAD

#include "entero.h"
#include "pcg_basic.h"

/** Retorna true si es divisible por 3, y false en caso contrario*/
bool     tres_divisible(Entero* n);

/** Retorna true si es divisible por 5, y false en caso contrario*/
bool     cinco_divisible(Entero* n);

/** Retorna true si existe m perteneciente a [i,i] tal que n = m ** k*/
bool     tiene_raiz_entera(Entero* n, int k, Entero* i, Entero* j);

/** Retorna true si n es potencia de un entero*/
bool     es_potencia(Entero* n);

/** Guarda en resp un numero random entre 1 y n - 1*/
void     get_random(Entero* resp, Entero* n);

/** Genera k numeros entre 1 y n - 1*/
Entero** generar(Entero* n, int k);

/** Retorna true o false diciendo si es primo o no*/
bool     es_primo(Entero* n, int k);

#endif
