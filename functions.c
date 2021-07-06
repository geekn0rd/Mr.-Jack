#include <stdio.h>
#include "assets.h"
#include <stdlib.h>

int is_found(struct node *head, int id) {
	struct node *current;
	for (current = head; current != NULL; current = current->next) {
		if (current->t.sus_id == id) {
			return 1;
		}
	}
	return 0;
}

void push_back(struct node **head, int id, int is_sus, int ori, int i, int j) {
	struct node *nn = malloc(sizeof(struct node));
	nn->t.sus_id = id;
	nn->t.is_sus = is_sus;
	nn->t.orien = ori;
	nn->t.r.x = i;
	nn->t.r.y = j;
	nn->next = NULL;
	if (*head == NULL) {
		*head = nn;
		return;
	}
	struct node *current;
	for (current = *head; current->next != NULL; current = current->next);
	current->next = nn;
	return; 
}

void print_by_xy(int x, int y, struct node *head, struct suspect *s, int *o, struct detective *dets) {
	if ((x == 0 && y == 0) || (x == 0 && y == 4) || (x == 4 && y == 0) || (x == 4 && y == 4)) {
		printf("0 ");
		return;
	}
	else if ((x > 0 && y > 0) && (x < 4 && y < 4)) {
		struct node *current;
		for (current = head; current != NULL; current = current->next) {
			if ((current->t.r.x == x && current->t.r.y == y)) {
			printf("[%s, %c, %4s] ", s[current->t.sus_id].name, o[current->t.orien], 
			current->t.is_sus ? "sus" : "clear", current->t.r.x, current->t.r.y);
			return;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (dets[i].r.x == x && dets[i].r.y == y) {
		printf("[%s] ", dets[i].name, dets[i].r.x, dets[i].r.y);
		return;
		}
	}
	printf("%c ", 219);
	return;
}


void print_tiles(struct node *head, struct suspect *s, int *o) {
	struct node *current;
	int i = 1;
	for (current = head; current != NULL; current = current->next, i++) {
		printf("[%s, %c, %4s, (%d, %d)] ", s[current->t.sus_id].name, o[current->t.orien],
		 current->t.is_sus ? "sus" : "clear", current->t.r.x, current->t.r.y);
		if (i % 3 == 0) {
			printf("\n");
		}
	}
}

void print_dets(struct detective *dets) {
	for (int i = 0; i < 3; i++) {
		printf("%s is located at (%d, %d)\n", dets[i].name, dets[i].r.x, dets[i].r.y);
	}
}
