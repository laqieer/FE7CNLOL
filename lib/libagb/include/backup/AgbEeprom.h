/********************************************************************/
/*          AgbEeprom.h	                                            */
/*            4kbit EEPROM Library Header ver. 1.2.0                */
/*                                                                  */
/*                                         last modified 2001.03.12 */
/*                                                                  */
/*          Copyright (C) 2000-2001 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef	__AGB_EEPROM_H__
#define	__AGB_EEPROM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Agb.h>

// define data----------------------------------


typedef struct eepromTypeTag {
	u32		size;			// Byte size
	u16		adrCount;		// Total number of addresses
	u16		agbWait;		// Read/write wait value of AGB game pak bus (ROM2 area)
						//   (Used inside the library)
	u8		adrBit;		// Number of address bits at DMA transfer time
}eepromType;				//  (Used inside the library)

/*******************************************************************
Å@
  For 4K/64Kbit EEPROM, the device structure information is defined in the 
above-mentioned eepromType structure inside the library in the format shown below. 
These definitions can be accessed by executing IdentifyEeprom and then referencing
the global variable [const eepromType *eeprom].



4Kbit EEPROM
{
	0x00000200,						// Total byte size
	0x0040,						// Total number of addresses
	CST_ROM2_1ST_8WAIT|CST_ROM2_2ND_8WAIT,	// 8/8 wait
	6,					// Number of address bits at DMA transfer time 
};

64Kbit EEPROM
{
	0x00002000,						// Total byte size
	0x0400,						// Total number of addresses
	CST_ROM2_1ST_8WAIT|CST_ROM2_2ND_8WAIT,	// 8/8 wait
	14,					// Number of address bits at DMA transfer time
};

/*------------------------------------------------------------------*/
/*          Global variables                                        */
/*------------------------------------------------------------------*/
extern const eepromType *eeprom;	//   Pointer to the data that shows the 
                                    // structure of the EEPROM which is stored 
                                    // after IdentifyEeprom is executed. 


/*------------------------------------------------------------------*/
/*    Device identification and initial settings                    */
/*------------------------------------------------------------------*/
extern u16 IdentifyEeprom(u16 eeprom_KbitSize);

/*	This function determines which EEPROM is mounted in the game pak 
   based on the value specified by the argument eeprom_KbitSize, and sets
   the EEPROM size, total address count and access speed.  (EEPROM does not
   have a device ID, so identification of which EEPROM is being used is 
   determined from the argument that is passed.)
      The obtained EEPROM data can be referenced using the global variable 
   eepromType *eeprom.  (For details about eepromType see the definitions above.)
      This function is called once prior to accessing EEPROM (including prior
   to reading the device.)
      When an incorrect argument is passed, an error is returned and the data
   for 4Kbit EEPROM are set in eepromType *eeprom.

    <Arguments>
	 u16 eeprom_KbitSize : The size of EEPROM being used, in Kbits
    <Return values>
	 u16 result	: 0 is normal end, non-zero is an argument error
	 
	 * Usage examples*
	  When using 4Kbit EEPROM     IdentifyEeprom(4);
	  When using 64Kbit EEPROM    IdentifyEeprom(64);
*/

/*------------------------------------------------------------------*/
/*          Timer Interrupt Settings for Access                     */
/*------------------------------------------------------------------*/

extern u16 SetEepromTimerIntr(u8 timerNo, void (**IntrFunc)(void));

/*   Selects timer interrupt for determining timeouts during access to EEPROM.
     This routine needs to be called at least one time before the write function 
   ProgramEepromDword is called.  Once the timer interrupt used with the routine 
   has been set, the timer interrupt No. that has been set can be used with other
   processes and there is no need to call this routine again, unless another 
   interrupt table is used.
     If timer No. is not from 0-3, error.
     *According to the library specifications, when this routine is called, a 
     specific timer interrupt routine is forcibly set for the library functions
     so the interrupt table when accessing EEPROM must be in the RAM area.
   <Arguments>
     u8 timerNo :Number of timer used by timeout routine.
     void (**IntrFunc)(void): Pointer to compatible timer interrupt 
                                 address in interrupt table.
     <Return Values>
     u16 result : 0 is normal end, Not 0 is error
*/

/*------------------------------------------------------------------*/
/*          Read Double-Word (8 bytes) Data                         */
/*------------------------------------------------------------------*/

extern u16 ReadEepromDword(u16 epAdr,u16 *dst);

/*   Reads 8 bytes of data from the target EEPROM address and loads
   it in and after address "src."
     * This routine uses DMA3.  All interrupts are prohibited while DMA
   is being used inside the routine.
    <Arguments>
     u32 epAdr  :Target EEPROM Address (0x00-0x3f)
     u16 *dst   :Read Data transfer destination
    <Return Values>
     u16 result : 0 is normal end, Not 0 is error

    *Please note all interrupts are prohibited during a certain period 
    (about 40us) when this function is called.    
    Refer to "Cautions when using EEPROM access function" in the 
    "AGB Back-up Library Manual" for details.  
    Do not use DMA that starts synchronizing with Direct sound, V-blank, 
    and H-blank when this function is called. 

*/

/*------------------------------------------------------------------*/
/*          Double-Word (8 bytes) Write Data                         */
/*------------------------------------------------------------------*/

extern u16 ProgramEepromDword(u16 epAdr,u16 *src);

/*  Write 8 bytes of data from src address to target EEPROM address.
    If outside range with target EEPROM address, error.
    *This routine uses DMA 3. When DMA is being used in this routine,
         all interrupts are prohibited.
    <Arguments>
     u32 epAdr  :Target EEPROM Address (0x00-0x3f)
     u16 *dst   :Write source data address
    <Return Values>
     u16 result : 0 is normal end, Not 0 is error

    *Please note all interrupts are prohibited during a certain period 
    (about 40us) when this function is called.    
    Refer to "Cautions when EEPROM access function is used." in the 
    "AGB Back-up Library Manual" for details.  
    Do not use DMA that starts synchronizing with Direct sound, V-blank, 
    and H-blank when this function is called. 
*/

/*------------------------------------------------------------------*/
/*          Verify Doubleword (8 bytes) Data                        */
/*------------------------------------------------------------------*/

extern u16 VerifyEepromDword(u16 epAdr,u16 *src);

/*  Verify 8 bytes of data for src address and target EEPROM address.
    *This routine uses DMA 3. When DMA is being used in this routine,
         all interrupts are prohibited.
    <Arguments>
     u16 epAdr  :Target EEPROM Address (0x00-0x3f)
     u8 *src    :Verify source address
    <Return Values>
    u16     :0 is normal end, Not 0 is error

    *Please note all interrupts are prohibited during a certain period 
    (about 40us) when this function is called.    
    Refer to "Cautions when Using EEPROM Access Functions" in the 
    "AGB Back-up Library Manual" for details.  
    Do not use DMA that starts synchronizing with Direct sound, V-blank, 
    and H-blank when this function is called.  
*/

#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif	// __AGB_EEPROM_H__
