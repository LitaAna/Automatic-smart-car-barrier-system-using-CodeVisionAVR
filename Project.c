#include <mega164a.h>
#include <alcd_twi.h> // Include the LCD library
#include <delay.h>
#include <i2c.h>

// Define LCD address and pins
#define F_CPU 20000000UL  // frecventa de ceas
#define PCF8574_I2C_ADDRESS 0x3F // LCD I2C address
#define IRPin PINA.0

unsigned int distance_cm;

//initializarea ADC-ului
void init_ADC() {
    ADMUX |= (1 << REFS0); // Reference voltage is AVCC with external capacitor at AREF pin
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC and set prescaler to 128
}

// Function to read ADC value from specified channel
int ADC_Read(char channel) {
    int Ain, AinLow;
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Set input channel to read
    ADCSRA |= (1 << ADSC); // Start conversion
    while((ADCSRA & (1 << ADIF)) == 0); // Wait for conversion to finish
    AinLow = (int)ADCL; // Read lower byte
    Ain = (int)ADCH * 256; // Read higher 2 bits and multiply by weight
    Ain += AinLow;
    return Ain; // Return digital value
}

//Functie pentru calcularea distantei
unsigned int calculDistanta(float volt) {
    float distance_cm = 1/ (volt* 0.001197676);
    return (unsigned int)distance_cm; // Convertim distan?a într-un întreg ?i o returnam
}

// Functia pentru initializarea senzorului
void initSensor() {
    // Set SENSOR_PIN as input
    DDRA &= ~(1 << IRPin);
}



void main(void) {

    // Initializare LCD
    twi_master_init(100);
    #asm("sei") // registrul pentru intrerupere
    lcd_twi_init(PCF8574_I2C_ADDRESS,16);   
    
    init_ADC(); // initializare ADC 
    
    DDRA &= ~(1 << DDA0);
    DDRB |= (1 << DDB0);
    lcd_clear(); 
    DDRD |= (1 << PIND5);        /* Make OC1A pin as output */ 
    TCNT0 = 0;                   /* Set timer1 count zero */
    ICR1H = 0x09;                /* Set TOP count (2499) for timer1 */
    ICR1L = 0xC3;                /* ICR1 = 2499 => 0x09C3 in hexadecimal */

    /* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/256 */
    TCCR1A = (1<<WGM11)|(1<<COM1A1);
    TCCR1B = (1<<WGM12)|(1<<WGM13)|(0<<CS10)|(0<<CS11)|(1<<CS12);
    
    while(1) {
        int adc_rd = ADC_Read(0);
        distance_cm = calculDistanta(adc_rd);
        lcd_printfxy(0,0,"Distance: %u dm",distance_cm);
        delay_ms(100);
        
        if(distance_cm==1){
          OCR1AH = 0x00;  
        OCR1AL = 0x2D;  
        delay_ms(2000);
        }
        
        else {
        OCR1AH = 0x00;  
        OCR1AL = 0x78; 
        delay_ms(2000);
      }
    }
}