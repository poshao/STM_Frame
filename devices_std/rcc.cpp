#include "rcc.h"

xRCC::xRCC(){
  RCC_DeInit();
}

void xRCC::HSE_Config(uint32_t HSE){
  RCC_HSEConfig(HSE);
}

//配置72MHz运行频率
void xRCC::Setup(){
  RCC_DeInit();
  //外部高速晶振启动
  RCC_HSEConfig(RCC_HSE_ON);
  while(ERROR==RCC_WaitForHSEStartUp());
  
  //AHB一分频
  RCC_HCLKConfig(RCC_SYSCLK_Div1);
  
  //APB2时钟
  RCC_PCLK2Config(RCC_HCLK_Div1);
  //APB1时钟
  RCC_PCLK1Config(RCC_HCLK_Div2);
  
  //PLL时钟
  RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);//8MHz*9
  RCC_PLLCmd(ENABLE);
  while(RESET==RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
  
  //系统时钟
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while(0x08!=RCC_GetSYSCLKSource());
}
