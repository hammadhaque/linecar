//****************************************************************
//************* Embedded Systems Classes, Dr. Bassem Alhalabi
//************* Line Following Car Project
//************* December 13, 2017
//************* Florida Atlantic University
//****************************************************************

#include <msp430.h>
unsigned char counter = 0;
int i=0;
int ADCReading [5];
int leftsensor=0;
int rightsensor=0;
int mainleft=0;
int mainright=0;
int count = 0;

// Function Prototypes
void ConfigureAdc(void);
void getanalogvalues();


int main(void)
{

    WDTCTL = WDTPW + WDTHOLD;                   // Stop WDT
    P1OUT = 0;
    P2OUT = 0;
   // P1IES &= ~BIT6;
    //P1IFG &= ~BIT6;
    //P1IE |=  BIT6;
    P1REN = 0;
    P2REN = 0;
    P1DIR |= ( BIT4 | BIT5| BIT7);             // set bits 4, 5, 7 as outputs
    P1DIR |= (BIT3 | BIT6);                    //bit 3 and bit 6 are also outputs
    P2DIR |= (BIT0 | BIT1 );                   // set bit  0, 1    as outputs
    ConfigureAdc();                            // reading the ADC values from the line sensor
    __delay_cycles(250);
    getanalogvalues();
    __delay_cycles(250);



for (;;)
{
        //reading leftsensors and rightsensor values repeatedly at the beginning of the main loop
        getanalogvalues();
        mainleft = leftsensor;
        mainright = rightsensor;

        if(mainleft<=790) //THIS IS BLACK IS SENSED == ON
        {
               P1OUT &=~BIT4;
               P1OUT |= BIT5;
        }
        else if(mainleft>=850) //if the values of the mainleft is greater than 850, one of the motors are turned off
        {       P1OUT &= ~BIT4;
                P1OUT &= ~BIT5;
        }
        if(mainright <=650)
        {
        
            P1OUT &= ~BIT3;
            P1OUT |= BIT7;
        }
        else if(mainright>=850)
        {
            P1OUT &= ~BIT3; //TWO STATEMENTS TURN OFF THE LEFT MOTOR
            P1OUT &= ~BIT7;
        }
}

TACTL = TASSEL_2|ID_3|MC_3|TAIE;
TACCR0 = 62500;

 _enable_interrupts();

BIS_SR(LPM4_bits + GIE); // enable GPIO interrupts and send into LPM4
for(;;);
}

void ConfigureAdc(void)
{
   ADC10CTL1 = INCH_1 | CONSEQ_1;             // A2 + A1 + A0, single sequence
   ADC10CTL0 = ADC10SHT_2 | MSC | ADC10ON;
   while (ADC10CTL1 & BUSY);
   ADC10DTC1 = 0x02;                      // 3 conversions
   ADC10AE0 |= (BIT0 | BIT1);              // ADC10 option select
}

void getanalogvalues()
{
i = 0;leftsensor =0; rightsensor=0; // set all analog values to zero
  for(i=1; i<=5 ; i++)                          // read all three analog values 5 times each and average
  {
    ADC10CTL0 &= ~ENC;
     while (ADC10CTL1 & BUSY);                         //Wait while ADC is busy
    ADC10SA = (unsigned)&ADCReading[0];           //RAM Address of ADC Data, must be reset every conversion
    ADC10CTL0 |= (ENC | ADC10SC);                     //Start ADC Conversion
    while (ADC10CTL1 & BUSY);                         //Wait while ADC is busy
    leftsensor += ADCReading[0];
    rightsensor +=ADCReading[1];
  }
   leftsensor= leftsensor/5; rightsensor= rightsensor/5 ;    // Average the 5 reading for the three variables
}


#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    __bic_SR_register_on_exit(CPUOFF);
}

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR() {
  if ((P1IFG & BIT6) == BIT6) { // if motion sensed
    P1IFG &= ~BIT6; // clear interrupt flag
    P1OUT &= ~BIT2; // toggle LED1
     }
  else {
    P1IFG = 0; // clear all other flags to prevent infinite interrupt loops
  }
}



