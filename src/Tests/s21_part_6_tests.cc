#include "s21_tests.h"

///////////////////// First algorithm ///////////////////////////////

TEST(GraphAlgorithms, Part_6_1_empty) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_3x3_empty");

  s21::TsmResult res;
  res = algorithms.GreedySolveTravelingSalesmanProblem(graph);

  EXPECT_EQ(res.distance, 0);
}

TEST(GraphAlgorithms, Part_6_1_empty_0) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_0");

  EXPECT_ANY_THROW(algorithms.GreedySolveTravelingSalesmanProblem(graph));
}

TEST(GraphAlgorithms, Part_6_1_5) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_5");

  s21::TsmResult res;
  res = algorithms.GreedySolveTravelingSalesmanProblem(graph);

  /*

  std::cout << "\n RESULT: " << "\n";
  for (long unsigned int i = 0; i < res.vertices.size(); ++i) {
    std::cout << res.vertices[i] << " ";
  }
  std::cout << "DISTANCE = " << res.distance << "\n";
  std::cout << "\n";
  */

  EXPECT_EQ(res.distance, 5);
}

TEST(GraphAlgorithms, Part_6_1_3) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_3_line");

  s21::TsmResult res;
  res = algorithms.GreedySolveTravelingSalesmanProblem(graph);

  /*
    std::cout << "\n RESULT: " << "\n";
    for (long unsigned int i = 0; i < res.vertices.size(); ++i) {
      std::cout << res.vertices[i] << " ";
    }
    std::cout << "DISTANCE = " << res.distance << "\n";
    std::cout << "\n";
    */

  EXPECT_EQ(res.distance, 0);
}

TEST(GraphAlgorithms, Part_6_1_6_different) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_6_different");

  s21::TsmResult res;
  res = algorithms.GreedySolveTravelingSalesmanProblem(graph);

  /*
    std::cout << "\n RESULT: " << "\n";
    for (long unsigned int i = 0; i < res.vertices.size(); ++i) {
      std::cout << res.vertices[i] << " ";
    }
    std::cout << "DISTANCE = " << res.distance << "\n";
    std::cout << "\n";
    */

  EXPECT_EQ(res.distance, 0);
}

TEST(GraphAlgorithms, Part_6_1_11) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_11");

  s21::TsmResult res;
  res = algorithms.GreedySolveTravelingSalesmanProblem(graph);

  /*
    std::cout << "\n RESULT: " << "\n";
    for (long unsigned int i = 0; i < res.vertices.size(); ++i) {
      std::cout << res.vertices[i] << " ";
    }
    std::cout << "DISTANCE = " << res.distance << "\n";
    std::cout << "\n";
  */
  EXPECT_EQ(res.distance, 255);
}

TEST(GraphAlgorithms, Part_6_1_20) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_20");

  s21::TsmResult res;
  res = algorithms.GreedySolveTravelingSalesmanProblem(graph);

  /*
    std::cout << "\n RESULT: " << "\n";
    for (long unsigned int i = 0; i < res.vertices.size(); ++i) {
      std::cout << res.vertices[i] << " ";
    }
    std::cout << "DISTANCE = " << res.distance << "\n";
    std::cout << "\n";
    */

  EXPECT_EQ(res.distance, 63);
}

///////////////////// Second algorithm ///////////////////////////////

TEST(GraphAlgorithms, Part_6_2_empty) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_3x3_empty");

  s21::TsmResult res;
  res = algorithms.FullSolveTravelingSalesmanProblem(graph);

  EXPECT_EQ(res.distance, 0);
}

TEST(GraphAlgorithms, Part_6_2_empty_0) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_0");

  EXPECT_ANY_THROW(algorithms.FullSolveTravelingSalesmanProblem(graph));
}

TEST(GraphAlgorithms, Part_6_2_5) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_5");

  s21::TsmResult res;
  res = algorithms.FullSolveTravelingSalesmanProblem(graph);

  /*
    std::cout << "\n RESULT: " << "\n";
    for (long unsigned int i = 0; i < res.vertices.size(); ++i) {
      std::cout << res.vertices[i] << " ";
    }
    std::cout << "DISTANCE = " << res.distance << "\n";
    std::cout << "\n";
    */

  EXPECT_EQ(res.distance, 5);
}

TEST(GraphAlgorithms, Part_6_2_3) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_3_line");

  s21::TsmResult res;
  res = algorithms.FullSolveTravelingSalesmanProblem(graph);
  /*
    std::cout << "\n RESULT: " << "\n";
    for (long unsigned int i = 0; i < res.vertices.size(); ++i) {
      std::cout << res.vertices[i] << " ";
    }
    std::cout << "DISTANCE = " << res.distance << "\n";
    std::cout << "\n";
  */

  EXPECT_EQ(res.distance, 0);
}

TEST(GraphAlgorithms, Part_6_2_6_different) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_6_different");
  s21::TsmResult res;
  res = algorithms.FullSolveTravelingSalesmanProblem(graph);

  EXPECT_EQ(res.distance, 0);
}

/*
  //  253
TEST(GraphAlgorithms, Part_6_2_11) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_11");

  s21::TsmResult res;
  res = algorithms.FullSolveTravelingSalesmanProblem(graph);


  std::cout << "\n RESULT: " << "\n";
  for (long unsigned int i = 0; i < res.vertices.size(); ++i) {
    std::cout << res.vertices[i] << " ";
  }
  std::cout << "DISTANCE = " << res.distance << "\n";
  std::cout << "\n";

  EXPECT_EQ(res.distance, 253);
}
*/

/*  //  Часа 2   ответ 61
TEST(GraphAlgorithms, Part_6_2_20) {

  s21::Graph graph;
  s21::GraphAlgorithms algorithms;


  graph.LoadGraphFromFile("Tests/TestFiles/graph_20");


  s21::TsmResult res;
  res = algorithms.FullSolveTravelingSalesmanProblem(graph);


  std::cout << "\n RESULT: " << "\n";
  for (long unsigned int i = 0; i < res.vertices.size(); ++i) {
    std::cout << res.vertices[i] << " ";
  }
  std::cout << "DISTANCE = " << res.distance << "\n";
  std::cout << "\n";


  EXPECT_EQ(res.distance, 61);
}
*/
