#define PINA0 0

int tensao = 220;
float potencia = 0;
float voltsporUnidade = 0.004887586;// 5%1023 //parâmetros para calibração do sensor
int sensorValue_aux  = 0;
float sensorValue = 0;
float currentValue = 0;
int samples = 1500;
float Vref = 2.15;
int ref = Vref/voltsporUnidade;
int gain = 5;
float max_current = 10;
float Vin = 0.300;
float sensibility = ((Vin*gain)/sqrt(2))/max_current;

void setup() {
  Serial.begin(115200);
  pinMode(PINA0,INPUT);
}

void loop() {
  
  for(int i=samples; i>0; i--){
    sensorValue_aux = (analogRead(PINA0) - ref); // le o sensor na pino analogico A0 e ajusta o valor lido ja que a saída do sensor é (1023)vcc/2 para corrente = 0
    sensorValue += pow(sensorValue_aux,2); // somam os quadrados das leituras.
  }
  
  sensorValue = (sqrt(sensorValue/samples)) * voltsporUnidade; // finaliza o calculo da méida quadratica e ajusta o valor lido para volts
  currentValue = (sensorValue/sensibility); // calcula a corrente considerando a sensibilidade do sensor
  potencia = currentValue*tensao;
  
  Serial.print("ADC:  ");
  Serial.println(analogRead(PINA0));
  Serial.print("SENSOR:  ");
  Serial.println(sensorValue);
  Serial.print("CORRENTE:  ");
  Serial.println(currentValue);
  Serial.print("POTENCIA:  ");
  Serial.println(potencia);
}
