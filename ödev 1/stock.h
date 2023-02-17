#ifndef STOCK_H
#define STOCK_H

#include "list.h"

struct stock {
	node* root;
	void create();
	void add_stock(int);
	void sell(int);
	void current_stock();
	void clear();
};

#endif

