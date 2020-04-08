#pragma once
#include "Node.h"
#include <vector>
#include <ctime>

class SIAN
{
public:
	SIAN(Node& goal_node);
	~SIAN();
	void solve(Node& start_node);
private:
	Node* goal_node;
	std::vector<Node*> nodes;
	bool check_goal(Node* node);
	bool check_repeats(Node* node);
	Node* expand_node(Node* node);
	void calc_E(Node* node);
	void print_solution(Node* node);

};

