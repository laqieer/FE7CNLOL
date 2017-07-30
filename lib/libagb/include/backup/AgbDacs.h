/********************************************************************/
/*          AgbDacs.h                                               */
/*            1Mbit DACS Library Header    ver. 1.2.0               */
/*                                                                  */
/*                                         last modified 2001.03.12 */
/*                                                                  */
/*          Copyright (C) 2000-2001 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef __AGBDACS_H__
#define __AGBDACS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <AgbTypes.h>

// define data----------------------------------
typedef struct dacsSectorTag {
	u32			size;	// Sector size in units of bytes
	u8			shift;	// The sector byte size converted into a shift count
					// (sector.size = 2<<sector.shift)
	u16			count;	// Sector Count
	u16			top;	// Starting sector No.
}dacsSector;

typedef struct dacsTypeTag {
	u32			topAdr;		// Starting address
	u32 		romSize;		// Size of save region
	u16			totalSector;	// Total Sector Count
	dacsSector	sector1;		// Sector 1's structure information
                                //  (The sector from the start of memory)
	dacsSector	sector2;		// Sector 2's structure information
                                //  (* Valid when there is sector of different size)
	u16			agbWait[2];	// Read/write wait value of AGB game pak bus (ROM2 area)
						//  (Used inside the library)
	u16			makerID;	// Maker ID
	u16			deviceID;	// Device ID
}dacsType;

/*******************************************************************
  For 1Mbit/8Mbit DACS, the device structure information is defined in the 
above-mentioned dacsType structure inside the library in the format shown below. 
These definitions can be accessed by executing IdentifyDacs() and then 
referencing the global variable [const dacsType *dacs].



1Mbit DACS (8kbit sector x 14 from starting address)
{
	0x0dfe4000,                                 Start address
	0x0001c000,                                 Size of save region
	14,                                         Total number of sectors
	{0x00002000,13,14, 0},                      Sector 1's structure information
	{0x00000000, 0, 0, 0},                      Sector 2's structure information
	{CST_ROM2_1ST_3WAIT|CST_ROM2_2ND_1WAIT,     Read cycle 3/1
	 CST_ROM2_1ST_8WAIT|CST_ROM2_2ND_8WAIT},    Write cycle 8/8
	0x00b0,                                     Maker ID
	0x0093,                                     Device ID
}

8Mbit DACS (64Kbit sector x 15 from starting address, followed by 8Kbit sector x 6)
{
	0x0df00000,                                 Start address
	0x000fc000,                                 Size of save region
	23,                                         Total number of sectors
	{0x00010000,16,15, 0},                      Sector 1's structure information
	{0x00002000,13, 6,15},	                    Sector 2's structure information
	{CST_ROM2_1ST_3WAIT|CST_ROM2_2ND_1WAIT,     Read cycle 3/1
	 CST_ROM2_1ST_8WAIT|CST_ROM2_2ND_8WAIT},    Write cycle 8/8
	0x00b0,                                     Maker ID
	0x009b,                                     Device ID
}
*********************************************************************/


/*------------------------------------------------------------------*/
/*          Global Variable                                         */
/*------------------------------------------------------------------*/

extern const dacsType *dacs;	// Pointer to the data that shows the structure of the
					// DACS which is stored after IdentifyDacs is executed. 
					// (See definition of above data for details)
extern u32 dacs_remainder;		// Barometer showing progress during DACS write

/*------------------------------------------------------------------*/
/*          Device Identification and Initial Settings              */
/*------------------------------------------------------------------*/

extern u16 IdentifyDacs();

/*   Identifies DACS device being used with Game Pak. Gets flash capacity 
     and sector size, and sets up access speed. The obtained data can be 
     referenced using the global variable dacsType *dacs.
     (See the header file dacs.h for more details on dacsType.)
	Prior to accessing DACS(including reads), please call once.
	If cannot identify device an error is returned and the following 
        access functions can no longer be used.
	
	<Arguments>
	 None
	<Return Values>
	 u16 result	: 0 is normal end, Not 0 is error
*/

/*------------------------------------------------------------------*/
/*          Access Timer Interrupt Settings                         */
/*------------------------------------------------------------------*/

extern u16 SetDacsTimerIntr(u8 timerNo, void (**IntrFunc)(void));

/*   Selects timer interrupt for determining timeouts during access to DACS. 
     Transfers timeout determination function and DACS status polling 
     function to buffer set aside in WRAM.
     You must call at least once before each access routine is called. Once 
     you have set the timer interrupt to be used with this routine, and as 
     long as you don't use the timer interrupt for the set No. with other 
     processing, or use a different interrupt table, it is not necessary to 
     call this routine again. However, if you overlay and use the RAM area of 
     this library, it is possible that the functions transfered to the RAM were
     overwritten. 
     If timer No. is not from 0-3, error.
     *According to the library specifications, when this routing is called, a 
     specific timer interrupt routine is forcibly set for the library functions
     so the interrupt table when accessing DACS must be in the RAM area.
	<Arguments>
	 u8 timerNo	:Number of timer used by timeout routine.
	 void (**IntrFunc)(void):Pointer to compatible timer interrupt 
                                 address in interrupt table.
	<Return Values>
	 u16 result	:0 is normal end, Not 0 is error

/*-------------------------------------------------------------------*/
/*  Address conversion (DACS sector No. -> CPU memory map address)   */
/*-------------------------------------------------------------------*/

extern u32 ExchangeSectorToPhysAdr(u16 secNo);

/*	Converts the DACS sector No. to an address in the CPU memory map.
     When sector No. is abnormal a parameter error is generated and 0 is returned.
    
    <Arguments>
      u16 secNo     : Target sector No.
    <Return value>
	u32 physAdr   : Normal end -> Staring address of target sector No. in 
                                    the AGB-CPU memory map
                      Parameter error -> 0

*/
/*------------------------------------------------------------------*/
/*               Address conversion                                 */
/*  (CPU memory map address -> DACS sector No. + offset in sector)  */
/*------------------------------------------------------------------*/

extern u32 ExchangePhysAdrToSector(u32 physAdr);

/*     Converts the DACS address in the AGB-CPU memory map into a 
    DACS sector No. + offset inside sector.
       In the return value, bits 31-24 are sector No. and bits 23-0 
    are the offset inside the sector.
       When an address is specified that is outside the range assigned
    to DACS, a parameter error is generated and 0 is returned.

     <Arguments>
	u32 physAdr      : The DACS address in the AGB-CPU memory map
     <Return value>
	u32 secNo_offset : Normal end -> (Sector No. <<24 | (Offset in sector)
                         Parameter error -> 0
*/

/*------------------------------------------------------------------*/
/*          Read data in 2byte units                                */
/*------------------------------------------------------------------*/

extern void ReadDacs(u16 secNo, u32 byteOffset,u16 *dst, u32 byteSize);

/*   This reads "byteSize" bytes of data starting at the address "byteOffset" 
   bytes away from the start of the target sector No., and loads the data into 
   the region starting from address "dst."
     The function operates normally even when the specified read size straddles 
   a sector boundary.
     Specify an even number of bytes for byteOffset and byteSize, and specify an 
   address with a 16 bit boundary for *dst.
	
     <Arguments>
	 u16 secNo     : Target sector No.
       u32 byteOffset: Offset inside the sector in units of bytes 
                        (Specified as an even number of bytes)
	 u16 *src      : Transfer destination address of the read data 
                      (An address with a 16 bit boundary in the AGB memory map)
       u32 byteSize  : Read byte size (Specified as an even number of bytes)
    <Return value>
	 None
*/

/*------------------------------------------------------------------*/
/*          Erase Chip                                              */
/*------------------------------------------------------------------*/

extern u16 EraseDacsChip();
/*	Erase entire chip.
      When calling this function, please halt direct sound and DMAs that start 
    in synch with V & H blanks.
      * All interrupts with the exception of the timer used for time-out 
    processing are prohibited for part of the time inside this function.  Be 
    aware that any interrupt that was enabled prior to the call of this function
    will occur immediately after the end of this prohibition period (which lasts 
    for several hundred milliseconds to several seconds).

	<Arguments>
	  None
	<Return value>
	 u16 result	: 0 is normal end, non-zero is an error
*/

/*------------------------------------------------------------------*/
/*          Erase Sector                                            */
/*------------------------------------------------------------------*/

extern u16 EraseDacsSector(u16 secNo);

/*   Erase sector of target sector No.
     This routine is called in write routine, so usually you don't
     need to call it before a write.
       A parameter error occurs when the target sector No. is outside the 
     range of sector numbers for this particular device.
       When calling this function, please halt direct sound and DMAs that start 
    in synch with V & H blanks.
      * All interrupts with the exception of the timer used for time-out 
    processing are prohibited for part of the time inside this function.  Be 
    aware that any interrupt that was enabled prior to the call of this function
    will occur immediately after the end of this prohibition period (which lasts 
    for several hundred milliseconds to several seconds).
	<Arguments>
	 u16 secNo	: Target sector No.
	<Return value>
	 u16 result	: 0 is normal end, non-zero is an error.
*/

/*--------------------------------------------------------------------*/
/*  Write data in 2byte units (without erasing from inside function)  */
/*--------------------------------------------------------------------*/

extern u16 ProgramDacs_NE(u16 secNo, u32 byteOffset, u16 *src, u32 byteSize);

/*    This function takes "byteSize" bytes of data from the address "src" and 
   writes it to the address "byteOffset" bytes away from the start of the target 
   sector No.
      Note that the EraseDacsSector routine is not called from inside this 
   function, so if data is already written to the destination area, then the 
   value that is written to this address is the AND of the existing data and the 
   new data.  Thus, for example, if 0x3333 is written to an address where 0x5555 
   is already written, the result will be 0x1111.
      The function operates normally even when the specified write size straddles
   a sector boundary.  However, a parameter error occurs when the specified size 
   exceeds the region allocated to the device.
      A parameter error occurs when the target sector No. is outside the range of 
   the pertinent device.
     Specify an even number of bytes for byteOffset and byteSize, and specify 
   an address with a 16 bit boundary for *src.
      When calling this function, please halt direct sound and DMAs that start 
   in synch with V & H blanks.
      * All interrupts with the exception of the timer used for time-out 
   processing are prohibited for part of the time inside this function.  Be 
   aware that any interrupt that was enabled prior to the call of this function
   will occur immediately after the end of this prohibition period (which lasts 
   for several dozen microseconds).

    <Arguments>
	u16 secNo     : Target sector No.
      u32 byteOffset: Offset inside the sector in units of bytes 
                        (Specified as an even number of bytes)
	u16 *src      : Write source address 
                      (An address with a 16 bit boundary in the AGB memory map)
      u32 byteSize  : Write byte size (Specified as an even number of bytes)
    <Return value>
	u16 result    : 0 is normal end, non-zero is an error.
*/

/*------------------------------------------------------------------*/
/*   Write data in sector units (with erasing from inside function) */
/*------------------------------------------------------------------*/

extern u16 ProgramDacsSector(u16 secNo,u16 *src);

/*    Takes one sector's worth of data from the "src" address and writes
   it to the target sector No.
      All sectors in the 1Mbit DACS are 8kbyte, but in the 8Mbit DACS, sectors 
   0-15 are 32kbyte and sectors 16-20 are 8kbyte, so those sizes determine the 
   amount of data written.
      This function makes an internal call to EraseDacsSector, so the sector is
   erased before data is written.
      A parameter error occurs when the target sector No. is outside the range of 
   the pertinent device.
      Specify an address with a 16 bit boundary for *src.
      When calling this function, please halt direct sound and DMAs that start 
   in synch with V & H blanks.
      * All interrupts with the exception of the timer used for time-out 
   processing are prohibited for part of the time inside this function.  Be 
   aware that any interrupt that was enabled prior to the call of this function
   will occur immediately after the end of this prohibition period (which lasts 
   for several dozen microseconds to several seconds).

	<Arguments>
	 u16 secNo	: Target sector No.
	 u8 *src	: Write source address
	<Return value>
	 u16 result	: 0 is normal end, non-zero is an error.
*/
/*------------------------------------------------------------------*/
/*          Verify data in 2byte units                              */
/*------------------------------------------------------------------*/

extern u32 VerifyDacs(u16 secNo, u16 byteOffset, u16 *src, u32 byteSize);

/*    This verifies "byteSize" worth of data at the address "src" and at the
   address "byteOffset" bytes away from the start of the target sector No.
      The function operates normally even when the specified verify size 
   straddles a sector boundary.
      Specify an even number of bytes for byteOffset and byteSize, and 
   specify an address with a 16 bit boundary for *src.
      This routine does not perform a parameter check.

    <Arguments>
	u16 secNo     : Target sector No.
      u32 byteOffset: Offset inside the sector in units of bytes 
                      (Specified as an even number of bytes)
	u16 *src      : Verify origin address  
                      (An address with a 16 bit boundary in the AGB memory map)
      u32 byteSize  : Verify byte size (Specified as an even number of bytes)
    <Return value>
	u16 result    : Normal end -> 0
                      Verify error -> Error address on device side
*/

/*------------------------------------------------------------------*/
/*          Verify data in sector units                             */
/*------------------------------------------------------------------*/

extern u32 VerifyDacsSector(u16 secNo, u16 *src);

/*    This function verifies the specified sector's worth of data at the 
   address "src" and in the target sector No.
      All sectors in the 1Mbit DACS are 8kbyte, but in the 8Mbit DACS, 
   sectors 0x00 - 0x0E are 32kbyte and sectors 0x0F - 0x14 are 8kbyte, 
   so those sizes determine the amount of data verified.
      Specify an address with a 16 bit boundary for *src.
      This routine does not perform a parameter check

   <Arguments>
    u16 secNo	: Target sector No.
    u16 *src	: Verify source address
   <Return value>
    u16 result  : Normal end -> 0
                  Verify error -> Error address on device side

*/

#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif	// __AGBDACS_H__
