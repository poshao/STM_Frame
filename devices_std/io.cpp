#include "io.h"

/**配置IO
 *参数：
 *  port：端口  可以是PA PB PC PD PE PF PG
 *  type：配置参数 包含模式，针脚，速率
 *返回值：
 *  空
 */
void xIO::Config(GPIO_TypeDef* port,GPIO_InitTypeDef* type){
  //参数检查
  assert_param(IS_GPIO_ALL_PERIPH(port));
  assert_param(IS_GPIO_MODE(type->GPIO_Mode));
  assert_param(IS_GPIO_PIN(type->GPIO_Pin));
  assert_param(IS_GPIO_SPEED(type->GPIO_Speed));
  
  GPIO_Init(port,type);
}

/**配置IO
 *参数：
 *  port：端口  可以是PA PB PC PD PE PF PG
 *  pin:针脚号  可以是PIN_0,PIN_1,PIN_2,...PIN_15
 *  mode：工作模式  可以为以下值
 *    M_AIN   模拟输入      M_OD    开漏输出
 *    M_IN_F  浮空输入      M_PP    推挽输出
 *    M_IPD   下拉输入      M_OD_AF 开漏输出（复用）
 *    M_IPU   上拉输入      M_PP_AF 推挽输出（复用）
 *  rate：翻转速率  可以为S_50MHz   S_10MHz   S_2MHz
 *返回值：
 *  空
*/
void xIO::Config(GPIO_TypeDef* port,uint16_t pin,GPIOMode_TypeDef mode,GPIOSpeed_TypeDef rate){
  GPIO_InitTypeDef GPIO_InitStruct;
  
  //参数检查
  assert_param(IS_GPIO_ALL_PERIPH(port));
  assert_param(IS_GPIO_MODE(mode));
  assert_param(IS_GPIO_PIN(pin));
  assert_param(IS_GPIO_SPEED(rate));
  
  GPIO_InitStruct.GPIO_Mode = mode;
  GPIO_InitStruct.GPIO_Pin = pin;
  GPIO_InitStruct.GPIO_Speed = rate;
  GPIO_Init(port,&GPIO_InitStruct);
}

/**配置单个针脚
 *参数：
 *  port：端口
 *  index：针脚序号
 *  mode：工作模式
 *  rate：翻转速率
 *返回值：
 *  空
 */
void xIO::ConfigPin(GPIO_TypeDef *port,uint8_t index,GPIOMode_TypeDef mode,GPIOSpeed_TypeDef rate){
  GPIO_InitTypeDef GPIO_InitStruct;
  uint16_t pin = 1<<index;
  
  //参数检查
  assert_param(IS_GPIO_ALL_PERIPH(port));
  assert_param(IS_GPIO_MODE(mode));
  assert_param(IS_GPIO_PIN(pin));
  assert_param(IS_GPIO_SPEED(rate));
  
  GPIO_InitStruct.GPIO_Mode = mode;
  GPIO_InitStruct.GPIO_Pin = pin;
  GPIO_InitStruct.GPIO_Speed = rate;
  GPIO_Init(port,&GPIO_InitStruct);
}

/**读取针脚电平(输入模式)
 *参数：
 *  port：端口
 *  index：针脚序号
 *返回值：
 *  true：高电平    false：低电平
*/
bool xIO::ReadBitIndex(GPIO_TypeDef *port,uint8_t index){
  uint16_t pin = 1<<index;
  
  //检查参数
  assert_param(IS_GPIO_ALL_PERIPH(port));
  assert_param(IS_GET_GPIO_PIN(pin)); 
  
  if((port->IDR & pin) != Bit_RESET){
    return true;
  }else{
    return false;
  }
}

/**读取针脚电平(输入模式)
 *参数：
 *  port：端口
 *  pin：针脚号  PIN_0,PIN_1,...PIN_15
 *返回值：
 *  true：高电平    false：低电平
*/
bool xIO::ReadBit(GPIO_TypeDef *port,uint16_t pin){
  //检查参数
  assert_param(IS_GPIO_ALL_PERIPH(port));
  assert_param(IS_GET_GPIO_PIN(pin));
  
  if((port->IDR & pin) != Bit_RESET){
    return true;
  }else{
    return false;
  }
}

/**读取针脚电平(输出模式)
 *参数：
 *  port：端口
 *  index：针脚序号
 *返回值：
 *  true：高电平    false：低电平
*/
bool xIO::ReadOutBitIndex(GPIO_TypeDef *port,uint8_t index){
  uint16_t pin = 1<<index;
  
  //检查参数
  assert_param(IS_GPIO_ALL_PERIPH(port));
  assert_param(IS_GET_GPIO_PIN(pin));
  
  if((port->ODR & pin) != Bit_RESET){
    return true;
  }else{
    return false;
  }
}

/**读取针脚电平(输出模式)
 *参数：
 *  port：端口
 *  pin：针脚号  PIN_0,PIN_1,...PIN_15
 *返回值：
 *  true：高电平    false：低电平
*/
bool xIO::ReadOutBit(GPIO_TypeDef *port,uint16_t pin){
  //检查参数
  assert_param(IS_GPIO_ALL_PERIPH(port));
  assert_param(IS_GET_GPIO_PIN(pin));
  
  if((port->ODR & pin) != Bit_RESET){
    return true;
  }else{
    return false;
  }
}

/**读取端口针脚电平(输入模式)
 *参数：
 *  port：端口
 *返回值：
 *  一组电平状态
 */
uint16_t xIO::Read(GPIO_TypeDef *port){
  //检查参数
  assert_param(IS_GPIO_ALL_PERIPH(port));
  
  return ((uint16_t)port->IDR);
}

/**读取端口针脚电平(输出模式)
 *参数：
 *  port：端口
 *返回值：
 *  一组电平状态
 */
uint16_t xIO::ReadOut(GPIO_TypeDef *port){
  //参数检查
  assert_param(IS_GPIO_ALL_PERIPH(port));
  return ((uint16_t)port->ODR);
}

/**设置针脚输出电平
 *参数：
 *  port：端口
 *  index：针脚序号
 *  value：电平状态值  true为高电平  false为低电平
 *返回值：
 *  空
 */
void xIO::WriteBitIndex(GPIO_TypeDef *port,uint8_t index,bool value){
  uint16_t pin=1<<index;
  
  //检查参数
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  //assert_param(IS_GPIO_BIT_ACTION(value));
  if (value != false){
    port->BSRR = pin;
  }else{
    port->BRR = pin;
  }
}

/**设置针脚输出电平
 *参数：
 *  port：端口
 *  pin：针脚号
 *  value：电平状态值  true为高电平  false为低电平
 *返回值：
 *  空
 */
void xIO::WriteBit(GPIO_TypeDef *port,uint16_t pin,bool value){
  //检查参数
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  //assert_param(IS_GPIO_BIT_ACTION(value));
  
  if (value != false){
    port->BSRR = pin;
  }else{
    port->BRR = pin;
  }
}

/**设置端口输出电平
 *参数：
 *  port：端口
 *  value：电平状态值
 *返回值：
 *  空
 */
void xIO::Write(GPIO_TypeDef *port,uint16_t value){
  //检查参数
  assert_param(IS_GPIO_ALL_PERIPH(port));
  
  port->ODR = value;
}

/**设置针脚高电平
 *参数：
 *  port：端口
 *  pin：针脚号
 *返回值：
 *  无
 */
void xIO::SetBits(GPIO_TypeDef *port,uint16_t pin){
  //检查参数
  assert_param(IS_GPIO_ALL_PERIPH(port));
  assert_param(IS_GPIO_PIN(pin));
  
  port->BSRR = pin;
}

/**设置针脚低电平
 *参数：
 *  port：端口
 *  pin：针脚号
 *返回值：
 *  无
 */
void xIO::ResetBits(GPIO_TypeDef *port,uint16_t pin){
  //检查参数
  assert_param(IS_GPIO_ALL_PERIPH(port));
  assert_param(IS_GPIO_PIN(pin));
  
  port->BRR = pin;
}

void xIO::DeInit(GPIO_TypeDef *port){
  GPIO_DeInit(port);
}
void xIO::AFIODeInit(void){
  GPIO_AFIODeInit();
}
void xIO::ETH_MediaInterfaceConfig(uint32_t interface){
  GPIO_ETH_MediaInterfaceConfig(interface);
}
void xIO::EventOutputConfig(uint8_t portSource,uint8_t pinSource){
  GPIO_EventOutputConfig(portSource,pinSource);
}
void xIO::EventOutputCmd(FunctionalState state){
  GPIO_EventOutputCmd(state);
}
void xIO::EXTIConfig(uint8_t portSource,uint8_t pinSource){
  GPIO_EXTILineConfig(portSource,pinSource);
}
void xIO::PinLockConfig(GPIO_TypeDef *port,uint16_t pin){
  GPIO_PinLockConfig(port,pin);
}
void xIO::PinRemapConfig(uint32_t remap,FunctionalState state){
  GPIO_PinRemapConfig(remap,state);
}
