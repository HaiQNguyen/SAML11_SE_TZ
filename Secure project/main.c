/** @file main.c
 *  @brief main file for the secure application
 *
 *  This file content the initialization code for the secure application
 *	and non-secure application.
 *
 *	@author Quang Hai Nguyen
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */


#include <atmel_start.h>
#include "Secure_functions/SecureAuthentication.h"


/* Define section ---------------------------------------------------*/

/* TZ_START_NS: Start address of non-secure application */
#define TZ_START_NS 0x00008000

/* typedef for non-secure callback functions */
typedef void (*ns_funcptr_void) (void) __attribute__((cmse_nonsecure_call));

int main(void)
{
	/* Pointer to Non secure reset handler definition*/
	ns_funcptr_void NonSecure_ResetHandler;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Print Secure Hello world on the terminal window */
	secure_console_puts("\x1b[2J");
	secure_console_puts ("Secure Hello world !\r\n");
	
	/* - Set non-secure main stack (MSP_NS) */
	__TZ_set_MSP_NS(*((uint32_t *)(TZ_START_NS)));
	
	/* - Get non-secure reset handler */
	NonSecure_ResetHandler = (ns_funcptr_void)(*((uint32_t *)((TZ_START_NS) + 4U)));
	
	/* - Start Non-secure Application */
	NonSecure_ResetHandler();
	
	/* Replace with your application code */
	while (1) {
	}
}


