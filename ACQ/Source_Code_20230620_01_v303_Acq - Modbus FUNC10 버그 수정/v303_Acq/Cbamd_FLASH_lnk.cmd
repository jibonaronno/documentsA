
MEMORY
{
PAGE 0 :  /* Program Memory */
          /* Memory (RAM/FLASH) blocks can be moved to PAGE1 for data allocation */
          /* BEGIN is used for the "boot to Flash" bootloader mode   */

  BEGIN           	  : origin = 0x080000, length = 0x000002

/*
  RAMD0           	  : origin = 0x00B000, length = 0x000800
  RAMD1               : origin = 0x00B800, length = 0x000800
  RAMGS0              : origin = 0x00C000, length = 0x001000
  RAMGS1              : origin = 0x00D000, length = 0x001000
  RAMGS2              : origin = 0x00E000, length = 0x001000
  RAMGS3              : origin = 0x00F000, length = 0x001000
  RAMGS4              : origin = 0x010000, length = 0x001000
  RAMGS5              : origin = 0x011000, length = 0x001000
  RAMGS6              : origin = 0x012000, length = 0x001000
  RAMGS7              : origin = 0x013000, length = 0x001000
  RAMGS8              : origin = 0x014000, length = 0x001000
  RAMGS9              : origin = 0x015000, length = 0x001000
  RAMD0               : origin = 0x00B000, length = 0x000800
  RAMD1               : origin = 0x00B800, length = 0x000800
*/
/*  RAMGS_ROM		        : origin = 0x00E000, length = 0x008000	*/
/*  RAMGS_ROM		        : origin = 0x014000, length = 0x008000  */
  RAMD0           	  : origin = 0x00B000, length = 0x000800
  RAMD1               : origin = 0x00B800, length = 0x000800
  RAMGS_ROM          	: origin = 0x012000, length = 0x004000

//  SDRAM0              : origin = 0x80000000, length = 0x00100000

  RESET           	  : origin = 0x3FFFC0, length = 0x000002
   
  /* Flash sectors */
  FLASHA              : origin = 0x080002, length = 0x003FFE	/* on-chip Flash */
  FLASHC              : origin = 0x084000, length = 0x004000	/* on-chip Flash */
  FLASHE              : origin = 0x088000, length = 0x008000	/* on-chip Flash */
  FLASHF              : origin = 0x090000, length = 0x008000	/* on-chip Flash */
  FLASHG              : origin = 0x098000, length = 0x008000	/* on-chip Flash */
  FLASHH              : origin = 0x0A0000, length = 0x008000	/* on-chip Flash */
  FLASHIJ             : origin = 0x0A8000, length = 0x010000	/* on-chip Flash */
  FLASHK              : origin = 0x0B8000, length = 0x002000	/* on-chip Flash */
  FLASHL              : origin = 0x0BA000, length = 0x006000  /* on-chip Flash */
/*  FLASHM              : origin = 0x0BC000, length = 0x002000    *//* on-chip Flash */
/*  FLASHN              : origin = 0x0BE000, length = 0x002000	*//* on-chip Flash */


PAGE 1 : /* Data Memory */
         /* Memory (RAM/FLASH) blocks can be moved to PAGE0 for program allocation */

  BOOT_RSVD           : origin = 0x000002, length = 0x000120     /* Part of M0, BOOT rom will use this for stack */
  RAMM01              : origin = 0x000122, length = 0x0006DE
/*  RAMM0               : origin = 0x000122, length = 0x0002DE */
/*  RAMM1               : origin = 0x000400, length = 0x000400 */    /* on-chip RAM block M1 */
/*
  RAMGS0              : origin = 0x00C000, length = 0x001000
  RAMGS1              : origin = 0x00D000, length = 0x001000
  RAMGS_RAM           : origin = 0x016000, length = 0x006000
  RAMGS_RAM		        : origin = 0x00E000, length = 0x006000
  RAMLS0              : origin = 0x008000, length = 0x000800
  RAMLS1              : origin = 0x008800, length = 0x000800
  RAMLS2              : origin = 0x009000, length = 0x000800
  RAMLS3              : origin = 0x009800, length = 0x000800
  RAMLS4              : origin = 0x00A000, length = 0x000800
  RAMLS5			        : origin = 0x00A800, length = 0x000800
*/
  RAMGS_RAM           : origin = 0x00B000, length = 0x007000
  RAMLS_RAM			      : origin = 0x008000, length = 0x003000

//  SDRAM1              : origin = 0x80010000, length = 0x00010000


}


SECTIONS
{
  /* Allocate program areas: */
  .cinit              : > FLASHA      PAGE = 0, ALIGN(4)
  .pinit              : > FLASHA      PAGE = 0, ALIGN(4)
  .text               : >> FLASHE | FLASHF | FLASHG | FLASHH     PAGE = 0, ALIGN(4)
  codestart           : > BEGIN       PAGE = 0, ALIGN(4)
  .TI.ramfunc         : LOAD = FLASHIJ,		/* RAM 용량이 FLASH 보다 작으므로 이 정도로 현재는 문제 없어 보임 */
                        RUN = RAMGS_ROM,
/*                        RUN = RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4 | RAMLS5, */
/*                        RUN = RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4 | RAMLS5 | RAMGS_ROM, */
/*                        RUN = RAMGS,	*/
                        LOAD_START(_RamfuncsLoadStart),
                        LOAD_SIZE(_RamfuncsLoadSize),
                        LOAD_END(_RamfuncsLoadEnd),
                        RUN_START(_RamfuncsRunStart),
                        RUN_SIZE(_RamfuncsRunSize),
                        RUN_END(_RamfuncsRunEnd),
                        PAGE = 0, ALIGN(4)
						 
  /* Allocate uninitalized data sections: */
  .stack              : > RAMM01,	PAGE = 1
  .ebss               : >> RAMGS_RAM	PAGE = 1
  .esysmem            : > RAMLS_RAM	PAGE = 1
  .cio                : > RAMLS_RAM   PAGE = 1 

  /* Initalized sections go in Flash */
  .econst             : >> FLASHL     PAGE = 0, ALIGN(4)
  .switch             : > FLASHC     PAGE = 0, ALIGN(4)

  .reset              : > RESET,      PAGE = 0, TYPE = DSECT /* not used, */

  /* The following section definitions are for SDFM examples */		
/*
  Filter1_RegsFile    : > RAMGS1,     PAGE = 1, fill=0x1111
  Filter2_RegsFile    : > RAMGS2,     PAGE = 1, fill=0x2222
  Filter3_RegsFile    : > RAMGS3,     PAGE = 1, fill=0x3333
  Filter4_RegsFile    : > RAMGS4,     PAGE = 1, fill=0x4444
*/
  Difference_RegsFile : >RAMLS_RAM, 	PAGE = 1, fill=0x3333

/*
  SHARERAMGS0         : > RAMGS0,     PAGE = 1
  SHARERAMGS1         : > RAMGS1,     PAGE = 1
  ramgs0              : > RAMGS0,     PAGE = 1
  ramgs1              : > RAMGS1,     PAGE = 1
*/
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
