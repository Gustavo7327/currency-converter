# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/usr/include/nlohmann

# Alvo e arquivos
TARGET = cambio
OBJS = main.o

# Regras
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o -lcurl

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

help:
	@echo "make: compila e executa o programa"
	@echo "make clean: remove arquivos temporários"

clean:
	rm -f $(TARGET) *.o