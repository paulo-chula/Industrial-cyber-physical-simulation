#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<limits.h>
#include<gsl/gsl_randist.h>


/*
	Systems

		5 tasks

	Execution times

		1 1 2 2 3

	Periods

		2 2 3 2 1
*/
int tasks[5]   = {10,10,20,20,30};
int periods[5] = {4,4,6,4,2};


int comp_task_e[10];
int comp_task_p[10];


double lambda;


double calc_lambda(int n)
{
	//smallest execution time * highest period
	int p = 0;
	int e = 1000;

	int i;

	for(i=0;i<n;i++)
	{
		if(comp_task_e[i] < e)
			e = comp_task_e[i];
		if(comp_task_p[i] > p)
			p = comp_task_p[i];
	}

	return 0.1 * p * e * n;
}


int main()
{
	/*
	//10 scenarios, where number of systems is scenario number


		Per scenario
			Set up N systems with tasks

			Draw random period and execution time for comp tasks (1 per system)

			Calculate sum total execution time

			Report
	*/

	int i;
	int j;

	//allocates a random number generator "execution", used for gaussian execution time generation
	gsl_rng * execution = gsl_rng_alloc (gsl_rng_taus);

	//allocates a random number generator "period", used for gaussian period generation
	gsl_rng * period = gsl_rng_alloc (gsl_rng_taus);

	//allocates a random number generator "seed", used for uniform seed generation for the other RNGs
	gsl_rng * seed = gsl_rng_alloc (gsl_rng_taus);

	//seeds the random number generator
	gsl_rng_set(seed, time(NULL));



	const double mean = 5.0;
	const double variance = 1.0;


	printf("n1\tn2\tn3\tn4\tn5\tn6\tn7\tn8\tn9\tn10\n");

	for(j=0;j<100;j++)
	{
			
		for(i=0;i<10;i++)
		{
		
		
			//seeds the random number generator
			gsl_rng_set(execution, gsl_rng_uniform_int(seed, INT_MAX));
			//seeds the random number generator
			gsl_rng_set(period, gsl_rng_uniform_int(seed, INT_MAX));

			int n;

			for(n=0; n<=i; n++)
			{
				//generates comp task e and p
				comp_task_e[n] = (int)gsl_ran_gaussian(execution, variance) + mean;

				if(comp_task_e[n] < 1)
					comp_task_e[n] = 1;
				if(comp_task_e[n] > 10)
					comp_task_e[n] = 10;

				comp_task_p[n] = (int)gsl_ran_gaussian(period, variance) + mean;

				if(comp_task_p[n] < 1)
					comp_task_p[n] = 1;
				if(comp_task_p[n] > 6)
					comp_task_p[n] = 6;
			}

			//calculate lambda
			lambda = calc_lambda(n);

			double sum = 0.0;
			//results
			for(n=0; n<=i; n++)
			{
				sum += (comp_task_e[n] * comp_task_p[n]);
				sum += lambda;
			}

			printf("%f",sum);
			if(i < 9)
				printf("\t");
		}
		printf("\n");
	}

	return 0;
}