#include <stdio.h>
#include "assets.h"
#include <stdlib.h>
#include <time.h>

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
	nn->t.p.r = i;
	nn->t.p.c = j;
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

void print_by_rc(int r, int c, struct node *head, struct suspect *s, int *o, struct detective *dets) {
	if ((r == 0 && c == 0) || (r == 0 && c == 4) || (r == 4 && c == 0) || (r == 4 && c == 4)) {
		printf(" [	] ");
		return;
	}
	else if ((r > 0 && c > 0) && (r < 4 && c < 4)) {
		struct node *current;
		for (current = head; current != NULL; current = current->next) {
			if ((current->t.p.r == r && current->t.p.c == c)) {
			printf(" [%s, %c, %4s] ", s[current->t.sus_id].name, o[current->t.orien], 
			current->t.is_sus ? "sus" : "clear");
			return;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (dets[i].p.r == r && dets[i].p.c == c) {
		printf(" [%s] ", dets[i].name);
		return;
		}
	}
	printf(" [	] ");
	return;
}


void print_tiles(struct node *head, struct suspect *s, int *o) {
	struct node *current;
	int i = 1;
	for (current = head; current != NULL; current = current->next, i++) {
		printf("[%s, %c, %4s, (%d, %d)] ", s[current->t.sus_id].name, o[current->t.orien],
		 current->t.is_sus ? "sus" : "clear", current->t.p.r, current->t.p.c);
		if (i % 3 == 0) {
			printf("\n");
		}
	}
}

void print_dets(struct detective *dets) {
	for (int i = 0; i < 3; i++) {
		printf("%s is located at (%d, %d)\n", dets[i].name, dets[i].p.r, dets[i].p.c);
	}
}

void replace_tiles(struct node *head) {
	printf("Enter row & column of the tile you want to move: ");
	int r1, r2, c1, c2;
	scanf("%d %d", &r1, &c1);
	printf("Enter row & column of the destination tile: ");
	scanf("%d %d", &r2, &c2);
	struct node *i = head;
	struct node *j = head;
	for (i; i != NULL; i = i->next) {
		if (i->t.p.r == r1 && i->t.p.c == c1) {
			for (j; j != NULL; j = j->next) {
				if (j->t.p.r == r2 && j->t.p.c == c2) {
					printf("%d %d to %d %d\n", r1, c1, r2, c2);
					i->t.p.r = r2;
					i->t.p.c = c2;
					j->t.p.r = r1;
					j->t.p.c = c1;
					return;
				}
			}
		}
	}
	printf("Entered rows & columns are wrong!\n");
	return;
}

void rotate_tile(struct node *head) {
	printf("Enter row & column of the tile you want to move: ");
	int r, c, x, d;
	scanf("%d %d", &r, &c);
	struct node *i = head;
	for (i; i != NULL; i = i->next) {
		if (i->t.p.r == r && i->t.p.c == c) {
			break;
		}
		else if (i->next == NULL) {
			printf("Entered row & column are wrong!\n");
			return;
		}
	}
	printf("1)clockwise 2)anticlockwise: ");
	scanf("%d", &x);
	printf("1)90 degrees 2)180 degrees: ");
	scanf("%d", &d);
	if (x == 1) {
		if (d == 1) {
			i->t.orien += 1;
		}
		else {
			i->t.orien += 2;
		}
	}
	else {
		if (d == 1) {
			i->t.orien -= 1;
		}
		else {
			i->t.orien -= 2;
		}
	}
	if (i->t.orien < 0) {
		i->t.orien += 4;
	}
	i->t.orien = i->t.orien % 4;
	return;
}

void print_map(struct node *head, struct suspect *susz, int *oriens, struct detective *dets) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			print_by_rc(i, j, head, susz, oriens, dets);
		}
		printf("\n");
	}
	return;
}

void init_tiles(struct node **head) {
		srand(time(0));
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				int o, id;
				if (i == 0 && j == 0) {
					o = 1;
			}
			else if (i == 0 && j == 2) {
				o = 3;
			}
			else if (i == 2 && j == 1) {
				o = 0;
			}
			else {
				o = rand() % 4;
			}
			id = rand() % 9;
			while (is_found(*head, id)) {
				id = rand() % 9;
			}
			push_back(head, id, 1, o, i + 1, j + 1); 
		}
	}
}
