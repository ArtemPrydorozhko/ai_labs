find_zero([0|_], Z, Index) :- Z is Index.
find_zero([H|T], Z, Index) :- H =\= 0, find_zero(T, Z, Index + 1).
move(Node, NewNode) :- find_zero(Node,Z,0), Z > 2, Xpos is Z - 3, swap_elements(Node, Xpos, Z, NewNode).
move(Node, NewNode) :- find_zero(Node,Z,0), Z < 3, Xpos is Z + 3, swap_elements(Node, Z, Xpos, NewNode).
move(Node, NewNode) :- find_zero(Node,Z,0), Z mod 3 > 0, Xpos is Z - 1, swap_elements(Node, Xpos, Z, NewNode).
move(Node, NewNode) :- find_zero(Node,Z,0), Z mod 3 < 2, Xpos is Z + 1, swap_elements(Node, Z, Xpos, NewNode).

%queue_push(ChildNodes, Queue, NewQueue, Nodes, NewNodes)
queue_push(ChildNodes, Queue, NewQueue, Nodes, NewNodes) :-
    append(Queue, ChildNodes, NewQueue),
    append(ChildNodes, Nodes, NewNodes).
queue_push(_, Queue, Queue, Nodes, Nodes).

% decompose list to A + [X] + C + [Y] + D and swap X with Y
swap_elements(List,Xpos,Ypos,NewList) :-
    append(A, [X|B], List),
    length(A, Xpos),
    append(C, [Y|D], B),
    L is Ypos - Xpos - 1,
    length(C, L),
    append(A, [Y|C], TempList),
    append(TempList, [X|D], NewList).

bfs(GoalNode, [CurrentNode|_], Nodes) :-
    GoalNode == CurrentNode,
    %write(Nodes),nl,
    write(CurrentNode), nl.
bfs(GoalValue,[CurrentNode|RestQueue], Nodes) :-
    findall(NewNode, (move(CurrentNode, NewNode), \+ member(NewNode, Nodes)), Children),
    queue_push(Children, RestQueue, NewQueue, Nodes, NewNodes),
    bfs(GoalValue,NewQueue,NewNodes).

% 1 - стул 2 - стол 3 - шкаф 4 - кресло
% bfs([2,1,3,1,0,4], [[2,1,4,1,0,3]], [[2,1,4,1,0,3]])