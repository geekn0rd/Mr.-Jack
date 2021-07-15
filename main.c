#include <stdio.h>
#include "assets.h"
#include "functions.c"
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>


int main() {
	int x;
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
				"The game checks end conditons only at end of each turn.\n-For counting rows and column ignore the detectives.\n-Remember your save file's name!\n"
				"Press any key (then Enter) to return to Main Menu.\n");
				char s[10];
				scanf("%s", s);
				system("cls");
				break;	
			case 4:
				exit(0);	
		}
	}
	/*struct node *head = NULL;
	init_tiles(&head);
	int mrJack = determine_jack(head, suspects);
	print_map(turn, jack_hourglass, head, suspects, orientations, dets);
	manhunt_stage(&turn, tokens, head, suspects, &jack_hourglass, dets, orientations);
	witness_stage(dets, head, &jack_hourglass);
	check_endgame(turn, jack_hourglass, head);
	print_map(turn, jack_hourglass, head, suspects, orientations, dets);
	manhunt_stage(&turn, tokens, head, suspects, &jack_hourglass, dets, orientations);
	witness_stage(dets, head, &jack_hourglass);
	check_endgame(turn, jack_hourglass, head);
	print_map(turn, jack_hourglass, head, suspects, orientations, dets);*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
