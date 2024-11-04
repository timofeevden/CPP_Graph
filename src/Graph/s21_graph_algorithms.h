#ifndef SRC_S21_GRAPH_ALGORITHMS_H
#define SRC_S21_GRAPH_ALGORITHMS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../Containers/s21_queue.h"
#include "../Containers/s21_stack.h"
#include "s21_ants_algorithm.h"
#include "s21_graph.h"

namespace s21 {

class GraphAlgorithms {
 public:
  // part 1
  std::vector<int> DepthFirstSearch(const Graph &graph, int start_vertex);
  std::vector<int> BreadthFirstSearch(const Graph &graph, int start_vertex);
  //   part 2
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      s21::Graph &graph);
  int GetShortestPathBetweenVertices(s21::Graph &graph, int vertex1,
                                     int vertex2);
  // part 3
  std::vector<std::vector<int>> GetLeastSpanningTree(s21::Graph &graph);

  TsmResult SolveTravelingSalesmanProblem(const Graph &graph);
  TsmResult GreedySolveTravelingSalesmanProblem(const Graph &graph);
  TsmResult FullSolveTravelingSalesmanProblem(const Graph &graph);

 private:
  // part 1
  void RecurseDfs(const Graph &graph, int vertex, std::vector<int> &visited);
  bool IsVisited(int vertex, const std::vector<int> &visited);
  void DoNumberPoints(std::vector<int> &points);

  //   part 4 first
  std::vector<std::pair<int, int>> FindNeighbours(
      const Graph &graph, int point, const std::vector<bool> &visited,
      int size);
  void GoToMinDistance(std::vector<std::pair<int, int>> &neighbours,
                       std::vector<bool> &visited, int &current_point,
                       TsmResult &path);
  void GoLastStep(const Graph &graph, std::vector<bool> &visited,
                  int current_point, int start_point, TsmResult &path);
  bool IsVisited(int vertex, const std::vector<bool> &visited);
  bool isAllVisited(const std::vector<bool> &visited);
  //   part 4 second
  void FullRecursiveWays(const Graph &graph, int size, TsmResult &path,
                         TsmResult &best_way, std::vector<bool> &visited);

 private:
  const int INF = std::numeric_limits<int>::max();
};

}  // namespace s21

#endif  // SRC_S21_GRAPH_ALGORITHMS_H
