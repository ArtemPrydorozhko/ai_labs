#pragma once
#include <vector>
#include "Node.h"

class RBFS
{
public:
	RBFS(Node& goal_state_);
	~RBFS();
	void solve(Node& start_state);
private:
	Node* goal_state;
	std::vector<Node*> states;
	int rbfs(Node* node, int flimit);
	bool check_goal(Node* state);
	void set_rel(Node* state, Node* new_state);
	bool check_repeats(Node* state);
	void expand_node(Node* state);
	void calc_f(Node* node);
	void calc_best_alt(Node* node, Node** best, Node** alt);
	void print_solution(Node* node);
};

