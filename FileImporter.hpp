#ifndef FILE_IMPORTER_HPP
#define FILE_IMPORTER_HPP

#include <stdio.h>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <vector>

using namespace std;

typedef unsigned short int uint16;
typedef unsigned long int uint32;

class FileImporter
{
public:
    FileImporter();
    ~FileImporter();
    bool import(char * p_file_path);
    static uint16 read_uint16(fstream & p_file, bool do_print = false);
    static uint32 read_uint32(fstream & p_file, bool do_print = false);
    static void clear_buffer(char * buffer, int size);
private:
    struct FileSection 
    {
    public:
        char name[8];
        uint32 virtual_size;
        uint32 virtual_address_rva;
        uint32 raw_data_size;
        uint32 pointer_raw_data;
        uint32 pointer_relocations;
        uint32 pointer_line_numbers;
        uint16 number_of_relocations;
        uint16 number_of_line_numbers;
        uint32 characteristics;
        FileSection();
    };
    enum RsrcType
    {
        RSRC_UNKNOWN = 0x0,
        RSRC_NAME = 0x1,
        RSRC_ID = 0x2,
    };
    class RsrcTable;
    
    class RsrcEntry
    {
    public:
        uint32 address;
        RsrcTable * parent;
        RsrcType type;
        RsrcEntry(uint32 p_address = 0, RsrcTable * p_parent = nullptr, RsrcType p_type = RSRC_UNKNOWN, uint32 p_name_or_id = 0);
        char * get_name(fstream & p_file);
        uint32 get_id();
        ~RsrcEntry();
    private:
        uint32 id;
        uint32 name_address;
        char * name;
    };
    
    class RsrcTable
    {
    public:
        uint32 address;
        RsrcTable * parent;
        vector<RsrcEntry*> entries;
        vector<RsrcTable*> subtables;
        uint16 number_of_name_entries;
        uint16 number_of_id_entries;
        bool has_unprocessed_children;
        bool unprocessed;
        RsrcType type;
        RsrcTable(uint32 p_address = 0, RsrcTable * p_parent = nullptr, RsrcType p_type = RSRC_UNKNOWN, uint32 p_name_or_id = 0);
        char * get_name(fstream & p_file);
        uint32 get_id();
        ~RsrcTable();
    private:
        uint32 id;
        uint32 name_address;
        char * name;
    };
    void load_rsrc(FileSection * p_section, fstream & p_file);
    void load_rsrc_table(FileSection * p_section, fstream & p_file, RsrcTable * p_table);
    void load_rsrc_entry(FileSection * p_section, fstream & p_file, RsrcEntry * p_entry);
    vector<RsrcTable*> all_rsrc_tables; //for cleanup
    vector<RsrcEntry*> all_rsrc_entries; //also for cleanup
    
    //constants that arent actually const because idk how to make that work
    char dos_header_signature[2];
    char pe_header_signature[4];
    uint32 addr_pointer_pe_header;
    

};

#endif // FILE_IMPORTER_HPP
