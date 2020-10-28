
#include <iostream>
#include <vector>
#include <unistd.h>

int main () 
{
    int size = 20;
    int repetition = 500;
    int* data = new int[size];
    int* data_copy = new int[size];
    long long copy_time = 0;
    long long move_time = 0;

    for( int i =0; i< size; i++){
        data[i] = i;
    }

    int* p = &data[10];

#if 0
    for (int j= 0; j < repetition; j++) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; i++) {
            data_copy[i] = data[i];
        }
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        copy_time += elapsed.count();
        start = std::chrono::high_resolution_clock::now();
        std::memmove(data_copy, data, size*sizeof(int));
        elapsed = std::chrono::high_resolution_clock::now() - start;
        move_time += elapsed.count();
    }
    std::cout << "SIZE: " << size << " -- REPETITION: " << repetition << std::endl;
    std::cout << "ELAPSED WITH COPY: " << copy_time/repetition << std::endl;
    std::cout << "ELAPSED WITH COPY: " << move_time/repetition << std::endl;
    std::cout << "RATIO: " << copy_time/move_time << std::endl;
#endif

    return 0;
}