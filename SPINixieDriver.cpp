#include "SPINixieDriver.h"


SPINixieDriver::SPINixieDriver() {

}

SPINixieDriver::~SPINixieDriver() {
	this->end();
}



void SPINixieDriver::outputEnable(bool value){
	if(this->_outputEnablePin){
		if(value){
			digitalWrite(this->_outputEnablePin, LOW);
		}
		else{
			digitalWrite(this->_outputEnablePin, HIGH);
		}
	}
}

void SPINixieDriver::begin( int rckPin, int clkPin, int dataPin, int outputEnablePin, bool useHardwareSPI ){
	
	this->_useHardwareSPI = useHardwareSPI;
	this->_clkPin = clkPin;
	this->_rckPin = rckPin;
	this->_dataPin = dataPin;
	this->_outputEnablePin = outputEnablePin;
	
	pinMode(outputEnablePin, OUTPUT);
	digitalWrite(outputEnablePin, HIGH);
	
	pinMode(rckPin, OUTPUT);
	digitalWrite(rckPin, LOW);
	
	if(useHardwareSPI){
		SPI.begin();
	}
	
	
	
}


uint16_t SPINixieDriver::decode(uint8_t digit){
	if(digit < 10){
		return ((uint16_t)1)<<digit;
	}
	else{
		return (uint16_t)0x0000;
	}
}

void SPINixieDriver::send(const uint8_t data){
	if(this->_useHardwareSPI){
		digitalWrite(this->_rckPin, LOW);
		SPI.transfer16(this->decode(data));
		digitalWrite(this->_rckPin, HIGH);
	}
}

void SPINixieDriver::end(){
	if(this->_useHardwareSPI){
		SPI.end();
	}
}
	