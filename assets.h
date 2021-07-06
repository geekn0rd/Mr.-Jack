#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>

struct suspect {
	char name[256];
	int  hourglass;
};

struct tile {
	int sus_id;
	int is_sus;
	int orientation;
	int position[2];
};

struct node {
	struct tile t;
	struct node *next;
};

void push_back(struct node **head, int id, int is_sus, int ori, int i, int j);
int is_found(struct node *head, int id);
#endif
