
	thumb

TIM3_CCR3	equ	0x4000043C	; adresse registre PWM

	area  	moncode, code, readonly
	export 	timer_callback
	get	etat.inc
;		
timer_callback	proc
	
	endp
;
	end
