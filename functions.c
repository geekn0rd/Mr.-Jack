#include <stdio.h>
#include "assets.h"
#include <stdlib.h>
#include <time.h>
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
	struct node *nn = malloc(sizeof(struct tile));
	nn->t.sus_id = id;
	nn->t.is_sus = is_sus;
	nn->t.orientation = ori;
	nn->t.position[0] = i;
	nn->t.position[1] = j;
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
