  //#include <megaTinyCore.h>
#include<math.h>

#define RESOLUTION 100
#define ADC 1024 //Digits
#define RESISTOR 10 //Ohm
#define MAXVOLTAGE 3.84 //Volt
#define OFFSET 550 //ADC/2 //Volt
#define RAUSCHEN 150 //Digits
#define VOLTAGE 14//Pin
#define CURRENT 15//Pin

void setup() {
  // put your setup code here, to run once:
  //pinMode(2,AnalogInput);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  //pinMode(4, OUTPUT);
  Serial.begin(9600); // setup serial
  Serial.print("Device Started\n");
  Serial.print("**********************");
  Serial.println("\t");
  Serial.flush();
  //delay(200);
}

/*****RMS function*****/
double rmsValue(double arr[], int n)
{
  double square = 0, mean = 0.0, root = 0.0;

  /*Calculate square*/
  for (int i = 0; i < n; i++) {
      square += pow(arr[i], 2.0);
  }

  /*Calculate Mean*/
  mean = (square /(double) (n));

  /*Calculate Root*/
  root = sqrt(mean);

  return root;
}
/******************/

void loop() {
int raw, rawV;//, powerInt;
double iArr[RESOLUTION], vArr[RESOLUTION];
double rms, rmsV, voltageI, voltage, voltageV, power, current;

/********CURRENT********/
for (int i = 0; i<RESOLUTION; i++){
    raw = analogRead(CURRENT) - (OFFSET);
    voltageI = ((double)raw/ADC) * MAXVOLTAGE;
    //printf("Volatge for I Measurement: %f",voltageI);
    iArr[i] = voltageI;
}   
rms = rmsValue(iArr, RESOLUTION);
current = rms / RESISTOR;
  Serial.print("Current");
  Serial.print(current);
  Serial.print("A");
  Serial.println("\t");  
  Serial.flush();
/***********************/

/*********************VOLTAGE**********************/
for (int i = 0; i<RESOLUTION; i++){
    rawV = analogRead(VOLTAGE) - (OFFSET);
    voltageV = ((double)rawV/ADC) * MAXVOLTAGE;
    //printf("Voltage Measurement: %fV", voltageV);
    vArr[i] = voltageV;
} 
/*RMS Voltage*/
rmsV = rmsValue(vArr, RESOLUTION);
voltage = rmsV / 0.002; //2k/1Meg=0.002
  Serial.print("Voltage");
  Serial.print(voltage);
  Serial.print("V");
  Serial.println("\t");  
  Serial.flush();
/***********************************************/

/**********POWER**********/
power = voltage * current;
//power = 230 * current;
  Serial.print("Power");
  Serial.print(power);
  Serial.print("W");
  Serial.println("\t");  
  Serial.flush();
/************************/

/*********RED*********/
if (power < 4.0) {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
} else {
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
}
/**********************/

  Serial.print("raw: ");
  Serial.print(iArr[0]);
  Serial.println("\t");  
  Serial.flush();
  int readI = analogRead(CURRENT);
  Serial.print("Val: ");
  Serial.print(readI);
  Serial.println("\t");  
  Serial.flush();
    int readV = analogRead(VOLTAGE);
  Serial.print("Val: ");
  Serial.print(readV);
  Serial.println("\t");  
  Serial.flush();
  
  Serial.print("**********************");
  Serial.println("\t");
  Serial.flush();
  delay(1000);
}
