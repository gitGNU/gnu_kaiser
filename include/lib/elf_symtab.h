#ifndef __ELF_SYMTAB_H__
#define __ELF_SYMTAB_H__

#include <elf.h>

void init_symtable(Elf32_Shdr *, int);
char *get_symbol_name(unsigned int);

#endif
