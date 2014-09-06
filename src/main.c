/* Includes ------------------------------------------------------------------*/
#include <stdlib.h> 
#include "stm32f4xx_conf.h" 
#include "stm32f429-leds.h" 
#include "fmc.h" 

#define BUFFER_SIZE         ((uint32_t)0x0100)
#define WRITE_READ_ADDR     ((uint32_t)0x0)
#define RAM_SIZE            ((uint32_t)(0x800000)) 
#define NUM_INTS            (RAM_SIZE / 4) 

void Delay(__IO uint32_t nCount);

int main(void)
{
    uint32_t i;
    uint32_t *sdram = (uint32_t*)SDRAM_BANK_ADDR;
    uint32_t bad_i = 0;
    uint32_t bad_sdram = 0;

    /* setup leds for error reporting */
    stmeval_leds_setup();
    FMC_Config();
    
    /* 8MB in 32-bit words */
    for (i = 0; i < 0x200000; i++) {
        sdram[i] = i;
    }

    /* check SDRAM Read-back */
    for (i = 0; i < 0x200000; i++) {
        if (sdram[i] != i) {
            bad_i = i;
            bad_sdram = sdram[i];
            stmeval_green_led_off();
            stmeval_red_led_on();
            break;
        }
        stmeval_green_led_on();
    }

    while(1);
}
    


/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  */
void Delay(__IO uint32_t nCount)
{
  while(nCount--);
}
