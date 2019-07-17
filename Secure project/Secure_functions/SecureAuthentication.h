

/** @file SecureAuthentication.h
 *  @brief Contain the header of secure functions
 *
 *	These function can be call directly by the secure application
 *	or indirectly thru a veneer table by the non-secure application
 *
 *	@author Quang Hai Nguyen
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */

#ifndef SECUREAUTHENTICATION_H_
#define SECUREAUTHENTICATION_H_

#include <atmel_start.h>


/**
 *  @brief Print text on the terminal
 *
 *	Text will be in green to indicate that it is coming from secure world
 *
 *	@param	string	string to be displayed	
 *	
 *	@return	NULL	always return
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
void secure_console_puts (uint8_t * string);


/**
 *  @brief Print text on the terminal
 *
 *	Text will be in red to indicate that it is coming from non-secure world
 *
 *	@param	string	string to be displayed	
 *	
 *	@return	NULL	always return
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
void non_secure_console_puts (uint8_t * string);

/**
 *  @brief Start authentication process
 *
 *	the underlying process is the challenge and
 *	response between 2 ATECC508
 *	the two ATECC508 are required to be provisioned before using 
 *	
 *	
 *	@return	NULL	always return
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
void SymmetricAuthentication(void);


/**
 *  @brief Return the authentication status
 *
 *	It allows the application in the non-secure world 
 *	to check if it need to runs the authentication process
 *
 *	
 *	@return	true if it is already authenticated, otherwise false
 *
 *	@date	29.05.2019 - initial 
 *
 *  @bug No known bugs.
 */
bool IsAuthenticated(void);



/**
 *  @brief Simulate the protected API 
 *
 *	it is just a sum function. Before the summation, it verify if 
 *	the authentication process is successful 
 *
 *	@param	temperature		parameter to store temperature value							
 *
 *	@return	function status
 *
 *	@date	29.05.2019 - initial
 *  @date	17.07.2019 - modify from a sum function to a random function 
 *
 *  @bug No known bugs.
 */
uint8_t APIInTrustZone(int * temperature);

#endif /* SECUREAUTHENTICATION_H_ */