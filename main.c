#include <stdio.h>
#include "assets.h"
#include "functions.c"
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>


int main() {
	int x;
	printf("Welcome to Mr. Jack Simple Editon;)\n\n");
	while (1) {
		printf("Main Menu:\n1)Start New Game\n2)Load Game\n3)FYI\n4)Exit\n");
		scanf("%d", &x);
		switch (x) {
			case 1 :
				start_new_game();
				break;
			case 2 :
				load_game();
				break;
			case 3 :
				printf("-Any unexpected input may break the game.\n-"
				"The game checks end conditons only at end of each turn.\n-For counting rows and columns ignore the detectives.\n-Remember your save file's name!\n"
				"Press any key (then Enter) to return to Main Menu.\n");
				char s[10];
				scanf("%s", s);
				system("cls");
				break;	
			case 4:
				exit(0);	
		}
	}

		
		
	return 0;
}
