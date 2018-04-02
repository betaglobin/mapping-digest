#include "declarations.h"

void Mapper::reading_file() {

    using namespace std;
    char file_name[20];
    bool cond = true;
    position = 0;
    FILE *reading;
    char seq;

    while (cond) {
        cout << "Provide a name of a multiset of cuts-containing file:" << endl;
        cin >> file_name;
        reading = fopen(file_name, "r");

        if (reading == NULL) {
            cout << "There is no such file!" << endl;
        } else {
            while ((seq = fgetc(reading)) != EOF) {
                position += 1;
            }
            cond = false;
        }
        fclose(reading);
    }

    reading = fopen(file_name, "r");
    position += 1;
    file.resize(position);

    int i = 0;
    while ((seq = fgetc(reading)) != EOF) {
        file[i] = seq;
        i += 1;
    }

    file[i] = ' ';
    fclose(reading);

    int iter = 0;
    for (int z = 0; z < position; z++) {
        iter += 1;
        if (file[z] == ' ') {
            pos_of_spaces.push(z);
        }
    }
}

void Mapper::merge_numbers() {

    int index = 0;
    std::queue<int> buffer;
    unsigned long queue_size = 0;

    while(!pos_of_spaces.empty()){
        int coord = pos_of_spaces.front();

        std::string score(&file[index], &file[coord]);
        int val = std::stoi(score);
        buffer.push(val);
        queue_size ++;
        index = coord+1;
        pos_of_spaces.pop();
    }

    multiset.resize(queue_size);
    int i = 0;
    while (!buffer.empty()) {
        int val = buffer.front();
        multiset[i] = val;
        buffer.pop();
        i++;
    }

    bubble_sort((int)queue_size);
    multi_len = queue_size;

    for (i = 0; i < queue_size; i++){
        std::cout<<multiset[i]<<std::endl;
    }

    std::string step;
    while (true){
        std::cout<<"Provide a number of cuts:"<<std::endl;
        std::cin>> step;
        cuts = stoi(step);

        if (queue_size == (cuts+2)*(cuts+1)/2) {
            map_len = cuts+1;
            break;
        }
        std::cout<<"Wrong number of cuts!"<<std::endl;
    }
};


void Mapper::bubble_sort(int size) {

    int j; int i; int temp;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1; j++) {
            if (multiset[j] > multiset[j + 1]){
                temp = multiset[j];
                multiset[j] = multiset[j + 1];
                multiset[j + 1] = temp;
            }
        }
    }
}

void Mapper::searching() {

    int hit = 0;
    std::vector <int> result; std::vector <int> used;

    map.resize(map_len); result.resize(map_len); used.resize(multi_len);

    for (int i = 0; i < map_len; i++) {
        map[i] = 0;
        result[i] = 0;
    }

    for (int i = 0; i < multi_len; i++)
        used[i] = 0;


    tick = clock();
    int first_el = multiset[multi_len-1] - multiset[multi_len-2];

    int index = 0;

    for (int i = 0; i < multi_len; i++){
        if(multiset[i] == first_el){        //mark the first value as taken
            used[i] = 1;
            break;
        }
    }

    backtracking(1, first_el, index, multi_len, map_len, multiset, result, used, &hit);


    if (hit == 0) {
        std::cout << "A map for provided multiset does not exist!" << std::endl;
        long double total = (long double) (tack - tick) / CLOCKS_PER_SEC;
        std::cout << "Total searching time: " << total << " sec." << std::endl;
    }

    else if  (hit == 1) {
        long double total = (long double) (tack - tick) / CLOCKS_PER_SEC;
        std::cout << "Found a map in: " << total << " sec." << std::endl;
        for (int i = 0; i < map_len; i++){
            std::cout<<map[i]<<" ";
        }
    }

}

int Mapper::backtracking(int first_time, int element, int index, unsigned long upp_bound, unsigned long result_len,
                           std::vector<int> multiset, std::vector<int> result, std::vector<int> used, int *hit) {
    using namespace std;
    result[index] = element;    //add an element to the potential solution set
                                //cout<<"Inspecting element: "<<element<<endl;
    if (first_time == 0) {
        for (int j = 0; j < upp_bound; j++) {

            if (multiset[j] == result[index] && used[j] == 0) {
                used[j] = 1;
                break;      //break is a must, because there can be repetitions of the same element in the multiset
            }

        }
    }

    int current = result[index];

    std::vector<int> backup_used;
    backup_used.resize(multi_len);

    for (int i = 0; i < multi_len; i++)
        backup_used[i] = used[i];

    int sum;
    int missing = 0;
    for (int k = index; k >= 0; k--) {

        if (missing == 0) {

            if (first_time == 1)
                sum = current;

            else if (k > 0)
                sum = current + result[k - 1];

            if (k != 0) {
                for (int i = 0; i < multi_len; i++) {

                    if (sum == multiset[i] && used[i] == 0) { //if the value exists in the multiset and haven't been taken yet
                        used[i] = 1;    //then mark this as taken
                        current = sum;  //next time total sum is the value that was before + a new one
                        break;

                    }
                    else if (i == multi_len - 1) {
                        missing = 1;            //there is no such sum in the multiset!
                        result[index] = 0;      //don't take it and stop inspecting
                        break;
                    }
                }
            }
        }
    }

    if (missing == 1) {
        for (int i = 0; i < multi_len; i++) {
            used[i] = backup_used[i];       //if inspecting value turned out to be wrong, update taken numbers
        }
    }

    if (index == result_len-1 && missing == 0) {
        *hit = 1;
        tack = clock();
        for (int i = 0; i < result_len; i++)
            map[i] = result[i];
    }

    else if (*hit == 0 && missing == 0) {

        for (int k = 0; k < multi_len; k++) {
            if (*hit == 1)
                break;

            if (used[k] == 0) {
                element = multiset[k];
                backtracking(0, element, index+1, multi_len, map_len, multiset, result, used, hit);

            }
        }
    }
}