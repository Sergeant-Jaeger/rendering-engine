#executable names for flexibility
EXE := rd_view
TEST := Test
SPIKE := Ticket

#compiler variable
CC := g++

#directory variables
BINDIR := bin
BUILDDIR := build
INCLUDEDIR := include
LIBDIR := lib
SPIKEDIR := spike
SRCDIR := src
TESTDIR := test

#extension variables
SRCEXT := cc
OBJEXT := o

#files
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

INCLUDES := -I $(INCLUDEDIR)

#libraries
LIB := -L $(LIBDIR) -lcs680 -lX11

#flags
CCFLAGS := -std=c++11 -g -Wall

#targets
TARGET := $(BINDIR)/$(EXE)
TESTTARGET := $(BINDIR)/$(TEST)
SPIKETARGET := $(BINDIR)/$(SPIKE)

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo "$(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CCFLAGS) $(INCLUDES) -c -o $@ $<"; $(CC) $(CCFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@echo "Cleaning...";
	@echo "rm -r $(BUILDDIR) $(TARGET)"; rm -r $(BUILDDIR) $(TARGET)

test:
	@echo "$(CC) $(CCFLAGS) $(TESTDIR)/$(TEST).$(SRCEXT) $(INCLUDES) $(LIB) -o $(TESTTARGET)";
	$(CC) $(CCFLAGS) $(TESTDIR)/$(TEST).$(SRCEXT) $(INCLUDES) $(LIB) -o $(TESTTARGET)

spike:
	@echo "$(CC) $(CCFLAGS) $(SPIKEDIR)/$(SPIKE).$(SRCEXT) $(INCLUDES) $(LIB) -o $(SPIKETARGET)";
	$(CC) $(CCFLAGS) $(SPIKEDIR)/$(SPIKE).$(SRCEXT) $(INCLUDES) $(LIB) -o $(SPIKETARGET)

.PHONY: clean
