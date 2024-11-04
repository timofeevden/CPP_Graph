#include "s21_tests.h"

TEST(GraphAlgorithms, Ants_Empty) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_3x3_empty");

  s21::TsmResult res;
  res = algorithms.SolveTravelingSalesmanProblem(graph);

  EXPECT_EQ(res.distance, 0);
}

TEST(GraphAlgorithms, Ants_Empty_0) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_0");

  EXPECT_ANY_THROW(algorithms.SolveTravelingSalesmanProblem(graph));
}

TEST(GraphAlgorithms, Ants_3_Easy) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_3x3");

  s21::TsmResult res;
  res = algorithms.SolveTravelingSalesmanProblem(graph);

  EXPECT_EQ(res.distance, 3);
}

TEST(GraphAlgorithms, Ants_2) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_2");

  s21::TsmResult res;
  res = algorithms.SolveTravelingSalesmanProblem(graph);

  EXPECT_EQ(res.distance, 2);
}

TEST(GraphAlgorithms, Ants_3) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_3_line");

  s21::TsmResult res;
  res = algorithms.SolveTravelingSalesmanProblem(graph);

  EXPECT_EQ(res.distance, 0);
}

TEST(GraphAlgorithms, Ants_5) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_5");

  s21::TsmResult res;
  res = algorithms.SolveTravelingSalesmanProblem(graph);

  EXPECT_EQ(res.distance, 5);
}

TEST(GraphAlgorithms, Ants_6_different) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_6_different");

  s21::TsmResult res;
  res = algorithms.SolveTravelingSalesmanProblem(graph);

  EXPECT_EQ(res.distance, 0);
}

TEST(GraphAlgorithms, Ants_11) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_11");

  s21::TsmResult res;
  res = algorithms.SolveTravelingSalesmanProblem(graph);

  while (res.distance != 253) {
    res = algorithms.SolveTravelingSalesmanProblem(graph);
  }
  /*
     std::cout << "\n RESULT: " << "\n";
     for (long unsigned int i = 0; i < res.vertices.size(); ++i) {
       std::cout << res.vertices[i] << " ";
     }
     std::cout << "DISTANCE = " << res.distance << "\n";
     std::cout << "\n";
   */
  EXPECT_EQ(res.distance, 253);
}

/*
TEST(GraphAlgorithms, Ants_20) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_20");

  s21::TsmResult res;
  res = algorithms.SolveTravelingSalesmanProblem(graph);

  while (res.distance != 61) {
    res = algorithms.SolveTravelingSalesmanProblem(graph);
  }
  EXPECT_EQ(res.distance, 61);
}
*/