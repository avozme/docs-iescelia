#include <stdio.h>
#include <stdlib.h>

#define PROVINCIAS 50
#define PARTIDOS 5
#define MAX_ESCANOS 20

int main()
{
	int votos[PROVINCIAS + 1][PARTIDOS + 1];	// Matriz de votos. No usaremos ni la fila 0 ni la columna 0, por eso asignamos uno más
	int esc[PROVINCIAS + 1][PARTIDOS + 1];		// Matriz de escaños. Tampoco usaremos la fila 0 ni la columna 0 
	int aux[MAX_ESCANOS + 1][PARTIDOS + 1];		// Matriz auxiliar para el cálculo de escaños
	int prov, part, escano, e;			// Contadores para los bucles
	int maximo, esc_max, part_max;			// Variables auxiliares para calcular los máximos
	int num_escanos;				// Número de escaños por provincia
	int totales[PARTIDOS + 1];			// Para calcular los votos totales nacionales de cada partido


	printf("Fundamentos programación 1º ASI\n");
	printf("Ejercicio del tema 3: REPARTO DE ESCAÑOS EN UNAS ELECCIONES\n");
	printf("----------------------------------------------------------\n\n");

	// Inicializamos la matriz de escaños a 0
	for (prov = 1; prov <= PROVINCIAS+1; prov++)
		for (part = 1; part <= PARTIDOS; part++)
			esc[prov][part] = 0;

	// Incializamos el vector de votos totales a 0
	for (part = 1; part <= PARTIDOS; part++)
		totales[part] = 0;

	// Asignamos aleatoriamente los votos
	for (prov = 1; prov <= PROVINCIAS; prov++)
		for (part = 1; part <= PARTIDOS; part++)
			votos[prov][part] = rand() % 1000 + 1;
			esc[prov][part] = 0;

	printf("He asignado aleatoriamente los votos. Pulsa INTRO para ver el reparto...\n");
	getchar();

	// Mostramos por pantalla el resultado de la asignación de votos
	printf(" = VOTOS =          Partido 1   Partido 2   Partido 3   Partido 4   Partido 5\n");
	printf("-----------------------------------------------------------------------------\n");
	for (prov = 1; prov <= PROVINCIAS; prov++)
	{
		printf("Provincia %2i        ", prov);
		for (part = 1; part <= PARTIDOS; part++)
		{
			printf("   %4i     ", votos[prov][part]);
		}
		printf("\n");
	}

	// Calculamos los escaños en cada provincia
	for (prov = 1; prov <= PROVINCIAS; prov++)
	{
		// Cada provincia tendrá un número de escaños variable entre 4 y MAX_ESCAÑOS
		num_escanos = rand() % (MAX_ESCANOS - 4) + 4;

		// Creamos la matriz auxiliar para la provincia "prov"
		for (part = 1; part <= PARTIDOS; part++)
		{
			for (escano = 1; escano <= num_escanos; escano++)
			{
				aux[escano][part] = votos[prov][part] / escano;
			}
		}

		// Mostramos la matriz auxiliar de cada provincia

		// Asignamos los escaños de esta provincia
		for (e = 1; e <= num_escanos; e++)
		{
			maximo = 0;		// Vamos a buscar el mayor número en la matriz "aux"
			esc_max = 0;
			part_max = 0;
			for (part = 1; part <= PARTIDOS; part++)
			{
				for (escano = 1; escano <= num_escanos; escano++)
				{
					if (aux[escano][part] > maximo)		// Hemos encontrado un nuevo máximo
					{
						maximo = aux[escano][part];	// Guardamos el nuevo máximo
						esc_max = escano;		// También guardamos su fila...
						part_max = part;		// ...y su columna
					}
				}
			}

			// El nuevo escaño corresponde al partido que haya tenido el máximo número de votos
			esc[prov][part_max] ++;		// Incrementamos en 1 el número de escaños de ese partido
			aux[esc_max][part_max] = 0;	// Ponemos a 0 la entrada en la matriz auxiliar para no volver a contar esos votos
		}
	} // for prov

	printf("\nHe calculado los escaños. Pulsa INTRO para ver el resultado...\n");
	getchar();

	// Mostramos por pantalla el resultado de la asignación de escaños
	printf(" = ESCAÑOS =        Partido 1   Partido 2   Partido 3   Partido 4   Partido 5   Total\n");
	printf("-------------------------------------------------------------------------------------\n");
	for (prov = 1; prov <= PROVINCIAS; prov++)
	{
		printf("Provincia %2i       ", prov);
		num_escanos = 0;
		for (part = 1; part <= PARTIDOS; part++)
		{
			printf("   %4i     ", esc[prov][part]);
			num_escanos = num_escanos + esc[prov][part];		// Vamos contabilizando los escaños de esta provincia
			totales[part] = totales[part] + esc[prov][part];	// También contamos los escaños totales de cada partido	
		}
		// Falta por escribir el total de escaños de esta provincia
		printf(" %4i\n", num_escanos);
	}
	// Por último, escribrimos los totales nacionales
	printf("TOTAL ESPAÑA       ");
	num_escanos = 0;
	for (part = 1; part <= PARTIDOS; part++)
	{
		printf("   %4i     ", totales[part]);
		num_escanos = num_escanos + totales[part];
	}
	printf(" %4i\n", num_escanos);

	printf("\n\n");
 
	return 0;
	
}

