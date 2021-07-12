#include <stdio.h>
#include "assets.h"
#include "functions.c"
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int turn = 1;
int jack_hourglass = 0;

int main() {
	// giving each suspect a dedicated id [0,8]
	struct suspect suspects[9] = {
		{"Insp. Lestrade", 0}, {"Jeremy Bert", 1}, {"John Pizer", 1},
		{"John Smith", 1}, {"Joseph Lane", 1}, {"Madame", 2}, 
		{"Miss Stealthy", 1}, {"Sgt Goodley", 0}, {"William Gull", 1}
	};
	struct action_token tokens[4] = {
		{0, {{"Alibi"}, {"Holmes"}}}, {0, {{"Toby"}, {"Watson"}}}, {0, {{"Rotation"}, {"Exchange"}}}, {0, {{"Rotation"}, {"Joker"}}}
	};
	// Ascii chars that look similar to the tiles [0,4]
	int orientations[4] = {193, 195, 194, 180};
	// giving each detective a dedicated id [0,3]
	struct detective dets[3] = {
		{"Holmes", {1, 0}}, {"Watson", {1, 4}}, {"Toby", {4, 2}}
	};
	struct node *head = NULL;
	init_tiles(&head);
	int mrJack = determine_jack(head, suspects); 
	print_map(head, suspects, orientations, dets);
	manhunt_stage(&turn, tokens, head, suspects, &jack_hourglass, dets, orientations);
	witness_stage(dets, head, &jack_hourglass);
	print_map(head, suspects, orientations, dets);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
