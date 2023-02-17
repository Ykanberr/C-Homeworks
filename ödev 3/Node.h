struct Node1{
	int id;
	Node1* parent;
	Node1* child;
	Node1* next;
	Node2* child2;
};

struct Node2 {
	int id;
	Node1* parent;
	Node2* next;
};
