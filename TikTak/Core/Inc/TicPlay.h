//
// Created by jingl on 2023/12/14.
//

#ifndef TIKTAK_TICPLAY_H
#define TIKTAK_TICPLAY_H
#include "main.h"
void Tick_Init();
void Tick_Play();
void  setTick(uint8_t newNc,uint8_t newNd,uint16_t newBPM);
extern uint16_t Nc,Nd,SettingBuff[5];
extern uint16_t BPM;
extern  uint8_t PlayQueueMode[16];

extern uint8_t Setting_FixIndex;
extern uint8_t FixPlayQueueMode_Index;
extern const char Str_pitch[];
#endif //TIKTAK_TICPLAY_H
