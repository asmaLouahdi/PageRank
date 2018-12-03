



#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<time.h>
#include <strings.h>

#define NLINKS 50000000


long maxFinale;
typedef struct {
	unsigned long s;//source node
	unsigned long t;//target node
} edge;

typedef struct {
	unsigned long s;//source node
	unsigned long degout;//target node
}degre;

long max(long a, long b)
{
	//printf("** %lu **** %lu", a,b);
	if (a >= b)
		return a;
	else
		return b;
}


double* calcul(int iter, double a) {
	long maxinterm = 0;
	FILE *file = fopen("net.txt", "r");
	long i = 0;
	long edgepoint = NLINKS;
	maxFinale = 0;
	edge *liste = malloc(edgepoint * sizeof(edge));
	while (fscanf(file, "%lu %lu\n", &(liste[i].s), &(liste[i].t)) == 2) {

		maxinterm = max(liste[i].s, liste[i].t);

		if (maxinterm > maxFinale) {
			maxFinale = maxinterm;
		}
		i++;
	}
	maxFinale++;
	printf("nombre de noeud %lu \n", maxFinale);
	printf("nombre de edge %lu \n", i);

	fclose(file);

	unsigned long *dout = calloc(maxFinale, sizeof(unsigned long));
	unsigned long *din = calloc(maxFinale, sizeof(unsigned long));
	for (int cmpt = 0; cmpt<i; cmpt++) {
		dout[liste[cmpt].s]++;
		din[liste[cmpt].t]++;

	}

	FILE* fileout = fopen("outdegrees.txt", "w");
	FILE* filein = fopen("indegrees.txt", "w");
	//FILE* pageRank = fopen("pagerank.txt", "w");


	/****PRODUIT MATRICIELLE****/
	double *p1, *p2, *p3;
	double s;
	long j;
	p1 = malloc(maxFinale * sizeof(double));
	for (j = 0; j<maxFinale; j++) {//initialisation

		p1[j] = 1. / (double)maxFinale;

	}
	p2 = malloc(maxFinale * sizeof(double));
	for (long t = 0; t < iter; t++)
	{
		/********/
		for (j = 0; j < maxFinale; j++) {
			p2[j] = 0;

		}
		for (long k = 0; k<i; k++) {
			if (dout[liste[k].s]>0) {
				p2[liste[k].t] += p1[liste[k].s] / ((double)(dout[liste[k].s]));
			}
		}
		/******/

		s = 0.;//to normalize
		for (j = 0; j<maxFinale; j++) {
			p2[j] = p2[j] * (1. - a) + a / ((double)maxFinale);
			s += p2[j];

		}

		s = (double)((1 - s) / ((double)maxFinale));

		for (j = 0; j<maxFinale; j++) {
			p2[j] += s;

		}

		p3 = p2, p2 = p1, p1 = p3;



	}


	free(p2);

	/****fichier dout et din et pageRank****/

	for (int f = 0; f<maxFinale; f++) {
		if (dout[f] != 0) {
			fprintf(fileout, "%lu %lu\n", f, dout[f]);
		}
		if (din[f] != 0) {
			fprintf(filein, "%lu %lu\n", f, din[f]);
		}
		
	if ((din[f] != 0) || (dout[f] != 0)) {
			fprintf(pageRank, " %lu % 10le\n", f, p1[f]);

		}

	}

	fclose(fileout);
	fclose(filein);
	fclose(pageRank);


	return p1;


	/***************************/



}



int main(int argc, char** argv) {
	time_t t1, t2;

	t1 = time(NULL);

	double *p1 = calcul(20, 0.15);
	t2=time(NULL);
	printf("- Overall time = %ldh%ldm%lds\n", (t2 - t1) / 3600, ((t2 - t1) % 3600) / 60, ((t2 - t1) % 60));


	/******affichage des 5 premiers et 5 dernier******/
/*
	long *maxi = malloc(5 * sizeof(long));

	int max;
	int tmp;
	int f = 0;
	for (int j = 0; j < 5; j++) {
		tmp = max;

		max = 0;
		for (f = 0; f < maxFinale; f++)
		{
			if (j > 0) {
				if ((p1[max] < p1[f]) && (p1[f] < p1[tmp])) {
					max = f;

				}
			}
			else {
				if (p1[max] < p1[f]) {
					max = f;

				}
			}
		}
		maxi[j] = max;
	}

	printf("**** les 5 premiers pageRank *****\n");

	for (int j = 0; j < 5; j++)
		printf(" le %lu noeud son pageRank %10le \n", maxi[j], p1[maxi[j]]);

	long *mini = malloc(5 * sizeof(long));

	int min = 0;

	for (int j = 0; j < 5; j++) {
		tmp = min;

		min = maxi[0];
		for (f = 0; f < maxFinale; f++)
		{
			if (j > 0) {
				if ((p1[min] > p1[f]) && (p1[f] > p1[tmp])) {
					min = f;

				}
			}
			else {
				if (p1[min] > p1[f]) {
					min = f;

				}
			}
		}
		mini[j] = min;
	}
	printf("**** les 5 derniers pageRank ****\n");

	for (int j = 0; j < 5; j++)
		printf(" le %lu noeud son pageRank %10le \n", mini[j], p1[mini[j]]);
		*/
	return 0;
}

