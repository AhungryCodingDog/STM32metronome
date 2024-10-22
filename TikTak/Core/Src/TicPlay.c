//
// Created by jingl on 2023/12/14.
//
#include "TicPlay.h"

uint16_t Nc = 4 , Nd = 4;
uint16_t BPM = 90;

uint16_t SettingBuff[5] = {4,4,90,0,0};

uint8_t Setting_FixIndex=0;
uint8_t FixFlag = 0;
struct Tick_Key{
    uint16_t KeyFreqTime;
    uint16_t KeyConTime;
    uint16_t ResTime;
};
struct Tick_Key Key[] = {{1276}, {1517},{2273}};

struct Tick_Key   PlayQueue[16];
uint8_t PlayQueueMode[16] = {0,2,2,2,2,2,2,
                             2,2,2,2,2,2,2,2,2};
uint8_t FixPlayQueueMode_Index = 0;
const char Str_pitch[] = {'H','M','L'};

static uint16_t Tick_Counter;
static uint8_t Play_Index;

void TIM_Tick_On(void);
void TIM_Tick_Res(void);
void Tick_LED_Clear();
void Tick_LED(uint8_t p);
void Tick_Init()
{
    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);

    for(uint8_t i=0;i<3;i++)
    {
        Key[i].ResTime = 60 * 1000000/(BPM*Key[i].KeyFreqTime) ;
//        Key[i].KeyConTime = Key[i].ResTime/3;
        Key[i].KeyConTime = 80000/Key[i].KeyFreqTime;

    }

    PlayQueue[0] = Key[0];
    PlayQueue[1] = Key[2];
    PlayQueue[2] = Key[2];
    PlayQueue[3] = Key[2];
}

void setTick(uint8_t newNc,uint8_t newNd,uint16_t newBPM)
{
    Nc = newNc;Nd = newNd; BPM = newBPM;

    for(uint8_t i=0;i<3;i++)
    {
        Key[i].ResTime = 60 * 1000000/(BPM*Key[i].KeyFreqTime) ;
//        Key[i].KeyConTime = Key[i].ResTime/3;
        Key[i].KeyConTime = 100000/Key[i].KeyFreqTime;

    }

    for(uint8_t i=0;i<Nc;i++)
    {
        PlayQueue[i] = Key[PlayQueueMode[i]];

    }

    FixFlag = 1;
}


void Tick_Play()
{

    if(FixFlag == 1)
    {
        Tick_Counter = 0;
        Play_Index = 0;
        FixFlag = 0;
    }

    Tick_Counter++;


    if(Tick_Counter <= PlayQueue[Play_Index].KeyConTime)
    {
        if(Practice_TIM_Res_Flag)
        {
            TIM_Tick_Res();
        }
        else
        {
            TIM_Tick_On();
        }
        Tick_LED(Play_Index%4);
        
    }
    else if(Tick_Counter <= PlayQueue[Play_Index].ResTime)
    {

        TIM_Tick_Res();
        Tick_LED_Clear();

    }
    else
    {
        Tick_Counter = 0;
        Play_Index++;
        Play_Index%=Nc;

        OLED_ShowNum(2,12,Play_Index+1,1);
//        OLED_ShowChar(2,16,Str_pitch[PlayQueueMode[Play_Index]]);
    }

}

void TIM_Tick_On(void)
{
    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,PlayQueue[Play_Index].KeyFreqTime/2);
    __HAL_TIM_SET_AUTORELOAD(&htim2,PlayQueue[Play_Index].KeyFreqTime);
//    HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_2);
}

void TIM_Tick_Res(void)
{
    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);
    __HAL_TIM_SET_AUTORELOAD(&htim2,PlayQueue[Play_Index].KeyFreqTime);
//    HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_2);
}

void Tick_LED(uint8_t p)
{
    switch (p) {
        case 0:
            HAL_GPIO_WritePin(TickLED_0_GPIO_Port,TickLED_0_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(TickLED_1_GPIO_Port,TickLED_1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(TickLED_2_GPIO_Port,TickLED_2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(TickLED_3_GPIO_Port,TickLED_3_Pin,GPIO_PIN_RESET);

            break;
        case 1:
            HAL_GPIO_WritePin(TickLED_0_GPIO_Port,TickLED_0_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(TickLED_1_GPIO_Port,TickLED_1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(TickLED_2_GPIO_Port,TickLED_2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(TickLED_3_GPIO_Port,TickLED_3_Pin,GPIO_PIN_RESET);

            break;
        case 2:
            HAL_GPIO_WritePin(TickLED_0_GPIO_Port,TickLED_0_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(TickLED_1_GPIO_Port,TickLED_1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(TickLED_2_GPIO_Port,TickLED_2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(TickLED_3_GPIO_Port,TickLED_3_Pin,GPIO_PIN_RESET);

            break;
        case 3:
            HAL_GPIO_WritePin(TickLED_0_GPIO_Port,TickLED_0_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(TickLED_1_GPIO_Port,TickLED_1_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(TickLED_2_GPIO_Port,TickLED_2_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(TickLED_3_GPIO_Port,TickLED_3_Pin,GPIO_PIN_SET);

            break;

    }
}
void Tick_LED_Clear()
{
    HAL_GPIO_WritePin(TickLED_0_GPIO_Port,TickLED_0_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TickLED_1_GPIO_Port,TickLED_1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TickLED_2_GPIO_Port,TickLED_2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TickLED_3_GPIO_Port,TickLED_3_Pin,GPIO_PIN_RESET);

}