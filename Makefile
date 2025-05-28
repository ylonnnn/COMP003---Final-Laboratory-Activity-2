CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++17

# For Linux
SOURCES := $(shell find . -name "*.cpp")

# For Windows 
# SOURCES = $(subst \,/,$(shell for /R %%f in (*.cpp) do @echo %%f))

OBJECTS = $(patsubst ./%.cpp, ./bin/%.o, $(SOURCES))

TARGET = ./bin/compiled

all: $(TARGET)
	$(TARGET)

# For Windows (Line 20)
# @if not exist "$(dir $@)" mkdir "$(dir $@)"
./bin/%.o: %.cpp 
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

clean:
	rm -rf ./bin/
