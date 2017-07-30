#ifndef _GsMODPLAYER
#define _GsMODPLAYER

#define MAX_CHANNELS	4
#define BUFFERS		2
#define BUFFER_SIZE	1344

extern void GsInitMOD(void);				//≥ı ºªØMOD
extern void GsModPlay(u32 pt_modaddress);
extern void GsModSetVol(u8 mastervol,u8 soundchan);
extern void GsModStop(void);
#endif
