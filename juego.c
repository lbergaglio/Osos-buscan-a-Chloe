#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include "osos_contra_reloj.h"
#include "test_de_personalidad.h"
#include "utiles.h"

#define INGRESAR_JUGADA "Ingrese jugada: "

#define CUADRO_LARGO 8
#define CUADRO_ALTO  4  

#define ESTADO_JUGANDO 0

#define LINTERNA    'L'
#define VELA        'V'
#define BENGALA     'E'
#define MOV_ARRIBA        'W'
#define MOV_ABAJO         'S'
#define MOV_IZQUIERDA     'A'
#define MOV_DERECHA       'D'
#define TIEMPO_RESTANTE   'T'

const int TIEMPO_PARA_GANAR = 120;

/*
	PRE: -
	POST: obtengo jugada validada ingresada por el usuario
*/
void ingreso_jugada(char* jugada){
	
	printf("%s",INGRESAR_JUGADA);
	scanf(" %s",jugada);
	while(!es_jugada_valida(*jugada)){
		printf("%s",INGRESAR_JUGADA);
		scanf(" %s",jugada);
	}
}
/*
	PRE: recibo el estado del juego(si el oso encontro a chloe o no)
	POST:-muestro por pantalla el mapa con todos los objetos visibles.
		 -el usuario ingresa jugada 	
*/
void jugar_juego(juego_t juego,char jugada){

	while(estado_juego(juego)==ESTADO_JUGANDO){

		if(jugada==TIEMPO_RESTANTE)
			printf("El tiempo actual es de: %f\n",tiempo_actual());

		mostrar_juego(juego);
		ingreso_jugada(&jugada);
		realizar_jugada(&juego,jugada);
		system("clear");
	}
}
/*
	PRE:-
	POST: en caso de ganar o perder, se imprime un cuadro diciendo si encontraste a chloe antes de tiempo o no.
*/
void ver_mensaje_resultado(double tiempo_total){
 	for(int i=0;i<CUADRO_ALTO;i++){
		for(int j=0;j<CUADRO_LARGO;j++){
			if(tiempo_total<=TIEMPO_PARA_GANAR)
				printf("GANASTE ");
			else
				printf("PERDISTE ");
		}
		printf("\n\n");
	}
 }
	
int main(){

	srand((unsigned)time(NULL));

	printf("HOLA. Bienvenidos al Test de Personalidad de Osos Escandalosos.\n\n");

	double tiempo_total;
	char personalidad_detectada;
	char jugada = '\0';
	juego_t juego;

	test_de_personalidad(&personalidad_detectada);
	inicializar_juego(&juego,personalidad_detectada);
	system("clear");
	iniciar_cronometro();
	jugar_juego(juego,jugada);

	tiempo_total=detener_cronometro() + juego.personaje.tiempo_perdido;

	ver_mensaje_resultado(tiempo_total);	
	
	return 0;

}