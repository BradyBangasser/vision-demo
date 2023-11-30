CXX=aarch64-bullseye-linux-gnu-g++
DEPS_CFLAGS=-std=c++20 -Iinclude -Iinclude/opencv4
DEPS_LIBS=-Llib -lwpilibc -lwpiHal -lapriltag -lcameraserver -lntcore -lcscore -lopencv_gapi -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_video -lopencv_dnn -lopencv_videoio -lopencv_imgcodecs -lopencv_aruco -lopencv_calib3d -lopencv_features2d -lopencv_imgproc -lopencv_flann -lopencv_core -lwpimath -lwpinet -lwpiutil -latomic
EXE=terminator.exe
DESTDIR?=/home/pi/

SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp, out/%.o, $(SRCS))

$(EXE): $(OBJS)
	$(CXX) $(DEPS_CFLAGS) $(DEPS_LIBS) -o $(EXE) $(OBJS)

out/%.o: src/%.cpp
	$(CXX) $(DEPS_CFLAGS) $(DEPS_LIBS) -o $@ -c $^