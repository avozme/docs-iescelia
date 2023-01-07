#include <ncurses.h>


#define BLANCAS 'B'
#define NEGRAS 'N'
#define PEON 'P'
#define TORRE 'T'
#define CABALLO 'C'
#define ALFIL 'A'
#define REY 'R'
#define REINA 'D'


struct s_casilla
{
   char pieza;
   char color_pieza;
   char color_casilla;
};

struct s_estado
{
	char turno;
	int cont;
	char jaque_al_blanco;
	char jaque_al_negro;
	int xp, yp;
	int enroque_blancas;
	int enroque_negras;
};


void inicializar_estado (struct s_estado *estado);
int inicializar_tablero(struct s_casilla tablero[9][9]);
void retardo(int tiempo);


