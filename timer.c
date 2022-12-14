#include "stm32f7xx.h"
#include "timer.h"

void init_TIMER8(void)
{
	//	Вкл. тактирования
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;

	//	НастраиваемЖ
	//	Предделитель:1
	//	Максимальный счет: 1079 (100кГц)

	TIM8->PSC=0;
	TIM8->ARR = 216000000/100000/2;//	init_GPIO_Output(GPIOD, 1);
	
	//	Регистр савнения: 540(50% заполнение)
	TIM8->CCR1 = TIM8->ARR/2; //	регистр сравнения CCR1  число с которым сравниваетс счетчик
	
	//	Симметричный счет (режим 2)
	TIM8->CR1|= TIM_CR1_CMS_1;			// режим симетричного счета до ARR

	TIM8->CCER|= TIM_CCER_CC1E;// включить канал сравнения, полярность если надо
	
	//	Режим ЩИМ 1
	TIM8->CCMR1|= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // выставить 0110
	
	//Включить буферизацию
	TIM8->CCMR1|= TIM_CCMR1_OC1PE;
	
	//	Вкл физический канал выхода.
	TIM8->BDTR|= TIM_BDTR_MOE;//
	
	//	Вкл. счет таймера.
	TIM8->CR1|= TIM_CR1_CEN;

}

