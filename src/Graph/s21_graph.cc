#include "s21_graph.h"

namespace s21 {

Graph::Graph() : error_(0), name_("graphname"), directed_graph_(false) {}

Graph::~Graph() { Clear(); }

void Graph::LoadGraphFromFile(const std::string& filename) {
  Clear();
  name_ = "graphname";
  std::ifstream file(filename);

  if (file.is_open()) {
    int tmp_int = 0;
    file >> tmp_int;

    if (tmp_int > 0 && !file.eof()) {
      int size = tmp_int;
      matrix_.Resize(size);

      for (int i = 0; i < size && !error_ && !file.eof(); ++i) {
        for (int j = 0; j < size && !error_ && !file.eof(); ++j) {
          file >> tmp_int;
          if (file.peek() == '\n' && j != size - 1) {
            error_ = 3;
            break;
          }
          matrix_(i, j) = tmp_int;
          // if (directed_graph_ == false && (tmp_int && matrix_(j, i))) {
          //   directed_graph_ = true;  //  направленный граф
          // }
        }
        char new_line = 0;
        file.get(new_line);

        if (i != size - 1 &&
            (new_line != '\n' && new_line != 13 && new_line != 0)) {
          error_ = 3;  //  std::cout << "BAD SYMBOL\n";
        }
      }
      directed_graph_ = IsDigraph();
    } else if (tmp_int != 0) {
      error_ = 2;  //  std::cout << "BAD SIZES or eof!\n";
    }
    file.close();
  } else {
    error_ = 1;  //  std::cout << "Cant open file!\n";
  }
}

bool Graph::IsDigraph() {
  if (!error_) {
    int size = matrix_.GetSize();
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (((!!matrix_(i, j)) ^ (!!matrix_(j, i))) == 1) {
          return true;
        }
      }
    }
  }
  return false;
}

void Graph::ExportGraphToDot(const std::string& filename) {
  std::ofstream file(filename);

  if (file.is_open()) {
    file << (directed_graph_ ? "digraph " : "graph ") << name_ << " {\n";
    int size = matrix_.GetSize();
    //  список всех вершин
    for (int i = 0; i < size; ++i) {
      file << "\t" << PointName(i) << ";\n";
    }
    //  список направлений
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (matrix_(i, j)) {
          file << "\t" << PointName(i) << (directed_graph_ ? " -> " : " -- ")
               << PointName(j) << ";\n";
        }
      }
    }
    file << "}\n";
    file.close();
  }
}

void Graph::Clear() {
  matrix_.Clear();
  directed_graph_ = false;
  error_ = 0;
}

void Graph::PrintMatrix() { matrix_.PrintMatrix(); }

std::string Graph::PointName(int n) {
  std::string point_name = "";

  do {
    point_name += char('a' + (n % 26));
    n /= 26;
  } while (n);

  return point_name;
}

void Graph::SetName(const std::string& new_name) { name_ = new_name; }

int Graph::operator()(int i, int j) const { return matrix_(i, j); }

int Graph::At(int i, int j) const { return matrix_(i, j); }

int Graph::GetSize() const noexcept { return matrix_.GetSize(); }

int Graph::GetError() const noexcept { return error_; }

}  // namespace s21