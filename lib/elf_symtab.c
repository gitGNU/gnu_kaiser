/*
 * elf_symtab.c - parse the symbol table of the kernel
 *
 * Copyright (C) 2008 Andrew 'Seadog' Etches
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

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
