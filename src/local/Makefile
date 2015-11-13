TARGET   = test

CC       = g++ -c
# compiling flags here
CFLAGS   = -std=c++11 -Wall

LINKER   = g++ -o
# linking flags here
LFLAGS   = -Wall

SOURCES  := $(wildcard *.cc)
INCLUDES := $(wildcard *.h)
OBJECTS  := $(SOURCES:.c=*.o)
rm       = rm -f
DEBUGGER = gdb

$(TARGET): obj
	@$(LINKER) $(TARGET) $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

obj: $(SOURCES) $(INCLUDES)
	@$(CC) $(CFLAGS) $(SOURCES)
	@echo "Compilation complete!"

clean:
	@$(rm) $(TARGET) $(OBJECTS)
	@echo "Cleanup complete!"

exec:
	./$(TARGET)

dbg:
	pwd
	$(DEBUGGER) ./$(TARGET)
