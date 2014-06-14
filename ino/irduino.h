/**
 * Arquivo de configurações
 */

// Textos usados
#define LINHA_APAGADA       "                "
#define MENU_INICIO         "<     Menu      "
#define MENU_SET_TIME       ". AJUSTAR HORA  "
#define MENU_SET_TIME_HOUR	".. AJUSTE HORA  "
#define MENU_SET_TIME_MIN	".. AJUSTE MIN   "
#define MENU_SET_TIME_SEC	".. AJUSTE SEC   "
#define ALERTA_MOLHANDO		"  ..Molhando..  "

#define UI_TIME 			0
#define UI_WATER			1

// Definições do Menu Principal
#define UI_MENU 			127
#define NUM_OPTIONS_MENU	2

// Definições do submenu para ajustar a hora:
#define UI_SET_TIME 		128
#define UI_SET_TIME_HOUR 	129
#define UI_SET_TIME_MIN		130
#define UI_SET_TIME_SEC		131

// Macros para ajudar no uso dos botões
#define BTN_SELECT 642
#define BTN_LEFT 413
#define BTN_DOWN 259
#define BTN_UP 110
#define BTN_RIGHT 0

#define BTN_SELECT_PRESSED (valor_Botao >=BTN_SELECT)
#define BTN_LEFT_PRESSED (valor_Botao <BTN_SELECT)&&(valor_Botao >=BTN_LEFT)
#define BTN_RIGHT_PRESSED (valor_Botao <BTN_SELECT)&&(valor_Botao >=BTN_LEFT)
