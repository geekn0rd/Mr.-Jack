#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>

//for storing coordinates
struct coords {
	int x;
	int y;
};

struct suspect {
	char name[256];
	int  hourglass;
};

struct detective {
	char name[256];
	struct coords r;
};

struct tile {
	int sus_id;
	int is_sus;
	int orien;
	struct coords r;
};

struct node {
	struct tile t;
	struct node *next;
};

void push_back(struct node **head, int id, int is_sus, int ori, int i, int j);
int is_found(struct node *head, int id);
void print_by_xy(int x, int y, struct node *head, struct suspect *s, int *o, struct detective *dets);
void print_tiles(struct node *head, struct suspect *s, int *o);
void print_dets(struct detective *dets);








#endif
