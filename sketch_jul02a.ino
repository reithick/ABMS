float varVolt = 1.95637657122904E-05;  // variance determined using excel and reading samples of raw sensor data

float varProcess = 1e-9;// need to be checked by estimation;

float Pc = 0.0;

float G = 0.0;

float T = 1.0;

float Xp = 0.0;

float Zp = 0.0;

float Xe = 0.0;

void setup() {

  pinMode(A0,INPUT);  

 pinMode(A1,INPUT);

 Serial.begin(9600);

}

void loop() {

  

 float p; 

 p=analogRead(A1);

 

 p=(p/1023.0)*5;

 

 Pc = T + varProcess;

 G = Pc/(Pc + varVolt);    // kalman gain

 

 T = (1-G)*Pc;

 Xp = Xe;

 Zp = Xp;

 Xe = G*(p-Zp)+Xp;

 Serial.print(Xe*1000.0,3);

 Serial.print(" ");

 

 Serial.println(p*1000.0,3);

 

 delay(5);

}
