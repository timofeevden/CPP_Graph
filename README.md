# Graph

В данном проекте реализованы несколько основных алгоритмов на графах. Графы являются одной из базовых структур данных в программировании, которая используется повсеместно. В виде графов можно, например, интерпретировать схемы дорог, электрические цепи, географические карты, связи между людьми в социальных сетях и многое-многое другое.


## Chapter II

### Основные определения

**Граф** — совокупность конечного множества вершин и множества ребер. Каждому ребру сопоставлены две точки из множества вершин графа, образующие граничные точки ребра.

**Виды графов по типу рёбер:**
* *Неориентированный* — граф, в котором перемещение между соединёнными ребром вершинами возможно в любом направлении.

* *Ориентированный* — граф, рёбрам которого присвоено направление. Направленные рёбра именуются также дугами. Перемещение из одной вершины в другую возможно только по дугам соответствующего направления.


Если помимо наличия ребра между двумя вершинами задан ещё и вес ребра, то такой граф называется ***взвешенным***.


**Виды графов по числу рёбер:**
* *Нулевой* — в графе отсутствуют рёбра.

* *Неполный* — в графе есть рёбра, но не из каждой вершины есть ребро в любую другую вершину.

* *Полный* — в графе из каждой вершины есть ребро в любую другую вершину.

**Виды графов по достижимости узлов:**
* *Связный* — для любой вершины в графе есть хотя бы один путь до любой другой вершины в этом же графе.

* *Несвязный* — в графе отсутствует путь хотя бы между двумя его вершинами.

Для ориентированных графов дополнительно разделяют ещё два типа связности: *сильносвязный* и *слабосвязный*.
* *Сильносвязный* — для любой вершины в ориентированном графе существует путь в любую другую вершину и обратно.
* *Слабосвязный* — между двумя любыми вершинами в графе существует путь, но этот путь может быть односторонним. Т.е. из вершины А в вершину B путь может существовать, а обратно нет.

**Деревья**

Отдельным важным подтипом графов являются *деревья*. \
***Дерево*** — это связный ациклический граф, в котором любые две вершины соединены лишь одним маршрутом. Для любого дерева справедлива следующая формула: *q = n - 1*, где q — это число рёбер, n — число вершин графа (дерева). Деревья могут быть построены на базе как неориентированных графов, так и ориентированных, в зависимости от решаемой задачи.

***Остовное дерево (остов)*** — это подграф данного графа, содержащий все его вершины и являющийся деревом. Рёбра графа, не входящие в остов, называются хордами графа относительно остова.

### Способы задания графа

Существуют следующие основные способы задания графов:
* *Матрица смежности* — квадратная матрица, размерность которой равна числу вершин в графе, и в которой $`A_{ij}`$ элемент матрицы содержит в себе информацию о ребре из вершины $`i`$ в вершину $`j`$. Возможные значения, которые может принимать $`A_{ij}`$:
    + Для невзвешенного неориентированного графа: 
        - 0 — ребра между вершинами нет;
        - 1 — ребро между вершинами есть. 
    + Для взвешенного неориентированного графа: 
        - 0 — ребра между вершинами нет; 
        - N — ребро между вершинами есть, и его вес равен N.
    + Для невзвешенного ориентированного графа: 
        - 0 — дуги между вершинами нет;
        - 1 — есть дуга (ориентированное ребро), которая направлена из вершины $`i`$ в вершину $`j`$.
    + Для взвешенного ориентированного графа: 
        - 0 — дуги между вершинами нет;
        - N — есть дуга (ориентированное ребро), которая направлена из вершины $`i`$ в вершину $`j`$, и её вес равен N.
* *Матрица инцидентности* — это матрица, количество строк в которой соответствует числу вершин, а количество столбцов – числу рёбер. В ней указываются связи между инцидентными элементами графа (ребро (дуга) и вершина). Если в неориентированном графе вершина инцидентна ребру, то соответствующий элемент равен 1, в противном случае элемент равен 0. Если в ориентированном графе ребро выходит из вершины, то соответствующий элемент равен 1; если ребро входит в вершину, то соответствующий элемент равен -1; если ребро отсутствует, то элемент равен 0.

Пример задания графа с помощью матрицы смежности можно найти в материалах.

Если количество ребер графа по сравнению с количеством вершин невелико, то значения большинства элементов матрицы смежности будут равны 0. При этом использование данного метода нецелесообразно. Для подобных графов имеются более оптимальные способы их представления:

* *Список смежности* — один из способов представления графа в виде коллекции списков вершин. Каждой вершине графа соответствует список, состоящий из «соседей» (т.е. из вершин, которые непосредственно достижимы напрямую из текущей вершины) этой вершины с указанием весов рёбер.
* *Список рёбер* — таблица (матрица размерность Nx3), в каждой строке которой записаны две смежные вершины и вес, соединяющего их ребра.


В данном проекте реализованы следующие алгоритмы:

    - Обход графа в глубину и в ширину
    - алгоритм Дейкстры
    - алгоритм Флойда-Уоршелла
    - алгоритма Прима
    - решение задачи коммивояжера с помощью муравьиного алгоритма

Реализован консольный интерфейс и сравнение методов решения задачи коммивояжера.
