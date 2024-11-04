#include "s21_tests.h"

const int INF = std::numeric_limits<int>::max();

TEST(GraphAlgorithms, Part_2) {
  s21::Graph g;
  s21::GraphAlgorithms algorithms;
  int res, expected;

  g.LoadGraphFromFile("Tests/TestFiles/test_graph");
  res = algorithms.GetShortestPathBetweenVertices(g, 0, 5);
  expected = 9;
  EXPECT_EQ(res, expected);

  g.LoadGraphFromFile("Tests/TestFiles/graph_ant_3x3_empty");
  res = algorithms.GetShortestPathBetweenVertices(g, 0, 2);
  expected = INF;  // here's no answer
  EXPECT_EQ(res, expected);

  g.LoadGraphFromFile("Tests/TestFiles/graph_3_line");
  res = algorithms.GetShortestPathBetweenVertices(g, 0, 2);
  expected = 2;
  EXPECT_EQ(res, expected);

  EXPECT_ANY_THROW(algorithms.GetShortestPathBetweenVertices(g, -1, 0));
  EXPECT_ANY_THROW(algorithms.GetShortestPathBetweenVertices(g, 5, 0));
  EXPECT_ANY_THROW(algorithms.GetShortestPathBetweenVertices(g, 0, 10));

  g.LoadGraphFromFile("Tests/TestFiles/graph_6_different");
  res = algorithms.GetShortestPathBetweenVertices(g, 0, 5);
  expected = INF;
  EXPECT_EQ(res, expected);

  g.LoadGraphFromFile("Tests/TestFiles/graph_0");
  EXPECT_ANY_THROW(algorithms.GetShortestPathBetweenVertices(g, 0, 5));
}

TEST(GraphAlgorithms, Part_2_) {
  s21::Graph g;
  s21::GraphAlgorithms algorithms;
  g.LoadGraphFromFile("Tests/TestFiles/test_graph");
  std::vector<std::vector<int>> res;
  std::vector<std::vector<int>> expected;

  res = algorithms.GetShortestPathsBetweenAllVertices(g);
  expected = {
      {0, 2, 5, 5, 7, 9},   {2, 0, 3, 7, 5, 7}, {5, 3, 0, 10, 8, 4},
      {5, 7, 10, 0, 7, 14}, {7, 5, 8, 7, 0, 9}, {9, 7, 4, 14, 9, 0},
  };
  int sz = res.size();
  for (auto i = 0; i < sz; ++i) {
    for (auto j = 0; j < sz; ++j) {
      EXPECT_EQ(res[i], expected[i]);
    }
  }

  g.LoadGraphFromFile("Tests/TestFiles/graph_ant_3x3_empty");
  res = algorithms.GetShortestPathsBetweenAllVertices(g);
  expected = {
      {0, INF, INF},
      {INF, 0, INF},
      {INF, INF, 0},
  };  // here's no answer
  EXPECT_EQ(res, expected);

  g.LoadGraphFromFile("Tests/TestFiles/graph_0");
  EXPECT_ANY_THROW(algorithms.GetShortestPathsBetweenAllVertices(g));

  g.LoadGraphFromFile("Tests/TestFiles/graph_3_line");
  res = algorithms.GetShortestPathsBetweenAllVertices(g);
  expected = {
      {0, 1, 2},
      {1, 0, 1},
      {2, 1, 0},
  };
  EXPECT_EQ(res, expected);
}

TEST(GraphAlgorithms, Part_3) {
  s21::Graph g;
  s21::GraphAlgorithms algorithms;
  g.LoadGraphFromFile("Tests/TestFiles/test_graph");
  std::vector<std::vector<int>> res;
  res = algorithms.GetLeastSpanningTree(g);
  std::vector<std::vector<int>> expected;

  expected = {
      {0, 2, 0, 5, 0, 0}, {2, 0, 3, 0, 5, 0}, {0, 3, 0, 0, 0, 4},
      {5, 0, 0, 0, 0, 0}, {0, 5, 0, 0, 0, 0}, {0, 0, 4, 0, 0, 0},
  };
  int sz = res.size();
  for (auto i = 0; i < sz; ++i) {
    for (auto j = 0; j < sz; ++j) {
      EXPECT_EQ(res[i], expected[i]);
    }
  }

  g.LoadGraphFromFile("Tests/TestFiles/graph_ant_3x3_empty");
  res = algorithms.GetLeastSpanningTree(g);
  expected = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
  };  // here's no answer
  EXPECT_EQ(res, expected);

  g.LoadGraphFromFile("Tests/TestFiles/graph_0");
  EXPECT_ANY_THROW(algorithms.GetLeastSpanningTree(g));

  g.LoadGraphFromFile("Tests/TestFiles/graph_3_line");
  res = algorithms.GetLeastSpanningTree(g);
  expected = {
      {0, 1, 0},
      {1, 0, 1},
      {0, 1, 0},
  };
  EXPECT_EQ(res, expected);
}
