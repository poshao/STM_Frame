#ifndef S__RCC__
#define S__RCC__
#include "stm32f10x.h"

class xRCC{
public:
  xRCC();

  static void HSE_Config(uint32_t HSE);
  static void Setup(void);

};


#endif
