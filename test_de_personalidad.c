#include <stdio.h>
#include <stdbool.h>
#include "test_de_personalidad.h"

const char ANIME = 'A';
const char MUSICA_POP = 'M';
const char LIMPIEZA = 'L';
const int VALOR_ANIME = 2;
const int VALOR_MUSICA_POP = 3;
const int VALOR_LIMPIEZA = 1;

const char BAMBU = 'B';
const char PESCADO = 'P';
const char FOCAS = 'F';
const int VALOR_BAMBU = 6;
const int VALOR_PESCADO = 9;
const int VALOR_FOCAS = 3;

const int MAX_PISO = 18;
const int MIN_PISO = 1;

const int MAX_GRITO = 18;
const int MIN_GRITO = 1;

const int MIN_POLAR = 5;
const int MAX_POLAR = 24;
const int MIN_PANDA = 25;
const int MAX_PANDA= 43;
const int MIN_PARDO = 44;
const int MAX_PARDO = 63;

const char POLAR = 'I';
const char PANDA = 'P';
const char PARDO = 'G';

/*VALIDACIONES*/

bool valido_respuesta_1 (char respuesta_1)
	{
		if((respuesta_1) == ANIME || (respuesta_1) == MUSICA_POP || (respuesta_1) == LIMPIEZA)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

bool valido_respuesta_2 (char respuesta_2)
	{
		if((respuesta_2 == BAMBU) || (respuesta_2 == PESCADO) || (respuesta_2) == FOCAS)
			{
				return true;
			}
		else 
		{
			return false;
		}
	}		

bool valido_respuesta_3 (int respuesta_3)
	{
		if((respuesta_3) >= MIN_PISO && (respuesta_3) <=MAX_PISO)
			{
				return true;
			}
		else 
		{
			return false;
		}
	}

bool valido_respuesta_4 (int respuesta_4)
	{
		if((respuesta_4) >= MIN_GRITO && (respuesta_4) <=MAX_GRITO)
			{
				return true;
			}
		else 
		{
			return false;
		}
	}

/*RESPUESTA DE ENCUESTAS*/

void pido_respuesta_1(char* respuesta_1)
{
	printf("Vas a ver televisión un rato, pones el canal de: Anime(A), Musica Pop (M), Limpieza (L).\n");
	scanf(" %c",respuesta_1);

	while(!valido_respuesta_1(*respuesta_1))
	{
		printf("El canal ingresado no existe. ¿Qué canal pondrías? %c %c %c \n",ANIME,MUSICA_POP,LIMPIEZA);
		scanf(" %c",respuesta_1);
	}
}

void pido_respuesta_2(char* respuesta_2)
{
	printf("Solo puedes guardar un alimento en tu vianda: Bambú(B), Pescado(P), Focas(F).\n");
	scanf(" %c",respuesta_2);

	while(!valido_respuesta_2(*respuesta_2))
	{
		printf("No podés guardar ese alimento en la vianda. ¿Qué alimento pondrías? %c %c %c \n",BAMBU,PESCADO,FOCAS);
		scanf(" %c",respuesta_2);
	}
}

void pido_respuesta_3(int* respuesta_3)
{
	printf("Te comprás una torre con tus dos hermanos de 18 pisos.¿En qué piso te gustaría vivir?\n");
	scanf(" %i",respuesta_3);

	while(!valido_respuesta_3(*respuesta_3))
	{
		printf("Ese piso no existe.¿En qué piso vivirÍas? %i - %i\n",MIN_PISO,MAX_PISO);
		scanf(" %i",respuesta_3);
	}
}

void pido_respuesta_4(int* respuesta_4)
{
	printf("¡Oh, una rata!¿Qué tan fuerte gritas del 1 al 18? Siendo 1 no gritar y 18 desgarrarse la garganta.\n");
	scanf(" %i",respuesta_4);

	while(!valido_respuesta_4(*respuesta_4))
	{
		printf("Mmmmm. No puedo reconocer tu grito. Ingresa un numero valido. %i - %i \n",MIN_GRITO,MAX_GRITO);
		scanf(" %i",respuesta_4);
	}
}

/*TRANSFORMACIÓN DE PUNTAJES*/
 
int transformar_respuesta_1(char respuesta_1)
{
	if(respuesta_1 == ANIME)
	{
		return VALOR_ANIME;
	}
	else if(respuesta_1 == MUSICA_POP)
	{
		return VALOR_MUSICA_POP;
	}
	else
	{
		return VALOR_LIMPIEZA;
	}

}

int transformar_respuesta_2(char respuesta_2)
{
	if(respuesta_2 == BAMBU)
	{
		return VALOR_BAMBU;
	}
	else if(respuesta_2 == PESCADO)
	{
		return VALOR_PESCADO;
	}
	else
	{
		return VALOR_FOCAS;
	}
}


int transformar_respuesta_3(int respuesta_3)
{
	return respuesta_3;

}

int transformar_respuesta_4(int respuesta_4)
{
	return respuesta_4;
}

/*CALCULO*/

int calculo_de_puntaje(char respuesta_1, char respuesta_2,int respuesta_3,int respuesta_4)
{
	int puntaje_total= ((transformar_respuesta_1(respuesta_1)) * (transformar_respuesta_2(respuesta_2)) + transformar_respuesta_3(respuesta_3) + transformar_respuesta_4(respuesta_4) );

	return puntaje_total;
}

/*IMPRESION*/

void imprimo_personalidad(char respuesta_1, char respuesta_2,int respuesta_3,int respuesta_4)
{
	if ((calculo_de_puntaje(respuesta_1,respuesta_2,respuesta_3,respuesta_4))>= MIN_POLAR && (calculo_de_puntaje(respuesta_1,respuesta_2,respuesta_3,respuesta_4))<= MAX_POLAR)
	{
		printf("- Oso Polar (I) -\n");

	}
	else if ((calculo_de_puntaje(respuesta_1,respuesta_2,respuesta_3,respuesta_4))>= MIN_PANDA && (calculo_de_puntaje(respuesta_1,respuesta_2,respuesta_3,respuesta_4))<= MAX_PANDA)
	{
		printf("- Oso Panda (P) -\n");

	}
	else
	{
		printf("- Oso Pardo (G) -\n");

	}
}	
/*DESIGNO PERSONAJE*/

char designo_personaje(char respuesta_1, char respuesta_2,int respuesta_3,int respuesta_4)
{
	if ((calculo_de_puntaje(respuesta_1,respuesta_2,respuesta_3,respuesta_4))>= MIN_POLAR && (calculo_de_puntaje(respuesta_1,respuesta_2,respuesta_3,respuesta_4))<= MAX_POLAR)
	{
		return POLAR;

	}
	else if ((calculo_de_puntaje(respuesta_1,respuesta_2,respuesta_3,respuesta_4))>= MIN_PANDA && (calculo_de_puntaje(respuesta_1,respuesta_2,respuesta_3,respuesta_4))<= MAX_PANDA)
	{
		return PANDA;

	}
	else
	{
		return PARDO;

	}
}

/*FIRMA AGREGADA PARA TP2*/

void test_de_personalidad(char* personalidad_detectada){

	char respuesta_1;
	char respuesta_2;
	int respuesta_3;
	int respuesta_4;

	pido_respuesta_1(&respuesta_1);
	pido_respuesta_2(&respuesta_2);
	pido_respuesta_3(&respuesta_3);
	pido_respuesta_4(&respuesta_4);

	(*personalidad_detectada)=designo_personaje(respuesta_1,respuesta_2,respuesta_3,respuesta_4);
}	

