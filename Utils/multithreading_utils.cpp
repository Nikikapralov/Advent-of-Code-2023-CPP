#include<thread>
#include<mutex>
#include<queue>
#include<vector>
#include<functional>
#include<iostream>

int get_queue_amount(int);


template<typename DataType>
void fill_queues(std::queue<std::queue<DataType>>& queues,
                                             const std::vector<DataType>& data){
    std::cout << "Master thread: Filling queues." << std::endl;
    for (auto entry: data){
        std::queue<DataType> current_queue = queues.front();
        current_queue.push(entry);
        queues.pop();
        queues.push(current_queue);
    }
}

template<typename DataType>
std::queue<std::queue<DataType>> generate_queues(const std::vector<DataType>& data){
    std::cout << "Master thread: Generating queues." << std::endl;
    int queue_count = get_queue_amount(data.size());
    std::queue<std::queue<DataType>> queue_wrapper;
    for (int i {0}; i < queue_count; ++i){
        queue_wrapper.emplace(std::queue<DataType> {});
    }
    return queue_wrapper;
}

int get_queue_amount(int amount_entries){
    const int min_per_thread = 1;
    const int max_amount = (amount_entries + min_per_thread - 1) / min_per_thread;
    const int cpu_thread_count = std::thread::hardware_concurrency();
    const int queue_amount = cpu_thread_count <= max_amount ? cpu_thread_count : max_amount;
    return queue_amount;
}

template <typename DataType, typename CollectionType>
void launch_threads(

        void (*func)(std::queue<DataType>, CollectionType &, std::mutex &, int),
        int& total_results,
        std::mutex& total_lock_mutex,
        std::queue<std::queue<std::string>>& queues) {

    std::cout << "Master thread: Launching threads" << std::endl;
    std::vector<std::thread> vector_threads{};
    int thread_number {1};

    while (!queues.empty()){
        std::queue<DataType> current_queue = queues.front();
        queues.pop();
        vector_threads.emplace_back(std::thread(func, current_queue,
                                                std::ref(total_results), std::ref(total_lock_mutex),
                                                thread_number));
        ++thread_number;
    }

    for (auto &current_thread: vector_threads){
        if (current_thread.joinable()){
            current_thread.join();
            std::cout << "Thread Joined" << std::endl;
        }
    }
}