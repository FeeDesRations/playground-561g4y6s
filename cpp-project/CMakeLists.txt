cmake_minimum_required (VERSION 2.6)
project (speakingthread)

find_package(Threads REQUIRED)

add_executable(speakingthread src/SpeakingThreadTest.cpp src/Exercises/MainUtil.h src/Exercises/MutexData.h src/Exercises/SpeakingThread.h src/Exercises/SpeakingThread.cpp)

target_link_libraries(speakingthread Threads::Threads )
