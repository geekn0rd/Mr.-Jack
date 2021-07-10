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
// you give it row and cloumn & it prints the right thing :)
void print_by_rc(int r, int c, struct node *head, struct suspect *s, int *o, struct detective *dets) {
	if ((r == 0 && c == 0) || (r == 0 && c == 4) || (r == 4 && c == 0) || (r == 4 && c == 4)) {
		if ((r == 0 && c == 4) || (r == 4 && c == 4)) {
			printf("  	  {     }	");
		}
		else {
			printf(" {	}	");
		}
		return;
	}
	else if ((r > 0 && c > 0) && (r < 4 && c < 4)) {
		struct node *current;
		for (current = head; current != NULL; current = current->next) {
			if ((current->t.p.r == r && current->t.p.c == c)) {
				if (current->t.is_sus != 0) {
					printf(" (%14s, %c) ", s[current->t.sus_id].name, o[current->t.orien]);
				}
				else {
					printf(" (%17c) ",  o[current->t.orien]);	
				}
				return;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (dets[i].p.r == r && dets[i].p.c == c) {
			if (r == 0 || r == 4) {
				printf("	 [%s]	 ", dets[i].name);
			}
			else {
				printf(" [%s] ", dets[i].name);
			}
			return;
		}
	}
	if (r == 0 || r == 4) {
		printf("       [  ]	  ");
	}
	else{
		printf(" [	] ");
	}
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
	printf("Enter row & column of the tile you want to rotate: ");
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
	printf("1)90 degrees 2)180 degrees: ");
	scanf("%d", &d);
	if (d == 1) {
		printf("1)clockwise 2)anticlockwise: ");
		scanf("%d", &x);
		if (x == 1) {
			i->t.orien += 1;
		}
		else {
			i->t.orien -= 1;
		}
	}
	else {
		i->t.orien -= 2;
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

int determine_jack(struct node *head) {
	//srand(time(0)); niyazi nis dobare seed bedi chon cpu sarriye (to hamon saniye ast time(0)) va hamon sequence adado mide
	int jack_id = rand() % 9;
	struct node *i = head;
	for (i; i != NULL; i = i->next) {
		if (i->t.sus_id == jack_id) {
			i->t.is_sus = -1;
			return jack_id;
		}
	}
}

void joker_action(int round, struct detective *dets) {
	int r, c;
	if (round % 2 == 0) {
		printf("Enter row & column of the detective you want to move or if you don't want to move any enter 0 0: ");
		scanf("%d %d", &r, &c);
		if (r == 0 && c == 0) {
			return;
		}
	}else {
		printf("Enter row & column of the detective you want to move: ");
		scanf("%d %d", &r, &c);
	}
	for (int i = 0; i < 3; i++) {
		if (dets[i].p.r == r && dets[i].p.c == c) {
			if (c == 0) {
				dets[i].p.r -= 1;
				if ( dets[i].p.r == 0) {
					dets[i].p.c += 1;
				}
				return;
			}
			else if (c == 4) {
				dets[i].p.r += 1;
				if (dets[i].p.r == 4) {
					dets[i].p.c -= 1;
				}
				return;	
			}
			else if (r == 0) {
				dets[i].p.c += 1;
				if (dets[i].p.c == 4) {
					dets[i].p.r += 1;
				}
				return;
			}
			else {
				dets[i].p.c -= 1;
				if (dets[i].p.c == 0) {
					dets[i].p.r -= 1;
				}
				return;
			}		
		}
	}
	printf("Entered row & column are wrong!\n");
	return;
	
}

void dets_action(int det_id, struct detective *dets) {
	int i = det_id;
	int s;
	printf("1)one step 2)two steps : ");
	scanf("%d", &s);
	if (dets[i].p.c == 0) {
		if (dets[i].p.r == 1 && s == 2) {
			dets[i].p.c += 2;
			dets[i].p.r -= 1;
			return;
		}
		dets[i].p.r -= s;
		if (dets[i].p.r == 0) {
			dets[i].p.c += 1;
		}
		return;
	}
	else if (dets[i].p.c == 4) {
		if (dets[i].p.r == 4 && s == 2) {
			dets[i].p.c -= 2;
			dets[i].p.r += 1;
			return;
		}
		dets[i].p.r += s;
		if (dets[i].p.r == 4) {
			dets[i].p.c -= 1;
			}
		return;	
		}
	else if (dets[i].p.r == 0) {
		if (dets[i].p.c == 3 && s == 2) {
			dets[i].p.r += 2;
			dets[i].p.c += 1;
			return;
		}
		dets[i].p.c += s;
		if (dets[i].p.c == 4) {
			dets[i].p.r += 1;
		}
		return;
	}
	else {
		if (dets[i].p.c == 1 && s == 2) {
			dets[i].p.r -= 2;
			dets[i].p.c -= 1;
			return;
		}
		dets[i].p.c -= s;
		if (dets[i].p.c == 0) {
			dets[i].p.r -= 1;
		}
		return;
	}
}

struct place *horizontal_trace(struct place det, struct node *head, int *size) {
	int x = 0;
	struct place *p = NULL;
	if (det.c == 0) {
		int c = det.c + 1;
		int r = det.r;
		struct node *i = head;
		for (i; i != NULL; i = i->next) {
			if (i->t.p.c == c && i->t.p.r == r) {
				if (i->t.orien == 1) {
					*size = x;
					return p;
				}
				else {
					p = realloc(p, ++x * sizeof(struct place));
					p[x - 1] = i->t.p;
					c += 1;
					if (i->t.orien == 3) {
						*size = x;
						return p;
					}
					if (x == 3) {
						*size = x;
						return p;
					}
					i = head;
				}
			}
		}
	}
	else {
		int c = det.c - 1;
		int r = det.r;
		struct node *i = head;
		for (i; i != NULL; i = i->next) {
			if (i->t.p.c == c && i->t.p.r == r) {
				if (i->t.orien == 3) {
					*size = x;
					return p;
				}
				else {
					p = realloc(p, ++x * sizeof(struct place));
					p[x - 1] = i->t.p;
					c -= 1;
					if (i->t.orien == 1) {
						*size = x;
						return p;
					}
					if (x == 3) {
						*size = x;
						return p;
					}
					i = head;
				}
			}
		}
	}
}

struct place *vertical_trace(struct place det, struct node *head, int *size) {
	int x = 0;
	struct place *p = NULL;
	if (det.r == 0) {
		int c = det.c;
		int r = det.r + 1;
		struct node *i = head;
		for (i; i != NULL; i = i->next) {
			if (i->t.p.c == c && i->t.p.r == r) {
				if (i->t.orien == 2) {
					*size = x;
					return p;
				}
				else {
					p = realloc(p, ++x * sizeof(struct place));
					p[x - 1] = i->t.p;
					r += 1;
					if (i->t.orien == 0) {
						*size = x;
						return p;
					}
					if (x == 3) {
						*size = x;
						return p;
					}
					i = head;
				}
			}
		}
	}
	else {
		int c = det.c;
		int r = det.r - 1;
		struct node *i = head;
		for (i; i != NULL; i = i->next) {
			if (i->t.p.c == c && i->t.p.r == r) {
				if (i->t.orien == 0) {
					*size = x;
					return p;
				}
				else {
					p = realloc(p, ++x * sizeof(struct place));
					p[x - 1] = i->t.p;
					r -= 1;
					if (i->t.orien == 2) {
						*size = x;
						return p;
					}
					if (x == 3) {
						*size = x;
						return p;
					}
					i = head;
				}
			}
		}
	}
}



