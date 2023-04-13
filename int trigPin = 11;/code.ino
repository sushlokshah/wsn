int trigPin = 11;    // Trigger
int echoPin = 12;
long duration, cm, inches;
int a[4];
void setup() {
 //Serial Port begin
 Serial.begin (9600);
 //Define inputs and outputs
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
}
void loop() {
 // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
 // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
 digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 // Read the signal from the sensor: a HIGH pulse whose
 // duration is the time (in microseconds) from the sending
 // of the ping to the reception of its echo off of an object.
 pinMode(echoPin, INPUT);
 duration = pulseIn(echoPin, HIGH);
 // Convert the time into a distance
 cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
 inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  Serial.print(inches);
 Serial.print("in, ");
 Serial.print(cm);
 Serial.print("cm");
 Serial.println();


 a[0]=(cm/10);
 a[1]=(cm%10);
send_api_frame();
  delay(250);
}
void send_api_frame()
   {
       int E1_arr[20]={0x00,0x13,0xA2,0x00,0x41,0x9F,0x6B,0xA9,0XFF,0XFE};   //MAC Address of END NODE 1  0013A20040C92DA3
       int check,s,p;
       s=0;
       for(p=0;p<=9;p++)
       {
           s=s+E1_arr[p];
       }
       check=0xFF-(0x10+0x01+a[0]+a[1]+a[2]+a[3]+s);        //Checksum calculation
       Serial.write(0x7E); //Start Delimiter
       Serial.write(0x00);     // left byte of Length
       Serial.write(0x10);   // Right byte of Length
      
       Serial.write(0x10);     //Frame Type
       Serial.write(0x01);   // Frame ID
       for(p=0;p<=9;p++)   // For loop to send MAC address
       {
           Serial.write(E1_arr[p]);
       }
       Serial.write(0x00);   //Broadcast Radius
       Serial.write(0x00);         // Options
       Serial.write (a[0]);    // RF data which is Stored in array
       Serial.write (a[1]);
       Serial.write (check);
   }  
