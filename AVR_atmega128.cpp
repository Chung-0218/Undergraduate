#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h> 
#include <util/delay.h>

unsigned char FND_SEG[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
 0x27, 0x7F, 0x6F}; // 0~9까지 10개의 숫자 정의

unsigned char FND_SEGPOS[4]={0x01, 0x02, 0x04, 0x08}; // 4개의 7 segment 정의

volatile unsigned char Index[4] = {0,};

volatile int n1, n2, n3, n4 = 0;

volatile int counter = 0, start = 0, stopsign = 1;

volatile unsigned char rx, tx;

void init_port()  // port 초기화
{
	DDRA = 0xFF; // PORTA의 모든 것들(PA0~PA7)을 출력으로 사용 
	DDRE = 0x0C; // PORTE중 PE2, PE3을 출력으로 사용 
	DDRG = 0x00; // PORTG의 모든 포트를 입력으로 사용 
	PORTA = 0x0F; // PORTA의 모든 포트를 출력으로 사용 
	PORTE = 0x04; // PORTE의 PE2, PE3를 출력으로 사용 
	PORTE = 0x00; // PORTE의 모든 포트를 LOW로 함 
	PORTA = 0x3F; // PORTE의 PE3를 HIGH로 함 
	PORTE = 0x08; // PORTE의 PE3를 HIGH로 함 
	PORTE = 0x00; // PORTE의 모든 포트를 LOW로 함 (0000)
}

void init_interrupt(void) // interrupt 초기화
{
	EIMSK = 0x00; // EIMSK 초기화
	EICRA = 0x00; // interrutp 0~3은 사용X
	EICRB = 0x0A; // INT5를 Falling edge로 하기 위해 2,3번 bit를 각각 0,1로 설정
	EIMSK = 0x30; // interrupt 4, 5번 사용
	EIFR = 0xFF;  // interrupt flag를 모두 1로 설정
}

void init_uart(void) 
{ 
	DDRE = 0x02; // RxD0(=PE0) = Input , TxD0(=PE1) = Output 
	UBRR0H = 0; 
	UBRR0L = 103;  // Baud rate setting 
	UCSR0B = 0x98; // Receive & Transimt enable & Rx interrupt enable
}

void timer_setting() 
{ 
	TCCR0 = 0x01; // No prescale
	TCNT0 = 0x00; // TCNT0를 0으로 해서 0~255 까지 작동하게 함 256 카운트 
	TIMSK = 0x01; // overflow로 작동하게 함 
	TIFR = 0xFF; // flag 초기화
}

void upcount() 
{ 
	n1++; // n1을 1씩 증가시킴 
	if(n1 >= 10) { // n1이 10보다 크거나 같으면 
		n2++;   // n2를 증가시키고
		n1 = 0;    // n1을 0으로 함 
	} 
	if(n2 >= 10) { // n2가 10보다 크거나 같으면 
		n3++;      // n3을 증가시키고 
		n2 = 0;    // n2를 0으로 함 
	} 
	if(n3 >= 10) { // n3이 10보다 크거나 같으면 
		n4++;      // n4를 증가시키고
		n3 = 0;    // n3을 0으로 함 
	}
	if(n4 == 10) { // n4가 10이면 
		n1 = 0, n2 = 0, n3 = 0, n4 = 0; // 네 자리 모두 0으로 함 
	} 
}

void show_segment() 
{ 
	PORTE = 0x04; // LED CTL 
	PORTA = FND_SEGPOS[3]; // 왼쪽에서 4번째 segment에 
	PORTE = 0x08; // LED DATA 
	PORTA = FND_SEG[n1]; // 숫자 표시 
	_delay_us(10); 
	PORTE = 0x04; // LED CTL 
	PORTA = FND_SEGPOS[2]; // 왼쪽에서 3번째 segment에 
	PORTE = 0x08; // LED DATA 
	PORTA = FND_SEG[n2]; // 숫자 표시 
	_delay_us(10);
	PORTE = 0x04; // LED CTL 
	PORTA = FND_SEGPOS[1]; // 왼쪽에서 2번째 segment에
	PORTE = 0x08; // LED DATA 
	PORTA = FND_SEG[n3]+0x80; // 숫자표시, 소수점 표현 때문에 0x08 하나만 계속 켠다 
	_delay_us(10); 
	PORTE = 0x04; // LED CTL 
	PORTA = FND_SEGPOS[0]; // 왼쪽에서 1번째 segment에 
	PORTE = 0x08; // LED DATA 
	PORTA = FND_SEG[n4]; // 숫자 표시 
	_delay_us(10);
}

void reset_segment() { // 모든 자리의 segment를 0으로 리셋함
	PORTE = 0x04;
	PORTA = FND_SEGPOS[3];
	PORTE = 0x08;
	PORTA = FND_SEG[0];
	_delay_us(10);
	PORTE = 0x04;
	PORTA = FND_SEGPOS[2];
	PORTE = 0x08;
	PORTA = FND_SEG[0];
	_delay_us(10);
	PORTE = 0x04;
	PORTA = FND_SEGPOS[1];
	PORTE = 0x08;
	PORTA = FND_SEG[0]+0x80;
	_delay_us(10);
	PORTE = 0x04;
	PORTA = FND_SEGPOS[0];
	PORTE = 0x08;
	PORTA = FND_SEG[0];
	_delay_us(10);
}

void newline(void){
	while((UCSR0A & 0x20) == 0x00); 
	UDR0  = 0x0A;
	while((UCSR0A & 0x20) == 0x00); 
	UDR0  = 0x0D;
}

void printsegment(void)
{ 
	while((UCSR0A & 0x20) == 0x00); 
	UDR0  = Index[0] + 48; // 문자 0과 10진수 0의 차이 48 
	while((UCSR0A & 0x20) == 0x00); 
	UDR0  = Index[1] + 48; 
	while((UCSR0A & 0x20) == 0x00); 
	UDR0  = Index[2] + 48; 
	while((UCSR0A & 0x20) == 0x00); 
	UDR0  = Index[3] + 48; 
}

ISR(TIMER0_OVF_vect) { // 이 함수는 16MHz / 256 = 62500Hz 이고, 1/62500초마다 동작하게 된다
	counter++; // 전역변수 counter를 1씩 증가시킨다
	if (counter == 625) { // counter가 625 이고
		if(start == 0) { // start가 0이면
			start = 1;   // start를 1로 하고
			counter = 0; // counter를 0으로 한다
		}
	}
}

ISR(INT4_vect) { // Interrupt 4 함수(INT4를 누를 때)
	_delay_us(100); // sw bouncing을 막기 위한 delay 
	if(stopsign == 1) { // stopsign이 1이면
		stopsign = 0; // stopsign을 0으로 한다
	}
	else // stopsign이 1이 아니면
		stopsign = 1; // stopsign을 1로 한다
	_delay_us(10); // sw bouncing을 막기 위한 delay
}

ISR(INT5_vect) { // Interrupt 5 함수(INT5를 누를 때)
	_delay_us(100); // sw bouncing을 막기 위한 delay
	reset_segment(); // 모든 segment를 0으로 리셋
	_delay_us(10); // sw bouncing을 막기 위한 delay
}

int main() {
	timer_setting(); // 타이머 세팅
	init_port();     // Port 초기화
	init_interrupt();// Interrupt 초기화
	sei(); // 인터럽트를 받기 위해 씀
	
	PORTE = 0x08; // LED DATA
	while(1) { // 무한 루프
		if(stopsign != 1) { // 앞에서 정의한 stopsign이 1이 아니면		
		show_segment(); 	// segment를 보여줌
			if (start == 1) { // start가 1이면
				upcount();    // upcount를 실행
				start = 0;    // start를 0으로 함
			}
		}		
	}
	return 0;
}
