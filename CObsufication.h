#pragma once

#define SIMPLE_OBF_H_VERSION		003

/******************************************************************************\
**                                                                            **
**                              Expansion macros                              **
**                      not recommended for direct usage                      **
**                                                                            **
\******************************************************************************/

#define PASTE(x,y)	x##y

#define OBFUSCATENOPS3(x,obf_start_nops,obf_end_nops) \
obf_start_nops: \
	x \
	__asm { \
	__asm push obf_end_nops \
	__asm push obf_start_nops \
	__asm call _AddNops \
} \
obf_end_nops: 

#define DEL_START3(del_start_lbl) \
del_start_lbl:

#define DEL_END3(del_start_lbl,del_end_lbl) \
	__asm { \
	__asm push del_end_lbl \
	__asm push del_start_lbl \
	__asm call _AddNops \
} \
del_end_lbl: 


#define OBFUSCATENOPS2(x,y)	OBFUSCATENOPS3(x,PASTE(obf_start_nops_,y),PASTE(obf_end_nops_,y))

#define DEL_START2(x,y)	DEL_START3(PASTE2(del_start_lbl_,x,y))
#define DEL_END2(x,y)	DEL_END3(PASTE2(del_start_lbl_,x,y),PASTE2(del_end_lbl_,x,y))



/******************************************************************************\
**                                                                            **
**                    Macros / functions for direct usage                     **
**                                                                            **
\******************************************************************************/

//use these nops with the macro OBFUSCATENOPS, or manually insert __asm nop
#define Nop_5	__asm nop __asm nop __asm nop __asm nop __asm nop
#define Nop_10	Nop_5 Nop_5
#define Nop_20	Nop_10 Nop_10

#define AddRandomNops( x )				OBFUSCATENOPS2(x,__LINE__)

//everything between the _START and _ENDE macro will only be executed once, after that
//it is overwritten with random nops.
//use both arguments to create a unique identifier, this is very important!
#define RunOnce_Start( x )				DEL_START3(PASTE(del_start_lbl_,x))
#define RunOnce_End( x )				DEL_END3(PASTE(del_start_lbl_,x),PASTE(del_end_lbl_,x))

void __stdcall _AddNops( PBYTE start, PBYTE end );
PBYTE __stdcall AllocateJumpgate( PBYTE target, int minlen, int maxlen );
void __stdcall FreeJumpgate( PBYTE target );