#include<iostream>
#include<vector>
#include<string>
#include "Utils/file_crud_utils.cpp"
#include "Day_1/day_1_1.cpp"


int main(){
    std::string file_path {"/home/archardor/Desktop/GitRepo/Advent-of-Code-2023-CPP/Day_1/puzzle_input.txt"};
    std::vector<std::string> input = extract_data_from_file(file_path);
    int result = day_1_solution(input);
    std::cout << result << std::endl;
};