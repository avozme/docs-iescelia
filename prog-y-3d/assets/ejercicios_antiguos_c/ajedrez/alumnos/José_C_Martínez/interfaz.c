//////////////////INTERFAZ///////////////////

#include "ajedrez.h"
#include "interfaz.h"
#include "comprobar.h"

int A;				///Aquí tenemos otra vez la variable A para el menú ///

void dibujar_tablero(struct s_casillas tablero[9][9]){
int i, j;
int x=1, y=1;
clear();

	for(i=0; i<=8; i++){
		for(j=0; j<=8; j++){
			if(tablero[i][j].color==BLANCA){
				attron(COLOR_PAIR(2));
				move(y, x);
				printw("       ");
				move(y+1, x);
				printw("       ");
				move(y+2, x);
				printw("       ");
				move(y+1, x+3);
				if(tablero[i][j].color_pieza==BLANCA){
					attron(COLOR_PAIR(1));
				}
				if(tablero[i][j].pieza==NADA){
					attron(COLOR_PAIR(2));
				}
				printw("%c", tablero[i][j].pieza);
			}
			if(tablero[i][j].color==NEGRA){
				attron(COLOR_PAIR(3));
				move(y, x);
				printw("       ");
				move(y+1, x);
				printw("       ");
				move(y+2, x);
				printw("       ");
				move(y+1, x+3);
				if(tablero[i][j].color_pieza==NEGRA){
					attron(COLOR_PAIR(4));
				}
				if(tablero[i][j].pieza==NADA){
					attron(COLOR_PAIR(3));
				}
				printw("%c", tablero[i][j].pieza);
			}
			if(tablero[i][j].color==AZUL){
				attron(COLOR_PAIR(5));
				move(y, x);
				printw("       ");
				move(y+1, x);
				printw("       ");
				move(y+2, x);
				printw("       ");
				move(y+1, x+3);
				printw("%c", tablero[i][j].pieza);
			}
			x=x+7;
		}
		y=y+3;
		x=1;
	}
	
	x=64; y=5;				///Aquí hacemos una sombra al tablero ///
	attron(COLOR_PAIR(3));
	do{
		move(y, x);
		printw("  ");
		y=y+1;
	}while(y<29);
	move(28, 10);
	printw("                                                      ");
	presentacion();
	refresh();
}

void presentacion(){			/// Dibujamos el cuadro de la derecha ///
int i;

	for(i=0; i<=40; i++){
		move(i, 80);
		attron(COLOR_PAIR(4));
		printw(" ");
		if((i!=0)&&(i!=40)){
			attron(COLOR_PAIR(6));
		}
		printw("                                         ");
		attron(COLOR_PAIR(4));
		printw(" ");
	}
}

void mover(struct s_estado* estado, struct s_casillas tablero[9][9]){
int io, id, jo, jd;
int x, y, selx, sely;
char colo, filo, cold, fild;
int car, correcto=0;
int jaque=0, i;

x=8; y=25;
io=1; jo=8;

while(1!=0){
								/////////////////// CASILLA ORIGEN ///////////
	do{
		dibujar_tablero(tablero);
		refresh();
		convertir_a_caracter(io, jo, &colo, &filo);
		move(9, 94);
		if(estado->turno==BLANCA){
			attron(COLOR_PAIR(6));
			printw("TURNO BLANCAS");
			move(10, 94);
			printw("-------------");
		}
		else{ 
			attron(COLOR_PAIR(9));
			printw("TURNO NEGRAS");
			move(10, 94);
			printw("------------");
		}
		
		move(12, 94);
		printw("ORIGEN: %c%c", colo, filo);
		
		jaque=comprobar_jaque(tablero, estado);
		if(jaque==1){
			move(18, 91);
			attron(COLOR_PAIR(6));
			printw("¡JAQUE AL REY BLANCO!");
		}
		if(jaque==2){
			move(18, 91);
			attron(COLOR_PAIR(9));
			printw("¡JAQUE AL REY NEGRO!");
		}
		if(jaque==4){
			attron(COLOR_PAIR(6));
			for(i=0; i<=4; i++){
				move(18, 90);
				printw("                       ");
				move(40, 122);
				refresh();
				retardo(7);
				move(18, 90);
				printw("GANADOR: JUGADOR BLANCO");
				move(40, 122);
				refresh();
				retardo(7);
			}
			retardo(15);
			clear();
			A=0;
			return ;
		}
		if(jaque==5){
			attron(COLOR_PAIR(9));
			for(i=0; i<=4; i++){
				move(18, 90);
				printw("                      ");
				move(40, 122);
				refresh();
				retardo(7);
				move(18, 90);
				printw("GANADOR: JUGADOR NEGRO");
				move(40, 122);
				refresh();
				retardo(7);
			}
			retardo(15);
			clear();
			A=0;
			return ;
		}


		attron(COLOR_PAIR(7));
		move(y, x);
		printw("       ");
		move(y+1, x);
		printw("  "); move(y+1, x+5); printw("  ");
		move(y+2, x);
		printw("       ");
		
		
		move(40, 122);
		
		car=getch();
		switch(car){
			case KEY_LEFT: if(x>14){ x=x-7; io=io-1;} break;
			case KEY_RIGHT: if(x<54){ x=x+7; io=io+1;} break;
			case KEY_UP: if(y>6){ y=y-3; jo=jo-1;} break;
			case KEY_DOWN: if(y<24){ y=y+3; jo=jo+1;} break;
			case 10: if((tablero[jo][io].pieza==NADA)||(tablero[jo][io].color_pieza!=estado->turno)){
					car='A'; break; }
					else{ selx=x; sely=y; }
				break;
			case KEY_BACKSPACE: clear(); A=1; return; break;
		}
	}while(car!=10);
	
	id=io; jd=jo;
							/////////////////// CASILLA DESTINO ///////////////
	do{
		convertir_a_caracter(id, jd, &cold, &fild);
		move(9, 94);
		if(estado->turno==BLANCA){
			attron(COLOR_PAIR(6));
			printw("TURNO BLANCAS");
			move(10, 94);
			printw("-------------");
		}
		else{
			attron(COLOR_PAIR(9));
			printw("TURNO NEGRAS");
			move(10, 94);
			printw("------------");
		}

		move(12, 94);
		printw("ORIGEN: %c%c", colo, filo);
		move(13, 94);
		printw("DESTINO: %c%c", cold, fild);
		
		if(jaque==1){
			move(18, 91);
			attron(COLOR_PAIR(6));
			printw("¡JAQUE AL REY BLANCO!");
		}
		if(jaque==2){
			move(18, 91);
			attron(COLOR_PAIR(9));
			printw("¡JAQUE AL REY NEGRO!");
		}
		
		attron(COLOR_PAIR(8));
		move(sely, selx);
		printw("       ");
		move(sely+1, selx);
		printw("  "); move(sely+1, selx+5); printw("  ");
		move(sely+2, selx);
		printw("       ");

		attron(COLOR_PAIR(7));
		move(y, x);
		printw("       ");
		move(y+1, x);
		printw("  "); move(y+1, x+5); printw("  ");
		move(y+2, x);
		printw("       ");
		move(40, 122);

		car=getch();
		switch(car){
			case KEY_LEFT: if(x>14){ x=x-7; id=id-1;} break;
			case KEY_RIGHT: if(x<54){ x=x+7; id=id+1;} break;
			case KEY_UP: if(y>6){ y=y-3; jd=jd-1;} break;
			case KEY_DOWN: if(y<24){ y=y+3; jd=jd+1;} break;
			case 10: if((io!=id)||(jo!=jd)){
					correcto=comprobar(tablero, estado, io, jo, id, jd);
					if(((tablero[jd][id].color_pieza!=estado->turno)||(tablero[jd][id].pieza==NADA))&&(correcto==1)){
						tablero[jd][id].pieza=tablero[jo][io].pieza;
						tablero[jd][id].color_pieza=tablero[jo][io].color_pieza;
						tablero[jo][io].pieza=NADA;
					
					if(estado->turno==BLANCA){ estado->turno=NEGRA; }
					else if(estado->turno==NEGRA){ estado->turno=BLANCA; }
					}
				else{ car='A'; }
				}
				break;
			case KEY_BACKSPACE: clear(); A=1; return; break;
		}
		if((tablero[jd][id].pieza==PEON)&&(tablero[jd][id].color_pieza==BLANCA)&&(jd==1)){
			attron(COLOR_PAIR(6));
		cambiar_pieza(tablero, jd, id);
		}
		if((tablero[jd][id].pieza==PEON)&&(tablero[jd][id].color_pieza==NEGRA)&&(jd==8)){
			attron(COLOR_PAIR(9));
			cambiar_pieza(tablero, jd, id);
		}
		dibujar_tablero(tablero);
		refresh();
	}while(car!=10);
	io=id; jo=jd;
}
} 

void convertir_a_caracter(int i, int j, char *col, char *fil){

	switch(i){
		case 1: *col='A'; break;
		case 2: *col='B'; break;
		case 3: *col='C'; break;
		case 4: *col='D'; break;
		case 5: *col='E'; break;
		case 6: *col='F'; break;
		case 7: *col='G'; break;
		case 8: *col='H'; break;
	}
	switch(j){
		case 1: *fil='8'; break;
		case 2: *fil='7'; break;
		case 3: *fil='6'; break;
		case 4: *fil='5'; break;
		case 5: *fil='4'; break;
		case 6: *fil='3'; break;
		case 7: *fil='2'; break;
		case 8: *fil='1'; break;
	}
}

void cambiar_pieza(struct s_casillas tablero[9][9], int j, int i){
int opc, tecla, x, y, xa, ya;

y=25; x=94; opc=1;
ya=y; xa=x;

	move(y-2, x);
	printw("CAMBIAR PEON POR:");
	move(y, x+4);
	printw("DAMA");
	move(y+2, x+4);
	printw("ALFIL");
	move(y+4, x+4);
	printw("TORRE");
	move(y+6, x+4);
	printw("CABALLO");
	
	do{
		move(ya, xa);
		printw("  ");
		move(y, x);
		printw(">>");
		move(40, 122);
		xa=x; ya=y;
		
		
		tecla=getch();
		switch(tecla){
			case KEY_UP: if(y>25){ y=y-2; opc=opc-1; }	break;
			case KEY_DOWN: if(y<31){ y=y+2; opc=opc+1; }	break;
			case 10: switch(opc){
					case 1: tablero[j][i].pieza=DAMA; break;
					case 2: tablero[j][i].pieza=ALFIL; break;
					case 3: tablero[j][i].pieza=TORRE; break;
					case 4: tablero[j][i].pieza=CABALLO; break;
				}
				break;
		}
	} while(tecla!=10);
}