TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
# 条件编译
CONFIG += WINDOWS_GCC

SOURCES += \
        src/main.cpp \
        src/buff_detect.cpp \
        src/videoprocess/video_process.cpp \      
        src/videoprocess/setting.cpp \
        src/videoprocess/utils.cpp

HEADERS += \
        src/buff_detect.h \
        src/videoprocess/video_process.h \
        src/videoprocess/setting.h \
        src/videoprocess/utils.h \

WINDOWS_GCC{
INCLUDEPATH += G:/opencv_mingw/install/include
LIBS += G:/opencv_mingw/install/x64/mingw/lib/libopencv_*.a
# 如果产生无法定位程序输入点，...于动态链接库xxxxx上
# 将mingw64\bin文件夹下libstdc+±6.dll复制到C:\Windows\System32下
}
else{
INCLUDEPATH += /usr/local/include \
               /usr/local/include/opencv \
               /usr/local/include/opencv2 \

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so \
        /usr/local/lib/libopencv_dnn.so
        #/usr/local/lib/..so \
        -pthread
      # -ldl
LIBS += -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_objdetect -lopencv_highgui -lopencv_videoio -lopencv_photo -lopencv_imgcodecs -lopencv_video -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_dnn

}
