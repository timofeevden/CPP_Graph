CXX := g++
CXXFLAGS :=-Wall -Wextra -Werror --std=c++17
LDFLAGS := -lgtest

TESTS := $(wildcard Tests/*.cc)
LIB_FILES = s21_graph.a s21_graph_algorithms.a

.PHONY: all clean

all: tests launch_app

s21_graph.a:
	$(CXX) $(CXXFLAGS) -c Graph/s21_graph.cc
	ar rc s21_graph.a s21_graph.o
	ranlib s21_graph.a

s21_graph_algorithms.a:
	$(CXX) $(CXXFLAGS) -c Graph/s21_graph_algorithms.cc Graph/s21_ants_algorithm.cc
	ar rc s21_graph_algorithms.a s21_graph_algorithms.o s21_ants_algorithm.o
	ranlib s21_graph_algorithms.a

launch_app: clean $(LIB_FILES)
	$(CXX) $(CXXFLAGS) View/*.cc Containers/s21_matrix.cc $(LIB_FILES) -o app.out
	./app.out

clean:
	rm -rf *.a *.o *.out Graph/*.gch *.gch *.gcno *.gcna *.gcda *.info *.tgz report ./Tests/s21_run_tests Tests/TestFiles/Export/* .clang-format

tests: clean
	$(CXX) $(CXXFLAGS) -g3 --coverage -c $(TESTS) Graph/s21_graph.cc Containers/s21_matrix.cc Graph/s21_graph_algorithms.cc Graph/s21_ants_algorithm.cc
	$(CXX) $(CXXFLAGS) *.o $(LDFLAGS) -g3 --coverage -o ./Tests/s21_run_tests 
	./Tests/s21_run_tests 

gcov_report: tests
	lcov -t "test" -o test_full.info --no-external -c -d .
	lcov --remove test_full.info '*/Containers/*' -o test.info
	genhtml -o report test.info
	open ./report/index.html

style:
	clang-format -style=Google -n ./Containers/*.cc ./Containers/*.h ./Graph/*.cc ./Graph/*.h ./View/*.cc ./View/*.h $(TESTS)

edit_style:
	clang-format -style=Google -i ./Containers/*.cc ./Containers/*.h ./Graph/*.cc ./Graph/*.h ./View/*.cc ./View/*.h $(TESTS)

cpp_check:
	cppcheck --language=c++ --suppress=missingIncludeSystem Containers/*.h Containers/*.cc Graph/*.cc Graph/*.h Tests/*.cc Tests/*.h View/*.cc View/*.h

