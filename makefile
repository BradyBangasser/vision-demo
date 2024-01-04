CXX=aarch64-bullseye-linux-gnu-g++
DEPS_CFLAGS=-std=c++20 -Iinclude -Iinclude/opencv4
LD_FLAGS=-pthread -Wall -Llib -Wl,--unresolved-symbols=ignore-in-shared-libs
DEPS_LIBS=#-Llib -lwpilibc -lwpiHal -lapriltag -lcameraserver -lntcore -lcscore -lopencv_gapi -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_video -lopencv_dnn -lopencv_videoio -lopencv_imgcodecs -lopencv_aruco -lopencv_calib3d -lopencv_features2d -lopencv_imgproc -lopencv_flann -lopencv_core -lwpimath -lwpinet -lwpiutil -latomic
EXE=terminator.shit
DESTDIR?=/home/pi/
CFLAGS=-Og

SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp, out/%.o, $(SRCS))

.PHONY: clean all

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(DEPS_CFLAGS) $(DEPS_LIBS) $(LD_FLAGS) -o $(EXE) $(OBJS) $(CFLAGS)

out/%.o: src/%.cpp
	$(CXX) $(DEPS_CFLAGS) $(DEPS_LIBS) $(CFLAGS) -o $@ -c $^

clean:
	rm -rf out/* $(EXE) ; clear