
/*
 * CODIGO ELABORADO POR LUIS MIGUEL MARMOLEJO PEÑA
 * @luchoss10 Twitter;
 * Ingeniero Mecatronico
 * Todos los derechos reeservados
 * Codigo Libre
 */

//Libreria LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(22, 23, 25, 24, 27, 26);

//Definción de variables---------------
//Variables de botones
int lcd_key     = 0;
int adc_key_in  = 0;
//Variable manejo de potencia
int RELE = 28;
int RPWM = 5;
int LPWM = 6;
int L_EN = 7;
int R_EN = 8;
int M2PWM = 9;
//Variables control de tiempo
unsigned long tAhora = 0;
unsigned long tAntes = 0;
long tActivo = 0, tActivoA;
//Variables Pines LCD
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
#define velocidadTexto 400
//Mensajes de la pantalla de eepera
String txt1 = "Club Drive Tennis";
String txt2 = "   Lanzapelotas  ";
String txt3 = "Ing. Mecatronica";
String txt4 = "       UTP      ";

//Mensajes de los menus
const char *txtMenu[] = {
  "Comenzar        ",
  "Configuracion   ",
  "Salir           "
};

const char *txtOptions [] = {
  "Velocidad   ",
  "Motor 2     ",
  "Movimiento  ",
  "Tiempo      ",
  "Salir No Guardar",
  "Guardar y Salir "
};

const char *txtMov[] = {
  "OFF ",
  "ON  "
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

const char *txtTime[] = {
  "1Min",
  "2Min",
  "3Min",
  "4Min",
  "5Min",
  "6Min",
  "7Min",
  "8Min",
  "9Min",
  "10Mi",
};

//Variabels control de menus
int MENU = 0;// 3 menus 0=  pantalla de muestra 1= selecionador 2= opciones
// Contadores de poscion menu y opciones, Variables que determinan el funcionamiento de la maquina
int countMenu = 0, countOp = 0, entM = 0, entO = 0, entS = 0, pushButton = 0, PWM_M1_S = 0, PWM_M2_S = 0, MOV = 0, PWM_M1_A, PWM_M2_A, MOVA; 
int PWM_M1_F[] = {51, 102, 153, 204, 255};
int PWM_M2_F[] = {43, 87, 130, 173, 217, 255};

void setup() {
  // Configuracion de pines de salida 
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE,HIGH);
  for(int i=5;i<9;i++){
   pinMode(i,OUTPUT);
  }
   for(int i=5;i<9;i++){
   digitalWrite(i,LOW);
  }
  
  lcd.begin(16, 2);              // Inicializar el LCD
  lcd.setCursor(0, 0);
}

void loop() {
  //Funcion loop que entra al menu determinado
  switch (MENU) {
    case 0:
      menu0 ();
      break;
    case 1:
      menu1();
      break;
    case 2:
      menu2();
      break;
    case 3:
      //funcion que determina el tiempo transcurrido en el instante
      tAhora = millis();
      operativo();
      break;
  }
  
}
//menu 0 que controla el modo de espera y muestra mensajes en la pantalla
void menu0 () {
  //Rutina mensaje que se desplaza ------------------------------
  int tamTxt1 = txt1.length();
  for (int i = tamTxt1; i > 0 ; i--) {
    if(MENU == 1) break;
    String texto1 = txt1.substring(i - 1);
    String texto2 = txt2.substring(i - 1);
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
  for (int i = 1; i <= 16; i++) {
    if(MENU == 1) break;
    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.print(txt1);
    lcd.setCursor(i, 1);
    lcd.print(txt2);
    delay(velocidadTexto);
    revBtns(MENU);
  }
  //Rutina que muestra un mensaje estatico
  for (int i = 1; i <= 16 ; i++) {
    if(MENU == 1) break;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(txt3);
    lcd.setCursor(0, 1);
    lcd.print(txt4);
    delay(velocidadTexto);
    revBtns(MENU);
  }
}
//Menu 1 dessde aqui se accede al menu de configuracion y se da inicio la maquina
void menu1() {
  if (entM == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Menu            ");
    lcd.setCursor(0, 1);
    lcd.print(txtMenu[countMenu]);
    entM = 1;
  } else {
    lcd.setCursor(0, 1);
    lcd.print(txtMenu[countMenu]);
    revBtns(MENU);
  }
}
//Menu 2 onfiguraciones del sistema
void menu2() {
  if (entO == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Configuracion   ");
    lcd.setCursor(0, 1);
    lcd.print(txtOptions[countOp]);
    PWM_M1_A = PWM_M1_S;
    PWM_M2_A = PWM_M2_S;
    MOVA = MOV;
    tActivoA = tActivo;
    entO = 1;
  } else {
    if (countOp == 0) {
      lcd.setCursor(12, 1);
      lcd.print(txtM1[PWM_M1_S]);
    }
    if (countOp == 1) {
      lcd.setCursor(12, 1);
      lcd.print(txtM2[PWM_M2_S]);
    }
    if (countOp == 2) {
      lcd.setCursor(12, 1);
      lcd.print(txtMov[MOV]);
    }
    if(countOp == 3){
      lcd.setCursor(12, 1);
      lcd.print(txtTime[tActivo]);
    }
    lcd.setCursor(0, 1);
    lcd.print(txtOptions[countOp]);
    revBtns(MENU);
  }
}
//Menu operativo, desde aqui se realizan todas las acciones para el control de la maquina en determinado tiempo con los datos y parametros configurados.
void operativo() {
  if(entS == 0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   ENCENDIDO    ");
    if (MOV == 1)
    {
      digitalWrite(RELE, LOW);
    }else if(MOV == 0){
      digitalWrite(RELE,HIGH);
    }
    digitalWrite(R_EN,HIGH);
  
    analogWrite(RPWM,PWM_M1_F[PWM_M1_S]);
    analogWrite(M2PWM,PWM_M2_F[PWM_M2_S]);
    entS = 1;
  }else{
    lcd.setCursor(0, 1);
    int Cosa = tActivo + 1;
    lcd.print(String(Cosa)   + "Min activo");
  }
  
  if(tAhora - tAntes >=((tActivo+1)*60*1000)){
    analogWrite(RPWM,0);
    analogWrite(M2PWM,0);
    digitalWrite(R_EN,LOW);
    digitalWrite(RELE,HIGH);
    entS = 0;
    MENU=1;
  }
  
}

//Funcion para determinar el boton pulsado con su valor analogico
int read_LCD_buttons() {
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

//Una vez determinado el boton pulsado en esta funcion se determina su accion, dependiendo del menu en el que se encuentre. 
void revBtns(int menuCase) {
  lcd_key = read_LCD_buttons();
  if ( lcd_key == btnRIGHT) {
    switch (menuCase) {
      case 0:
          MENU = 1;
        break;
      case 1:
          //Nada
        break;
      case 2:
        if (pushButton == 0) {
          if (countOp == 0) {
            if (PWM_M1_S < 4) {
              PWM_M1_S++;
            }

          } else if (countOp == 1) {
            if (PWM_M2_S < 5) {
              PWM_M2_S++;
            }
          } else if (countOp == 2) {
            if (MOV < 1) MOV++;
          } else if (countOp == 3){
            if(tActivo<9) tActivo++;
          }
          pushButton = 1;
        }
        break;
    }
  }
  else if ( lcd_key == btnLEFT ) {
    switch (menuCase) {
      case 0:
          MENU = 1;
        break;
      case 1:
          //Nada
        break;
      case 2:
        if (pushButton == 0) {
          if (countOp == 0) {
            if (PWM_M1_S > 0) {
              PWM_M1_S--;
            }
          } else if (countOp == 1) {
            if (PWM_M2_S > 0) {
              PWM_M2_S--;
            }
          } else if (countOp == 2) {
            if (MOV > 0)MOV--;
          } else if(countOp == 3){
            if(tActivo>0) tActivo--;
          }
          pushButton = 1;
        }
        break;
    }
  }
  else if ( lcd_key == btnUP) {
    switch (menuCase) {
      case 0:
        MENU = 1;
        break;
      case 1:
        if (pushButton == 0) {
          if (countMenu < 2) {
            countMenu++;
          }
          pushButton = 1;
        }
        break;
      case 2:
        if (pushButton == 0) {
          if (countOp < 5) {
            countOp++;
          }
          pushButton = 1;
        }
        break;
    }
  }
  else if ( lcd_key == btnDOWN) {
    switch (menuCase) {
      case 0:
        MENU = 1;
        break;
      case 1:
        if (pushButton == 0) {
          if (countMenu > 0) {
            countMenu--;
          }
          pushButton = 1;
        }
        break;
      case 2:
        if (pushButton == 0) {
          if (countOp > 0) {
            countOp--;
          }
          pushButton = 1;
        }
        break;
    }
  }
  else if ( lcd_key == btnSELECT) {
    switch (menuCase) {
      case 0:
        MENU = 1;
        break;
      case 1:
        if (pushButton == 0) {
            entM = 0;
          if (countMenu == 0) {
            tAntes =  millis();
            MENU = 3;
          } else if (countMenu == 1) {
            MENU = 2;
          } else {
            MENU = 0;
          }
          pushButton = 1;
        }
        break;
      case 2:
      if (pushButton == 0) {
        if (countOp == 0) {
          if (PWM_M1_S < 4) {
            PWM_M1_S++;
          } else if (PWM_M1_S == 4) {
            PWM_M1_S = 0;
          }
        } else if (countOp == 1) {
          if (PWM_M2_S < 5) {
            PWM_M2_S++;
          } else if (PWM_M2_S == 6) {
            PWM_M2_S = 0;
          }
        } else if (countOp == 2) {
          if (MOV < 1) {
            MOV++;
          } else if (MOV == 1) {
            MOV = 0;
          }
        } else if (countOp == 3) {
          //Nada
        } else if (countOp == 4) {
          MOV = MOVA;
          PWM_M1_S = PWM_M1_A;
          PWM_M2_S = PWM_M2_A;
          tActivo =  tActivoA;
          entO = 0;
          MENU = 1;
        }else if(countOp == 5){
          entO = 0;
          MENU = 1;
        }
        pushButton = 1;
      }
        break;
    }
  }
  else if ( lcd_key == btnNONE) {
    pushButton = 0;
  }
}
