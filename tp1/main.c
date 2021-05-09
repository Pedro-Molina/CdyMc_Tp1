#include <avr/io.h> // Registros del microcontrolador
#define F_CPU 8000000UL // Defino la frecuencia de oscilador en 8MHz
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
	DDRD = 0xff;//configuro el PORTB para todo salida
	int aux = 0;// inicializo variable auxiliar
	DDRC = 0b11111110;//configuro el pin0 del port C para entrada
	PORTC = 1<<PINC0;//activo resitencia pull-up
	PORTD = 1<<PINC0;//inicializo PORTB
	while (1)
	{
		if ((PINC & (1<<PINC0)) == 0)//si hay un cero en el bit 0 del PINC (boton presionado)
		{
			_delay_ms(20);//retardo para contrarrestar el efecto rebote
			while ((PINC & (1<<PINC0)) == 0)//mientras siga en cero (hasta que se suelte el boton)
			{
			}
			_delay_ms(20);//retardo para contrarrestar el efecto rebote
			aux= aux+1;//incremento variable auxiliar para conocer el sentido de la secuencia
		}else
		{
			if (aux % 2 == 1)//si estoy en la secuencia hacia la izquierda
			{
				if ((PORTD & (1<<PIND7)) == 0 )//no llego al final de la secuencia
				{
					PORTD = PORTD<<1;//desplazo el valor del portB a la izquierda
				}else//llego al final de la secuencia
				{
					PORTD= 0b00000001;//reinicializo el valor del port B
				}
			}else //si estoy en la secuencia hacia la derecha
			{
				if ((PORTD & (1<<PINC0)) == 0 )//no llego al final de la secuencia
				{
					PORTD = PORTD>>1;//desplazo el valor del portB a la derecha
				}else//llego al final de la secuencia
				{
					PORTD= 0b10000000;//reinicializo el valor del port B
				}
			}
			_delay_ms(10000);//retardo para la visualizacion
		}
	}
}