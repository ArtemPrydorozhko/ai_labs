#include "SIAN.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

SIAN::SIAN(Node& goal_state_)
{
	goal_node = new Node(goal_state_);
	srand(time(NULL));
}

SIAN::~SIAN()
{
	for (Node* node : nodes)
	{
		delete node;
	}
	delete goal_node;
}

void SIAN::solve(Node& start_state_)
{
	Node* prev = new Node(start_state_);
	calc_E(prev);
	nodes.push_back(prev);
	Node* state = prev;
	const double alpha = 0.9;
	const double e = 2.718281828;

	for (double T = 1; T > 0.00001; T *= alpha)
	{
		for (size_t i = 0; i < 200; i++)
		{
			if (check_goal(state)) {
				print_solution(state);
				return;
			}
			state = expand_node(prev);
			calc_E(state);

			if (state->E - prev->E > 0) {
				prev = state;
			}
			else if (pow(e, (state->E - prev->E) / T) > (rand() % 100000) / 100000.0) {
				prev = state;
			}
		}
	}

	print_solution(state);
}

bool SIAN::check_goal(Node* node)
{
	return node->equals(goal_node);
}

bool SIAN::check_repeats(Node* new_node)
{
	for (Node* state : nodes)
	{
		if (state->equals(new_node))
		{
			return true;
		}
	}

	return false;
}

Node* SIAN::expand_node(Node* state)
{
	Node* child = nullptr;
	int i = state->find_empty_index();
	int r = rand() % 4;

	for (size_t j = 0; j < 4; j++)
	{
		switch (r)
		{
		case 0:
			child = state->move_down(i);
			break;
		case 1:
			child = state->move_up(i);
			break;
		case 2:
			child = state->move_left(i);
			break;
		case 3:
			child = state->move_right(i);
			break;
		}

		if (child && !check_repeats(child)) {
			break;
		}
		r = r == 3 ? 0 : r + 1;
	}
	
	return child;
}

void SIAN::calc_E(Node* node)
{
	int manh_dist = 0;

	int index = -1;
	int goal_index = 0;
	for (int y = 0; y < node->matrix_size; y++) {
		for (int x = 0; x < node->matrix_size; x++) {
			index++;
			for (int i = 0; i < goal_node->state.size(); i++)
			{
				if (node->state[index] == goal_node->state[i])
				{
					goal_index = i;
				}
			}

			int val = node->state[index];

			if (val != 0) {
				int horiz = index % node->matrix_size;
				int horiz_goal = goal_index % node->matrix_size;
				int vert = index / node->matrix_size;
				int vert_goal = goal_index / node->matrix_size;
				manh_dist += abs(vert - vert_goal) + abs(horiz - horiz_goal);
			}
		}
	}

	node->E = -manh_dist;
}

void SIAN::print_solution(Node* node)
{
	for (int i = 0; i < node->state.size(); i++)
	{
		cout << " " << node->state[i];
		if (i % node->matrix_size == node->matrix_size - 1)
		{
			cout << endl;
		}
	}
	cout << endl;
}
