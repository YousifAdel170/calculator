/******************************************************************************
 * File Name: application.c
 * Description: Simple Calculator [+, -, *, /]
 * Author: Yousif Adel
 *******************************************************************************/
#include	"lcd.h"
#include	"keypad.h"
#include	<util/delay.h>

#define ZERO					0
#define ADDITION_OPERATOR		'+'
#define SUBTRACTION_OPERATOR	'-'
#define MULTIPLY_OPERATOR		'*'
#define DIVISION_OPERATOR		'%'
#define EQUAL					'='
#define CLEAR_BUTTON			13

uint32 result = ZERO;

void calculator(uint8 num1, uint8 num2, uint8 operator)
{
	/* move to next line to display the result */
	LCD_moveCursor(1,0);

	switch(operator)
	{
	case ADDITION_OPERATOR:
		result  = num1 + num2;
		LCD_displayString("Result = ");
		break;
	case SUBTRACTION_OPERATOR:
		result  = num1 - num2;
		LCD_displayString("Result = ");
		break;
	case MULTIPLY_OPERATOR:
		result  = num1 * num2;
		LCD_displayString("Result = ");
		break;
	case DIVISION_OPERATOR:
		if(num2 != 0)
		{
			result  = num1 / num2;
			LCD_displayString("Result = ");
		}
		else
			LCD_displayString("Error!!!!!!!!!!!");
		break;
	default:
		LCD_displayString("Wrong Operator!!!");
		break;
	}
}


int main(void)
{
	/* Initialize The LCD driver */
	LCD_init();

	LCD_displayString("Enter The ");
	LCD_displayStringRowColumn(1,0, "Operation");
	_delay_ms(500);
	LCD_clearScreen();

	/* Initialize the variables to zero */
	uint8 num1 = ZERO, num2 = ZERO, operator = ZERO, key;
	LCD_displayString("Op: ");
	while(1)
	{

		/* gets the input from the keypad */
		key = KEYPAD_getPressedKey();
		_delay_ms(500);	/* Press Time */

		/* check if the user entered number */
		if((key >= 0) && (key <= 9))
		{
			/* Print The first number */
			LCD_intgerToString(key);

			/*Stored it in num2 because we will store num2 in num1 then add the next element in it */
			/* also here we multiply to 10 then add the number because if the number contains multiple digits */
			num2 = (num2 * 10) + key;
		}

		/*check if the user entered operator*/
		else if ((key == ADDITION_OPERATOR) ||
				(key == SUBTRACTION_OPERATOR) ||
				(key == MULTIPLY_OPERATOR) ||
				(key == DIVISION_OPERATOR))
		{
			/* Display The operator */
			LCD_displayCharacter(key);

			/* Save the operator */
			operator = key;
			num1 = num2;		/* Save first number entered into num1 variable */
			num2 = 0;			/* reset the number to store the second number */
		}
		/* This means the user Entered the two numbers and the operator then pressed equal */
		else if(key == EQUAL)
		{

			calculator(num1, num2, operator);
			LCD_intgerToString(result);
		}
		/* Clear Button to clear the LCD & reset the values */
		else if(key == CLEAR_BUTTON)
		{
			LCD_clearScreen();
			num1 = ZERO, num2 = ZERO, operator = ZERO;
			LCD_displayString("Op: ");

		}

	}
}