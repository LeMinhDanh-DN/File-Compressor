#ifndef BITWRITER_H
#define BITWRITER_H
#include <iostream>
#include <fstream>

class Bitwriter{
    private:
        char buffer; 
        int cnt;
    public:
        void write(const std::string& bits, std::ofstream& out);
        void flush(std::ofstream& out);
        Bitwriter();

        // ~Bitwriter();
};

#endif