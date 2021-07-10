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
	// 0 not sus : 1 sus : -1 Mr.Jack
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
int determine_jack(struct node *head);
void dets_action(int det_id, struct detective *dets);
void joker_action(int round, struct detective *dets);
void lens_action(struct node *head, struct suspect *s, int *score);
struct place *horizontal_trace(struct place det, struct node *head, int *size);
struct place *vertical_trace(struct place det, struct node *head, int *size);






#endif
