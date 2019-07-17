/**
 * \file
 *
 * \brief TrustZone secure gateway veneer header file.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifndef _TRUSTZONE_VENEER_H_INCLUDED
#define _TRUSTZONE_VENEER_H_INCLUDED

#include <compiler.h>

/* ======== Non-secure callable common driver functions ======== */

/**
 *  \brief External IRQ settings for EIC
 */
//@{
struct ext_irq_setting {
	uint32_t evctrl;    /** EIC.EVCTRL register value */
	uint32_t config[1]; /** EIC.CONFIG register value */
	uint32_t asynch;    /** EIC.ASYNCH register value */
	uint32_t debouncen; /** EIC.DEBOUNCEN register value */
};
//@}

/**
 * \brief Initialize peripheral clock.
 *
 * \param[in] gclk_id    GCLK ID for the peripheral
 * \param[in] gclk_src   GCLK source for the peripheral
 *
 * \return The status of operation request
 * \retval  0 The operation is completed successfully
 * \retval  1 No operation needed, the peripheral clock is enabled already
 */
extern int32_t nsc_periph_clock_init(uint32_t gclk_id, uint32_t gclk_src);

/**
 * \brief Initialize non-secure external interrupt.
 *
 * \param[in] irq_setting    Non-secure external IRQ settings
 *
 * \return 0 if the operation is completed successfully
 */
extern int32_t nsc_ext_irq_init(struct ext_irq_setting irq_setting);

/* ======== Non-secure callable functions defined by customer ======== */
/* Add your function declaration here */


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
extern void nsc_non_secure_console_puts (uint8_t * string);

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
extern void nsc_SymmetricAuthentication (void);

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
extern bool nsc_IsAuthenticated (void);

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
extern uint8_t nsc_APIInTrustZone (int * temperature);

#endif /* _TRUSTZONE_VENEER_H_INCLUDED */
