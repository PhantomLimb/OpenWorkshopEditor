#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef signed short int sint16;
typedef unsigned long int uint32;

class Util
{
public:
    static void string_split(string p_input, string p_delim, vector<string> & p_vec);
    static string string_strip(string p_input, string p_delim);
    static int string_to_int(string p_string);
    static unsigned int string_to_uint(string p_string);
    
    static uint16 read_uint8(fstream & p_file, bool do_print = false);
    static uint16 read_uint16(fstream & p_file, bool do_print = false);
    static uint32 read_uint32(fstream & p_file, bool do_print = false);
    static string read_string(fstream & p_file, bool do_print = false, const int p_size=512, char p_delim='\0');
    static sint16 read_sint16(fstream & p_file, bool do_print = false);
    static void clear_buffer(char * buffer, int size);
};

#endif // UTIL_HPP
