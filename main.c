#include <stdio.h>
#include "assets.h"
#include "functions.c"
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

int main() {
	// giving each suspect a dedicated id [0,8]
	struct suspect suspects[9] = {
		{"Insp. Lestrade", 0}, {"Jeremy Bert", 1}, {"John Pizer", 1},
		{"John Smith", 1}, {"Joseph Lane", 1}, {"Madame", 2}, 
		{"Miss Stealthy", 1}, {"Sgt Goodley", 0}, {"William Gull", 1}
	};
	// Ascii chars that look similar to the tiles
	int ori[4] = {193, 195, 194, 180};
	struct node *head = NULL;
	
	srand(time(0));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i > 0 && j > 0 && i < 4 && j < 4) {
			int n = rand() % 4;
			printf(" %c, clear %c ", ori[n], 179);
			}
			else {
				printf("   0 ");
			}
		
		}
		printf("\n======================\n");
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
