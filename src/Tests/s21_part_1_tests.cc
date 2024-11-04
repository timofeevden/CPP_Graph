#include "s21_tests.h"

TEST(GraphAlgorithms, DepthFirstSearch) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_7x7");

  std::vector<int> res;
  res = algorithms.DepthFirstSearch(graph, 0);

  std::vector<int> answer = {1, 5, 4, 3, 2};

  for (size_t i = 0; i < res.size(); ++i) {
    EXPECT_EQ(res[i], answer[i]);
  }
}

TEST(GraphAlgorithms, DFS_empty) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_3x3_empty");

  std::vector<int> res;
  res = algorithms.DepthFirstSearch(graph, 0);

  std::vector<int> answer = {1};

  EXPECT_EQ(res.size(), answer.size());
}

TEST(GraphAlgorithms, DFS_bad) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_0");

  std::vector<int> res;

  EXPECT_ANY_THROW(algorithms.DepthFirstSearch(graph, 0));
}

TEST(GraphAlgorithms, DFS_bad_2) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_0");

  std::vector<int> res;

  EXPECT_ANY_THROW(algorithms.DepthFirstSearch(graph, 999));
}

TEST(GraphAlgorithms, DFS_bad_3) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_3x3");

  std::vector<int> res;

  EXPECT_ANY_THROW(algorithms.DepthFirstSearch(graph, 999));
}

TEST(GraphAlgorithms, BreadthFirstSearch) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_7x7");

  std::vector<int> res;
  res = algorithms.BreadthFirstSearch(graph, 0);

  std::vector<int> answer = {1, 5, 4, 2, 3};

  for (size_t i = 0; i < res.size(); ++i) {
    EXPECT_EQ(res[i], answer[i]);
  }
  /*
    for (long unsigned int i = 0; i < res.size(); ++i) {
      std::cout << res[i] << " ";
    }
    std::cout << "\n";
  */
}

TEST(GraphAlgorithms, BFS_empty) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_3x3_empty");

  std::vector<int> res;
  res = algorithms.BreadthFirstSearch(graph, 0);

  std::vector<int> answer = {1};

  EXPECT_EQ(res.size(), answer.size());
}

TEST(GraphAlgorithms, BFS_bad) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_0");

  std::vector<int> res;

  EXPECT_ANY_THROW(algorithms.BreadthFirstSearch(graph, 0));
}

TEST(GraphAlgorithms, BFS_bad_2) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_0");

  std::vector<int> res;

  EXPECT_ANY_THROW(algorithms.BreadthFirstSearch(graph, 999));
}

TEST(GraphAlgorithms, BFS_bad_3) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_3x3");

  std::vector<int> res;

  EXPECT_ANY_THROW(algorithms.BreadthFirstSearch(graph, 999));
}