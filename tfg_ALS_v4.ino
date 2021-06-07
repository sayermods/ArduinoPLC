/********************************************************************************/
/* PROYECTO MANTENIMIENTO ELECTRÓNICO /
 * Autor: Alejandro Lasierra Sabio
 * _AUTÓMATA BASADO EN ARDUINO MEGA_
 * ..V2: eliminación de librerías en desuso de la primera versión,
 *       vista más clara de comunicación I2C.
 * ..V3: Reducción de código.     
 * ..V4: Corrección problemas de compilación.
 */
/********************************************************************************/

// Librerías************ 
#include <SoftwareSerial.h>       // Librería serial
#include <Wire.h>                 // incluye libreria para interfaz I2C
#include <Adafruit_GFX.h>         // OLED
#include <Adafruit_SSD1306.h>     // OLED
#include <RTClib.h>               // incluye libreria para el manejo del modulo RTC (reloj)

/*  Información sobre I2C
    Patillaje SCL y SDA por librería Wire.h. Establece los pines automáticamente al compilar para el hardware.
    En arduino UNO:       A4(SDA), A5(SCL)
    En arduino MEGA 2560: 20(SDA), 21(SCL) (Usaremos los pines 20 y 21 para conectar OLED y reloj)
    En arduino LEONARDO:   2(SDA),  3(SCL)
*/

SoftwareSerial Smartphone(19,18); // Comandos bluetooth (pin3 RX , pin 4 TX)

// Definiciones (pines, variables, objetos,...)**********
 //CONFIG OLED**********
#define SCREEN_WIDTH   128        // Ancho pixel OLED
#define SCREEN_HEIGHT   64        // Altura piex OLED
#define OLED_RESET      -1        // Pin reset OLED (-1 Indica que comparte el botón reset integrado de arduino)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

 //Reloj
RTC_DS3231 rtc;                   // Crea objeto del tipo RTC_DS3231

 //Bluetooth
int dato;                         // Dato recibido bluetooth
 
 //Configuración entradas optoacopladores 230VAC
int ACin1 = 32;
int ACin2 = 33;
int ACin3 = 34;
int ACin4 = 35;
int ACin5 = 36;
int ACin6 = 37;
int ACin7 = 38;
int ACin8 = 39;

 //Configuración salidas relés 230VAC
int ACout1 = 40;
int ACout2 = 41;
int ACout3 = 42;
int ACout4 = 43;
int ACout5 = 44;
int ACout6 = 45;
int ACout7 = 46;
int ACout8 = 47;


//____________________________SETUP_______________________
void setup()
{
 //Inicio MONITOR SERIE*****
 Serial.begin(9600);

 //Inicio Bluetooth
 Smartphone.begin(9600);
 Smartphone.println("Inicializado");

 //Inicio OLED*****
 display.begin (SSD1306_SWITCHCAPVCC, 0x3C); 
 display.clearDisplay();

 //Configuración Reloj
 if (! rtc.begin()) 
 {                                              // si falla la inicializacion del modulo
 Serial.println("Modulo RTC no encontrado !");  // muestra mensaje de error ^
 while (1);                                     // bucle infinito que detiene ejecucion del programa
 }

 //CONFIGURACIÓN I/O AC
 pinMode(ACin1, INPUT);
 pinMode(ACin2, INPUT);
 pinMode(ACin3, INPUT);
 pinMode(ACin4, INPUT);
 pinMode(ACin5, INPUT);
 pinMode(ACin6, INPUT);
 pinMode(ACin7, INPUT);
 pinMode(ACin8, INPUT);
 pinMode(ACout1, OUTPUT);
 pinMode(ACout2, OUTPUT); 
 pinMode(ACout3, OUTPUT);
 pinMode(ACout4, OUTPUT);
 pinMode(ACout5, OUTPUT);
 pinMode(ACout6, OUTPUT);
 pinMode(ACout7, OUTPUT);
 pinMode(ACout8, OUTPUT);

 //BIENVENIDA_OLED*****
 display.clearDisplay();        
 display.setTextSize(2); 
 display.setTextColor (WHITE);
 display.setCursor (0,0); 
 display.println("Alejandro Lasierra");         
 display.setCursor(0,17); 
 display.println("PROYECTO"); 
 display.display(); 
 display.setCursor(0,34); 
 display.println("BIENVENIDO"); 
 display.display(); 
 delay(1500);
 
}

/* USO DE LOOP
 * PARA UN PROGRAMA MÁS ORDENADO USAREMOS EL SEGMENTO LOOP PRINCIPALMENTE PARA HACER LLAMADAS
 */

//____________________________LOOP________________________
void loop()
{
PROG1();
PROG2();
PROG3();
}

/* USO DE SUBRUTINAS
 * A CONTINUACIÓN ENCONTRAMOS LA CONFIGURACIÓN DE LAS DIFERENTES SUBRUTINAS
 */
//_________________________SUBRUTINAS______________________
 //SUBRUTINA 1************
void PROG1()            //
{                  
 //PROGRAMA USUARIO 1
 HORAms();
 display.clearDisplay(); //Escribir en pantalla programa en funcionamiento         
 display.setTextSize(2); 
 display.setTextColor (WHITE);
 display.setCursor (0,0); 
 display.println("Programa 1");         
 display.setCursor(0,17); 
 display.println("X"); 
 display.display();  
 delay(10);
 
 //actuación
/* Descripción Programa 1, 
 * Si las entradas 1 y 2 de AC están activas, la salida AC 1 será activada
 * O en su defecto si por bluetooth recibe el dato 'A'.
 */
 if (digitalRead(ACin1)==HIGH && digitalRead(ACin2)==HIGH || (dato=='A') )
   {
   digitalWrite(ACout1, HIGH);
   
   }
   else{
    digitalWrite(ACout1, LOW);
   }
 if (digitalRead(ACin1)==LOW || digitalRead(ACin2)==LOW || (dato=='B') ) //Apagar regleta televisión
   {
   digitalWrite(ACout1, LOW);
   }
   
}

 //SUBRUTINA 2************
void PROG2()            //
{ 
 //PROGRAMA USUARIO 2
 HORAms();
 display.clearDisplay(); //Escribir en pantalla programa en funcionamiento      
 display.setTextSize(2); 
 display.setTextColor (WHITE);
 display.setCursor (0,0); 
 display.println("Programa 2");         
 display.setCursor(0,17); 
 display.println("X"); 
 display.display();  
 delay(10);

 /* Descripción Programa 2, encender regleta televisión 
 * Si la entrada 3 de AC está activa, la salida AC 2 será activada
 * O en su defecto si por bluetooth recibe el dato 'B'.
 */
 if (digitalRead(ACin3)==HIGH || (dato=='C') )
   {
   digitalWrite(ACout2, HIGH);
   }
   else
   {
    digitalWrite(ACout2, LOW);
   }
 if (digitalRead(ACin3)==LOW || (dato=='D') ) //Apagar regleta televisión
   {
   digitalWrite(ACout2, LOW);
   }
 
}

 //SUBRUTINA 3************
void PROG3()            //
{ 
 //PROGRAMA USUARIO 3
 HORAms();
 display.clearDisplay(); //Escribir en pantalla programa en funcionamiento         
 display.setTextSize(2); 
 display.setTextColor (WHITE);
 display.setCursor (0,0); 
 display.println("Programa 3");         
 display.setCursor(0,17); 
 display.println("X"); 
 display.display();  
 delay(10);

  /* Descripción Programa 3, encender aire acondicionado 
 * Si por bluetooth recibe el dato 'B', la salida AC 3 será activada
 */
 if (dato=='E') 
   {
   digitalWrite(ACout3, HIGH);
   }
   else
   {
    digitalWrite(ACout3, LOW);
   }
 if (dato=='F')  //Apagar aire acondicionado
   {
   digitalWrite(ACout2, LOW);
   }
 
 
}

 //SUBRUTINA 4************
void PROG4()            //
{ 
 //PROGRAMA USUARIO 4
 HORAms();
 display.clearDisplay(); //Escribir en pantalla programa en funcionamiento         
 display.setTextSize(2); 
 display.setTextColor (WHITE);
 display.setCursor (0,0); 
 display.println("Programa 4");         
 display.setCursor(0,17); 
 display.println("X"); 
 display.display();  
 delay(10);
}

 //SUBRUTINA 5************
void PROG5()            //
{ 
 //PROGRAMA USUARIO 5
 HORAms();
 display.clearDisplay(); //Escribir en pantalla programa en funcionamiento         
 display.setTextSize(2); 
 display.setTextColor (WHITE);
 display.setCursor (0,0); 
 display.println("Programa 5");         
 display.setCursor(0,17); 
 display.println("X"); 
 display.display();  
 delay(10);
}

 //SUBRUTINA 6************
void PROG6()            //
{ 
 //PROGRAMA USUARIO 6
 HORAms();
 display.clearDisplay(); //Escribir en pantalla programa en funcionamiento         
 display.setTextSize(2); 
 display.setTextColor (WHITE);
 display.setCursor (0,0); 
 display.println("Programa 6");         
 display.setCursor(0,17); 
 display.println("X"); 
 display.display();  
 delay(10);
}

 //SUBRUTINA 7************
void PROG7()            //
{ 
 //PROGRAMA USUARIO 7
 HORAms();
 display.clearDisplay(); //Escribir en pantalla programa en funcionamiento         
 display.setTextSize(2); 
 display.setTextColor (WHITE);
 display.setCursor (0,0); 
 display.println("Programa 7");         
 display.setCursor(0,17); 
 display.println("X"); 
 display.display();  
 delay(10);
}

 //SUBRUTINA 8************
void PROG8()            //
{ 
 //PROGRAMA USUARIO 8
 HORAms();
 display.clearDisplay(); //Escribir en pantalla programa en funcionamiento         
 display.setTextSize(2); 
 display.setTextColor (WHITE);
 display.setCursor (0,0); 
 display.println("Programa 8");         
 display.setCursor(0,17); 
 display.println("X"); 
 display.display();  
 delay(10);
}

 //HORA MONITOR SERIE******
void HORAms()
{
 DateTime fecha = rtc.now();      // funcion que devuelve fecha y horario en formato
                                  // DateTime y asigna a variable fecha
 Serial.print(fecha.day());       // funcion que obtiene el dia de la fecha completa
 Serial.print("/");               // caracter barra como separador
 Serial.print(fecha.month());     // funcion que obtiene el mes de la fecha completa
 Serial.print("/");               // caracter barra como separador
 Serial.print(fecha.year());      // funcion que obtiene el año de la fecha completa
 Serial.print(" ");               // caracter espacio en blanco como separador
 Serial.print(fecha.hour());      // funcion que obtiene la hora de la fecha completa
 Serial.print(":");               // caracter dos puntos como separador
 Serial.print(fecha.minute());    // funcion que obtiene los minutos de la fecha completa
 Serial.print(":");               // caracter dos puntos como separador
 Serial.println(fecha.second());  // funcion que obtiene los segundos de la fecha completa
 
}
  
