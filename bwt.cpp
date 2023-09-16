#include "bwt.h"
#include <vector>
#include <algorithm>

using namespace std;

vector<unsigned char> shift_left(const vector<unsigned char>& mas) {
    vector<unsigned char> buf_str = mas;
    unsigned char buf_sim = buf_str.front();
    for (size_t i = 1; i < buf_str.size(); i++) {
        buf_str[i - 1] = buf_str[i];
    }
    buf_str.back() = buf_sim;
    return buf_str;
}

vector<unsigned char> bwt_encod(const vector<unsigned char>& mas) {
    vector<vector<unsigned char>> shift_mas(mas.size(), vector<unsigned char>(mas.size()));
    if (!mas.size()) throw 1;
    shift_mas[0] = mas;    
    for (size_t i = 1; i < mas.size(); i++) {
        shift_mas[i] = shift_left(shift_mas[i - 1]);
    }
    sort(shift_mas.begin(), shift_mas.end());
    vector<unsigned char> bwt_result(mas.size() + 1);
    size_t index_initial_mas = -1;
    for (size_t i = 0; i < shift_mas.size(); i++) {
        bwt_result[i] = shift_mas[i].back();
        if (mas == shift_mas[i]) {
            index_initial_mas = i;
        }
    }
    bwt_result.back() = index_initial_mas;
    return bwt_result;
}

vector<unsigned char> bwt_decod(const vector<unsigned char>& mas) {
    vector<pair<unsigned char,size_t>> sort_mas;
    for (size_t i = 0; i < mas.size() - 1; i++) {
        sort_mas.push_back({ mas[i],i });
    }
    sort(sort_mas.begin(), sort_mas.end());
    size_t select = mas.back();
    vector<unsigned char> ret(sort_mas.size());
    for(auto& elem : ret){
        elem = sort_mas[select].first;
        select = sort_mas[select].second;
    }
    return ret;
}