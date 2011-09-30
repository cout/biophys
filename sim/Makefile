OBJS = \
	main.o \
	Ion.o \
	Ions.o \
	Cell.o \
	System.o \
	Na_K_Pump.o \
	util.o

CFLAGS = -Wall -g

LDFLAGS = -lGL -lGLU -lglut -lm

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

main: $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJS) main

CFLAGS += -MMD -MP
DEP_FILES = $(patsubst %.o,%.d,$(OBJS))
-include $(DEP_FILES)

