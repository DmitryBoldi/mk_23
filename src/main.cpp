#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/usart.h>  //заголовок для перерывааний находиться в другой папке 

#include "ring_buf/ring_buf.hpp"

Ring_buffer buf;

uint8_t c{'a'};
void setup()
{
rcc_periph_clock_enable(RCC_GPIOA);                        
gpio_mode_setup(GPIOA, GPIO_MODE_AF,GPIO_PUPD_NONE, GPIO2 | GPIO3 );
gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3 );


rcc_periph_clock_enable(RCC_USART2);

usart_set_baudrate(USART2, 115200);                       // Скорость передачи
usart_set_databits(USART2, 8);                            // Размер посылки
usart_set_stopbits(USART2, USART_STOPBITS_1);             // Количество стоп-битов
usart_set_parity(USART2, USART_PARITY_NONE);              // Контроль четности


usart_set_mode(USART2, USART_MODE_TX_RX);                 // Режим работы ПУ
usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);   // Управление процессом передачи сообщений

usart_enable_rx_interrupt(USART2);
nvic_enable_irq(NVIC_USART2_EXTI26_IRQ);

usart_enable(USART2);

rcc_periph_clock_enable(RCC_GPIOE);
gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9 | GPIO11 | GPIO15);

}

void loop()
{
  if(!buf.empty() ){
    
    c=buf.get();
  }
  usart_send_blocking(USART2, c);
  for(volatile uint32_t i=0; i<400000;i++);
  gpio_toggle(GPIOE, GPIO9);

}

int main()
{

setup();
while(true)
 {
  loop();
 }
}

void usart2_exti26_isr(void)
{
  USART_RQR(USART2) &=  ~(USART_RQR_RXFRQ);
  buf.put(static_cast<uint8_t>(usart_recv(USART2)));
  //USART_ISR(USART2) &=  ~(USART_ISR_RXNE);//попадает в обработичк из запроса сигналов 
  //[[maybe_unused]]
   
  // c= static_cast<uint8_t>(usart_recv(USART2));
  gpio_toggle(GPIOE, GPIO11);


}

//cc