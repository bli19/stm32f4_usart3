/*********************************************
    Get the original code from IAR platform from 小船, but his code does not work for my MDK software, I have to
    test using individual function.
**********************************************/
#include <stm32f4xx.h> 

u32 Gb_TimingDelay;

u8 suffer[100];
u8 ok_to_send;
u8 Rx_data_counter;
 
void Delay(uint32_t nTime);
uint16_t s=60;
int main ()
{  
  char Tx_data_counter;
  
  SCB->AIRCR = 0x05AF0000 | 0x400;  //中断优先级分组 抢占：响应=3:1  
  SysTick_Config(SystemCoreClock / 1000); //设置systemtick一毫秒中断
  
  RCC->AHB1ENR |= 0x00000008; //使能GPIOD时钟
  RCC->APB1ENR |= (1<<18);  //使能usart3时钟
  
 USART3->BRR = 0x0000018c;//0x22c   //波特率115200 115 0x0000016C  18c
 
  /*
  使能usart3
  usart3发送使能
  usart3接收使能
  接收缓冲区非空中断使能
  8bit
  一位停止位
  无校验
  */
  USART3->CR1 |= (( 1<<13 ) | ( 1<<3 ) | ( 1<<2 ) | ( 1<<5 )); 
  
  GPIOD->AFR[1] |= 0x00000077;//选择PD8,9复用功能 
  
  GPIOD->MODER &= 0xFFF0FFFF; //设置PD8,9,复用模式
  GPIOD->MODER |= 0x000A0000;  
  
  GPIOD->OSPEEDR &= 0xFFFCFFFF; //PD8速度50m
  GPIOD->OSPEEDR |= 0x00020000;
  
  GPIOD->PUPDR &= 0xFFFCFFFF; //PD8
  GPIOD->PUPDR |= 0x00010000;
  
  NVIC->IP[39] = 0xf0; //最低抢占优先级，最低响应优先级1111
  NVIC->ISER[1] |= (1<<(39-32)); //使能中断线39，也就是usart3中断
  
  
 // while(1){
		 
	USART_SendData(USART3,s);
 // USART_ReceiveData(USART3);
//}	 
}


void Delay(uint32_t nTime)
{ 
  Gb_TimingDelay = nTime;

  while(Gb_TimingDelay != 0);
}

void SysTick_Handler(void)
{
  if (Gb_TimingDelay != 0x00)
  { 
    Gb_TimingDelay--;
  }
}

// void USART3_IRQHandler(void)
// {
//   if(USART3->SR & (1<<5)) //接收数据寄存器非空
//   {
//     suffer[Rx_data_counter] = USART3->DR;
//     Rx_data_counter++;
//     if(suffer[Rx_data_counter - 1] == '\0')
//     {
//       Rx_data_counter = 0;
//       USART3->CR1 &= ~(1<<5); //除能接收中断
//       ok_to_send = 1;
//     }
//    } 
// }
