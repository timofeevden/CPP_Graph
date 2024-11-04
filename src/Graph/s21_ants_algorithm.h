#ifndef SRC_GRAPH_S21_ANTS_ALGORITHM_H
#define SRC_GRAPH_S21_ANTS_ALGORITHM_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "s21_graph.h"

#define CNT_ITERATIONS 1000
#define CNT_ANTS (size_ * 2)

namespace s21 {

struct TsmResult {
  std::vector<int> vertices;
  double distance = 0;
};

class AntsAlgorithm {
 public:
  TsmResult FindPath(const s21::Graph* graph);

 private:
  void InitStartPheromones();
  void InitEmptyAnts();
  void SendAnts();
  std::vector<int> FindNeighbours(int point, std::vector<bool>& visited);
  bool UpdateBestWay();
  void UpdatePheromones();
  void GoNextStep(std::vector<int>& neighbours, s21::Matrix& wishes,
                  s21::TsmResult& ant, std::vector<bool>& visited,
                  int& current_point);
  void GoLastStep(s21::TsmResult& ant, std::vector<bool>& visited,
                  int current_point, int start_point);
  void FindWaysWishes(s21::Matrix& wishes, const std::vector<int>& neighbours,
                      int current_point);
  void UpdateLocalPheromones(s21::TsmResult& ant);
  void NumberPoints(TsmResult& result);

 private:
  const s21::Graph* graph_;
  int size_;
  std::vector<TsmResult> ants_;
  s21::Matrix pheromons_;
  s21::Matrix pheromons_local_;
  double start_pheromone_ = 0.1;
  double alpha_ = 1;
  double beta_ = 4;
  double Q_ = 1;  //  коэф-т для желания при дистанции, зависит от графа
  double p_ = 0.4;  //  испарение
  s21::TsmResult best_way_;
};

}  // namespace s21

#endif  // SRC_GRAPH_S21_ANTS_ALGORITHM_H
