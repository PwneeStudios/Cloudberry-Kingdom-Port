#ifndef __GFX_PAD_H_
#define __GFX_PAD_H_

void gfxInitPad(void);
void gfxPadRead(void);
void gfxPadEnd(void);

bool gfxPadConnected(int pad);
bool gfxStartDown(int pad);
bool gfxSelectDown(int pad);
bool gfxL1Down(int pad);
bool gfxL2Down(int pad);
bool gfxL3Down(int pad);
bool gfxR1Down(int pad);
bool gfxR2Down(int pad);
bool gfxR3Down(int pad);

bool gfxDpadLeft(int pad);
bool gfxDpadRight(int pad);
bool gfxDpadUp(int pad);
bool gfxDpadDown(int pad);

bool gfxDpadTri(int pad);
bool gfxDpadCross(int pad);
bool gfxDpadSquare(int pad);
bool gfxDpadCircle(int pad);

float gfxL2Pressure(int pad);
float gfxR2Pressure(int pad);

void gfxLeftStick(int pad, float &x, float &y);
void gfxRightStick(int pad, float &x, float &y);

#endif
