 

#ifndef STATE_H_
#define STATE_H_
typedef enum {
	IDLE_S,
	LEFT_S,
	RIGHT_S,
	W8_S
	}State_type;
	
typedef enum{
	L_B,
	R_B,
	W8_B
	}transition_type;

void Idle(void);
void Left(void);
void Right(void); 
void W8(void);
transition_type Get_transition(void);
#endif /* STATE_H_ */