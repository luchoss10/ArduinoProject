#include <LiquidCrystal.h>
LiquidCrystal lcd(22, 23, 25, 24, 27, 26);

//Definción de variables
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
#define velocidadTexto 400

String txt1="Club Drive Tennis";
String txt2="   Lanzapelotas  ";
String txt3="Ing. Mecatronica";
String txt4="       UTP      ";

const char *txtMenu[] = {
  "Comenzar        ",
  "Configuracion   ",
  "Salir           "
};

const char *txtOptions [] = {
  "Velocidad   ",
  "Cosa X      ",
  "Movimiento  ",
  "Salir No Guardar"
  "Guardar y Salir "                                                                             
};

const char *txtMov[] = {
  "ON  ",
  "OFF "
};

const char*txtM1[] = {
  "20% ",
  "40% ",
  "60% ",
  "80% ",
  "100%"
};

const char*txtM2[] = {
  "5   ",
  "10  ",
  "15  ",
  "20  ",
  "25  ",
  "30  "
};

int MENU = 0;// 3 menus 0=  pantalla de muestra 1= selecionador 2= opciones
int countMenu = 0, countOp = 0, entM=0, entO=0, pushButton = 0, PWM_M1_S=0, PWM_M2_S=0, MOV=0;// Contadores de poscion menu y opciones

int PWM_M1_F[] = {51, 102, 153, 204, 255};
int PWM_M2_F[] = {43, 87, 130, 173, 217, 255};

void setup(){
  // put your setup code here, to run once:
  lcd.begin(16, 2);              // Inicializar el LCD
  lcd.setCursor(0,0);
  }

void loop() {
  switch(MENU){
    case 0:
    menu0 ();
    break;
    case 1:
    menu1();
    break;
    case 2:
    menu2();
    break;
  }
  
  
}
void menu0 (){
  int tamTxt1= txt1.length();
  for(int i=tamTxt1; i>0 ; i--){
    String texto1 = txt1.substring(i-1);
    String texto2 = txt2.substring(i-1);
    // Limpiamos pantalla
    lcd.clear();
    //Situamos el cursor
    lcd.setCursor(0, 0);
    // Escribimos el texto
    lcd.print(texto1);
    //Situamos el cursor
    lcd.setCursor(0, 1);
    // Escribimos el texto
    lcd.print(texto2);
    // Esperamos
    delay(velocidadTexto);
    
    revBtns(MENU);
  }
  delay(1000);
  for(int i=1; i<=16; i++){
    lcd.clear();
    lcd.setCursor(i,0);
    lcd.print(txt1);
    lcd.setCursor(i,1);
    lcd.print(txt2);

    delay(velocidadTexto);
    revBtns(MENU);
  }
  for(int i=1; i<=16 ; i++){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(txt3);
    lcd.setCursor(0, 1);
    lcd.print(txt4);
    delay(velocidadTexto);
    revBtns(MENU);
  }
}

void menu1(){
  if(entM == 0){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Menu            ");
  lcd.setCursor(0, 1);
  lcd.print(txtMenu[countMenu]);
  entM=1;  
  }else{
    lcd.setCursor(0,1);
    lcd.print(txtMenu[countMenu]);
    revBtns(MENU);
  }
}

void menu2(){
  if(entO == 0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Configuracion   ");
    lcd.setCursor(0, 1);
    lcd.print(txtOptions[countOp]);
  entM=1;  
  }else{
    lcd.setCursor(0, 1);
    lcd.print(txtOptions[countOp]);
    if(countOp == 0){
      lcd.setCursor(12, 1);
      lcd.print(txtM1[PWM_M1_S]);
    }else if(countOp == 1){
      lcd.setCursor(12, 1);
      lcd.print(txtM2[PWM_M2_S]);
    }else if(countOp == 2){
      lcd.setCursor(12, 1);
      lcd.print(txtMov[MOV]);
    }
    revBtns(MENU);
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

void revBtns(int menuCase){
  
  lcd_key = read_LCD_buttons();
  if( lcd_key == btnRIGHT){
    switch(menuCase){
      case 0:
      MENU=1;
      break;
      case 1:
        
      break;
      case 2:
        if(countOp == 0){
          
        }else if(countOp == 1){
          
        }else if(countOp == 2){
          
        }
      break;
    }
  }
  else if ( lcd_key == btnLEFT ){
   switch(menuCase){
      case 0:
        MENU=1;
      break;
      case 1:
      
      break;
      case 2:
        if(countOp == 0){
          
        }else if(countOp == 1){
          
        }else if(countOp == 2){
          
        }
      break;
    }   
  }
  else if ( lcd_key == btnUP){
   switch(menuCase){
      case 0:
        MENU=1;
      break;
      case 1:
        if(pushButton == 0){
        if(countMenu<2){
            countMenu++;
          }
          pushButton = 1;
        }
      break;
      case 2:

      break;
    }
  }
  else if ( lcd_key == btnDOWN){
    switch(menuCase){
      case 0:
        MENU=1;
      break;
      case 1:
        if(pushButton == 0){
          if(countMenu>0){
            countMenu--;
          }
          pushButton=1;
        }
      break;
      case 2:

      break;
    }
  }
  else if ( lcd_key == btnSELECT){
   switch(menuCase){
      case 0:
        MENU=1;
      break;
      case 1:
        if(pushButton == 0){
        entM = 0;
        if(countMenu==0){
          //Por ahora nada
        }else if(countMenu==1){
          MENU=2;
        }else{
          MENU=0;
        }
        pushButton = 1;
        }
      break;
      case 2:
      
      break;
    }
  }
  else if ( lcd_key == btnNONE){
    pushButton = 0;
  }
}
  
