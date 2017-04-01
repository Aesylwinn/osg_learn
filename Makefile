CC      = g++
CFLAGS  = -g -Wall
LDFLAGS =

SDIR    = src
ODIR    = obj
EXEC    = party

_OBJ    = main.o
OBJS    = $(patsubst %,$(ODIR)/%,$(_OBJ))
DEPS    =


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@


.PHONY: clean
clean:
	rm -rf obj/*
	rm -f  $(EXEC)

