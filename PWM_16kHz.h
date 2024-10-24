#ifndef PWM_16KHZ_H
#define PWM_16kHz_H

namespace PWM{
	#define PWM1A                   (9)
	#define PWM1B                   (10)
	#define PWM2A                   (11)
	#define PWM2B                   (3)

	void init_16kHz_PWM(void);
	void setDuty(unsigned int, float);
}

#endif