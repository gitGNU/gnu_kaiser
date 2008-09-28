#include <elf.h>
#include <lib/elf_symtab.h>

int symbol_table_size;
Elf32_Sym *symbol_table;
char *string_table;

void init_symtable(Elf32_Shdr *section_table, int size){
	Elf32_Shdr *section_header;

	int i;
	for(i=0; i<size; i++){
		section_header = &section_table[i];
		if(section_header->sh_type == SHT_SYMTAB){
			symbol_table = (Elf32_Sym *)section_header->sh_addr;
			symbol_table_size = section_header->sh_size / sizeof(Elf32_Sym);
		} else if(section_header->sh_type == SHT_STRTAB){
			string_table = kmalloc(section_header->sh_size);
			string_table = memcpy(string_table, (char *)section_header->sh_addr, section_header->sh_size);
		}
	}
}

char *get_symbol_name(unsigned int symbol_location){
	char *retval = NULL;
	Elf32_Sym *symbol;
	int i;

	for(i=0; i < symbol_table_size; i++){
		symbol = &symbol_table[i];
		if(symbol->st_value == symbol_location){
			retval = string_table + symbol->st_name;
		}
	}
	return retval;
}
