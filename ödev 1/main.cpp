/* @Author
Student Name: Yavuz Kanber
Student ID: 150170034
Date: 22.10.2019 
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include "list.h"
#include "stock.h"

using namespace std;
stock sto;
FILE* fp;

int main() {
	int shoe_size;
	fp = fopen("input.txt", "r");
	sto.create();
	while (!feof(fp)) {
		fscanf(fp, "%d", &shoe_size);
		if (shoe_size > 0) {
			sto.add_stock(shoe_size);
		}
		if (shoe_size < 0) {
			sto.sell(shoe_size);
		}
		if (shoe_size == 0) {
			sto.current_stock();
		}
	}
	sto.clear();
	return 0;
}

	void stock::create() {
	root = NULL;
}
void stock::add_stock(int shoe_size) {
	node* traverse = root;
	node* tail = NULL;
	node* newnode = new node;

	if (!root) {
		newnode->nsize = shoe_size;
		newnode->quantity += 1;
		root = newnode;
		root->next = NULL;
		return;
	}
	while (traverse && traverse->nsize <= shoe_size) {
		if (traverse->nsize == shoe_size) {
			traverse->quantity += 1;
			return;
		}
		tail = traverse;
		traverse = traverse->next;
	}
	newnode->nsize = shoe_size;
	newnode->quantity = 1;
	if (root->nsize > shoe_size) {
		newnode->next = traverse;
		root = newnode;
		return;
	}
	if (traverse) {
		newnode->next = traverse;
		tail->next = newnode;
	}
	else {
		tail->next = newnode;
		newnode->next = NULL;
	}
}
void stock::sell(int shoe_size) {
	shoe_size = -1 * shoe_size;
	node* traverse = root;
	node* tail = NULL;
	if (traverse->nsize == shoe_size) {
		traverse->quantity -= 1;
		if (traverse->quantity == 0) {
			root = traverse->next;
			delete traverse;
		}
		return;
	}
	while (traverse && traverse->nsize <= shoe_size) {
		if (traverse->nsize == shoe_size) {
			traverse->quantity -= 1;
			if (traverse->quantity == 0) {
				tail->next = traverse->next;
				delete traverse;
			}
			return;
		}
		tail = traverse;
		traverse = traverse->next;
	}
	cout << "NO_STOCK" << endl;
}

void stock::current_stock() {
	node* print = root;
	while (print) {
		cout << print->nsize << ":" << print->quantity << endl;
		print = print->next;
	}
}

void stock::clear() {
	node* traverse = root;
	node* tail = NULL;
	while (traverse) {
		tail = traverse;
		traverse = traverse->next;
		delete tail;
	}
}
