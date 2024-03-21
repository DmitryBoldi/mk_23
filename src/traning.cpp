
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/usart.h>  //заголовок для перерывааний находиться в другой папке 

void setup()
{
// Интерфейс U(S)ART с внешним миром
rcc_periph_clock_enable(RCC_GPIOA);                           // Разморозка порта ввода/вывода

gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO10);  // Режим альтернативной функции
gpio_set_af(GPIOA,GPIO_AF7, GPIO9 | GPIO10);                           // Альтернативная функция (выбор по номеру) PA9 --- Tx, PA10 --- Rx.


// Настройка и включение U(S)ART, номер устройства настраивается
// для stm32f303 --- в диапазоне 1 -- 5; 4 и 5 --- UART.
// для stm32f407 --- в диапазоне 1 -- 6; 4 и 5 --- UART.

rcc_periph_clock_enable(RCC_USART2);                      // Разморозка ПУ

usart_set_baudrate(USART2, 19200);                       // Скорость передачи
usart_set_databits(USART2, 8);                            // Размер посылки
usart_set_stopbits(USART2, USART_STOPBITS_2);             // Количество стоп-битов
usart_set_parity(USART2, USART_PARITY_NONE);              // Контроль четности


usart_set_mode(USART1, USART_MODE_TX_RX);                 // Режим работы ПУ
usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);   // Управление процессом передачи сообщений

usart_enable(USART2);                                     // Включение ПУ

                                                    // nvic_enable_irq(NVIC_USART1_IRQ);
                                                     //usart_enable(USART1);

}

void loop() {

  if(usart_send_blocking(USART2, 'c' ))
  {
    gpio_toggle(GPIOA, GPIO9)
  };
  else 
  {

  }

  for(volatile uint32_t = 0; i<20000; ++i );{

//uint16_t c= usart_recv_blocking(USART2);
usart_send_blocking(USART2, 0x55);
// usart_send_blocking(USART1, 0x55);
// usart_send_blocking(USART1, 'H');
// usart_send_blocking(USART1, 'e');
// usart_send_blocking(USART1, 'l');
// usart_send_blocking(USART1, 'l');
// usart_send_blocking(USART1, 'o');
// usart_send_blocking(USART1, '\n');
// usart_send_blocking(USART1, '\r');

//for(volatile uint32_t i=0 ; i<1000; i++); 

}

int main()
{
  setup();

  while(true)
  {
    loop();
  }


}

void usart1_exit25_isr(void)

{

uart_enable(){

   uart_clear_interrupt_flag( uint32_t  USART2, UART_INT_RX  ) ;//Очистить флаг запроса пррываний 

  uint16_t c= usart_recv_blocking(USART2); 
  
   //Сохранить принятый1 символ в переменную (глобальную надо определить! )
      // Переключить светодиод , например , PE1 (настроить порт для работы со светодиодом в setup)


} 

// constexpr uint16_t PERIOD_MS{1000};

// void blink_LED() 
// {
// if(timer_get_counter(TIM1) < PERIOD_MS / 2)   
//   {
//     gpio_set(GPIOE, GPIO9);  
//   } 


// else 
//   {
//   gpio_clear(GPIOE, GPIO9);
//   } 

// }


// void LED_gpio_setup()
// {
//   rcc_periph_clock_enable( RCC_GPIOE);
//   gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9 | GPIO11  | GPIO14 );

//   gpio_mode_setup(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO14 );

//   gpio_set_af(GPIOE, GPIO_AF2, GPIO14);

// }

// void timer_setup()
// {
//   rcc_periph_clock_enable( RCC_TIM1);
//   timer_set_prescaler (TIM1, rcc_get_timer_clk_freq(TIM1) / PERIOD_MS -1  );
//   timer_set_period(TIM1, PERIOD_MS-1);

// //для разрешения беспокойства процессора 
//   timer_enable_irq(TIM1, TIM_DIER_UIE);
//   nvic_enable_irq (NVIC_TIM1_UP_TIM16_IRQ ); 

//   timer_enable_counter(TIM1);
// }




// int main()
// { //  насттройка порта ввода-вывода 
//   //Для разгоник ЦП нужно порабоать с rcc_clock_setup_pll
//   rcc_clock_setup_pll( &rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);

//     rcc_periph_clock_enable( RCC_GPIOE);
//   gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO11);
//   gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);




// LED_gpio_setup();
// timer_setup();

//   while (true )
//  {
//   blink_LED();








// СТАРЫЙ ОЛГАРИТМ       //  переключение светодиона
// gpio_toggle(GPIOE, GPIO10);
//   for(volatile uint32_t i = 0; i < 1'000'000; ++i);
// gpio_toggle(GPIOE, GPIO12);
  
//   }

// }



// void tim1_up_tim16_isr(void)  //обработчик  
// {

// timer_clear_flag(TIM1, TIM_SR_UIF); // снимаем заброс или выключаем будильник.  TIM_SR_UIF- для обнуленяи
// //полезная работа те переключение сетодиода  
// gpio_toggle(GPIOE, GPIO11) ;
// }





// hsi - hight speed internal когда появляется кварц 
// uint32_t---жёсткое приивание разрядности для МК
// cmake --install build --- для загрузки на плату прокта 
// cmake --build build --- сборка прокта на проверку ошибок 
//  cmake -B build --- настройка . Редко при удалении папки , добавление файлов в покт или редоктирование CMakeList.txt)
//  cmake --install build
//  git pull upstream  main
//  sudo apt install nscd
//  git pull origin main
//  sudo apt upgrade 
//  sudo apt update
//  cat /etc/group | grep plug
//   sudo usermod -a -G plugdev stud133   
//   sudo openocd -f board/stm32f3discovery

//09.11.2023//volatile - позволяет  программе выполнять функцию ,которую она хочет игнорировать. Для того чтобы начать рабоать с платой нцжно 
//    1.Ничего не надо писать просто подключаем плату  ( sudo  openocd -f board/stm32f3discovery.cfg,  в случае если плата ушла в ожидании то нужно нажать )

//    2. написать программу сохранить и сначала вцыполонить cmake --build build, а потом ,  cmake --install build


// 29.11.2023 изменение алгоритма мигания 
//для разрешения сигнла из вне 
// для многих каналов используеться канал захвата сравнение 