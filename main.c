#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
/********************/
static unsigned int NUMBER_OF_ELEMENTS = 5;
unsigned int mat[5][5] = {
        {0, 4, 2, 5, 8},
        {4, 0, 6, 8, 7},
        {2, 6, 0, 2, 9},
        {5, 8, 2, 0, 3},
        {8, 7, 9, 3, 0}
};
struct _Solution{
    unsigned int *elementOrder;
    unsigned int cost;
}typedef Solution;

/*********************************/

unsigned int costCalcul(unsigned int* T){
    unsigned int cost = 0;
    for(int i = 0 ; i<NUMBER_OF_ELEMENTS -1 ;i++){
        cost += mat[T[i]][T[i+1]];
    }
    return cost + mat[T[NUMBER_OF_ELEMENTS - 1]][T[0]];
}

unsigned int currentDepth = -1; /** <profondeur courrant d'arbre*/
unsigned int FIRST_VERTEX_TO_VISITE = 0; /** <premier sommet visité par l'algorithm*/
bool *isVisited; // keeps tract of visited vertices
/**
 * Cette Méthode cherche le cycle hamitolien le moins coûteux
 * sol contient le cycle T et le coût
 * cost contient le coût actuel (il est calculé inversement càd depuis la feuille
 * */
Solution * costlessHamiltonCycle(unsigned int vertex){
    Solution *sol = NULL;
    unsigned int cost = 0;
    
    currentDepth++;
    isVisited[vertex] = true;

    if(currentDepth == NUMBER_OF_ELEMENTS - 1){
        //dernier element visité (la feuille d'arbre) => génerer un vecteur T
        sol = malloc(sizeof(Solution));
        sol->elementOrder = malloc(NUMBER_OF_ELEMENTS*sizeof(unsigned int));
        //Le coût entre la feuille et la racine (le premier sommet visité)
        sol->cost = mat[vertex][FIRST_VERTEX_TO_VISITE];
    }else{
        for(int i = 0; i < NUMBER_OF_ELEMENTS;i++) {
            if ((mat[vertex][i] != 0) && (!isVisited[i])) {
                //Le premier fis visité => init sol
                if(sol == NULL) {
                    sol = costlessHamiltonCycle(i);
                    sol->cost += mat[vertex][i];
                }
                //Comparer la solution trouvée avec celle d'autre fis
                else{
                    Solution* s1 = costlessHamiltonCycle(i);
                    s1-> cost += mat[vertex][i];
                    sol = (sol->cost < s1->cost)? sol:s1;
                }
            }
        }
    }
    //Marquer l'ordrer du sommet actuel (visité)
    sol->elementOrder[currentDepth] = vertex;
    //Monter d'un seul niveau (profondeur--)
    currentDepth--;
    //On suppose qu'il est non visité (il sera visité dans d'autre branche)
    isVisited[vertex] = false;
    return sol;
}
void init(){
    isVisited = calloc(NUMBER_OF_ELEMENTS, sizeof(bool));
    isVisited[FIRST_VERTEX_TO_VISITE] = true;
}
void consolePrintSolution(Solution* sol){
    printf("\n#%u\n", sol->cost);
    for (int i = 0; i < NUMBER_OF_ELEMENTS; ++i) {
        printf("|%u|", sol->elementOrder[i]);
    }
    printf("\n");
}
int main() {
//DFS
    init();
    Solution* sol = costlessHamiltonCycle(FIRST_VERTEX_TO_VISITE);
    consolePrintSolution(sol);
    return 0;
}
