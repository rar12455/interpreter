CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

interpreter: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o interpreter

clean:
	rm -f interpreter
