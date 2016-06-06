#include "rcc.h"

/**重置RCC
  描述：重置RCC
  返回值：无
*/
void xRCC::Reset(){
  RCC_DeInit();
}

/**使能外部高速晶振
  描述：使能外部高速晶振
  返回值：无
*/
void xRCC::HSE_ON(){
  RCC_HSEConfig(RCC_HSE_ON);
}

/**关闭外部高速晶振
  描述：关闭外部高速晶振
  返回值：无
*/
void xRCC::HSE_OFF(){
  RCC_HSEConfig(RCC_HSE_OFF);
}

/**使用外置震荡源
  描述：使用外置震荡源
  返回值：无
*/
void xRCC::HSE_Bypass(){
  RCC_HSEConfig(RCC_HSE_Bypass);
}

/**使能外部低速晶振
  描述：使能外部低速晶振
  返回值：无
*/
void xRCC::LSE_ON(){
  RCC_LSEConfig(RCC_LSE_ON);
}

/**关闭外部低速晶振
  描述：关闭外部低速晶振
  返回值：无
*/
void xRCC::LSE_OFF(){
  RCC_LSEConfig(RCC_LSE_OFF);
}

/**使用外置震荡源
  描述：使用外置震荡源
  返回值：无
*/
void xRCC::LSE_Bypass(){
  RCC_LSEConfig(RCC_LSE_Bypass);
}

/**启动内部高速晶振
  描述：启动内部高速晶振
  返回值：无
*/
void xRCC::HSI_ON(){
  RCC_HSICmd(ENABLE);
}

/**关闭内部高速晶振
  描述：关闭内部高速晶振
  返回值：无
*/
void xRCC::HSI_OFF(){
  RCC_HSICmd(DISABLE);
}

/**启动内部低速晶振
  描述：启动内部低速晶振
  返回值：无
*/
void xRCC::LSI_ON(){
  RCC_LSICmd(ENABLE);
}

/**关闭内部低速晶振
  描述：关闭内部低速晶振
  返回值：无
*/
void xRCC::LSI_OFF(){
  RCC_LSICmd(DISABLE);
}

/**设置外部高速晶振作为系统时钟
  描述：设置外部高速晶振作为系统时钟
  返回值：无
*/
void xRCC::HSEasSysClock(){
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
}

/**设置内部高速晶振作为系统时钟
  描述：设置内部高速晶振作为系统时钟
  返回值：无
*/
void xRCC::HSIasSysClock(){
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
}

/**设置锁相环作为系统时钟
  描述：设置锁相环作为系统时钟
  返回值：无
*/
void xRCC::PLLasSysClock(){
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}

/**设置锁相环作为系统时钟
  描述：设置锁相环作为系统时钟
  返回值：当前系统振源
          0x00  HSI
          0x04  HSE
          0x08  PLL
*/
uint8_t xRCC::GetSysClock(void){
  return RCC_GetSYSCLKSource();
}
/**设置AHB总线时钟预分频
  描述：设置AHB总线时钟预分频
  返回值：无
*/
void xRCC::AHBDiv(uint32_t SYSCLK_DIVx){
  RCC_HCLKConfig(SYSCLK_DIVx);
}

/**设置APB1总线时钟预分频
  描述：设置APB1总线时钟预分频
  返回值：无
*/
void xRCC::APB1Div(uint32_t AHBCLK_DIVx){
  RCC_PCLK1Config(AHBCLK_DIVx);
}

/**设置APB2总线时钟预分频
  描述：设置APB2总线时钟预分频 不得超过36MHz
  返回值：无
*/
void xRCC::APB2Div(uint32_t AHBCLK_DIVx){
  RCC_PCLK2Config(AHBCLK_DIVx);
}

/**配置PLL
  描述：配置PLL
  参数：PLLSRC_XXX：锁相环振荡源  mul：倍频 取值范围2-16 且主频率不得高于72MHz
  返回值：无
*/
void xRCC::PLLConfig(uint32_t PLLSRC_XXX,uint8_t mul){
  RCC_PLLConfig(PLLSRC_XXX,((uint32_t)(mul-2)*4)<<16);
}

/**启动PLL振荡
  描述：启动PLL振荡
  返回值：无
*/
void xRCC::PLL_ON(){
  RCC_PLLCmd(ENABLE);
}

/**关闭PLL振荡
  描述：关闭PLL振荡
  返回值：无
*/
void xRCC::PLL_OFF(){
  RCC_PLLCmd(DISABLE);
}

/**等待振荡稳定
  描述：等待振荡稳定
  参数：RDY_XXX：等待稳定的振荡体名称
  返回值：振源稳定状态 SUCCESS：稳定  ERROR:不稳定
*/
ErrorStatus xRCC::WaitForReady(uint32_t RDY_XXX){
  __IO uint32_t StartUpCounter = 0;
  ErrorStatus status = ERROR;
  FlagStatus HSEStatus = RESET;
  
  /* Wait till HSE is ready and if Time out is reached exit */
  do{
    HSEStatus = RCC_GetFlagStatus(RDY_XXX);
    StartUpCounter++;  
  }while((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));
  
  if (RCC_GetFlagStatus(RDY_XXX) != RESET){
    status = SUCCESS;
  }else{
    status = ERROR;
  }
  return (status);
}

/**使能AHB总线外设时钟
  描述：使能AHB总线外设时钟
  参数：RCC_AHBPeriph_XXX：AHB外设
  返回值：无
*/
void xRCC::AHBPeriph_ON(uint32_t RCC_AHBPeriph_XXX){
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_XXX,ENABLE);
}

/**失能AHB总线外设时钟
  描述：失能AHB总线外设时钟
  参数：RCC_AHBPeriph_XXX：AHB外设
  返回值：无
*/
void xRCC::AHBPeriph_OFF(uint32_t RCC_AHBPeriph_XXX){
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_XXX,DISABLE);
}

/**使能APB1总线外设时钟
  描述：使能APB1总线外设时钟
  参数：RCC_APB1Periph_XXX：APB1外设
  返回值：无
*/
void xRCC::APB1Periph_ON(uint32_t RCC_APB1Periph_XXX){
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_XXX,ENABLE);
}

/**失能APB1总线外设时钟
  描述：失能APB1总线外设时钟
  参数：RCC_APB1Periph_XXX：APB1外设
  返回值：无
*/
void xRCC::APB1Periph_OFF(uint32_t RCC_APB1Periph_XXX){
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_XXX,DISABLE);
}

/**使能APB2总线外设时钟
  描述：使能APB2总线外设时钟
  参数：RCC_APB2Periph_XXX：APB2外设
  返回值：无
*/
void xRCC::APB2Periph_ON(uint32_t RCC_APB2Periph_XXX){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_XXX,ENABLE);
}

/**失能APB2总线外设时钟
  描述：失能APB2总线外设时钟
  参数：RCC_APB2Periph_XXX：APB2外设
  返回值：无
*/
void xRCC::APB2Periph_OFF(uint32_t RCC_APB2Periph_XXX){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_XXX,DISABLE);
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

/**配置72MHz主频
  描述：配置72MHz主频
  返回值：无
*/
void xRCC::Simple72Mhz(){
  Reset();
  HSE_ON();
  while(WaitForReady(RDY_HSE)==ERROR);
  AHBDiv(SYSCLK_DIV1);
  APB1Div(AHBCLK_DIV2);
  APB2Div(AHBCLK_DIV1);
  PLLConfig(PLLSRC_HSEv1,9);
  PLL_ON();
  while(WaitForReady(RDY_PLL)==ERROR);
  PLLasSysClock();
  while(0x08!=GetSysClock());
}
