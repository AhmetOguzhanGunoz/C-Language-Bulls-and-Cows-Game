#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "game.h"

int main()
{
	FILE *fp;
	char *secret_number_S, guess[11], *choice, digit_counter[2];
	int *secret_number_I, digit_count = 0, i, j, index = 0, attempt = 0, bulls = 0, cows = 0, limit = 0;

	choice = (char *)malloc(3*sizeof(char) + 1);

	if (choice == NULL)
	{
		printf("Malloc failed. Try to open program again.\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
	else
	{
		strcpy(choice, "yes");

		fp = fopen("history.txt", "w");

		if ((fp = fopen("history.txt", "w")) == NULL)
		{
			printf("Can`t open %s\n", "history.txt");
			system("pause");
			exit(1);
		}

		printf("***Welcome to The Bulls & Cows Game***\n");

		while ((strcmp(choice, "yes")) == 0 || (strcmp(choice, "y")) == 0)
		{
			hand object;
			printf("Enter the digit count that you desire(max 10,first 2 left digit):");
			scanf(" %s", &digit_counter);

			limit = 0; // Updating those values for next game.
			attempt = 0;

			if (strlen(digit_counter) > 2) //Input Check
			{
				printf("You entered more than 10 digit. Program will exit.\n");
				system("pause");
				exit(EXIT_FAILURE);
			}
			if (digit_counter[0] == '0') //Input Check
			{
				printf("You entered first digit as 0. Program will exit.\n");
				system("pause");
				exit(EXIT_FAILURE);
			}

			for (int c = 0; c < 2;c++)//Input Check
			{
				if (!isdigit(digit_counter[c]) && digit_counter[c] != '\0')
				{
					printf("You entered non digit character. Program will exit.\n");
					system("pause");
					exit(EXIT_FAILURE);
				}
			}

			if (digit_counter[1] != '0' && digit_counter[1] != '\0')//Input Check
			{
				printf("You entered more than 10 digit. Program will exit.\n");
				system("pause");
				exit(EXIT_FAILURE);
			}

			digit_count = atoi(&digit_counter);

			secret_number_S = (char*)malloc((digit_count * sizeof(char)) + 1); //Dynamically allocation is easier and faster.
			secret_number_I = (int*)malloc(digit_count * sizeof(int));

			if (secret_number_S == NULL)
			{
				printf("Something went wrong_1\n");
				system("pause");
				exit(EXIT_FAILURE);
			}

			if (secret_number_I == NULL)
			{
				printf("Something went wrong_2\n");
				system("pause");
				exit(EXIT_FAILURE);
			}

			generate_number(secret_number_I, digit_count);  // Create number whose digits are different each other

			integer_to_string(secret_number_S, secret_number_I, digit_count); // Convert number to a string form

			free(secret_number_I); // Do not need it anymore
			object.secret = atoi(secret_number_S);    // Get the full number without array by the help of atoi() function
			++index;
			object.index = index;

			printf("Ok, I have chosen a number.\n");

			while (limit < guess_limit)
			{
			start:

				printf("Enter your guess(Guess limit is 5, write quit for exiting game): ");
				scanf(" %s", guess);
				if (strcmp(guess, "quit") == 0)
				{
					object.attemp_count = attempt;
					printf("You lose!\n"); 
					object.result = 0; 
					free(secret_number_S); 
					break;
				}
				else if (strlen(guess) != digit_count)
				{
					printf("Guess must have lenght of %d, try again\n", digit_count); 
					goto start;
				}
				else if (strcmp(guess, secret_number_S) == 0)
				{
					++attempt;
					object.guess_list[limit] = atoi(guess);
					object.attemp_count = attempt;
					printf("You win!\n"); 
					object.result = 1; 
					free(secret_number_S); 
					break;
				}
				else if (check_alpha(guess, digit_count))
				{
					printf("Contains non-numbers, try again\n");
					goto start;
				}
				else
				{
					++attempt;					
					object.guess_list[limit] = atoi(guess);
					object.attemp_count = attempt;
					++limit;
					bulls_cows(guess, secret_number_S, digit_count, &bulls, &cows);
					printf("Bulls:%d Cows:%d \n", bulls, cows);
					cows = 0;
					bulls = 0;
					if (limit == 5)
					{
						printf("You lose!\n"); 
						printf("Number was: %d\n", object.secret); 
						object.result = 0; 
						free(secret_number_S); 
						break;
					}

				}
			}

			fprintf(fp, "Secret Number: %d - Guess List: ", object.secret);
			
			for (i = 0; i < object.attemp_count; i++)
			{
				fprintf(fp, "%d ", object.guess_list[i]);
			}

			if (object.attemp_count == 0)
			{
				fprintf(fp, "%s ", "empty then Quit");
			}
			else if (strcmp(guess, "quit") == 0)
			{
				fprintf(fp, "%s ", "then Quit");
			}

			fprintf(fp, "Attempt Count: %d  ", object.attemp_count);

			if (object.result)
			{
				fprintf(fp, "Result: %s \n", "Win");
			}
			else
			{
				fprintf(fp, "Result: %s \n", "Lose");
			}		

			printf("Do you want to play again (yes/no): ");
			scanf(" %s", choice);

			
		}
		free(choice);

		fclose(fp);
		
		return 0;
	}

	
}
		


	
	


	


	