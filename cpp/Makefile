CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -isysroot $(shell xcrun --show-sdk-path)
CPP_TARGET = futoshiki
CPP_SOURCE = futoshiki.cpp

all: $(CPP_TARGET)

$(CPP_TARGET): $(CPP_SOURCE)
	$(CXX) $(CXXFLAGS) -o $(CPP_TARGET) $(CPP_SOURCE)

run-cpp: $(CPP_TARGET)
	./$(CPP_TARGET)

clean:
	rm -f $(CPP_TARGET)
