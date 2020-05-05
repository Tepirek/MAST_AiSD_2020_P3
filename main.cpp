#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include "GeneralTree.h"
#include "HashMap.h"

int main(void) {
    int numberOfTrees = 0;
    scanf_s("%d ", &numberOfTrees);
    GeneralTree** trees = new GeneralTree * [numberOfTrees];
    for (int i = 0; i < numberOfTrees; i++) {
        GeneralTree* gt = new GeneralTree();
		gt->getInput();
    	if(i < numberOfTrees - 1) {
            char c; while ((c = getchar()) != '\n');
    	}
        gt->parseInput();
        gt->assignChildren();
        trees[i] = gt;
    }
    for (int i = 0; i < numberOfTrees; i++) {
        for (int j = i; j < numberOfTrees; j++) {
            if (i == j) continue;
            HashMap* h = new HashMap(trees[i], trees[j]);
            h->handleLeaves();
            h->handleInnerNodes();
			printf("%hd\n", h->getSolution());
        }
    }
    delete[] trees;
    _CrtDumpMemoryLeaks();
    return 0;
}

/*

Input:
2
(4,(8,1,(5,3)),(9,2,(10,(7,6))));
(10,(8,(9,(5,4)),(6,2,3)),(7,1));
Output:
6

Input:
4
(1,5,(10,6,3),(2,(8,7)),(9,4));
((7,(3,(4,9,(1,2)))),8,(5,(10,6)));
(7,((6,(9,5),(8,3)),(1,(2,10,4))));
(7,(8,3,4,6,1),(9,5,10),2);
Output:
5
7
6
6
6
6

*/