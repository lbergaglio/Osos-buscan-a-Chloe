#ifndef __TEST_DE_PERSONALIDAD__
#define __TEST_DE_PERSONALIDAD__

#include<stdio.h>
#include<stdbool.h>



/*VALIDACIONES*/
bool valido_respuesta_1 (char respuesta_1);
bool valido_respuesta_2 (char respuesta_2);
bool valido_respuesta_3 (int respuesta_3);
bool valido_respuesta_4 (int respuesta_4);

/*RESPUESTA DE ENCUESTAS*/
void pido_respuesta_1(char* respuesta_1);
void pido_respuesta_2(char* respuesta_2);
void pido_respuesta_3(int* respuesta_3);
void pido_respuesta_4(int* respuesta_4);

/*TRANSFORMACIÓN DE PUNTAJES*/
int transformar_respuesta_1(char respuesta_1);
int transformar_respuesta_2(char respuesta_2);
int transformar_respuesta_3(int respuesta_3);
int transformar_respuesta_4(int respuesta_4);

/*CALCULO*/
int calculo_de_puntaje(char respuesta_1, char respuesta_2,int respuesta_3,int respuesta_4);

/*IMPRESION*/
void imprimo_personalidad(char respuesta_1, char respuesta_2,int respuesta_3,int respuesta_4);

/*SELECCION PERSONAJE*/
char designo_personaje(char respuesta_1, char respuesta_2,int respuesta_3,int respuesta_4);

/*FIRMA AGREGADA PARA TP2*/
void test_de_personalidad(char* personalidad_detectada);

#endif /*__TEST_DE_PERSONALIDAD__*/
