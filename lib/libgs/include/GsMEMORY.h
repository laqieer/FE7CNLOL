#ifndef Gs_GBA_MEMORY_H
#define Gs_GBA_MEMORY_H


/*------------------------------------------------------------------*/
/*                      Memory Map                                  */
/*------------------------------------------------------------------*/

#define BOOT_ROM                0x00000000          // Boot ROM
#define BOOT_ROM_END            (BOOT_ROM + 0x4000)
#define EX_WRAM                 0x02000000          // CPU External Work RAM
#define EX_WRAM_END             (EX_WRAM + 0x40000)
#define CPU_WRAM                0x03000000          // CPU Internal Work RAM
#define CPU_WRAM_END            (CPU_WRAM + 0x8000)
#define WRAM                     EX_WRAM            // Entire Work RAM
#define WRAM_END                 CPU_WRAM_END
#define SOUND_AREA_ADDR_BUF     (CPU_WRAM_END - 0x10)//Sound Driver Work Address
#define INTR_CHECK_BUF          (CPU_WRAM_END - 0x8)// Interrupt Check
#define INTR_VECTOR_BUF         (CPU_WRAM_END - 0x4)// Interrupt Branch Address
#define OFFSET_REG_IE			0x200 
#define REG_BASE                0x04000000          // Registers
#define REG_END                 (REG_BASE +  0x300)
#define PLTT                    0x05000000          // Palette RAM
#define PLTT_END                (PLTT +      0x400)
#define BG_PLTT                 (PLTT +        0x0) // BG Palette RAM
#define BG_PLTT_END             (PLTT +      0x200)
#define OBJ_PLTT                (PLTT +      0x200) // OBJ Palette RAM
#define OBJ_PLTT_END            (PLTT +      0x400)
#define VRAM                    0x06000000          // VRAM
#define VRAM_END                (VRAM +    0x18000)
#define BG_VRAM                 (VRAM +        0x0) // BG Character/Screen RAM
#define BG_BITMAP0_VRAM         (VRAM +        0x0) // BG Bitmap 0 RAM
#define BG_BITMAP1_VRAM         (VRAM +     0xa000) // BG Bitmap 1 RAM
#define OBJ_MODE0_VRAM          (VRAM +    0x10000) // OBJ Character RAM
#define OBJ_MODE1_VRAM          (VRAM +    0x10000)
#define OBJ_MODE2_VRAM          (VRAM +    0x10000)
#define OBJ_MODE3_VRAM          (VRAM +    0x14000)
#define OBJ_MODE4_VRAM          (VRAM +    0x14000)
#define OBJ_MODE5_VRAM          (VRAM +    0x14000)
#define OBJ_VRAM_END            (VRAM +    0x18000)
#define OAM                     0x07000000          // OAM
#define OAM_END                 (OAM +       0x400)

#define ROM_BANK0               0x08000000          // ROM Bank 0
#define ROM_BANK0_END           0x0a000000
#define ROM_BANK1               0x0a000000          // ROM Bank 1
#define ROM_BANK1_END           0x0c000000
#define ROM_BANK2               0x0c000000          // ROM Bank 2
#define ROM_BANK2_END           0x0e000000
#define RAM_BANK                0x0c000000          // RAM Bank
#define RAM_BANK_END            0x10000000

#define FLASH_1M                0x09fe0000          // 1M Flash Memory
#define FLASH_1M_END            0x0a000000

/*------------------------------------------------------------------*/
/*                      Memory Size                                 */
/*------------------------------------------------------------------*/

#define BOOT_ROM_SIZE           0x4000              // Boot ROM
#define EX_WRAM_SIZE            0x40000             // CPU External Work RAM
#define CPU_WRAM_SIZE           0x8000              // CPU Internal Work RAM
#define WRAM_SIZE               0x48000             // Entire Work RAM
#define PLTT_SIZE               (2*256*2)           // Palette RAM
#define BG_PLTT_SIZE            (2*256)             // BG Palette RAM
#define OBJ_PLTT_SIZE           (2*256)             // OBJ Palette RAM
#define VRAM_SIZE               0x18000             // VRAM
#define BG_MODE0_VRAM_SIZE      0x10000             // BG Character/Screen
#define BG_MODE1_VRAM_SIZE      0x10000
#define BG_MODE2_VRAM_SIZE      0x10000
#define BG_MODE3_VRAM_SIZE      0x14000             // BG Bitmap
#define BG_MODE4_VRAM_SIZE      0x0a000
#define BG_MODE5_VRAM_SIZE      0x0a000
#define OBJ_MODE0_VRAM_SIZE     0x08000             // OBJ Character
#define OBJ_MODE1_VRAM_SIZE     0x08000
#define OBJ_MODE2_VRAM_SIZE     0x08000
#define OBJ_MODE3_VRAM_SIZE     0x04000
#define OBJ_MODE4_VRAM_SIZE     0x04000
#define OBJ_MODE5_VRAM_SIZE     0x04000
#define OAM_SIZE                (8*128)             // OAM

#define ROM_BANK_SIZE           0x02000000          // ROM Bank
#define ROM_BANK0_SIZE          0x02000000          // ROM Bank 0
#define ROM_BANK1_SIZE          0x02000000          // ROM Bank 1
#define ROM_BANK2_SIZE          0x02000000          // ROM Bank 2
#define RAM_BANK_SIZE           0x02000000          // RAM Bank

#define FLASH_1M_SIZE           0x20000             // 1M Flash Memory


//-----------------------------------------------------------//
//					Register Defines						 //
//-----------------------------------------------------------//		


#define REG_INTERUPT	 0x3007FFC		//Interrupt Register
#define REG_DISPCNT		 *(volatile u16* )0x4000000		//Display Control (Mode)
#define REG_STAT		 0x4000004		//Display Status
#define REG_VCOUNT		 0x4000006		//Vertical Control (Sync)
#define REG_WAITCNT      0x4000204		//wait cart
#define REG_BG0CNT		 0x4000008		//Background 0
#define REG_BG1CNT		 0x400000A		//Background 1
#define REG_BG2CNT		 0x400000C		//Background 2
#define REG_BG3CNT		 0x400000E		//Background 3

#define REG_BG0HOFS		 0x4000010		//Background 0 Offset	H
#define REG_BG0VOFS		 0x4000012		//Background 0 Offset	V
#define REG_BG1HOFS		 0x4000014		//Background 1 Offset	H
#define REG_BG1VOFS		 0x4000016		//Background 1 Offset	V
#define REG_BG2HOFS		 0x4000018		//Background 2 Offset	H
#define REG_BG2VOFS		 0x400001A		//Background 2 Offset	V
#define REG_BG3HOFS		 0x400001C		//Background 3 Offset	H
#define REG_BG3VOFS		 0x400001E		//Background 3 Offset	V


#define REG_BG2AFFINE	 0x4000020   // BG 2 Affin Transformation Parameters
#define REG_BG2PA        0x4000020   // BG 2 Line Direction X Coordinate Difference
#define REG_BG2PB        0x4000022   // BG 3 Vertical Direction X Coordinate Difference
#define REG_BG2PC        0x4000024   // BG 2 Line Direction Y coordinate Difference
#define REG_BG2PD        0x4000026   // BG 2 Vertical Direction Y Coordinate Difference
#define REG_BG2X         0x4000028   // BG 2 Start X Coordinate
#define REG_BG2X_L       0x4000028
#define REG_BG2X_H       0x400002a
#define REG_BG2Y         0x400002c   // BG 2 Start Y Coordinate
#define REG_BG2Y_L       0x400002c
#define REG_BG2Y_H       0x400002e
#define REG_BG3AFFINE    0x4000030   // BG 3 Affin Transformation Parameters
#define REG_BG3PA        0x4000030   // BG 3 Line Direction X Coordinate Difference
#define REG_BG3PB        0x4000032   // BG 3 Vertical Direction X Coordinate Difference
#define REG_BG3PC        0x4000034   // BG 3 Line Direction Y Coordinate Difference
#define REG_BG3PD        0x4000036   // BG 3 Vertical Direction Y Coordinate Difference
#define REG_BG3X         0x4000038   // BG 3 Start X Coordinate
#define REG_BG3X_L       0x4000038
#define REG_BG3X_H       0x400003a
#define REG_BG3Y         0x400003c   // BG 3 Start Y Coordinate
#define REG_BG3Y_L       0x400003c
#define REG_BG3Y_H       0x400003e


#define REG_WIN0H		 *(volatile u16          * )0x4000040		//Window 0 X coords (bits 0-7 right, bits 8-16 left)
#define REG_WIN1H		 *(volatile u16          * )0x4000042		//Window 1 X coords (bits 0-7 right, bits 8-16 left)
#define REG_WIN0V		 *(volatile u16          * )0x4000044		//Window 0 Y coords (bits 0-7 bottom, bits 8-16 top)
#define REG_WIN1V		 *(volatile u16          * )0x4000046		//Window 1 Y coords (bits 0-7 bottom, bits 8-16 top)

#define REG_WININ		 0x4000048		//Inside Window Settings
#define REG_WINOUT		 0x400004A		//Outside Window Settings

#define REG_MOSAIC		 0x400004C		//Mosaic Mode
#define REG_BLDCNT		 0x4000050		//Blend Mode

#define REG_BLDALPHA     0x4000052		// Semi-transparent Parameter
#define REG_BLDY         0x4000054		// Brightness Change Parameter

#define REG_SG10		 0x4000060		//Sound 10
#define REG_SG11		 0x4000064		//Sound 11
#define REG_SG20		 0x4000068		//Sound 20
#define REG_SG21		 0x400006C		//Sound 21
#define REG_SG30		 0x4000070		//Sound 30
#define REG_SG31		 0x4000074		//Sound 31
#define REG_SG40		 0x4000078		//Sound 40
#define REG_SG41		 0x400007C		//Sound 41

#define REG_SGCNT		 0x4000080		//Sound Control 0,1 & bias
#define REG_SGCNT0		 0x4000080		//Sound Control 0
#define REG_SGCNT0_L	 0x4000080		//Sound Control 0 Lo Word
#define REG_SGCNT0_H	 0x4000082		//Sound Control 0 Hi Word
#define REG_SGCNT1		 0x4000084		//Sound Control 1

#define REG_SOUNDCNT    (REG_BASE + 0x80)   // Sound Control
#define REG_SOUNDCNT_L  (REG_BASE + 0x80)
#define REG_SOUNDCNT_H  (REG_BASE + 0x82)
#define REG_SOUNDCNT_X  (REG_BASE + 0x84)

#define REG_SGWR0		 0x4000090		
#define REG_SGWR0_L		 0x4000090		
#define REG_SGWR0_H		 0x4000092		
#define REG_SGWR1		 0x4000094		
#define REG_SGWR1_L		 0x4000094		
#define REG_SGWR1_H		 0x4000096		
#define REG_SGWR2		 0x4000098	
#define REG_SGWR2_L		 0x4000098	
#define REG_SGWR2_H		 0x400009A	
#define REG_SGWR3		 0x400009C		
#define REG_SGWR3_L		 0x400009C		
#define REG_SGWR3_H		 0x400009E	
#define REG_SGFIF0A		 0x40000A0		//DirectSound A FIFO
#define REG_SGFIFOA_L	 0x40000A0		//DirectSound A FIFO Lo Word
#define REG_SGFIFOA_H	 0x40000A2		//DirectSound A FIFO Hi Word
#define REG_SGFIFOB		 0x40000A4		//DirectSound B FIFO
#define REG_SGFIFOB_L	 0x40000A4		//DirectSound B FIFO Lo Word
#define REG_SGFIFOB_H	 0x40000A6		//DirectSound B FIFO Hi Word

#define REG_FIFO        (REG_BASE + 0xa0)   // Sound FIFO
#define REG_FIFO_A      (REG_BASE + 0xa0)
#define REG_FIFO_A_L    (REG_BASE + 0xa0)
#define REG_FIFO_A_H    (REG_BASE + 0xa2)
#define REG_FIFO_B      (REG_BASE + 0xa4)
#define REG_FIFO_B_L    (REG_BASE + 0xa4)
#define REG_FIFO_B_H    (REG_BASE + 0xa6)

#define REG_DMA0		0x40000B0								// DMA 0
#define REG_DMA0SAD		 *(volatile u32		   * )0x40000B0		//DMA0 Source Address
#define REG_DMA0DAD		 *(volatile u32		   * )0x40000B4		//DMA0 Destination Address
#define REG_DMA0CNT		0x40000B8		//DMA0 Control (Amount)
#define REG_DMA1        0x40000BC								// DMA 1
#define REG_DMA1SAD		 *(volatile u32		   * )0x40000BC		//DMA1 Source Address
#define REG_DMA1DAD		 *(volatile u32		   * )0x40000C0		//DMA1 Desination Address
#define REG_DMA1CNT		0x40000C4		//DMA1 Control (Amount)
#define REG_DMA2        0x40000C8								// DMA 2
#define REG_DMA2SAD		 *(volatile u32		   * )0x40000C8		//DMA2 Source Address
#define REG_DMA2DAD		 *(volatile u32		   * )0x40000CC		//DMA2 Destination Address
#define REG_DMA2CNT		0x40000D0		//DMA2 Control (Amount)
#define REG_DMA3        0x40000D4								// DMA 3
#define REG_DMA3SAD		 *(volatile u32		   * )0x40000D4		//DMA3 Source Address
#define REG_DMA3DAD		 *(volatile u32		   * )0x40000D8		//DMA3 Destination Address
#define REG_DMA3CNT		0x40000DC		//DMA3 Control (Amount)

#define REG_TM0DC		 0x4000100		//Timer 1 Data & Control
#define REG_TM1DC		 0x4000104		//Timer 2 Data & Control
#define REG_TM2DC		 0x4000108		//Timer 3 Data & Control
#define REG_TM3DC		 0x400010C		//Timer 4 Data & Control

#define REG_SCD0		 0x4000120		//32-bit Normal Serial Communication Data 0 / Multi-play
#define REG_SCD1		 0x4000122		//32-bit Normal Serial Communication Data 1 /Multi-play
#define REG_SCD2		 0x4000124		//Multi-play Communication Data 2
#define REG_SCD3		 0x4000126		//Multi-play Communication Data 3
#define REG_SCCNT		 0x4000128		//???
#define REG_SCCNT_L		 0x4000128		//???
#define REG_SCCNT_H		 0x400012A		//???

#define REG_P1			 *(volatile s_KeyData	* )0x4000130		//Player 1 Input
#define REG_P1CNT		 *(volatile s_KeyCnt    * )0x4000132		//Player 1 Input Interrupt Status
#define REG_KEYINPUT     0x4000130		// Key Input
#define REG_KEYCNT       0x4000132		// Key Control

#define REG_R			 0x4000134		//???
#define REG_HS_CTRL		 0x4000140		//???
#define REG_JOYRE		 0x4000150		//???
#define REG_JOYRE_L		 0x4000150		//???
#define REG_JOYRE_H		 0x4000152		//???
#define REG_JOYTR		 0x4000154		//???
#define REG_JOYTR_L		 0x4000154		//???
#define REG_JOYTR_H		 0x4000156		//???
#define REG_JSTAT		 0x4000158		//???
#define REG_JSTAT_L		 0x4000158		//???
#define REG_JSTAT_H		 0x400015A		//???


#define REG_IE			 0x4000200		//Master Interrupt Enable
#define REG_IF			 0x4000202		//Interrupt Flags
#define REG_WSCNT		 0x4000204		//???
#define REG_IME			 0x4000208		//Interrupt Master Enable
#define REG_PAUSE		 0x4000300		//Pause


#define OAM_ADDR		 *(volatile s_OamData	   * )0x07000000
//-------------------------------------------------------------

#define BGPaletteMem 	((u16*)0x5000000)
#define OBJPaletteMem 	((u16*)0x5000200)
#define FrontBuffer		0x6000000
#define BackBuffer		0x600A000



#endif

