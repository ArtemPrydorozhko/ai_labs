#include <iostream>
#include "Node.h"
#include "RBFS.h"
#include <vector>

using namespace std;

int main()
{
    vector<int> vect_start(
        { 2, 8, 3,
          1, 6, 4,
          7, 0, 5 });
    vector<int> vect_goal(
        { 1, 2, 3,
          8, 0, 4,
          7, 6, 5 });

    Node goal_state(vect_goal);
    Node start(vect_start);
    RBFS rbfs(goal_state);
    rbfs.solve(start);
}
