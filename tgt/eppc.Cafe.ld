
MEMORY 
{
    codearea : origin = 0x02000000, length = 0x0E000000
    dataarea : origin = 0x10000000, length = 0xB0000000	// maximum virtual size (to start of r/o area)
    dynlarea : origin = 0xC0000000, length = 0x08000000 // dynamic loader info
}

OPTION("-append")

SECTIONS 
{
    .syscall    ALIGN(0x20)  :   > codearea
    .text	    ALIGN(0x20)  :   > codearea

    .fexports   ALIGN(0x20)  :   > dynlarea
    .dexports   ALIGN(0x20)  :   > dynlarea

    .sdata2     ALIGN(0x20)  :   > dataarea    // ROM SDA BASE (r2)
                                               // custom ROM SDA sections should go here
                                               
    .rodata     ALIGN(0x20)  :   > dataarea
    .secinfo    ALIGN(0x20)  :   > dataarea
    .data       ALIGN(0x20)  :   > dataarea
    .module_id  ALIGN(0x20)  :   > dataarea
    .bss        ALIGN(0x40)  : { *(.bss2) }  > dataarea
    .ipc_smem	ALIGN(0x20)  :   > dataarea    // Special section for shared memory
    .sdabase    ALIGN(0x20)  :   > dataarea    // RAM SDA BASE (r13)
    .sdata      ALIGN(0x20)  :   > dataarea    // SDA sections must be in this order
                                               // custom RAM SDA sections should go here
    .sbss       ALIGN(0x20)  :   > dataarea    // SDA sections must be in this order
                                               // custom RAM ZSDA zersions should go here

    // this should be the last line
    .appended   ALIGN(0x20)  :   > codearea    // import sections
}

