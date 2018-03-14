#include "DB_CG_scale.h"

void changeValue(int button,float *value, float adj)
{
  switch (button)
  {
    case BUTTON2:
      *value += adj;
      break;
    case BUTTON3:
      *value -= adj;
      break;
  }
}

int OptionHandler::handle(int button, I2C_LCD lcd, HX711 *frontCell, HX711 *rearCell, EepromValues *eepromValues) {
  static int step = 0;
    
  if (status == WAITING)
  {
    status = WORKING;
    step = 0;
  }
  switch (step) {
    case 0:
      lcd.printrow(0, "Change options?");
      lcd.printrow(1, "Btn 1 = Yes");
      if ((button == BUTTON2) || (button == BUTTON3)) {
          status = WAITING;
          return MAIN_ID;
      }
      break;
    case 1:
      lcd.printrow(0, "Span Dist. 1's");
      lcd.printrow(1, String(eepromValues->spanDistance,2));
      changeValue(button, &eepromValues->spanDistance, 1.0);
      break;
    case 2:
      lcd.printrow(0, "Span Dist. .1's");
      lcd.printrow(1, String(eepromValues->spanDistance,2));
      changeValue(button, &eepromValues->spanDistance, 0.1);
      break;
    case 3:
      lcd.printrow(0, "Span Dist. .01's");
      lcd.printrow(1, String(eepromValues->spanDistance,2));
      changeValue(button, &eepromValues->spanDistance, 0.01);
      break;
    case 4:
      lcd.printrow(0, "Peg Dist. 1's");
      lcd.printrow(1, String(eepromValues->pegDistance,2));
      changeValue(button, &eepromValues->pegDistance, 1.0);
      break;
    case 5:
      lcd.printrow(0, "Peg Dist. .1's");
      lcd.printrow(1, String(eepromValues->pegDistance,2));
      changeValue(button, &eepromValues->pegDistance, 0.1);
      break;
    case 6:
      lcd.printrow(0, "Peg Dist. .01's");
      lcd.printrow(1, String(eepromValues->pegDistance,2));
      changeValue(button, &eepromValues->pegDistance, 0.01);
      break;
    // set units of measure
    case 7:
      lcd.printrow(0, "Btn 1 = Grams");
      lcd.printrow(1, "Btn 2 = Ounces");
      switch (button)
      {
        case BUTTON1:
          eepromValues->gramsOuncesFactor = 1;
          step++;
          break;
        case BUTTON2:
          eepromValues->gramsOuncesFactor = 0.035274;
          step++;
          break;
      }
      break;
      
    default:
      lcd.printrow(0, "Saving values ...");
      lcd.printrow(1, "");
      Eeprom::putValues(*eepromValues);
      delay(500);
      status = WAITING;
      return MAIN_ID;
      break;
  }

  switch (button) {
    case BUTTON1:
      step++;
      break;
  }
  return OPTION_ID;
}

