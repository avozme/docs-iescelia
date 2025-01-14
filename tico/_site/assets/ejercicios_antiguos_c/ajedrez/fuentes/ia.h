/*
PROGRAMA:  Ajedrez 1.0
ARCHIVO:   ia.h
CONTENIDO: Archivo de cabecera de las funciones de inteligencia artificial
AUTOR:     Alfredo Moreno
*/

#ifndef _IA_H
#define _IA_H

#include <stdlib.h>
#include <stdio.h>
#include "tipos.h"

#define PROFUNDIDAD_MAX 9	// Profundidad m�ima del �bol de bsqueda
#define MEMORIA_MAX 10000L	// Memoria m�ima ocupada por el �bol (en bytes)
#define NIVEL_PODA1 4       // Nivel al que se har� la primera poda del �rbol minimax
#define NIVEL_PODA2 6       // Nivel de la segunda poda

// Realiza una valoraci� num�ica del estado del juego y del tablero pasados como argumento
int valorar_estado(Tcasilla tablero[9][9], Testado* estado, char jugador);

// Inicial el recorrido en el �bol de bsqueda.
// Devuelve la valoraci� del mejor nodo-hoja encontrado y el movimiento que hay que realizar
// y que representa el primer paso del camino hacia ese nodo-hoja.
Tmovimiento buscar_mejor_movimiento(Tcasilla tablero[9][9], Testado* estado, char jugador);

// Recorrido por el árbol de búsqueda del juego. Nivel MIN del MINIMAX (correspondiente al jugador contrario)
// Se lleva un control del nivel de profundidad y de la memoria ocupada para no sobrepasar los l�ites.
// Devuelve la valoración MINIMA de todos los nodos hijo.
int jugador_contrario(int profundidad, long int memoria_ocup, Tcasilla tablero[9][9], Testado* estado, char jugador);


// Recorrido por el árbol de búsqueda del juego. Nivel MAX del MINIMAX (correspondiente al jugador activo)
// Se lleva un control del nivel de profundidad y de la memoria ocupada para no sobrepasar los l�ites.
// Devuelve la valoración MINIMA de todos los nodos hijo.
int jugador_activo(int profundidad, long int memoria_ocup, Tcasilla tablero[9][9], Testado* estado, char jugador);


// Hace una copia del tablero
void copiar_tablero(Tcasilla tab_orig[9][9], Tcasilla tab_dest[9][9]);

// Hace una copia del estado
void copiar_estado(Testado* est_orig, Testado* est_dest);

// Escribe el �rbol minimax en la salida est�ndar (usar s�lo para depuraci�n)
void imprimir_result(char* nivel, int prof, int valor);

// Devuelve 1 si la pieza que hay en (x,y) est� protegida por otra pieza
// de su mismo color. Generalmente, la pieza de (x,y) ser� un pe�n y el "protector"
// ser� una pieza mayor (caballo, alfil, torre o dama)
int esta_protegido(Tcasilla tablero[9][9], Testado* estado, int dx, int dy);

#endif
