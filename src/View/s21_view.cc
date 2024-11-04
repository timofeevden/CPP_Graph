#include "s21_view.h"

#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

#include "../Graph/s21_graph.h"
#include "../Graph/s21_graph_algorithms.h"

namespace s21 {

void MainView::DisplayMenu() {
  std::cout << "\033[1;92mSIMPLE NAVIGATOR\033[0m" << std::endl;
  LoadFile();
  DisplayOptions();
}

void MainView::ToMenuOrExit() {
  char status = 0;
  std::cout << "\n\033[1;92mPress 'Q' to exit or any key to return to the "
               "menu\033[0m "
            << std::endl;
  std::cin.clear();
  std::cin >> status;

  if (status == 'q' || status == 'Q') {
    exit(0);
  } else {
    DisplayOptions();
  }
}

void MainView::LoadFile() {
  filename_.clear();
  using namespace std;
  std::cout << "\033[1;92mEnter the name of file:\033[0m " << std::endl;
  std::cin >> filename_;

  if (filename_ == "0") {
    filename_ = "./Tests/TestFiles/graph_ant_3x3_empty";
  } else if (filename_ == "11") {
    filename_ = "./Tests/TestFiles/graph_ant_11";
  } else if (filename_ == "test") {
    filename_ = "./Tests/TestFiles/test.txt";
  }

  std::ifstream file(filename_);
  if (filename_.empty() || !file.good()) {
    ErrorMessage();
    LoadFile();
  } else {
    graph_.LoadGraphFromFile(filename_);
    if (graph_.GetError() == 0) {
      std::cout << "\033[1;92mLoaded Graph:\033[0m " << std::endl;
      graph_.PrintMatrix();
    } else {
      ErrorMessage();
      LoadFile();
    }
  }
}

void MainView::ErrorMessage() {
  if (std::cin.good()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\033[1;31mError. Please, try again.\033[0m " << std::endl;
  } else {
    std::cout << "\033[1;31mInput Error. Exit.\033[0m " << std::endl;
    exit(0);
  }
}

void MainView::DisplayOptions() {
  std::cout
      << "\033[1;92m--------------------- MENU ---------------------\033[0m"
      << std::endl;
  std::cout
      << "\033[1;92m|  1 - Non-recursive DFS from a vertex.         |\033[0m"
      << std::endl;
  std::cout
      << "\033[1;92m|  2 - BFS from a vertex.                       |\033[0m"
      << std::endl;
  std::cout
      << "\033[1;92m|  3 - Shortest path with Dijkstra's.           |\033[0m"
      << std::endl;
  std::cout
      << "\033[1;92m|  4 - Shortest paths with Floyd-Warshall.      |\033[0m"
      << std::endl;
  std::cout
      << "\033[1;92m|  5 - Prim's MST.                              |\033[0m"
      << std::endl;
  std::cout
      << "\033[1;92m|  6 - Traveling Salesman with Ant Colony.      |\033[0m"
      << std::endl;
  std::cout
      << "\033[1;92m|  7 - Comparison of speed of algorithms TSP.    |\033[0m"
      << std::endl;
  std::cout
      << "\033[1;92m|  8 - Load new Graph.                          |\033[0m"
      << std::endl;
  std::cout
      << "\033[1;92m|  9 - Exit.                                    |\033[0m"
      << std::endl;
  std::cout
      << "\033[1;92m-------------------------------------------------\033[0m"
      << std::endl;
  std::cout << "\033[1;92mEnter the option:\033[0m" << std::endl;

  std::cin.clear();
  do {
    std::cin >> option_;
    if (std::cin.fail() || option_ < 1 || option_ > 9) {
      ErrorMessage();
    } else {
      break;
    }
  } while (true);

  PerformOption();
}

void MainView::PerformOption() {
  try {
    switch (option_) {
      case 1:
        BreadthFirstSearch();
        break;
      case 2:
        DepthFirstSearch();
        break;
      case 3:
        GetShortestPathBetweenVertices();
        break;
      case 4:
        GetShortestPathsBetweenAllVertices();
        break;
      case 5:
        GetLeastSpanningTree();
        break;
      case 6:
        SolveTravelingSalesmanProblem();
        break;
      case 7:
        CompareTSP();
        break;
      case 8:
        LoadFile();
        break;
      case 9:
        std::cout << "\033[1;92mExit\033[0m" << std::endl;
        exit(0);
      default:
        ErrorMessage();
        DisplayOptions();
        break;
    }
  } catch (const std::exception& e) {
    std::cerr << "\033[1;31mError: " << e.what() << "\033[0m " << std::endl;
  }
  if (option_ == 8) {
    DisplayOptions();
  } else if (option_ != 9) {
    ToMenuOrExit();
  }
}

void MainView::BreadthFirstSearch() {
  std::cout << "\033[1;92mEnter start point:\033[0m" << std::endl;
  int start;
  std::cin.clear();
  std::cin >> start;
  start -= 1;
  if (start < 0 || start >= graph_.GetSize()) {
    ErrorMessage();
    BreadthFirstSearch();
  } else {
    auto result = algos_.BreadthFirstSearch(graph_, start);
    std::cout << "\033[1;92mResult:\033[0m" << std::endl;
    for (auto i : result) {
      std::cout << i << " ";
    }
  }
}

void MainView::DepthFirstSearch() {
  std::cout << "\033[1;92mEnter start point:\033[0m" << std::endl;
  int start;
  std::cin.clear();
  std::cin >> start;
  start -= 1;
  if (graph_.GetSize() == 0 || graph_.GetError()) {
    std::cout << "\033[1;31mGraph is uncorrect\033[0m " << std::endl;
  } else if (start < 0 || start >= graph_.GetSize()) {
    ErrorMessage();
    DepthFirstSearch();
  } else {
    auto result = algos_.DepthFirstSearch(graph_, start);
    std::cout << "\033[1;92mResult:\033[0m" << std::endl;
    for (auto i : result) {
      std::cout << i << " ";
    }
  }
}

void MainView::GetShortestPathBetweenVertices() {
  std::cout << "\033[1;92mEnter start and end vertices:\033[0m" << std::endl;
  int x, y;
  std::cin.clear();
  std::cin >> x >> y;
  x -= 1;
  y -= 1;
  if (graph_.GetSize() == 0 || graph_.GetError()) {
    std::cout << "\033[1;31mGraph is uncorrect\033[0m " << std::endl;
  } else if (x < 0 || y < 0 || x == y || x >= graph_.GetSize() ||
             y >= graph_.GetSize()) {
    ErrorMessage();
    GetShortestPathBetweenVertices();
  } else {
    auto result = algos_.GetShortestPathBetweenVertices(graph_, x, y);
    if (result == INF) result = 0;
    std::cout << "\033[1;92mResult:\033[0m " << result << std::endl;
  }
}

void MainView::GetShortestPathsBetweenAllVertices() {
  auto result = algos_.GetShortestPathsBetweenAllVertices(graph_);
  std::cout << "\033[1;92mResult:\033[0m" << std::endl;
  for (auto i : result) {
    for (auto j : i) {
      if (j == INF) j = 0;
      std::cout << j << " ";
    }
    std::cout << std::endl;
  }
}

void MainView::GetLeastSpanningTree() {
  auto result = algos_.GetLeastSpanningTree(graph_);
  std::cout << "\033[1;92mResult:\033[0m" << std::endl;
  for (auto i : result) {
    for (auto j : i) {
      if (j == INF) j = 0;
      std::cout << j << " ";
    }
    std::cout << std::endl;
  }
}

void MainView::SolveTravelingSalesmanProblem() {
  auto result = algos_.SolveTravelingSalesmanProblem(graph_);
  auto sz = result.vertices.size();
  std::cout << "\033[1;92mResult:\033[0m" << std::endl;
  for (size_t i = 0; i < sz; ++i) {
    std::cout << result.vertices[i];
    if (i != sz - 1) {
      std::cout << " - ";
    }
  }
  std::cout << "\nDistance: " << result.distance << std::endl;
}

void MainView::CompareTSP() {
  int n = 0;
  std::cout << "\033[1;92mNumber of repetitions:\033[0m" << std::endl;
  std::cin.clear();
  std::cin >> n;
  if (n <= 0) {
    ErrorMessage();
    CompareTSP();
  } else {
    std::cout << std::endl;
    auto res = performAlgorithm(
        n, [&]() { algos_.SolveTravelingSalesmanProblem(graph_); });
    std::cout << "1) Ant Colony Algorithm result: "
              << round(res * 100000) / 100000 << " sec." << std::endl;
    res = performAlgorithm(
        n, [&]() { algos_.GreedySolveTravelingSalesmanProblem(graph_); });
    std::cout << "2) Greedy Algorithm result: " << round(res * 100000) / 100000
              << " sec." << std::endl;
    res = performAlgorithm(
        n, [&]() { algos_.FullSolveTravelingSalesmanProblem(graph_); });
    std::cout << "3) Full Solve Algorithm result: "
              << round(res * 100000) / 100000 << " sec." << std::endl;
  }
}

double MainView::performAlgorithm(int n, std::function<void()> algorithm) {
  double total_time = 0.0;
  if (n > 0) {
    while (n--) {
      auto start = std::chrono::high_resolution_clock::now();
      algorithm();
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> duration = end - start;
      total_time += duration.count();
    }
  }
  return total_time;
}

}  // namespace s21
