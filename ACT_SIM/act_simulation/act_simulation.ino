
#define PD1 10
#define PS1 11
#define PD2 4
#define PS2 5
#define IN1 40
double hPulseBuff ;
double vPulseBuff ;
int h_pulse_clock_counter;
int v_pulse_clock_counter;
int h_freq_devider = 100;
int v_freq_devider = 100;
int minPulsePeriodh, minPulsePeriodv;


void setup() {
  // put your setup code here, to run once:
// motorTimer.begin(callbackMotorUpdate, 1000000.0 / MOTOR_PULSE_CLOCK);
Serial.begin(115200);
    pinMode(PD1, OUTPUT);
  pinMode(PS1, OUTPUT);
  pinMode(PD2, OUTPUT);
  pinMode(PS2, OUTPUT);
  pinMode(PS2, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(IN1, INPUT);
}
  
void loop() {
  int base_period = 80;
  // put your main code here, to run repeatedly:
    int period_pulse=400000;
    for (int i=0;i<2005;i++)
    {
      float speed = sin(i*3.14/2000.0);
      period_pulse = base_period/(abs(speed)+0.05);
      if(period_pulse<base_period)period_pulse=base_period;
      digitalWrite(PD1, HIGH);
      digitalWrite(13, digitalRead(IN1));
      if(digitalRead(IN1))
      {Serial.println(millis());break;}
      // Serial.println(digitalRead(IN1));
      // delay(20);
      // Serial.println(period_pulse);
      digitalWrite(PS1, HIGH);
      delayMicroseconds(period_pulse);
      digitalWrite(PS1, LOW);
      delayMicroseconds(period_pulse);
    }
    // period_pulse=400000;
    for (int i=0;i<2000;i++)
    {
      float speed = sin(i*3.14/2000.0);
      period_pulse = base_period/(abs(speed)+0.05);
      if(period_pulse<base_period)period_pulse=base_period;
      digitalWrite(PD1, LOW);
      // Serial.println(period_pulse);
      // Serial.println(digitalRead(IN1));
      digitalWrite(13, digitalRead(IN1));
      digitalWrite(PS1, HIGH);
      delayMicroseconds(period_pulse);
      digitalWrite(PS1, LOW);
      delayMicroseconds(period_pulse);
    }
  // digitalWrite(PD2, LOW);
  // delay(20);
  // digitalWrite(PS2, LOW);
  // delay(20);
  
}
