#ifndef TEST_EXERCICES_UNIVERSE_H_
#define TEST_EXERCICES_UNIVERSE_H_

#include "MutexData.h"
#include <thread>
#include <chrono>
#include <map>
#include <array>
#include <tuple>
#include <mutex>
#include <algorithm>
#include <iostream>


using namespace std;


template <class Data, unsigned int id>
class Publisher
{
public :

    Publisher()
    {
        _publisher_id = id;
    }

    Publisher(Data current_data)
    {
        _publisher_id = id;
        _current_data._data = current_data;
        publish(_current_data._data, _publisher_id);
    }


    void publish(Data& data, unsigned int thread_id)
    {
        if (thread_id == _publisher_id)
        {
            const std::lock_guard<std::mutex> lock1(_current_data_mutex);
            std::cout << "publishing data : " << data << " by thread id : " << thread_id << std::endl;

            for (auto it = _double_buffer.begin(); it != _double_buffer.end(); ++it)
            {
                try
                {
                    (*it)[_write_index]._mutex.lock();
                    _current_data._data = data;
                    (*it)[_write_index]._data = data;
                    (*it)[_write_index]._mutex.unlock();
                }
                catch (std::exception e)
                {
                    (*it)[_write_index]._mutex.unlock();
                }
            }

            switchIndex();
        }
    }

    void seek(Data& data, unsigned int thread_id)
    {
        for (size_t i = 0; i != _seeker_id.size(); ++i)
        {
            if (thread_id == _seeker_id[i])
            {
                try
                {
                    _double_buffer[_next_seeker_index][_read_index]._mutex.lock();
                    memcpy(data._data, _double_buffer[_next_seeker_index][_read_index]._data, sizeof(_current_data._data));
                    _double_buffer[_next_seeker_index][_read_index]._mutex.unlock();
                }
                catch (std::exception e)
                {
                    _double_buffer[_next_seeker_index][_read_index]._mutex.unlock();
                }
            }
        }
    }

    void registerPublisher(const unsigned int thread_id)
    {
        if (_publisher_id >= 0)
        {
            _publisher_id = static_cast<long long int >(thread_id);
        }
    }

    void registerSeeker(const unsigned int thread_id)
    {
        if (_next_seeker_index < c_max_seeker)
        {
            try
            {
                const std::lock_guard<std::mutex> lock1(_current_data_mutex);
                const std::lock_guard<std::mutex> lock2(_double_buffer[_next_seeker_index][0]._mutex);
                const std::lock_guard<std::mutex> lock3(_double_buffer[_next_seeker_index][1]._mutex);

                _seeker_id[_next_seeker_index] = thread_id;
                //_double_buffer[_next_seeker_index][0]._data = _current_data._data;
                //_double_buffer[_next_seeker_index][1]._data = _current_data._data;
                memcpy(_double_buffer[_next_seeker_index][0]._data, _current_data._data, sizeof(_current_data._data));
                memcpy(_double_buffer[_next_seeker_index][1]._data, _current_data._data, sizeof(_current_data._data));
                ++_next_seeker_index;
            }
            catch (std::exception e) {}
        }
    }

private :

    static const unsigned int c_max_seeker = 10;

    MutexData<Data> _current_data;
    std::mutex _current_data_mutex;
    std::array<std::array<MutexData<Data>, 2>, c_max_seeker> _double_buffer{};
    std::array<unsigned int, c_max_seeker> _seeker_id{};
    long long int _publisher_id = -1;
    unsigned int _write_index = 0;
    unsigned int _read_index = 1;
    unsigned int _next_seeker_index = 0;



    void lockAll()
    {
        for (auto it = _double_buffer.begin(); it != _double_buffer.end(); ++it)
        {
            (*it)[_write_index]._mutex.lock();
            (*it)[_read_index]._mutex.lock();
        }
    }
    void unlockAll()
    {
        for (auto it = _double_buffer.begin(); it != _double_buffer.end(); ++it)
        {
            (*it)[_write_index]._mutex.unlock();
            (*it)[_read_index]._mutex.unlock();
        }
    }
    void switchIndex()
    {
        lockAll();
        _read_index = _write_index; _write_index = (_write_index == 0) ? 1 : 0;
        unlockAll();
    }

};

#endif // TEST_EXERCICES_UNIVERSE_H_

