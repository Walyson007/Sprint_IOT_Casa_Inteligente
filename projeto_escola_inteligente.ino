//bibliotecas
#include <DHT11.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN A1 //Definimos qual sera o pino paara o sensor
#define DHTTYPE DHT11 //Variavel do tipo DHT

DHT dht(DHTPIN, DHT11); //Inicializa o objeto DHT 

//variaveis globsis dao da funcao acenderLEDAoDetectarPrensenca()
const int PIR = 2;  //Pino Digital que PIR está plugado
const int ledAmarelo = 13;

//variaveis globsis dao da funcao verificarVazamentoDeGas
const int MQ135 = A0;
const int buzzer = 12;

void acenderLEDAoDetectarPrensenca() {
int estadoPIR = digitalRead(PIR);  //Lê o pino Digital 2

//SHIFT + ALT + F
// HIGH VALE O VALOR DE 1
// LOW VALE O VALOR DE 0

if (estadoPIR == HIGH) {
  digitalWrite(ledAmarelo, HIGH);
  Serial.println("LED ligado");
} else {
  digitalWrite(ledAmarelo, LOW);
  Serial.println("LED apagado");
}
}


void verificarVazamentoDeGas() {
int estadoMQ135 = analogRead(MQ135);

if (estadoMQ135 >= 600) {
 alarme_dois_tons();
 } else {
 noTone(buzzer);
}
//if - verificar a intesidade do valor do estadoMQ135 >= 600
//sim - ativar o alarme - alarme_dois_tons()
//nao - desativar o alarme - noTone(buzzer);
Serial.println(estadoMQ135);
delay(5000);
}

void alarme_dois_tons() {
int freqAlta = 2000;
int freqBaixa = 800;
int duracaoTom = 250;

tone(buzzer, freqAlta, duracaoTom);
delay(duracaoTom);
tone(buzzer, freqBaixa, duracaoTom);
delay(duracaoTom);
}

void verificarTemperaturaEUmidade(){
 float umidade = dht.readHumidity(); //lê a umidade
 float tempreratura = dht.readTemperature(); // lê a temperatura em Celsius (Padrão)

 Serial.println("Umidade: " + String(umidade) + "%");
 Serial.println("Temperatura: " + String(tempreratura) + "C");
}

void setup() {
Serial.begin(9600);

//fala ao programa que o pino 13 será uma saída/output
pinMode(ledAmarelo, OUTPUT);
pinMode(MQ135, INPUT);
pinMode(buzzer, OUTPUT);

//INICIALIZA O SENSOR DHT
dht.begin();

Serial.println("Calibrando os sensores");
delay(1000);
Serial.println("Sensores calibrado!!! Pode testar ai bbzao");
}

void loop() {
 // As instruções no loop será somente chamada de funções
 //acenderLEDAoDetectarPrensenca()
 //verificarVazamentoDeGas();
 verificarTemperaturaEUmidade();
}
