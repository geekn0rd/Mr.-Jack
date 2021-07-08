#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>

// row & column for storing placement
struct place {
	int r;
	int c;
};

struct suspect {
	char name[256];
	int  hourglass;
};

struct detective {
	char name[256];
	struct place p;
};

struct tile {
	int sus_id;
	int is_sus;
	int orien;
	struct place p;
};

struct node {
	struct tile t;
	struct node *next;
};

void push_back(struct node **head, int id, int is_sus, int ori, int i, int j);
int is_found(struct node *head, int id);
void print_by_rc(int r, int c, struct node *head, struct suspect *s, int *o, struct detective *dets);
void print_tiles(struct node *head, struct suspect *s, int *o);
void print_dets(struct detective *dets);
void replace_tiles(struct node *head);
void rotate_tile(struct node *head);
void print_map(struct node *head, struct suspect *susz, int *oriens, struct detective *dets);
void init_tiles(struct node **head);






#endif
