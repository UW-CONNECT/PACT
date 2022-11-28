//******************************************************************************
//   MSP430FR235x Demo - eUSCI_B0, SPI 4-Wire Master multiple byte RX/TX
//
//   Description: SPI master communicates to SPI slave sending and receiving
//   3 different messages of different length. SPI master will enter LPM0 mode
//   while waiting for the messages to be sent/receiving using SPI interrupt.
//   SPI Master will initially wait for a port interrupt in LPM0 mode before
//   starting the SPI communication.
//   ACLK = NA, MCLK = SMCLK = DCO 16MHz.
//
//
//                   MSP430FR2355
//                 -----------------
//            /|\ |             P6.6|-> Comms LED
//             |  |                 |
//             ---|RST          P2.5|-> Slave Reset (GPIO)
//                |                 |
//                |             P1.2|-> Data Out (UCB0SIMO)
//                |                 |
//       Button ->|P4.1         P1.3|<- Data In (UCB0SOMI)
//   Button LED <-|P5.4             |
//                |             P1.1|-> Serial Clock Out (UCB0CLK)
//                |                 |
//                |             P2.4|-> Slave Chip Select (GPIO)
//
//   Xiaodong Li
//   Texas Instruments Inc.
//   May 2020
//   Built with CCS V9.2
//******************************************************************************

#include <msp430.h>
#include <stdint.h>
#include <ax5043.h>

//******************************************************************************
// Pin Config ******************************************************************
//******************************************************************************


#define SLAVE_CS_OUT    P2OUT
#define SLAVE_CS_DIR    P2DIR
#define SLAVE_CS_PIN    BIT4

#define SLAVE_RST_OUT   P2OUT
#define SLAVE_RST_DIR   P2DIR
#define SLAVE_RST_PIN   BIT5



#define COMMS_LED_OUT   P6OUT
#define COMMS_LED_DIR   P6DIR
#define COMMS_LED_PIN   BIT6
//******************************************************************************
// Example Commands ************************************************************
//******************************************************************************

//******************************************************************************
// General SPI State Machine ***************************************************
//******************************************************************************

//******************************************************************************
// Device Initialization *******************************************************
//******************************************************************************

void initSPI()
{
    //Clock Polarity: The inactive state is high
    //MSB First, 8-bit, Master, 3-pin mode, Synchronous
    UCB0CTLW0 = UCSWRST;                       // **Put state machine in reset**
    UCB0CTLW0 |= UCCKPL | UCMSB | UCSYNC
                | UCMST | UCSSEL__SMCLK;      // 3-pin, 8-bit SPI Slave
    UCB0BRW = 0x20;
    //UCB0MCTLW = 0;
    UCB0CTLW0 &= ~UCSWRST;                     // **Initialize USCI state machine**
    UCB0IE |= UCRXIE;                          // Enable USCI0 RX interrupt
}


void initGPIO()
{
    //LEDs
    COMMS_LED_DIR |= COMMS_LED_PIN;
    COMMS_LED_OUT &= ~COMMS_LED_PIN;


    // Configure SPI
    P1SEL0 |= BIT1 | BIT2 | BIT3;


    SLAVE_RST_DIR |= SLAVE_RST_PIN;
    SLAVE_RST_OUT |= SLAVE_RST_PIN;

    SLAVE_CS_DIR |= SLAVE_CS_PIN;
    SLAVE_CS_OUT |= SLAVE_CS_PIN;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;
}

void initClockTo16MHz()
{
    // Configure one FRAM waitstate as required by the device datasheet for MCLK
    // operation beyond 8MHz _before_ configuring the clock system.
    FRCTL0 = FRCTLPW | NWAITS_1;

    __bis_SR_register(SCG0);    // disable FLL
    CSCTL3 |= SELREF__REFOCLK;  // Set REFO as FLL reference source
    CSCTL0 = 0;                 // clear DCO and MOD registers
    CSCTL1 &= ~(DCORSEL_7);     // Clear DCO frequency select bits first
    CSCTL1 |= DCORSEL_5;        // Set DCO = 16MHz
    CSCTL2 = FLLD_0 + 487;      // set to fDCOCLKDIV = (FLLN + 1)*(fFLLREFCLK/n)
                                //                   = (487 + 1)*(32.768 kHz/1)
                                //                   = 16 MHz

    __delay_cycles(3);
    __bic_SR_register(SCG0);                        // enable FLL
    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1));      // FLL locked
}



//******************************************************************************
// Main ************************************************************************
// Send and receive three messages containing the example commands *************
//******************************************************************************

void set_timer_sleep (unsigned long time)
{
    //Start timer for a small delay and go into LPM3
    TB0CTL = TBCLR;
    TB0CCR0 = time;                             // set delay
    TB0CTL = ID__1 | TBSSEL__ACLK | MC__UP;
    __bis_SR_register(LPM4_bits | GIE);         // Enter LPM3 w/ interrupt
    TB0CTL = TBCLR;
}


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    TB0CCTL0 |= CCIE;
    P1DIR |= BIT0;                                // P1.0 output
    P1OUT |= BIT0;                                // P1.0 high

    initClockTo16MHz();
    initGPIO();
    initSPI();


    ax5043_reset();
    ax5043_radio_setup_tx();
    ax5043_pll_ranging();

    uint8_t Transmit[1]={0x00};

    int i;
    for (i=0;i<500;i++)
    {
        ax5043_transmit(Transmit,1);
        P1OUT ^= BIT0;
        set_timer_sleep(1500);
    }


    return 0;
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void TB0_ISR(void) {
    __bic_SR_register_on_exit(LPM4_bits | GIE);
}
