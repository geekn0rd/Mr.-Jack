#include <stdio.h>
#include "assets.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

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
			printf("  	         	");
		}
		else {
			printf("  	 	");
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
				printf("    [%6s]	  ", dets[i].name);
			}
			else {
				printf(" [%6s] ", dets[i].name);
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

void exchange_action(struct node *head) {
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
					//printf("moved %d %d to %d %d\n", r1, c1, r2, c2);
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

void rotation_action(struct node *head) {
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
	printf("\n");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			print_by_rc(i, j, head, susz, oriens, dets);
		}
		printf("\n");
	}
	printf("\n");
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

int determine_jack(struct node *head, struct suspect *s) {
	//srand(time(0)); niyazi nis dobare seed bedi chon cpu sarriye (to hamon saniye ast time(0)) va hamon sequence adado mide
	printf("Mr. Jack's identity will be determined (Investigator must close his/her eyes): \n");
	Sleep(3000);
	int jack_id = rand() % 9;
	printf("Mr. Jack is %s.\n(this will be cleared from console in 5 seconds)\n", s[jack_id].name);
	Sleep(5000);
	system("cls");
	struct node *i = head;
	for (i; i != NULL; i = i->next) {
		if (i->t.sus_id == jack_id) {
			i->t.is_sus = -1;
			return jack_id;
		}
	}
}

void alibi_action(struct node *head, struct suspect *s, int who, int *score) {
	int id = rand() % 9;
	struct node *i = head;
	for (i; i != NULL; i = i->next) {
		if (i->t.sus_id == id) {
			if (i->t.is_sus == 1) {
				i->t.is_sus = 0;
				if (who == -1) {
					*score += s[id].hourglass;
					printf("Mr. Jack gained %d hourglass.\n", s[id].hourglass);
				}
				printf("%s is cleared from suspects.\n", s[id].name);
				return;
			}
			i = head;
			id = rand() % 9;
		}
	}
}

void joker_action(int who, struct detective *dets) {
	int x;
	if (who == -1) {
		printf("Choose one of the detectives or if you don't want to move any enter 0: \n");
	}else {
		printf("Choose one of the detectives: \n");
	}
	printf("1)Holmes 2)Watson 3)Toby ");
	scanf("%d", &x);
	if (x == 0) {
		return;
	}
	int i = x - 1;
	int r = dets[i].p.r;
	int c = dets[i].p.c;
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
	printf("Entered something wrong!\n");
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

void manhunt_stage(int *turn, struct action_token *t, struct node *head, struct suspect *s, int *score, struct detective *dets, int *o) {
	if (*turn % 2 != 0) {
		srand(time(NULL));
		for (int i = 0; i < 4; i++) {
			t[i].side = rand() % 2;
		}
		int a, b, c;
		int x;
		printf("Investigator should select one of these action tokens: \n");
		for (int i = 0; i < 4; i++) {
			printf("%d)%s ", i + 1, t[i].name[t[i].side]);
			if (i == 3) {
				printf("\n");
			}
		}
		scanf("%d", &x);
		a = x - 1;
		switch (x) {
			case(1) :
				if (t[0].side == 0) {
					alibi_action(head, s, 1, score);
				}
				else {
					dets_action(0, dets);
				}
				break;
			case(2) :
				if (t[1].side == 0) {
					dets_action(2, dets);
				}
				else {
					dets_action(1, dets);
				}
				break;
			case(3) :
				if (t[2].side == 0) {
					rotation_action(head);
				}
				else {
					exchange_action(head);
				}
				break;
			case(4) :
				if (t[3].side == 0) {
					rotation_action(head);
				}
				else {
					joker_action(1, dets);
				}
				break;
			default :
				printf("wrong button selected!\n Game Aborted.\n");
				exit(-1);										
		}
		Sleep(2500);
		system("cls");
		print_map(head, s, o, dets);
		printf("Mr. Jack should select one of these action tokens: \n");
		for (int i = 0; i < 4; i++) {
			if (i == a) {		
				continue;
			}
			printf("%d)%s ", i + 1, t[i].name[t[i].side]);
			if (i == 3) {
				printf("\n");
			}
		}
		scanf("%d", &x);
		b = x - 1;
		switch (x) {
			case(1) :
				if (t[0].side == 0) {
					alibi_action(head, s, -1, score);
				}
				else {
					dets_action(0, dets);
				}
				break;
			case(2) :
				if (t[1].side == 0) {
					dets_action(2, dets);
				}
				else {
					dets_action(1, dets);
				}
				break;
			case(3) :
				if (t[2].side == 0) {
					rotation_action(head);
				}
				else {
					exchange_action(head);
				}
				break;
			case(4) :
				if (t[3].side == 0) {
					rotation_action(head);
				}
				else {
					joker_action(-1, dets);
				}
				break;
			default :
				printf("Wrong button selected!\n Game Aborted.\n");
				exit(-1);										
		}
		Sleep(2500);
		system("cls");
		print_map(head, s, o, dets);
		printf("Mr. Jack should select one of these action tokens: \n");
		for (int i = 0; i < 4; i++) {
			if (i == a || i == b) {		
				continue;
			}
			printf("%d)%s ", i + 1, t[i].name[t[i].side]);
			if (i == 3) {
				printf("\n");
			}
		}
		scanf("%d", &x);
		c = x - 1;
		switch (x) {
			case(1) :
				if (t[0].side == 0) {
					alibi_action(head, s, -1, score);
				}
				else {
					dets_action(0, dets);
				}
				break;
			case(2) :
				if (t[1].side == 0) {
					dets_action(2, dets);
				}
				else {
					dets_action(1, dets);
				}
				break;
			case(3) :
				if (t[2].side == 0) {
					rotation_action(head);
				}
				else {
					exchange_action(head);
				}
				break;
			case(4) :
				if (t[3].side == 0) {
					rotation_action(head);
				}
				else {
					joker_action(-1, dets);
				}
				break;
			default :
				printf("Wrong button selected!\n Game Aborted.\n");
				exit(-1);										
		}
		Sleep(2500);
		system("cls");
		print_map(head, s, o, dets);
		for (int i = 0; i < 4; i++) {
			if (i == a || i == b || i == c) {		
				continue;
			}
			printf("Investigator has only one choice %s:\n", t[i].name[t[i].side]);
			x = i + 1;
		}
		switch (x) {
			case(1) :
				if (t[0].side == 0) {
					alibi_action(head, s, -1, score);
				}
				else {
					dets_action(0, dets);
				}
				break;
			case(2) :
				if (t[1].side == 0) {
					dets_action(2, dets);
				}
				else {
					dets_action(1, dets);
				}
				break;
			case(3) :
				if (t[2].side == 0) {
					rotation_action(head);
				}
				else {
					exchange_action(head);
				}
				break;
			case(4) :
				if (t[3].side == 0) {
					rotation_action(head);
				}
				else {
					joker_action(1, dets);
				}
				break;
			default :
				printf("Wrong button selected!\n Game Aborted.\n");
				exit(-1);										
		}
		Sleep(2500);
		system("cls");
		print_map(head, s, o, dets);
		*turn += 1;
		return;	
	}
	else {
		for (int i = 0; i < 4; i++) {
			t[i].side += 1;
			t[i].side %= 2;
		}
		int a, b, c;
		int x;
		printf("Mr. Jack should select one of these action tokens: \n");
		for (int i = 0; i < 4; i++) {
			printf("%d)%s ", i + 1, t[i].name[t[i].side]);
			if (i == 3) {
				printf("\n");
			}
		}
		scanf("%d", &x);
		a = x - 1;
		switch (x) {
			case(1) :
				if (t[0].side == 0) {
					alibi_action(head, s, -1, score);
				}
				else {
					dets_action(0, dets);
				}
				break;
			case(2) :
				if (t[1].side == 0) {
					dets_action(2, dets);
				}
				else {
					dets_action(1, dets);
				}
				break;
			case(3) :
				if (t[2].side == 0) {
					rotation_action(head);
				}
				else {
					exchange_action(head);
				}
				break;
			case(4) :
				if (t[3].side == 0) {
					rotation_action(head);
				}
				else {
					joker_action(-1, dets);
				}
				break;
			default :
				printf("wrong button selected!\n Game Aborted.\n");
				exit(-1);										
		}
		Sleep(2500);
		system("cls");
		print_map(head, s, o, dets);
		printf("Investigator should select one of these action tokens: \n");
		for (int i = 0; i < 4; i++) {
			if (i == a) {		
				continue;
			}
			printf("%d)%s ", i + 1, t[i].name[t[i].side]);
			if (i == 3) {
				printf("\n");
			}
		}
		scanf("%d", &x);
		b = x - 1;
		switch (x) {
			case(1) :
				if (t[0].side == 0) {
					alibi_action(head, s, 1, score);
				}
				else {
					dets_action(0, dets);
				}
				break;
			case(2) :
				if (t[1].side == 0) {
					dets_action(2, dets);
				}
				else {
					dets_action(1, dets);
				}
				break;
			case(3) :
				if (t[2].side == 0) {
					rotation_action(head);
				}
				else {
					exchange_action(head);
				}
				break;
			case(4) :
				if (t[3].side == 0) {
					rotation_action(head);
				}
				else {
					joker_action(1, dets);
				}
				break;
			default :
				printf("Wrong button selected!\n Game Aborted.\n");
				exit(-1);										
		}
		Sleep(2500);
		system("cls");
		print_map(head, s, o, dets);
		printf("Investigator should select one of these action tokens: \n");
		for (int i = 0; i < 4; i++) {
			if (i == a || i == b) {		
				continue;
			}
			printf("%d)%s ", i + 1, t[i].name[t[i].side]);
			if (i == 3) {
				printf("\n");
			}
		}
		scanf("%d", &x);
		c = x - 1;
		switch (x) {
			case(1) :
				if (t[0].side == 0) {
					alibi_action(head, s, 1, score);
				}
				else {
					dets_action(0, dets);
				}
				break;
			case(2) :
				if (t[1].side == 0) {
					dets_action(2, dets);
				}
				else {
					dets_action(1, dets);
				}
				break;
			case(3) :
				if (t[2].side == 0) {
					rotation_action(head);
				}
				else {
					exchange_action(head);
				}
				break;
			case(4) :
				if (t[3].side == 0) {
					rotation_action(head);
				}
				else {
					joker_action(1, dets);
				}
				break;
			default :
				printf("Wrong button selected!\n Game Aborted.\n");
				exit(-1);										
		}
		Sleep(2500);
		system("cls");
		print_map(head, s, o, dets);
		for (int i = 0; i < 4; i++) {
			if (i == a || i == b || i == c) {		
				continue;
			}
			printf("Mr. Jack has only one choice %s:\n", t[i].name[t[i].side]);
			x = i + 1;
		}
		switch (x) {
			case(1) :
				if (t[0].side == 0) {
					alibi_action(head, s, -1, score);
				}
				else {
					dets_action(0, dets);
				}
				break;
			case(2) :
				if (t[1].side == 0) {
					dets_action(2, dets);
				}
				else {
					dets_action(1, dets);
				}
				break;
			case(3) :
				if (t[2].side == 0) {
					rotation_action(head);
				}
				else {
					exchange_action(head);
				}
				break;
			case(4) :
				if (t[3].side == 0) {
					rotation_action(head);
				}
				else {
					joker_action(-1, dets);
				}
				break;
			default :
				printf("Wrong button selected!\n Game Aborted.\n");
				exit(-1);										
		}	
	}
	Sleep(2500);
	system("cls");
	print_map(head, s, o, dets);
	*turn += 1;
	return;
}

void witness_stage(struct detective *dets, struct node *head, int *score) {
	struct place **p = calloc(3, sizeof(struct place *));
	int size[3] = {0};
	for (int i = 0; i < 3; i++) {
		if (dets[i].p.c == 0 || dets[i].p.c == 4) {
			p[i] = horizontal_trace(dets[i].p, head, size + i);
		}
		else {
			p[i] = vertical_trace(dets[i].p, head, size + i);
		}
	}
	if (size[0] == 0 && size[1] == 0 && size[2] == 0) {
		printf("No one can be seen.\n");
		*score += 1;
		printf("Mr. Jack gained 1 hourglass.\n");
		return;
	}
	int flag = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < size[i]; j++) {
			struct node *a = head;
			for (a; a != NULL; a = a->next) {
				if (a->t.p.c == p[i][j].c && a->t.p.r == p[i][j].r && a->t.is_sus == -1) {
					printf("Mr. Jack can be seen.\n");
					flag = 1;
					break;
				}
			}
		}
	}
	if (flag == 0) {
		printf("Mr. Jack cannot be seen.\n");
		*score += 1;
		printf("Mr. Jack gained 1 hourglass.\n");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < size[i]; j++) {
				struct node *n;
				for (n = head; n != NULL; n = n->next) {
					if (n->t.p.r == p[i][j].r && n->t.p.c == p[i][j].c) {
						n->t.is_sus = 0;
						break;
					}
				}
			}
		}
	}
	else {
		struct node *n;
		for (n = head; n != NULL; n = n->next) {
			int bul = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < size[i]; j++) {
					if (n->t.p.r == p[i][j].r && n->t.p.c == p[i][j].c) {
						bul = 1;
						break;
					}		
				}
				if (bul) {
					break;
				}
				if (i == 2) {
					n->t.is_sus = 0;
				}	
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		free(p[i]);
	}
	free(p);
	return;
}
int check_endgame(int turn, int score, struct node *head) {
	if (turn > 8) {
		printf("Mr. Jack escaped from the law, Mr. Jack wins.\n");
		return 1;
	}
	else if (score > 5) {
		printf("Mr. Jack escaped from the law, Mr. Jack wins.\n");
		return 1;
	}
	int susz = 0;
	struct node *i = head;
	for (i; i != NULL; i = i->next) {
		if (i->t.is_sus != 0) {
			susz += 1;
		}
	}
	if (susz < 2) {
		printf("Mr. Jack has no alibis, Investigator wins.\n");
		return 1;
	}
	return 0;
}

void start_new_game() {
	struct node *head = NULL;
	int turn = 1, score = 0;
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

	init_tiles(&head);
	int mrJack = determine_jack(head, suspects);
	while (1) {
		printf("Turn = %d, Mr. Jack's Hourglasses =  %d\n", turn, score);
		print_map(head, suspects, orientations, dets);
		printf("FIRST STAGE - THE MANHUNT\n\n");
		manhunt_stage(&turn, tokens, head, suspects, &score, dets, orientations);
		printf("SECOND STAGE - APPEAL FOR WITNESSES\n\n");
		witness_stage(dets, head, &score);
		print_map(head, suspects, orientations, dets);
		if(check_endgame(turn, score, head)) {
			printf("Press any key to return to Main Menu.\n");
			char s;
			scanf("%c", &s);
			free(head);
			return;
		}
		int x;
		printf("End of Turn %d, Mr. Jack's Hourglasses =  %d:\n\n1)Continue\n2)Save and Return to Main Menu\n3)Return to Main Menu Without Saving\n", turn - 1, score);
		scanf("%d", &x);
		switch (x) {
			case 1:
				Sleep(2500);
				system("cls");
				break;
			case 2:
				break;
			case 3:
				Sleep(2500);
				system("cls");
				free(head);
				return;
				break;
			default:
				break;			
		}
	}
}
