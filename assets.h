#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>

struct character {
	char name[256];
	int  hourglass;
};

struct tile {
	struct character c;
	int is_suspect;
	int orientation;
};

struct node {
	struct tile;
	struct node *next;
};

#endif
