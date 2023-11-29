CXX=aarch64-bullseye-linux-gnu-g++
# CXX=g++
DEPS_CFLAGS=-std=c++20 -Iinclude -Iinclude/opencv4
DEPS_LIBS=-Llib -lwpilibc -lwpiHal -lapriltag -lcameraserver -lntcore -lcscore -lopencv_gapi -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_video -lopencv_dnn -lopencv_videoio -lopencv_imgcodecs -lopencv_aruco -lopencv_calib3d -lopencv_features2d -lopencv_imgproc -lopencv_flann -lopencv_core -lwpimath -lwpinet -lwpiutil -latomic
EXE=multiCameraServerExample
DESTDIR?=/home/pi/

.PHONY: clean build install

build: ${EXE}

install: build
	cp ${EXE} runCamera ${DESTDIR}

clean:
	rm ${EXE} *.o

OBJS=main.o

${EXE}: ${OBJS}
	${CXX} -pthread -g -o $@ $^ ${DEPS_LIBS} -Wl,--unresolved-symbols=ignore-in-shared-libs

.cpp.o:
	${CXX} -pthread -g -Og -c -o $@ -std=c++20 ${CXXFLAGS} ${DEPS_CFLAGS} $<
