#include "rle.h"
#include <vector>
#include <exception>
#include <stdexcept>

using namespace std;

vector<unsigned char> encode(const vector<unsigned char>& str){
    vector<unsigned char> str_buf;
    if(!str.size()) throw 5;
    unsigned char slect_elem = str[0];
    vector<unsigned char> non_repeating_elem;
    unsigned char count = 1,non_repeating_count = 0;
    for(size_t i = 1; i < str.size(); i++){
        if(non_repeating_count == 127){
            str_buf.push_back(non_repeating_count + 128);
                for(auto elem:non_repeating_elem){
                    str_buf.push_back(elem);
                    non_repeating_count = 0;
                }
                non_repeating_elem.clear();
        }
        if(str[i] == slect_elem && count < 127){
            count++;
            if(!non_repeating_elem.empty()){
                str_buf.push_back(non_repeating_count + 128);
                for(auto elem:non_repeating_elem){
                    str_buf.push_back(elem);
                    non_repeating_count = 0;
                }
                non_repeating_elem.clear();
            }
        }else{
            if(count == 1){
                non_repeating_elem.push_back(slect_elem);
                slect_elem = str[i];
                non_repeating_count++;
            }else{
                str_buf.push_back(count);
                str_buf.push_back(slect_elem);
                slect_elem = str[i];
                count = 1;
            }
        }
    }
    if(count == 1){
        non_repeating_elem.push_back(slect_elem);        
        non_repeating_count++;
    }else{
        str_buf.push_back(count);
        str_buf.push_back(slect_elem);        
    }
    if(non_repeating_count){
        str_buf.push_back(non_repeating_count + 128);
        for(auto elem:non_repeating_elem){
            str_buf.push_back(elem);
            non_repeating_count = 0;
        }
        non_repeating_elem.clear();
    }
    return str_buf;
}

vector<unsigned char> decode(const vector<unsigned char>& str){
    vector<unsigned char> str_buf;
    if(!str.size()) throw 5;
    for(size_t i = 0; i < str.size(); i += 2){
        if(str[i] & 128){
            for(size_t j = 0; j < static_cast<size_t>(str[i] - 128); j++){            
                str_buf.push_back(str[i + j + 1]);
            }
            i += str[i] - 129;//128 +1
        }else{
            for(size_t j = 0; j < static_cast<size_t>(str[i]); j++){            
                str_buf.push_back(str[i+1]);
            }
        }
    }
    return str_buf;
}