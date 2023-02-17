#include <iostream>
#include <fstream>
#include <string>

#include "Node.h"
#include "Network.h"
using namespace std;

typedef Network Datastructure;
Datastructure Network1;

FILE* fp;


int main(){
	int end;
	int begin;
	char type[3];
	char type1[3] = "BS";
	char type2[3] = "MH";
	Network1.create();
	fp = fopen("Network.txt", "r");
	while (!feof(fp)) {
		fscanf(fp, "%s %d &d",type,&end,&begin);
		if (strcmp(type1, type)) {
			Network1.add_node1(end,begin);
		}
		else if (strcmp(type2,type)){
			Network1.add_node2();
		}
	}
	return 0;
}	

void Network::add_node1(int a,int b) {
	Node1* add_task = new Node1;
	add_task->id = a;
	Node1* traverse = head;
	if (head == NULL) {
		head = add_task;
		head->child = NULL;
		head->parent = NULL;
		head->next = NULL;
		head->child2 = NULL;
		return;
	}
	if (head->child == NULL) {
		head->child = add_task;
		add_task->parent = head;
		add_task->next = NULL;
		add_task->child = NULL;
		add_task->child2 = NULL;
		return;
	}
	rec(b);
}

int Network::rec(int b) {
	if (traverse->id == b) {
		return;
	}
	else {
		traverse = traverse->child;
		if (!traverse)
			return 1;
		rec(b);
		traverse = traverse->next;
		rec(b);
	}
}

/*void find(Node1* add_task) {

}
void Network::add_node2() {

}
*/
void Network::create() {
	head = NULL;
	int a = 0;
	int b = 0;
	add_node1(a, b);
}

/*void Network::close() {

}*/
