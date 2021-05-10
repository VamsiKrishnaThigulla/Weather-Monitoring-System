

/* Interfacing LM35 temperature sensor and a photoresistor*/
 
/*
The analog input from the LM35 is connected to ADC0 AIN0 i.e. the PE3 pin
The analog input from the photoresistor is connected to ADC0 AIN1 i.e. the PE2 pin

These analog inputs are interpreted as required
Temperature input is converted to Fahrenheit
Voltage input is converted to a percentage scale 
*/
 
#include <stdint.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"


void UART0Tx(char c);
void UART0_init(void);
void UART0_puts(char* s);

void delayMs(int n);

void Get_temp(void);
void Get_light(void);

int temperature;
float intensity;
char buffer[18];

int main(void)
{
    /* initialize UART0 for output */
    UART0_init();
    
    while(1)
    {
      
    Get_temp();
    
    Get_light();
    
    }
}
 
void UART0_init(void)
{
    SYSCTL_RCGCUART_R |= 1;         /* provide clock to UART0 */
    SYSCTL_RCGCGPIO_R |= 0x01;      /* enable clock to GPIO_PORTA */
 
    /* UART0 initialization */
    UART0_CTL_R = 0;                /* disable UART0 */
    UART0_IBRD_R = 104;             /* 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
    UART0_FBRD_R = 11;              /* fraction part*/
    UART0_CC_R = 0;                 /* Enable the use of system clock as the clock to be used for UART0*/
    UART0_LCRH_R = 0x60;            /* 8-bit, no parity, 1-stop bit, no FIFO */
    UART0_CTL_R = 0x301;            /* enable UART0, TXE, RXE */
 
    /* UART0 TX0 and RX0 use PA0 and PA1, which need to be set up.*/
    GPIO_PORTA_DEN_R = 0x03;        /* Make PA0 and PA1 as digital */
    GPIO_PORTA_AFSEL_R = 0x03;      /* Use PA0,PA1 alternate function */
    GPIO_PORTA_PCTL_R = 0x11;       /* configure PA0 and PA1 for UART */
}
 
void UART0Tx(char c)
{
    while((UART0_FR_R & 0x20) != 0); /* wait until Tx buffer not full */
    UART0_DR_R = c;                 /* send the byte to UART0 */
}
 
void UART0_puts(char* s)
{
    while (*s != 0)                 /* if not end of string */
        UART0Tx(*s++);              /* send the character through UART0 */
}
 
/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
    int32_t i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3180; j++)
            {;}  /* do nothing for 1 ms */
}

void Get_temp(void)
{
    SYSCTL_RCGCGPIO_R |= 0x10;      /* enable clock to GPIO_PORTE */
    SYSCTL_RCGCADC_R |= 1;          /* enable clock to ADC0 */
    
    /* initialize PE3 for AIN0 input */
    GPIO_PORTE_AFSEL_R |= 8;        /* enable alternate function */
    GPIO_PORTE_DEN_R &= ~8;         /* disable digital function */
    GPIO_PORTE_AMSEL_R |= 8;        /* enable analog function */
 
    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~8;             /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;         /* software trigger conversion */
    ADC0_SSMUX3_R = 0;              /* get input from channel 0 PE3 */
    ADC0_SSCTL3_R |= 6;             /* take one sample at a time, set flag at 1st sample */
    ADC0_ACTSS_R |= 8;              /* enable ADC0 sequencer 3 SS3*/
    
    
        ADC0_PSSI_R |= 8;           /* start a conversion sequence 3 */
        while((ADC0_RIS_R & 0x08) == 0)
            ;                       /* wait for conversion to complete */
        temperature = ((ADC0_SSFIFO3_R * 330) / 4096);
        ADC0_ISC_R = 8;             /* clear completion flag  */
        sprintf(buffer, "%d\r\n", temperature);
        UART0_puts(buffer);
        delayMs(1000);
    
}

void Get_light(void)
{
    
    SYSCTL_RCGCGPIO_R |= 0x10;      /* enable clock to GPIO_PORTE */
    SYSCTL_RCGCADC_R |= 1;          /* enable clock to ADC0 */
    
    /* initialize PE2 for AIN1 input */
    GPIO_PORTE_AFSEL_R |= 4;        /* enable alternate function */
    GPIO_PORTE_DEN_R &= ~4;         /* disable digital function */
    GPIO_PORTE_AMSEL_R |= 4;        /* enable analog function */
    
    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~8;             /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;         /* software trigger conversion */
    ADC0_SSMUX3_R = 1;              /* get input from channel 1 PE2*/
    ADC0_SSCTL3_R |= 6;             /* take one sample at a time, set flag at 1st sample */
    ADC0_ACTSS_R |= 8;              /* enable ADC0 sequencer 3 SS3*/
    
    
        ADC0_PSSI_R |= 8;           /* start a conversion sequence 3 */
        while((ADC0_RIS_R & 0x08) == 0)
            ;                       /* wait for conversion to complete */
        intensity = (ADC0_SSFIFO3_R/4096.0);
        ADC0_ISC_R = 8;             /* clear completion flag  */
        sprintf(buffer, "%f\r\n", intensity);
        UART0_puts(buffer);
        delayMs(1000);
    
    
}
