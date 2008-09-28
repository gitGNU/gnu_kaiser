#include <elf.h>
#include <lib/elf_symtab.h>
#include <lib/string.h>
#include <kmalloc.h>

int __symbol_table_size;
Elf32_Sym *__symbol_table;
char *__string_table;

void init_symtable(Elf32_Shdr *section_table, int size){
	Elf32_Shdr *section_header;

	int i;
	for(i=0; i<size; i++){
		section_header = &section_table[i];
		if(section_header->sh_type == SHT_SYMTAB){
			__symbol_table = (Elf32_Sym *)section_header->sh_addr;
			__symbol_table_size = section_header->sh_size / sizeof(Elf32_Sym);
		} else if(section_header->sh_type == SHT_STRTAB){
			__string_table = kmalloc(section_header->sh_size);
			memcpy(__string_table, (char *)section_header->sh_addr, section_header->sh_size);
		}
	}
}

char *get_symbol_name(unsigned int symbol_location){
	char *retval = NULL;
	Elf32_Sym *symbol;
	int i;

	for(i=0; i < __symbol_table_size; i++){
		symbol = &__symbol_table[i];
		if(symbol->st_value == symbol_location){
			retval = __string_table + symbol->st_name;
		}
	}
	return retval;
}
