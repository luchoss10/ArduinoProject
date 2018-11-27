#include <LiquidCrystal.h>
LiquidCrystal lcd(22, 23, 25, 24, 27, 26);

int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
#define velocidadTexto = 300

String txt1="Club Drive Tennis"
String txt2="   Lanzapelotas  ";
String txt3="Ing. Mecatronica";
String txt4="UTP"

int MENU = 0;


void setup(){
  // put your setup code here, to run once:
  lcd.begin(16, 2);              // Inicializar el LCD
  lcd.setCursor(0,0);
  
  }

void loop() {
  int tamTxt1= txt1.length();
  switch(){
    case 0:
    
    break;
    case 1:
    
    break;
  }
  
  
}

int read_LCD_buttons(){
  adc_key_in = analogRead(0);      // Leemos A0
  // Mis botones dan:  0, 145, 329,507,743
  // Y ahora los comparamos con un margen comodo
  if (adc_key_in > 900) return btnNONE;     // Ningun boton pulsado 
  if (adc_key_in < 50)   return btnRIGHT; 
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT; 
  return btnNONE;  // Por si todo falla
}

void revBtns(){
  lcd_key = read_LCD_buttons();
   if( lcd_key == btnRIGHT)
           
   else if ( lcd_key == btnLEFT )
           
   else if ( lcd_key == btnUP)
           
   else if ( lcd_key == btnDOWN)
           
   else if ( lcd_key == btnSELECT)
           
   else if ( lcd_key == btnNONE)
           
}


void menu0 (){
  for(int i=tamTxt1; i>0 ; i--)
  {
    String texto1 = txt1.substring(i-1);
    String texto2 = txt2.substring(i-1);
    // Limpiamos pantalla
    lcd.clear();
    //Situamos el cursor
    lcd.setCursor(0, 0);
    // Escribimos el texto
    lcd.print(texto1);
    //Situamos el cursor
    lcd.setCursor(1, 0);
    // Escribimos el texto
    lcd.print(texto2);
    // Esperamos
    delay(VELOCIDAD);
    revBtns();
  }
  
}
  
