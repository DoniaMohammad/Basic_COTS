#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendCommand (uint8 copy_u8Command);
void CLCD_voidSendData (uint8 copy_u8data);
void CLCD_voidInit (void);

void CLCD_voidSendString(uint8* copy_u8string);
void CLCD_voidSendNumber(sint32 copy_s32number);

void CLCD_voidGoToXY(uint8 copy_u8XPos, uint8 copy_u8YPos);
uint8 CLCD_u8WriteSpecialCharacter(uint8 copy_PatternNumber, uint8 copy_pu8PatternArray[], uint8 copy_u8XPos, uint8 copy_u8YPos);;

#endif
