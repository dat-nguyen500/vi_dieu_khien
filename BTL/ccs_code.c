#include <16F877A.h>
#device ADC = 10
#fuses NOWDT, NOBROWNOUT, NOLVP
#use delay(crystal = 4000000)
float VREF = 5;
int16 i;
int8 giatri, chuc, donvi;
const char chuso[] = 
{
   0b00111111,
   0b00000110,
   0b01011011, 
   0b01001111,
   0b01100110, 
   0b01101101, 
   0b01111101, 
   0b00000111, 
   0b01111111,
   0b01101111
};

void quet_led(int8 giatri)
{
   for (i = 0; i < 1000; i++)
   {
      chuc = giatri / 10;
      donvi = giatri % 10;
      
      if (chuc == 0)
      {
         output_b(0b11111110);
         output_d(0);
         delay_us(500);
      }
      else
      {
         output_b(0b11111110);
         output_d(chuso[chuc]);
         delay_us(500);
      }
      
      output_b(0b11111101);
      output_d(chuso[donvi]);
      delay_us(500);
   }
}

int8 round(float a)
{
   return (int8) (a + 0.5);
}

void main(void)
{
   set_tris_a(0xFF);
   set_tris_b(0);
   set_tris_d(0);
   output_b(0b11111111);
   output_d(0);
   setup_ADC(ADC_CLOCK_INTERNAL) ; 
   setup_ADC_ports(AN0); 
   set_ADC_channel(0) ; 
   delay_us(10);
   while(True)
   {
      giatri = round(read_adc() * VREF / 10.230);
      quet_led(giatri);
   }
}
