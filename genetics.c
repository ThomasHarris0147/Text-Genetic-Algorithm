#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int population = 10000;
int mutation_chance = 0.01; // between 0.01 and 1 chance
char phrase[] = "monkey";

double check(char *phrase, char *to_check){ // returns percentage of how close to original
    int to_return = 0;
    for (int i = 0; i < strlen(phrase);i ++){
        to_return = to_return + ((int)phrase[i] == (int)to_check[i]);
    }
    return (double)to_return/strlen(phrase);
}

int main() {
    // initialization
    srand(time(NULL));
    double r;
    int count = 2;
    char* random_chars = malloc(strlen(phrase)*sizeof(char));
    int i;
    double fitness;
    int iterations = 1;
    char* fittest_one = malloc(strlen(phrase)*sizeof(char));
    double fitness_of_one;
    char* fittest_two = malloc(strlen(phrase)*sizeof(char));
    double fitness_of_two = 0;
    int index;

    // find strlen(phrase) random characters
    for (i=0;i<strlen(phrase);i++){
         random_chars[i] = (rand()%94)+32; // looking at ascii values from 32 - 126
    }
    strcpy(fittest_one,random_chars); // setting first max 1
    fitness_of_one = check(phrase,random_chars);
    // find strlen(phrase) random characters
    for (i=0;i<strlen(phrase);i++){
         random_chars[i] = (rand()%94)+32; // looking at ascii values from 32 - 126
    }
    strcpy(fittest_two,random_chars); // setting first max 2
    fitness_of_two = check(phrase,random_chars);
    do{
        // find strlen(phrase) random characters
        for (i=0;i<strlen(phrase);i++){
            random_chars[i] = (rand()%94)+32; // looking at ascii values from 32 - 126
        }
        count++;
        fitness = check(phrase,random_chars); // check fitness
        // if fitness is higher
        if (fitness > fitness_of_two){
            if (fitness > fitness_of_one && !strcmp(fittest_two,random_chars)){
                strcpy(fittest_one,random_chars);
                fitness_of_one = fitness;
            } else {
                strcpy(fittest_two,random_chars);
                fitness_of_two = fitness;
            }
        }
    } while (count < population);
    // now we have the 2 best genes. we will mix them.
    char* proxy_fittest_one = malloc(strlen(phrase)*sizeof(char));
    char* proxy_fittest_two = malloc(strlen(phrase)*sizeof(char));
    do{
        strcpy(proxy_fittest_one,fittest_one);
        strcpy(proxy_fittest_two,fittest_two);
        printf("fittest one = %s, fitness of one = %f\n",proxy_fittest_one,fitness_of_one);
        printf("fittest two = %s, fitness of two = %f\n",proxy_fittest_two,fitness_of_two);
        count = 0;
        //fitness_of_one = 0;
        //fitness_of_two = 0;
        do{
            index = rand()%strlen(phrase); // we will mix them via random pivot point
            for (i = 0; i < index; i++){ // using the first fittest first
                r = (double)rand() / (double)RAND_MAX;
                if (r <= mutation_chance){ // chance to mutate
                    random_chars[i] = (rand()%94)+32; // looking at ascii values from 32 - 126
                }
                else {
                    random_chars[i] = proxy_fittest_one[i];
                }
            }
            for (i = index; i < strlen(phrase); i++){ // then the second fittest
                r = (double)rand() / (double)RAND_MAX;
                if (r <= mutation_chance){ // chance to mutate
                    random_chars[i] = (rand()%94)+32; // looking at ascii values from 32 - 126
                }
                else {
                    random_chars[i] = proxy_fittest_two[i];
                }
            }
            fitness = check(phrase,random_chars);
            count++;
            // if fitness is higher
            if (fitness > fitness_of_two && strcmp(random_chars,fittest_one) && strcmp(random_chars,fittest_two)){
                if (fitness > fitness_of_one){
                    strcpy(fittest_one,random_chars);
                    fitness_of_one = fitness;
                } else {
                    strcpy(fittest_two,random_chars);
                    fitness_of_two = fitness;
                }
            }
        }while(count<population);
        iterations++;
    }while(fitness_of_one != 1.0);
    printf("phrase: %s, iterations: %d\nclosest second: %s with a fitness of %f.\n",fittest_one,iterations,fittest_two,fitness_of_two);
    return 0;
}