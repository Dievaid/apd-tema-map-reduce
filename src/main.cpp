#include <iostream>
#include <fstream>
#include <queue>

#include "./impl/data_controller.cpp"
#include "./libs/mapper.hpp"
#include "./libs/reducer.hpp"

int main(int argc, char** argv)
{
    if (argc != 4) 
    {
        std::cout << "Not enough CLI args" << std::endl;
        return -1;
    }

    int mappers = (data::controller::get().mappers() = atoi(argv[1]));
    int reducers = (data::controller::get().reducers() = atoi(argv[2]));

    std::ifstream fin(argv[3]);
    int no_files = 0;
    fin >> no_files;

    auto& mapper_res = data::controller::get().mapper_results();
    mapper_res = std::vector<std::set<long long>*>(mappers);

    std::queue<std::string> file_queue;

    for (int i = 0; i < no_files; i++)
    {
        std::string file;
        fin >> file;
        file_queue.push(file);
    }

    pthread_mutex_t q_mutex;
    pthread_barrier_t barrier;
    pthread_mutex_init(&q_mutex, NULL);
    pthread_barrier_init(&barrier, NULL, mappers + reducers);

    pthread_t mapper_threads[mappers];
    pthread_t reducer_threads[reducers];

    for (int i = 0; i < mappers; i++)
    {
        mapper_res[i] = new std::set<long long>();
    }

    for (int i = 0; i < mappers; i++)
    {
        mapper::Info* info = new mapper::Info(i, &file_queue, &q_mutex, &barrier);
        int res = pthread_create(&mapper_threads[i], NULL, mapper::executor, (void*)info);

        if (res)
        {
            exit(-1);
        }
    }

    for (int i = 0; i < reducers; i++)
    {
        reducer::Info* info = new reducer::Info(i, &mapper_res, &barrier);
        int res = pthread_create(&reducer_threads[i], NULL, reducer::executor, (void*)info);

        if (res)
        {
            exit(-1);
        }
    }

    for (auto& thr : mapper_threads) { (void) pthread_join(thr, NULL); }
    for (auto& thr : reducer_threads) { (void) pthread_join(thr, NULL); }

    return 0;
}