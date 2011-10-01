OBJS = \
	main.o \
	Ion.o \
	Ions.o \
	Cell.o \
	System.o \
	Na_K_Pump.o \
	Texture_Loader.o \
	util.o

CFLAGS = -Wall -g -DGL_GLEXT_PROTOTYPES

LDFLAGS = -lSOIL -lGL -lGLU -lglut -lm

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

main: $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJS) main

CFLAGS += -MMD -MP
DEP_FILES = $(patsubst %.o,%.d,$(OBJS))
-include $(DEP_FILES)

