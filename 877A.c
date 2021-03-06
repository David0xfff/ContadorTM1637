#include <16F877.h>
#include <math.h>    
#include <string.h>                                                                    // Librerias para manejo de strings
#include <stdlib.h> 

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOCPD                    //No EE protection
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOBROWNOUT               //Reset when brownout detected

#define CLK PIN_A0   //salida transmisor
#define DIO PIN_A1   //entrada boton
#define GP2 PIN_A2   //salida de led
#define GP3 PIN_A3
#define GP4 PIN_A4   
#define GP5 PIN_A5   
#define TIEMPO 50
#use delay(clock=4000000)

#include <display_tm1637.h>  //se agrega despues de la declaracion de pines

#use fast_io (B)      // PARA PERMITIRNOS CONFIGURAR MANUALMENTE
#use fast_io (C)      // LOS PUERTOS COMO ENTRADAS O SALIDAS   
#use fast_io (A) 

int16 periodo, Valor, DC, CONT=0, unidad, decena, centena;
float  volts=0, voltsV=0;



#DEFINE BOTON_UP    PIN_B0
#DEFINE BOTON_DOWN  PIN_B1

// FUNCIONES********************************************************************
 
 void IniVariables()
         {
         
      periodo= 0; 
      DC= 0;            // Ciclo ?til
      Valor=0;
         }
 

void IniPuertos()
         {
         
   set_tris_b(0B00000011);      // PULSADOR Y SALIDA
   set_tris_c(0b11111011);      // SALIDA PWM
   set_tris_a(0b00000000);  // configuracion de puerto todas salidas
   port_b_pullups(1);
      
         } 
         
         
void ConfiguraPWM()
         {
         
   setup_ccp1(CCP_PWM);
   periodo= 125;                        // 249 para 1 kHz (1000us). 8 bits
   setup_timer_2(T2_DIV_BY_16, Periodo, 1);      // T=(4/clock)*t2div*(periodo+1)
                                    // t2div puede ser 1, 4, 16
 //    Valor= DC*10;                       // Valor es de 10 bits
   set_pwm1_duty(DC);                  // valor*(1/clock)*t2div= TAlto    
   
         }   
         
void Visualiza(){
      voltsV= volts*10;
    
      int16 numero;
      numero = DC;
      unidad = numero % 10;
      decena = (numero / 10) % 10;
      centena = (numero / 10) / 10;


write_full_display(0,0,centena,decena); 
}


//FIN FUNCIONES******************************************************************






void main()
{

   IniPuertos();
   IniVariables();
   ConfiguraPWM();
   init_tm1637(0x07);   //habilito diplay enviando brillo

write_full_display(0,0,0,0);


WHILE(true){


 if (!input(BOTON_UP))
            {
         DC=DC+20;
         ConfiguraPWM();
         CONT=CONT+1;
         volts=CONT/5;
         Visualiza();
         delay_ms(250);
            }   
            
if (!input(BOTON_DOWN))
            {
         DC=DC-20;
         ConfiguraPWM();
         CONT--;
         volts=CONT/5;
         Visualiza();
         delay_ms(250);
            }  
            
if (DC >= 500 ){DC=0;}
            
   }


}
