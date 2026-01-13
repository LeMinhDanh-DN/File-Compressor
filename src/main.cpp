#include "HuffmanTree.h"
#include "Bitwriter.h"
#include <iostream>
#include <fstream>

int main(){
    // DATA
    std::ifstream inp("../data/INP.txt");
    std::ofstream out("../data/OUT.txt", std::ios::binary);

    std::string text = "";
    std::string line = "";
    while(getline(inp, line)){
        text += line + '\n';
    }

    // COMPRESSION

    //convert to bits
    Huffmantree DSA;

    DSA.built(text);
    std::map<char,std::string> encode = DSA.getENcodes();

    //write
    Bitwriter writer;
    for(char c: text){
        writer.write(encode[c], out);
    }
    writer.flush(out);

    inp.close();
    out.close();

    return 0;
}