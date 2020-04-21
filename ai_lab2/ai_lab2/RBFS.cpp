#include "RBFS.h"
#include <iostream>

using namespace std;

RBFS::RBFS(Node& goal_state_)
{
	goal_state = new Node(goal_state_);
}

RBFS::~RBFS()
{
	for (Node* node : states)
	{
		delete node;
	}
	delete goal_state;
}

void RBFS::solve(Node& start_state_)
{
	Node* start_state = new Node(start_state_);
	calc_f(start_state);
	states.push_back(start_state);
	int result = rbfs(start_state, INT_MAX);

	if (result == INT_MAX)
	{
		cout << "Cant find solution";
	}
}

int RBFS::rbfs(Node* node, int flimit)
{
	if (check_goal(node))
	{
		print_solution(node);
		return -1;
	}

	expand_node(node);
	if (node->children.size() == 0)
	{
		return INT_MAX;
	}

	for (Node* child : node->children)
	{
		if (node->f < node->F)
		{
			child->F = node->F > child->f ? node->F : child->f;
		}
		else
		{
			child->F = child->f;
		}
	}

	Node* best = nullptr, *alt = nullptr;
	calc_best_alt(node, &best, &alt);

	int new_flimit;
	while (best->F <= flimit && best->F < INT_MAX)
	{
		new_flimit = alt ? (alt->F < flimit ? alt->F : flimit) : flimit;
		best->F = rbfs(best, new_flimit);
		if (best->F == -1)
		{
			return -1;
		}
		calc_best_alt(node, &best, &alt);
	}
	return best->F;
}

bool RBFS::check_goal(Node* state)
{
	return state->equals(goal_state);
}

void RBFS::set_rel(Node* state, Node* new_state)
{
	if (!check_repeats(new_state))
	{
		new_state->parent = state;
		state->children.push_back(new_state);
		states.push_back(new_state);
		calc_f(new_state);
	}
	else
	{
		delete new_state;
	}
}

bool RBFS::check_repeats(Node* new_state)
{
	for (Node* state : states)
	{
		if (state->equals(new_state))
		{
			return true;
		}
	}

	return false;
}

void RBFS::expand_node(Node* state)
{
	Node* child;
	int i = state->find_empty_index();

	child = state->move_down(i);
	if (child) set_rel(state, child);

	child = state->move_up(i);
	if (child) set_rel(state, child);

	child = state->move_left(i);
	if (child) set_rel(state, child);

	child = state->move_right(i);
	if (child) set_rel(state, child);
}

void RBFS::calc_f(Node* node)
{
	int step = 0;
	int manh_dist = 0;
	Node* parent = node;
	while (true)
	{
		parent = parent->parent;
		if (!parent) {
			break;
		}
		step++;
	}

	int index = -1;
	int goal_index = 0;
	for (int y = 0; y < node->matrix_size; y++) {
		for (int x = 0; x < node->matrix_size; x++) {
			index++;
			for (int i = 0; i < goal_state->state.size(); i++)
			{
				if (node->state[index] == goal_state->state[i])
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

	node->f = node->F = manh_dist + step;
}

void RBFS::calc_best_alt(Node* node, Node** best, Node** alt)
{
	*best = *alt = nullptr;
	if (node->children.size() == 1)
	{
		*best = node->children[0];
	}
	else
	{
		*best = node->children[0];
		*alt = node->children[1];
		for (int i = 1; i < node->children.size(); i++)
		{
			if (node->children[i]->F <= (*best)->F)
			{
				*alt = *best;
				*best = node->children[i];
			}
			else if (node->children[i]->F <= (*alt)->F)
			{
				*alt = node->children[i];
			}
		}
	}
}

void RBFS::print_solution(Node* node)
{
	do
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
		node = node->parent;
	} while (node);
}
