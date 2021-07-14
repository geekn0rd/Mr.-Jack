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
