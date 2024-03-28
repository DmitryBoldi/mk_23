#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/usart.h>  //заголовок для перерывааний находиться в другой папке 
#include "ring_buf/ring_buf.hpp"
#include <libopencm3/stm32/spi.h>





{





//НАСТРОЙКА SPI

rcc_periph_clock_enable(RCC_SPI1); 

spi_set_master_mode(SPI1);
spi_set_baudrate_prescaler (SPI1,SPI_CR1_BR_FPCLK_DIV_64);
spi_set_clock_polarity_0(SPI1);
spi_set_clock_phase_0(SPI1);
spi_set_data_size(SPI1, SPI_CR2_DS_8BIT);
spi_send_msb_first(SPI1);
spi_send_lsb_first(SPI1);

spi_enable(SPI1);

rcc_periph_clock_enable(RCC_SPI1); 

gpio_mode_setup(GPIOE, GPIO_MODE_AF,GPIO_PUPD_NONE, GPIO9 );//spi
gpio_mode_setup(GPIOE, GPIO_MODE_AF,GPIO_PUPD_NONE, GPIO4 | GPIO5 | GPIO6 | GPI7 );
gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3 );





}

void loop()
{

   gpio_toggle(GPIOE,GPIO9 )//spi

 
}

int main()
{

setup();
while(true)
 {
  loop();
 }
}

