// { autofold
#include "SpeakingThread.h"
#include "MainUtil.h"

// }


/*


// thread id
static const unsigned int C_AIRPORT_THREAD_ID = 1;
static const unsigned int C_PISTE_THREAD_ID = 2;

// enumeration disponible
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

// map a remplir :)
static std::map<unsigned int, enum::pisteState> pisteStatesMap;
static std::map<unsigned int, enum::pisteState> aeroportStatesMap;


// class de discussion entre thread

template <class Data, unsigned int id>
class Publisher
{
public :

    Publisher()
    Publisher(Data current_data)


    void publish(Data& data, unsigned int thread_id)
    void seek(Data& data, unsigned int thread_id)
    void registerPublisher(const unsigned int thread_id)
    void registerSeeker(const unsigned int thread_id)
};

*/

void * stateThreadfunc(void * ptr);
void * pisteThreadFunc(void * ptr);


// i need to react to data published by the airport state thread and publish my state as well
// when the airport is ferme i'm indisponible
// when the airport is ouvert i'm libre
// when the airport is decolageUniquement i'm decolage
// when the airport is atterrissageUniquement i'm atterissage
void * pisteThreadFunc(void * ptr)
{


    return nullptr;
}



void * stateThreadFunc(void * ptr)
{
    int i = 0;
    aeroportState aeroport_state = aeroportState::ferme;

    aeroportStatePublisher.registerPublisher(C_AIRPORT_THREAD_ID);
    aeroportStatePublisher.publish(aeroport_state, C_AIRPORT_THREAD_ID);

    while (i < 4)
    {
        if (aeroport_state != aeroportState::atterrissageUniquement)
        {
            aeroport_state = static_cast<aeroportState>(static_cast<int>(aeroport_state + 1));
        }
        else
        {
            aeroport_state = aeroportState::ferme;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        aeroportStatePublisher.publish(aeroport_state, C_AIRPORT_THREAD_ID);
        ++i;
    }

    return nullptr;
}


// this method is use in main to init and launch thread
void initThread()
{
    pthread_t* mThreadID1 = new pthread_t();
    pthread_t* mThreadID2 = new pthread_t();

    ::pthread_create(mThreadID1, nullptr, stateThreadFunc, nullptr);
    ::pthread_create(mThreadID2, nullptr, pisteThreadFunc, nullptr);


    ::pthread_join(*mThreadID1, nullptr);
    ::pthread_join(*mThreadID2, nullptr);

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
