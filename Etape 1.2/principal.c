# include "gassp72.h"
# include "etat.h"

void timer_callback(void);
int Periode_en_Tck=72000;
int Periode_PWM_en_Tck;
extern short Son[];
extern int LongueurSon;
extern int PeriodeSonMicroSec;
type_etat etat;

int main(void)
{
// config port PB0 pour être utilisé par TIM3-CH3
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
// config TIM3-CH3 en mode PWM
etat.resolution = PWM_Init_ff( TIM3, 3, Periode_PWM_en_Tck );
etat.taille = LongueurSon;
etat.periode_ticks = PeriodeSonMicroSec*72;

short max = Son[0];
short min = Son[0];
for (int i=0; i<LongueurSon; i++) {
	if (Son[i] > max) max = Son[i];
	else if (Son[i] < min) min = Son[i];
}

etat.son = Son;

// activation de la PLL qui multiplie la fréquence du quartz par 9
 CLOCK_Configure();
// initialisation du timer 4
// Periode_en_Tck doit fournir la durée entre interruptions,
// exprimée en périodes Tck de l'horloge principale du STM32 (72 MHz)
Timer_1234_Init_ff( TIM4, Periode_en_Tck );
// enregistrement de la fonction de traitement de l'interruption timer
// ici le 2 est la priorité, timer_callback est l'adresse de cette fonction, a créér en asm,
// cette fonction doit être conforme à l'AAPCS
Active_IT_Debordement_Timer( TIM4, 2, timer_callback );
// lancement du timer
Run_Timer( TIM4 );

while	(1)
	{
	}
} 
