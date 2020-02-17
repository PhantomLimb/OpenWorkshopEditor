#include "FileImporter.hpp"
#include "LnzLoader.hpp"

FileImporter::FileImporter()
{
    memcpy(dos_header_signature, "MZ", 2);
    memcpy(pe_header_signature, "PE\0\0", 4);
    addr_pointer_pe_header = 0x3C;
    lnz_loaded = false;
}

FileImporter::~FileImporter()
{
}

FileImporter::FileSection::FileSection()
{
    memset(name, 0, 8);
}


FileImporter::RsrcEntry::RsrcEntry(uint32 p_address, RsrcTable * p_parent, RsrcType p_type, uint32 p_name_or_id)
{
    address = p_address;
    parent = p_parent;
    type = p_type;
    if (type == RSRC_NAME)
    {
        name_address = p_name_or_id;
    }
    else if (type == RSRC_ID)
    {
        id = p_name_or_id;
    }
    name = "";
}

string FileImporter::RsrcEntry::get_name(fstream & p_file)
{
    // make sure the resource actually HAS a name
    if (type != RSRC_NAME)
    {
        return "";
    }
    if (name == "")
    {
        //save our current position in the file so we can return to it
        int original_position = p_file.tellg();
        printf("Looking for name at: %08lX\n", name_address);
        p_file.seekg(name_address);
        uint16 length = Util::read_uint16(p_file);
        for (int i = 0; i<length; i++)
        {
            name.push_back(p_file.get());
            p_file.get(); // because there's a weird empty space between each letter
        }
        p_file.seekg(original_position);
    }
    return name;
}

FileImporter::RsrcEntry::~RsrcEntry()
{
}

FileImporter::RsrcTable::RsrcTable(uint32 p_address, RsrcTable * p_parent, RsrcType p_type, uint32 p_name_or_id)
{
    address = p_address;
    parent = p_parent;
    type = p_type;
    if (type == RSRC_NAME)
    {
        name_address = p_name_or_id;
    }
    else if (type == RSRC_ID)
    {
        id = p_name_or_id;
    }
    name = "";
    unprocessed = true;
    has_unprocessed_children = true;
}

FileImporter::RsrcTable::~RsrcTable()
{
}

string FileImporter::RsrcTable::get_name(fstream & p_file)
{
    // make sure the resource actually HAS a name
    if (type != RSRC_NAME)
    {
        return "";
    }
    if (name == "")
    {
        //save our current position in the file so we can return to it
        int original_position = p_file.tellg();
        printf("Looking for name at: %08lX\n", name_address);
        p_file.seekg(name_address);
        uint16 length = Util::read_uint16(p_file);
        for (int i = 0; i<length; i++)
        {
            name.push_back(p_file.get());
            p_file.get();
        }
        p_file.seekg(original_position);
    }
    return name;
}

uint32 FileImporter::RsrcTable::get_id()
{
    return id;
}

uint32 FileImporter::RsrcEntry::get_id()
{
    return id;
}

void FileImporter::load_rsrc_entry(FileSection * p_section, fstream & p_file, RsrcEntry * p_entry)
{
    p_file.seekg(p_entry->address);
    uint32 data_rva = Util::read_uint32(p_file);
    uint32 data_size = Util::read_uint32(p_file);
    printf("DATA RVA: %08lX\n", data_rva);
    if (p_entry->parent->type == RSRC_NAME)
    {
        printf("NAME: %s\n", p_entry->parent->get_name(p_file).c_str());
    }
    else if (p_entry->parent->type == RSRC_ID)
    {
        printf("ID: %08lX\n", p_entry->parent->get_id());
    }
    string file_type = "";
    if (p_entry->parent->parent->type == RSRC_NAME)
    {
        file_type = p_entry->parent->parent->get_name(p_file);
        printf("TYPE: %s\n", p_entry->parent->parent->get_name(p_file).c_str());
    }
    if (file_type == "LNZ" && !lnz_loaded)
    {
        lnz_loaded = true;
        p_file.seekg(data_rva);
        char * buffer = new char[data_size];
        Util::clear_buffer(buffer, data_size);
        p_file.read(buffer, data_size);
        printf("%s \n", buffer);
        LnzLoader lnz_loader;
        lnz_loader.load(string(buffer));
        delete buffer;
    }
}

bool FileImporter::import(char * p_file_path)
{
    fstream fs;
    fs.open(p_file_path, fstream::in | fstream::binary);
    //start at the beginning
    fs.seekg(0);
    //read the dos header to make sure its the right type of file
    char dos_header_buffer[16];
    Util::clear_buffer(dos_header_buffer, 16);
    fs.read(dos_header_buffer, 2);
    //if theres no DOS signature, give up!
    if (memcmp(dos_header_buffer, dos_header_signature, 2) != 0)
    {
        printf("Invalid DOS HEADER SIGNATURE: %s\n", dos_header_buffer);
        printf("Expected: %s\n", dos_header_signature);
        return false;
    }
    printf("Valid DOS HEADER SIGNATURE found.\n");
    //skip to the address of the pointer to the PE header 
    fs.seekg(addr_pointer_pe_header);
    //read the pointer...
    uint32 pointer_pe_header = Util::read_uint32(fs);
    //...now skip to the PE header
    fs.seekg(pointer_pe_header);
    char pe_header_buffer[16];
    Util::clear_buffer(pe_header_buffer, 16);
    fs.read(pe_header_buffer, 4);
    //and if there's no PE header, give up!!
    if (memcmp(pe_header_buffer, pe_header_signature, 4) != 0)
    {
        printf("Invalid PE HEADER SIGNATURE: %s\n", pe_header_buffer);
        printf("Expected: %s\n", pe_header_signature);
        return 0;
    }
    printf("Valid PE HEADER SIGNATURE found.\n");
    
    //some cool info that we dont really care about
    Util::read_uint16(fs); //machine
    //info that we do care about
    uint16 number_of_sections = Util::read_uint16(fs);
    const long int time_date_stamp = Util::read_uint32(fs);
    printf ("Time Stamp: %s", ctime(&time_date_stamp));
    Util::read_uint32(fs); //pointer to symbol table - deprecated, i guess we can ignore this
    Util::read_uint32(fs); //number of symbol tables - deprecated, ignore this too i guess???
    uint16 size_of_optional_header = Util::read_uint16(fs);
    Util::read_uint16(fs); // coff characteristics - i dont think we need this
    //skip the optional header for now because it doesnt seem important to this project
    fs.seekg(fs.tellg() + fstream::streampos(size_of_optional_header));
    //save all the file sections to a vector
    vector<FileSection*> file_sections;
    for (int i=0; i<number_of_sections; i++)
    {
        FileSection * current_section = new FileSection;
        file_sections.push_back(current_section);
        fs.read(current_section->name, 8);
        printf("Found section: %s\n", current_section->name);
        current_section->virtual_size = Util::read_uint32(fs);
        current_section->virtual_address_rva = Util::read_uint32(fs);
        current_section->raw_data_size = Util::read_uint32(fs);
        current_section->pointer_raw_data = Util::read_uint32(fs);
        current_section->pointer_relocations = Util::read_uint32(fs);
        current_section->pointer_line_numbers = Util::read_uint32(fs);
        current_section->number_of_relocations = Util::read_uint16(fs);
        current_section->number_of_line_numbers = Util::read_uint16(fs);
        current_section->characteristics = Util::read_uint32(fs);
    }
    // now iterate through the vector and process the parts we need
    for (int i=0; i<file_sections.size(); i++)
    {
        if (strcmp(file_sections[i]->name, ".rsrc") == 0)
        {
            load_rsrc(file_sections[i], fs);
        }
    }
    
    //clean up!
    for (int i=0; i<file_sections.size(); i++)
    {
        delete file_sections[i];
    }
    return true;
}

void FileImporter::load_rsrc_table(FileSection * p_section, fstream & p_file, RsrcTable * p_table)
{
    p_file.seekg(p_table->address);
    Util::read_uint32(p_file);
    Util::read_uint32(p_file);
    Util::read_uint16(p_file);
    Util::read_uint16(p_file);
    p_table->number_of_name_entries = Util::read_uint16(p_file);
    p_table->number_of_id_entries = Util::read_uint16(p_file);
    for (int i = 0; i< p_table->number_of_name_entries; i++)
    {
        uint32 name_offset = Util::read_uint32(p_file);
        name_offset = (name_offset & 0x7FFFFFFF) + p_section->pointer_raw_data;
        uint32 subdirectory_or_data_offset = Util::read_uint32(p_file);
        subdirectory_or_data_offset += p_section->pointer_raw_data;
        if ((subdirectory_or_data_offset & 0x80000000) == 0)
        {
            uint32 data_address = subdirectory_or_data_offset & 0x7FFFFFFF;
            RsrcEntry * new_entry = new RsrcEntry(data_address, p_table, RSRC_NAME, name_offset);
            printf("Name Resource Data Entry %08lX\n", data_address);
            p_table->entries.push_back(new_entry);
            //add it to the vector of all entries (for cleanup and processing)
            all_rsrc_entries.push_back(new_entry);
        }
        else
        {
            uint32 data_address = subdirectory_or_data_offset & 0x7FFFFFFF;
            RsrcTable * new_table = new RsrcTable(data_address, p_table, RSRC_NAME, name_offset);
            new_table->parent = p_table;
            printf("Name Table: %08lX\n", data_address);
            p_table->subtables.push_back(new_table);
            //add it to the vector of all tables (for cleanup)
            all_rsrc_tables.push_back(new_table);
        }
    }
    for (int i = 0; i< p_table->number_of_id_entries; i++)
    {
        uint32 entry_id = Util::read_uint32(p_file);
        uint32 subdirectory_or_data_offset = Util::read_uint32(p_file);
        subdirectory_or_data_offset += p_section->pointer_raw_data;
        if ((subdirectory_or_data_offset & 0x80000000) == 0)
        {
            uint32 data_address = subdirectory_or_data_offset & 0x7FFFFFFF;
            RsrcEntry * new_entry = new RsrcEntry(data_address, p_table, RSRC_ID, entry_id);
            printf("ID Resource Data Entry %08lX\n", data_address);
            p_table->entries.push_back(new_entry);
            //add it to the vector of all entries (for cleanup and processing)
            all_rsrc_entries.push_back(new_entry);
        }
        else
        {
            uint32 data_address = subdirectory_or_data_offset & 0x7FFFFFFF;
            RsrcTable * new_table = new RsrcTable(data_address, p_table, RSRC_ID, entry_id);
            new_table->parent = p_table;
            printf("ID Table: %08lX\n", data_address);
            p_table->subtables.push_back(new_table);
            //add it to the vector of all tables (for cleanup)
            all_rsrc_tables.push_back(new_table);
        }
    }
    p_table->unprocessed = false;
}

void FileImporter::load_rsrc(FileSection * p_section, fstream & p_file)
{
    RsrcTable root;
    root.address = p_section->pointer_raw_data;
    load_rsrc_table(p_section, p_file, &root);
    RsrcTable * current_table = &root;
    bool finished = false;
    while (!finished)
    {
        for (int i = 0; i < current_table->subtables.size(); i++)
        {
            if (current_table->subtables[i]->unprocessed)
            {
                load_rsrc_table(p_section, p_file, current_table->subtables[i]);
            }
        }
        // if the current directory has children, process them next
        if (current_table->subtables.size()>0 && current_table->has_unprocessed_children)
        {
            bool found_unprocessed_child = false;
            int i = 0;
            while ((!found_unprocessed_child) && i < current_table->subtables.size())
            {
                if (current_table->subtables[i]->has_unprocessed_children || current_table->subtables[i]->unprocessed)
                {
                    found_unprocessed_child = true;
                    current_table = current_table->subtables[i];
                }
                i++;
            }
            if (!found_unprocessed_child)
            {
                current_table->has_unprocessed_children = false;
            }
        }
        else 
        {
            current_table->has_unprocessed_children = false;
        }
        if (!current_table->has_unprocessed_children)
        {
            if (root.has_unprocessed_children)
            {
                current_table = &root;
            }
            else
            {
                finished = true;
            }
        }
    }
    
    for (int i = 0; i<all_rsrc_entries.size(); i++)
    {
        load_rsrc_entry(p_section, p_file, all_rsrc_entries[i]);
    }
    
    
    for (int i = 0; i < all_rsrc_tables.size(); i++)
    {
        delete all_rsrc_tables[i];
    }
    for (int i = 0; i < all_rsrc_entries.size(); i++)
    {
        delete all_rsrc_entries[i];
    }
}