OBJS = \
	main.o \
	Particle.o \
	Particle_System.o

CFLAGS = -Wall -g

LDFLAGS = -lGL -lGLU -lglut -o 

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

main: $(OBJS)
	$(CXX) $< $(LDFLAGS) $@

