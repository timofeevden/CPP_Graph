#include "s21_graph_algorithms.h"

namespace s21 {

TsmResult AntsAlgorithm::FindPath(const s21::Graph* graph) {
  graph_ = graph;
  size_ = graph_->GetSize();
  Q_ = size_ * 10;
  pheromons_.Clear();
  pheromons_.Resize(size_);  //  создаем карту феромонов
  pheromons_local_.Clear();
  pheromons_local_.Resize(size_);
  InitStartPheromones();
  ants_.clear();  //  создаем муравьев
  ants_.resize(CNT_ANTS);
  best_way_.vertices.clear();
  best_way_.distance = 0;
  srand((int)time(0));
  int cnt = 0;

  while (cnt++ != CNT_ITERATIONS) {
    InitEmptyAnts();
    SendAnts();  //  проходим пути муравьями и оставляем феромоны
    UpdatePheromones();  //  обновляем феромоны

    if (UpdateBestWay()) {  //  обновляем результат
      cnt = 0;
    }
  }

  NumberPoints(best_way_);
  return best_way_;
}

void AntsAlgorithm::InitStartPheromones() {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (graph_->At(i, j) != 0) {
        pheromons_(i, j) = start_pheromone_;
      }
    }
  }
}

void AntsAlgorithm::InitEmptyAnts() {
  for (int i = 0; i < CNT_ANTS; ++i) {
    ants_[i].vertices.clear();
    ants_[i].vertices.reserve(size_ + 1);
    ants_[i].distance = 0;
  }
}

void AntsAlgorithm::SendAnts() {
  pheromons_local_.Fill(0);
  s21::Matrix wishes(size_, 0);
  std::vector<int> neighbours;
  neighbours.reserve(size_);
  int start_point = -1;

  for (TsmResult& ant : ants_) {
    std::vector<bool> visited(size_, false);
    wishes.Fill(0);
    ant.vertices.clear();
    ant.distance = 0;
    start_point >= size_ - 1 ? start_point = 0 : start_point += 1;
    int current_point = start_point;
    ant.vertices.push_back(
        current_point);  //  добавляем точку в маршрут, на которой находимся

    for (int i = 0; i < size_; ++i) {  //  перебираем путь
      visited[current_point] = true;
      neighbours = FindNeighbours(current_point, visited);  //  смотрим соседей

      if (neighbours.empty() == false) {  //  выбираем соседа и идем
        GoNextStep(neighbours, wishes, ant, visited, current_point);
      } else if (i == size_ - 1 &&
                 ant.distance > 0) {  //  финальная точка старта
        GoLastStep(ant, visited, current_point, start_point);
      } else {  //  тупик, смотрим следующего муравья
        ant.vertices.clear();
        ant.distance = 0;
        break;
      }
    }

    if (ant.distance != 0) {  //  если был успешный путь
      UpdateLocalPheromones(ant);  //  оставляем феромоны 1 муравья
    } else {
      ant.vertices.clear();
    }
  }
}

std::vector<int> AntsAlgorithm::FindNeighbours(int point,
                                               std::vector<bool>& visited) {
  std::vector<int> neighbours;

  for (int i = 0; i < size_; ++i) {  //  смотрим непосещенных соседей
    if (graph_->At(point, i) != 0 && i != point && visited[i] == false) {
      neighbours.push_back(i);
    }
  }
  return neighbours;
}

void AntsAlgorithm::GoNextStep(std::vector<int>& neighbours,
                               s21::Matrix& wishes, s21::TsmResult& ant,
                               std::vector<bool>& visited, int& current_point) {
  FindWaysWishes(wishes, neighbours, current_point);

  double random =
      (rand() % 101) /
      100.0;  //  по рандому и вероятности(желанию) определяем соседа:
  int neighbours_amount = neighbours.size();

  std::sort(neighbours.begin(), neighbours.end());

  for (int j = 0; j < neighbours_amount; j++) {
    if (neighbours_amount == 1 || j == neighbours_amount - 1 ||
        (wishes(current_point, neighbours[j]) >= random)) {
      ant.distance += graph_->At(current_point, neighbours[j]);
      ant.vertices.push_back(
          neighbours[j]);  //  добавляем точку в маршрут, на которой находимся
      current_point = neighbours[j];  //  сохраняем выбранного соседа
      visited[current_point] = true;
      break;
    }
  }
}

void AntsAlgorithm::GoLastStep(s21::TsmResult& ant, std::vector<bool>& visited,
                               int current_point, int start_point) {
  if (graph_->At(current_point, start_point) != 0) {
    ant.distance += graph_->At(current_point, start_point);
    ant.vertices.push_back(start_point);
  } else {
    visited[start_point] = false;
    ant.vertices.clear();
    ant.distance = 0;
  }
}

void AntsAlgorithm::FindWaysWishes(s21::Matrix& wishes,
                                   const std::vector<int>& neighbours,
                                   int current_point) {
  double sum_wishes = 0;

  for (auto neighbour :
       neighbours) {  //   определяем вероятности выбора пути(желание)
    if (graph_->At(current_point, neighbour) != 0 &&
        current_point != neighbour) {
      wishes(current_point, neighbour) =
          (double)pow(pheromons_(current_point, neighbour), alpha_) *
          (double)pow(((1.0 / graph_->At(current_point, neighbour))), beta_);
      sum_wishes += wishes(current_point, neighbour);
    }
  }
  for (auto neighbour :
       neighbours) {  //   определяем вероятности выбора пути(желание)
    if (graph_->At(current_point, neighbour) != 0 &&
        current_point != neighbour) {
      wishes(current_point, neighbour) /= sum_wishes;
    }
  }
}

void AntsAlgorithm::UpdateLocalPheromones(s21::TsmResult& ant) {
  if (ant.distance != 0) {
    for (size_t i = 1; i < ant.vertices.size(); ++i) {
      pheromons_local_(ant.vertices[i - 1], ant.vertices[i]) +=
          Q_ / ant.distance;
      if (graph_->At(ant.vertices[i - 1], ant.vertices[i]) ==
          graph_->At(ant.vertices[i], ant.vertices[i - 1])) {
        pheromons_local_(ant.vertices[i], ant.vertices[i - 1]) +=
            Q_ / ant.distance;
      }
    }
    pheromons_local_(ant.vertices.back(), ant.vertices[0]) += Q_ / ant.distance;

    if (graph_->At(ant.vertices.back(), ant.vertices[0]) ==
        graph_->At(ant.vertices[0], ant.vertices.back())) {
      pheromons_local_(ant.vertices[0], ant.vertices.back()) +=
          Q_ / ant.distance;
    }
  }
}

bool AntsAlgorithm::UpdateBestWay() {
  bool was_updated = false;

  for (auto way : ants_) {
    if (way.distance > 0 &&
        (way.distance < best_way_.distance || best_way_.distance == 0)) {
      best_way_.distance = way.distance;
      best_way_.vertices = std::move(way.vertices);
      was_updated = true;
    }
    way.vertices.clear();
    way.distance = 0;
  }

  return was_updated;
}

void AntsAlgorithm::UpdatePheromones() {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      pheromons_(i, j) = (1.0 - p_) * pheromons_(i, j) + pheromons_local_(i, j);
    }
  }
}

void AntsAlgorithm::NumberPoints(TsmResult& result) {
  for (auto& name : result.vertices) {
    ++name;
  }
}

}  // namespace s21