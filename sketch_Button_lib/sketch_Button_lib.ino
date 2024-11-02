uint8_t pin = 8;
unsigned long _tmr = 0; 
bool _flag = digitalRead(pin);
uint32_t _btnTimer = millis();
void setup() {
 Serial.begin (9600);
 pinMode(8,INPUT);

}
void loop() 
{
 _flag = digitalRead(pin);
 clickType();
 Serial.println(_btnTimer);
}
uint8_t clickType()
{
 switch(_flag)
 {
  case 0:
   Serial.println("Нет нажатия");
   if(1000 > _btnTimer > 0 )
   {
    return 1;
   }
   else
   {
    Serial.println(0);
    return 0;
   }
   _btnTimer = 0;
   _tmr = millis();
   break;
  case 1:
   Serial.println("Нажатие");
   _btnTimer = millis();
/*    for(uint8_t i= 0; i>=0; i++)
   {
    _btnTimer = (_btnTimer + i);
    if(_btnTimer >= 1000)
    {
    Serial.println("Удержание");
     return 2;
    }
   } */
   break;
 }
}