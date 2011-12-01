OBJS = \
	main.o \
	Particle.o \
	Cell.o \
	System.o \
	Na_K_Pump.o \
	Texture_Loader.o \
	Graph.o \
	util.o

CFLAGS += -I/usr/include/freetype2
CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -DGL_GLEXT_PROTOTYPES
CFLAGS += -O3
# CFLAGS += -fno-inline
CFLAGS += -msse
CFLAGS += -msse2
CFLAGS += -mfpmath=sse
# CFLAGS += -flto
# CFLAGS += -ffast-math
CFLAGS += -funsafe-math-optimizations
CFLAGS += -ffinite-math-only
CFLAGS += -fno-trapping-math
CFLAGS += -mrecip
CFLAGS += `pkg-config gtk+-2.0 --cflags`
CFLAGS += `pkg-config gtkgl-2.0 --cflags`

CXXFLAGS += -std=c++0x

LDFLAGS += -lSOIL
LDFLAGS += -lftgl
LDFLAGS += -lGL
LDFLAGS += -lGLU
LDFLAGS += -lglut
LDFLAGS += -lm
LDFLAGS += `pkg-config gtk+-2.0 --libs`
LDFLAGS += `pkg-config gtkgl-2.0 --libs`

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

main: $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJS) main

CFLAGS += -MMD -MP
DEP_FILES = $(patsubst %.o,%.d,$(OBJS))
-include $(DEP_FILES)

