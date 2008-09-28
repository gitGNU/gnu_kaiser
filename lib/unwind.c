#include <lib/kprintf.h>
#include <asm/stddef.h>
#include <lib/unwind.h>
#include <lib/elf_symtab.h>

/* Unwind the functions called */
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
