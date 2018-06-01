#include <openGLCD_Buildinfo.h>
#include <openGLCD.h>
#include <openGLCD_Config.h>
int temp=A5;


void setup()
{
  
  GLCD.Init();
  GLCD.SelectFont(System5x7);
  GLCD.CursorTo(96,0);
  GLCD.print("ABMS FAM!");
  GLCD.CursorTo(96,1);
  GLCD.print("Temperatur");
  GLCD.CursorTo(96,2);
  GLCD.print("Voltage :");
  GLCD.CursorTo(96,3);
  GLCD.print("Current Fl");
  GLCD.CursorTo(0,3);
  GLCD.print("owing ");
  GLCD.CursorTo(96,4);
  GLCD.print("Bat %");
  
}

void loop()
{
  int h=10;
  GLCD.CursorTo(0, 1);
  int p=map(h,1,1023,1,100);
  GLCD.print(h);
}
