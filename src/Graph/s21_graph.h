#ifndef SRC_S21_GRAPH_H
#define SRC_S21_GRAPH_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../Containers/s21_matrix.h"

namespace s21 {

class Graph {
 public:
  Graph();
  ~Graph();
  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename);
  void PrintMatrix();
  void SetName(const std::string& new_name);
  int GetSize() const noexcept;
  int GetError() const noexcept;
  int operator()(int i, int j) const;
  int At(int i, int j) const;

 private:
  void Clear();
  bool IsDigraph();
  std::string PointName(int n);

 private:
  Matrix matrix_;
  int error_;
  std::string name_;
  bool directed_graph_;
};

}  // namespace s21

#endif  // SRC_S21_GRAPH_H
