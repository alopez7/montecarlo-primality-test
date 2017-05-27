#include "primalidad.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void testo_primo(void* stream, Entero* n, int k){
  if(es_primo(n, k))
  {
    fprintf(stream, "PRIMO");
  }
  else
  {
    fprintf(stream, "COMPUESTO");
  }
}

int main(int argc, char *argv[]) {

  //Revisar input
  if (argc != 1){
    printf("ERROR, debe ejecutar el programa como ./solver sin argumentos\n");
    return 1;
  }

  //Inicializo variables globales
  uno = entero_string_init("1");
  dos = entero_string_init("2");

  //PROGRAMA

  char buf[1024*64];
  bool scanning = true;
  int k;
  while (scanning){
    printf("\n");
    printf("Ingrese una opcion:\n");
    printf("  1. Ingresar datos por consola\n");
    printf("  2. Ingresar archivo de datos\n");
    printf("  3. Salir\n");
    printf(">> ");
    if (!fscanf(stdin, "%s", buf)){
      printf("Error: el input ingresado es muy largo\n");
      continue;
    }
    switch (atoi(buf)) {
      case  1:
        do {
          printf("n >> ");
          if (!fscanf(stdin, "%s", buf))
          {
            printf("Error: el input ingresado es muy largo\n");
            continue;
          }
          if (!atoi(buf) || atoi(buf) <= 0)
          {
            printf("Input inválido: %s\n  Debe ser un número entero positivo\n", buf);
          }
        } while(!atoi(buf) || atoi(buf) <= 0);
        Entero* n = entero_string_init(buf);

        do {
          printf("k >> ");
          if (!fscanf(stdin, "%s", buf)){
            printf("Error: el input ingresado es muy largo\n");
            continue;
          }
          if(!atoi(buf) || atoi(buf) <= 0)
          {
            printf("Input inválido: %s\n  Debe ser un número entero positivo\n", buf);
          }
        } while(!atoi(buf) || atoi(buf) <= 0);

        k = atoi(buf);

        testo_primo(stdout, n, k);
        printf("\n");

        entero_destroy(n);
        break;
      case  2:
        printf("Indique el archivo de entrada\n");
        FILE* input = NULL;
        FILE* output = NULL;
        do {
          printf("entrada >> ");
          if (!fscanf(stdin, "%s", buf)){
            printf("Error: el input ingresado es muy largo\n");
            continue;
          }
          input = fopen(buf, "r");
          if(!input)
          {
            printf("Error: el archivo %s no pudo ser abierto\n", buf);
          }
        } while(!input);

        printf("Indique el archivo de salida\n");
        do {
          printf("salida >> ");

          if (!fscanf(stdin, "%s", buf)){
            printf("Error: el input ingresado es muy largo\n");
            continue;
          }
          output = fopen(buf, "w");
          if(!output)
          {
            printf("Error: el archivo %s no pudo ser abierto\n", buf);
          }
        } while(!output);

        int status;

        int count = 0;

        while(true){
          status = fscanf(input, "%s %d", buf, &k);
          if(status == 0)
          {
            printf("Error leyendo el archivo de input\n");
            break;
          }

          /* Fuck u, comma */
          buf[strlen(buf) - 1] = '\0';

          Entero* n = entero_string_init(buf);
          if(0 < count++) fprintf(output, ", ");

          // entero_imprimir(n);
          // printf(" %d : ", k);
          testo_primo(output, n, k);
          // printf("\n");
          entero_destroy(n);

          status = fscanf(input, ", ");

          if(status == EOF)
          {
            break;
          }
        }

        fprintf(output, "\n");

        fclose(input);
        fclose(output);
        break;
      case  3:
        scanning = false;
        break;
      default:
        printf("Opción inválida: %s\n", buf);
    }
  }

  // Entero* n = entero_string_init(argv[1]);
  // if (es_primo(n, 100)){
  //   printf("PRIMO\n");
  // }
  // else {
  //   printf("COMPUESTO\n");
  // }
  // entero_destroy(n);


  //FIN PROGRAMA

  //Libero variables globales
  entero_destroy(uno);
  entero_destroy(dos);
  return 0;
}
