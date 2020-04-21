#include <iostream>
#include "Node.h"
#include "RBFS.h"
#include <vector>

using namespace std;

int main()
{
    vector<int> vect_start(
        { 2, 8, 1,
          3, 6, 4,
          7, 0, 5 });
    vector<int> vect_goal(
        { 1, 2, 3,
          4, 0, 5,
          6, 7, 8 });

    Node goal_state(vect_goal);
    Node start(vect_start);
    RBFS rbfs(goal_state);
    rbfs.solve(start);
}
