#ifndef GsGBA_TYPE_H
#define GsGBA_TYPE_H



//类型定义--------------------------------------------------------------
typedef unsigned char			u8;
typedef unsigned short			u16;
typedef unsigned long			u32;

typedef signed char				s8;
typedef signed short			s16;
typedef signed long				s32;
typedef signed long long int    s64;

typedef volatile unsigned char  vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned long  vu32;
typedef volatile long long int  vu64;

typedef volatile char			vs8;
typedef volatile short			vs16;
typedef volatile long			vs32;
typedef volatile long long int  vs64;

typedef float					f32;
typedef double					f64;

typedef volatile float			vf32;
typedef volatile double			vf64;

#define BIT00 1
#define BIT01 2
#define BIT02 4
#define BIT03 8
#define BIT04 16
#define BIT05 32
#define BIT06 64
#define BIT07 128
#define BIT08 256
#define BIT09 512
#define BIT10 1024
#define BIT11 2048
#define BIT12 4096
#define BIT13 8192
#define BIT14 16384
#define BIT15 32768

//structs
typedef struct s_RGB
{
	u16 r:5;
	u16 g:5;
	u16 b:5;
	u16 dummy:1;
}s_RGB;


// 程序状态字 寄存器
typedef struct s_PsrData{
    u32 CpuMode:5;          // CPU Mode
    u32 Thumb_State:1;      // THUMB State
    u32 Fiq_Disable:1;      // FIQ Disable
    u32 Irq_Disable:1;      // IRQ Disable
    u32 Dummy_27_8:20;
    u32 V_Flag:1;           // Overflow
    u32 C_Flag:1;           // Carry/Borrow/Expand
    u32 Z_Flag:1;           // Zero
    u32 N_Flag:1;           // Negative/Less than
} s_PsrData;

typedef volatile s_PsrData    vPsrData;


// 中断标志REG
typedef struct {
    u16 V_Blank:1;          // V Blank
    u16 H_Blank:1;          // H Blank
    u16 V_Count:1;          // V Counter Matching
    u16 Timer0:1;           // Timer 0
    u16 Timer1:1;           // Timer 1
    u16 Timer2:1;           // Timer 2
    u16 Timer3:1;           // Timer 3
    u16 Sio:1;              // Serial Communication
    u16 Dma0:1;             // DMA 0
    u16 Dma1:1;             // DMA 1
    u16 Dma2:1;             // DMA 2
    u16 Dma3:1;             // DMA 3
    u16 Key:1;              // Key
    u16 Cassette:1;         // Game Pak
    u16 Dummy_15_14:2;
} s_IntrFlags;

typedef  volatile s_IntrFlags    vIntrFlags;

// 屏幕控制结构
typedef struct s_DispCnt{
    u16 BgMode:3;           // BG Mode Select
    u16 CgbMode:1;          // CGB Mode Select
    u16 Bmp_FrameNo:1;      // Bitmap Mode Display Frame Select
    u16 Obj_H_Off:1;        // OBJ Processing in H Blank OFF
    u16 ObjCharMapType:1;   // OBJ Character Data Mapping Type
    u16 Lcdc_Off:1;         // LCDC OFF
    u16 Bg0_On:1;           // BG 0 ON
    u16 Bg1_On:1;           // BG 1 ON
    u16 Bg2_On:1;           // BG 2 ON
    u16 Bg3_On:1;           // BG 3 ON
    u16 Obj_On:1;           // OBJ ON
    u16 Win0_On:1;          // Window 0 ON
    u16 Win1_On:1;          // Window 1 ON
    u16 ObjWin_On:1;        // OBJ Window ON
} s_DispCnt;

typedef  volatile s_DispCnt   vDispCnt;


// 状态位
typedef struct s_StatCnt{
    u16 V_Blank_Flag:1;     // During V Blank
    u16 H_Blank_Flag:1;     // During H Blank
    u16 V_Count_Flag:1;     // V Counter Matching
    u16 V_Blank_IF_Enable:1;// V Blank Interrupt Request Enable
    u16 H_Blank_IF_Enable:1;// H Blank Interrupt Request Enable
    u16 V_Count_IF_Enable:1;// V Counter Matching Interrupt Request Enable
    u16 Dummy_7_6:2;
    u8  V_Count_Cmp;        // V Counter Comparison Value
    u8  V_Count;            // V Counter Value
    u8  Dummy_31_24;
} s_StatCnt;
typedef  volatile s_StatCnt   vStatCnt;


// 马赛克控制
typedef struct s_MosCnt{
    u16 Bg_HSize:4;         // BG Mosaic H Size
    u16 Bg_VSize:4;         // BG Mosaic V Size
    u16 Obj_HSize:4;        // OBJ Mosaic H Size
    u16 Obj_VSize:4;        // OBJ Mosaic V Size
} s_MosCnt;
typedef  volatile s_MosCnt    vMosCnt;


// Blend Control Structure
typedef struct s_BlendCnt{
    u16 Pixel_1st_Bg0_On:1; // 1st Pixel
    u16 Pixel_1st_Bg1_On:1;
    u16 Pixel_1st_Bg2_On:1;
    u16 Pixel_1st_Bg3_On:1;
    u16 Pixel_1st_Obj_On:1;
    u16 Pixel_1st_Bd_On:1;
    u16 BlendMode:2;        // Blend Mode
    u16 Pixel_2nd_Bg0_On:1; // 2nd Pixel
    u16 Pixel_2nd_Bg1_On:1;
    u16 Pixel_2nd_Bg2_On:1;
    u16 Pixel_2nd_Bg3_On:1;
    u16 Pixel_2nd_Obj_On:1;
    u16 Pixel_2nd_Bd_On:1;
    u16 Dummy_15_14:2;

    u16 Value_A:5;          // Parameter A
    u16 Dummy_23_21:3;
    u16 Value_B:5;          // Parameter B
    u16 Dummy_31_29:3;
    u16 Value_Y:5;          // Parameter Y
    u16 Dummy_39_37:3;
} s_BlendCnt;
typedef  volatile s_BlendCnt    vBlendCnt;


// BG Control Structure
typedef struct s_BgCnt{
    u16 Priority:2;         // Display Priority
    u16 CharBasep:2;        // Character Base Address
    u16 Dummy_5_4:2;
    u16 Mosaic:1;           // Mozaic
    u16 ColorMode:1;        // 16 colors/ 256 colors Select
    u16 ScBasep:5;          // Screen Base Address
    u16 Loop:1;             // Loop
    u16 Size:2;             // Screen Size
} s_BgCnt;
typedef  volatile s_BgCnt    vBgCnt;


// BG Offset Control Structure
typedef struct s_BgOffsetCnt{
    u16 H;
    u16 V;
} s_BgOffsetCnt;
typedef  volatile s_BgOffsetCnt    vBgOffsetCnt;

// BG Screen Structure	//MAP文件的数据格式
typedef struct s_BgScData{
    u16 CharNo:10;          // Character No
    u16 HFlip:1;            // H Flip
    u16 VFlip:1;            // V Flip
    u16 Pltt:4;             // Palette No
} s_BgScData;
typedef  volatile s_BgScData       vBgScData;
typedef  volatile s_BgScData       BgScData;


// BG Affine Transformation Source Data Structure
typedef struct s_BgAffineSrcData{
    s32 SrcCenterX;         // Source Data Center Coordinate  << 8
    s32 SrcCenterY;
    s16 DispCenterX;        // Display Center Coordinate	//pa
    s16 DispCenterY;
    s16 RatioX;             // Scaling Ratio << 8			//pb	
    s16 RatioY;
    u16 Theta;              // Rotation Angle (0 - 255) << 8	//pc
} s_BgAffineSrcData;
typedef  volatile s_BgAffineSrcData    vBgAffineSrcData;
typedef  volatile s_BgAffineSrcData    BgAffineSrcData;


// BG Affine Transformation Destination Data Structure
typedef struct s_BgAffineDestData{
    s16 H_DiffX;            // Line Direction X Coordinate Difference
    s16 V_DiffX;            // Vertical Direction X Coordinate Difference
    s16 H_DiffY;            // Line Direction Y Coordinate Difference
    s16 V_DiffY;            // Vertical Direction Y Coordinate Difference
    s32 StartX;             // Start X Coordinate
    s32 StartY;             // Start Y Coordinate
} s_BgAffineDestData;
typedef  volatile s_BgAffineDestData   vBgAffineDestData;
typedef  volatile s_BgAffineDestData   BgAffineDestData;

//in memory lay
typedef struct s_BGST
{
	u16 XL;
	u16 XH;
	u16 YL;
	u16 YH;
}s_BGST;
typedef volatile s_BGST vBGST;


typedef struct s_BGDP
{
	s16 PA;
	s16 PB;
	s16 PC;
	s16 PD;
}s_BGDP;



// OAM Structure
typedef struct s_OamData{
    u32 VPos:8;             // Y Coordinate
    u32 AffineMode:2;       // Affine Mode
	u32 ObjMode:2;          // OBJ Mode
    u32 Mosaic:1;           // Mosaic
    u32 ColorMode:1;        // 16 colors/256 colors Select
    u32 Shape:2;            // OBJ Shape

    u32 HPos:9;             // X Coordinate
    
	u32 AffineParamNo_L:3;  // Affine Transformation Parameter No.  Lower 3 bits
    u32 HFlip:1;            // H Flip
    u32 VFlip:1;            // V Flip
	
    u32 Size:2;             // OBJ Size

    u32 CharNo:10;          // Character No
    u32 Priority:2;         // Display Priority
    u32 Pltt:4;             // Palette No
    u16 AffineParam;        // Affine Trasnformation Parameter
} s_OamData;
typedef  volatile s_OamData    vOamData;
typedef  volatile s_OamData    SPRITE;


// OBJ Affine Transformation Source Data Structure
typedef struct s_ObjAffineSrcData{
    s16 RatioX;             // Scaling Ratio
    s16 RatioY;
    u16 Theta;              // Rotation Angle (0 - 255) << 8
} s_ObjAffineSrcData;
typedef  volatile s_ObjAffineSrcData   vObjAffineSrcData;
typedef  volatile s_ObjAffineSrcData   GsSPRITEAffine;
typedef  volatile s_ObjAffineSrcData   ObjAffineSrcData;

// OBJ Affine Transformation Destination Data Structure
typedef struct s_ObjAffineDestData{
    s16 H_DiffX;            // Line Direction X Coordinate Difference
    s16 V_DiffX;            // Vertical Direction X Coordinate Difference
    s16 H_DiffY;            // Line Direction Y Coordinate Difference
    s16 V_DiffY;            // Vertical Direction Y Coordinate Difference
} s_ObjAffineDestData;
typedef  volatile s_ObjAffineDestData  vObjAffineDestData;
typedef  volatile s_ObjAffineDestData  ObjAffineDestData;


// Color Palette Structure
typedef struct s_PlttData{
    u16 Red:5;              // Red
    u16 Green:5;            // Green
    u16 Blue:5;             // Blue
    u16 Dummy_15:1;
} s_PlttData;
typedef  volatile s_PlttData    vPlttData;


// Window Control Structure
typedef struct s_WindCnt{
    u16  Bg0_On:1;           // BG 0 ON			//WINDOW 0 AND 1
    u16  Bg1_On:1;           // BG 1 ON
    u16  Bg2_On:1;           // BG 2 ON
    u16  Bg3_On:1;           // BG 3 ON
    u16  Obj_On:1;           // OBJ ON
    u16  Blend_On:1;         // Color Special Effect ON
    u16  Dummy_7_6:2;

	u16  OBJ_Bg0_On:1;           // BG 0 ON		//OBJ window
    u16  OBJ_Bg1_On:1;           // BG 1 ON
    u16  OBJ_Bg2_On:1;           // BG 2 ON
    u16  OBJ_Bg3_On:1;           // BG 3 ON
    u16  OBJ_Obj_On:1;           // OBJ ON
    u16  OBJ_Blend_On:1;         // Color Special Effect ON
    u16  OBJ_Dummy_7_6:2;

} s_WindCnt;
typedef  volatile s_WindCnt     vWindCnt;


// Sound Control Structure
typedef struct s_SoundCnt{
	//L
    u8  So1_Level:3;        // S01 Output Level
    u8  So1_Vin_On:1;       // Vin -> S01 ON
    u8  So2_Level:3;        // S02 Output Level
    u8  So2_Vin_On:1;       // Vin -> S02 ON
    u8  So1_Sound1_On:1;    // Sound 1 -> S01 ON
    u8  So1_Sound2_On:1;    // Sound 2 -> S01 ON
    u8  So1_Sound3_On:1;    // Sound 3 -> S01 ON
    u8  So1_Sound4_On:1;    // Sound 4 -> S01 ON
    u8  So2_Sound1_On:1;    // Sound 1 -> S02 ON
    u8  So2_Sound2_On:1;    // Sound 2 -> S02 ON
    u8  So2_Sound3_On:1;    // Sound 3 -> S02 ON
    u8  So2_Sound4_On:1;    // Sound 4 -> S02 ON
	//H
    u8  Sound_1_4_Mix:2;    // DMG Compatible Sound Mix Ratio
    u8  DirectA_Mix:1;      // Direct Sound A Mix Ratio
    u8  DirectB_Mix:1;      // Direct Sound B Mix Ratio
    u8  Dummy_23_20:4;
    u8  So1_DirectA_On:1;   // Direct Sound A -> S01 ON
    u8  So2_DirectA_On:1;   // Direct Sound A -> S02 ON
    u8  DirectA_Timer:1;    // Direct Sound A Timer Select
    u8  FifoA_Reset:1;      // Direct Sound A FIFO Reset
    u8  So1_DirectB_On:1;   // Direct Sound B -> S01 ON
    u8  So2_DirectB_On:1;   // Direct Sound B -> S02 ON
    u8  DirectB_Timer:1;    // Direct Sound B Timer Select
    u8  FifoB_Reset:1;      // Direct Sound B FIFO Reset
	//x
    u8  Sound1_On:1;        // Sound 1 ON
    u8  Sound2_On:1;        // Sound 2 ON
    u8  Sound3_On:1;        // Sound 3 ON
    u8  Sound4_On:1;        // Sound 4 ON
    u8  Dummy_38_36:3;
    u8  Sound_1_4_On:1;     // DMG Compatible Sound ON

    u8  Dummy_47_40;
    u16 Dummy_63_48;
    u16 BiasLevel:10;       // BIAS Level
    u16 Dummy_77_74:4;
    u16 OutFrequency:2;     // Replay Frequency	//00 9bit 32.768KHz  
												//01 8bit 65.536KHz 
												//10 7bit 131.072KHz 
												//11 6bit 262.144KHz  
} s_SoundCnt;
typedef  volatile s_SoundCnt     vSoundCnt;

// Sound 1 Control Structure
typedef struct s_Sound1Cnt{
    u8  SweepShift:3;       // Sweep Shift Number
    u8  SweepUpDownt:1;     // Sweep Up/Down
    u8  SweepTime:3;        // Sweep Time
    u8  Dummy_7:1;
    u8  Dummy_15_8;
    u8  Counts:6;           // Sound Length (Count Number)
    u8  Duty:2;             // Waveform Duty
    u8  EnvSteps:3;         // Envelope Step Number
    u8  EnvUp_Down:1;       // Envelope UP/DOWN
    u8  EnvInitData:4;      // Envelope Inial Value
    u16 Frequency:11;       // Frequency
    u16 Dummy_45_43:3;
    u16 Counter_On:1;       // Counter ON
    u16 Start:1;            // Start
} s_Sound1Cnt;
typedef  volatile s_Sound1Cnt    vSound1Cnt;
typedef  vSound1Cnt    GsSound1Cnt;

// Sound 2 Control Structure
typedef struct s_Sound2Cnt{
    u8  Counts:6;           // Sound Length (Count Number)
    u8  Duty:2;             // Waveform Duty
    u8  EnvSteps:3;         // Envelope Step Number
    u8  EnvUp_Down:1;       // Envelope UP/DOWN
    u8  EnvInitData:4;      // Envelope Initial Value
    u16 Dummy_31_16;
    u16 Frequency:11;       // Frequency
    u16 Dummy_45_43:3;
    u16 Counter_On:1;       // Counter ON
    u16 Start:1;            // Start
} s_Sound2Cnt;
typedef  volatile s_Sound2Cnt    vSound2Cnt;
typedef vSound2Cnt GsSound2Cnt;

// Sound 3 Control Structure
typedef struct s_Sound3Cnt{
    u8  Dummy_6_0:5;
    u8  Connect:1;          // Waveform RAM Connect
    u8  Bank:1;             // Waveform RAM Bank
    u8  On:1;               // Sound 3 ON
    u8  Dummy_15_8;
    u8  Counts;             // Sound Length (Count Number)
    u8  Dummy_28_24:5;
    u8  OutputLevel:3;      // Output Level
    u16 Frequency:11;       // Frequency
    u16 Dummy_45_43:3;
    u16 Counter_On:1;       // Counter ON
    u16 Start:1;            // Start
} s_Sound3Cnt;
typedef  volatile s_Sound3Cnt    vSound3Cnt;
typedef vSound3Cnt GsSound3Cnt;

// Sound 4 Control Structure
typedef struct s_Sound4Cnt{
    u8  Counts:6;           // Sound Length (Count Number)
    u8  Dummy_15_14:2;
    u8  EnvSteps:3;         // Envelope Step Number
    u8  EnvUp_Down:1;       // Envelope UP/DOWN
    u8  EnvInitData:4;      // Envelope Initial Value
    u16 Dummy_31_16;
    u8  PreScaler:3;        // Prescaler Select
    u8  PolySteps:1;        // Polynomical/Counter Step Number Select
    u8  PolyShift:4;        // Polynomical/Counter Shift Number
    u8  Dummy45_40:6;
    u8  Counter_On:1;       // Counter ON
    u8  Start:1;            // Start
} s_Sound4Cnt;
typedef  volatile s_Sound4Cnt    vSound4Cnt;
typedef vSound4Cnt GsSound4Cnt;


// Normal SIO Control Structure
typedef struct s_SioNormalCnt{
    u16 Sck_I_O:1;          // Clock I/O Select
    u16 Sck:1;              // Internal Clock Select
    u16 AckRecv:1;          // Transfer Enable Flag Receive
    u16 AckSend:1;          // Transfer Enable Flag Send
    u16 Dummy_6_4:3;
    u16 Enable:1;           // SIO Enable
    u16 Dummy_11_8:4;
    u16 Mode:2;             // Communication Mode Select
    u16 IF_Enable:1;        // Interrupt Request Enable
    u16 Dammy_15:1;
    u8  Data;               // Data
    u8  Dummy_31_24;
} s_SioNormalCnt;
typedef  volatile s_SioNormalCnt    vSioNormalCnt;

// Multi-play SIO Control Structure
typedef struct s_SioMultiCnt{
    u16 BaudRate:2;         // Baud Rate
    u16 SI:1;               // SI Terminal
    u16 SD:1;               // SD Terminal
    u16 ID:2;               // ID
    u16 Error:1;            // Error Detect
    u16 Enable:1;           // SIO Enable
    u16 Dummy_11_8:4;
    u16 Mode:2;             // Communication Mode Select
    u16 IF_Enable:1;        // Interrupt Request Enable
    u16 Dammy_15:1;
    u16 Data;               // Data
} s_SioMultiCnt;
typedef  volatile s_SioMultiCnt     vSioMultiCnt;

// UART - SIO Control Structure
typedef struct s_SioUartCnt{
    u16 BaudRate:2;         // Baud Rate
    u16 Cts_Enable:1;       // Send Signal Enable
    u16 ParitySelect:1;     // Parity Even/Odd
    u16 TransDataFull:1;    // Transmit Data Full
    u16 RecvDataEmpty:1;    // Receive Data Empty
    u16 Error:1;            // Error Detect
    u16 Length:1;           // Data Length
    u16 Fifo_Enable:1;      // FIFO Enable
    u16 Parity_Enable:1;    // Parity Enable
    u16 Trans_Enable:1;     // Transmitter Enable
    u16 Recv_Enable:1;      // Receiver Enable
    u16 Mode:2;             // Communication Mode Select
    u16 IF_Enable:1;        // Interrupt Request Enable
    u16 Dammy_15:1;
    u8  Data;               // Data
    u8  Dummy_31_24;
} s_SioUartCnt;
typedef  volatile s_SioUartCnt		vSioUartCnt;


// JOY Bus Communication Control Structure
typedef struct s_JoyCnt{
    u8  IF_Reset:1;         // JOY Bus Reset Interrupt Request
    u8  IF_Recv:1;          // JOY Bus Received Interrupt Request
    u8  IF_Send:1;          // JOY Bus Sent Interrupt Request
    u8  Dummy_5_3:3;
    u8  IF_Enable:1;        // Interrupt Request Enable
    u8  Dummy_7:1;
} s_JoyCnt;
typedef  volatile s_JoyCnt     vJoyCnt;

// JOY Bus Communication Status Structure
typedef struct s_JoyStat{
    u8  Dummy_0:1;
    u8  Recv:1;             // Receive Status
    u8  Dummy_2:1;
    u8  Send:1;             // Send Status
    u8  Flags:2;            // General Flag
    u8  Dummy_7_6:2;
} s_JoyStat;
typedef  volatile s_JoyStat    vJoyStat;


// General Input/Output Control Structure
typedef struct s_RCnt{
    u8  SC:1;               // Data
    u8  SD:1;
    u8  SI:1;
    u8  SO:1;
    u8  SC_I_O:1;           // I/O Select
    u8  SD_I_O:1;
    u8  SI_I_O:1;
    u8  SO_I_O:1;
    u8  IF_Enable:1;        // Interrupt Request Enable
    u8  Dummy_13_9:5;
    u8  SioModeMaster:2;    // SIO Mode Master
} s_RCnt;
typedef  volatile s_RCnt      vRCnt;


// DMA Control Structure
typedef struct s_DmaCnt{
    u16 Count;              // Transfer Count
    u16 Dummy_21_16:5;
    u16 DestpCnt:2;         // Destination Address Control
    u16 SrcpCnt:2;          // Source Address Control
    u16 ContinuousON:1;     // Continuous Mode
    u16 BusSize:1;          // Bus Size 16/32Bit Select
    u16 DataRequest:1;      // Data Request Synchronize Mode
    u16 Timming:2;          // Timing Select
    u16 IF_Enable:1;        // Interrupt Request Enable
    u16 Enable:1;           // DMA Enable
} s_DmaCnt;
typedef volatile s_DmaCnt    vDmaCnt;


// Timer Control Structure
typedef struct s_TimerCnt{
    u16 Count;              // Count Number
    u16 PreScaler:2;        // Prescaler Select
    u16 Connect:1;          // Lower Timer Connect
    u16 Dummy_5_3:3;
    u16 IF_Enable:1;        // Interrupt Request Enable
    u16 Enable:1;           // Timer Enable
    u16 Dummy_15_8:8;
} s_TimerCnt;
typedef volatile s_TimerCnt    vTimerCnt;


// Key Data Structure
typedef struct s_KeyData{
    u16 A:1;                // A
    u16 B:1;                // B
    u16 Select:1;           // SELECT
    u16 Start:1;            // START
    u16 Plus_R:1;           // Right
    u16 Plus_L:1;           // Left
    u16 Plus_U:1;           // Higher
    u16 Plus_D:1;           // Lower
    u16 R:1;                // R
    u16 L:1;                // L
    u16 Dummy_15_10:6;
} s_KeyData;
typedef volatile s_KeyData   vKeyData;

// Key Control Structure
typedef struct s_KeyCnt{
    u16 Sel_A:1;            // Select A Button
    u16 Sel_B:1;            // Select B Button
    u16 Sel_Select:1;       // Select SELECT Button
    u16 Sel_Start:1;        // Select START Button
    u16 Sel_Plus_R:1;       // Select Right Key
    u16 Sel_Plus_L:1;       // Select Left Key
    u16 Sel_Plus_U:1;       // Select Up Key
    u16 Sel_Plus_D:1;       // Select Down Key
    u16 Sel_R:1;            // Select R Button
    u16 Sel_L:1;            // Select L Button
    u16 Dummy_13_10:4;
    u16 IF_Enable:1;        // Interrupt Request Enable
    u16 IntrType:1;         // Interrupt Type Select
} s_KeyCnt;
typedef  volatile s_KeyCnt    vKeyCnt;


// Game Pak Wait Control Structure
typedef struct s_CstWaitCnt{
    u16 Sram:2;             // SRAM Wait
    u16 Rom0_1st:2;         // ROM 0 1st Wait
    u16 Rom0_2nd:1;         //          2nd Wait
    u16 Rom1_1st:2;         // ROM 1 1st Wait
    u16 Rom1_2nd:1;         //          2nd Wait
    u16 Rom2_1st:2;         // ROM 2 1st Wait
    u16 Rom2_2nd:1;         //          2nd Wait
    u16 OutClock:2;         // Output Clock Select
    u16 Dummy_13:1;
    u16 PrefetchEnale:1;    // Prefetch Buffer Enable
    u16 CassetteType:1;     // Game Pak Type
} s_CstWaitCnt;
typedef  volatile s_CstWaitCnt   vCstWaitCnt;


// Bit Compress Data Expansion Parameter
typedef struct s_BitUnPackParam{
    u16 SrcNum;             // Source Data Byte Size
    u8  SrcBitNum;          // 1 Source Data Bit Number
    u8  DestBitNum;         // 1 Destination Data Bit Number
    u32 DestOffset:31;      // Number added to Source Data
    u32 DestOffset0_On:1;   // Flag to add/not add Offset to 0 Data
} s_BitUnPackParam;
typedef volatile s_BitUnPackParam   vBitUnPackParam;
typedef volatile s_BitUnPackParam   BitUnPackParam;

// DMA struct
typedef struct s_DMACnt			//DMA控制字
{
	u16 Count		  ;		//传输数量
	u16 dummy		:5;		//xxxxx
	u16 DestAddrCnt	:2;		//0:递增传输,1:递减传输,2:固定传输,3递增后传输
	u16 SrcAddrCnt	:2;		//0:递增传输,1:递减传输,2:固定传输,3禁止
	u16 DMARepeat	:1;		//0：OFF ，1： ON
	u16 transTYPE	:1;		// 0:16bit or 1:32 bit
	u16 TIMING		:2;		//0:立即模式,1:由V中断触发,2:由H中断触发 3:禁止
	u16 IREQ		:1;		//中断允许 0：OFF 1：ON
	u16 DMAFLAG		:1;		//DMA使能0:0FF,1:ON
}s_DMACnt;
typedef volatile s_DMACnt vDMACnt;

typedef struct GsSoundCnt
{
	u16 RightOutVol:3;
	u16 dummy1:1;
	u16 LeftOutVol:3;
	u16 dummy2:1;
	u16 Sound1Lf:1;
	u16 Sound2Lf:1;
	u16 Sound3Lf:1;
	u16 Sound4Lf:1;
	u16 Sound1Rf:1;
	u16 Sound2Rf:1;
	u16 Sound3Rf:1;
	u16 Sound4Rf:1;
}GsSoundCnt;



typedef struct GsBGAffine
{
	s32 bg_start_x ;
    s32 bg_start_y ;
    s16 bg_pa ;
    s16 bg_pb ;
    s16 bg_pc ;
    s16 bg_pd ;
    u8 bg_mosaic ;
    u16 bg_scale_x ;
    u16 bg_scale_y ;
    u16 bg_rotate ;
    s16 bg_pos_x ;
    s16 bg_pos_y ;
}GsBGAffine;

//GsLIB的精灵结构
typedef struct GsSPRITE
{
	u8 ID:7;					//在OAM中的编号
	u8 Flag:1;					//是否已经被画到屏幕上
//	s16 x;						//虚屏幕上的X坐标
//	s16 y;						//虚屏幕上的Y坐标
	SPRITE obj;
}GsSPRITE;


// 下面是MK4需要的声音定义
//Waveform Data Structure

typedef struct {
    u16 type;   //Type
    u16 stat;   //Status
    u32 freq;   //Frequency Calculation Value
    u32 loop;   //Loop Start Point
    u32 size;   //Sampling Number
    s8 data[1]; //Sampling Data Order
} WaveData;

#define WAVE_STAT_LOOP  0xc000


//Sound Quality Data Structure
typedef struct {
    u8 typ;         //Type
    u8 key;         //Original Key
    u8 len;         //Sound Length (Compatible Sound)
    u8 p_s;         //Pan or Sweep (Compatible Sound 1)
    WaveData *wav;  //Wave Data Address
    u8 att;         //Attack
    u8 dec;         //Decay
    u8 sus;         //Sustain
    u8 rel;         //Release
} ToneData;

#define TONEDATA_TYP_RHY    0x80
#define TONEDATA_TYP_SPL    0x40
#define TONEDATA_TYP_FIX    0x08
#define TONEDATA_TYP_CGB    0x07

#define TONEDATA_P_S_PAN    0xc0
#define TONEDATA_P_S_PAM    TONEDATA_P_S_PAN

typedef struct { u32 typ; ToneData *ta; u8 *st; } SplitTone;
typedef union { ToneData t; SplitTone s; } ToneDataArr;

#define RHYTHM_TONE(TA)     {TONEDATA_TYP_RHY,0,0,0,(WaveData *)(TA)}
#define SPLIT_TONE(TA,ST)   (ToneDataArr)(SplitTone)\
                {TONEDATA_TYP_SPL, (ToneData *)(TA), (u8 *)(ST)}
#define RHY_SPL_TONE(TA,ST) (ToneDataArr)(SplitTone)\
                {TONEDATA_TYP_RHY|TONEDATA_TYP_SPL, (ToneData *)(TA), (u8 *)(ST)}


//Virtual Channel Structure
typedef struct {
    u8 sf;          //Status
    u8 ty;          //Type
    u8 rv;          //Right Volume
    u8 lv;          //Left Volume
    u8 at;          //Attack
    u8 de;          //Decay
    u8 su;          //Sustain
    u8 re;          //Release
    u8 r1[24];      // (reserved)
    u32 fr;         //Frequency Calculation Value
    WaveData *wp;   //Wave Pointer
    u32 r3[6];      // (reserved)
} SoundChannel;

#define MAX_DIRECTSOUND_CHANNEL 12
#define SOUND_CHANNEL_SF_START  0x80
#define SOUND_CHANNEL_SF_STOP   0x40
#define SOUND_CHANNEL_SF_LOOP   0x10
#define SOUND_CHANNEL_SF_IEC    0x04
#define SOUND_CHANNEL_SF_ENV    0x03
#define SOUND_CHANNEL_SF_ON     (SOUND_CHANNEL_SF_START|SOUND_CHANNEL_SF_STOP\
                                |SOUND_CHANNEL_SF_IEC|SOUND_CHANNEL_SF_ENV)

#define SOUND_CHANNEL_TY_FIX    TONEDATA_TYP_FIX
#define SOUND_CHANNEL_TY_CGB    TONEDATA_TYP_CGB


//Size of Direct Sound Transmission Buffer
#define PCM_DMA_BUF 1584


//Sound Work Area Structure
typedef struct {
    u32 r1;     // (reserved)
    vu8 DmaCount;
    u8 reverb;  //Direct Sound  Reverb Value
    u8 maxchn;  //Direct Sound  Simultaneous Sound Number
    u8 masvol;  //Direct Sound  Master Volume
    u8 freq;    //Direct Sound  Replay Frequency Number(1=5734Hz ~ 12=42048Hz)
    u8 mode;    //Sound Driver  Operation Mode
    u8 r2[6];   // (reserved)
    u32 r3[16]; // (reserved)
    SoundChannel vchn[MAX_DIRECTSOUND_CHANNEL];
    #ifndef ONLY_DMA1_SOUND
    s8 pcmbuf[PCM_DMA_BUF*2];
#else
    s8 pcmbuf[PCM_DMA_BUF];
#endif
} SoundArea;

#define SOUND_MODE_REVERB_VAL   0x0000007f
#define SOUND_MODE_REVERB_SET   0x00000080
#define SOUND_MODE_MAXCHN       0x00000f00
#define SOUND_MODE_MAXCHN_SHIFT 8
#define SOUND_MODE_MASVOL       0x0000f000
#define SOUND_MODE_MASVOL_SHIFT 12
#define SOUND_MODE_FREQ_05734   0x00010000
#define SOUND_MODE_FREQ_07884   0x00020000
#define SOUND_MODE_FREQ_10512   0x00030000
#define SOUND_MODE_FREQ_13379   0x00040000
#define SOUND_MODE_FREQ_15768   0x00050000
#define SOUND_MODE_FREQ_18157   0x00060000
#define SOUND_MODE_FREQ_21024   0x00070000
#define SOUND_MODE_FREQ_26758   0x00080000
#define SOUND_MODE_FREQ_31536   0x00090000
#define SOUND_MODE_FREQ_36314   0x000a0000
#define SOUND_MODE_FREQ_40137   0x000b0000
#define SOUND_MODE_FREQ_42048   0x000c0000
#define SOUND_MODE_FREQ_SHIFT   16
#define SOUND_MODE_DA_BIT_9     0x00800000
#define SOUND_MODE_DA_BIT_8     0x00900000
#define SOUND_MODE_DA_BIT_7     0x00a00000
#define SOUND_MODE_DA_BIT_6     0x00b00000
#define SOUND_MODE_DA_BIT_SHIFT 20


//Song Data Structure
typedef struct {
    u8 trks;            //Track Number
    u8 blks;            //Block Number
    u8 prio;            //Priority
    u8 rvrb;            //Reverb
    ToneData *tone;     //Tone Table
    u8 *part[1];
} SongHeader;


//Music Player Work Area Structure
typedef struct {
    SongHeader *song;   //Current Song Pointer
    u32 stat;           //Status
    u8 mtrk;            //Track Number
    u8 prio;            //Current Priority
    u8 d1[2];
    u32 clock;          //Calculation Clock from Performance Start
    u8 d2[48];
} MusicPlayerArea;

//Each Track Structure of Music Player
typedef struct {
    u8 d[80];
} MusicPlayerTrack;

#define MAX_MUSICPLAYER_TRACK       16
#define MUSICPLAYER_STATUS_TRACK    0x0000ffff
#define MUSICPLAYER_STATUS_PAUSE    0x80000000


#endif 
