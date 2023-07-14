#include <string>
#include <iostream>
#include "rle.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include "bwt.h"

using namespace std;

int main(){
    
    cout << "e = endcod,d - decod" << endl;
    char select;    
    cin >> select;
    try
    {    
        switch(select){
            case('e'):{
                string file_encode_name;
                cout << "read file name with extension:";
                cin >> file_encode_name;
                ifstream encode_file(file_encode_name,std::ifstream::binary);
                if(!encode_file.is_open()){
                    cout << "not open";
                    return 0;
                }
                vector<unsigned char> byt_mas;
                while (!encode_file.eof())
                {
                    byt_mas.push_back(encode_file.get());
                }
                encode_file.close();
                vector<unsigned char> mas = encode(byt_mas);
                cout << "write file name without extension:";
                string file_write;
                cin >> file_write;                
                ofstream ecsport(file_write + ".rle",std::ifstream::binary);
                for (size_t i = 0; i < mas.size(); i++)
                {
                    ecsport << mas[i];
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
                vector<unsigned char> byt_mas;
                while (!decode_file.eof())
                {
                    byt_mas.push_back(decode_file.get());                
                }
                decode_file.close();                
                vector<unsigned char> mas = decode(byt_mas);
                cout << "write file name without extension:";
                string file_write;
                cin >> file_write;
                ofstream ecsport(file_write + ".bmp",std::ofstream::binary);
                for (size_t i = 0; i < mas.size(); i++)
                {                    
                    ecsport << mas[i];
                }
                break;
            }
        }
    }
    catch(int e)
    {
        cout << e;
    }
    return 0;
}