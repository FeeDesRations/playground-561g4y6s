#ifndef TEST_MUTEXDATA_H_
#define TEST_MUTEXDATA_H_

#include <thread>
#include <chrono>
#include <map>
#include <array>
#include <tuple>
#include <mutex>
#include <algorithm>


using namespace std;


template <class Data>
struct MutexData
{
    MutexData() {}
    MutexData(Data data) : _data(data) {}

    Data _data;
    std::mutex _mutex;
};

#endif // TEST_EXERCICES_UNIVERSE_H_

