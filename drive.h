#ifndef __DRIVE_H__
#define __DRIVE_H___

#ifdef __cplusplus 
extern "C" {
#endif

char* dummy();
void drive_foward(int position,AccelStepper mot);
void DEBUG_CHECK(int IR1, int IR2, int posTogo);
#ifdef __cplusplus 
}

#endif

#endif
