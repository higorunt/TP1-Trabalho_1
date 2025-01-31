# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -fexceptions -g -O0
INCLUDES = -Iinclude -IC:/msys64/mingw64/include/pdcurses -IC:/msys64/mingw64/include
LDFLAGS = -LC:/msys64/mingw64/lib
LIBS = -lsqlite3 -lpdcurses -luser32 -lgdi32 -lkernel32 -lcomdlg32 -lwinmm

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Source files (ajuste para incluir todos os .cpp necessários)
SOURCES = $(wildcard $(SRCDIR)/dominios/*.cpp) \
          $(wildcard $(SRCDIR)/entidades/*.cpp) \
          $(wildcard $(SRCDIR)/repositorios/*.cpp) \
          $(wildcard $(SRCDIR)/servicos/*.cpp) \
          $(wildcard $(SRCDIR)/telas/*.cpp) \
          $(wildcard $(SRCDIR)/testes/*.cpp) \
          main.cpp

# Object files (preserva a estrutura src/*)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Output executable
TARGET = $(BINDIR)/TP1-Trabalho

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	@if not exist "$(BINDIR)" mkdir "$(BINDIR)"
	$(CXX) $^ -o $@ $(LDFLAGS) $(LIBS)

# Compilation rule (cria diretórios automaticamente)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	@if exist "$(OBJDIR)" rmdir /s /q "$(OBJDIR)"
	@if exist "$(BINDIR)" rmdir /s /q "$(BINDIR)"

# Run
run: all
	$(TARGET)

.PHONY: all clean run