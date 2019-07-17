
/** @file SecureAuthentication.c
 *  @brief Contain the secure functions
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

#include "Secure_functions/SecureAuthentication.h" 
#include "cryptoauthlib.h"
#include "atca_host.h"
#include <stdlib.h>

#define CHECK_STATUS(s)										\
if(s != ATCA_SUCCESS) {										\
	printf("status code: 0x%x\r\n", s);						\
	printf("Error: Line %d in %s\r\n", __LINE__, __FILE__); \
	return;													\							
}															\


/* Local variable section --------------------------------------------*/
ATCAIfaceCfg cfg_ateccx08a_i2c_sensor = {
	.iface_type				= ATCA_I2C_IFACE,
	.devtype				= ATECC608A,
	.atcai2c.slave_address	= 0xC2,
	.atcai2c.bus			= 1,
	.atcai2c.baud			= 400000,
	.wake_delay				= 800,
	.rx_retries				= 20,
	.cfg_data              = &I2C_0
};

ATCAIfaceCfg cfg_ateccx08a_i2c_host = {
	.iface_type				= ATCA_I2C_IFACE,
	.devtype				= ATECC508A,
	.atcai2c.slave_address	= 0xC0,
	.atcai2c.bus			= 1,
	.atcai2c.baud			= 400000,
	.wake_delay				= 800,
	.rx_retries				= 20,
	.cfg_data              = &I2C_0
};



/* Local function prototype section ----------------------------------*/

static void print_bytes(uint8_t * ptr, uint8_t length);
bool static authen_status = false;


static void print_bytes(uint8_t * ptr, uint8_t length)
{
	
	uint8_t i = 0;
	uint8_t line_count = 0;
	for(;i < length; i++) {
		printf("0x%02x, ",ptr[i]);
		line_count++;
		if(line_count == 8) {
			printf("\r\n");
			line_count = 0;
		}
	}
	
	printf("\r\n");
}

void secure_console_puts (uint8_t * string)
{
	/* Set display foreground color to green */
	printf("\033[0;32m");
	/* Print string on console */
	printf("%s", string);
}

void non_secure_console_puts (uint8_t * string)
{
	/* Set display foreground color to red */
	printf("\033[0;31m");
	/* Print string on console */
	printf("%s", string);
}

bool IsAuthenticated(void)
{
	return authen_status;	
}


void SymmetricAuthentication(void)
{
	
	//Step 1.1
	/* Set display foreground color to green */
	printf("\033[0;32m");
	printf("Authentication between sensor and host\r\n");
	
	printf("Authentication in progress\r\n");
	volatile ATCA_STATUS status;
	status = atcab_init( &cfg_ateccx08a_i2c_host ); CHECK_STATUS(status);
	printf("Host init complete\r\n");
	

	uint8_t serial_number[ATCA_SERIAL_NUM_SIZE];
	status = atcab_read_serial_number((uint8_t*)&serial_number);
	CHECK_STATUS(status);
	printf("Serial Number of host\r\n");
	print_bytes((uint8_t*)&serial_number, 9); printf("\r\n");
	

	uint8_t nonce[32];
	status = atcab_random((uint8_t*)&nonce);
	CHECK_STATUS(status);
	printf("Random from host\r\n");
	print_bytes((uint8_t*)&nonce, 32);


	status = atcab_init( &cfg_ateccx08a_i2c_sensor );
	CHECK_STATUS(status);
	
	status = atcab_read_serial_number((uint8_t*)&serial_number);
	CHECK_STATUS(status);
	
	printf("Serial Number of sensor\r\n");
	print_bytes((uint8_t*)&serial_number, 9); printf("\r\n");
	

	uint8_t mac[32];
	uint8_t slot = 0; uint8_t mode = (1<<6); // include serial number
	status = atcab_mac(mode, slot, (const uint8_t*)&nonce, (uint8_t*)&mac);
	CHECK_STATUS(status);
	printf("MAC from sensor\r\n");
	print_bytes((uint8_t*)&mac, 32);
	

	status = atcab_init( &cfg_ateccx08a_i2c_host );
	uint8_t otherdata[CHECKMAC_OTHER_DATA_SIZE];
	memset(otherdata, 0x00, CHECKMAC_OTHER_DATA_SIZE);
	otherdata[0] = 0x08;
	otherdata[1] = 0x40;
	otherdata[7] = serial_number[4];
	otherdata[8] = serial_number[5];
	otherdata[9] = serial_number[6];
	otherdata[10] = serial_number[7];
	otherdata[11] = serial_number[2];
	otherdata[12] = serial_number[3];
	mode = 0;
	
	printf("Host verifying MAC from sensor\r\n");
	status = atcab_checkmac(mode, slot, (const uint8_t*)&nonce, (const uint8_t*)&mac, (const uint8_t*)&otherdata);
	
	if(status == ATCA_SUCCESS)
	{
		printf("Authenticated by host\r\n\r\n");
		authen_status = true;
	}
	else
	{
		printf("Failed to authenticate\r\n\r\n");
		authen_status = false;
	}
}

uint8_t APIInTrustZone(int * temperature)
{

	if(authen_status)
	{
		* temperature = 15 + (rand() % 10);
		return 0;
	}
	else
	{	
		return 1; 
	}
	
}
