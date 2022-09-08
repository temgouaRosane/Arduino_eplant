
#define SensorPin A0
unsigned long int avgValue;
float b;
int buf[10], temp;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready");
}

void loop() 
{
  for(int i=0; i<10; i++)
  {
    buf[i]= analogRead(SensorPin);
    delay(10);
    }
    for(int i=0; i<9; i++)
    {
      for(int j=i+1; j<10; j++)
      {
        if (buf[i]>buf[j])
        {
          temp= buf[i];
          buf[i]= buf[j];
          buf[j]= temp;
          }
        }
      }
      avgValue = 0;
      for(int i=2; i<8; i++)
        avgValue+=buf[i];
      float phValue=(float)avgValue*5.0/1025/6;
      avgValue= 3.5*avgValue;
      Serial.print("      PH:");
      Serial.print(phValue,2);
      Serial.println(" ");
      digitalWrite(13, HIGH);
      delay(800);
      digitalWrite(13, LOW);
}
