#include <Arduino.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1X15.h>

void ok();
void updateDisplay();
void readValues();
void setValue();

Adafruit_MCP4725 dac;
Adafruit_ADS1115 adc;

int displayIndex, dacWrite, optionIndex;
bool running, setting, stop;
float currentVolt, currentAmps, setVolt, setAmps;
unsigned long prevMillis;


void setup() {
  Serial.begin(115200);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(10), ok, FALLING);

  adc.begin(0x60);
  dac.begin(0x70);

  adc.setGain(GAIN_ONE);
  adc.setDataRate(RATE_ADS1115_860SPS);
}

void loop() {
  if (millis() - prevMillis >= 200){
    prevMillis = millis();
    updateDisplay();
  }
}

void ok(){
  if (running){
    stop = true;
    running = false;
  }
  if (setting){
    if (optionIndex == 5){
      running = true;
      stop = false;
    }
  }
  if (stop){
    
  }
}

void updateDisplay(){

}

void readValues(){
  currentVolt = adc.computeVolts(adc.readADC_SingleEnded(2));
  currentAmps = adc.computeVolts(adc.readADC_Differential_0_1());
}

void setValue(){
  dac.setVoltage(dacWrite,false);
}

void adjustValue(){
  if (currentAmps <= setAmps){
    if (setVolt >= currentVolt){
      dacWrite -= 1;
    }
    else if (setVolt <= currentVolt){
      dacWrite += 1;
    }
  } else {
    dacWrite += 1;
  }
  dac.setVoltage(dacWrite,false);
}