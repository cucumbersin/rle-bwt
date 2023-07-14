#include "rle.h"
#include <vector>
#include <exception>
#include <stdexcept>

using namespace std;

vector<unsigned char> encode(const vector<unsigned char>& str){
    vector<unsigned char> str_buf;
    if(!str.size()) throw 5;
    unsigned char slect_elem = str[0];
    unsigned char count = 1;
    for(size_t i = 1; i < str.size(); i++){
        if(str[i] == slect_elem && count < 250){
            count++;
        }else{
            str_buf.push_back(count);
            str_buf.push_back(slect_elem);
            slect_elem = str[i];
            count = 1;
        }
    }
    return str_buf;
}

vector<unsigned char> decode(const vector<unsigned char>& str){
    vector<unsigned char> str_buf;
    if(!str.size()) throw 5;    
    for(size_t i = 0; i < str.size(); i += 2){
        for(size_t j = 0; j < static_cast<size_t>(str[i]); j++){
            str_buf.push_back(str[i+1]);
        }
    }
    return str_buf;
}