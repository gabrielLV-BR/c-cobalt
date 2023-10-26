CC:=gcc

CFLAGS=-g -Wall -I"$(CURDIR)/src/"
LDFLAGS=-lc -ldl -lm -DNDEBUG -lX11

SOURCES:=$(wildcard src/**/*.c src/*.c)

TARGET:=game

# DEFINES

CFLAGS+=-DASSETS="$(CURDIR)/assets/"

#
VENDOR_dir:=$(CURDIR)/vendor/

CFLAGS+=-I"$(VENDOR_dir)"

# GLAD

GLAD_source:=$(VENDOR_dir)glad/glad.c
SOURCES+=$(GLAD_source)

# GLFW

LDFLAGS+=-lglfw -lpthread

#

OBJECTS:=$(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	@echo "SOURCES BE LIKE:"
	@echo $(SOURCES)
	@echo "-----"
	$(CC) $(CFLAGS) $? -o $(TARGET) $(LDFLAGS)

.PHONY: clean run

run: $(TARGET)
	-./$(TARGET)

clean:
	-rm -f $(OBJECTS) $(TARGET)