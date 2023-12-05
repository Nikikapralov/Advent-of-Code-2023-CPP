#include<fstream>
#include<vector>
#include<string>
#include<iostream>

std::vector<std::string> extract_data_from_file(const std::string& file_path){
    std::vector<std::string> results_vector {};
    std::fstream new_file;
    new_file.open(file_path, std::ios::in);
    if (new_file.is_open()){
        std::string line;
        while (std::getline(new_file, line)) {
            results_vector.push_back(line);
        }
        new_file.close();
    }
    return results_vector;
};

