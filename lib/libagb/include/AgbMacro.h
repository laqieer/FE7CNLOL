/********************************************************************/
/*          AgbMacro.h                                              */
/*            AGB Standard Macro Functions                          */
/*                                                                  */
/*	Copyright (C) 2000-2001 NINTENDO Co.,Ltd. 		    */
/********************************************************************/
#ifndef _AGB_MACRO_H
#define _AGB_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <AgbTypes.h>
#include <AgbSystemCall.h>


/*------------------------------------------------------------------*/
/*                      Read Data                                   */
/*------------------------------------------------------------------*/

#define DataRead(Readp, Bit)    (*(vu##Bit *)(Readp))

/*------------------------------------------------------------------*/
/*                      Write Data                                  */
/*------------------------------------------------------------------*/

#define DataWrite(Writep, Data, Bit)                    \
                                                        \
    *(vu##Bit *)(Writep) = (Data)

/*------------------------------------------------------------------*/
/*                      Data Copy                                   */
/*------------------------------------------------------------------*/

#define DataCopy(Readp, Writep, Bit)                    \
                                                        \
    *(vu##Bit *)(Writep) = *(vu##Bit *)(Readp)


/*------------------------------------------------------------------*/
/*                  Set Interrupt Address                           */
/*------------------------------------------------------------------*/

#define IntrAddrSet(Intrp)                              \
                                                        \
    *(vu32 *)INTR_VECTOR_BUF = (vu32 )Intrp

//* Set Interrupt Process Address.

/*------------------------------------------------------------------*/
/*                            Set DMA                               */
/*------------------------------------------------------------------*/

//#define SIMULATOR
#ifndef SIMULATOR
#ifndef CODE32
#define DmaSet(DmaNo, Srcp, Destp, DmaCntData)          \
{                                                       \
    vu32 *(DmaCntp) = (vu32 *)REG_DMA##DmaNo;           \
    DmaCntp[0] = (vu32 )(Srcp);                         \
    DmaCntp[1] = (vu32 )(Destp);                        \
    DmaCntp[2] = (vu32 )(DmaCntData);                   \
    DmaCntp[2];                                         \
}
#else
#define DmaSet(DmaNo, Srcp, Destp, DmaCntData)                   \
{                                                                \
    vu32 *(RegBasep) = (vu32 *)REG_BASE;                         \
    RegBasep[OFFSET_REG_DMA##DmaNo##SAD/4] = (vu32 )(Srcp);      \
    RegBasep[OFFSET_REG_DMA##DmaNo##DAD/4] = (vu32 )(Destp);     \
    RegBasep[OFFSET_REG_DMA##DmaNo##CNT/4] = (vu32 )(DmaCntData);\
    RegBasep[OFFSET_REG_DMA##DmaNo##CNT/4];                      \
}

#endif
#else
#define DmaSet(DmaNo, Srcp, Destp, DmaCntData)                   \
{                                                                \
    int    i;                                                    \
    for (i=0; i<(DmaCntData & 0x1ffff); i++)                     \
        if ((DmaCntData) & DMA_SRC_FIX) {                        \
            if ((DmaCntData) & DMA_32BIT_BUS)                    \
                    ((vu32 *)(Destp))[i] = ((vu32 *)(Srcp))[0];  \
            else    ((vu16 *)(Destp))[i] = ((vu16 *)(Srcp))[0];  \
         } else {                                                \
            if ((DmaCntData) & DMA_32BIT_BUS)                    \
                ((vu32 *)(Destp))[i] = ((vu32 *)(Srcp))[i];      \
            else    ((vu16 *)(Destp))[i] = ((vu16 *)(Srcp))[i];  \
        }                                                        \
}
#endif

//* Set Parameter in DMA Controller.
//* By defining SIMULATOR, simulated with CPU.
//  Valid for debugging wtih GDB, etc.
//* At the end, a command "LDR" is inserted to wait for DMA to start.
//
//* Arguments: 
//  DmaNo       DMA Number
//  Srcp        Source Address
//  Destp       Destination Address
//  DmaCntData  Parameter Data
//
// *By running DMA with a program in the CPU internal RAM, 
//  the instruction immediately following is executed first.
//  Due to this, when you attempt to change the tranfer
//  destination with the CPU directly following DMA, the DMA
//  wil run during Read/Rewrite.  Thus, there are cases when
//  the DMA destination data can become a value that was not
//  intended.  In this case, if you insert DmaWait() directly
//  following, you can check if DMA has finished and be sure to
//  avoid any impact on following code.


/*------------------------------------------------------------------*/
/*                      Clear DMA                                   */
/*------------------------------------------------------------------*/

#define DmaClear(DmaNo, Data, Destp, Size, Bit)             \
{                                                           \
    vu##Bit Tmp = (vu##Bit )(Data);                         \
    DmaSet(DmaNo, &Tmp, Destp, (                            \
        DMA_ENABLE         | DMA_TIMMING_IMM |              \
        DMA_SRC_FIX        | DMA_DEST_INC    |              \
        DMA_##Bit##BIT_BUS | ((Size)/(Bit/8))));            \
}

#define DmaClearIf(DmaNo, Data, Destp, Size, Bit)           \
{                                                           \
    vu##Bit Tmp = (vu##Bit )(Data);                         \
    DmaSet(DmaNo, &Tmp, Destp, (                            \
        DMA_ENABLE         | DMA_TIMMING_IMM |              \
        DMA_IF_ENABLE      |                                \
        DMA_SRC_FIX        | DMA_DEST_INC    |              \
        DMA_##Bit##BIT_BUS | ((Size)/(Bit/8))));            \
}

#define DmaArrayClear(  DmaNo, Data, Destp, Bit)            \
        DmaClear(       DmaNo, Data, Destp, sizeof(Destp), Bit)

#define DmaArrayClearIf(DmaNo, Data, Destp, Bit)            \
        DmaClearIf(     DmaNo, Data, Destp, sizeof(Destp), Bit)

//* Clear RAM with DMA.
//* Clear Data is placed in a Stack and copied to the Destination.
//* DmaClearIf/DmaArrayClearIf generates an Interrupt Request when ending.
//* DmaArrayClear/DmaArrayClearIf clears the entire Destination Array.
//
//* Arguments: 
//  DmaNo       DMA Number
//  Data        Clear Data
//  Destp       Destination Address
//  Size        Clear Byte Size
//  Bit         Transfer Bit Width (16|32)
//
//
// *By running DMA with a program in the CPU internal RAM, 
//  the instruction immediately following is executed first.
//  Due to this, when you attempt to change the transfer
//  destination with the CPU directly following DMA, the DMA
//  will run during Read/Rewrite.  Thus, there are cases when 
//  the DMA destination data can become a value that was not
//  intended.  In this case, if you insert DmaWait() directly
//  following, you can check if DMA has finished and be sure to
//  avoid any impact on following code.

/*------------------------------------------------------------------*/
/*                      Copy DMA                                    */
/*------------------------------------------------------------------*/

#define DmaCopy(DmaNo, Srcp, Destp, Size, Bit)              \
                                                            \
    DmaSet(DmaNo, Srcp, Destp,  (                           \
        DMA_ENABLE         | DMA_TIMMING_IMM |              \
        DMA_SRC_INC        | DMA_DEST_INC    |              \
        DMA_##Bit##BIT_BUS | ((Size)/((Bit)/8))))

#define DmaCopyIf(DmaNo, Srcp, Destp, Size, Bit)            \
                                                            \
    DmaSet(DmaNo, Srcp, Destp,  (                           \
        DMA_ENABLE         | DMA_TIMMING_IMM |              \
        DMA_IF_ENABLE      |                                \
        DMA_SRC_INC        | DMA_DEST_INC    |              \
        DMA_##Bit##BIT_BUS | ((Size)/(Bit/8))))

#define DmaArrayCopy(  DmaNo, Srcp, Destp, Bit)             \
        DmaCopy(       DmaNo, Srcp, Destp, sizeof(Srcp), Bit)

#define DmaArrayCopyIf(DmaNo, Srcp, Destp, Bit)             \
        DmaCopyIf(     DmaNo, Srcp, Destp, sizeof(Srcp), Bit)

//* Copy with DMA.
//* DmaCopyIf/DmaArrayCopyIf generates an Interrupt Request when ending.
//* DmaArrayCopy/DmaArrayCopyIf copies the entire source array.
//
//* Arguments: 
//  DmaNo       DMA Number
//  Srcp        Source Address
//  Destp       Destination Address
//  Size        Transfer Byte Size
//  Bit         Transfer Bit Width (16|32)
//
//
// *By running DMA with a program in the CPU internal RAM,
//  the instruction immediately following is executed first. 
//  Due to this, when you attempt to change the transfer 
//  destination with the CPU directly following DMA, the DMA 
//  will run during Read/Rewrite. Thus, there are cases when 
//  the DMA destination data can become a value that was not 
//  intended. In this case, if you insert DmaWait() directly 
//  following, you can check if DMA has finished and be sure to 
//  avoid any impact on following code.  

/*------------------------------------------------------------------*/
/*                 Copy H Blank DMA                                 */
/*------------------------------------------------------------------*/

#define H_DmaCopy(DmaNo, Srcp, Destp, Size, Bit)            \
                                                            \
    DmaSet(DmaNo, Srcp, Destp,  (                           \
        DMA_ENABLE         | DMA_TIMMING_H_BLANK |          \
        DMA_SRC_INC        | DMA_DEST_RELOAD     |          \
        DMA_CONTINUOUS_ON  |                                \
        DMA_##Bit##BIT_BUS | ((Size)/((Bit)/8))))

#define H_DmaCopyIf(DmaNo, Srcp, Destp, Size, Bit)          \
                                                            \
    DmaSet(DmaNo, Srcp, Destp,  (                           \
        DMA_ENABLE         | DMA_TIMMING_H_BLANK |          \
        DMA_IF_ENABLE      |                                \
        DMA_SRC_INC        | DMA_DEST_RELOAD     |          \
        DMA_CONTINUOUS_ON  |                                \
        DMA_##Bit##BIT_BUS | ((Size)/(Bit/8))))

#define H_DmaArrayCopy(  DmaNo, Srcp, Destp, Bit)           \
        H_DmaCopy(       DmaNo, Srcp, Destp, sizeof(Srcp), Bit)

#define H_DmaArrayCopyIf(DmaNo, Srcp, Destp, Bit)           \
        H_DmaCopyIf(     DmaNo, Srcp, Destp, sizeof(Srcp), Bit)

// Synchronize with H Blank and copy using DMA.
// H_DmaCopyIf/H_DmaArrayCopyIf generates an Interrupt Request when ending.
// H_DmaArrayCopy/H_DmaArrayCopyIf copies the entire Source Array.
//
// Arguments:
//  DmaNo       DMA Number
//  Srcp        Source Address
//  Destp       Destination Address
//  Size        Transfer Byte Size
//  Bit         Transfer Bit Width(16|32)

/*------------------------------------------------------------------*/
/*                  Copy V Blank DMA                                */
/*------------------------------------------------------------------*/

#define V_DmaCopy(DmaNo, Srcp, Destp, Size, Bit)            \
                                                            \
    DmaSet(DmaNo, Srcp, Destp,  (                           \
        DMA_ENABLE         | DMA_TIMMING_V_BLANK |          \
        DMA_SRC_INC        | DMA_DEST_INC        |          \
        DMA_##Bit##BIT_BUS | ((Size)/(Bit/8))))

#define V_DmaCopyIf(DmaNo, Srcp, Destp, Size, Bit)          \
                                                            \
    DmaSet(DmaNo, Srcp, Destp,  (                           \
        DMA_ENABLE         | DMA_TIMMING_V_BLANK |          \
        DMA_IF_ENABLE      |                                \
        DMA_SRC_INC        | DMA_DEST_INC        |          \
        DMA_##Bit##BIT_BUS | ((Size)/(Bit/8))))

#define V_DmaArrayCopy(  DmaNo, Srcp, Destp, Bit)           \
        V_DmaCopy(       DmaNo, Srcp, Destp, sizeof(Srcp), Bit)

#define V_DmaArrayCopyIf(DmaNo, Srcp, Destp, Bit)           \
        V_DmaCopyIf(     DmaNo, Srcp, Destp, sizeof(Srcp), Bit)

// Synchronize with V Blank and copy using DMA.
// V_DmaCopyIf/V_DmaArrayCopyIf generates an Interrupt Request when ending.
// V_DmaArrayCopy/V_DmaArrayCopyIf copies entire Source Array.
//
// Arguments:
//  DmaNo       DMANumber
//  Srcp        SourceAddress
//  Destp       DestinationAddress
//  Size        Transfer Byte Size
//  Bit         Transfer Bit Width(16|32)

/*------------------------------------------------------------------*/
/*                  Transfer DMA Sound FIFO                         */
/*------------------------------------------------------------------*/

#if 1
#define DmaSound(DmaNo, Srcp, FifoName)                             \
{                                                                   \
    u8    i;                                                        \
    *((u8 *)(REG_SOUNDCNT + 3)) |= SOUND_##FifoName##_FIFO_RESET;   \
    for (i=0; i<8; i++)                                             \
        *(u32 *)REG_FIFO_##FifoName = ((u32 *)Srcp)[i];             \
    DmaSet( DmaNo, (u32 *)Srcp + 8, REG_FIFO_##FifoName, (          \
        DMA_ENABLE         | DMA_TIMMING_SOUND |                    \
        DMA_CONTINUOUS_ON  |                                        \
        DMA_SRC_INC        | DMA_DEST_FIX      |                    \
        DMA_32BIT_BUS      | (4*4)/(32/8)))                         \
}

#define DmaSoundIf(DmaNo, Srcp, FifoName)                           \
{                                                                   \
    u8    i;                                                        \
    *((u8 *)(REG_SOUNDCNT + 3)) |= SOUND_##FifoName##_FIFO_RESET;   \
    for (i=0; i<8; i++)                                             \
        *(u32 *)REG_FIFO_##FifoName = ((u32 *)Srcp)[i];             \
    DmaSet( DmaNo, (u32 *)Srcp + 8, REG_FIFO_##FifoName, (          \
        DMA_ENABLE         | DMA_TIMMING_SOUND |                    \
        DMA_IF_ENABLE      |                                        \
        DMA_CONTINUOUS_ON  |                                        \
        DMA_SRC_INC        | DMA_DEST_FIX      |                    \
        DMA_32BIT_BUS      | (4*4)/(32/8)))                         \
}
#else
#define DmaSound(DmaNo, Srcp, FifoName)                             \
                                                                    \
    DmaSet( DmaNo, Srcp, REG_FIFO_##FifoName, (                     \
        DMA_ENABLE         | DMA_TIMMING_SOUND |                    \
        DMA_CONTINUOUS_ON  |                                        \
        DMA_SRC_INC        | DMA_DEST_FIX      |                    \
        DMA_32BIT_BUS      | (4*4)/(32/8)))

#define DmaSoundIf(DmaNo, Srcp, FifoName)                           \
                                                                    \
    DmaSet(DmaNo, Srcp, REG_FIFO_##FifoName, (                      \
        DMA_ENABLE         | DMA_TIMMING_SOUND |                    \
        DMA_IF_ENABLE      |                                        \
        DMA_CONTINUOUS_ON  |                                        \
        DMA_SRC_INC        | DMA_DEST_FIX      |                    \
        DMA_32BIT_BUS      | (4*4)/(32/8)))
#endif

// Set DMA for Direct Sound.
// DmaSoundIf generates an Interrupt Request when ending.
//
// Arguments:
//  DmaNo       DMA Number
//  Srcp        Source Address
//  FifoName    Destination Address


/*------------------------------------------------------------------*/
/*                      Wait for DMA End                            */
/*------------------------------------------------------------------*/

#define DmaWait(DmaNo)                                      \
{                                                           \
    vu32 *(DmaCntp) = (vu32 *)REG_DMA##DmaNo;               \
    while (DmaCntp[2] & DMA_ENABLE) ;                       \
}

//* Wait for DMA to end.
//
//* Arguments:
//  DmaNo       DMA Number


/*------------------------------------------------------------------*/
/*                      Stop DMA                                    */
/*------------------------------------------------------------------*/

#define DmaStop(DmaNo)                                      \
{                                                           \
    vu16 *(DmaCntp) = (vu16 *)REG_DMA##DmaNo;               \
    DmaCntp[5] &= ~((DMA_TIMMING_MASK | DMA_CONTINUOUS_ON   \
                   | DMA_DREQ_ON) >> 16);                   \
    DmaCntp[5] &= ~( DMA_ENABLE   >> 16);                   \
    DmaCntp[5];                                             \
}

// Stop DMA.
//* However, if automatic start of DMA is activated during a processing, DMA is
//executed only once.  
//* When stopping Sound DMA, please set the settings that agree with the actual
//operation in advance at the time of starting.    
//
// Arguments:
//  DmaNo       DMA Number


/*------------------------------------------------------------------*/
/*                      Clear CPU                                   */
/*------------------------------------------------------------------*/

#define CpuClear(Data, Destp, Size, Bit)                    \
{                                                           \
    vu##Bit Tmp = (vu##Bit )(Data);                         \
    CpuSet((u8 *)&(Tmp), (u8 *)(Destp), (                   \
        DMA_SRC_FIX        |                                \
        DMA_##Bit##BIT_BUS | ((Size)/(Bit/8) & 0x1fffff))); \
}

#define CpuArrayClear(Data, Destp, Bit)                     \
        CpuClear(     Data, Destp, sizeof(Destp), Bit)

// Call System Call to clear RAM with CPU.
// Place Clear Data in a Stack and copy to Destination.
// CpuArrayClear clears the entire Destination Array.
//
// Arguments:
//  Data        Clear Data
//  Destp       Destination Address
//  Size        Clear Byte Size
//  Bit         Transfer Bit Width(16|32)

/*------------------------------------------------------------------*/
/*                      Copy CPU                                    */
/*------------------------------------------------------------------*/

#define CpuCopy(Srcp, Destp, Size, Bit)                     \
                                                            \
    CpuSet((u8 *)(Srcp), (u8 *)(Destp),  (                  \
        DMA_SRC_INC        |                                \
        DMA_##Bit##BIT_BUS | ((Size)/(Bit/8) & 0x1fffff)))

#define CpuArrayCopy(Srcp, Destp, Bit)                      \
        CpuCopy(     Srcp, Destp, sizeof(Srcp), Bit)

// Call System Call to copy with CPU.
// CpuArrayCopy copies the entire Source Array.
//
// Arguments:
//  Srcp        Source Address
//  Destp       Destination Address
//  Size        Transmit Byte Size
//  Bit         Transfer Bit Width(16|32)

/*------------------------------------------------------------------*/
/*                  CPU High Speed Clear(32Byte Units)              */
/*------------------------------------------------------------------*/

#define CpuFastClear(Data, Destp, Size)                     \
{                                                           \
    vu32 Tmp = (vu32 )(Data);                               \
    CpuFastSet((u8 *)&(Tmp), (u8 *)(Destp), (               \
        DMA_SRC_FIX        | ((Size)/(32/8) & 0x1fffff)));  \
}

#define CpuFastArrayClear(Data, Destp)                      \
        CpuFastClear(     Data, Destp, sizeof(Destp))

// Call System Call to clear RAM at High Speed with CPU.
// Put Clear Data in Stack and copy to Destination.
// CpuFastArrayClear clears the entire Destination Array.
// Clear with 8Word(32Byte) Units using 32-bit Transfer.
//
// Arguments:
//  Data        Clear Data
//  Destp       Destination Address
//  Size        Clear Byte Size

/*------------------------------------------------------------------*/
/*                  CPU High Speed Copy(32Byte Units)               */
/*------------------------------------------------------------------*/


#define CpuFastCopy(Srcp, Destp, Size)                      \
                                                            \
    CpuFastSet((u8 *)(Srcp), (u8 *)(Destp),  (              \
        DMA_SRC_INC           | ((Size)/(32/8) & 0x1fffff)))

#define CpuFastArrayCopy(Srcp, Destp)                       \
        CpuFastCopy(     Srcp, Destp, sizeof(Srcp))

// Call System Call copy at High Speed with CPU.
// CpuFastArrayCopy copies entire Source Array.
// Copy with 8Word(32Byte) Units using 32-bit Transfer.
//
// Arguments:
//  Srcp        Source Address
//  Destp       Destination Address
//  Size        Transfer Byte Size

#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif /* _AGB_MACRO_H */
