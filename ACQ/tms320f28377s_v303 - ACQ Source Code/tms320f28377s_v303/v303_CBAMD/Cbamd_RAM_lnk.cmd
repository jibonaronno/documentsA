
MEMORY
{
PAGE 0 :
/* BEGIN is used for the "boot to SARAM" bootloader mode   */

  BEGIN           	: origin = 0x000000, length = 0x000002
/*
  RAMLS0          	: origin = 0x008000, length = 0x000800
  RAMLS1          	: origin = 0x008800, length = 0x000800
  RAMLS2            : origin = 0x009000, length = 0x000800
  RAMLS3            : origin = 0x009800, length = 0x000800
  RAMLS4            : origin = 0x00A000, length = 0x000800
  RAMLS5            : origin = 0x00A800, length = 0x000800
*/
  RAMLSF          	: origin = 0x00A000, length = 0x001000

/*
  RAMD0             : origin = 0x00B000, length = 0x000800
  RAMD1             : origin = 0x00B800, length = 0x000800
  RAMGS0            : origin = 0x00C000, length = 0x001000
  RAMGS1            : origin = 0x00D000, length = 0x001000
  RAMGS2            : origin = 0x00E000, length = 0x001000
  RAMGS3            : origin = 0x00F000, length = 0x001000
  RAMGS4            : origin = 0x010000, length = 0x001000
  RAMGS5            : origin = 0x011000, length = 0x001000
  RAMGS6            : origin = 0x012000, length = 0x001000
  RAMGS7            : origin = 0x013000, length = 0x001000
  RAMGS8            : origin = 0x014000, length = 0x001000
  RAMGS9            : origin = 0x015000, length = 0x001000
  RAMGS10           : origin = 0x016000, length = 0x001000
  RAMGS11           : origin = 0x017000, length = 0x001000
  RAMGS12           : origin = 0x018000, length = 0x001000
  RAMGS13           : origin = 0x019000, length = 0x001000
  RAMGS14           : origin = 0x01A000, length = 0x001000
  RAMGS15           : origin = 0x01B000, length = 0x001000
*/
  RAMGS             : origin = 0x00B000, length = 0x011000

  SDRAM0            : origin = 0x80000000, length = 0x00010000

  RESET           	: origin = 0x3FFFC0, length = 0x000002

PAGE 1 :

  BOOT_RSVD         : origin = 0x000002, length = 0x000120     /* Part of M0, BOOT rom will use this for stack */
  RAMM0           	: origin = 0x000122, length = 0x0002DE
  RAMM1             : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
/*
  RAMD1             : origin = 0x00B800, length = 0x000800

*/
  RAMLS           	: origin = 0x008000, length = 0x002000

  SDRAM1            : origin = 0x80010000, length = 0x00010000
}


SECTIONS
{
  codestart           : > BEGIN,  PAGE = 0
  ramfuncs            : > RAMGS   PAGE = 0
  .text               : >>RAMGS,  PAGE = 0
/*  .text               : > SDRAM0, PAGE = 0 */
  .cinit              : > RAMGS,  PAGE = 0
  .pinit              : > RAMGS,  PAGE = 0
  .switch             : > RAMLSF, PAGE = 0
  .reset              : > RESET,  PAGE = 0, TYPE = DSECT /* not used, */

  .stack              : > RAMM0,  PAGE = 1
  .ebss               : > RAMLS,  PAGE = 1
  .econst             : > RAMM0 | RAMM1,     PAGE = 1
  .esysmem            : > RAMM0 | RAMM1,     PAGE = 1

/*  FIFO ALIGN(0x1000) : { } >   RAMGS2 | RAMGS3 | RAMGS4 | RAMGS5 | RAMGS6 | RAMGS7 | RAMGS8 | RAMGS9 | RAMGS10 | RAMGS11		PAGE 1 */

/*
  ramgs0              : > RAMGS0, PAGE = 1
  ramgs1              : > RAMGS1, PAGE = 1
*/
   /* The following section definitions are for SDFM examples */		
/*
  Filter1_RegsFile    : > RAMGS1,	PAGE = 1, fill=0x1111
  Filter2_RegsFile    : > RAMGS2,	PAGE = 1, fill=0x2222
  Filter3_RegsFile    : > RAMGS3,	PAGE = 1, fill=0x3333
  Filter4_RegsFile    : > RAMGS4,	PAGE = 1, fill=0x4444
*/
  Difference_RegsFile : >RAMLS, 	PAGE = 1, fill=0x3333
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
