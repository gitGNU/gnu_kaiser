pgroup = group of mmaps
mmap = map of consecutive allocated pages
page = 4kB memory block
malloc = small buffers of allocated data

the base pgroup will be at 0x100000, containing mappings for the kernel code
memory, initially the page at 0x100000 will contain the ELF header, the program
header and padding, this will be used to determine the length of the kernel code
and how much memory to allocate for it

pgroups would optimally reside on 0x100000 boundaries (1MB / 256 pages)
allowing for a 16 byte pgroup header and 16 bytes for each mmap
this will allow for the case of each page in the pgroup being mapped
individually, however unlikely this might be

typedef struct pgroup pgroup_t;
typedef struct mmap mmap_t;
struct {
	u32 pg_magic; /* magic value identifying pgroup header */
	u32 pg_flags; /* various flags */
	pgroup_t *pg_prev, *pg_next; /* doubly linked */
} pgroup;
struct {
	u32 mm_base; /* base address (0 indicates available mmap struct) */
	u16 mm_limit; /* number of pages */
	u16 mm_tid; /* task identifier */
	u32 mm_flags; /* mmap flags */
	u32 mm_vaddr; /* virtual address */
} mmap;

the base pgroup will have a prev link to a stack pgroup which would be located
at memboundary - 0x200 & 0x3fffff
but then we might not really need a growdown stack pgroup, it might be feasible
simply to allocate pages mapped to virtual addresses at lower memory addresses,
thus apparantly growing down

a page will be allocated to detail memory in lowmem (<0x100000)
the first page of memory (0x0000 to 0x1000) will not be used for any purpose
other than for junk data from NULL pointer dereferences


Virtual address space layout.

	00000000 - c0000000 (3GB)
	Userspace address space, the kernel touches this as little as possible.
	Just ELF loading and system calls from the userspace.

	c0000000 - e0000000 (512MB)
	Global/shared kernelspace address space for global code and heap area.
	A shared heap space means individual tasks won't need their own heaps
	along with all the overhead of page tables and heap metadata.

	e0000000 - f0000000 (256MB)
	Private kernel stack address space.

	f0000000 - 00000000 (256MB)
	Private kernel heap address space, availiable in the event a
	kernelspace task requires private heap data, it should be used
	as little as possible.

Possibly randomise page table entries (10 bit randomness) for kernel base
address in each task for added security, would require compiling with -fPIE and
linking with -pie. However some things would have to be global and these could
possibly open a possible workaround.

EXPERIMENTAL:
Another idea is to have user accessible memory based file access/socket systems
implemented with copy-on-write in some special adress space, most likely in the
upper 1GB for kernel memory. This isn't very UNIX-like, however. If possible
this could also have an address randomised by 10 bits that one of the general
purpose segment registers could point to, with a pointer to the linear address
at the start of the data.
