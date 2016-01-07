/* Arduino interface to the CM17A Wireless X10 'Firecracker' dongle. 
	BroHogan 7/19/08
	DaveK AC0KG Dec/08
	Hari Wiguna Jan/16
 */

#ifndef X10Firecracker_h
#define X10Firecracker_h
#include <stdint.h>

enum HouseCode { hcA, hcB, hcC, hcD, hcE, hcF, hcG, hcH, 
				 hcI, hcJ, hcK, hcL, hcM, hcN, hcO, hcP };

enum CommandCode { cmdOn, cmdOff, cmdBright, cmdDim };

class X10Firecracker {
public:	
	int RTS_pin;    // RTS line for C17A - DB9 pin 7
	int DTR_pin;    // DTR line for C17A - DB9 pin 4
	int Bit_delay;  // mS delay between bits (0.5mS min.)

	X10Firecracker();
	
	void init( int RTS_Pin, int DTR_Pin, int Bit_Delay );
	void sendCmd(HouseCode house, int device, CommandCode cmnd);
};

extern X10Firecracker X10;

#endif