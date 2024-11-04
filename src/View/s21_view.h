#ifndef A2_SIMPLENAVIGATOR_S21_VIEW_H_
#define A2_SIMPLENAVIGATOR_S21_VIEW_H_

#include <functional>
#include <string>

#include "../Graph/s21_graph.h"
#include "../Graph/s21_graph_algorithms.h"

namespace s21 {
class MainView {
 public:
  void DisplayMenu();
  void LoadFile();
  void ErrorMessage();
  void DisplayOptions();
  void PerformOption();
  void PrintResult();
  void BreadthFirstSearch();
  void DepthFirstSearch();
  void GetShortestPathBetweenVertices();
  void GetShortestPathsBetweenAllVertices();
  void GetLeastSpanningTree();
  void SolveTravelingSalesmanProblem();
  void ToMenuOrExit();
  void CompareTSP();
  double performAlgorithm(int n, std::function<void()> algorithm);

 private:
  std::string filename_;
  int option_;
  Graph graph_;
  GraphAlgorithms algos_;
  const int INF = std::numeric_limits<int>::max();
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_S21_VIEW_H_
