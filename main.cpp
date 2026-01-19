#include "HuffmanTree.h"
#include "Bitwriter.h"
#include "CLI11.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <iomanip>

void compress(const std::string& inf, const std::string& outf){
    std::ifstream inp(inf, std::ios::binary); // input
    std::ofstream out(outf, std::ios::binary); // output
    if (!inp) {
        std::cerr << "Loi: Khong tim thay file input: " << inf << std::endl;
        return;
    }

    std::vector<char> buffer(1024 * 1024); // 1MB buffer
    std::map<char,int> freq;
    while(inp){
        inp.read(buffer.data(), buffer.size());
        
        // streamsize = long long
        std::streamsize cnt_byte = inp.gcount(); // -> getcount() so luogn ky tu lay dc
        for(int i = 0; i < cnt_byte; i++){
            char c = buffer[i];
            freq[c]++;
        }
    }

    //convert to bits
    Huffmantree DSA;

    DSA.built_frommap(freq);
    Huffmancode* encode = DSA.getcodes();// du lieu ma hoa

    //write freq_map in header
    //1. write map location of map size 
    int mpsize = freq.size();
    out.write(reinterpret_cast<char*>(&mpsize), sizeof(mpsize));
    
    //2. write each ch and freq
    for(auto const&[key,val] : freq){
        char c = key;
        int cnt = val;
        out.put(c); // ghi ky tu
        out.write(reinterpret_cast<char*>(&cnt), sizeof(cnt));
    }

    inp.clear();
    inp.seekg(0, std::ios::beg); // move read pointer to beginning
    //write in zip file
    Bitwriter writer;
    char c;
    
    while(inp){
        inp.read(buffer.data(), buffer.size());
        std::streamsize cnt_byte = inp.gcount();

        for(int i = 0; i< cnt_byte; i++){
            char c = buffer[i];

            unsigned char u_c = (unsigned char)c;
            Huffmancode h_c = encode[u_c];
            writer.write(h_c.code, h_c.len, out);
        }
    }

    writer.flush(out);

    inp.close();
    out.close();

}

void decompress(const std::string& inf, const std::string& outf){
    std::ifstream inp(inf,std::ios::binary);
    std::ofstream out(outf,std::ios::binary);

    if (!inp) { 
        std::cerr << "Loi: Khong tim thay file input: " << inf << std::endl;
        return;
    }

    //lay map size
    int mpsize;
    inp.read(reinterpret_cast<char*>(&mpsize), sizeof(mpsize));

    std::map<char,int> restored_mp;
    long long total = 0; // tong so ky tu

    for(int i = 1; i<= mpsize; i++){
        char c;
        inp.get(c);
        int cnt;
        inp.read(reinterpret_cast<char*>(&cnt), sizeof(cnt));

        restored_mp[c] = cnt;
        total += cnt;
    }

    // restored lai cay
    Huffmantree DSA;
    DSA.built_frommap(restored_mp);
    Node* root = DSA.getroot();

    Node *cur = root;
    char byte;
    while(inp.get(byte) && total){
        unsigned char u_byte = static_cast<unsigned char> (byte); // for safe
        for(int i = 7; i>= 0; i--){

            if(((u_byte >> i) & 1) == 0) cur = cur->l;
            else cur = cur->r;

            if(!cur->isInterval){ // ur if normal leaf
                out.put(cur->c);
                total --;
                cur = root;
            }
            if(total == 0) break;
        }
    }
    inp.close();
    out.close();
}
int main(int argc, char* argv[]){

    CLI::App app{"File compressor"};

    bool com = false;
    bool decom = false;

    std::string input;
    std::string output;

    auto* modeGroup = app.add_option_group("Mode", "select opreratin mode");
    modeGroup->add_flag("-c,--compressor", com, "compress file");
    modeGroup->add_flag("-d,--decompressor", decom, "decompress file");
    
    modeGroup->require_option(1);

    app.add_option("input", input, "inputfile")->required();
    app.add_option("output", output, "outputfile")->required();

    CLI11_PARSE(app, argc, argv);

    if(com){
        compress(input, output);
    }
    else{
        decompress(input,output);
    }
    return 0;
}