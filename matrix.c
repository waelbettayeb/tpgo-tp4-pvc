//
// Created by wael on 05/11/18.
//
/********************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
bool *visited; // keeps tract of visited vertices

static unsigned int NUMBER_OF_ELEMENTS = 5;

unsigned int mat[5][5] = {
        {0, 4, 2, 5, 8},
        {4, 0, 6, 8, 7},
        {2, 6, 0, 2, 9},
        {5, 8, 2, 0, 3},
        {8, 7, 9, 3, 0}
};



/*********************************
 * Using matrix / swaping
 */
unsigned int minCost = 0;
unsigned int* cycle;

void swap(unsigned int*a, unsigned int*b){
    unsigned int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
unsigned int costCalcul(unsigned int* a){
    unsigned int cost = 0;
    for(int i = 0 ; i<NUMBER_OF_ELEMENTS -1 ;i++){
        cost += mat[a[i]][a[i+1]];
    }
    return cost + mat[a[NUMBER_OF_ELEMENTS - 1]][a[0]];
}

void permutations(unsigned int *a, int l, int r) {
    int i;
    unsigned int newCost;

    if (l == r){
        newCost = costCalcul(a);
        if(minCost>newCost){
            minCost = newCost;//min
            //clone vector
            for(int j; j<NUMBER_OF_ELEMENTS;j++){
                cycle[j] = a[j];
            }
        }
    }
    else
    {
        for (i = l; i <= r; i++)
        {
            swap((a+l), (a+i));
            permutations(a, l+1, r);
            swap((a+l), (a+i));
        }
    }
}
int main() {
    unsigned int a[] = {0, 1, 2, 3, 4};
    minCost = costCalcul(a);
    cycle = malloc(NUMBER_OF_ELEMENTS* sizeof(unsigned int));

    //clone vector
    for(int j; j<NUMBER_OF_ELEMENTS;j++){
        cycle[j] = a[j];
    }

    permutations(a, 1, NUMBER_OF_ELEMENTS -1);
    //printing
    for(int k = 0; k<NUMBER_OF_ELEMENTS;k++){
        printf("%u ", cycle[k]);
    }
    printf("#%u \n", costCalcul(cycle));
return 0;
}