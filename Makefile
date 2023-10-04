# Adjust WT_BASE to the Wt installation directory.  Default: /usr/local

CXX=g++
WT_BASE=/usr/local
CXXFLAGS=--std=c++14 -I$(WT_BASE)/include 
LDFLAGS=-L$(WT_BASE)/lib -Wl,-rpath,$(WT_BASE)/lib -lwthttp -lwt

# Codebase to build. Headers are under DEPS, objects under OBJS

DEPS = wordle.h game.h
OBJS = main.o wordle.o game.o

# Build the objects

%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Build the executable

wordle: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 

# Clean up script

clean:
	rm -f wordle $(OBJS)


