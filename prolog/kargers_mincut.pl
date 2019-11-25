graph_nTrials_minCut(G, N, MinCut) :-
    length(Trials, N),
    maplist(graph_kargersMinCut(G), Trials),
    min_list(Trials, MinCut), !.

graph_kargersMinCut(G, N) :-
    graph_contracted(G, C),
    length(C, N), !.

/* The Contraction Algorithm:

From https://en.wikipedia.org/wiki/Karger%27s_algorithm#Contraction_algorithm

  contraction algorithm:
    contract(G=(V,E)):
      while |V| > 2
                choose e in E uniformly at random
                G is the contraction G/e
      return the only cut in G
*/
graph_contracted(Graph, Contracted) :-
    graph(Nodes, Edges) = Graph,
    length(Nodes, Len),
    Len > 2,
    random_member(Edge, Edges),
    graph_edge_contracted(Graph, Edge, NewGraph),
    graph_contracted(NewGraph, Contracted).
graph_contracted(Graph, Contracted) :-
    graph(Nodes, Edges) = Graph,
    length(Nodes, Len),
    Len =< 2,
    Contracted = Edges.

random_edge(Graph, Edge) :-
    graph(_, Edges) = Graph,
    random_member(Edge, Edges).

graph_edge_contracted(Graph, Edge, NewGraph) :-
    graph(Nodes,Edges) = Graph,
    maplist(edge_node_merged(Edge), Nodes, NodesToSort),
    sort(NodesToSort, NewNodes),
    maplist(edges_merged(Edge), Edges, EdgesToFilter),
    exclude_self_loops(EdgesToFilter, NewEdges),
    NewGraph = graph(NewNodes, NewEdges).

edge_node_merged(A-B, A, AB) :-
    atom_concat(A,B,AB), !.
edge_node_merged(A-B, B, AB) :-
    atom_concat(A,B,AB), !.
edge_node_merged(A-B, X, X)   :-
    X \= A, X \= B.

edges_merged(Edge, X-Y, L-R)  :-
    edge_node_merged(Edge, X, L),
    edge_node_merged(Edge, Y, R).

exclude_self_loops(Edges, NewEdges) :-
    exclude(=(A-A), Edges, NewEdges).


%% Reading graph data from files

file_edgesGraph(File, Graph) :-
    file_to_lines(File, Lines),
    maplist(string_to_words, Lines, AdjLists),
    maplist(hd, AdjLists, Nodes),
    %% Presupposes that the adjacency lists describe a proper graph, and not a multi graph:
    aggregate_all( set(Edge),
                   ( member([A|Bs], AdjLists),
                     member(B,Bs),
                     ( A @< B -> Edge = A-B ; Edge = B-A) ),
                   Edges ),
    Graph = graph(Nodes, Edges).

file_to_lines(File, Lines) :-
    read_file_to_string(File, String, []),
    split_string(String, "\n", "\n", Lines).

string_to_words(String, Words) :-
    split_string(String, " ", " ", Words).

hd([Hd|_], Hd).


%% Tests

:- begin_tests(kargers).

test(edge_node_merge_left) :-
    edge_node_merged(a-b, a, Merged),
    Merged = ab.
test(edge_node_merge_right) :-
    edge_node_merged(a-b, b, Merged),
    Merged = ab.
test(edge_node_merge_none) :-
    edge_node_merged(a-b, x, Merged),
    Merged = x.

test(edges_merged_both) :-
    edges_merged(a-b, b-a, ab-ab),
    edges_merged(a-b, a-b, ab-ab).
test(edges_merged_left) :-
    edges_merged(a-b, a-x, ab-x),
    edges_merged(a-b, b-x, ab-x).
test(edges_merged_right) :-
    edges_merged(a-b, x-a, x-ab),
    edges_merged(a-b, x-b, x-ab).
test(edges_merged_none) :-
    edges_merged(a-b, x-y, x-y).

test(kargers_minCut_1) :-
     File = '../../nlang-algorithms/karger_minimum_cut/one_cut_graphs/a_1.txt',
     file_edgesGraph(File, G),
     graph_nTrials_minCut(G, 100, N),
     N =:= 1.

test(kargers_minCut_2) :-
    File = '../../nlang-algorithms/karger_minimum_cut/two_cut_graphs/a_2.txt',
    file_edgesGraph(File, G),
    graph_nTrials_minCut(G, 100, N),
    N =:= 2.

test(kargers_minCut_3) :-
    File = '../../nlang-algorithms/karger_minimum_cut/three_cut_graphs/a_3.txt',
    file_edgesGraph(File, G),
    graph_nTrials_minCut(G, 100, N),
    N =:= 3.

test(kargers_minCut_4) :-
    File = '../../nlang-algorithms/karger_minimum_cut/four_cut_graphs/a_4.txt',
    file_edgesGraph(File, G),
    graph_nTrials_minCut(G, 100, N),
    N =:= 4.

:- end_tests(kargers).
