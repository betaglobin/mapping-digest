#ifndef METHODS_H_
#define METHODS_H_

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>

class Mapper {
public:
    void reading_file();
    void merge_numbers();
    void bubble_sort(int size);
    void searching();
    int backtracking(int first_time, int element, int index, unsigned long upp_bound, unsigned long length,
                     std::vector<int> multiset, std::vector<int> result, std::vector<int> used, int *hit);

private:
    std::vector<int>multiset;
    unsigned long multi_len;
    std::vector<int>map;
    unsigned long map_len;

    std::vector<char>file;
    std::queue<int>pos_of_spaces;
    int cuts;
    int position;
    clock_t tick, tack;
};



#endif
