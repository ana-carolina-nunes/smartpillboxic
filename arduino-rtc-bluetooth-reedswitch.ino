#include <Wire.h>
#include <RTClib.h> //inclusão das bibliotecas
//#include <SoftwareSerial.h>
#define RX 8
#define TX 9
//SoftwareSerial bluetooth(RX, TX); // RX, TX

RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231
 
//DECLARAÇÃO DOS DIAS DA SEMANA
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};

const int pinoLed = 12; //pino digital utilizado pelo LED
const int pinoSensor=8; //pino digital utilizado pelo sensor

void setup() {
  // put your setup code here, to run once:

  //RTC

   Serial.begin(9600); //INICIALIZA A SERIAL
  if(! rtc.begin()) { // SE O RTC NÃO FOR INICIALIZADO, FAZ
    Serial.println("DS3231 não encontrado"); //imprime o texto
    while(1); //SEMPRE ENTRE NO LOOP
  }
  if(rtc.lostPower()){ //SE RTC FOI LIGADO PELA PRIMEIRA VEZ / FICOU SEM ENERGIA / ESGOTOU A BATERIA, FAZ
    Serial.println("DS3231 OK!"); //imprime o texto
   
    //INSERINDO AS INFORMAÇÕES ATUALIZADAS EM SEU RTC (apenas para a primeira vez que for usar o RTC)
    //depois disso, a linha a seguir é opcional
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO   
  }
  delay(100); //INTERVALO DE 100 MILISSEGUNDOS

  //PREED SWITCH
  
  pinMode(pinoSensor, INPUT); //define o pino como entrada
  pinMode(pinoLed, OUTPUT); //define o pino como saída
  digitalWrite(pinoLed, LOW); //LED inicia desligado
}

/*void verificaBluetooth(){ // Verifica se existe algum dado a ser lido da serial
  if (bluetooth.available()){ // verifica se existem bytes a serem lidos da porta serial virtual
     char dados = bluetooth.read(); // Lê 1 byte da porta serial
     Serial.print(dados); // Mostra esse dado lido na porta serial
     if (dados=='0'){ // Se o byte lido for igual a 0
        Serial.print(" Não há dados disponíveis (primeiro if) ");
     }
     else{
        if (dados=='1'){ // Se o byte lido for igual a 1
            Serial.print(" Não há dados disponíveis (segundo if)"); 
        }
     }
  }
}*/
          
void loop() {
  // put your main code here, to run repeatedly:

//RTC


    DateTime now = rtc.now(); //CHAMADA DE FUNÇÃO
    /*
    Serial.print("Data: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(now.day(), DEC); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.month(), DEC); //IMPRIME NO MONITOR SERIAL O MÊS
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.year(), DEC); //IMPRIME NO MONITOR SERIAL O ANO
    Serial.print(" / Dia: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print(" / Horas: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(now.hour(), DEC); //IMPRIME NO MONITOR SERIAL A HORA
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.minute(), DEC); //IMPRIME NO MONITOR SERIAL OS MINUTOS
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.second(), DEC); //IMPRIME NO MONITOR SERIAL OS SEGUNDOS    
*/
     //REED SWITCH
    if(digitalRead (pinoSensor) == LOW){ //se a leitura do pino for igual a LOW 
    digitalWrite(pinoLed,LOW); //ascende o LED
    
  String variavel;
  variavel = (String)now.year()+"-"+(String)now.month()+"-"+(String)now.day()+"-"+(String)now.hour()+"-"+(String)now.minute()+"-"+(String)now.second();

Serial.print(variavel);
Serial.print("-0-*");
      
   //Serial.print(" LED DESLIGADO => caixinha FECHADA ");//0

  }else{//se não
    digitalWrite (pinoLed, HIGH); //apaga o LED

   String variavel2;
  variavel2 = (String)now.year()+"-"+(String)now.month()+"-"+(String)now.day()+"-"+(String)now.hour()+"-"+(String)now.minute()+"-"+(String)now.second();

Serial.print(variavel2);
Serial.print("-1-*");
      
    
  // Serial.print(" LED LIGADO => caixinha ABERTA ");      //1
  }
   // Serial.println(); //QUEBRA DE LINHA NA SERIAL
    delay(10000); //INTERVALO DE 10 SEGUNDOS
    
  }
