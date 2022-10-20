#ifndef TEST_MAINUTIL_H_
#define TEST_MAINUTIL_H_

#include <thread>
#include <chrono>
#include <map>
#include <array>
#include <tuple>
#include <mutex>
#include <algorithm>
#include "SpeakingThread.h"

using namespace std;


static const unsigned int C_AIRPORT_THREAD_ID = 1;
static const unsigned int C_PISTE_THREAD_ID = 2;

enum pisteState
{
    indisponible,
    libre,
    decolage,
    atterissage
};

enum aeroportState
{
    ferme,
    ouvert,
    decolageUniquement,
    atterrissageUniquement
};


static std::map<unsigned int, enum::pisteState> pisteStatesMap;
static std::map<unsigned int, enum::pisteState> aeroportStatesMap;

static Publisher<aeroportState, C_AIRPORT_THREAD_ID> aeroportStatePublisher;

void initThread();



#endif // TEST_MAINUTIL_H_

