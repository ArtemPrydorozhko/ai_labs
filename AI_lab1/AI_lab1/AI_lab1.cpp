#include <iostream>
#include <queue>
#include <stack>
using namespace std;

const int bucket1Capacity = 5;
const int bucket2Capacity = 9;

struct State
{
	int bucket1;
	int bucket2;
	State* parent;

	State(int bucket1, int bucket2) {
		this->bucket1 = bucket1;
		this->bucket2 = bucket2;
		parent = NULL;
	}
};

vector<State*> states;

bool solve();
State* createState(int, int);
bool checkState(int, int);
void printResult();

int main()
{
	bool solved = solve();

	if (solved) {
		printResult();
	}
	else {
		cout << "n";
	}
    
}

bool solve() {
	State *initial = new State(0, 0);
	queue<State*> q;
	q.push(initial);
	states.push_back(initial);

	while (!q.empty()) {
		State *current = q.front();
		q.pop();

		// cout << "------" << current.bucket1 << " " << current.bucket2 << "\n";
		while (true) {
			State *newState = createState(current->bucket1, current->bucket2);
			if (newState->bucket1 == -1) {
				break;
			}
		//	cout << newState.bucket1 << " " << newState.bucket2 << '\n';
			newState->parent = current;
			states.push_back(newState);
			if (newState->bucket1 == 3 || newState->bucket2 == 3) {
				return true;
			}
			q.push(newState);
		}
	}

	return false;
}

State* createState(int bucket1, int bucket2) {
	int newbucket1 = 0;
	int newbucket2 = 0;
	bool isUnique;
	State *newState = new State(0, 0);

	if (bucket1 != bucket1Capacity) {
		newbucket1 = bucket1Capacity;
		newbucket2 = bucket2;
		isUnique = checkState(newbucket1, newbucket2);
		if (isUnique) {
			newState->bucket1 = newbucket1;
			newState->bucket2 = newbucket2;
			return newState;
		}
		else {
			newbucket1 = 0;
			newbucket2 = 0;
		}
	}
	if (bucket2 != bucket2Capacity) {
		newbucket1 = bucket1;
		newbucket2 = bucket2Capacity;
		isUnique = checkState(newbucket1, newbucket2);
		if (isUnique) {
			newState->bucket1 = newbucket1;
			newState->bucket2 = newbucket2;
			return newState;
		}
		else {
			newbucket1 = 0;
			newbucket2 = 0;
		}
	}
	if (bucket1 != bucket1Capacity && bucket2 != 0) {
		int addTobucket1 = bucket1Capacity - bucket1;
		newbucket1 = bucket1 + (bucket2 <= addTobucket1 ? bucket2 : addTobucket1);
		newbucket2 = bucket2 <= addTobucket1 ? 0 : bucket2 - addTobucket1;
		isUnique = checkState(newbucket1, newbucket2);
		if (isUnique) {
			newState->bucket1 = newbucket1;
			newState->bucket2 = newbucket2;
			return newState;
		}
		else {
			newbucket1 = 0;
			newbucket2 = 0;
		}
	}
	if (bucket2 != bucket2Capacity && bucket1 != 0) {
		int addTobucket2 = bucket2Capacity - bucket2;
		newbucket2 = bucket2 + (bucket1 <= addTobucket2 ? bucket1 : addTobucket2);
		newbucket1 = bucket1 <= addTobucket2 ? 0 : bucket1 - addTobucket2;
		isUnique = checkState(newbucket1, newbucket2);
		if (isUnique) {
			newState->bucket1 = newbucket1;
			newState->bucket2 = newbucket2;
			return newState;
		}
		else {
			newbucket1 = 0;
			newbucket2 = 0;
		}
	}
	if (bucket1 != 0) {
		newbucket1 = 0;
		newbucket2 = bucket2;
		isUnique = checkState(newbucket1, newbucket2);
		if (isUnique) {
			newState->bucket1 = newbucket1;
			newState->bucket2 = newbucket2;
			return newState;
		}
		else {
			newbucket1 = 0;
			newbucket2 = 0;
		}
	}
	if (bucket2 != 0) {
		newbucket1 = bucket1;
		newbucket2 = 0;
		isUnique = checkState(newbucket1, newbucket2);
		if (isUnique) {
			newState->bucket1 = newbucket1;
			newState->bucket2 = newbucket2;
			return newState;
		}
		else {
			newbucket1 = 0;
			newbucket2 = 0;
		}
	}

	return new State(-1, -1);
}

bool checkState(int bucket1, int bucket2) {
	bool isUnique = true;

	for (int i = 0; i < states.size(); i++)	{
		State *state = states[i];
		if (state->bucket1 == bucket1 && state->bucket2 == bucket2) {
			isUnique = false;
			break;
		}
	}

	return isUnique;
}

void printResult() {
	State *state = states.back();
	stack<State*> s;
	while (true) {
		s.push(state);
		if (!state->parent) {
			break;
		}
		state = state->parent;
	}
	cout << "bucket " << bucket1Capacity << " bucket "<< bucket2Capacity << endl;
	while (!s.empty()) {
		state = s.top();
		s.pop();
		cout << state->bucket1 << " " << state->bucket2 << endl;
	}
}