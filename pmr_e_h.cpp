/*******************************************************************************
 * MC658 - Projeto e Análise de Algoritmos III - 1s2018
 * Prof: Flavio Keidi Miyazawa
 * PED: Francisco Jhonatas Melo da Silva
 * Usa ideias e código de Mauro Mulati e Flávio Keidi Miyazawa 
 ******************************************************************************/

/*******************************************************************************
 * EDITE ESTE ARQUIVO APENAS ONDE INDICADO
 * DIGITE SEU RA: 145979
 * SUBMETA SOMENTE ESTE ARQUIVO
 ******************************************************************************/

#include <iostream>
#include <float.h>
#include "pmr_e_h.h"

typedef struct ProblemParameters {
    int capacity;
    unsigned int itemsQuantity;
    matriz relations;
} ProblemParameters;

typedef struct Item {
    int index;
    int value;
    int weight;
    double priority;
    double valuePerWeight;
    double valueRelations;

    Item(int index, int value, int weight, int priority) : index(index), value(value),
                                                           weight(weight),  priority(priority) {
        valuePerWeight = 0;
        valueRelations = 0;
    }

    bool operator<(const Item &itemB) const {
        return (priority < itemB.priority);
    }

} Item;

clock_t clockBefore;
ProblemParameters problemParameters;
vector<Item> items;

void initializeProblemParameters(int capacity, int quantItens, matriz &relation) {
    problemParameters.capacity = capacity;
    problemParameters.itemsQuantity = static_cast<unsigned int>(quantItens);
    problemParameters.relations = relation;
}

void initializeItemsBacktracking(vector<int> &v, vector<int> &s) {

    for (int i = 0; i < problemParameters.itemsQuantity; i++) {
        //set priority with weight value for performance reasons
        items.emplace_back(i, v[i], s[i], s[i]);
    }
}

bool timeIsOver(int maxTime) {

    if (maxTime == 0) {
        return false;
    }

    clock_t clockAfter = clock();
    double elapsedTime = (double) (clockAfter - clockBefore) / CLOCKS_PER_SEC;

    return elapsedTime > maxTime;
}

void updateBestSolutionItems(vector<int> &currentItems, vector<int> &bestItems) {
    for (int i = 0; i < problemParameters.itemsQuantity; i++) {
        bestItems[i] = currentItems[i];
    }
}

int calculateTotalItemValue(int index, vector<int> &currentItems) {
    int relationsValue = 0;

    for (int i = 0; i < index; i++) {
        relationsValue += problemParameters.relations[index][i] * currentItems[i];
    }

    return items[index].value + relationsValue;
}

void backtracking(int i, int currentValue, int currentWeight, vector<int> &currentItems,
                  int *bestValue, vector<int> &bestKnapsackItems, int maxTime) {

    if (timeIsOver(maxTime)) {
        cout << "Time is over" << endl;
        return;
    }

    if (i == problemParameters.itemsQuantity || (currentWeight + items[i].weight) > problemParameters.capacity) {
        if (currentValue > (*bestValue)) {
            (*bestValue) = currentValue;
            updateBestSolutionItems(currentItems, bestKnapsackItems);
        }
    } else {
        //add current item into knapsack
        currentItems[i] = 1;
        int totalItemValue = calculateTotalItemValue(i, currentItems);

        backtracking(i + 1, currentValue + totalItemValue, currentWeight + items[i].weight, currentItems,
                     bestValue, bestKnapsackItems, maxTime);

        //remove current item from knapsack
        currentItems[i] = 0;
        backtracking(i + 1, currentValue, currentWeight, currentItems,
                     bestValue, bestKnapsackItems, maxTime);
    }
}

int algE(int capacity, int quantItens, vector<int> s, vector<int> v, matriz &relation, vector<int> &itensMochila,
         int maxTime) {

    clockBefore = clock();

    initializeProblemParameters(capacity, quantItens, relation);
    initializeItemsBacktracking(v, s);

    vector<int> currentKnapsackItems(problemParameters.itemsQuantity, 0);

    int bestValue = -10000;

    //Sorting by priority
    std::sort(items.begin(), items.end());

    backtracking(0, 0, 0, currentKnapsackItems, &bestValue, itensMochila, maxTime);

    return bestValue;
}

int algH(int capacity, int quantItens, vector<int> s, vector<int> v, matriz &relation, vector<int> &itensMochila,
         int maxTime) {
    return 0;
}


