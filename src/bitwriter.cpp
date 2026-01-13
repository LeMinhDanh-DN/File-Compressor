#include "Bitwriter.h"
#include <iostream>
#include <fstream>

Bitwriter::Bitwriter(){
    buffer = cnt = 0;
}

void Bitwriter::write(const std::string &bits, std::ofstream &out){
    for(char c : bits){
        cnt ++ ;
        buffer <<= 1;
        buffer |= (c == '1' ? 1 : 0);

        if(cnt == 8){
            out.put(buffer);
            cnt = buffer = 0;
        }
    }

}

void Bitwriter::flush(std::ofstream &out){
    if(cnt != 0){
        buffer <<= (8-cnt);
        out.put(buffer);
        buffer = cnt = 0;
    }
}