// setup used board
#ifndef CREDENTIALS
#define CREDENTIALS
#define UNO
//#define D1R32

// setup motor pins
#if defined(UNO)
	#define PWM_L 10
	#define PWM_R 9
	#define DIR_L 8
	#define DIR_R 7

#elif defined(D1R32)
	#define PWM_L 5 
	#define PWM_R 13
	#define DIR_L 12
	#define DIR_R 14

#else
	#error "Unknown board defininition, please provide pinout for board engine"
#endif


#endif // CREDENTIALS
