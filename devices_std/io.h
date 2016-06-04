#ifndef S__IO__
#define S__IO__
#include "stm32f10x.h"

//端口简写
#define PA  GPIOA
#define PB  GPIOB
#define PC  GPIOC
#define PD  GPIOD
#define PE  GPIOE
#define PF  GPIOF
#define PG  GPIOG

//针脚号简写
#define PIN_0   GPIO_Pin_0
#define PIN_1   GPIO_Pin_1
#define PIN_2   GPIO_Pin_2
#define PIN_3   GPIO_Pin_3
#define PIN_4   GPIO_Pin_4
#define PIN_5   GPIO_Pin_5
#define PIN_6   GPIO_Pin_6
#define PIN_7   GPIO_Pin_7
#define PIN_8   GPIO_Pin_8
#define PIN_9   GPIO_Pin_9
#define PIN_10  GPIO_Pin_10
#define PIN_11  GPIO_Pin_11
#define PIN_12  GPIO_Pin_12
#define PIN_13  GPIO_Pin_13
#define PIN_14  GPIO_Pin_14
#define PIN_15  GPIO_Pin_15

//工作模式简写
#define M_AIN    0x0
#define M_IN_F   0x04
#define M_IPD    0x28
#define M_IPU    0x48
#define M_OD     0x14
#define M_PP     0x10
#define M_OD_AF  0x1C
#define M_PP_AF  0x18

//翻转速度简写
#define S_50MHz   GPIO_Speed_50MHz
#define S_10MHz   GPIO_Speed_10MHz
#define S_2MHz    GPIO_Speed_2MHz

class xIO{
  public:
    //配置
    static void Config(GPIO_TypeDef *port,GPIO_InitTypeDef* type);
    static void Config(GPIO_TypeDef *port,uint16_t pin,GPIOMode_TypeDef mode,GPIOSpeed_TypeDef rate);
    static void ConfigPin(GPIO_TypeDef *port,uint8_t index,GPIOMode_TypeDef mode,GPIOSpeed_TypeDef rate);

    //读操作
    static bool ReadBitIndex(GPIO_TypeDef *port,uint8_t index);
    static bool ReadBit(GPIO_TypeDef *port,uint16_t pin);
    static bool ReadOutBitIndex(GPIO_TypeDef *port,uint8_t index);
    static bool ReadOutBit(GPIO_TypeDef *port,uint16_t pin);

    static uint16_t Read(GPIO_TypeDef *port);
    static uint16_t ReadOut(GPIO_TypeDef *port);
    
    //写操作
    static void WriteBitIndex(GPIO_TypeDef *port,uint8_t index,bool value=true);
    static void WriteBit(GPIO_TypeDef *port,uint16_t pin,bool value=true);
    static void Write(GPIO_TypeDef *port,uint16_t value);
  
    static void SetBits(GPIO_TypeDef *port,uint16_t pin);
    static void ResetBits(GPIO_TypeDef *port,uint16_t pin);
    
    //未完成
    static void DeInit(GPIO_TypeDef *port);
    static void AFIODeInit(void);
    static void ETH_MediaInterfaceConfig(uint32_t interface);
    static void EventOutputConfig(uint8_t portSource,uint8_t pinSource);
    static void EventOutputCmd(FunctionalState state);
    static void EXTIConfig(uint8_t portSource,uint8_t pinSource);
    static void PinLockConfig(GPIO_TypeDef *port,uint16_t pin);
    static void PinRemapConfig(uint32_t remap,FunctionalState state);
};

#endif
