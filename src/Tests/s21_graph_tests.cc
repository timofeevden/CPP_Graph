#include "s21_tests.h"

TEST(Graph, Graph_Test_3) {
  s21::Graph graph;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_3x3");

  EXPECT_EQ(graph.GetSize(), 3);
  EXPECT_EQ(graph.GetError(), 0);

  graph.PrintMatrix();

  graph.SetName("NEW_NAME");
  graph.ExportGraphToDot("Tests/TestFiles/Export/exort_graph_3x3");
}

TEST(Graph, Graph_Test_test) {
  s21::Graph graph;

  graph.LoadGraphFromFile("Tests/TestFiles/test.txt");

  EXPECT_EQ(graph.GetSize(), 6);
  EXPECT_EQ(graph.GetError(), 0);

  graph.PrintMatrix();

  graph.ExportGraphToDot("Tests/TestFiles/Export/exort_test");
}

TEST(Graph, Graph_Test_3_empty) {
  s21::Graph graph;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_3x3_empty");

  EXPECT_EQ(graph.GetSize(), 3);
  EXPECT_EQ(graph.GetError(), 0);

  graph.ExportGraphToDot("Tests/TestFiles/Export/exort_graph_ant_3x3_empty");
}

TEST(Graph, Graph_Test_0_empty) {
  s21::Graph graph;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_0");

  EXPECT_EQ(graph.GetSize(), 0);
  EXPECT_EQ(graph.GetError(), 0);

  graph.ExportGraphToDot("Tests/TestFiles/Export/exort_graph_0");
}

TEST(Graph, Graph_Test_6_different) {
  s21::Graph graph;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_6_different");

  EXPECT_EQ(graph.GetSize(), 6);
  EXPECT_EQ(graph.GetError(), 0);

  graph.ExportGraphToDot("Tests/TestFiles/Export/exort_graph_6_different");
}

TEST(Graph, Graph_Test_11) {
  s21::Graph graph;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_ant_11");

  EXPECT_EQ(graph.GetSize(), 11);
  EXPECT_EQ(graph.GetError(), 0);

  graph.ExportGraphToDot("Tests/TestFiles/Export/exort_graph_ant_11");
}

/////////////// TESTS WITH ERRORS /////////////////////

TEST(Graph, Graph_Test_Error_1_no_file) {
  s21::Graph graph;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_no_file");
  EXPECT_EQ(graph.GetError(), 1);
}

TEST(Graph, Graph_Test_Error_2) {
  s21::Graph graph;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_error_2");
  EXPECT_EQ(graph.GetError(), 2);
}

TEST(Graph, Graph_Test_Error_2_second) {
  s21::Graph graph;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_error_2_second");
  EXPECT_EQ(graph.GetError(), 2);
}

TEST(Graph, Graph_Test_Error_3) {
  s21::Graph graph;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_error_3");
  EXPECT_EQ(graph.GetError(), 3);
}

TEST(Graph, Graph_Test_Error_3_second) {
  s21::Graph graph;

  graph.LoadGraphFromFile("Tests/TestFiles/graph_error_3_second");
  EXPECT_EQ(graph.GetError(), 3);
}