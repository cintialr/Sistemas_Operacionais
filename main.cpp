#include <chrono> // std::chrono
#include <ctime> // time
#include <iostream> // std::cout, std::endl
#include <thread> // std::thread
#include <vector> // std::vector3

#include "./screen.hpp" // bathroom::Bathroom
#include "./gender.hpp" // gender::sexo

void task (long thread_id, bathroom::Bathroom* bathroom){
    gender::sexo sexo = gender::sexo(rand()%2);

    bathroom->log_in(sexo);
    std::cout << "Thread [" << thread_id << "] GET IN [";
    std::cout << (sexo == gender::sexo::homem ? "homem" : "mulher") << ']'<< std::endl;
 
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));
 
    bathroom->log_out(sexo);
    std::cout << "Thread [" << thread_id << "] GET OUT [";
    std::cout << (sexo == gender::sexo::homem ? "homem" : "mulher") << ']'<< std::endl;

}

int main(){
    srand(time(nullptr)); // valores aleatórios
    std::vector<std::thread> threads; // threads vector
    auto bathroom = new bathroom::Bathroom(); // unisex bathroom controller
    long thread_number = std::thread::hardware_concurrency() * 2;
 
    for (long i = 0; i < thread_number; ++i) {
        threads.push_back(std::thread(&task, i, bathroom)); // create threads passing id (i) and bathroom controller (bathroom)
  }
 
    for (auto& thread : threads) thread.join(); // wait for all threads
 
    return 0; // exit successfully
}

/*Para compilar no linux
> g++ --std=c++11 -pthread main.cpp bathroom.cpp -o bathroom
> ./bathroom 
*/