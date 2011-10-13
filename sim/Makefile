OBJS = \
	main.o \
	Ion.o \
	Cell.o \
	System.o \
	Na_K_Pump.o \
	Texture_Loader.o \
	util.o

CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -DGL_GLEXT_PROTOTYPES
CFLAGS += -O3
CFLAGS += -msse
CFLAGS += -msse2
CFLAGS += -mfpmath=sse
# CFLAGS += -flto

CXXFLAGS = -std=c++0x

LDFLAGS += -lSOIL
LDFLAGS += -lGL
LDFLAGS += -lGLU
LDFLAGS += -lglut
LDFLAGS += -lm

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

main: $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJS) main

CFLAGS += -MMD -MP
DEP_FILES = $(patsubst %.o,%.d,$(OBJS))
-include $(DEP_FILES)

