#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "electrotest.h"

float calc_resistance(int count, char conn, float *array){
	float sum = 0.0;
	if(count && conn && array){
		if(conn == 'P'){
			while(count > 0){
				count -= 1;
				sum += (1/array[count]);
			}
			return (1/sum);
		} else if(conn == 'S') {
			while(count > 0) {
				count -= 1;
				sum += array[count];
			}
			return sum;
		} else {
			printf("Error: conn can only have values S or P");
			return -1;
			}
	} else {
		printf("Error: please specify all variables: count, conn and *array");
		return -1;
		}
	
}

float calc_power_r(float volt, float resistance)
{
	if (volt && resistance)
	{
		return volt*volt/resistance;
	}
	else if (!volt)
	{
		printf("Volt can't be null, try again.");
		return 0;
	}
	else if (!resistance)
	{
		printf("Resistance can't be null, try again.");
		return 0;
	}
	else
	{
		printf("Something went wrong, try again.");
		return 0;
	}
}

int e_resistance(float orig_resistance, float *res_array)
{
    const float e12[29] = {1, 10, 12, 15, 18, 22, 27, 33, 39, 47, 56, 68, 82, 100, 
        120, 150, 180, 220, 270, 330, 390, 470, 560, 680, 820, 1000,
        1200, 1500, 1800};

    int count = 0;
    int i = 0;
    //int j = 0;
    float temp = orig_resistance;

// serching on e12-series and finding the best value
    while(i>=0&&count<3){
        //j = i; unused variable

        for(i=28; temp-e12[i]<0 && i>=0;i--);

        if(i>=0)
        {
            temp = temp-e12[i];
        // safe the value to the array
            *res_array=e12[i];
            res_array++;
            count++;
        }

    }

    return count;
}

float calc_power_i(float volt, float current)
{
	if (volt && current)
	{
		return volt*current;
	}
	else if (!volt)
	{
		printf("Volt can't be null, try again.");
		return 0;
	}
	else if (!current)
	{
		printf("Resistance can't be null, try again.");
		return 0;
	}
	else
	{
		printf("Something went wrong, try again.");
		return 0;
	}
}

int main()
{
	float resistance, volt, effect;
	int nbr_resistors, resistors_count;
	char type[]={0};
	
	printf("Enter volt: ");
	if(scanf("%f", &volt) == 1) {
		printf("%f\n", volt);
	} else {
		printf("Failed to read integer.\n");
	}
	
	printf("Serial 'S' or Paralel 'P' ?: ");
	if(scanf("%s", type) == 1) {
		printf("%s\n", type);
	} else {
		printf("Failed to read char.\n");
	}
	
	printf("Enter number of resistors: ");
	if(scanf("%d", &nbr_resistors) == 1) {
		printf("%d\n", nbr_resistors);
	} else {
		printf("Failed to read integer.\n");
	}
	resistors_count = nbr_resistors;
	
	float *resistors = (float*)malloc(nbr_resistors *sizeof(float));

	while(resistors_count > 0) {
		printf("Enter resistor: ");
		scanf("%f", &resistors[resistors_count-1]);
		resistors_count -= 1;
	}
	
	resistance = calc_resistance(nbr_resistors, type[0], resistors);
	printf("%s\n", "Replacement resistance: ");
	printf("%0.1f\n", resistance);
	
	
	effect = calc_power_r(volt, resistance);
	printf("Effect (calc_power_r): \n%0.2f W\n", effect);
	//effect = calc_power_i(volt, (volt/resistance));
	//printf("Effect (calc_power_i): \n%0.2f W\n", effect);
	
	
	printf("Replacement resistance in E12-serie: \n");
	int a = e_resistance(resistance, resistors);
	for(int i = 0; i < a; i++) {
		printf("%.1f\n", resistors[i]);
	}
	
	free(resistors);	
	
	
	return 0;
}
