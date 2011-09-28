OBJS = \
	main.o \
	Particle.o \
	Particle_System.o \
	Cell.o \
	System.o \
	util.o

CFLAGS = -Wall -g

LDFLAGS = -lGL -lGLU -lglut -lm

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

main: $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

