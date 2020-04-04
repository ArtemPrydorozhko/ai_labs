#pragma once
#include<vector>

class Node
{
public:
	Node(std::vector<int> &state_);
	Node(Node& node);
	Node* move_left(int i);
	Node* move_right(int i);
	Node* move_up(int i);
	Node* move_down(int i);
	bool equals(Node* state);
	int find_empty_index();

	std::vector<int> state;
	std::vector<Node*> children;
	Node* parent;
	int matrix_size;
	int f;
	int F;
};
