#define HEATER_CONTROL 11

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(HEATER_CONTROL, OUTPUT);
}
float target_temp=40;

void loop() {
  // put your main code here, to run repeatedly:
  float temperature_sum=0;
  for(int i=0;i<10000;i++)
  {
    temperature_sum+= (5.0*analogRead(A0)*100.0/1024.0);
  }
  float temperature = temperature_sum/10000;
  if(temperature<5)
  {
    int i=0;
    while(i<10)
    {
      Serial.println("error");
      analogWrite(HEATER_CONTROL,0);
      delay(1000);
      i++;
    }
  }
  float temp_diff = target_temp-temperature;
  if(temp_diff>5)temp_diff=5;
  if(temp_diff<0)temp_diff=0;
  
  Serial.println(temperature);
  
  analogWrite(HEATER_CONTROL,temp_diff*50);
  delay(1000);
  
}
