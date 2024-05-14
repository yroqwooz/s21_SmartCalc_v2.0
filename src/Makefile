CC = gcc
CFLAGS = -std=c++17 -lstdc++ -pedantic -Wall -Wextra -Werror
TEST_FLAGS = -lgtest

all:
	$(MAKE) clean
	$(MAKE) install

install:
	mkdir SmartCalc
	cd SmartCalc && cmake ../SmartCalc_v2
	cd SmartCalc && make


uninstall:
	rm -rf SmartCalc

launch:
	open SmartCalc/SmartCalc_v2.app

dvi:
	open documentation.md

dist:
	tar -cf SmartCalc.tar SmartCalc

build_test:
	mkdir Tests
	cd Tests && cmake ../SmartCalc_v2_tests 
	cd Tests && make 

test: build_test
	cd Tests && ctest -VV --rerun-failed --output-on-failure

stylecheck:
	clang-format -style=Google -n ./SmartCalc_v2/*.cpp ./SmartCalc_v2/*.cpp ./SmartCalc_v2/QCustomPlot/lib/*.cpp ./SmartCalc_v2/QCustomPlot/lib/*.h ./SmartCalc_v2/CreditCalc/*.cpp ./SmartCalc_v2/CreditCalc/*.h

styleapply:
	clang-format -style=Google -i ./SmartCalc_v2/*.cpp ./SmartCalc_v2/*.cpp ./SmartCalc_v2/QCustomPlot/lib/*.cpp ./SmartCalc_v2/QCustomPlot/lib/*.h ./SmartCalc_v2/CreditCalc/*.cpp ./SmartCalc_v2/CreditCalc/*.h

gcov_report: 
	mkdir gcov_report
	cd gcov_report && cmake ../SmartCalc_v2_tests -D"CMAKE_CXX_FLAGS=-g -O2 -w -fprofile-arcs -ftest-coverage" -D"CMAKE_C_FLAGS=-g -O2 -w -fprofile-arcs -ftest-coverage"
	cd gcov_report && make
	cd gcov_report && ./Regular

	gcovr -r . --html --html-details --filter SmartCalc_v2/ -o gcov_report/index.html
	open gcov_report/index.html

clean:
	rm -rf SmartCalc Tests
	rm -rf SmartCalc_v2/build
	rm -rf gcov_report