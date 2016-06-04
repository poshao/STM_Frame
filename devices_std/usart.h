#ifndef S__USART__
#define S__USART__
#include "stm32f10x.h"

class Serial{
  private:
    USART_TypeDef *m_com;
  
  public:
    Serial();
    Serial(USART_TypeDef *com);
    ~Serial();
    
    //初始化
    void IO();
    void Init();
};


#endif
