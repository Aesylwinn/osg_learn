CC      = g++
CFLAGS  = -g -Wall
LDFLAGS = -L /usr/local/lib64 -losg -losgViewer -losgDB

SDIR    = src
ODIR    = obj
EXEC    = party

_OBJ    = main.o geometry.o
OBJS    = $(patsubst %,$(ODIR)/%,$(_OBJ))
_DEP    = geometry.hpp
DEPS    = $(patsubst %,$(SDIR)/%,$(_DEP))


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@


.PHONY: clean
clean:
	rm -rf obj/*
	rm -f  $(EXEC)

