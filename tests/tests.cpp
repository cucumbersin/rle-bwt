#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../rle.h"
#include "../bwt.h"

using namespace std;

TEST(rle,encod1){

    vector<unsigned char> mas1,mas2;
    string str1 = "abcda";
    for(auto elem:str1){
        mas1.push_back(elem);
    }
    string str2 = "abcda";
    mas2.push_back(5 + 128);
    for(auto elem:str2){
        mas2.push_back(elem);
    }
    EXPECT_EQ(encode(mas1),mas2);    
}

TEST(rle,encod2){
    vector<unsigned char> mas22 = {4,'a',2,'b'};
    vector<unsigned char> mas21 = {'a','a','a','a','b','b'};
    EXPECT_EQ(encode(mas21),mas22);
}

TEST(rle,encod3){
    vector<unsigned char> mas22 = {4,'a',2,'b',130,'c','b',2,'c'};
    vector<unsigned char> mas21 = {'a','a','a','a','b','b','c','b','c','c'};
    EXPECT_EQ(encode(mas21),mas22);
}

TEST(bwt,bwt1){
    vector<unsigned char> mas22 = {'2',0};
    vector<unsigned char> mas21 = {'2'};
    auto mas_buf = bwt_encod(mas21);
    EXPECT_EQ(mas_buf,mas22);
    EXPECT_EQ(bwt_decod(mas_buf),mas21);
    vector<unsigned char> mas123 = {'0','1','1'};
    EXPECT_EQ(bwt_decod(bwt_encod(mas123)),mas123);
    mas123 = {'0','1'};
    EXPECT_EQ(bwt_decod(bwt_encod(mas123)),mas123);
    mas123 = {'0'};
    EXPECT_EQ(bwt_decod(bwt_encod(mas123)),mas123);
}