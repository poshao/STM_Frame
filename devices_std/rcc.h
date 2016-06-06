#ifndef S__RCC__
#define S__RCC__
#include "stm32f10x.h"

#define SYSCLK_DIV1 RCC_SYSCLK_Div1
#define SYSCLK_DIV2 RCC_SYSCLK_Div2
#define SYSCLK_DIV4 RCC_SYSCLK_Div4
#define SYSCLK_DIV8 RCC_SYSCLK_Div8
#define SYSCLK_DIV16 RCC_SYSCLK_Div16
#define SYSCLK_DIV64 RCC_SYSCLK_Div64
#define SYSCLK_DIV128 RCC_SYSCLK_Div128
#define SYSCLK_DIV256 RCC_SYSCLK_Div256
#define SYSCLK_DIV512 RCC_SYSCLK_Div512

#define AHBCLK_DIV1 RCC_HCLK_Div1
#define AHBCLK_DIV2 RCC_HCLK_Div2
#define AHBCLK_DIV4 RCC_HCLK_Div4
#define AHBCLK_DIV8 RCC_HCLK_Div8
#define AHBCLK_DIV16 RCC_HCLK_Div16

#define PLLSRC_HSEv1 RCC_PLLSource_HSE_Div1
#define PLLSRC_HSEv2 RCC_PLLSource_HSE_Div2
#define PLLSRC_HSIv2 RCC_PLLSource_HSI_Div2

#define RDY_HSI RCC_FLAG_HSIRDY
#define RDY_HSE RCC_FLAG_HSERDY
#define RDY_PLL RCC_FLAG_PLLRDY
#define RDY_LSE RCC_FLAG_LSERDY
#define RDY_LSI RCC_FLAG_LSIRDY

class xRCC{
public:
  //xRCC(void);

  void Reset(void);

  void HSE_ON(void);
  void HSE_OFF(void);
  void HSE_Bypass(void);
  //ErrorStatus WaitForHSEStartUp(void);
  void LSE_ON(void);
  void LSE_OFF(void);
  void LSE_Bypass(void);
  
  void HSI_ON(void);
  void HSI_OFF(void);
  void LSI_ON(void);
  void LSI_OFF(void);
  
  void HSEasSysClock(void);
  void HSIasSysClock(void);
  void PLLasSysClock(void);
  uint8_t GetSysClock(void);
  
  void AHBDiv(uint32_t SYSCLK_DIVx);
  void APB1Div(uint32_t AHBCLK_DIVx);
  void APB2Div(uint32_t AHBCLK_DIVx);
  
  void PLLConfig(uint32_t PLLSRC_XXX,uint8_t mul);
  void PLL_ON(void);
  void PLL_OFF(void);
  
  ErrorStatus WaitForReady(uint32_t RDY_XXX);
  
  void AHBPeriph_ON(uint32_t RCC_AHBPeriph_XXX);
  void AHBPeriph_OFF(uint32_t RCC_AHBPeriph_XXX);
  void APB1Periph_ON(uint32_t RCC_APB1Periph_XXX);
  void APB1Periph_OFF(uint32_t RCC_APB1Periph_XXX);
  void APB2Periph_ON(uint32_t RCC_APB2Periph_XXX);
  void APB2Periph_OFF(uint32_t RCC_APB2Periph_XXX);
  
  static void Setup(void);
  
  void Simple72Mhz(void);
};


#endif
