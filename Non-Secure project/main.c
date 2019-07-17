

/** @file main.c
 *  @brief main function of the non-secure application
 *
 *	@author Quang Hai Nguyen
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */


#include <atmel_start.h>
#include "trustzone_veneer.h"
#include <stdio.h>


static int temperature;
static char s[100];


int main(void)
{
	
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Verify non-secure application is authenticated */
	nsc_non_secure_console_puts((uint8_t *)"Non-Secure Hello World !\r\n");
	
	/*Try to execute secure function call before authentication*/
	nsc_non_secure_console_puts((uint8_t *)"Verify if sensor node is authenticated\r\n");	
	if(nsc_IsAuthenticated())
	{
		nsc_non_secure_console_puts((uint8_t *)"Authenticated\r\n");
	}
	else
	{
		nsc_non_secure_console_puts((uint8_t *)"Not authenticated\r\n");
	}
	
	/*Execute secure function without authentication*/
	nsc_non_secure_console_puts((uint8_t *)"Try to read the temperature value without sensor node authentication\r\n");
	if(0 == nsc_APIInTrustZone(&temperature))
	{
		sprintf(s, "temperature: %d\r\n", temperature);
		nsc_non_secure_console_puts((uint8_t *)s);
	}
	else
	{
		nsc_non_secure_console_puts((uint8_t *)"Function is not executed\r\n");
	}
	
	/*Authentication and call the secure function again*/
	nsc_non_secure_console_puts((uint8_t *)"Press SW0 to start Authenticate\r\n");
	while(gpio_get_pin_level(SW0));	
	
	nsc_SymmetricAuthentication();
	
	nsc_non_secure_console_puts((uint8_t *)"Verify if sensor node is authenticated\r\n");
	if(nsc_IsAuthenticated())
	{
		nsc_non_secure_console_puts((uint8_t *)"Authenticated\r\n");
	}
	else
	{
		nsc_non_secure_console_puts((uint8_t *)"Not authenticated\r\n");
	}
	
	
	
	/* Replace with your application code */
	while (1) {
		
		nsc_non_secure_console_puts((uint8_t *)"Read out temperature value\r\n");
		if(0 == nsc_APIInTrustZone(&temperature))
		{
			sprintf(s, "temperature: %d\r\n", temperature);
			nsc_non_secure_console_puts((uint8_t *)s);
		}
		else
		{
			nsc_non_secure_console_puts((uint8_t *)"Function is not executed\r\n");
		}
		
		delay_ms(2000);
		
	}
}
