#include<string>
#include<vector>
#include<iostream>
#include<queue>
#include<mutex>
#include "Utils/multithreading_utils.cpp"

int get_number_from_line(const std::string&);
void day_1_thread_function(std::queue<std::string>, int&, std::mutex&, int);


int day_1_solution(const std::vector<std::string>& input){
    int total_results {0};
    std::mutex total_results_lock;
    std::queue<std::queue<std::string>> queues = generate_queues(input);
    fill_queues(queues, input);
    launch_threads(&day_1_thread_function, total_results, total_results_lock, queues);
    return total_results;
}

void day_1_thread_function(std::queue<std::string> data_queue,
                           int& total_results,
                           std::mutex& total_results_lock,
                           int thread_number){

    int current_result {0};
    std::cout << "Thread with number: " << thread_number << " is working" << std::endl;
    while (!data_queue.empty()){
        std::string current_data = data_queue.front();
        int result = get_number_from_line(current_data);
        std::cout << "Thread with number: " << thread_number << " has result: " << result << std::endl;
        current_result += result;
        data_queue.pop();
    }
    std::lock_guard<std::mutex> lock (total_results_lock);
    total_results += current_result;
}



int get_number_from_line(const std::string& line){

    char first_number;
    char second_number;
    bool first_time {true};

    for (auto element: line){

        if (isdigit(element)){
            if (first_time){
                first_number = element;
                second_number = element;
                first_time = false;
            }
            second_number = element;
        }
    }

    std::string string_result;
    string_result += first_number;
    string_result +=  second_number;

    int result = std::stoi(string_result);
    return result;
}