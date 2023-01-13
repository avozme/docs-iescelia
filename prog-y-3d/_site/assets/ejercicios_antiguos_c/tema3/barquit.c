// Juego de los barquitos (SIMPLIFICADO)
// Actividad obligatoria del tema 5

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// Utilizaremos dos matrices de enteros de 9x9 (pasaremos de la fila 0 y la columna 0,
// y nos quedaremos solo con las coordenadas del 1 al 8, para simplificar).
// En cada posicion de la matriz habra un numero entre 0 cuyo significado esta
// declarado en las siguientes constantes:
#define NADA 0
#define BARCO 1
#define TOCADO 2
#define AGUA 3

// Jugadores
#define HUMANO 'H'
#define MAQUINA 'M'
#define NINGUNO 'X'

// Prototipos de funciones
void dibujar_pantalla(int tab_hum[9][9], int tab_maq[9][9]);
void inicializar(int tab[9][9]);
void colocar_barco(int tab[9][9], int long_barco, char quien);
int comprobar_barco(int tab[9][9], int x, int y, int long_barco);
void disparar(int tab[9][9], char quien);
int comprobar_disparo(int tab[9][9], int x, int y);
int contar_tocados(int tab[9][9]);
int traducir_a_numero(char col);


int main(void)
{
	int tablero_hum[9][9];		// Tablero del jugador humano
	int tablero_maq[9][9];		// Tablero de la maquina
	char ganador;
   int i, tocados;

	randomize();
	inicializar(tablero_hum);	// Inicializamos las matrices
	inicializar(tablero_maq);

	for (i=2; i<=5; i++)			// Colocamos los barcos (de longitud entre 2 y 5)
	{
		// Primero, colocar el barco de longitud i del jugador humano
		colocar_barco(tablero_hum, i, HUMANO);
		// Despues colocar el barco de longitud i de la maquina
		colocar_barco(tablero_maq, i, MAQUINA);
	}

	// Bucle principal del juego
	ganador = NINGUNO;
	do
	{
		dibujar_pantalla(tablero_hum, tablero_maq);

		// El jugador humano dispara sobre el tablero de la maquina
		disparar(tablero_maq, HUMANO);
		// Comprobar si se han hundido todos los barcos del oponente
		tocados = contar_tocados(tablero_maq);
		if (tocados == 14) {
		  ganador = HUMANO;
		  break;
		}
		// La maquina dispara sobre el tablero del jugador humano
		disparar(tablero_hum, MAQUINA);
		// Comprobar si se han hundido todos los barcos del oponente
		tocados = contar_tocados(tablero_hum);
		if (tocados == 14) {
			ganador = MAQUINA;
			break;
		}
	}
	while (ganador == NINGUNO);

	// Mensajes de despedida
	if (ganador == HUMANO)
		printf("Enhorabuena, eres el ganador");
	else
		printf("Te he ganado vilmente. �Intentalo otra vez!");

	return 0;
}

// Inicializa una matriz de juego con todas sus posiciones a 0 (NADA)
void inicializar(int tab[9][9])
{
	int x,y;
	// Las coordenadas correspondientes a la fila 0 y a la columna 0
	// no las vamos a utilizar; solo usaremos de la 1 a la 8 por comodidad
	for (x=1; x<=8; x++)
	  for (y=1; y<=8; y++)
		  tab[x][y] = 0;
}


// Coloca un barco de longitud "long_barco" en el tablero "tab". El parametro
// "quien" sera 'H' (humano) o 'M' (maquina)
void colocar_barco(int tab[9][9], int long_barco, char quien)
{
	int x,y,i;
	char c;
	int correcto;				// �esta el barco colocado correctamente?

	do
	{
		if (quien == HUMANO)		// Al jugador humano le pediremos que introduzca
		{								// las coordenadas del barco por teclado
			printf("Colocando el barco de longitud %i\n", long_barco);
			do {
				printf("Introduzca columna (A-H): ");
				flushall();
				scanf("%c", &c);		// La columna es un caracter (A-H) y debe traducirse a numero (1-8)
				x = traducir_a_numero(c);
			}
			while ((x < 1) || (x > 8));
			do {
				printf("Introduzca fila (1-8): ");
				scanf("%i", &y);
			}
			while ((y < 1) || (y > 8));
			correcto = comprobar_barco(tab, x, y, long_barco);
			if (correcto == 0)
				printf("�El barco no puede ir en esa posicion!\n");
		}
		else							// La maquina elegira sus coordenadas al azar
		{
			x = random(8)+1;
			y = random(8)+1;
			correcto = comprobar_barco(tab, x, y, long_barco);
		}
	}
	while (correcto == 0);		// Repetir todo hasta que el barco este bien colocado

	// Ya tenemos las coordenadas (x,y) de colocacion del barco. Ahora vamos a
	// grabarlo en la matriz poniendo un 1 en las posiciones que ocupa
	for (i = x; i < x+long_barco; i++)
		tab[i][y] = BARCO;		// La constante BARCO vale 1
}


// Comprueba si un barco esta bien colocado. Devuelve 1 si lo esta y 0 si no lo esta
int comprobar_barco(int tab[9][9], int x, int y, int long_barco)
{
	int i, correcto;

	correcto = 1;	// Supondremos que es correcto

	if (x+long_barco >= 8)  // El barco se sale del tablero por la derecha
		correcto = 0;

	for (i=x; i<x+long_barco; i++)
		if (tab[i][y] != NADA)	// Hay otro barco en esa posicion
			correcto = 0;

	return correcto;
}

// Realiza un disparo. El parametro "quien" debe ser 'H' o 'M'
void disparar(int tab[9][9], char quien)
{
	int x,y;
	char c;

	if (quien == HUMANO)			// Dispara el jugador humano
	{
		gotoxy(1,22);
		printf("Realice su disparo\n");
		do {							// Introducir columna
		  gotoxy(1,23);
		  printf("Columna (A-H) :");
		  flushall();
		  scanf("%c", &c);
		  x = traducir_a_numero(c);
		}
		while ((x < 1) || (x > 8));
		do {							// introducir fila
		  gotoxy(1,24);
		  printf("Fila (1-8) :");
		  scanf("%i", &y);
		}
		while ((y < 1) || (y > 8));
	}
	else								// Dispara la maquina
	{
		gotoxy(40,22);
		printf("Me toca disparar...");
		x = random(8)+1;
		y = random(8)+1;
		gotoxy(40,23);
		printf("Columna: %i", x);
		gotoxy(40,24);
		printf("Fila: %i", y);
	}
	comprobar_disparo(tab, x, y);
}

// Comprueba el resultado de un disparo. Devuelve 0 si es agua o 1 si es tocado.
// Modifica la posicion de la matriz que este afectada.
int comprobar_disparo(int tab[9][9], int x, int y)
{
	int result;

	result = 0;

	if (tab[x][y] == BARCO) {
		gotoxy(37,24);
		printf("TOCADO!!");
		result = 1;
		tab[x][y] = TOCADO;
	}

	if (tab[x][y] == NADA) {
		gotoxy(37,24);
		printf("  Agua  ");
		tab[x][y] = AGUA;
	}

	return result;
}

// Cuenta el numero de aciertos en un tablero
int contar_tocados(int tab[9][9])
{
	int x,y,cont;

	cont = 0;

	for (x=1; x<=8; x++)
	  for (y=1; y<=8; y++)
		 if (tab[x][y] == TOCADO) cont++;

	return cont;
}

// Convierte una columna escrita en letra (A-H) a un numero (1-8)
int traducir_a_numero(char col)
{
	int num;
	switch (col)
	{
		case 'A':
		case 'a': num = 1; break;
		case 'B':
		case 'b': num = 2; break;
		case 'C':
		case 'c': num = 3; break;
		case 'D':
		case 'd': num = 4; break;
		case 'E':
		case 'e': num = 5; break;
		case 'F':
		case 'f': num = 6; break;
		case 'G':
		case 'g': num = 7; break;
		case 'H':
		case 'h': num = 8; break;
		default:  num = -1;
	}
	return num;
}
 

// Dibuja la pantalla de juego, incluyendo el contenido de los tableros
void dibujar_pantalla(int tab_hum[9][9], int tab_maq[9][9])
{
	int x,y;

	clrscr();

	gotoxy(19,1);  printf("= TU TABLERO =");
	gotoxy(47,1);  printf("= TABLERO ENEMIGO =");

	gotoxy(21,3);  printf("  ABCDEFGH                      ABCDEFGH");
	gotoxy(21,4);  printf(" +--------+                    +--------+");
	gotoxy(21,5);  printf("1|        |                   1|        |");
	gotoxy(21,6);  printf("2|        |                   2|        |");
	gotoxy(21,7);  printf("3|        |                   3|        |");
	gotoxy(21,8);  printf("4|        |                   4|        |");
	gotoxy(21,9);  printf("5|        |                   5|        |");
	gotoxy(21,10); printf("6|        |                   6|        |");
	gotoxy(21,11); printf("7|        |                   7|        |");
	gotoxy(21,12); printf("8|        |                   8|        |");
	gotoxy(21,13); printf(" +--------+                    +--------+");

	// Dibujamos ahora el contenido del tablero del jugador humano, cuyas coordenadas
	// en la pantalla empiezan en (23, 5)
	for (x=1; x<=8; x++)
	  for (y=1; y<=8; y++)
	  {
		  gotoxy(x+22, y+4);
		  switch (tab_hum[x][y])
		  {
			  case NADA: break;				// No escribir nada
			  case BARCO: printf("o"); break;
			  case AGUA: printf("."); break;
			  case TOCADO: printf("X"); break;
		  }
	  }

	// Ahora dibujamos el contenido del tablero de la maquina
	// Sus coordenadas de pantalla empiezan en (53,5)
	for (x=1; x<=8; x++)
	  for (y=1; y<=8; y++)
	  {
		  gotoxy(x+52, y+4);
		  switch (tab_maq[x][y])
		  {
			  case NADA: break;				// No escribir nada
			  case BARCO: break;				// No debemos ver los barcos enemigos
			  case AGUA: printf("."); break;
			  case TOCADO: printf("X"); break;
		  }
	  }
}
