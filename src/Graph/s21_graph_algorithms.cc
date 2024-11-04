#include "s21_graph_algorithms.h"

namespace s21 {

///////////////////////// PART 1  //////////////////////////////////////

//  нерекурентный поиск в глубину в графе от заданной вершины.
//  Функция должна возвращать массив, содержащий в себе обойдённые вершины в
//  порядке их обхода. При реализации этой функции обязательно использовать
//  самописную структуру данных стек, которую предварительно стоит оформить в
//  виде отдельной статической библиотеки

std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph &graph,
                                                   int start_vertex) {
  int size = graph.GetSize();

  if (size == 0 || graph.GetError()) {
    throw std::invalid_argument("Graph is uncorrect");
  } else if (start_vertex < 0 || start_vertex >= size) {
    throw std::invalid_argument("Incorrect start_vertex in DepthFirstSearch");
  }

  std::vector<int> visited;
  RecurseDfs(graph, start_vertex, visited);
  DoNumberPoints(visited);

  return visited;
}

void GraphAlgorithms::RecurseDfs(const Graph &graph, int vertex,
                                 std::vector<int> &visited) {
  visited.push_back(vertex);  //  запоминаем посещенную вершину
  s21::stack<int> neighbours;

  for (int i = 0; i < graph.GetSize(); ++i) {
    if (graph(vertex, i) != 0) {
      neighbours.push(i);  //  запоминаем соседей в стек
    }
  }

  while (!neighbours.empty()) {  //  разворачиваем стек, смотрим соседей
    if (!IsVisited(neighbours.top(), visited)) {
      RecurseDfs(graph, neighbours.top(),
                 visited);  //  смотрим соседей у соседей
    }
    neighbours.pop();
  }
}

bool GraphAlgorithms::IsVisited(int vertex, const std::vector<int> &visited) {
  size_t size = visited.size();
  if (size > 0) {
    for (size_t i = 0; i < size; ++i) {
      if (visited[i] == vertex) {
        return true;
      }
    }
  }

  return false;
}

void GraphAlgorithms::DoNumberPoints(std::vector<int> &points) {
  for (auto &name : points) {
    name += 1;  //  нумерация точек
  }
}

//  поиск в ширину в графе от заданной вершины. Функция должна возвращать
//  массив, содержащий в себе обойдённые вершины в порядке их обхода. При
//  реализации этой функции обязательно использовать самописную структуру данных
//  очередь, которую предварительно стоит оформить в виде отдельной статической
//  библиотеки.
std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph &graph,
                                                     int start_vertex) {
  int size = graph.GetSize();

  if (size == 0 || graph.GetError()) {
    throw std::invalid_argument("Graph is uncorrect");
  } else if (start_vertex < 0 || start_vertex >= size) {
    throw std::invalid_argument("Incorrect start_vertex in BreadthFirstSearch");
  }

  std::vector<int> visited = {start_vertex};
  s21::queue<int> q;
  q.push(start_vertex);

  while (!q.empty()) {
    int vertex = q.front();
    q.pop();

    for (int i = 0; i < size; ++i) {
      if (graph(vertex, i) != 0 && !IsVisited(i, visited)) {
        visited.push_back(i);
        q.push(i);
      }
    }
  }

  DoNumberPoints(visited);

  return visited;
}

///////////////////////////////////// PART 2
///////////////////////////////////////////////

//  поиск кратчайшего пути между двумя вершинами в графе с использованием
//  алгоритма Дейкстры. Функция принимает на вход номера двух вершин и
//  возвращает численный результат, равный наименьшему расстоянию между ними.

int GraphAlgorithms::GetShortestPathBetweenVertices(s21::Graph &graph,
                                                    int vertex1, int vertex2) {
  int sz = graph.GetSize();
  if (sz <= 0 || graph.GetError()) {
    throw std::invalid_argument("Invalid Graph");
  } else if (vertex1 < 0 || vertex2 < 0 || vertex2 > sz || vertex1 > sz) {
    throw std::invalid_argument("Invalid verticies");
  }

  std::vector<int> costs(sz, INF);         // graph weights
  costs[vertex1] = 0;                      // init zero for start
  std::vector<bool> processed(sz, false);  // processed Vs
  int cost = INF;
  int nearest = vertex1;
  do {
    cost = INF;
    for (auto j = 0; j != sz; ++j) {
      if (!processed[j] &&
          costs[j] < cost) {  // compare non-visited to find min
        cost = costs[j];
        nearest = j;  // mark as min
      }
    }
    for (auto j = 0; j != sz; ++j) {
      if (graph(nearest, j) && costs[nearest] + graph(nearest, j) < costs[j])
        costs[j] = costs[nearest] + graph(nearest, j);  // relaxation
    }

    processed[nearest] = true;  // mark V as processed
  } while (cost != INF);

  return costs[vertex2];
}

// поиск кратчайших путей между всеми парами вершин в графе с использованием
// алгоритма Флойда-Уоршелла. В качестве результата функция возвращает матрицу
// кратчайших путей между всеми вершинами графа.

std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(s21::Graph &graph) {
  int sz = graph.GetSize();  // graph order
  if (sz <= 0 || graph.GetError()) throw std::invalid_argument("Invalid graph");

  std::vector<std::vector<int>> costs(sz, std::vector<int>(sz, INF));
  for (auto i = 0; i != sz; ++i) {  // copy graph, init costs
    for (auto j = 0; j != sz; ++j) {
      ;
      if (j == i)
        costs[i][j] = 0;
      else if (graph(i, j)) {
        costs[i][j] = graph(i, j);
      }
    }
  }

  for (int k = 0; k < sz; ++k) {
    for (int i = 0; i < sz; ++i) {
      for (int j = 0; j < sz; ++j) {
        if (costs[i][k] < INF && costs[k][j] < INF) {  // check of overloaded
          costs[i][j] = std::min(costs[i][j], costs[i][k] + costs[k][j]);
        }
      }
    }
  }
  return costs;
}

//////////////////////////////  Part 3. Поиск минимального остовного дерева
/////////////////////////////////////

// GetLeastSpanningTree(Graph &graph) — поиск наименьшего остовного дерева в
// графе с помощью алгоритма Прима.
// В качестве результата функция должна возвращать матрицу смежности для
// минимального остовного дерева

std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(
    s21::Graph &graph) {
  int sz = graph.GetSize();
  if (sz <= 0 || graph.GetError()) throw std::invalid_argument("Invalid graph");

  std::vector<std::vector<int>> mst(
      sz, std::vector<int>(sz, 0));  // minimum spanning tree
  std::vector<bool> processed(sz, false);
  processed[0] = true;
  int counter = sz;
  int sum = 0;

  while (--counter) {  // Process all Vs
    int min_weight = INF;
    int min_V = INF;
    int parent_V = INF;

    for (int i = 0; i < sz; ++i) {
      if (processed[i]) {
        for (int j = 0; j < sz; ++j) {
          if (!processed[j] && graph(i, j) != 0 && graph(i, j) < min_weight) {
            min_weight = graph(i, j);
            min_V = j;
            parent_V = i;
          }
        }
      }
    }

    if (min_V != INF) {  // if V is found
      mst[parent_V][min_V] = min_weight;
      mst[min_V][parent_V] = min_weight;
      sum += min_weight;
      processed[min_V] = true;
    }
  }
  return mst;
}

///////////////////////// PART 4    //////////////////////////////////////

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(const Graph &graph) {
  if (graph.GetSize() == 0 || graph.GetError()) {
    throw std::invalid_argument("Graph is uncorrect");
  }

  s21::AntsAlgorithm ants;
  s21::TsmResult path = ants.FindPath(&graph);

  return path;
}

///////////////////////////     PART 6 FIRST ALGORITHM
//////////////////////////////////////////////////////////

TsmResult GraphAlgorithms::GreedySolveTravelingSalesmanProblem(
    const Graph &graph) {
  int size = graph.GetSize();
  if (size == 0 || graph.GetError()) {
    throw std::invalid_argument("Graph is uncorrect");
  }

  s21::TsmResult result, path;
  path.vertices.reserve(size);
  std::vector<std::pair<int, int>> neighbours;
  neighbours.reserve(size);

  for (int start_point = 0; start_point < size;
       ++start_point) {  //  перебираем стартовые точки
    int current_point = start_point;
    std::vector<bool> visited(size, false);
    visited[start_point] = true;
    path.vertices.clear();
    path.distance = 0;
    path.vertices.push_back(start_point);

    for (int i = 0; i < size; ++i) {  //  перебираем путь
      neighbours = FindNeighbours(graph, current_point, visited, size);

      if (neighbours.empty() == false) {
        //  cмотрим у кого минимальное расстояние у соседей
        GoToMinDistance(neighbours, visited, current_point, path);
      } else if (i == size - 1 && path.distance > 0) {
        //  смотрим последнего соседа, должен быть стартовый
        GoLastStep(graph, visited, current_point, start_point, path);
      } else {
        break;  //  тупик, смотрим след итерацию
      }
    }
    if (isAllVisited(visited) &&
        (result.distance == 0 || result.distance > path.distance)) {
      result.vertices = std::move(path.vertices);  //  обновляем результат
      result.distance = path.distance;
    }
  }  //  завершили смотреть все маршруты
  DoNumberPoints(result.vertices);  //  нумерация точек

  return result;
}

std::vector<std::pair<int, int>> GraphAlgorithms::FindNeighbours(
    const Graph &graph, int point, const std::vector<bool> &visited, int size) {
  std::vector<std::pair<int, int>> neighbours;

  for (int i = 0; i < size; ++i) {  //  смотрим непосещенных соседей
    if (graph.At(point, i) != 0 && i != point && visited[i] == false) {
      neighbours.push_back({i, graph.At(point, i)});
    }
  }
  return neighbours;
}

void GraphAlgorithms::GoToMinDistance(
    std::vector<std::pair<int, int>> &neighbours, std::vector<bool> &visited,
    int &current_point, TsmResult &path) {
  size_t amount = neighbours.size();

  if (amount) {
    std::pair<int, int> min = {neighbours[0].first, neighbours[0].second};

    for (size_t i = 1; i < amount; ++i) {  //  смотрим непосещенных соседей
      if (neighbours[i].second < min.second) {
        min.first = neighbours[i].first;
        min.second = neighbours[i].second;
      }
    }
    path.vertices.push_back(min.first);
    path.distance += min.second;
    current_point = min.first;
    visited[current_point] = true;
  }
}

void GraphAlgorithms::GoLastStep(const Graph &graph, std::vector<bool> &visited,
                                 int current_point, int start_point,
                                 TsmResult &path) {
  if (graph.At(current_point, start_point) != 0) {
    path.vertices.push_back(start_point);
    path.distance += graph.At(current_point, start_point);
  } else {
    visited[start_point] = false;
  }
}

bool GraphAlgorithms::IsVisited(int vertex, const std::vector<bool> &visited) {
  if (visited[vertex] == true) return true;

  return false;
}

bool GraphAlgorithms::isAllVisited(const std::vector<bool> &visited) {
  size_t size = visited.size();
  for (size_t v = 0; v < size; ++v) {
    if (visited[v] == false) return false;
  }

  return true;
}

///////////////////////////     PART 6 SECOND ALGORITHM
//////////////////////////////////////////////////////////

TsmResult GraphAlgorithms::FullSolveTravelingSalesmanProblem(
    const Graph &graph) {
  int size = graph.GetSize();
  if (size == 0 || graph.GetError()) {
    throw std::invalid_argument("Graph is uncorrect");
  }

  s21::TsmResult result, path;
  path.vertices.reserve(size);
  std::vector<bool> visited(size, false);

  FullRecursiveWays(graph, size, path, result, visited);
  DoNumberPoints(result.vertices);  //  нумерация точек

  return result;
}

void GraphAlgorithms::FullRecursiveWays(const Graph &graph, int size,
                                        TsmResult &path, TsmResult &best_way,
                                        std::vector<bool> &visited) {
  if ((int)path.vertices.size() == size) {
    if (graph(path.vertices.back(), path.vertices[0]) != 0) {
      path.distance += graph(path.vertices.back(), path.vertices[0]);
      path.vertices.push_back(path.vertices[0]);
      if (path.distance < best_way.distance || best_way.distance == 0) {
        best_way.distance = path.distance;
        best_way.vertices = path.vertices;  //  сохраняем лучший результат
      }
      path.vertices.pop_back();  //  откатываемся назад
      path.distance -= graph(path.vertices.back(), path.vertices[0]);
    }
    return;  //  выходим из маршрута
  }
  for (int i = 0; i < size; ++i) {
    if (IsVisited(i, visited) == false &&
        ((path.distance == 0 && path.vertices.size() == 1) ||
         (graph(path.vertices.back(), i)))) {
      path.vertices.push_back(i);  // добавляем точку в путь
      int tmp_distance = 0;
      if (path.vertices.size() > 1) {
        tmp_distance = graph(path.vertices[path.vertices.size() - 2], i);
      }
      path.distance += tmp_distance;
      visited[i] = true;

      if (path.distance < best_way.distance || best_way.distance == 0) {
        FullRecursiveWays(graph, size, path, best_way, visited);
      }
      if (path.vertices.size() > 1) {
        tmp_distance = graph(path.vertices[path.vertices.size() - 2], i);
      }
      path.vertices.pop_back();  // откатываемся к пред точке
      path.distance -= tmp_distance;
      visited[i] = false;
    }
  }
}

}  // namespace s21