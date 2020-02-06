#include <Wire.h>

byte x = 255;
int temperatura=20;
byte inclinacion = 0;
int vapor;
int volquete;
boolean cambio;

void setup()
{
	Wire.begin();
	pinMode(2,INPUT_PULLUP);
	pinMode(3,INPUT_PULLUP);
	pinMode(4,INPUT_PULLUP);
	pinMode(5,INPUT_PULLUP);
	pinMode(6,INPUT_PULLUP);
	pinMode(13,OUTPUT);
}

void loop()
{
	delay(50);
	digitalWrite(13, LOW);
	cambio = false;
	// Subir
	if (digitalRead(5)==LOW)
	{
		volquete++;
		if (volquete > 5)
		{
			volquete=0;
			if ( inclinacion > 0 )
			{
				inclinacion--;
				cambio=true;
			}
		}
	}
	// Bajar
	if (digitalRead(6)==LOW)  
	{
		volquete++;
		if (volquete > 3)
		{
			volquete=0;
			if ( inclinacion < 250 )
			{
				inclinacion++;
				cambio=true;
			}
		}
	}
	// Vapor
	if (digitalRead(4) == LOW)
	{
		vapor++;
		if (vapor >= 20)
		{
			vapor=0;
			if (temperatura < 255)
			{
				temperatura++;
				cambio=true;
			}
		}
	}
	else
	{
		vapor++;
		if (vapor >= 100)
		{
			vapor=0;
			if (temperatura > 10)
			{
				temperatura--;
			}
		}
	}
	// Agua fria o caliente
	if (digitalRead(3)==LOW)
	{
		if (bitRead(x,0)==0)
		{
			bitSet(x,0);
		}
		else
		{
			bitClear(x,0);
		}
		cambio=true;
	}
	// Desague
	if (digitalRead(2)==LOW)
	{
		vapor++;
		if (vapor >= 5)
		{
			vapor=0; 
			if (temperatura > 10)
			{
				temperatura--;
				cambio=true;
			}
		}
	}
	if ((inclinacion >= 120 ) && (inclinacion <= 140))
	{
		bitClear(x,1);
	}
	else
	{
		bitSet(x,1);
	}
	
	analogWrite(11,temperatura);
	if (cambio)
	{
		delay(50);
		digitalWrite(13, HIGH);
	}
	Wire.beginTransmission(39);
	Wire.write(x);
	Wire.endTransmission();
}
