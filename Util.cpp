#include "Util.hpp"
#include <iostream> 
#include <sstream> 

void Util::string_split(string p_input, string p_delim, vector<string> & p_vec)
{
    int last_delim=0;
    int current_delim=0;
    while (current_delim != string::npos)
    {
        current_delim = p_input.find(p_delim, last_delim+1);
        if (current_delim != string::npos)
        {
            p_vec.push_back(p_input.substr(last_delim+1, current_delim-last_delim));
        }
        else
        {
            p_vec.push_back(p_input.substr(last_delim+1, string::npos));
        }
        last_delim = current_delim;
    }
}

string Util::string_strip(string p_input, string p_delim)
{
    while (p_input.find(p_delim) != string::npos)
    {
        p_input.erase(p_input.find(p_delim), 1);
    }
    return p_input;
}

int Util::string_to_int(string p_string)
{
    int output = 0;
    stringstream(p_string) >> output;
    return output;
}

unsigned int Util::string_to_uint(string p_string)
{
    unsigned int output = 0; 
    stringstream(p_string) >> output;
    return output;
}

void Util::clear_buffer(char * buffer, int size)
{
    memset(buffer, 0, size);
}


uint16 Util::read_uint8(fstream & file, bool do_print)
{
    const int size = 1;
    char * buffer = new char[8];
    file.read(buffer,size);
    uint8 output = (uint8)buffer[0];
    if (do_print)
    {
        printf("Read uint8: %u (hex: %04X)\n", output, output);
    }
    delete[] buffer;
    return output;
}

uint16 Util::read_uint16(fstream & file, bool do_print)
{
    const int size = 2;
    char * buffer = new char[8];
    file.read(buffer,size);
    uint16 output = ((uint16)buffer[1]<<8 & 0xFF00) | ((uint16)buffer[0] & 0xFF);
    if (do_print)
    {
        printf("Read uint16: %u (hex: %04X)\n", output, output);
    }
    delete[] buffer;
    return output;
}

uint32 Util::read_uint32(fstream & file, bool do_print)
{
    const int size = 4;
    char * buffer = new char[8];
    file.read(buffer,size);
    uint32 output = ((uint32)buffer[0] & 0xFF) | ((uint32)buffer[1]<<8 & 0xFF00) | ((uint32)buffer[2]<<16 & 0xFF0000) | ((uint32)buffer[3]<<24 & 0xFF000000);
    if (do_print)
    {
        printf("Read uint32: %lu (hex: %08lX)\n", output, output);
    }
    delete[] buffer;
    return output;
}

string Util::read_string(fstream & file, bool do_print, const int p_size, char p_delim)
{
    char * buffer = new char[p_size];
    clear_buffer(buffer, p_size);
    file.getline(buffer,p_size,p_delim);
    string output = string(buffer);
    if (do_print)
    {
        printf("Read string: %s\n", output.c_str());
    }
    delete[] buffer;
    return output;
}

sint16 Util::read_sint16(fstream & file, bool do_print)
{
    const int size = 2;
    char * buffer = new char[8];
    file.read(buffer,size);
    sint16 output = ((uint16)buffer[1]<<8 & 0xFF00) | ((uint16)buffer[0] & 0xFF);
    if (do_print)
    {
        printf("Read uint16: %i (hex: %04X)\n", output, output);
    }
    delete[] buffer;
    return output;
}
