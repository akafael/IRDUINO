/**
 * Programa para controlar um sistema de irrigação feito em arduino
 * @author Rafael Lima
 * @version 0.33
 */

#include <Time.h>
#include <TimeAlarms.h>
#include <LiquidCrystal.h>    //Biblioteca para Display LCD

#include "irduino.h"

#define PIN_MOLHAR_JARDIM 12
#define PIN_BACKLIGHT     10

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte pinoBotao = A0;

int valorBotao = 0;
int opcao_tela = 0;

void setup(){
  Serial.begin(9600);
	setTime(6,59,30,2,6,14);
  
  pinMode(PIN_MOLHAR_JARDIM,OUTPUT);
  pinMode(PIN_BACKLIGHT,OUTPUT);
  digitalWrite(PIN_BACKLIGHT, LOW);

  desligarIrrigacao();
  lcd.begin(16, 2);    //Definindo o LCD com 16 colunas e 2 linhas
  lcd.clear();
  lcd.setCursor(0, 0); //Definindo o cursor na posição inicial do LCD

  Alarm.alarmRepeat(7,00,0, acionarIrrigacao);  // 7:00am every day
  Alarm.alarmRepeat(7,01,0, desligarIrrigacao);  // 7:01am every day

  Alarm.alarmRepeat(12,00,0, acionarIrrigacao);  // 12:00am every day
  Alarm.alarmRepeat(12,01,0, desligarIrrigacao);  // 12:01am every day

  Alarm.alarmRepeat(18,00,0, acionarIrrigacao);  // 6:00pm every day
  Alarm.alarmRepeat(18,01,0, desligarIrrigacao);  // 6:01pm every day
}

void loop(){
  valorBotao = analogRead(pinoBotao);
  switch (opcao_tela) {
      case UI_MENU:
        menu();
        break;
      case UI_WATER:
        lcdDigitalClockDisplay();
        lcd.setCursor(0, 1);
        lcd.print(ALERTA_MOLHANDO);
        break;
      case UI_SET_TIME:
        navergarMenuHora();
        break;
      case UI_SET_TIME_HOUR:
        MenuHora_AjusteHora();
        break;
      case UI_SET_TIME_MIN:
        MenuHora_AjusteMin();
        break;
      case UI_SET_TIME_SEC:
        MenuHora_AjusteSec();
        break;
      case UI_TIME:
      default:
        lcdDigitalClockDisplay();
        if((valorBotao <= BTN_SELECT)&&((valorBotao > BTN_LEFT)))
          opcao_tela = UI_MENU;
        else
          opcao_tela = UI_TIME;
        break;
  }
  Alarm.delay(100);
}

/*
 * Funções para controle do módulo relé
 */
void acionarIrrigacao(){
  digitalWrite(PIN_MOLHAR_JARDIM, HIGH);
  digitalWrite(PIN_BACKLIGHT, HIGH);
  Serial.println("Molhando o Jardim");
  opcao_tela = UI_WATER;
}

void desligarIrrigacao(){
  digitalWrite(PIN_MOLHAR_JARDIM, LOW);
  digitalWrite(PIN_BACKLIGHT, LOW);
  Serial.println("Feixando a torneira");
  lcd.setCursor(0, 1);
  lcd.print(LINHA_APAGADA);
  opcao_tela = UI_TIME;
}


/*
 * Funções para Manipulação do display lcd:
 * E menus
 */

void lcdDigitalClockDisplay()
{
  // digital clock display of the time
  lcd.setCursor(0,0);
  if(hour()<10)
    lcd.print("     "); // 5c em branco
  else
    lcd.print("    "); // 4c em branco
  lcd.print(hour());
  lcdPrintDigits(minute());
  lcdPrintDigits(second());
  lcd.print("    "); // 4c em branco
}

void lcdDigitalsetTimeDisplay()
{
  // digital clock display of the time
  lcd.setCursor(0,0);
  if(hour()<10)
    lcd.print("-    "); // 5c em branco
  else
    lcd.print("-   "); // 4c em branco
  lcd.print(hour());
  lcdPrintDigits(minute());
  lcdPrintDigits(second());
  lcd.print("   -"); // 4c em branco
}

void lcdPrintDigits(int digits)
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
        opcao_tela = UI_SET_TIME;
      }else{
        if(valorBotao <= BTN_LEFT){
          lcd.setCursor(0,1);
          lcd.print(LINHA_APAGADA);
          opcao_tela = UI_TIME;
        }else{
          if(valorBotao <= BTN_SELECT){
            // do something
          }
        }
      }
    }
  }
}

void navergarMenuHora(){
  lcdDigitalClockDisplay();
        lcd.setCursor(0, 1);
        lcd.print(MENU_SET_TIME);
        if(valorBotao <= BTN_UP){
          opcao_tela = UI_MENU;
        }else{
          if(valorBotao <= BTN_SELECT){
            opcao_tela = UI_SET_TIME_HOUR;
          }
        }
}

void MenuHora_AjusteHora(){
  lcdDigitalsetTimeDisplay();
  lcd.setCursor(0, 1);
  lcd.print(MENU_SET_TIME_HOUR);
  if(valorBotao<=BTN_RIGHT){
    opcao_tela = UI_SET_TIME_MIN;
  }else{
    if(valorBotao <= BTN_UP){
      setTime(hour()+1, minute(), second(), day(), month(), year());
      Alarm.delay(500);
    }else{
      if(valorBotao <= BTN_DOWN){
        setTime(hour()-1, minute(), second(), day(), month(), year());
        Alarm.delay(500);
      }else{
        if(valorBotao <= BTN_LEFT){
            opcao_tela = UI_SET_TIME_SEC;
        }else{
          if(valorBotao <= BTN_SELECT){
            opcao_tela = UI_SET_TIME;
          }
        }
      }
    }
  }
}

void MenuHora_AjusteMin(){
  lcdDigitalsetTimeDisplay();
  lcd.setCursor(0, 1);
  lcd.print(MENU_SET_TIME_MIN);
  if(valorBotao<=BTN_RIGHT){
    opcao_tela = UI_SET_TIME_SEC;
  }else{
    if(valorBotao <= BTN_UP){
      setTime(hour(), minute()+1, second(), day(), month(), year());
      Alarm.delay(500);
    }else{
      if(valorBotao <= BTN_DOWN){
        setTime(hour(), minute()-1, second(), day(), month(), year());
        Alarm.delay(500);
      }else{
        if(valorBotao <= BTN_LEFT){ 
            opcao_tela = UI_SET_TIME_HOUR;
        }else{
          if(valorBotao <= BTN_SELECT){
            opcao_tela = UI_SET_TIME;
          }
        }
      }
    }
  }
}

void MenuHora_AjusteSec(){
  lcdDigitalsetTimeDisplay();
  lcd.setCursor(0, 1);
  lcd.print(MENU_SET_TIME_SEC);
  if(valorBotao<=BTN_RIGHT){
    opcao_tela = UI_SET_TIME_HOUR;
  }else{
    if(valorBotao <= BTN_UP){
      setTime(hour(), minute(), second()+1, day(), month(), year());
      Alarm.delay(500);
    }else{
      if(valorBotao <= BTN_DOWN){
        setTime(hour(), minute(), second()-1, day(), month(), year());
        Alarm.delay(500);
      }else{
        if(valorBotao <= BTN_LEFT){ 
          opcao_tela = UI_SET_TIME_MIN;
        }else{
          if(valorBotao <= BTN_SELECT){
            opcao_tela = UI_SET_TIME;
          }
        }
      }
    }
  }
}
