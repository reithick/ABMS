void setup() {
  pinMode(A0,INPUT);
 pinMode(A1,INPUT);
 //pinMode(A0,OUTPUT);
 //pinMode(13,OUTPUT);
 Serial.begin(9600);

}


void loop() {
  
float p,j,crr; 
float sum=0; 
float sumi=0;
float chrg=0;
 
for(int i=0;i<1000;i++)
 {
 //   analogWrite(A0,i);
 //digitalWrite(13,HIGH);
 j=analogRead(A0);
  p=analogRead(A1);
 p=(p/1023.0)*5;
 j=(j/1023.0)*5;
 crr=j/(2.2);
 Serial.println(p);
 Serial.println(j);
 Serial.println(j/p,3);
 Serial.println(crr);
 Serial.println("\n");
 //a[i]= j/p;
// Serial.print(i);
// Serial.print("\n");
if(p!=0.00)
sum+=j/p;
 sumi=crr+sumi;
 delay(5);
  }
  
   
   Serial.println("avg of 1000");
   Serial.println(sum/1000);
   Serial.println("avg current through shunt");
   Serial.println(sumi/1000);
   chrg= chrg+(sumi*(5*10));
   Serial.print("Charge through battery in 50000 seconds : ");
   Serial.print(chrg,4);
   Serial.print("*1000");
   //sum=0;
   Serial.print("\n");
   Serial.print("\n");
   delay(10000);
}
