int con12 = 2;
int checkvolt = A4;
int opamp= A5;
int curr12 = A3;
int woab = 4;
int wab1 = 5;
int wab2 = 3;
int a= 9;
int b= 8;
int mux= A2;
//float a;
float varVolt = 1.95637657122904E-05;  // variance determined using excel and reading samples of raw sensor data
float varProcess = 1e-9;// need to be checked by estimation;
float Pc = 0.0;
float G = 0.0;
float T = 1.0;
float Xp = 0.0;
float Zp = 0.0;
float Xe = 0.0;
float tchrg=400.0;
float millproc=0.0;
float rshunt=3.2;
float millproc1=0.0;
float SOC=0.0;
int i=1;
float s;
int dischargecheck = A1;
//float a1,b1;
float a1= 4.09;//bat1positive() - bat1negative();
float b1=3.58;
void currentsensing()
{
  float p; 
 p=analogRead(opamp);
 p=(p/1023.0)*5;
 Pc = T + varProcess;
 G = Pc/(Pc + varVolt);    // kalman gain
 T = (1-G)*Pc;
 Xp = Xe;
 Zp = Xp;
 Xe = G*(p-Zp)+Xp;
 Serial.print("Filtered opamp output Voltage : ");
 Serial.println(Xe*1.0,3);
 float i= Xe/(102*rshunt) ;
 Serial.print("Shunt Voltage : ");
 Serial.println(Xe*1.0/102,3);
 tchrg= tchrg+(i*(millis()-millproc))/3600.0 ;
 Serial.print("Charge out of the cell(mAh): ");
 Serial.println(tchrg,3);
 
 SOC= (1426.0-tchrg)/14.26 ;
 Serial.print("State of Charge:");
 Serial.print(SOC,2);
 Serial.println("%");
 //delay(1000);

}

float bat1positive() {
 digitalWrite(a,HIGH);
 digitalWrite(b,LOW);
 delay(2);
 return analogRead(mux);
}

float bat1negative() {
 digitalWrite(a,HIGH);
 digitalWrite(b,HIGH);
 delay(2);
 return analogRead(mux);
}


float bat2positive() {
 digitalWrite(a,LOW);
 digitalWrite(b,HIGH);
 delay(2);
 return analogRead(mux);
}

float bat2negative() {
 digitalWrite(a,LOW);
 digitalWrite(b,LOW);
 delay(2);
 return analogRead(mux);
}


void CheckLow(int x,int y) {
 if(x<=y) {
     digitalWrite(wab1,HIGH);
   }
   else {
     digitalWrite(wab2,HIGH);
   }
 }

void tux()
{
 a1= 4.09;//bat1positive() - bat1negative();
 b1=3.58;//bat2positive() - bat2negative();
millproc1=millis();

CheckLow(a,b);
delay(1000);
}
 
void activecellbalancing()
{ 
  digitalWrite(woab,LOW);
  if(i==1)
  {
    tux();
    i++;
  }
  if((float)millis()-millproc1 > 300000 )
  {
    tux();
  }
  
  currentsensing();
}

void withoutactivecellbalancing()
{
  digitalWrite(woab,HIGH);
  digitalWrite(wab1,LOW);
  digitalWrite(wab2,LOW);
  float t=bat1negative();
  float k=analogRead(curr12);
  float s=bat2negative();
  t=(t*5)/1023;
  k=(k*5)/1023;
  s=(s*5)/1023;
  tchrg-=((t-k)*(millis()-millproc)/3600);
  Serial.println(tchrg);
  tchrg=tchrg-(s*(millis()-millproc)/3600);
  millproc=millis();
  SOC= (1426.0-tchrg)/14.26 ;
 Serial.print("State of Charge:");
 Serial.print(SOC,2);
 Serial.println("%");
}

void dischargecharge()
{
  withoutactivecellbalancing();
  digitalWrite(con12,LOW);
}

void charge()
{
  withoutactivecellbalancing();
  digitalWrite(con12,LOW);
  
}

void discharge()
{
  digitalWrite(con12,HIGH);
  activecellbalancing();
}

void setup() {
 pinMode(con12,OUTPUT);
 pinMode(checkvolt,INPUT);
 pinMode(dischargecheck,INPUT);
 pinMode(curr12,INPUT);
 pinMode(opamp,INPUT);
  pinMode(a,OUTPUT);
 pinMode(b,OUTPUT);
 pinMode(mux,INPUT);
 pinMode(woab,OUTPUT);
 pinMode(wab1,OUTPUT);
 pinMode(wab2,OUTPUT);
 Serial.begin(9600);

}



void loop() {
  //digitalWrite(woab,LOW);
//delay(1000);
float m=analogRead(checkvolt);
float s=analogRead(A1);
//Serial.println(m);
//Serial.println(s);
//Serial.println(bat1positive());
//a=analogRead(soc);

if(m<1000 && s>100 )
{
discharge();
Serial.println("discharge");
}

if(m>1000 && s<100.00)
  {
    charge();
    Serial.println("charge");
  }
if(m>1000 && s>100.00)
  {
    dischargecharge();
    Serial.println("dischargecharge");
  } 
  if(m<1000 && s<100)
  {
    discharge(); 
  Serial.println("Sleep");
  }
delay(1000);

Serial.print("bat1= ");
Serial.println((float)a1);
Serial.print("bat2= ");
Serial.println((float)b1);
}


