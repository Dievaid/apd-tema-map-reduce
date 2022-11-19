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

    //! Consuming CLI args
    int mappers = (data::controller::get().mappers() = atoi(argv[1]));
    int reducers = (data::controller::get().reducers() = atoi(argv[2]));
    std::ifstream fin(argv[3]);

    int no_files = 0;
    fin >> no_files;

    //? Preparing the mapper results storage
    auto& mapper_res = data::controller::get().mapper_results();
    mapper_res = std::vector<std::set<long long>*>(mappers);
    for (int i = 0; i < mappers; i++)
    {
        mapper_res[i] = new std::set<long long>();
    }

    //! Enqueing all the files for the mapping procedure
    std::queue<std::string> file_queue;
    for (int i = 0; i < no_files; i++)
    {
        std::string file;
        fin >> file;
        file_queue.push(file);
    }

    //? Mutex for locking the queue inside the mapper executor
    //? Barrier used for waiting the mappers to finish before the reducers take control
    pthread_mutex_t q_mutex;
    pthread_barrier_t barrier;
    pthread_mutex_init(&q_mutex, NULL);
    pthread_barrier_init(&barrier, NULL, mappers + reducers);

    pthread_t mapper_threads[mappers];
    pthread_t reducer_threads[reducers];

    //! Kickstarting all the necessary threads
    for (int i = 0; i < mappers + reducers; i++)
    {
        //? Starting the mappers
        if (i < mappers)
        {
            //* Passing necessary data for executor function
            mapper::Info* info = new mapper::Info(i, &file_queue, &q_mutex, &barrier);
            int res = pthread_create(&mapper_threads[i], NULL, mapper::executor, (void*)info);

            if (res)
            {
                exit(-1);
            }
        }
        //? Starting the reducers
        else
        {
            //* Passing necessary data for executor function
            reducer::Info* info = new reducer::Info(i - mappers, &barrier);
            int res = pthread_create(&reducer_threads[i - mappers], NULL, reducer::executor, (void*)info);

            if (res)
            {
                exit(-1);
            }
        }
    }

    //! Join all the threads right after starting
    for (int i = 0; i < mappers + reducers; i++)
    {
        if (i < mappers)
        {
            (void) pthread_join(mapper_threads[i], NULL);
        }
        else
        {
            (void) pthread_join(reducer_threads[i - mappers], NULL);
        }
    }

    return 0;
}