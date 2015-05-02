OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY
{
	NVM (r) : ORIGIN = 0, LENGTH = (512 * 1024)
	RAM (rw) : ORIGIN = 0x10000000, LENGTH = (16 * 1024)
	RAM_BUF (r): ORIGIN = ORIGIN(RAM) + LENGTH(RAM), LENGTH = (4 * 1024)
	MALLOC (r):	ORIGIN = ORIGIN(RAM_BUF) + LENGTH(RAM_BUF), LENGTH = (4 * 1024)
	STACK (r):	ORIGIN = ORIGIN(MALLOC) + LENGTH(MALLOC), LENGTH = (4 * 1024)
}

SECTIONS
{
	.vectors 0 :
	{
		*(.vectors) /* ÏòÁ¿±í*/
	} >NVM
	.crp 0x1FC :AT(0x1FC)
	{
		 *(.crp) 
		 *(.crp*)
	} >NVM
	.text :
	{
		*(.text)
		*(.rodata*)

	} >NVM
	
	.data : {
		_data_start = .;
		_data_lma_start = LOADADDR(.data);
		. = ALIGN(4);
		*(.ramcode)
		_data_end = .;
	} >RAM AT>NVM
	
	
	.bss : {
		_bss_start = .;
		*(.bss)
		*(COMMON)
		_bss_end = .;
	} >RAM
	
	.stack :
	{
		*(.stack)
	} >STACK
}

/*
 * Export memory addresses
 */
_mem_nvm_base		= ORIGIN(NVM);
_mem_nvm_size		= LENGTH(NVM);
_mem_ram_base		= ORIGIN(RAM);
_mem_ram_size		= LENGTH(RAM);
_mem_ram_buf_base	= ORIGIN(RAM_BUF);
_mem_ram_buf_size	= LENGTH(RAM_BUF);
_mem_malloc_base	= ORIGIN(MALLOC);
_mem_malloc_size	= LENGTH(MALLOC);
_mem_stack_base		= ORIGIN(STACK);
_mem_stack_size		= LENGTH(STACK);
_mem_stack_end		= ORIGIN(STACK) + LENGTH(STACK);

