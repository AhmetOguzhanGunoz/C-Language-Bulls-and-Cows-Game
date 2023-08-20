#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define guess_limit 5

typedef struct
{
	int index, guess_list[guess_limit], attemp_count, result, secret;	
}hand; //Because of intend to use atoi() function, secret and guess_list defined in same struct not as string

void bulls_cows(char arr1[],char arr2[],int size,int *bull, int *cow);
int check_alpha(char arr[], int size);
void integer_to_string(char arr1[],int arr2[],int size);
void generate_number(int arr[], int size);