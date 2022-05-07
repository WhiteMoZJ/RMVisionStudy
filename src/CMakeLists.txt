set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

#set the path installed OpenCV to ../opencv/build
#which includes folders /bin /include
set(OpenCV_DIR "G:/opencv_mingw/install")
set(OPENCV_FOUND TRUE)
find_package(OpenCV REQUIRED)

#print the imformation about current OpenCV
message(STATUS "OpenCV library status: ")
message(STATUS "> version: ${OpenCV_VERSION} ")
message(STATUS "> libraries: ${OpenCV_LIBS} ")
message(STATUS "> include: ${OpenCV_INCLUDE_DIRS}  ")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})

set(SRC_LIST "main.cpp" "buff_detect.cpp" "buff_detect.h" "videoprocess/setting.cpp" "videoprocess/setting.h" "videoprocess/utils.cpp" "videoprocess/utils.h" "videoprocess/video_process.cpp" "videoprocess/video_process.h")
add_executable(RMCV ${SRC_LIST})

target_link_libraries(RMCV ${OpenCV_LIBS})
