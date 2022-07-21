#include "./screen.hpp"

const static long MAX = 3;

namespace bathroom{
    Bathroom::Bathroom() :count_girl(0),count_boy(0){
        count_waiters[gender::sexo::mulher] = &count_girl;
        count_waiters[gender::sexo::homem] = &count_boy;

        count_opposite[gender::sexo::homem] = &count_girl; //Contador para o sexo oposto
        count_opposite[gender::sexo::mulher] = &count_boy;

    }


    void Bathroom::log_in(gender::sexo sexo){
        std::unique_lock<std::mutex> lock(*this); //região crítica

        while (count_waiters[sexo]->load() >= MAX || count_opposite[sexo]->load() > 0)
            this->wait(lock);
    lock.unlock();

    long load = count_waiters[sexo]->load();
    while (!count_waiters[sexo]->compare_exchange_strong(load, load + 1));
    }

    void Bathroom::log_out(gender::sexo sexo){
        long load = count_waiters[sexo]->load();
        while(!count_waiters[sexo]->compare_exchange_strong(load,load-1));
    this -> notify_all();
    }
};