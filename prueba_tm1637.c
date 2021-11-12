
#include <16F877.h>
#include <string.h>                                                                    // Librerias para manejo de strings
#include <stdlib.h> 



#FUSES NOWDT                    //No Watch Dog Timer
//#FUSES INTRC_IO //  XT          //Internal RC Osc, no CLKOUT
#FUSES NOCPD                    //No EE protection
#FUSES NOPROTECT                //Code not protected from reading
//#FUSES NOMCLR                   //Master Clear pin used for I/O
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


//         FUNCIONES********************************************************************
 


//        FIN FUNCIONES******************************************************************
void main()
{
int a =1;
//setup_comparator(NC_NC);  //apago comparador
set_tris_a(0b00000000);  // configuracion de puerto todas salidas
output_a(0);   //todas las salidas a cero
//****************************************************************

delay_ms(2000);


write_full_display(8,2,3,4); // digitos a escribir

init_tm1637(0x07);   //habilito diplay enviando brillo

WHILE(true);


}
