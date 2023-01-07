#include "tablero.h"
#include "mov.h"
#include <curses.h>

int f, c,fil=7,column=0;// variables glovales
void tirar (struct s_casillas tab[8][8], struct s_estado *esta)
{
	
	int fila,columna,filad,columnad,i,va,pass,toca;
	char color;
	pass=0;
 	if (esta->cont==0)
	{
		fila=7;
 	columna=0;
	}
	
	
	
	
	
		if (esta->cont%2==0)		// ----------------------   Turno BLANCAS
		{
			while(pass==0)
			{
 				
 				color=BLANCA;
				
				origen(tab,&fila,&columna,color,esta);
				
				
				if(esta->salir!=1)// para terminar el prgrama si es 1 sale 
				{
				
					filad=fila;
					
					columnad=columna;
					destino(tab,&filad,&columnad,color,esta);
				
				
					va=movimientos(tab,&columna,&fila, &columnad, &filad,color,esta);
				
// 				
					if ((va == 1)||(va==2))
						pass=1;
					
				}
				else
				pass=1;
			}
		}
		
		else				// ----------------------   Turno NEGRAS
		{
			while(pass==0)
			{
				
				color=NEGRA;
				origen(tab,&fila,&columna,color,esta);
				if(esta->salir!=1)// para terminar el prgrama si es 1 sale 
				{
				filad=fila;
				columnad=columna;
				destino(tab,&filad,&columnad,color,esta);
				
				va=movimientos(tab,&columna,&fila, &columnad, &filad,color,esta);
				
				
					if ((va == 1)||(va==2))
						pass=1;
// 					else
// 					{	
// 						toca=' ';
// // 						dibujar_cuadro(tab,color,&filad,&columnad,toca);
// // 						move(17,83);
// // 						printw(" MOVIMIENTO INCORRECTO");
// 						
// 					}
				}
				else
					pass=1;
			}
		}
	
	if(va==1)// Se realiza el cambio de ficha execto el del rey en  caso d enroque
	{
		tab[filad][columnad].pieza=tab[fila][columna].pieza;
		tab[filad][columnad].color_pieza=tab[fila][columna].color_pieza;
		tab[fila][columna].pieza=' ';
		tab[fila][columna].color_pieza=' ';	
	}
}

void origen(struct s_casillas tab[8][8],int *fila , int *columna ,char color,struct s_estado *esta)
{
	
	int c,  i, pass,seguir;
	char toca;
	toca='o';// pa ssaber si es origen o destino
	
	
	
	seguir=0;
	while(seguir==0)
	{
		
		selec_casilla(tab, fila, columna,color,toca,esta);
		
		if (esta->salir!=1)// para terminar el prgrama si es 1 sale
		{
		if(tab[*fila][*columna].color_pieza==color)
			seguir=1;
		}
		else
			seguir=1;
	}
	
	
}

void destino (struct s_casillas tab[8][8], int *filad, int *columnad,char color,struct s_estado *esta )
{
	
	int toca;
	toca='d';
	
	selec_casilla(tab, filad, columnad,color,toca,esta);	
}	



int movimientos(struct s_casillas tab[8][8],int *columna,int *fila, int *columnad, int *filad,char color,struct s_estado *esta)
{
	int v,n,na,compro,cont_pie,cont,corre,i;
	v=0;
	cont_pie=1;
	compro=0;
	corre=0;
	
	

	
	switch (tab[*fila][*columna].pieza)
	{
		case 'C': //mov caballo
		{
			if((*fila-2==*filad)&&(*columna-1==*columnad)&&(tab[*filad][*columnad].color_pieza!=color))v=1;//2 arriba 1 izq
			if((*fila-2==*filad)&&(*columna+1==*columnad)&&(tab[*filad][*columnad].color_pieza!=color))v=1;//2 arriba 1 der
			if((*fila-1==*filad)&&(*columna+2==*columnad)&&(tab[*filad][*columnad].color_pieza!=color))v=1;//1 arriba 2 der
			if((*fila-1==*filad)&&(*columna-2==*columnad)&&(tab[*filad][*columnad].color_pieza!=color))v=1;//1 arriba 2 izq
			if((*fila+2==*filad)&&(*columna-1==*columnad)&&(tab[*filad][*columnad].color_pieza!=color))v=1;//2 abajo 1 izq
			if((*fila+2==*filad)&&(*columna+1==*columnad)&&(tab[*filad][*columnad].color_pieza!=color))v=1;//2 abajo 1 der
			if((*fila+1==*filad)&&(*columna+2==*columnad)&&(tab[*filad][*columnad].color_pieza!=color))v=1;//1 abajo 2der
			if((*fila+1==*filad)&&(*columna-2==*columnad)&&(tab[*filad][*columnad].color_pieza!=color))v=1;//1 abajo 2 izq
			
			return v;
		};break;
		case 'T'://mov torre
		{	
			
			if (*fila==*filad)
			{
				cont=*columna;
				if (*columna<*columnad)// mov arriba
				{
					while(cont!=*columnad)
					{
						if (tab[*fila][*columna+cont_pie].color_pieza!=color)
						{
							cont_pie++;
							cont++;
							compro++;
						
						}
						else
							cont=*columnad;
			
					}
					if ((*columnad-*columna)== compro)
						v=1;
						
				}
				if (*columna>*columnad)// mov abajo
				{
					cont=*columna;
					while(cont!=*columnad)
					{
						if (tab[*fila][*columna-cont_pie].color_pieza!=color)
						{
							cont_pie++;
							compro++;
							cont--;
						}
						else
							cont=*columnad;
					
					}
					if ((*columna-*columnad)==compro)
						v=1;
				
				}
				
			}
			if (*columna==*columnad)
			{	
				cont=*fila;
				if (*fila<*filad)//mov izq
				{
					while(cont!=*filad)
					{
						if(tab[*fila+cont_pie][*columna].color_pieza!=color)
						{
							cont_pie++;
							cont++;
							compro++;
						}
						else
							cont=*filad;
						
					}
					if ((*filad-*fila)== compro)
						v=1;

				}
				
				
				if (*fila>*filad)//mov der
				{
					compro=0;
					cont=*fila;
					while(cont!=*filad)
					{
						if (tab[*fila-cont_pie][*columna].color_pieza!=color)
						{
							cont_pie++;
							compro++;
							cont--;
						}
						else
							cont=*filad;
						
					}
				
			
					if ((*fila-*filad)==compro)
						v=1;
			
				}
			}
			if(v==1)
			{
				if (color==BLANCA)
					esta->mov_torre= esta->mov_torre +1;
				if (color==NEGRA)
					esta->mov_torren= esta->mov_torren +1;
			}
			return v;
			
		};break;
		
		case 'P'://peon
		{
			
			if (NEGRA==color)// peon negro
			{
				
				
				if (*fila==1)// Peón puede avanzar dos casillas
				{
				   if ((*fila+1==*filad)&&(*columna+1==*columnad)&&(tab[*filad][*columnad].color_pieza==BLANCA))v=1;
				    if ((*fila-1==*filad)&&(*columna+1==*columnad)&&(tab[*filad][*columnad].color_pieza==BLANCA))v=1;
				      if ((*fila+2==*filad)&&(*columna==*columnad)&&(tab[*filad][*columnad].color_pieza==' '))v=1;
				      if ((*fila+1==*filad)&&(*columna==*columnad)&&(tab[*filad][*columnad].color_pieza==' '))v=1;
				}
				else // Peón solo avanza una casilla
				{
			           if ((*fila+1==*filad)&&(*columna+1==*columnad)&&(tab[*filad][*columnad].color_pieza==BLANCA))v=1;
				   if ((*fila+1==*filad)&&(*columna-1==*columnad)&&(tab[*filad][*columnad].color_pieza==BLANCA))v=1;
			        	if ((*fila+1==*filad)&&(*columna==*columnad)&&(tab[*filad][*columnad].color_pieza==' '))v=1;
				
				}	
			
			
			}
			
			
			if (BLANCA==color)// peron blanco
			{
				
				
				if(*fila==6)		// Peón puede avanzar dos casillas
				{
					
			           if ((*fila-1==*filad)&&(*columna-1==*columnad)&&(tab[*filad][*columnad].color_pieza==NEGRA))v=1;
				   if ((*fila-1==*filad)&&(*columna+1==*columnad)&&(tab[*filad][*columnad].color_pieza==NEGRA))v=1;
				   if ((*fila-2==*filad)&&(*columna==*columnad)&&(tab[*filad][*columnad].color_pieza==' '))v=1;
				   if ((*fila-1==*filad)&&(*columna==*columnad)&&(tab[*filad][*columnad].color_pieza==' '))v=1;
				   
				  
				   
				}
				else			// Peón solo avanza una casilla
				{
				   if ((*fila-1==*filad)&&(*columna-1==*columnad)&&(tab[*filad][*columnad].color_pieza==NEGRA))v=1;
			           if ((*fila-1==*filad)&&(*columna+1==*columnad)&&(tab[*filad][*columnad].color_pieza==NEGRA))v=1;
				   if ((*fila-1==*filad)&&(*columna==*columnad)&&(tab[*filad][*columnad].color_pieza==' '))v=1;
				   
					
				}
			}
			
			return v;
		
		};break;
		case 'R': //rey
		{
			if (tab[*filad][*columnad].color_pieza!=color)
			{
				
				if((*fila==*filad)&&(*columna-1==*columnad))v=1;
 				if((*fila==*filad)&&(*columna+1==*columnad))v=1;
 				if((*fila+1==*filad)&&(*columna+1==*columnad))v=1;
 				if((*fila-1==*filad)&&(*columna-1==*columnad))v=1;
 				if((*fila-1==*filad)&&(*columna+1==*columnad))v=1;
 				if((*fila+1==*filad)&&(*columna-1==*columnad))v=1;
				if ((*fila+1==*filad)&&(*columna==*columnad))v=1;
 				if ((*fila-1==*filad)&&(*columna==*columnad))v=1;

				
				if (color==BLANCA)// enroque rey banco
				{
					
					if ((esta->mov_rey==0)&&(esta->mov_torre==0)&&(tab[7][5].pieza==' ')&&(tab[7][6].pieza==' ')&&(*filad==7)&&(*columnad==6))// enroque corto
					{
						v=2;
						
						tab[*filad][*columnad-1].pieza=tab[7][7].pieza;
						tab[*filad][*columnad-1].color_pieza=tab[7][7].color_pieza;
						tab[7][6].pieza=tab[*fila][*columna].pieza;
						tab[7][6].color_pieza=tab[*fila][*columna].color_pieza;
						tab[*fila][*columna].pieza=' ';
						tab[*fila][*columna].color_pieza=' ';
						tab[7][7].pieza=' ';
						tab[7][7].color_pieza=' ';
					}
					if ((esta->mov_rey==0)&&(esta->mov_torre==0)&&(tab[7][1].pieza==' ')&&(tab[7][2].pieza==' ')&&(tab[7][3].pieza==' ')&&(*filad==7)&&(*columnad==2))//enroque largo
					{
						v=2;
						tab[*filad][*columnad+1].pieza=tab[7][0].pieza;
						tab[*filad][*columnad+1].color_pieza=tab[7][0].color_pieza;
						tab[7][2].pieza=tab[*fila][*columna].pieza;
						tab[7][2].color_pieza=tab[*fila][*columna].color_pieza;
						tab[*fila][*columna].pieza=' ';
						tab[*fila][*columna].color_pieza=' ';
						tab[7][0].pieza=' ';
						tab[7][0].color_pieza=' ';
					
					}
				}
				if (color==NEGRA)// enroque rey banco
				{
					
					
					if ((esta->mov_reyn==0)&&(esta->mov_torren==0)&&(tab[0][5].pieza==' ')&&(tab[0][6].pieza==' ')&&(*filad==0)&&(*columnad==6))// enroque corto
					{
						v=2;
						
						tab[*filad][*columnad-1].pieza=tab[0][7].pieza;
						tab[*filad][*columnad-1].color_pieza=tab[0][7].color_pieza;
						tab[0][6].pieza=tab[*fila][*columna].pieza;
						tab[0][6].color_pieza=tab[*fila][*columna].color_pieza;
						tab[*fila][*columna].pieza=' ';
						tab[*fila][*columna].color_pieza=' ';
						tab[0][7].pieza=' ';
						tab[0][7].color_pieza=' ';
					}
					if ((esta->mov_rey==0)&&(esta->mov_torre==0)&&(tab[0][1].pieza==' ')&&(tab[0][2].pieza==' ')&&(tab[0][3].pieza==' ')&&(*filad==0)&&(*columnad==2))//enroque largo
					{
						v=2;
						tab[*filad][*columnad+1].pieza=tab[0][0].pieza;
						tab[*filad][*columnad+1].color_pieza=tab[0][0].color_pieza;
						tab[0][2].pieza=tab[*fila][*columna].pieza;
						tab[0][2].color_pieza=tab[*fila][*columna].color_pieza;
						tab[*fila][*columna].pieza=' ';
						tab[*fila][*columna].color_pieza=' ';
						tab[0][0].pieza=' ';
						tab[0][0].color_pieza=' ';
					
					}	
				}
				
				
				if((v==1)||(v==2))
				{
				if (color==BLANCA)
					esta->mov_rey=esta->mov_rey+1;
				if (color==NEGRA)
					esta->mov_reyn=esta->mov_reyn+1;
				}
				return v;
			}
		};break;	
		case 'A'://arfil
		{	
			
				if (*columna<*columnad)
				{
					
								
					cont=*columna;
					if(*fila<*filad)
					
					{
						compro=1;
						while(cont!=*columnad)
						{
							if ((tab[*fila+cont_pie][*columna+cont_pie].color_pieza!=color)&&(*columna+cont_pie!=*columnad)&&(*fila+cont_pie!=*filad))
							{
								cont_pie++;
								compro++;
								cont++;
							}
						else
							cont=*columnad;
			
						}
						if( ((*columnad-*columna)== compro)&&((*filad-*fila)==compro)&&(tab[*filad][*columnad].color_pieza!=color))
							v=1;
					}
					if(*filad<*fila)
					{
						compro=1;
						
						while(cont!=*columnad)
						{
							if((tab[*fila-cont_pie][*columna+cont_pie].color_pieza!=color)&&(*columna+cont_pie!=*columnad)&&(*fila-cont_pie!=*filad))
							{
								cont_pie++;
								compro++;
								cont++;
// // 								
							}
							else
							cont=*columnad;
						
						
						}
							
					if (((*columnad-*columna)== compro)&&((*fila-*filad)==compro)&&(tab[*filad][*columnad].color_pieza!=color) )
							v=1;
					}
				}
				if (*columna>*columnad)
				{
		 		
					compro=1;
					if(*fila<*filad)
					{
						
						cont=*columna;
						while(cont!=*columnad)
						{
							if ((tab[*fila+cont_pie][*columna-cont_pie].color_pieza!=color)&&(*fila+cont_pie!=*filad)&&(*columna-cont_pie!=*columnad))
							{
								cont_pie++;
								cont++;
								compro++;
						
							}
							else
								cont=*columnad;
						
						}	
						
						
						
						
						if (((*columna-*columnad)==compro)&&((*filad-*fila)==compro)&&(tab[*fila+cont_pie][*columna-cont_pie].color_pieza!=color))
							v=1;
					}
					if(*filad<*fila)
					
					{
						cont=*columna;
						compro=1;
						while(cont!=*columnad)
						{
													
							if((tab[*fila-cont_pie][*columna-cont_pie].color_pieza!=color)&&(*fila-cont_pie!=*filad)&&(*columna-cont_pie!=*columnad))
							{
								cont_pie++;
								cont--;
								compro++;
							}
							else
								cont=*columnad;
							
							
						}
												

						
						if (((*columna-*columnad)==compro)&&((*fila-*filad)==compro)&&(tab[*filad][*columnad].color_pieza!=color))
							v=1;
					
					}
				}
			
				return v;
			};break;
		case 'D':// mov dama arrfil+torre
		{
			
			
			if (*fila==*filad)
			{
				cont=*columna;
				if (*columna<*columnad)// mov arriba
				{
					while(cont!=*columnad)
					{
						if (tab[*fila][*columna+cont_pie].color_pieza!=color)
						{
							cont_pie++;
							cont++;
							compro++;
						
						}
						else
							cont=*columnad;
			
					}
					if ((*columnad-*columna)== compro)
						v=1;
						
				}
				if (*columna>*columnad)// mov abajo
				{
					cont=*columna;
					while(cont!=*columnad)
					{
						if (tab[*fila][*columna-cont_pie].color_pieza!=color)
						{
							cont_pie++;
							compro++;
							cont--;
						}
						else
							cont=*columnad;
					
					}
					if ((*columna-*columnad)==compro)
						v=1;
				
				}
				
			}
			if (*columna==*columnad)
			{	
				cont=*fila;
				if (*fila<*filad)//mov izq
				{
					while(cont!=*filad)
					{
						if(tab[*fila+cont_pie][*columna].color_pieza!=color)
						{
							cont_pie++;
							cont++;
							compro++;
						}
						else
							cont=*filad;
						
					}
					if ((*filad-*fila)== compro)
						v=1;
						
				
				}
				
				
				if (*fila>*filad)//mov der
				{
					
					compro=0;
					cont=*fila;
					while(cont!=*filad)
					{
						if (tab[*fila-cont_pie][*columna].color_pieza!=color)
						{
							cont_pie++;
							compro++;
							cont--;
						}
						else
							cont=*filad;
						
					}
				
			
					if ((*fila-*filad)==compro)
						v=1;
				
				}
			}
				
			if(v==0)// por si en los casos anterios el mov es correcto aki no entra
			{
				
				if (*columna<*columnad)
				{
					
								
					cont=*columna;
					if(*fila<*filad)
					
					{
						compro=1;
						while(cont!=*columnad)
						{
							if ((tab[*fila+cont_pie][*columna+cont_pie].color_pieza!=color)&&(*columna+cont_pie!=*columnad)&&(*fila+cont_pie!=*filad))
							{
								cont_pie++;
								compro++;
								cont++;
							}
						else
							cont=*columnad;
			
						}
						if (((*columnad-*columna)== compro)&&((*filad-*fila)==compro)&&(tab[*filad][*columnad].color_pieza!=color))
							v=1;
					}
					if(*filad<*fila)
					{
						compro=1;
						
						while(cont!=*columnad)
						{
							if((tab[*fila-cont_pie][*columna+cont_pie].color_pieza!=color)&&(*columna+cont_pie!=*columnad)&&(*fila-cont_pie!=*filad))
							{
								cont_pie++;
								compro++;
								cont++;
// // 								
							}
							else
							cont=*columnad;
						
						
						}
					

						
							
						if (((*columnad-*columna)== compro) &&((*fila-*filad)==compro)&&(tab[*filad][*columnad].color_pieza!=color))
					
								v=1;
						}
				}
				if (*columna>*columnad)
				{
		 			
					compro=1;
					if(*fila<*filad)
					{
						cont=*columna;
						while(cont!=*columnad)
						{
							if ((tab[*fila+cont_pie][*columna-cont_pie].color_pieza!=color)&&(*fila+cont_pie!=*filad)&&(*columna-cont_pie!=*columnad))
							{
								cont_pie++;
								cont++;
								compro++;
						
							}
							else
								cont=*columnad;
						
						}	
						
						
						
						
						if (((*columna-*columnad)==compro)&&((*filad-*fila)==compro)&&(tab[*filad][*columnad].color_pieza!=color))
							v=1;
					}
					if(*filad<*fila)
					
					{
						cont=*columna;
						compro=1;
						while(cont!=*columnad)
						{
													
							if((tab[*fila-cont_pie][*columna-cont_pie].color_pieza!=color)&&(*fila-cont_pie!=*filad)&&(*columna-cont_pie!=*columnad))
							{
								cont_pie++;
								cont--;
								compro++;
							}
							else
								cont=*columnad;
							
							
						}
						if (((*columna-*columnad)==compro)&&((*fila-*filad)==compro)&&(tab[*fila+cont_pie][*columna-cont_pie].color_pieza!=color))
							v=1;
					} 
			
			
			
				}
	
	
			}
			return v;
		};break;
	}
}




void dibujar_cuadro(struct s_casillas tab[8][8],char color,int *fila,int *columna,char toca)// pasar
{
	
	char i;
	for(i=0;i<=10;i++)
	{
			
			move(8+i,83);
			attron(COLOR_PAIR(1));
			printw("                       \n");	
			
	
	}
	if (color==BLANCA)// dibuja pa el caso d las blancas
	{
		
		move(8,85);
		attron(COLOR_PAIR(1));
		printw(" Turno Blancas    ");
		move(10,85);
	
		if(toca=='o')
		{	
			move(11,85);
			printw(" Origen " );
			move(12,85);
			printw("   Fila: %i",*fila+1);
			move(13,85);
			printw("   Columna: %c ",*columna+65);
			f=*fila;
			c=*columna;
			
			
		}
		if(toca=='d')
		{	
			move(11,85);
			printw(" Origen " );
			
			move(12,85);
			printw("   Fila: %i",f+1);
			move(13,85);
			printw("   Columna: %c ",c+65);
			move(15,85);
			printw(" Destino " );
			
			move(16,85);
			printw("   Fila: %i",*fila+1);
			move(17,85);
			printw("   Columna: %c ",*columna+65);
		}
	}
		
	if (color==NEGRA)//dibuja pa el caso d las negras
	{
		
		move(8,85);
		attron(COLOR_PAIR(1));
		printw(" Turno Negras    ");
		move(10,85);
	
		if(toca=='o')//saca por pantalla solo el origen
		{	
			move(11,85);
			printw(" Origen " );
			
			move(12,85);
			printw("   Fila: %i",*fila+1);
			move(13,85);
			printw("   Columna: %c ",*columna+65);
			f=*fila;
			c=*columna;
			
		}
		if(toca=='d')//saca por pantalla el origen y destino
		{	
			move(11,85);
			printw(" Origen " );
			move(12,85);
			printw("   Fila: %i",f+1);
			move(13,85);
			printw("   Columna: %c ",c+64);
			
			move(15,85);
			printw(" Destino " );
			
			move(16,85);
			printw("   Fila: %i",*fila+1);
			move(17,85);
			printw("   Columna: %c ",*columna+65);
		}
		
		
	}


}



void selec_casilla(struct s_casillas tab[8][8], int *fila,int *columna,char color,char toca,struct s_estado *esta)
{
	int c, pass,i,na,columna_menu,fila_menu,columna_men,fila_men;
	
	
		
	pass=0;
	
	*fila=fil;// para q se kede el cursor en la utlimo movimiento
	*columna=column;// para q se kede el cursor en la utlimo movimiento
	while(pass==0)
	{
		pintar_tablero(tab);
		dibujar_cuadro(tab,color,fila,columna,toca);
		
		
		column=(*columna*9)+9;// pinto el recuadro pa seleccionar la casilla
		fil=(*fila*4)+6;
		move(fil,column);
		attron(COLOR_PAIR(7));
		printw("         ");
		move(fil+1,column);
		printw(" ");
		move(fil+1,column+8);
		printw(" ");
		move(fil+2,column);
		printw(" ");
		move(fil+2,column+8);
		printw(" ");
		move(fil+3,column);
		printw("         ");
				
	
		c=getch();
		switch(c)
		{
		
			case KEY_UP:
			{
				if (*fila>0)
					*fila=*fila-1;
			};break;
		
			case KEY_DOWN:
			{
				if(*fila<7)
					*fila= *fila+1;
			};break;
					
			case KEY_LEFT:
			{
				if(*columna>0)
					*columna=*columna -1;
			};break;
			case KEY_RIGHT:
			{
				if(*columna<7)
					*columna=*columna+1;
			};break;
			case 10:
			{
			
				pass=1;
				
			};break;
			case 'm':
			{
				columna_menu=0;
				fila_menu=1;
	
				pass=0;
 				while(pass==0)
				{
					cuadro_menu();
		
					columna_men=(columna_menu)+49;
					fila_men=(fila_menu)+15;
					move(fila_men, columna_men);
					attron(COLOR_PAIR(8));
					printw(" ");
					c=getch();
					switch(c)
					{
						case KEY_UP:
						{
							if (fila_menu>1)
							fila_menu=fila_menu-1;
							
						};break;
		
						case KEY_DOWN:
						{
							if(fila_menu<4)
							fila_menu= fila_menu+1;
						};break;
 						case 10:
 						{
							pass=1;
							
							
				
 						};break;
					}
 			
 			
				}
					
				
				
				switch(fila_menu)// menu dentro d juego
				{
					case 1:// cargar partida
					{
 					FILE *f;
 					
					f=fopen("partida.bin","r+b");
 					if (f==NULL)
					{	
 					
 						move(30,30);
 						printw("El archivo no se puede abrir");
 					}
					else
 					{
 						fil=*fila;
						column=*columna;
						
						fread(tab,sizeof(struct s_casillas),64,f);
						fread(&esta,sizeof(struct s_estado),1,f);
						esta->cont=esta->cont-1;
						
  						while((esta->hake==0)&&(esta->salir==0))
  						{
  							pintar_tablero(tab);
 							tirar(tab, esta);
  							esta->cont=esta->cont+1;
						}
						fclose(f);
					}	
					}break;
					case 2://guardar partida
					{
  						FILE *f;
 				
  						f=fopen("partida.bin","w+b");
 						if (f==NULL)
  						{	
  					
 							move(30,30);
 							printw("El archivo no se puede abrir");
  						}
  						else
						{
 							
							
							fwrite(tab,sizeof (struct s_casillas),64,f);
 							fwrite(&esta,sizeof (struct s_estado),1,f);
  							
							
 						}
						fclose (f);
					}break;
					case 3://se sale del menu
					{
			
					};break;
					case 4://se sle del juego
					{	
						esta->salir=1;
					
				
			
					};break;
				}
	
			}
		}	
	}
	fil=*fila;// para q se kede el cursor en la utlimo movimiento
	column=*columna;// para q se kede el cursor en la utlimo movimiento
		
}

