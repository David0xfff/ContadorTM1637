////////////////////////////////////////////////////////////////////////////
//  Libreria simple para el uno del modulo con display tm1637            ///
//  Programador Adrian A                                                 ///
//  codigo probado en pic12f629                                          ///
////////////////////////////////////////////////////////////////////////////    
//            Primero en el programa principal se debe definir los pines
//            de salia para CLK y DIO ejemplo PIC12F629 
//            #define CLK PIN_A0
//            #define DIO PIN_A1
//            el display 0 es el primero de la izquierda
//
//
//            Luego la funcion  init_tm1637(unsigned char BRIGHT) se debe
//            ejecutar luego de enviar los bytes al display
//            y con distintos valore de BRIGHT se cambia el brillo 
//            cuyo valor va de  0x01  a  0x07    
//            si quieren controlar los dos puntitos centrale del display

unsigned char valores[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x76, 0x00, 0x76, 0x3f, 0x38, 0x77};


void start(void)
{  
   output_high(CLK);
   output_high(DIO);
   delay_us(TIEMPO);
   output_low(DIO);

}

void stop(void)
{
   output_low(CLK);
   delay_us(TIEMPO);
   output_low(DIO);
   delay_us(TIEMPO);
   output_high(CLK);
   delay_us(TIEMPO);
   output_high(DIO);
   
}

void writebyte(unsigned char value)  //bit por bit
{
   unsigned char i, ack;

   for (i = 0; i < 8; ++i, value >>= 1) 
   {
      output_low(CLK);
      delay_us(TIEMPO);
      if(value & 0x01)
         output_high(DIO);
      else 
         output_low(DIO);
      
      output_high(CLK);
      delay_us(TIEMPO);
   }

   output_low(CLK);
   delay_us(TIEMPO);
   ack = input_state(DIO);
   if (ack) 
      output_low(DIO);
   
   delay_us(TIEMPO);

   output_high(CLK);
   delay_us(TIEMPO);

   output_low(CLK);
   delay_us(TIEMPO);
  
}

void init_tm1637(unsigned char BRIGHT)
{
   start();
   writebyte(0x88 | BRIGHT);
   stop();


}

void write_full_display(unsigned char valor0,unsigned char valor1, unsigned char valor2, unsigned char valor3)
{

start();
writebyte(0x40);
stop();

start();
writebyte(0xc0);

writebyte(valores[valor0]);
writebyte(valores[valor1]);
writebyte(valores[valor2]);
writebyte(valores[valor3]);



stop();










}
