% bestfirst(Start, Solution)
bestfirst(Start, Solution) :- rbfs([], [ (Start, 0/0/0) ], 99999, _, yes, Solution).

% rbfs(Path, SiblingNodes, Bound, NewBestFF, Solved, Solution):
% Path = path so far in reverse order
% SiblingNodes = children of head of Path
% Bound = upper bound on F-value for search from SiblingNodes
% NewBestFF = best f-value after searching just beyond Bound
% Solved = yes, no, or never 
% Solution = solution path if Solve = yes
%
% Representation of nodes: Node = (State, G/F/FF)
% where G is cost till State, F is static f-value of State, 
% FF is backed-up value of State

rbfs(_, [ (_, _/_/FF) | _], Bound, FF, no, _) :-
    FF > Bound, !.

rbfs(_, [ (Node, _/F/FF) | _], _, _, yes, Node) :-
    F = FF,
    write(Node).

rbfs(_, [], _, _, never, _) :- !.    % No candidates

rbfs(Path, [ (Node, G/F/FF) | Ns], Bound, NewFF, Solved, Sol) :-
    %write(Node), nl,
    FF =< Bound,
    findall(Child,
            (move(Node, Child), \+ member(Child, Path)),
            Children),
    inherit(F, FF, InheritedFF),
    succlist(G, InheritedFF, Children, SuccNodes, Sol),    % Order children
    bestff(Ns, NextBestFF),          % Closest competitor FF among siblings
    min(Bound, NextBestFF, Bound2), !,
    rbfs([Node | Path], SuccNodes, Bound2, NewFF2, Solved2, Sol),
    continue(Path, [(Node,G/F/NewFF2)|Ns], Bound, NewFF, Solved2, Solved, Sol).



% continue(Path, Nodes, Bound, NewFF, ChildSolved, Solved, Solution)
continue(Path, [_ | Ns], Bound, NewFF, never, Solved, Sol) :- !,
    rbfs(Path, Ns, Bound, NewFF, Solved, Sol). % Node N a dead end

continue(_, _, _, _, yes, yes, _).

continue(Path, [ N | Ns], Bound, NewFF, no, Solved, Sol) :-
    insert(N, Ns, NewNs), !,         % Ensure siblings are ordered by values
    rbfs(Path, NewNs, Bound, NewFF, Solved, Sol).



succlist(_, _, [], [], _).

succlist(G0, InheritedFF, [Node | NCs], Nodes, Sol) :-
    G is G0 + 1,
    h(Node, Node, H, Sol),
    F is G + H,
    max(F, InheritedFF, FF),
    succlist(G0, InheritedFF, NCs, Nodes2, Sol),
    insert((Node, G/F/FF), Nodes2, Nodes).

inherit(F, FF, FF) :-
    FF > F, !.

inherit(_, _, 0).

insert((N, G/F/FF), Nodes, [ (N, G/F/FF) | Nodes]) :-
    bestff(Nodes, FF2),
    FF =< FF2, !.

insert(N, [N1 | Ns], [N1 | Ns1]) :-
    insert(N, Ns, Ns1).

bestff([ (_, _/_/FF) | _], FF).

bestff([], 99999).

min(X, Y, X) :-
    X  =<  Y, !.
min(_, Y, Y).

max(X, Y, X) :-
    X  >=  Y, !.
max(_, Y, Y).

h([], _, 0, _).
h([El|Rest], Node, H, Sol) :-
	find_index(El, Node, Nindex, 0),
    find_index(El, Sol, Sindex, 0),
    Ydiff is Nindex // 3 - Sindex // 3,
    abs(Ydiff, Yabs),
    Xdiff is Nindex mod 3 - Sindex mod 3,
    abs(Xdiff, Xabs),
    h(Rest, Node, H2, Sol),
    H is Xabs + Yabs + H2.
    
find_index(Num, [Num|_], Z, Index) :-
    Z is Index.
find_index(Num, [_|T], Z, Index) :-
    find_index(Num, T, Z, Index + 1).
    
find_zero([0|_], Z, Index) :- Z is Index.
find_zero([H|T], Z, Index) :- H =\= 0, find_zero(T, Z, Index + 1).

move(Node, NewNode) :- find_zero(Node,Z,0), Z > 2, Xpos is Z - 3, swap_elements(Node, Xpos, Z, NewNode).
move(Node, NewNode) :- find_zero(Node,Z,0), Z < 6, Xpos is Z + 3, swap_elements(Node, Z, Xpos, NewNode).
move(Node, NewNode) :- find_zero(Node,Z,0), Z mod 3 > 0, Xpos is Z - 1, swap_elements(Node, Xpos, Z, NewNode).
move(Node, NewNode) :- find_zero(Node,Z,0), Z mod 3 < 2, Xpos is Z + 1, swap_elements(Node, Z, Xpos, NewNode).

% decompose list to A + [X] + C + [Y] + D and swap X with Y
swap_elements(List,Xpos,Ypos,NewList) :-
    append(A, [X|B], List),
    length(A, Xpos),
    append(C, [Y|D], B),
    L is Ypos - Xpos - 1,
    length(C, L),
    append(A, [Y|C], TempList),
    append(TempList, [X|D], NewList).

% bestfirst([2,8,1,3,6,4,7,0,5], [1,2,3,4,0,5,6,7,8]).
