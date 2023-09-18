#include <string>
#include <iostream>
#include "rle.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include "bwt.h"
#include "task_completion_percentage.h"

using namespace std;

const size_t size_bwt_string = 150;

int main(){
    
    cout << "e = endcod,d - decod" << endl;
    char select;    
    cin >> select;
    //select = 'e';    
    switch(select){
        case('e'):{
            string file_encode_name;
            cout << "read file name with extension:";
            cin >> file_encode_name;
            //file_encode_name = "image2.bmp";
            ifstream encode_file(file_encode_name,std::ifstream::binary);
            if(!encode_file.is_open()){
                cout << "not open";
                return 0;
            }
            string extension;
            for (int i = file_encode_name.size() - 1; i > 0; i--)
            {
                if(file_encode_name[i] == '.'){
                    extension = file_encode_name.substr(i + 1,file_encode_name.size());
                }
            }         
            vector<unsigned char> byt_mas,byt_mas_bwt;
            while (!encode_file.eof())
            {
                byt_mas_bwt.push_back(encode_file.get());
                if(byt_mas_bwt.size() == size_bwt_string){
                    vector<unsigned char> buf = bwt_encod(byt_mas_bwt);
                    for(auto elem: buf){
                        byt_mas.push_back(elem);
                    }
                    byt_mas_bwt.clear();
                }
            }
            if(byt_mas_bwt.size() == size_bwt_string){
                    vector<unsigned char> buf = bwt_encod(byt_mas_bwt);
                    for(auto elem: buf){
                        byt_mas.push_back(elem);
                    }
                    byt_mas_bwt.clear();
            }
            encode_file.close();
            cout << endl << "size_prev:" << byt_mas.size() << endl;
            vector<unsigned char> mas = encode(byt_mas);
            byt_mas.clear();
            byt_mas.shrink_to_fit();
            cout << endl << "size_now:" << mas.size() << endl;
            cout << "write file name without extension:";
            string file_write;
            cin >> file_write;
            ofstream export_file(file_write + ".rle",std::ifstream::binary);
            export_file << static_cast<unsigned char>(extension.size());
            for(const auto elem : extension){
                export_file << elem;
            }
            for (size_t i = 0; i < mas.size(); i++)
            {
                export_file << mas[i];
            }            
            break;
        }
        case('d'):{
            string file_decod;
            cout << "read file name without extension:";
            cin >> file_decod;            
            ifstream decode_file(file_decod + ".rle",std::ifstream::binary);
            if(!decode_file.is_open()){
                cout << "not open";
                return 0;
            }
            string extension;
            int size_extension = decode_file.get();            
            for (size_t i = 0; i < size_extension; i++)
            {
                extension.push_back(decode_file.get());
            }            
            vector<unsigned char> byt_mas;
            while (!decode_file.eof())
            {
                byt_mas.push_back(decode_file.get());                
            }
            decode_file.close();                
            vector<unsigned char> mas = decode(byt_mas);
            size_t index = 0;
            vector<unsigned char> mas_decod_bwt;
            mas_decod_bwt.reserve(mas.size());            
            for (size_t i = 0;i < mas.size() / (size_bwt_string + 1); i++)
            {
                completion_percentage(i,mas.size() / (size_bwt_string + 1));
                vector<unsigned char> buf;
                for(size_t i = 0;i < (size_bwt_string + 1);index++,i++){
                    buf.push_back(mas[index]);
                }
                vector<unsigned char> buf1 = bwt_decod(buf);
                for(auto elem:buf1){
                    mas_decod_bwt.push_back(elem);
                }
            }
            vector<unsigned char> buf;
            for(size_t i = 0;i < mas.size() % (size_bwt_string + 1);index++,i++){
                buf.push_back(mas[index]);
            }
            if(!buf.empty()){
                buf = bwt_decod(buf);//work?
                for(auto elem:buf){
                    mas_decod_bwt.push_back(elem);
                }
            }
            cout << endl << "write file name without extension:";
            string file_write;
            cin >> file_write;
            //file_write = "image11";
            ofstream export_file(file_write + '.' + extension,std::ofstream::binary);
            for (size_t i = 0; i < mas_decod_bwt.size(); i++)
            {                    
                export_file << mas_decod_bwt[i];
            }
            break;
        }
    }    
    return 0;
}