#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "osos_contra_reloj.h"
#include "test_de_personalidad.h"
#include "utiles.h"

#define PARDO 'G'
#define POLAR 'I'
#define PANDA 'P'

#define MARCO        		"------------------------------------------------------------------------------------------"
#define TITULO_1     		"|                     ESTE ES EL JUEGO DE LOS OSOS ESCANDALOSOS                          |"
#define TITULO_2     		"|                        AYUDA A TU OSO A ENCONTRAR A CHLOE                              |"
#define CUADRO_ALTO_TITULO  "__________________________________________________________________________________________"
#define CUADRO_BAJO_TITULO  "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"

#define CUADRO_ALTO_MOV       "____________________________________________________"
#define CUADRO_BAJO_MOV		  "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"
#define LISTA_DE_MOVIMIENOS_1 "|W: Si el personaje debe moverse para la arriba.   |" 
#define LISTA_DE_MOVIMIENOS_2 "|A: Si el personaje debe moverse para la izquierda.|"
#define LISTA_DE_MOVIMIENOS_3 "|S: Si el personaje debe moverse para la abajo.    |"
#define LISTA_DE_MOVIMIENOS_4 "|D: Si el personaje debe moverse para la derecha.  |"
#define LISTA_DE_MOVIMIENOS_5 "|L: Si el personaje quiere encender una linterna.  |"
#define LISTA_DE_MOVIMIENOS_6 "|V: Si el personaje quiere encender una vela.      |"
#define LISTA_DE_MOVIMIENOS_7 "|E: Si el personaje quiere encender una bengala.   |"
#define LISTA_DE_MOVIMIENOS_8 "|T: Si el personaje quiere ver el tiempo restante. |"

#define MAX_FILAS 20
#define MAX_COLUMNAS 30


const char CHLOE = 'C';

const char ARBOL      = 'A';
const char PIEDRA     = 'R';
const char KOALAS     = 'K';
const char LINTERNA   = 'L';
const char VELA       = 'V';
const char BENGALA    = 'E';
const char PILA       = 'B';

const char MOV_ARRIBA       = 'W';
const char MOV_ABAJO        = 'S';
const char MOV_IZQUIERDA    = 'A';
const char MOV_DERECHA      = 'D';
const char TIEMPO_RESTANTE  = 'T';

const int ARBOLES_BOSQUE           = 350;
const int PIEDRAS_BOSQUE           = 80;
const int KOALAS_BOSQUE            = 1;
const int PILA_BOSQUE              = 30;
const int VELA_BOSQUE              = 30;
const int BENGALA_BOSQUE           = 10;

const int VIDA_LINTERNA_GENERAL = 10;
const int VIDA_LINTERNA_PARDO   = 15; 
const int VIDA_PILA_ENCONTRADA  = 5;
const int VIDA_VELA             = 5;
const int VIDA_BENGALA          = 3;
const int SIN_VIDA              = 0;
const int MAX_VIDA_PILA         = 15;

const int ESTADO_JUGANDO   =  0;
const int ESTADO_TERMINADO = -1;

const int ELEMENTO_FUERA_DE_USO = -1;

const int INICIAL_VELA_GENERAL     = 4;
const int INICIAL_VELA_POLAR       = 6;
const int INICIAL_BENGALA_PANDA    = 2;

const double TIEMPO_PERDIDO_ARBOL_PARDO   = 0.5;
const double TIEMPO_PERDIDO_ARBOL_GENERAL = 1;

const double TIEMPO_PERDIDO_PIEDRA  = 2;

const char VACIO = '\0';

bool es_jugada_valida(char jugada){
	return (jugada==MOV_ABAJO || jugada==MOV_ARRIBA || jugada==MOV_DERECHA || jugada==MOV_IZQUIERDA || jugada==LINTERNA || jugada==VELA || jugada==BENGALA|| jugada==TIEMPO_RESTANTE);
}
/*
	PRE:-
	POST: devuelve si el oso tiene la misma ubicacion en el mapa que chloe o no.
*/
bool oso_encontro_chloe(juego_t juego){
	return((juego.personaje.posicion.fil==juego.amiga_chloe.fil)&&(juego.personaje.posicion.col==juego.amiga_chloe.col));
}
/*
	PRE: recibo fila y columna del bosque.
	POST: devulevo si el luagr esta ocupado o no.
*/
bool el_espacio_esta_ocupado(char bosque[MAX_FILAS][MAX_COLUMNAS], int fila,int columna){
	return (bosque[fila][columna]=='-');
}
/*
	PRE: recibo fila y columna random del mapa.
	POST: calculo los obstaculos que estan dentro de la distancia manhattan.
*/
int distancia_manhattan_obstaculos(juego_t juego,int i, int fila_random,int columna_random){
	return(abs(fila_random-(juego.obstaculos[i].posicion.fil)) + abs(columna_random-(juego.obstaculos[i].posicion.col)));
}
/*
	PRE: recibo fila y columna random del mapa.
	POST: calculo las herramientas que estan dentro de la distancia manhattan.
*/
int distancia_manhattan_herramientas(juego_t juego,int i,int fila_random,int columna_random){
	return(abs(fila_random-(juego.herramientas[i].posicion.fil)) + abs(columna_random-(juego.herramientas[i].posicion.col)));
}
/*
	PRE: recibo fila y columna random del mapa.
	POST: calculo si chloe esta dentro de la distancia manhattan.
*/
int distancia_manhattan_chloe(juego_t juego,int fila_random,int columna_random){
	return(abs(fila_random-(juego.amiga_chloe.fil)) + abs(columna_random-(juego.amiga_chloe.col)));
}
/*
	PRE:-
	POST: vuelvo no visibles los obstaculos, herramientas y chloe.
*/
void oscurecer_todo(juego_t* juego){
	for(int i=0;i<(juego->cantidad_obstaculos);i++){
		juego->obstaculos[i].visible=false;
	}

	for(int i=0;i<(juego->cantidad_herramientas);i++){
		juego->herramientas[i].visible=false;
	}
 
	juego->chloe_visible=false;
}
/*
	PRE: recibo mapa no inicializado
	POST: lleno el mapa de elementos vacios
*/
void vaciar_bosque(char bosque[MAX_FILAS][MAX_COLUMNAS]){
	for(int i=0;i<MAX_FILAS;i++){
		for(int j=0;j<MAX_COLUMNAS;j++){
			bosque[i][j]='-';
		}
	}
}
/*
	PRE: recibo el mapa vacio
	POST: agrego en el mapa las herramientas y los obstaculos
*/
void agregar_obstaculos_herramientas(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS]){
	for(int i=0;i<(juego->cantidad_obstaculos);i++){
		bosque[juego->obstaculos[i].posicion.fil][juego->obstaculos[i].posicion.col]=juego->obstaculos[i].tipo;
	}

	for(int j=0;j<(juego->cantidad_herramientas);j++){
		bosque[juego->herramientas[j].posicion.fil][juego->herramientas[j].posicion.col]=juego->herramientas[j].tipo;
	
	}
}
/*
	PRE:-
	POST:hago visible los obstaculos iluninados por la linterna.
*/
void iluminar_obstaculos_con_linterna(juego_t* juego){
	for(int i=0;i<(juego->cantidad_obstaculos);i++){
		if((juego->personaje.ultimo_movimiento==MOV_IZQUIERDA)&&(juego->obstaculos[i].posicion.fil==juego->personaje.posicion.fil)&&(juego->obstaculos[i].posicion.col<juego->personaje.posicion.col))
			juego->obstaculos[i].visible=true;
		if((juego->personaje.ultimo_movimiento==MOV_DERECHA)&&(juego->obstaculos[i].posicion.fil==juego->personaje.posicion.fil)&&(juego->obstaculos[i].posicion.col>juego->personaje.posicion.col))
			juego->obstaculos[i].visible=true;
		if((juego->personaje.ultimo_movimiento==MOV_ARRIBA)&&(juego->obstaculos[i].posicion.fil<juego->personaje.posicion.fil)&&(juego->obstaculos[i].posicion.col==juego->personaje.posicion.col))
			juego->obstaculos[i].visible=true;
		if((juego->personaje.ultimo_movimiento==MOV_ABAJO)&&(juego->obstaculos[i].posicion.fil>juego->personaje.posicion.fil)&&(juego->obstaculos[i].posicion.col==juego->personaje.posicion.col))
			juego->obstaculos[i].visible=true;
	}
}
/*
	PRE:-
	POST:hago visibles las herramientas iluminadas por la linterna.
*/
void iluminar_herramientas_con_linterna(juego_t* juego){
	for(int i=0;i<(juego->cantidad_herramientas);i++){
		if((juego->personaje.ultimo_movimiento==MOV_IZQUIERDA)&&(juego->herramientas[i].posicion.fil==juego->personaje.posicion.fil)&&(juego->herramientas[i].posicion.col<juego->personaje.posicion.col))
			juego->herramientas[i].visible=true;
		if((juego->personaje.ultimo_movimiento==MOV_DERECHA)&&(juego->herramientas[i].posicion.fil==juego->personaje.posicion.fil)&&(juego->herramientas[i].posicion.col>juego->personaje.posicion.col))
			juego->herramientas[i].visible=true;
		if((juego->personaje.ultimo_movimiento==MOV_ARRIBA)&&(juego->herramientas[i].posicion.fil<juego->personaje.posicion.fil)&&(juego->herramientas[i].posicion.col==juego->personaje.posicion.col))
			juego->herramientas[i].visible=true;
		if((juego->personaje.ultimo_movimiento==MOV_ABAJO)&&(juego->herramientas[i].posicion.fil>juego->personaje.posicion.fil)&&(juego->herramientas[i].posicion.col==juego->personaje.posicion.col))
			juego->herramientas[i].visible=true;
	}
}
/*
	PRE:
	POST:hago visible a chloe en caso de ser iluminada por la linterna.
*/
void iluminar_chloe_con_linterna(juego_t* juego){
	if((juego->personaje.ultimo_movimiento==MOV_DERECHA)&&(juego->personaje.posicion.fil==juego->amiga_chloe.fil)&&(juego->personaje.posicion.col<juego->amiga_chloe.col))
			juego->chloe_visible=true;
	if((juego->personaje.ultimo_movimiento==MOV_ARRIBA)&&(juego->personaje.posicion.fil>juego->amiga_chloe.fil)&&(juego->personaje.posicion.col==juego->amiga_chloe.col))
			juego->chloe_visible=true;
	if((juego->personaje.ultimo_movimiento==MOV_ABAJO)&&(juego->personaje.posicion.fil<juego->amiga_chloe.fil)&&(juego->personaje.posicion.col==juego->amiga_chloe.col))
			juego->chloe_visible=true;
}
/*
	PRE:-
	POST:hago visible los obstaculos, herramientas y chloe al prender la linterna.
*/
void iluminar_bosque_con_linterna(juego_t*juego){
	if((juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo==LINTERNA)&&(juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes>=0)){	

		iluminar_obstaculos_con_linterna(juego);
		iluminar_herramientas_con_linterna(juego);
		iluminar_chloe_con_linterna(juego);

		if(juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes==SIN_VIDA)
			juego->personaje.elemento_en_uso=ELEMENTO_FUERA_DE_USO;
		else
			(juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes)--;
	}
}
/*
	PRE:-
	POST:hago visible los obstaculos iluminados por la vela
*/
void iluminar_obstaculos_con_vela(juego_t* juego){
	for(int i=0;i<(juego->cantidad_obstaculos);i++){
		if(((juego->obstaculos[i].posicion.fil)+1)==(juego->personaje.posicion.fil) && ((juego->obstaculos[i].posicion.col)==(juego->personaje.posicion.col)))
			juego->obstaculos[i].visible=true;
		if(((juego->obstaculos[i].posicion.fil)+1)==(juego->personaje.posicion.fil) && (((juego->obstaculos[i].posicion.col)-1)==(juego->personaje.posicion.col)))
			juego->obstaculos[i].visible=true;
		if(((juego->obstaculos[i].posicion.fil)+1)==(juego->personaje.posicion.fil) && (((juego->obstaculos[i].posicion.col)+1)==(juego->personaje.posicion.col)))
			juego->obstaculos[i].visible=true;
		if(((juego->obstaculos[i].posicion.fil)-1)==(juego->personaje.posicion.fil) && ((juego->obstaculos[i].posicion.col)==(juego->personaje.posicion.col)))
			juego->obstaculos[i].visible=true;
		if(((juego->obstaculos[i].posicion.fil)-1)==(juego->personaje.posicion.fil) && (((juego->obstaculos[i].posicion.col)-1)==(juego->personaje.posicion.col)))
			juego->obstaculos[i].visible=true;
		if(((juego->obstaculos[i].posicion.fil)-1)==(juego->personaje.posicion.fil) && (((juego->obstaculos[i].posicion.col)+1)==(juego->personaje.posicion.col)))
			juego->obstaculos[i].visible=true;
		if((juego->obstaculos[i].posicion.fil)==(juego->personaje.posicion.fil) && (((juego->obstaculos[i].posicion.col)+1)==(juego->personaje.posicion.col)))
			juego->obstaculos[i].visible=true;
		if(((juego->obstaculos[i].posicion.fil))==(juego->personaje.posicion.fil) && (((juego->obstaculos[i].posicion.col)-1)==(juego->personaje.posicion.col)))
			juego->obstaculos[i].visible=true;
	}
}
/*
	PRE:-
	POST:hago visible las herramientas iluminadas por la vela.
*/
void iluminar_herramientas_con_vela(juego_t* juego){
	for(int i=0;i<(juego->cantidad_herramientas);i++){
		if(((juego->herramientas[i].posicion.fil)+1)==(juego->personaje.posicion.fil) && ((juego->herramientas[i].posicion.col)==(juego->personaje.posicion.col)))
			juego->herramientas[i].visible=true;
		if(((juego->herramientas[i].posicion.fil)+1)==(juego->personaje.posicion.fil) && (((juego->herramientas[i].posicion.col)-1)==(juego->personaje.posicion.col)))
			juego->herramientas[i].visible=true;
		if(((juego->herramientas[i].posicion.fil)+1)==(juego->personaje.posicion.fil) && (((juego->herramientas[i].posicion.col)+1)==(juego->personaje.posicion.col)))
			juego->herramientas[i].visible=true;
		if(((juego->herramientas[i].posicion.fil)-1)==(juego->personaje.posicion.fil) && ((juego->herramientas[i].posicion.col)==(juego->personaje.posicion.col)))
			juego->herramientas[i].visible=true;
		if(((juego->herramientas[i].posicion.fil)-1)==(juego->personaje.posicion.fil) && (((juego->herramientas[i].posicion.col)-1)==(juego->personaje.posicion.col)))
			juego->herramientas[i].visible=true;
		if(((juego->herramientas[i].posicion.fil)-1)==(juego->personaje.posicion.fil) && (((juego->herramientas[i].posicion.col)+1)==(juego->personaje.posicion.col)))
			juego->herramientas[i].visible=true;
		if(((juego->herramientas[i].posicion.fil))==(juego->personaje.posicion.fil) && (((juego->herramientas[i].posicion.col)+1)==(juego->personaje.posicion.col)))
			juego->herramientas[i].visible=true;
		if(((juego->herramientas[i].posicion.fil))==(juego->personaje.posicion.fil) && (((juego->herramientas[i].posicion.col)-1)==(juego->personaje.posicion.col)))
			juego->herramientas[i].visible=true;

	}
}
/*
	PRE:-
	POST:hago visible a chloe en caso de ser iluminada por un vela.
*/
void iluminar_chloe_con_vela(juego_t* juego){
	for(int i=0;i<(juego->cantidad_herramientas);i++){
		if(((juego->amiga_chloe.fil)+1)==(juego->personaje.posicion.fil) && ((juego->amiga_chloe.col)==(juego->personaje.posicion.col)))
			juego->chloe_visible=true;
		if(((juego->amiga_chloe.fil)+1)==(juego->personaje.posicion.fil) && ((juego->amiga_chloe.col)==(juego->personaje.posicion.col)))
			juego->chloe_visible=true;
		if(((juego->amiga_chloe.fil)+1)==(juego->personaje.posicion.fil) && (((juego->amiga_chloe.col)+1)==(juego->personaje.posicion.col)))
			juego->chloe_visible=true;
		if(((juego->amiga_chloe.fil)-1)==(juego->personaje.posicion.fil) && ((juego->amiga_chloe.col)==(juego->personaje.posicion.col)))
			juego->chloe_visible=true;
		if(((juego->amiga_chloe.fil)-1)==(juego->personaje.posicion.fil) && (((juego->amiga_chloe.col)-1)==(juego->personaje.posicion.col)))
			juego->chloe_visible=true;
		if(((juego->amiga_chloe.fil)-1)==(juego->personaje.posicion.fil) && (((juego->amiga_chloe.col)+1)==(juego->personaje.posicion.col)))
			juego->chloe_visible=true;
		if((juego->amiga_chloe.fil==(juego->personaje.posicion.fil) && ((juego->amiga_chloe.col)+1)==(juego->personaje.posicion.col)))
			juego->chloe_visible=true;
		if((juego->amiga_chloe.fil)==(juego->personaje.posicion.fil) && (((juego->amiga_chloe.col)-1)==(juego->personaje.posicion.col)))
				juego->chloe_visible=true;
	}
}
/*
	PRE:-
	POST:hago visible los obstaculos, herramientas y chloe al prender la vela
*/
void iluminar_bosque_con_vela(juego_t* juego){
	if((juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo==VELA)&&(juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes>=0)){

		iluminar_obstaculos_con_vela(juego);
		iluminar_herramientas_con_vela(juego);
		iluminar_chloe_con_vela(juego);

		if(juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes==SIN_VIDA)
			juego->personaje.elemento_en_uso=ELEMENTO_FUERA_DE_USO;
		else 
			(juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes)--;
	}	
}
/*
	PRE: recibo fila y column aleatoria
	POST: hago visibles los elementos que se encuentran dentro de la distancia manhattan
*/
void iluminar_herramientas_obstaculos_chloe_con_bengala(juego_t* juego,int fila_random,int columna_random){
	for(int i=0;i<(juego->cantidad_obstaculos);i++){
		if(distancia_manhattan_obstaculos(*juego,i,fila_random,columna_random)<=2)
			juego->obstaculos[i].visible=true;
	}
	for(int i=0;i<(juego->cantidad_herramientas);i++){
		if(distancia_manhattan_herramientas(*juego,i,fila_random,columna_random)<=2)
			juego->herramientas[i].visible=true;
	}

	if(distancia_manhattan_chloe(*juego,fila_random,columna_random)<=2)
		juego->chloe_visible=true;
}
/*
	PRE:-
	POST:hago visible los obstaculos, herramientas y chloe al prender la bengala.
*/
void iluminar_bosque_con_bengala(juego_t* juego){

	int fila_random=rand()%MAX_FILAS;
	int columna_random=rand()%MAX_COLUMNAS;

	if((juego->personaje.elemento_en_uso!=ELEMENTO_FUERA_DE_USO)&&(juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo==BENGALA)&&(juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes>=0)){
		
		iluminar_herramientas_obstaculos_chloe_con_bengala(juego,fila_random,columna_random);

		if(juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes==SIN_VIDA)
			juego->personaje.elemento_en_uso=ELEMENTO_FUERA_DE_USO;
		else
			(juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes)--;
	}
}
/*
	PRE:-
	POST: hago visible los obstaculos, herramientas y chloe.
*/
void iluminar_bosque(juego_t* juego){
	
	iluminar_bosque_con_linterna(juego);
	iluminar_bosque_con_vela(juego);
	iluminar_bosque_con_bengala(juego);
}
/*
	PRE: recibo que oso es y mapa completamanete vacio.
	POST: asigno lugar aleatorio al oso en la primer columna.
*/
void asignar_lugar_oso(juego_t* juego,char tipo_personaje,char bosque[MAX_FILAS][MAX_COLUMNAS]){
	
	juego->personaje.tipo = tipo_personaje;
	juego->personaje.posicion.fil = rand()%MAX_FILAS;
	juego->personaje.posicion.col = 0;

	bosque[juego->personaje.posicion.fil][juego->personaje.posicion.col]=juego->personaje.tipo;	
}
/*
	PRE: recibo mapa solo con el oso con lugar asignado.
	POST: asigno lugar aleatorio a chloe en el mapa y no la hago visible.
*/
void asignar_lugar_chloe(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS]){

	juego->amiga_chloe.fil = rand()%MAX_FILAS;
	juego->amiga_chloe.col = rand()%MAX_COLUMNAS;
	juego->chloe_visible = false;
	
	bosque[juego->amiga_chloe.fil][juego->amiga_chloe.col]=CHLOE;
}
/*
	PRE: recibo mapa sin obstaculos y herramientas.
	POST: asigno 350 arboles en distintos lugares del mapa que se encuentarn vacios.
*/
void asignar_lugar_arbol(juego_t* juego,char bosque [MAX_FILAS][MAX_COLUMNAS],int i){
	if(i<ARBOLES_BOSQUE){
		juego->obstaculos[i].tipo=ARBOL;
		juego->obstaculos[i].posicion.fil=rand()%MAX_FILAS;
		juego->obstaculos[i].posicion.col=rand()%MAX_COLUMNAS;

		while(!el_espacio_esta_ocupado(bosque,(juego->obstaculos[i].posicion.fil),(juego->obstaculos[i].posicion.col))){
			juego->obstaculos[i].posicion.fil=rand()%MAX_FILAS;
			juego->obstaculos[i].posicion.col=rand()%MAX_COLUMNAS;
		}
	}
}
/*
	PRE: recibo mapa sin piedras, koalas ni herramientas.
	POST: asigno 80 piedras en distintos lugares del mapa que se encuentran vacios.
*/
void asignar_lugar_piedra(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS],int i){
	if(i>=ARBOLES_BOSQUE && i<(ARBOLES_BOSQUE+PIEDRAS_BOSQUE)){
			juego->obstaculos[i].tipo=PIEDRA;
			juego->obstaculos[i].posicion.fil=rand()%MAX_FILAS;
			juego->obstaculos[i].posicion.col=rand()%MAX_COLUMNAS;

			while(!el_espacio_esta_ocupado(bosque,(juego->obstaculos[i].posicion.fil),(juego->obstaculos[i].posicion.col))){
				juego->obstaculos[i].posicion.fil=rand()%MAX_FILAS;
				juego->obstaculos[i].posicion.col=rand()%MAX_COLUMNAS;
			}
		}
}
/*
	PRE: recibo mapa sin koalas ni herramientas.
	POST: asigno 1 koala aleatoriamente en un lugar del mapacque se encuentre vacio. 
*/
void asignar_lugar_koala(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS],int i){
	if(i>=(ARBOLES_BOSQUE+PIEDRAS_BOSQUE)){
		juego->obstaculos[i].tipo=KOALAS;
		juego->obstaculos[i].posicion.fil=rand()%MAX_FILAS;
		juego->obstaculos[i].posicion.col=rand()%MAX_COLUMNAS;

		while(!el_espacio_esta_ocupado(bosque,(juego->obstaculos[i].posicion.fil),(juego->obstaculos[i].posicion.col))){
			juego->obstaculos[i].posicion.fil=rand()%MAX_FILAS;
			juego->obstaculos[i].posicion.col=rand()%MAX_COLUMNAS;
		}			
	}
}
/*
	PRE: recibo mapa con lugares asignados de chloe y el oso.
	POST: asigno todos los obstaculos en distintos lugares del mapa y no los hago visibles.
*/
void asignar_lugar_obstaculos(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS]){

	juego->cantidad_obstaculos=ARBOLES_BOSQUE+PIEDRAS_BOSQUE+KOALAS_BOSQUE;

	for(int i=0;i<(juego->cantidad_obstaculos);i++){
		
		asignar_lugar_arbol(juego,bosque,i);
		asignar_lugar_piedra(juego,bosque,i);
		asignar_lugar_koala(juego,bosque,i);
		
		bosque[juego->obstaculos[i].posicion.fil][juego->obstaculos[i].posicion.col]=juego->obstaculos[i].tipo;
		juego->obstaculos[i].visible = false;
	}
}
/*
	PRE:recibo bosque cargado con obstaculos, herramientas y chloe.
	POST: asigno lugar a koala cada vez que prendo una linterna.
*/
void agregar_nuevo_koala(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS]){
	juego->obstaculos[juego->cantidad_obstaculos].tipo=KOALAS;
	juego->obstaculos[juego->cantidad_obstaculos].posicion.fil=rand()%MAX_FILAS;
	juego->obstaculos[juego->cantidad_obstaculos].posicion.col=rand()%MAX_COLUMNAS;

	while(!el_espacio_esta_ocupado(bosque,(juego->obstaculos[juego->cantidad_obstaculos].posicion.fil),(juego->obstaculos[juego->cantidad_obstaculos].posicion.col))){
		juego->obstaculos[juego->cantidad_obstaculos].posicion.fil=rand()%MAX_FILAS;
		juego->obstaculos[juego->cantidad_obstaculos].posicion.col=rand()%MAX_COLUMNAS;
	}
	juego->cantidad_obstaculos++;
}
/*
	PRE: recibo mapa sin herramientas asignadas.
	POST: asingo 30 pilas en distintos lugares del mapa que se encuentren vacios.
*/
void asignar_lugar_pila(juego_t* juego,char bosque[MAX_FILAS][MAX_COLUMNAS],int j){
	if(j<PILA_BOSQUE){
		juego->herramientas[j].tipo=PILA;
		juego->herramientas[j].posicion.fil=rand()%MAX_FILAS;
		juego->herramientas[j].posicion.col=rand()%MAX_COLUMNAS;

		while(!el_espacio_esta_ocupado(bosque,(juego->herramientas[j].posicion.fil),(juego->herramientas[j].posicion.col))){
			juego->herramientas[j].posicion.fil=rand()%MAX_FILAS;
			juego->herramientas[j].posicion.col=rand()%MAX_COLUMNAS;
		}
	}
}
/*
	PRE: recibo mapa sin velas y bengalas.
	POST: asigno 30 velas en distintos lugares del mapa que se encuentren vacios.
*/
void asignar_lugar_vela(juego_t* juego,char bosque[MAX_FILAS][MAX_COLUMNAS],int j){
	if(j>=PILA_BOSQUE && j<(PILA_BOSQUE+VELA_BOSQUE)){
		juego->herramientas[j].tipo=VELA;
		juego->herramientas[j].posicion.fil=rand()%MAX_FILAS;
		juego->herramientas[j].posicion.col=rand()%MAX_COLUMNAS;

		while(!el_espacio_esta_ocupado(bosque,(juego->herramientas[j].posicion.fil),(juego->herramientas[j].posicion.col))){
			juego->herramientas[j].posicion.fil=rand()%MAX_FILAS;
			juego->herramientas[j].posicion.col=rand()%MAX_COLUMNAS;
		}
	}
}
/*
	PRE: recibo el mapa sin bengalas.
	POST: asigno 10 bengalas en distintos lugares del mapa que se encuentren vacios. 
*/
void asignar_lugar_bengala(juego_t* juego,char bosque[MAX_FILAS][MAX_COLUMNAS],int j){
	if(j>=(PILA_BOSQUE+VELA_BOSQUE)){
		juego->herramientas[j].tipo=BENGALA;
		juego->herramientas[j].posicion.fil=rand()%MAX_FILAS;
		juego->herramientas[j].posicion.col=rand()%MAX_COLUMNAS;

		while(!el_espacio_esta_ocupado(bosque,(juego->herramientas[j].posicion.fil),(juego->herramientas[j].posicion.col))){
			juego->herramientas[j].posicion.fil=rand()%MAX_FILAS;
			juego->herramientas[j].posicion.col=rand()%MAX_COLUMNAS;
		}
	}
}
/*
	PRE: recibo mapa con lugares asignados de obstaculos, chloe y el oso.
	POST: asgno todas las herramientas en distintos lugares del mapa y no los hao visibles.
*/
void asignar_lugar_herramientas(juego_t* juego,char bosque[MAX_FILAS][MAX_COLUMNAS]){

	juego->cantidad_herramientas=PILA_BOSQUE+VELA_BOSQUE+BENGALA_BOSQUE;

	for(int j=0;j<(juego->cantidad_herramientas);j++){

		asignar_lugar_pila(juego,bosque,j);
		asignar_lugar_vela(juego,bosque,j);
		asignar_lugar_bengala(juego,bosque,j);

		bosque[juego->herramientas[j].posicion.fil][juego->herramientas[j].posicion.col]=juego->herramientas[j].tipo;
		juego->herramientas[j].visible = false;
	}
}
/*
	PRE: recibo posicion incial de la mocila.
	POST: asigno linterna en la mochila con vida util dependiendo de la personalidad del oso, aumento tope de mochila.
*/
void asignar_linterna_mochila(juego_t* juego,int posicion_mochila_vacia){
	if(juego->personaje.mochila[posicion_mochila_vacia].tipo==VACIO){
		juego->personaje.mochila[posicion_mochila_vacia].tipo=LINTERNA;
		(juego->personaje.cantidad_elementos)++;
	}
	if(juego->personaje.tipo==PARDO)
		juego->personaje.mochila[posicion_mochila_vacia].movimientos_restantes=VIDA_LINTERNA_PARDO;
	else
		juego->personaje.mochila[posicion_mochila_vacia].movimientos_restantes=VIDA_LINTERNA_GENERAL;
}
/*
	PRE: recibo posicion inicial de la mochila.
	POST: asigno cierta cantidad de velas en la mochila dependiendo la personalidad del oso, aumento tope de mochila.
*/
void asignar_vela_mochila(juego_t* juego,int posicion_mochila_vacia,int* cantidad_inicial_velas){
	if(juego->personaje.tipo==POLAR)
		*cantidad_inicial_velas=INICIAL_VELA_POLAR+1;
	else
		*cantidad_inicial_velas=INICIAL_VELA_GENERAL+1;

	for(int i=posicion_mochila_vacia+1;i<*cantidad_inicial_velas;i++){
		juego->personaje.mochila[i].tipo=VELA;
		juego->personaje.mochila[i].movimientos_restantes=VIDA_VELA;
		(juego->personaje.cantidad_elementos)++;
	}
}	
/*
	PRE: recibo cantidad de velas segun personalidad del oso.
	POST: asigno bengalas en la mochila dependiendo la personalidad del oso, aumento tope de mochila.
*/
void asignar_bengala_mochila(juego_t* juego,int cantidad_inicial_velas,int* cantidad_inicial_bengalas){
	if(juego->personaje.tipo==PANDA)
		*cantidad_inicial_bengalas=INICIAL_BENGALA_PANDA+cantidad_inicial_velas;
	else
		*cantidad_inicial_bengalas=cantidad_inicial_velas;

	for(int i=cantidad_inicial_velas;i<*cantidad_inicial_bengalas;i++){
		juego->personaje.mochila[i].tipo=BENGALA;
		juego->personaje.mochila[i].movimientos_restantes=VIDA_BENGALA;
		(juego->personaje.cantidad_elementos)++;
	}
}
/*
	PRE:-
	POST:asigno todas la herramientas disponibles en la mochila dependiendo la personaldiad del oso al iniciar el juego.
*/
void asignar_herramientas_mochila(juego_t* juego){

	int posicion_mochila_vacia=0;
	int cantidad_inicial_velas=0;
	int cantidad_inicial_bengalas=0;
	
	juego->personaje.cantidad_elementos=0;

	asignar_linterna_mochila(juego,posicion_mochila_vacia);
	asignar_vela_mochila(juego,posicion_mochila_vacia,&cantidad_inicial_velas);
	asignar_bengala_mochila(juego,cantidad_inicial_velas,&cantidad_inicial_bengalas);	
}

void inicializar_juego(juego_t* juego, char tipo_personaje){

	char bosque[MAX_FILAS][MAX_COLUMNAS];
	
	juego->personaje.tiempo_perdido=0;
	juego->personaje.elemento_en_uso=ELEMENTO_FUERA_DE_USO;

	vaciar_bosque(bosque);
	asignar_lugar_oso(juego,tipo_personaje,bosque);
	asignar_lugar_chloe(juego,bosque);
	asignar_lugar_obstaculos(juego,bosque);	
	asignar_lugar_herramientas(juego,bosque);
	asignar_herramientas_mochila(juego);	
	mostrar_juego(*juego);
}
int estado_juego(juego_t juego){
	if(!oso_encontro_chloe(juego))
		return ESTADO_JUGANDO;
	else
		return ESTADO_TERMINADO;
}
/*
	PRE:-
	POST: elimino herramiente que se encuentre en la misma osicion que el oso.
*/
void eliminar_herramienta_encontrada(juego_t* juego){	
	for(int j=0;j<(juego->cantidad_herramientas);j++){
		if((juego->herramientas[j].posicion.fil)==(juego->personaje.posicion.fil) && (juego->herramientas[j].posicion.col)==(juego->personaje.posicion.col)){
			juego->herramientas[j]=juego->herramientas[juego->cantidad_herramientas - 1];
			(juego->cantidad_herramientas)--;
		}

	}
}
/*
	PRE: recibo mapa con obstaculos, herramientas, chloe y el oso. 
	POST: agrego movimientos en la linterna si coincide la ubicacion del oso con una pila en el mapa.
*/
void agregar_pilas_encontradas(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS], int posicion_herramienta_encontrada){
	if(bosque[juego->personaje.posicion.fil][juego->personaje.posicion.col]==PILA){
		for(int i=0;i<(juego->personaje.cantidad_elementos);i++){
			if(juego->personaje.mochila[i].tipo==LINTERNA)	
				posicion_herramienta_encontrada=i;
		}
		for(int j=0;j<VIDA_PILA_ENCONTRADA;j++){
			if((juego->personaje.mochila[posicion_herramienta_encontrada].movimientos_restantes)<MAX_VIDA_PILA)
				juego->personaje.mochila[posicion_herramienta_encontrada].movimientos_restantes++;
		}	
	}
}
/*
	PRE: recibo mapa con obstaculos, herramientas, chloe y el oso.
	POST: agrego vela en la mochile si coincide la ubicacion del oso con una vela en el mapa.
*/
void agregar_velas_encontradas(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS], int posicion_herramienta_encontrada){
	if(bosque[juego->personaje.posicion.fil][juego->personaje.posicion.col]==VELA){
		juego->personaje.mochila[juego->personaje.cantidad_elementos].tipo=VELA;
		juego->personaje.mochila[juego->personaje.cantidad_elementos].movimientos_restantes=VIDA_VELA;
	}
}
/*
	PRE: recibo mapa con obstaculos, herramientas, chloe y el oso.
	POST: agrego bengala en la mochile si coincide la ubicacion del oso con una bengala en el mapa.
*/
void agregar_bengalas_encontradas(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS], int posicion_herramienta_encontrada){
	if(bosque[juego->personaje.posicion.fil][juego->personaje.posicion.col]==BENGALA){
		juego->personaje.mochila[juego->personaje.cantidad_elementos].tipo=BENGALA;
		juego->personaje.mochila[juego->personaje.cantidad_elementos].movimientos_restantes=VIDA_BENGALA;
	}
}
/*
	PRE: recibo mapa con obstaculos, herramientas, chloe y el oso.
	POST: agrego a la mochila las herramientas encontradas en el mapa.
*/
void agregar_herramientas_encontradas(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS], int posicion_herramienta_encontrada){
	
	agregar_pilas_encontradas(juego,bosque,posicion_herramienta_encontrada);
	agregar_velas_encontradas(juego,bosque,posicion_herramienta_encontrada);
	agregar_bengalas_encontradas(juego,bosque,posicion_herramienta_encontrada);
	
	if(bosque[juego->personaje.posicion.fil][juego->personaje.posicion.col]==VELA || bosque[juego->personaje.posicion.fil][juego->personaje.posicion.col]==BENGALA)
		(juego->personaje.cantidad_elementos)++;
}
/*
	PRE: recibo mapa con obstaculos, herramientas, chloe y el oso.
	POST: agrego segundos al tiempo perdido dependiendo de la personalidad del oso si tiene la misma ubicaion del arbol.
*/
void restar_tiempo_arbol(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS]){
	if(bosque[juego->personaje.posicion.fil][juego->personaje.posicion.col]==ARBOL){
		if(juego->personaje.tipo==PARDO)
			juego->personaje.tiempo_perdido+=TIEMPO_PERDIDO_ARBOL_PARDO;
		else
			juego->personaje.tiempo_perdido+=TIEMPO_PERDIDO_ARBOL_GENERAL;

		if(juego->personaje.tipo==PANDA && juego->personaje.tiempo_perdido>=30)
			juego->chloe_visible=true;
	}
}
/*
	PRE: recibo mapa con obstaculos, herramientas, chloe y el oso.
	POST: agrego segundos al tiempo perdido dependiendo de la personalidad del oso si tiene la misma ubicaion del piedra.
*/
void restar_tiempo_piedra(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS]){
	if(bosque[juego->personaje.posicion.fil][juego->personaje.posicion.col]==PIEDRA && juego->personaje.tipo!=POLAR)
		juego->personaje.tiempo_perdido+=TIEMPO_PERDIDO_PIEDRA;
}
/*
	PRE: recibo mapa con obstaculos, herramientas, chloe y el oso.
	POST: llevo al oso a la primer columna y fila aleatoria si tiene la misma ubicacion del koala. 
*/
void volver_al_inicio_koala(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS]){
	if(bosque[juego->personaje.posicion.fil][juego->personaje.posicion.col]==KOALAS){
		juego->personaje.posicion.fil = rand()%MAX_FILAS;
		juego->personaje.posicion.col = 0;
	}
}
/*
	PRE: recibo mapa con obstaculos, herramientas, chloe y el oso.
	POST: 
*/
void restar_tiempo_obstaculos(juego_t* juego, char bosque[MAX_FILAS][MAX_COLUMNAS]){
	restar_tiempo_arbol(juego,bosque);
	restar_tiempo_piedra(juego,bosque);
	volver_al_inicio_koala(juego,bosque);
}
/*
	PRE:-
	POST:- agrego herrmamientas en a mochila si las encontre y las elimino del mapa.
		 - agrego tiempo perdido o vuelvo al inicio si me choco con un obstaculo.
*/
void verificar_elementos_en_posicion_actual(juego_t* juego){

	int posicion_herramienta_encontrada=0;

	char bosque[MAX_FILAS][MAX_COLUMNAS];

	vaciar_bosque(bosque);
	agregar_obstaculos_herramientas(juego,bosque);
	restar_tiempo_obstaculos(juego,bosque);
	agregar_herramientas_encontradas(juego,bosque,posicion_herramienta_encontrada);
	eliminar_herramienta_encontrada(juego);	
}
/*
	PRE: recibo jugada del usario.
	POST: modifico ubicacion del oso en fila o columna dependiendo de la jugada.
*/
void mover_diferentes_direcciones(juego_t* juego,char jugada){
	if(jugada==MOV_ABAJO||jugada==MOV_IZQUIERDA||jugada==MOV_ARRIBA||jugada==MOV_DERECHA)
		juego->personaje.ultimo_movimiento=jugada;

	if(jugada==MOV_ARRIBA && juego->personaje.posicion.fil!=0)
		juego->personaje.posicion.fil--;
	if(jugada==MOV_ABAJO && juego->personaje.posicion.fil!=MAX_FILAS-1)
		juego->personaje.posicion.fil++;
	if(jugada==MOV_IZQUIERDA && juego->personaje.posicion.col!=0)
		juego->personaje.posicion.col--;
	if(jugada==MOV_DERECHA && juego->personaje.posicion.col!=MAX_COLUMNAS-1)
		juego->personaje.posicion.col++;
}
/*
	PRE: recibo jugada del usario.
	POST:- enciendo linterna o la apago(dependiendo de si estaba prendida o no).
		 - agrego un koala al mapa si se prende linterna.
*/
void encender_herramientas_linterna(juego_t* juego,char bosque[MAX_FILAS][MAX_COLUMNAS],char jugada){
	int contador = 0;
	bool herramienta_encontrada=false;

	if(jugada==LINTERNA && (juego->personaje.elemento_en_uso==ELEMENTO_FUERA_DE_USO || juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo!=BENGALA)){

		if(juego->personaje.elemento_en_uso==ELEMENTO_FUERA_DE_USO || juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo!=LINTERNA){

			while(contador<juego->personaje.cantidad_elementos && !herramienta_encontrada){
				if(juego->personaje.mochila[contador].tipo==LINTERNA){
					juego->personaje.elemento_en_uso=contador;
					herramienta_encontrada=true;
				}
				contador++;	
			}
			agregar_nuevo_koala(juego,bosque);
		}
		else{
			juego->personaje.elemento_en_uso=ELEMENTO_FUERA_DE_USO;	
		}
	}
}
/*
	PRE: recibo jugada del usario.
	POST: enciendo vela o la apago(dependiendo de si estaba prendida o no).
*/
void encender_herramientas_vela(juego_t* juego,char jugada){
	int contador = 0;
	bool herramienta_encontrada=false;

	if(jugada==VELA && (juego->personaje.elemento_en_uso==ELEMENTO_FUERA_DE_USO||juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo!=BENGALA)){
		if(juego->personaje.elemento_en_uso==ELEMENTO_FUERA_DE_USO || juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo!=VELA){
			while(contador<juego->personaje.cantidad_elementos && !herramienta_encontrada){
				if(juego->personaje.mochila[contador].tipo==VELA){
					juego->personaje.elemento_en_uso=contador;
					herramienta_encontrada=true;
				}
				contador++;	
			}
		}
		else {
			juego->personaje.elemento_en_uso=ELEMENTO_FUERA_DE_USO;
		} 
	}
}
/*
	PRE: recibo jugada del usario.
	POST: enciendo bengala.
*/
void encender_herramientas_bengala(juego_t* juego,char jugada){
	int contador = 0;
	bool herramienta_encontrada=false;

	if(jugada==BENGALA && (juego->personaje.elemento_en_uso==ELEMENTO_FUERA_DE_USO||juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo!=BENGALA)){
		if(juego->personaje.elemento_en_uso==ELEMENTO_FUERA_DE_USO || juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo!=BENGALA){
			while(contador<juego->personaje.cantidad_elementos && !herramienta_encontrada){
				if(juego->personaje.mochila[contador].tipo==BENGALA){
					juego->personaje.elemento_en_uso=contador;
					herramienta_encontrada=true;
				}
				contador++;	
			}
		}
		else{
			juego->personaje.elemento_en_uso=ELEMENTO_FUERA_DE_USO;
		}
	}
}
/*
	PRE: recibo jugada del usario.
	POST: enciendo una herramienta o la apago (dependiendo si estaba prendida o no).
*/
void encender_herramientas(juego_t* juego,char bosque[MAX_FILAS][MAX_COLUMNAS],char jugada){

	encender_herramientas_linterna(juego,bosque,jugada);
	encender_herramientas_vela(juego,jugada);
	encender_herramientas_bengala(juego,jugada);	
}
void realizar_jugada(juego_t* juego,char jugada){	
	char bosque[MAX_FILAS][MAX_COLUMNAS];
	vaciar_bosque(bosque);
	agregar_obstaculos_herramientas(juego,bosque);
	mover_diferentes_direcciones(juego,jugada);
	encender_herramientas(juego,bosque,jugada);
	oscurecer_todo(juego);
	verificar_elementos_en_posicion_actual(juego);
	iluminar_bosque(juego);
}
/*
	PRE: recibo mapa solo con el oso visible
	POST: agrego al mapa los obstaculos, herramientas y chloe si son visibles.
*/
void agregar_obstaculos_herramientas_chloe_visibles(juego_t* juego,char bosque[MAX_FILAS][MAX_COLUMNAS]){
	if(juego->chloe_visible==true)
		bosque[juego->amiga_chloe.fil][juego->amiga_chloe.col]=CHLOE;

	for(int i=0;i<(juego->cantidad_obstaculos);i++){
		if(juego->obstaculos[i].visible==true){	
			bosque[juego->obstaculos[i].posicion.fil][juego->obstaculos[i].posicion.col]=juego->obstaculos[i].tipo;
		}
	}

	for(int j=0;j<(juego->cantidad_herramientas);j++){
		if(juego->herramientas[j].visible==true && juego->herramientas[j].tipo!=VACIO){
			bosque[juego->herramientas[j].posicion.fil][juego->herramientas[j].posicion.col]=juego->herramientas[j].tipo;
		}
	}
}
/*
	PRE:-
	POST: agrego al mapa vacio a el oso y luego las herramientas, obstaculos y chloeS
*/
void cargar_bosque(juego_t* juego,char bosque[MAX_FILAS][MAX_COLUMNAS]){

	vaciar_bosque(bosque);

	bosque[juego->personaje.posicion.fil][juego->personaje.posicion.col]=juego->personaje.tipo;
	
	agregar_obstaculos_herramientas_chloe_visibles(juego,bosque);
	
}
void mostrar_juego(juego_t juego){

	printf("%s\n",MARCO);
	printf("%s\n",TITULO_1);
	printf("%s\n",TITULO_2);
	printf("%s\n",MARCO);
	printf("%s\n",CUADRO_ALTO_TITULO);

	char bosque[MAX_FILAS][MAX_COLUMNAS];

	cargar_bosque(&juego,bosque);
		
	for(int i=0;i<MAX_FILAS;i++){
		for(int j=0;j<MAX_COLUMNAS;j++){
				printf("|%c|",bosque[i][j]);

		}
		printf("\n");
	}
	printf("%s\n",CUADRO_BAJO_TITULO);

	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",CUADRO_ALTO_MOV,LISTA_DE_MOVIMIENOS_1,LISTA_DE_MOVIMIENOS_2,LISTA_DE_MOVIMIENOS_3,LISTA_DE_MOVIMIENOS_4,LISTA_DE_MOVIMIENOS_5,LISTA_DE_MOVIMIENOS_6,LISTA_DE_MOVIMIENOS_7,LISTA_DE_MOVIMIENOS_8,CUADRO_BAJO_MOV);
}