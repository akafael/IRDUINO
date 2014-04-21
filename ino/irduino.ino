/**
 * Programa para controlar um sistema de irrigação feito em arduino
 * @author Rafael Lima
 * @version 0.23
 */

#include <Time.h>
#include <TimeAlarms.h>
#include <LiquidCrystal.h>    //Biblioteca para Display LCD

#include "irduino.h"

#define BTN_SELECT 642
#define BTN_LEFT 413
#define BTN_RIGHT 0
#define BTN_UP 100
#define BTN_DOWN 259

#define PIN_MOLHAR_JARDIM 13

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte pinoBotao = A0;

int valorBotao = 0;
int opcao_tela = 0;

void setup(){
  Serial.begin(9600);
	setTime(7,59,50,5,6,14); // set time to Saturday 8:29:00am Jan 1 2011
  
  pinMode(PIN_MOLHAR_JARDIM,OUTPUT);

  desligarIrrigacao();
  lcd.clear();

  Alarm.alarmRepeat(8,00,0, acionarIrrigacao);  // 8:00am every day
  Alarm.alarmRepeat(8,05,0, desligarIrrigacao);  // 8:05am every day
}

void loop(){
  valorBotao = analogRead(pinoBotao);
  switch (opcao_tela) {
      case 1:
        menu();
        break;
      default:
        digitalClockDisplay();
        if((valorBotao <= BTN_SELECT)&&((valorBotao > BTN_LEFT)))
          opcao_tela = 1;
        else
          opcao_tela = 0;
        break;
  }
  Alarm.delay(10);
}

/*
 * Funções para controle do módulo relé
 */
void acionarIrrigacao(){
  digitalWrite(PIN_MOLHAR_JARDIM, HIGH);
  Serial.println("Molhando o Jardim");
}

void desligarIrrigacao(){
  digitalWrite(PIN_MOLHAR_JARDIM, LOW);
  Serial.println("Feixando a torneira");
}

/*
 * Funções para Manipulação do display lcd:
 * E menus
 */

void digitalClockDisplay()
{
  // digital clock display of the time
  lcd.setCursor(0,0);
  if(hour()<10)
    lcd.print("     "); // 5c em branco
  else
    lcd.print("    "); // 4c em branco
  lcd.print(hour());
  printDigits(minute());
  printDigits(second());
  lcd.print("    "); // 4c em branco
}

void printDigits(int digits)
{
  lcd.print(":");
  if(digits < 10)
     lcd.print('0');
  lcd.print(digits);
}

void menu(){
  lcd.setCursor(0,1);
  navegarMenu();
  lcd.print(MENU_INICIO);
}

void navegarMenu(){
  valorBotao = analogRead(pinoBotao);
  if(valorBotao <= BTN_RIGHT){
  }else{
    if(valorBotao <= BTN_UP){
    }else{
      if(valorBotao <= BTN_DOWN){
      }else{
        if(valorBotao <= BTN_LEFT){
          opcao_tela = UI_TIME;
        }else{
          if(valorBotao <= BTN_SELECT){
          }
        }
      }
    }
  }
}