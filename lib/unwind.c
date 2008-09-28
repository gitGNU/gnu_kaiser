/*
 * unwind.c - unwind the stack to see the chain of function calls
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


#include <lib/kprintf.h>
#include <asm/stddef.h>
#include <lib/unwind.h>
#include <lib/elf_symtab.h>

void unwind(void){
	/* end is defined in our linker script */
  extern uint32_t end;
  end = (uint32_t)&end;

  int ebp;
  int return_address;
  unsigned int symtable_entry;

  __asm__ __volatile__("mov %%ebp, %0;" : "=a" (ebp));
  while(1){
		/* on the first run, skip the first ebp as it's the unwind function,
		 * on the runs after, grab the next ebp
		 */
		ebp = *(int *)ebp;

    return_address = *(int *)(ebp+4);
    symtable_entry = return_address + *(int *)(return_address-4);
    if(symtable_entry < 0x100000 || symtable_entry > end)
      break;

    /* we have the current ebp, let's see what function it referrs to */
    kprintf("Symtable entry: %x:%s\n", symtable_entry, get_symbol_name(symtable_entry));
  }
}
