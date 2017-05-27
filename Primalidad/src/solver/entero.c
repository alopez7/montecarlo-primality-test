#include "entero.h"
#include <unistd.h>

/** Inicializa el entero*/
Entero* entero_init(uint8_t* digitos, int n_digitos, int t_arreglo){
  Entero* ent = malloc(sizeof(Entero));

  ent -> digitos = digitos;
  ent -> n_digitos = n_digitos;
  ent -> t_arreglo = t_arreglo;
  ent -> cero = false;

  return ent;
}

/** Inicializa el entero desde un string*/
Entero* entero_string_init(char* string){
  int n = strlen(string);
  uint8_t* digitos = malloc(sizeof(uint8_t) * n);
  for (int i = 0; i < n; i++){
    digitos[n - i - 1] = string[i]-'0';
  }
  return entero_init(digitos, n, n);
}

/** Inicializa un entero como 0*/
Entero* entero_cero(){
  Entero* ent = malloc(sizeof(Entero));

  ent -> digitos = NULL;
  ent -> n_digitos = 0;
  ent -> t_arreglo = 0;
  ent -> cero = true;

  return ent;
}

/** Retorna la suma, y guarda en d3 el carry*/
uint8_t digito_suma(uint8_t d1, uint8_t d2, uint8_t carryIn, uint8_t* carryOut){
  uint8_t respuesta = d1 + d2 + carryIn;
  *carryOut = respuesta >= 10;
  return respuesta - *carryOut * 10;
}

/** Imprime el entero*/
void entero_imprimir(Entero* e){
  if (e -> cero){
    printf("0");
    return;
  }
  for(int i = e -> n_digitos - 1; i >= 0; i--){
    printf("%i", e -> digitos[i]);
  }
}

/** Separa el entero 'a' en 'a1' y 'a2' donde a2 tiene n digitos*/
void entero_separar(Entero* a, Entero* a1, Entero* a2, int n2){
  //Caso base: n2 >= n_digitos
  if (n2 >= a -> n_digitos){
    //a2 es una copia de a
    uint8_t* digitos2 = malloc(sizeof(uint8_t) * a -> n_digitos);
    for (int i = 0; i < a -> n_digitos; i++){
      digitos2[i] = a -> digitos[i];
    }
    a2 -> digitos = digitos2;
    a2 -> cero = false;
    a2 -> n_digitos = a -> n_digitos;
    a2 -> t_arreglo = a -> t_arreglo;

    //a1 es cero
    a1 -> cero = true;
    a1 -> digitos = NULL;
    a1 -> n_digitos = 0;
    a1 -> t_arreglo = 0;
    return;
  }

  //Creando los digitos de a1 y a2
  int n_digitos1 = a -> n_digitos - n2;
  int n_digitos2 = n2;
  uint8_t* digitos1 = malloc(sizeof(uint8_t) * n_digitos1);
  uint8_t* digitos2 = malloc(sizeof(uint8_t) * n_digitos2);
  int n_real_digitos2 = 0;
  for (int i = n_digitos2 - 1; i >= 0; i--){
    if (a -> digitos[i] != 0 && n_real_digitos2 == 0){
      n_real_digitos2 = i + 1;
    }
    digitos2[i] = a -> digitos[i];
  }
  for (int i = 0; i < n_digitos1; i++){
    digitos1[i] = a -> digitos[i + n_digitos2];
  }

  //Guardando el valor en a1 y a2
  a1 -> cero = false;
  a1 -> n_digitos = n_digitos1;
  a1 -> t_arreglo = n_digitos1;
  a1 -> digitos = digitos1;

  if (n_real_digitos2 == 0){
    a2 -> cero = true;
    a2 -> n_digitos = 0;
    a2 -> t_arreglo = 0;
    a2 -> digitos = NULL;
    free(digitos2);
  }
  else {
    a2 -> cero = false;
    a2 -> n_digitos = n_real_digitos2;
    a2 -> t_arreglo = n_digitos2;
    a2 -> digitos = digitos2;
  }
}

/** Retorna -1 (e1 < e2), 0 (=) o 1 (e1 > e2)*/
int entero_comparar(Entero* e1, Entero* e2){
  if (e1 -> cero || e2 -> cero){
    if (!e1 -> cero){
      return 1;
    }
    if (!e2 -> cero){
      return -1;
    }
    return 0;
  }
  if (e1 -> n_digitos < e2 -> n_digitos){
    return -1;
  }
  if (e1 -> n_digitos == e2 -> n_digitos){
    for (int i = e1 -> n_digitos - 1; i >= 0; i--){
      if (e1 -> digitos[i] < e2 -> digitos[i]){
        return -1;
      }
      if (e1 -> digitos[i] > e2 -> digitos[i]){
        return 1;
      }
    }
    return 0;
  }
  return 1;
}

/** Retorna -1 (e1 < e2), 0 (=) o 1 (e1 > e2)*/
int entero_digito_comparar(Entero* e, uint8_t i){
  if (e -> cero){
    if (i == 0){
      return 0;
    }
    return -1;
  }
  if (e -> n_digitos > 1){
    return 1;
  }
  if (e -> digitos[0] > i){
    return 1;
  }
  else if (e -> digitos[0] == i){
    return 0;
  }
  else {
    return -1;
  }
}

/** Guarda en resp el entero nuevo e1 + e2*/
void entero_suma(Entero* e1, Entero* e2, Entero* resp){

  //Si alguno de los valores es 0
  if (e1 -> cero || e2 -> cero){
    if (e1 -> cero && e2 -> cero){
      resp -> cero = true;
      resp -> digitos = NULL;
      resp -> n_digitos = 0;
      resp -> t_arreglo = 0;
      return;
    }
    Entero* ee;
    if (e1 -> cero){
      ee = e2;
    }
    if (e2 -> cero){
      ee = e1;
    }
    uint8_t* digitos = malloc(sizeof(uint8_t) * ee -> n_digitos);
    for (int i = 0; i < ee -> n_digitos; i++){
      digitos[i] = ee -> digitos[i];
    }
    resp -> digitos = digitos;
    resp -> cero = false;
    resp -> n_digitos = ee -> n_digitos;
    resp -> t_arreglo = ee -> t_arreglo;
    return;
  }

  //Minimo y maximo de digitos
  int m;
  int M;
  Entero* eM;
  if (e1 -> n_digitos >= e2 -> n_digitos){
    M = e1 -> n_digitos;
    eM = e1;
    m = e2 -> n_digitos;
  }
  else {
    M = e2 -> n_digitos;
    eM = e2;
    m = e1 -> n_digitos;
  }

  //Crear las variables para el entero
  int t_arreglo = M + 1;
  uint8_t* digitos = malloc(sizeof(uint8_t) * t_arreglo);
  int n_digitos;

  //Sumar digito a digito
  uint8_t carry = 0;
  for (int i = 0; i < m; i++){
    digitos[i] = digito_suma(e1 -> digitos[i], e2 -> digitos[i], carry, &carry);
  }

  //Seguir sumando si uno tiene más dígitos que el otro
  if (m != M) {
    for (int i = m; i < M; i++){
      digitos[i] = digito_suma(eM -> digitos[i], 0, carry, &carry);
    }
  }

  digitos[M] = carry;
  n_digitos = M + carry;

  resp -> digitos = digitos;
  resp -> n_digitos = n_digitos;
  resp -> t_arreglo = t_arreglo;
  resp -> cero = false;
}

/** Guarda en resp el entero nuevo e1 + e2 (e1 >= e2)*/
void entero_resta(Entero* e1, Entero* e2, Entero* resp){

    //Si ambos son iguales
    if (entero_comparar(e1, e2) == 0){
      resp -> cero = true;
      resp -> digitos = NULL;
      resp -> n_digitos = 0;
      resp -> t_arreglo = 0;
      return;
    }

    //Si alguno de los valores es 0
    if (e1 -> cero || e2 -> cero){
      if (e1 -> cero && e2 -> cero){
        resp -> cero = true;
        resp -> digitos = NULL;
        resp -> n_digitos = 0;
        resp -> t_arreglo = 0;
        return;
      }
      Entero* ee = e1;
      uint8_t* digitos = malloc(sizeof(uint8_t) * ee -> n_digitos);
      for (int i = 0; i < ee -> n_digitos; i++){
        digitos[i] = ee -> digitos[i];
      }
      resp -> digitos = digitos;
      resp -> cero = false;
      resp -> n_digitos = ee -> n_digitos;
      resp -> t_arreglo = ee -> t_arreglo;
      return;
    }


    //Minimo y maximo de digitos
    int M = e1 -> n_digitos;
    int m = e2 -> n_digitos;

    //Crear las variables para el entero
    int t_arreglo = M;
    uint8_t* digitos = malloc(sizeof(uint8_t) * t_arreglo);
    int n_digitos = 0;

    //Restar digito a digito
    int carry = 0;
    int d2;
    for (int i = 0; i < M; i++){
      if (i >= m){
        d2 = 0;
      }
      else {
        d2 = e2 -> digitos[i];
      }
      if (e1 -> digitos[i] - carry >= d2){
        digitos[i] = e1 -> digitos[i] - carry - d2;
        carry = 0;
      }
      else {
        digitos[i] = 10 + e1 -> digitos[i] - carry - d2;
        carry = 1;
      }

      if (digitos[i] != 0){
        n_digitos = i + 1;
      }
    }
    resp -> digitos = digitos;
    resp -> n_digitos = n_digitos;
    resp -> t_arreglo = t_arreglo;
    resp -> cero = false;
}

/** Multiplica a por 10 n veces y guarda en resp a*10^n*/
void entero_agregar_ceros(Entero* a, Entero* resp, int n){
  //Caso base a = 0
  if (a -> cero){
    resp -> cero = true;
    resp -> digitos = NULL;
    resp -> n_digitos = 0;
    resp -> t_arreglo = 0;
    return;
  }
  //Caso normal
  uint8_t* digitos = malloc(sizeof(uint8_t) * (a -> n_digitos + n));
  for (int i = 0; i < n; i++){
    digitos[i] = 0;
  }
  for (int i = 0; i < a -> n_digitos; i++){
    digitos[i + n] = a -> digitos[i];
  }
  resp -> cero = false;
  resp -> digitos = digitos;
  resp -> n_digitos = a -> n_digitos + n;
  resp -> t_arreglo = resp -> n_digitos;
}

/** Guarda en resp un entero nuevo e1 * e2*/
void entero_multiplicacion(Entero* a, Entero* b, Entero* resp){

  //Caso base: Si alguno es cero
  if (a -> cero || b -> cero){

    //Por si estoy sobreescribiendo una variable
    if (a == resp && !a -> cero){
      free(a -> digitos);
    }
    if (b == resp && !b -> cero){
      free(b -> digitos);
    }
    resp -> cero = true;
    resp -> digitos = NULL;
    resp -> n_digitos = 0;
    resp -> t_arreglo = 0;
    return;
  }
  // Caso base: si uno de los números tiene solo 1 dígito
  if (a -> n_digitos == 1 || b -> n_digitos == 1){

    int t_arreglo = a -> n_digitos + b -> n_digitos;
    uint8_t* digitos = malloc(sizeof(uint8_t) * t_arreglo);
    int n_digitos;
    Entero* num;
    uint8_t dig;
    if (a -> n_digitos == 1){
      dig = a -> digitos[0];
      num = b;
    }
    else {
      dig = b -> digitos[0];
      num = a;
    }
    uint8_t carry = 0;
    uint8_t res = 0;
    for (int i = 0; i < num -> n_digitos; i++){
      res = dig * num -> digitos[i] + carry;
      if (res < 10){
        digitos[i] = res;
        carry = 0;
      }
      else{
        digitos[i] = res % 10;
        carry = res / 10;
      }
    }
    if (carry > 0){
      digitos[num -> n_digitos] = carry;
      n_digitos = num -> n_digitos + 1;
    }
    else {
      n_digitos = num -> n_digitos;
    }

    //Por si estoy sobreescribiendo una variable
    if (a == resp){
      free(a -> digitos);
    }
    if (b == resp){
      free(b -> digitos);
    }
    resp -> digitos = digitos;
    resp -> n_digitos = n_digitos;
    resp -> t_arreglo = t_arreglo;
    resp -> cero = false;
    return;
  }

  // Caso recursivo
  else {
    int n1;
    int n2;
    int max_n;
    if (a -> n_digitos >= b -> n_digitos){
      max_n = a -> n_digitos;
    }
    else {
      max_n = b -> n_digitos;
    }
    if (max_n % 2 == 0){
      n1 = max_n / 2;
      n2 = n1;
    }
    else {
      n1 = (max_n - 1) / 2 + 1;
      n2 = n1 - 1;
    }

    //Caluculo a1, a2, b1 y b2
    Entero* a1 = malloc(sizeof(Entero));
    Entero* a2 = malloc(sizeof(Entero));
    Entero* b1 = malloc(sizeof(Entero));
    Entero* b2 = malloc(sizeof(Entero));
    entero_separar(a, a1, a2, n2);
    entero_separar(b, b1, b2, n2);

    //Calculo c1 y c2
    Entero* c1 = malloc(sizeof(Entero));
    Entero* c2 = malloc(sizeof(Entero));
    Entero* c3 = malloc(sizeof(Entero));
    entero_multiplicacion(a1, b1, c1);
    entero_multiplicacion(a2, b2, c2);

    //Calculo c3
    Entero* aux1 = malloc(sizeof(Entero));
    Entero* aux2 = malloc(sizeof(Entero));
    entero_suma(a1, a2, aux1);
    entero_suma(b1, b2, aux2);
    entero_multiplicacion(aux1, aux2, c3);

    //Calculo c1 + c2
    Entero* c12 = malloc(sizeof(Entero));
    entero_suma(c1, c2, c12);

    //Calculo c3 - (c1 + c2)
    Entero* c312 = malloc(sizeof(Entero));
    entero_resta(c3, c12, c312);

    //Calculo los datos a sumar
    Entero* c1_10 = malloc(sizeof(Entero));
    Entero* c312_10 = malloc(sizeof(Entero));
    entero_agregar_ceros(c1, c1_10, n2 * 2);
    entero_agregar_ceros(c312, c312_10, n2);

    //sumo los que me quedan
    Entero* aux3 = malloc(sizeof(Entero));
    entero_suma(c1_10, c312_10, aux3);

    //Por si estoy sobreescribiendo una variable
    if (a == resp){
      free(a -> digitos);
    }
    if (b == resp){
      free(b -> digitos);
    }

    entero_suma(aux3, c2, resp);

    //Destruyo todo lo que use intermedio
    entero_destroy(a1);
    entero_destroy(a2);
    entero_destroy(b1);
    entero_destroy(b2);
    entero_destroy(c1);
    entero_destroy(c2);
    entero_destroy(c3);
    entero_destroy(aux1);
    entero_destroy(aux2);
    entero_destroy(aux3);
    entero_destroy(c12);
    entero_destroy(c312);
    entero_destroy(c1_10);
    entero_destroy(c312_10);
  }
}

/** Guarda en resp un entero nuevo e1 ^ e2*/
void entero_potencia(Entero* a, int n, Entero* resp){

  //Caso base: n = 1
  if (n == 1){
    uint8_t* digitos;
    digitos = malloc(sizeof(uint8_t) * a -> n_digitos);
    for (int i = 0; i < a -> n_digitos; i++){
      digitos[i] = a -> digitos[i];
    }
    resp -> digitos = digitos;
    resp -> cero = false;
    resp -> n_digitos = a -> n_digitos;
    resp -> t_arreglo = a -> n_digitos;
    return;
  }

  //Caso con n par
  else if (n % 2 == 0){
    //Calculo an2 = a ** (n/2)
    Entero* an2 = malloc(sizeof(Entero));
    entero_potencia(a, n/2, an2);
    //Calculo resp = an2 * an2
    entero_multiplicacion(an2, an2, resp);
    //Destruyo an2
    entero_destroy(an2);
    return;
  }

  //Caso con n impar
  else {
    //Calculo an2 = a ** ((n-1)/2)
    Entero* an2 = malloc(sizeof(Entero));
    entero_potencia(a, (n-1)/2, an2);
    //Calculo aux = an2 * an2
    Entero* aux = malloc(sizeof(Entero));
    entero_multiplicacion(an2, an2, aux);
    //Calculo resp = aux * a
    entero_multiplicacion(aux, a, resp);
    //Destruyo las variables auxiliares que hice
    entero_destroy(an2);
    entero_destroy(aux);
  }
}

/** Retorna True si e <= a[i,j]*/
bool menor_igual(Entero* e, uint8_t* a, int i, int j){

  //Caso digitos de e < i - j + 1
  if (e -> n_digitos < i - j + 1 && a[i] != 0){
    return true;
  }
  //Caso con misma cantidad de digitos
  else{
    for (int q = e -> n_digitos - 1; q >= 0; q--){
      if (e -> digitos[q] > a[q + j]){
        return false;
      }
      else if (e -> digitos[q] < a[q + j]){
        return true;
      }
    }
    return true;
  }
}

/** Retorna cuantas veces cabe e en a[i:j] y disminuye a[i:j]*/
uint8_t entero_cabe(Entero* e, uint8_t* a, int i, int j){
  uint8_t contador = 0;
  //Caso base i - j + 1 < n_digitos
  if (i - j + 1 < e -> n_digitos){
    return contador;
  }
  //Caso i - j + 1 >= n_digitos
  else if (i - j + 1 >= e -> n_digitos){
    //Mientras e cabe en a
    while (menor_igual(e, a, i, j)){
      //Restar
      int carry = 0;
      int d2;
      for (int q = 0; q < i - j + 1; q++){
        if (q >= e -> n_digitos){
          d2 = 0;
        }
        else {
          d2 = e -> digitos[q];
        }
        if (a[q + j] >= carry + d2){
          a[q + j] -= carry + d2;
          carry = 0;
        }
        else {
          a[q + j] += 10;
          a[q + j] -= carry + d2;
          carry = 1;
        }
      }
      //Y sumar 1 al contador
      contador += 1;

    }
  }
  return contador;
}

/** Guarda en divi un entero nuevo e1 // e2 y en mod e1 % e2*/
void entero_division(Entero* e1, Entero* e2, Entero* divi, Entero* mod){

  //Creo los arreglos de digitos del modulo y la division
  int t_arreglo_divi = e1 -> n_digitos - e2 -> n_digitos + 1;
  if (t_arreglo_divi <= 0){
    t_arreglo_divi = 1;
  }
  int t_arreglo_mod = e1 -> n_digitos;
  uint8_t* digitos_mod = malloc(sizeof(uint8_t) * t_arreglo_mod);
  uint8_t* digitos_divi = malloc(sizeof(uint8_t) * t_arreglo_divi);

  //Copio el dividendo en el modulo
  for (int k = 0; k < e1 -> n_digitos; k++){
    digitos_mod[k] = e1 -> digitos[k];
  }

  //Creo los indices que se mueven en los distintos arreglos
  // mod[i:j] es el numero en el cual quiero saber si e2 cabe en cad iteracion
  int i = e1 -> n_digitos - 1;
  // j además es el indice del digito del resultado de la division
  int j = i - e2 -> n_digitos + 1;
  // n_digitos_divi indica la cantidad de digitos de la division
  int n_digitos_divi = 0;
  //Mientras me queden digitos en el dividento
  while (j >= 0){
    //Guardo en division[k] la cantidad de veces que cabe el dividendo
    // y resto al dividento esa cantidad
    digitos_divi[j] = entero_cabe(e2, digitos_mod, i, j);

    //Tomo el mayor digito de la division tal que no es cero,
    //Y es la cantidad de digitos de la division
    if (digitos_divi[j] != 0 && j + 1 > n_digitos_divi){
      n_digitos_divi = j + 1;
    }
    // agrego un nuevo digito
    j--;
    // Muevo i hasta que indique un digito que no es 0, o llegue a j
    while (i > j && digitos_mod[i] == 0){
      i--;
    }
  }

  //Creo divi si es cero
  if (n_digitos_divi == 0){
    divi -> cero = true;
    divi -> digitos = NULL;
    free(digitos_divi);
    divi -> n_digitos = 0;
    divi -> t_arreglo = 0;
  }
  //Creo divi si no es cero
  else {
    divi -> cero = false;
    divi -> digitos = digitos_divi;
    divi -> n_digitos = n_digitos_divi;
    divi -> t_arreglo = t_arreglo_divi;
  }

  //Comprobar si modulo es cero y contar sus digitos
  int n_digitos_mod = 0;
  for (int i = t_arreglo_mod - 1; i >= 0; i--){
    if (digitos_mod[i] != 0){
      n_digitos_mod = i + 1;
      break;
    }
  }
  //Caso modulo es cero
  if (n_digitos_mod == 0){
    mod -> cero = true;
    mod -> digitos = NULL;
    free(digitos_mod);
    mod -> n_digitos = n_digitos_mod;
    mod -> t_arreglo = t_arreglo_mod;
  }

  //Caso modulo no es cero
  else {
    mod -> cero = false;
    mod -> digitos = digitos_mod;
    mod -> n_digitos = n_digitos_mod;
    mod -> t_arreglo = t_arreglo_mod;
  }
}

/** Guarda en resp un entero nuevo (a ** b) mod n*/
void entero_potencia_mod(Entero* a, Entero* b, Entero* n, Entero* resp){
  //Caso base: retorno a mod n
  if (entero_digito_comparar(b, 1) == 0){
    Entero* divi = malloc(sizeof(Entero));
    entero_division(a, n, divi, resp);
    entero_destroy(divi);
    return;
  }
  //Caso recursivo con b par
  else if (b -> digitos[0] % 2 == 0){
    //Calculo b2 = b/2
    Entero* b2 = malloc(sizeof(Entero));
    Entero* mod = malloc(sizeof(Entero));
    entero_division(b, dos, b2, mod);
    //Calculo a = a ** (b/2) mod n
    Entero* a2 = malloc(sizeof(Entero));
    entero_potencia_mod(a, b2, n, a2);
    //Calculo mult = a2 * a2
    Entero* mult = malloc(sizeof(Entero));
    entero_multiplicacion(a2, a2, mult);
    //Calculo resp = mult % n
    Entero* divi = malloc(sizeof(Entero));
    entero_division(mult, n, divi, resp);
    //Destruyo todo
    entero_destroy(b2);
    entero_destroy(mod);
    entero_destroy(a2);
    entero_destroy(mult);
    entero_destroy(divi);
    return;
  }
  else {
    //Calculo b2 = b/2
    Entero* b2 = malloc(sizeof(Entero));
    Entero* mod = malloc(sizeof(Entero));
    entero_division(b, dos, b2, mod);
    //Calculo a = a ** (b/2) mod n
    Entero* a2 = malloc(sizeof(Entero));
    entero_potencia_mod(a, b2, n, a2);
    //Calculo mult = a2 * a2
    Entero* mult = malloc(sizeof(Entero));
    entero_multiplicacion(a2, a2, mult);
    Entero* aux = malloc(sizeof(Entero));
    entero_multiplicacion(mult, a, aux);
    //Calculo resp = aux % n
    Entero* divi = malloc(sizeof(Entero));
    entero_division(aux, n, divi, resp);
    //Destruyo todo
    entero_destroy(b2);
    entero_destroy(mod);
    entero_destroy(a2);
    entero_destroy(mult);
    entero_destroy(aux);
    entero_destroy(divi);
    return;
  }
}

/** Guarda en resp maximo comun divisor entre a y b*/
void entero_mcd(Entero* a, Entero* b, Entero* resp){
  //Caso base
  if (b -> cero){
    uint8_t* digitos = malloc(sizeof(uint8_t) * a -> n_digitos);
    for (int i = 0; i < a -> n_digitos; i++){
      digitos[i] = a -> digitos[i];
    }
    resp -> digitos = digitos;
    resp -> cero = false;
    resp -> n_digitos = a -> n_digitos;
    resp -> t_arreglo = a -> n_digitos;
    return;
  }

  //Caso recursivo
  else {
    Entero* divi = malloc(sizeof(Entero));
    Entero* mod = malloc(sizeof(Entero));
    entero_division(a, b, divi, mod);
    entero_destroy(divi);
    entero_mcd(b, mod, resp);
    entero_destroy(mod);
  }
}

/** Retirna un entero nuevo con la suma de los digitos de n*/
Entero* entero_suma_digitos(Entero* n){
  int dig = 0;
  for (int i = 0; i < n -> n_digitos; i++){
    dig += n -> digitos[i];
  }
  char buf[1024];
  sprintf(buf, "%i", dig);
  return entero_string_init(buf);
}

/** Destruye el entero*/
void entero_destroy(Entero* entero){
  if (entero -> digitos){
    free(entero -> digitos);
  }
  free(entero);
}
