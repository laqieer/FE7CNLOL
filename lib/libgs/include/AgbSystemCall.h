#ifndef _AGB_SYSTEM_CALL_H
#define _AGB_SYSTEM_CALL_H

#define SystemCall(No) asm (" SWI    No << 16")

extern void SoftReset(u32 ResetFlags);

extern void RegisterRamReset(u32 ResetFlags);

#define Halt()                   SystemCall(2)

extern void SoundBiasSet(void);
extern void SoundBiasReset(void);

extern void IntrWait(u8 InitCheckClear, u16 IntrFlags);

extern void VBlankIntrWait(void);

extern s32 Div(s32 Number, s32 Denom);      // Compatible with the libary from 
                                            // RedHat (formerly Cygnus)
extern s32 DivArm(s32 Denom, s32 Number);   // Compatible with the library from 

extern s32 DivRem(s32 Number, s32 Denom);    // Compatible with the library from 
                                             // RedHat (formerly Cygnus)
extern s32 DivRemArm(s32 Denom, s32 Number); // Compatible with the library from 
                                             // ARM
extern u16 Sqrt(u32 X);

extern s16 ArcTan(s16 Tan);

extern u16 ArcTan2(s16 X, s16 Y);

extern void CpuSet(void *Srcp, void *Destp, u32 DmaCntData);

extern void CpuFastSet(void *Srcp, void *Destp, u32 DmaCntData);

extern void BgAffineSet(BgAffineSrcData *Srcp, BgAffineDestData *Destp, s32 Num);

// Calculate and set the BG affine parameter.
//
// Arguments:
//  BgAffineSrcData  *Srcp      Source Address
//  BgAffineDestData *Destp     Destination Address
//              s32   Num       Number of times calculated
//
// BgAffineSrcData Structure
//    s32 SrcCenterX            Source Data Center Coordinate (8bits after decimal
//                               point)
//    s32 SrcCenterY
//    s16 DispCenterX           Display Center Coordinate
//    s16 DispCenterY
//    s16 RatioX                Scaling Ratio (8 bits after decimal point)
//    s16 RatioY
//    u16 Theta                 Rotation Angle (8bits after decimal point)
//                                  Valid Range    0 - 0xffff
// BgAffineDestData Structure
//    s16 H_DiffX               Line Direction X Coordinate Difference
//    s16 V_DiffX                 Vertical Direction X Coordinate Difference
//    s16 H_DiffY               Line Direction Y Coordinate Difference
//    s16 V_DiffY                 Vertical Direction Y Coordinate Difference
//    s32 StartX                Start X Coordinate
//    s32 StartY                Start Y Coordinate

/*------------------------------------------------------------------*/
/*                   OBJ Affine Transformation Set                  */
/*------------------------------------------------------------------*/

extern void ObjAffineSet(ObjAffineSrcData *Srcp, void *Destp, s32 Num, s32 Offset);

// Calculate and set the OBJ affine parameter.
//
// Arguments:
//  ObjAffineSrcData *Srcp      Source Address
//              void *Destp     Destination Address
//              s32   Num       Number of times calculated
//              s32   Offset    Parameter address offset byte size (Normally 2|8)
//                              Designate "8" when directly setting to OAM
//
// ObjAffineSrcData Structure
//    s16 RatioX                Scaling Ratio (8bits to the right of the decimal 
//                              point)
//    s16 RatioY
//    u16 Theta                 Rotation Angle (8bits after decimal point)
//                                  Valid Range    0 - 0xffff
// ObjAffineDestData Structure
//    s16 H_DiffX               Line Direction X Coordinate Difference
//    s16 V_DiffX                 Vertical Direction X Coordinate Difference
//    s16 H_DiffY               Line Direction Y Coordinate Difference
//    s16 V_DiffY                 Vertical Direction Y Coordinate Difference

/*------------------------------------------------------------------*/
/*                       Bit Compressed Data Expansion              */
/*------------------------------------------------------------------*/
extern void BitUnPack(void  *Srcp, void *Destp, BitUnPackParam *BitUnPackParamp);

// Expand data with 0 fixed bit.
// Match the destination address to a 4 byte boundary.
//
// Arguments:
//            void *Srcp    Source Address
//            void *Destp   Destination Address
//  BitUnPackParam *Paramp  BitUnPackParam Structure Data Address
//
// BitUnPackParam Structure
//    u16 SrcNum              Source Data Byte Number
//    u8  SrcBitNum           1 Source Data Bit Number
//    u8  DestBitNum          1 Destination Data Bit Number
//    u32 DestOffset:31       Number of offsets that are added to source data
//        DestOffset0_On:1    Flag to indicate whether or not offsett is added to 
//                            0 data

/*------------------------------------------------------------------*/
/*             LZ77 Compressed Data Expansion (-> Work RAM)         */
/*------------------------------------------------------------------*/

extern void LZ77UnCompWram(void *Srcp, void *Destp);

extern void LZ77UnCompVram(void *Srcp, void *Destp);

extern void HuffUnComp(void *Srcp, void *Destp);

extern void RLUnCompWram(void *Srcp, void *Destp);

// Expand run length compressed data and write with 8 bit units.
// Cannot directly expand to VRAM.
// When compressed data size is not a multiple of 4, fill as much as possible 
// with 0 and adjust.
// Match source address to a 4 byte boundary.
//
// Arguments:
//    void *Srcp              Source Address
//    void *Destp             Destination Address
//
// Data Header
//    u32 :4                  Reserve
//        CompType:4          Compressed Type (=3)
//        DestSize:24         Post-expansion Data Size
//
// Flag Data Format 
//    u8  Length:7            Expanded Data Length - 1 (When not compressed)
//                            Expanded Data Length - 3 (Compress only when a 
//                            continuous length is 3 bytes or more)
//        Flag:1              (0, 1) = (Noncompressed data, Compressed data)

/*------------------------------------------------------------------*/
/*              Run Length Compressed Data Expansion (->VRAM)       */
/*------------------------------------------------------------------*/

extern void RLUnCompVram(void *Srcp, void *Destp);

// Expand run length compressed data and write with 16 bit units.
// Can expand to Work RAM, but slower than RLUnCompWram().
// When compressed data size is not a multiple of 4, fill as much as possible 
// with 0 and adjust.
// Match source address to a 4 byte boundary.
//
// Arguments:
//    void *Srcp              Source Address
//    void *Destp             Destination Address
//
// Data Header
//    u32 :4                  Reserve
//        CompType:4          Compressed Type (=3)
//        DestSize:24         Post-expansion data size
//
// Flag Data Format
//    u8  Length:7            Expansion Data Length - 1 (When not compressed)
//                            Expansion Data Length -3 (Compress only when a 
//                            consecutive length is  3 bytes or more)
//        Flag:1              (0, 1) = (Noncompressed Data, Compressed Data)

/*------------------------------------------------------------------*/
/*          Difference Filter Expansion (8bits -> Work RAM)         */
/*------------------------------------------------------------------*/

extern void Diff8bitUnFilterWram(void *Srcp, void *Destp);

extern void Diff8bitUnFilterVram(void *Srcp, void *Destp);

extern void Diff16bitUnFilter(void *Srcp, void *Destp);

extern void SoundBiasSet(void);

extern void SoundBiasReset(void);

//extern void SoundDriverInit(SoundArea *sa);

extern void SoundDriverMode(u32 mode);

extern void SoundDriverMain(void);

extern void SoundDriverVSync(void);

extern void SoundChannelClear(void);

extern void SoundDriverVSyncOff(void);

extern void SoundDriverVSyncOn(void);

#endif /* _AGB_SYSTEM_CALL_H */
