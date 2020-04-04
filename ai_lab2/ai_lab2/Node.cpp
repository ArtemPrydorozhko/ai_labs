#include "Node.h"
#include <vector>
#include <math.h>

using namespace std;

Node::Node(std::vector<int>& state_)
{
	state = vector<int>(state_);
	matrix_size = sqrt(state.size());
	parent = nullptr;
	f = F = 0;
}

Node::Node(Node& node)
{
	state = node.state;
	children = node.children;
	parent = node.parent;
	matrix_size = node.matrix_size;
	f = node.f;
	F = node.F;
}

Node* Node::move_left(int i)
{
	if (i % matrix_size > 0)
	{
		vector<int> new_state = vector<int>(state);
		int temp = state[i - 1];
		new_state[i - 1] = new_state[i];
		new_state[i] = temp;

		return new Node(new_state);
	}
	return nullptr;
}

Node* Node::move_right(int i)
{
	if (i % matrix_size < matrix_size - 1)
	{
		vector<int> new_state = vector<int>(state);
		int temp = state[i + 1];
		new_state[i + 1] = new_state[i];
		new_state[i] = temp;

		return new Node(new_state);
	}
	return nullptr;
}

Node* Node::move_up(int i)
{
	if (i - matrix_size >= 0)
	{
		vector<int> new_state = vector<int>(state);
		int temp = state[i - 3];
		new_state[i - 3] = new_state[i];
		new_state[i] = temp;

		return new Node(new_state);
	}
	return nullptr;
}

Node* Node::move_down(int i)
{
	if (i + matrix_size < state.size())
	{
		vector<int> new_state = vector<int>(state);
		int temp = state[i + 3];
		new_state[i + 3] = new_state[i];
		new_state[i] = temp;

		return new Node(new_state);
	}
	return nullptr;
}

bool Node::equals(Node* node)
{
	for (size_t i = 0; i < state.size(); i++)
	{
		if (node->state[i] != state[i])
		{
			return false;
		}
	}

	return true;
}

int Node::find_empty_index()
{
	for (int i = 0; i < state.size(); i++)
	{
		if (state[i] == 0)
		{
			return i;
		}
	}
	return -1;
}

