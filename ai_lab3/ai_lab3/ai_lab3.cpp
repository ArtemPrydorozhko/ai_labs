#include <iostream>
#include <vector>
#include "SIAN.h"
#include "Node.h"

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
    SIAN sian(goal_state);
    sian.solve(start);
    sian.solve(start);
    sian.solve(start);
    sian.solve(start);
    sian.solve(start);
}
