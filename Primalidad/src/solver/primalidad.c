#include "primalidad.h"

/** Retorna true si es divisible por 3, y false en caso contrario*/
bool tres_divisible(Entero* n){
  //Caso base numero tiene 1 digito
  if (n -> n_digitos == 1){
    if (n -> digitos[0] == 3 || n -> digitos[0] == 6 || n -> digitos[0] == 9){
      return true;
    }
    return false;
  }

  //Caso recursivo
  Entero* nuevo = entero_suma_digitos(n);
  bool td = tres_divisible(nuevo);
  entero_destroy(nuevo);
  return td;
}

/** Retorna true si es divisible por 5 (sin contar el 5), y false en caso contrario*/
bool cinco_divisible(Entero* n){
  if (n -> n_digitos == 1){
    return false;
  }
  else if (n -> digitos[0] == 5 || n -> digitos[0] == 0){
    return true;
  }
  return false;
}

/** Retorna true si existe m perteneciente a [i,i] tal que n = m ** k*/
bool tiene_raiz_entera(Entero* n, int k, Entero* i, Entero* j){
  int comp = entero_comparar(i, j);

  //Caso i = j
  if (comp == 0){
    Entero* potencia = malloc(sizeof(Entero));
    entero_potencia(i, k, potencia);
    //Si i ** k = n
    if (entero_comparar(potencia, n) == 0){
      entero_destroy(potencia);
      return true;
    }
    entero_destroy(potencia);
    return false;
  }

  //Caso i < j
  else if (comp < 0){
    // ij = i + j
    Entero* ij = malloc(sizeof(Entero));
    entero_suma(i, j, ij);
    // p = piso((i + j) / 2)
    Entero* p = malloc(sizeof(Entero));
    Entero* mod = malloc(sizeof(Entero));
    entero_division(ij, dos, p, mod);

    //Destruyo los valores intermedios
    entero_destroy(ij);
    entero_destroy(mod);

    //val = p**k
    Entero* val = malloc(sizeof(Entero));
    entero_potencia(p, k, val);

    //Comparo val con n
    int comp_val_n = entero_comparar(val, n);

    //destruyo val
    entero_destroy(val);

    //Si val = n retorno si
    if (comp_val_n == 0){
      entero_destroy(p);
      return true;
    }
    //Si val < n
    else if (comp_val_n < 0){
      // pM = p + 1
      Entero* pM = malloc(sizeof(Entero));
      entero_suma(p, uno, pM);

      //Destruyo todo lo que ya no necesito
      entero_destroy(p);
      bool respuesta = tiene_raiz_entera(n, k, pM, j);
      entero_destroy(pM);

      return respuesta;
    }
    //Si val > n
    else{
      // pm = p - 1
      Entero* pm = malloc(sizeof(Entero));
      entero_resta(p, uno, pm);

      //Destruyo todo lo que ya no necesito
      entero_destroy(p);
      bool respuesta = tiene_raiz_entera(n, k, i, pm);
      entero_destroy(pm);

      return respuesta;
    }
  }

  //Caso i > j
  else {
    return false;
  }
}

/** Retorna true si n es potencia de un entero*/
bool es_potencia(Entero* n){

  if (entero_digito_comparar(n, 3) <= 0){
    return false;
  }
  else{

    for (int k = 2; k <= n -> n_digitos * 3.33;k++){
      if (tiene_raiz_entera(n, k, uno, n)){
        return true;
      }
    }
    return false;

    // //k = 2
    // int k = 2;
    // //p = 4
    // Entero* p = entero_string_init("4");
    // //mientras p < n (mismo que k < log_2(n))
    // while (entero_comparar(p, n) <= 0){
    //   //Si tiene_raiz_entera(n,k,1,n)
    //   if (tiene_raiz_entera(n, k, uno, n)){
    //     entero_destroy(p);
    //     return true;
    //   }
    //   //k = k + 1
    //   k = k + 1;
    //   //p = p * 2
    //   entero_multiplicacion(p, dos, p);
    // }
    // entero_destroy(p);
    // return false;

  }
}

/** Guarda en resp un numero random entre 1 y n - 1*/
void get_random(Entero* resp, Entero* m){
  Entero* n = malloc(sizeof(Entero));
  entero_resta(m, dos, n);
  uint8_t* digitos = malloc(sizeof(uint8_t) * n -> n_digitos);
  bool restricted = true;
  uint32_t max;
  int n_digitos = 0;
  for (int i = n -> n_digitos - 1; i >= 0; i--){
    if (restricted){
      max = n -> digitos[i] + 1;
    }
    else {
      max = 10;
    }

    if (max == 1){
      digitos[i] = 0;
    }
    else {
      digitos[i] = pcg32_boundedrand(max);
    }

    if (restricted && digitos[i] < max - 1){
      restricted = false;
    }
    if (n_digitos < i + 1 && digitos[i] != 0){
      n_digitos = i + 1;
    }
  }
  Entero* aux = entero_init(digitos, n_digitos, n -> n_digitos);
  entero_suma(aux, uno, resp);

  //Libero la memoria
  entero_destroy(n);
  entero_destroy(aux);
}

/** Genera k numeros entre 1 y n - 1*/
Entero** generar(Entero* n, int k){
  Entero** randoms = malloc(sizeof(Entero*) * k);
  for (int i = 0; i < k; i++){
    randoms[i] = malloc(sizeof(Entero));
    get_random(randoms[i], n);
  }
  return randoms;
}

/** Retorna true o false diciendo si es primo o no*/
bool es_primo(Entero* n, int k){
  //Si n == 1: Compuesto
  if (entero_digito_comparar(n, 1) == 0){
    return false;
  }
  //Si n == 2 o n == 3: Primo
  else if (entero_digito_comparar(n, 2) == 0 || entero_digito_comparar(n, 3) == 0){
    return true;
  }
  //Si n es par: Compuesto
  else if (n -> digitos[0] % 2 == 0){
    return false;
  }
  //Si es divisible por 3: compuesto
  else if (tres_divisible(n)){
    return false;
  }
  //Si es divisible por 5 (excepto si es 5): compuesto
  else if (cinco_divisible(n)){
    return false;
  }
  //Si n es potencia: Compuesto
  else if (es_potencia(n)){
    return false;
  }
  else {

    //Genero los numeros aleatorios y los guardo en A
    Entero** A = generar(n,k);
    //Creo la lista B
    Entero** B = malloc(sizeof(Entero*) * k);

    for (int i = 0; i < k; i++){
      Entero* mcd = malloc(sizeof(Entero));
      //Calculo el mcd
      //Libero sus digitos si ya existian
      entero_mcd(A[i], n, mcd);
      //Si el mcd es dintinto de 1
      if (entero_digito_comparar(mcd, 1) != 0){
        //Liberar toda la memoria
        for (int j = 0; j < k; j++){
          entero_destroy(A[j]);
        }
        free(A);
        for (int j = 0; j < i; j++){
          entero_destroy(B[j]);
        }
        free(B);
        entero_destroy(mcd);
        //Si mcd ditinto de 1: Compuesto
        return false;
      }
      //Si el mcd es 1
      else {
        //Calculo n2 =  (n - 1)/2
        Entero* n2 = malloc(sizeof(Entero));
        Entero* mod = malloc(sizeof(Entero));
        entero_division(n, dos, n2, mod);
        B[i] = malloc(sizeof(Entero));
        entero_potencia_mod(A[i], n2, n, B[i]);
        entero_destroy(n2);
        entero_destroy(mod);
        entero_destroy(mcd);
      }
    }

    //Destruyo A y mcd
    for (int j = 0; j < k; j++){
      entero_destroy(A[j]);
    }
    free(A);

    //Creo neg, bimodn y n1
    int neg = 0;
    for (int i = 0; i < k; i++){
      //Calculo bimodn = b[i] mod n
      Entero* n1 = malloc(sizeof(Entero));
      Entero* divi = malloc(sizeof(Entero));
      Entero* bimodn = malloc(sizeof(Entero));
      entero_division(B[i], n, divi, bimodn);
      //Calculo n1 = n - 1
      entero_resta(n, uno, n1);
      //Destruyo divi
      entero_destroy(divi);

      //Si b[i] = -1 mod n
      if (entero_comparar(bimodn, n1) == 0){
        // free(bimodn -> digitos);
        // free(divi -> digitos);
        // free(n1 -> digitos);
        neg += 1;
      }
      //Si b[i] != 1 mod n: Compuesto
      else if (entero_comparar(bimodn, uno) != 0){
        //Destruyo todo
        entero_destroy(bimodn);
        // entero_destroy(divi);
        entero_destroy(n1);
        for (int j = 0; j < k; j++){
          entero_destroy(B[j]);
        }
        free(B);
        return false;
      }
      entero_destroy(bimodn);
      entero_destroy(n1);
    }

    //Destruyo todo
    // entero_destroy(divi);
    for (int j = 0; j < k; j++){
      entero_destroy(B[j]);
    }
    free(B);

    //Si neg = 0: Compuesto
    if (neg == 0){
      return false;
    }
    //Sino: primo
    else{
      return true;
    }
  }
}
