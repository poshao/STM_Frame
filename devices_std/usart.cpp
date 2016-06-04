#include "usart.h"

/*默认使用串口1*/
Serial::Serial(){
  this->m_com=USART1;
}

Serial::Serial(USART_TypeDef *com){
  this->m_com=com;
}

/*配置IO*/
void Serial::IO(){
  
}
