#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <map>

#include "./gender.hpp"

namespace bathroom {
    class Bathroom : 
    protected std::mutex, 
    protected std::condition_variable{
        private:
            std::atomic<long> count_boy, count_girl;

            std::map<gender::sexo,std::atomic<long>*> count_waiters;
            std::map<gender::sexo,std::atomic<long>*> count_opposite;
        
        public:
            Bathroom();
            void log_in (gender::sexo);
            void log_out (gender:: sexo);
        };
};

#endif
