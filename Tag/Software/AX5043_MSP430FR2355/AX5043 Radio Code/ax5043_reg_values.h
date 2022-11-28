#define AX_STATUS_POWER_READY				(1 << 15)
#define AX_STATUS_PLL_LOCK					(1 << 14)
#define AX_STATUS_FIFO_OVERFLOW				(1 << 13)
#define AX_STATUS_FIFO_UNDERFLOW			(1 << 12)
#define AX_STATUS_THRESHOLD_FREE			(1 << 11)
#define AX_STATUS_THRESHOLD_COUNT			(1 << 10)
#define AX_STATUS_FIFO_FULL					(1 << 9)
#define AX_STATUS_FIFO_EMPTY				(1 << 8)
#define AX_STATUS_PWRGOOD					(1 << 7)
#define AX_STATUS_PWR_INTERRUPT_PENDING		(1 << 6)
#define AX_STATUS_RADIO_EVENT_PENDING		(1 << 5)
#define AX_STATUS_XTAL_OSCILLATOR_RUNNING	(1 << 4)
#define AX_STATUS_WAKEUP_INTERRUPT_PENDING	(1 << 3)
#define AX_STATUS_LPOSC_INTERRUPT_PENDING	(1 << 2)
#define AX_STATUS_GPADC_INTERRUPT_PENDING	(1 << 1)

/**
 * Revision
 */
#define AX_SILICONREVISION	0x51

/**
 * Scratch
 */
#define AX_SCRATCH			0xC5

/**
 * Power Mode
 */
#define AX_PWRMODE_POWERDOWN	0  /* 400nA */
#define AX_PWRMODE_DEEPSLEEP	1  /* 50nA */
#define AX_PWRMODE_STANDBY	5  /* 230µA */
#define AX_PWRMODE_FIFOON	7  /* 310µA */
#define AX_PWRMODE_SYNTHRX	8  /* 5mA */
#define AX_PWRMODE_FULLRX	9  /* 7-11mA */
#define AX_PWRMODE_WORRX	11 /* 500nA */
#define AX_PWRMODE_SYNTHTX	12 /* 5mA */
#define AX_PWRMODE_FULLTX	13 /* 6-70mA */

#define AX_PWRMODE_WDS		(1 << 4) /* Wakeup from Deep Sleep */
#define AX_PWRMODE_REFEN	(1 << 5) /* Power to internal reference */
#define AX_PWRMODE_XOEN		(1 << 6) /* Crystal Oscillator Enable */
#define AX_PWRMODE_RST		(1 << 7) /* Reset */

/**
 * Power Status
 */
#define AX_POWSTAT_SVIO		(1 << 0) /* IO Voltage Large Enough (not Brownout) */
#define AX_POWSTAT_SBEVMODEM	(1 << 1) /* Modem Domain Voltage Brownout Error (Inverted) */
#define AX_POWSTAT_SBEVANA	(1 << 2) /* Analog Domain Voltage Brownout Error (Inverted) */
#define AX_POWSTAT_SVMODEM	(1 << 3) /* Modem Domain Voltage Regulator Ready */
#define AX_POWSTAT_SVANA	(1 << 4) /* Analog Domain Voltage Regulator Ready */
#define AX_POWSTAT_SVREF	(1 << 5) /* Reference Voltage Regulator Ready */
#define AX_POWSTAT_SREF		(1 << 6) /* Reference Ready */
#define AX_POWSTAT_SSUM		(1 << 7) /* Summary Ready Status */

/**
 * Interrupt Control
 */
#define AX_IRQMFIFONOTEMPTY	(1 << 0) /* FIFO not empty interrupt */
#define AX_IRQMFIFONOTFULL	(1 << 1) /* FIFO not full interrupt */
#define AX_IRQMFIFOTHRCNT	(1 << 2) /* FIFO count > threshold interrupt */
#define AX_IRQMFIFOTHRFREE	(1 << 3) /* FIFO free > threshold interrupt */
#define AX_IRQMFIFOERROR	(1 << 4) /* FIFO error interrupt */
#define AX_IRQMPLLUNLOCK	(1 << 5) /* PLL lock lost interrupt */
#define AX_IRQMRADIOCTRL	(1 << 6) /* Radio Controller interrupt */
#define AX_IRQMPOWER		(1 << 7) /* Power interrupt */
#define AX_IRQMXTALREADY	(1 << 8) /* Crystal Oscillator Ready interrupt */
#define AX_IRQMWAKEUPTIMER	(1 << 9) /* Wakeup Timer interrupt */
#define AX_IRQMLPOSC		(1 << 10) /* Low Power Oscillator interrupt */
#define AX_IRQMGPADC		(1 << 11) /* GPADC interrupt */
#define AX_IRQMPLLRNGDONE	(1 << 12) /* PLL autoranging done interrupt */

/**
 * Radio Event Mask
 */
#define AX_REVMDONE		(1 << 0) /* Transmit or Receive Done Radio Event */
#define AX_REVMSETTLED		(1 << 1) /* PLL Settled Radio Event */
#define AX_REVMRADIOSTATECHG	(1 << 2) /* Radio State Changed Event */
#define AX_REVMRXPARAMSETCHG	(1 << 3) /* Receiver Parameter Set Changed Event */
#define AX_REVMFRAMECLK		(1 << 4) /* Frame Clock Event */

/**
 * Modulation
 */
#define AX_MODULATION_ASK			0
#define AX_MODULATION_ASK_COHERENT	1
#define AX_MODULATION_PSK			4
#define AX_MODULATION_CW			5 /* not documented.. */
#define AX_MODULATION_OQSK			6
#define AX_MODULATION_MSK			7
#define AX_MODULATION_FSK			8
#define AX_MODULATION_4_FSK			9
#define AX_MODULATION_AFSK			10
#define AX_MODULATION_FM			11
#define AX_MODULATION_HALFSPEED		(1 << 4)

/**
 * Encoding
 */
#define AX_ENC_INV		(1 << 0) /* Invert data */
#define AX_ENC_DIFF		(1 << 1) /* Differential Encode/Decode data */
#define AX_ENC_SCRAM	(1 << 2) /* Enable Scrambler / Descrambler */
#define AX_ENC_MANCH	(1 << 3) /* Enable manchester encoding/decoding */
#define AX_ENC_NOSYNC	(1 << 4) /* Disable Dibit synchronisation in 4-FSK mode */

#define AX_ENC_NRZ		(0x0)      /* NRZ - level encodes data */
#define AX_ENC_NRZI		(0x3)      /* NRZI - inversion encodes data */
#define AX_ENC_FM0		(0xA)      /* FM0 - biphase space */
#define AX_ENC_FM1		(0xB)      /* FM1 - biphase mark */

/**
 * Framing
 */
#define AX_FRAMING_ABORT			(1 << 0)
#define AX_FRAMING_MODE_RAW			(0 << 1)
#define AX_FRAMING_MODE_RAW_SOFT_BITS		(1 << 1)
#define AX_FRAMING_MODE_HDLC			(2 << 1)
#define AX_FRAMING_MODE_RAW_PATTERN_MATCH	(3 << 1)
#define AX_FRAMING_MODE_WIRELESS_MBUS		(4 << 1)
#define AX_FRAMING_MODE_WIRELESS_MBUS_4_TO_6	(5 << 1)
#define AX_FRAMING_CRCMODE_OFF			(0 << 4)
#define AX_FRAMING_CRCMODE_CCITT		(1 << 4)
#define AX_FRAMING_CRCMODE_CRC_16		(2 << 4)
#define AX_FRAMING_CRCMODE_DNP			(3 << 4)
#define AX_FRAMING_CRCMODE_CRC_32		(4 << 4)
#define AX_FRAMING_RX				(1 << 7)

/**
 * FEC
 */
#define AX_FEC_ENA		(1 << 0) /* Enable FEC (Convolutional Encoder) */
#define AX_FEC_POS		(1 << 4) /* Enable noninverted Interleaver Synchronisation */
#define AX_FEC_NEG		(1 << 5) /* Enable inverted Interleaver Synchronisation */
#define AX_FEC_RSTVITERBI	(1 << 6) /* Reset Viterbi Decoder */
#define AX_FEC_SHORTMEM		(1 << 7) /* Shorten Backtrack Memory */

/**
 * FEC Status
 */
#define AX_FECSTATUS_INVERTED_SYNC	(1 << 7)

/**
 * Radio State
 */
#define AX_RADIOSTATE_IDLE		0
#define AX_RADIOSTATE_POWERDOWN		1
#define AX_RADIOSTATE_TX_PLL_SETTLING	4
#define AX_RADIOSTATE_TX		6
#define AX_RADIOSTATE_TX_TAIL		7
#define AX_RADIOSTATE_RX_PLL_SETTLING	8
#define AX_RADIOSTATE_RX_ANTENNA_SELECTION	9
#define AX_RADIOSTATE_RX_PREAMBLE_1	12
#define AX_RADIOSTATE_RX_PREAMBLE_2	13
#define AX_RADIOSTATE_RX_PREAMBLE_3	14
#define AX_RADIOSTATE_RX		15

/**
 * XTAL Status
 */
#define AX_XTALSTATUS_RUNNING	(1 << 0)

/**
 * Pin State
 */
#define AX_PSSYSCLK	(1 << 0) /* Signal Level on Pin SYSCLK */
#define AX_PSDCLK	(1 << 1) /* Signal Level on Pin DCLK */
#define AX_PSDATA	(1 << 2) /* Signal Level on Pin DATA */
#define AX_PSIRQ	(1 << 3) /* Signal Level on Pin IRQ */
#define AX_PSANTSEL	(1 << 4) /* Signal Level on Pin ANTSEL */
#define AX_PSPWRAMP	(1 << 5) /* Signal Level on Pin PWRAMP */

/**
 * Sysclk Pin Status
 */
#define AX_SYSCLK_OUTPUT_0		0
#define AX_SYSCLK_OUTPUT_1		1
#define AX_SYSCLK_OUTPUT_Z		2
#define AX_SYSCLK_OUTPUT_INVERTED_XTAL	3
#define AX_SYSCLK_OUTPUT_XTAL		4
#define AX_SYSCLK_OUTPUT_XTAL_DIV_2	5
#define AX_SYSCLK_OUTPUT_XTAL_DIV_4	6
#define AX_SYSCLK_OUTPUT_XTAL_DIV_8	7
#define AX_SYSCLK_OUTPUT_XTAL_DIV_16	8
#define AX_SYSCLK_OUTPUT_XTAL_DIV_32	9
#define AX_SYSCLK_OUTPUT_XTAL_DIV_64	10
#define AX_SYSCLK_OUTPUT_XTAL_DIV_128	11
#define AX_SYSCLK_OUTPUT_XTAL_DIV_256	12
#define AX_SYSCLK_OUTPUT_XTAL_DIV_512	13
#define AX_SYSCLK_OUTPUT_XTAL_DIV_1024	14
#define AX_SYSCLK_OUTPUT_LPOSC		15
#define AX_SYSCLK_OUTPUT_TEST		16
#define AX_SYSCLK_PU_ENABLE		(1 << 7) /* Weak Pullup Enable */

/**
 * FIFO Status (FIFOSAT)
 */
#define AX_FIFO_EMPTY		(1 << 0) /* FIFO is empty if 1 (SEE NOTE)  */
#define AX_FIFO_FULL		(1 << 1) /* FIFO is full if 1 */
#define AX_FIFO_UNDER		(1 << 2) /* FIFO underrun occured since last read of FIFOSTAT when 1 */
#define AX_FIFO_OVER		(1 << 3) /* FIFO overrun occured since last read of FIFOSTAT when 1 */
#define AX_FIFO_CNT_THR		(1 << 4) /* 1 if the FIFO count is > FIFOTHRESH */
#define AX_FIFO_FREE_THR	(1 << 5) /* 1 if the FIFO free space is > FIFOTHRESH */
#define AX_FIFO_AUTO_COMMIT	(1 << 7) /* If one, FIFO bytes are automatically committed on every write */

#define AX_FIFOCMD_NO_OPERATION		0
#define AX_FIFOCMD_CLEAR_FIFO_DATA	1
#define AX_FIFOCMD_CLEAR_FIFO_ERROR_FLAGS	2
#define AX_FIFOCMD_CLEAR_FIFO_DATA_AND_FLAGS	3
#define AX_FIFOCMD_COMMIT		4
#define AX_FIFOCMD_ROLLBACK		5

/**
 * PLL LOOP
 */
#define AX_PLLLOOP_EXTERNAL_FILTER				0
#define AX_PLLLOOP_INTERNAL_FILTER_BW_100_KHZ	1
#define AX_PLLLOOP_INTERNAL_FILTER_BW_200_KHZ	2
#define AX_PLLLOOP_INTERNAL_FILTER_BW_500_KHZ	3
#define AX_PLLLOOP_FILTER_ENABLE_EXTERNAL		(1 << 2)
#define AX_PLLLOOP_FILTER_DIRECT				(1 << 3)
#define AX_PLLLOOP_FREQSEL_A					(0 << 7)
#define AX_PLLLOOP_FREQSEL_B					(1 << 7)

/**
 * PLL VCO Divider
 */
#define AX_PLLVCODIV_DIVIDE_1	0
#define AX_PLLVCODIV_DIVIDE_2	1
#define AX_PLLVCODIV_DIVIDE_4	2
#define AX_PLLVCODIV_DIVIDE_8	3
#define AX_PLLVCODIV_RF_DIVIDER_NONE			(0 << 2)
#define AX_PLLVCODIV_RF_DIVIDER_DIV_TWO			(1 << 2)

#define AX_PLLVCODIV_RF_INTERNAL_VCO					(0 << 4)
#define AX_PLLVCODIV_RF_INTERNAL_VCO_EXTERNAL_INDUCTOR	(3 << 4)
#define AX_PLLVCODIV_RF_EXTERNAL_VCO					(1 << 4)


/**
 * PLL Ranging
 */
#define AX_PLLRANGING_RNG_START		(1 << 4)
#define AX_PLLRANGING_RNGERR		(1 << 5)
#define AX_PLLRANGING_PLL_LOCK		(1 << 6)
#define AX_PLLRANGING_STICKY_LOCK	(1 << 7)

/**
 * 5.15 Receiver Parameters ----------------------------------------
 */

/**
 * Max RF offset
 */
#define AX_MAXRFOFFSET_FREQOFFSCORR_FIRST_LO	(1 << 23)
#define AX_MAXRFOFFSET_FREQOFFSCORR_SECOND_LO	(0 << 23)

/**
 * FREQGAIN registers
 */
/* A */
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_AMPLITUDE_GATE	(1 << 4)
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_WRAP_HALF_MODULO	(1 << 5)
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_WRAP_MODULO		(1 << 6)
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_WRAP_LIMIT		(1 << 7)
/* B */
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_AVERAGE_CONSECUTIVE	(1 << 6)
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_FREEZE_LOOP			(1 << 7)
/* D */
#define AX_FREQGAIN_RF_FREQUENCY_RECOVERY_FREEZE_LOOP		(1 << 7)

/**
 * AMPLGAIN
 */
#define AX_AMPLGAIN_TRY_TO_CORRECT_AMPLITUDE_ON_AGC_JUMP	(1 << 6)
#define AX_AMPLGAIN_AMPLITUDE_RECOVERY_PEAKDET		(0 << 7)
#define AX_AMPLGAIN_AMPLITUDE_RECOVERY_AVERAGING	(1 << 7)

/**
 * FOURFSK
 */
#define AX_FOURFSK_ENABLE_DEVIATION_UPDATE	(1 << 4)

/**
 * 5.16 Transmitter Parameters ----------------------------------------
 */

/**
 * Modulation Config - Frequency (MODCFGF)
 */
#define AX_MODCFGF_FREQSHAPE_UNSHAPED			(0 << 0)
#define AX_MODCFGF_FREQSHAPE_GAUSSIAN_BT_0_3	(2 << 0)
#define AX_MODCFGF_FREQSHAPE_GAUSSIAN_BT_0_5	(3 << 0)

/**
 * FSK Deviation - FM Mode
 */
#define AX_FSKDEV_FMSHIFT_DIV_32768	0
#define AX_FSKDEV_FMSHIFT_DIV_16384	1
#define AX_FSKDEV_FMSHIFT_DIV_8192	2
#define AX_FSKDEV_FMSHIFT_DIV_4096	3
#define AX_FSKDEV_FMSHIFT_DIV_2048	4
#define AX_FSKDEV_FMSHIFT_DIV_1024	5
#define AX_FSKDEV_FMSHIFT_DIV_512	6
#define AX_FSKDEV_FMSHIFT_DIV_256	7
#define AX_FSKDEV_FMINPUT_GPADC13	(0 << 8)
#define AX_FSKDEV_FMINPUT_GPADC1	(1 << 8)
#define AX_FSKDEV_FMINPUT_GPADC2	(2 << 8)
#define AX_FSKDEV_FMINPUT_GPADC3	(3 << 8)
#define AX_FSKDEV_FMSEXT			(1 << 14) /* ADC Sign Extension */
#define AX_FSKDEV_FMOFFS			(1 << 15) /* ADC Offset Subtract */

/**
 * Modulation Config - Amplitude (MODCFGA)
 */
#define AX_MODCFGA_TXDIFF					(1 << 0) /* Differential TX */
#define AX_MODCFGA_TXSE						(1 << 1) /* Single Ended TX */
#define AX_MODCFGA_AMPLSHAPE_RAISED_COSINE	(1 << 2) /* RC Filter on TX */
#define AX_MODCFGA_SLOWRAMP_1_BIT_TIME		(0 << 4) /* 1 bit time startup */
#define AX_MODCFGA_SLOWRAMP_2_BIT_TIME		(1 << 4) /* 2 bit time startup */
#define AX_MODCFGA_SLOWRAMP_4_BIT_TIME		(2 << 4) /* 4 bit time startup */
#define AX_MODCFGA_SLOWRAMP_8_BIT_TIME		(3 << 4) /* 8 bit time startup */
#define AX_MODCFGA_PTTLCK_GATE_ENABLE		(1 << 6) /* Disable TX if PLL unlocks */
#define AX_MODCFGA_BROWN_GATE_ENABLE		(1 << 7) /* Disable TX if brownout */

/**
 * 5.17 PLL Parameters ----------------------------------------
 */

/**
 * PLL VCO Current
 */
#define AX_PLLVCOI_ENABLE_MANUAL	(1 << 7)

/**
 * PLL Ranging Clock
 */
#define AX_PLLRNGCLK_DIV_256	0
#define AX_PLLRNGCLK_DIV_512	1
#define AX_PLLRNGCLK_DIV_1024	2
#define AX_PLLRNGCLK_DIV_2048	3
#define AX_PLLRNGCLK_DIV_4096	4
#define AX_PLLRNGCLK_DIV_8192	5
#define AX_PLLRNGCLK_DIV_16384	6
#define AX_PLLRNGCLK_DIV_32768	7

/**
 * 5.22 Packet Controller ----------------------------------------
 */

#define AX_PKT_MAXIMUM_CHUNK_SIZE_1_BYTES		1
#define AX_PKT_MAXIMUM_CHUNK_SIZE_2_BYTES		2
#define AX_PKT_MAXIMUM_CHUNK_SIZE_4_BYTES		3
#define AX_PKT_MAXIMUM_CHUNK_SIZE_8_BYTES		4
#define AX_PKT_MAXIMUM_CHUNK_SIZE_16_BYTES		5
#define AX_PKT_MAXIMUM_CHUNK_SIZE_32_BYTES		6
#define AX_PKT_MAXIMUM_CHUNK_SIZE_64_BYTES		7
#define AX_PKT_MAXIMUM_CHUNK_SIZE_128_BYTES		8
#define AX_PKT_MAXIMUM_CHUNK_SIZE_160_BYTES		9
#define AX_PKT_MAXIMUM_CHUNK_SIZE_192_BYTES		10
#define AX_PKT_MAXIMUM_CHUNK_SIZE_224_BYTES		11
#define AX_PKT_MAXIMUM_CHUNK_SIZE_240_BYTES		12

#define AX_PKT_FLAGS_RSSI_UNITS_MICROSECONDS	(0 << 0)
#define AX_PKT_FLAGS_RSSI_UNITS_BIT_TIME		(1 << 0)
#define AX_PKT_FLAGS_AGC_UNITS_MICROSECONDS		(0 << 1)
#define AX_PKT_FLAGS_AGC_UNITS_BIT_TIME			(1 << 1)
#define AX_PKT_FLAGS_ENABLE_BGND_RSSI			(1 << 2)
#define AX_PKT_FLAGS_AGC_SETTLING_DETECTION		(1 << 3)

#define AX_PKT_STORE_TIMER					(1 << 0)
#define AX_PKT_STORE_FREQUENCY_OFFSET		(1 << 1)
#define AX_PKT_STORE_RF_OFFSET				(1 << 2)
#define AX_PKT_STORE_DATARATE_OFFSET		(1 << 3)
#define AX_PKT_STORE_RSSI					(1 << 4)
#define AX_PKT_STORE_CRC_BYTES				(1 << 5)
#define AX_PKT_STORE_RSSI_ON_ANTENNA_SELECT	(1 << 6)

#define AX_PKT_ACCEPT_RESIDUE			(1 << 0)
#define AX_PKT_ACCEPT_ABORTED			(1 << 1)
#define AX_PKT_ACCEPT_CRC_FAILURES		(1 << 2)
#define AX_PKT_ACCEPT_ADDRESS_FAILURES	(1 << 3)
#define AX_PKT_ACCEPT_SIZE_FAILURES		(1 << 4)
#define AX_PKT_ACCEPT_MULTIPLE_CHUNKS	(1 << 5)

/**
 * 5.24 Low Power Oscillator --------------------------------------
 */
#define AX_LPOSC_ENABLE		(1 << 0)
#define AX_LPOSC_640_HZ		(0 << 1)
#define AX_LPOSC_10240_HZ	(1 << 1)
#define AX_LPOSC_IRQR		(1 << 2)
#define AX_LPOSC_IRQF		(1 << 3)
#define AX_LPOSC_CALIBF		(1 << 4)
#define AX_LPOSC_CALIBR		(1 << 5)
#define AX_LPOSC_OSC_DOUBLE	(1 << 6)
#define AX_LPOSC_OSC_INVERT	(1 << 7)

/**
 * 5.25 DAC --------------------------------------
 */
#define AX_DAC_INPUT_DACVALUE		(0)
#define AX_DAC_INPUT_TRKAMPLITUDE	(1)
#define AX_DAC_INPUT_TRKRFFREQUENCY	(2)
#define AX_DAC_INPUT_TRKFREQUENCY	(3)
#define AX_DAC_INPUT_FSKDEMOD		(4)
#define AX_DAC_INPUT_AFSKDEMOD		(5)
#define AX_DAC_INPUT_RXSOFTDATA		(6)
#define AX_DAC_INPUT_RSSI			(7)
#define AX_DAC_INPUT_SAMPLE_ROT_I	(8)
#define AX_DAC_INPUT_SAMPLE_ROT_Q	(9)
#define AX_DAC_INPUT_GPADC13		(10)

#define AX_DEC_CLKX2			(1 << 6)
#define AX_DAC_MODE_DELTA_SIGMA	(0 << 7)
#define AX_DAC_MODE_PWM			(1 << 7)








#define AX_FIFO_CHUNK_NO_PAYLOAD    (0 << 5)
#define AX_FIFO_CHUNK_SINGLE_BYTE   (1 << 5)
#define AX_FIFO_CHUNK_TWO_BYTE      (2 << 5)
#define AX_FIFO_CHUNK_THREE_BYTE    (3 << 5)
#define AX_FIFO_CHUNK_VARIABLE      (7 << 5)

/**
 * Chunk Types
 */
#define AX_FIFO_CHUNK_NOP           0x00 /* No Operation */
#define AX_FIFO_CHUNK_DATA          0xE1 /* Data */
/* Transmit */
#define AX_FIFO_CHUNK_TXCTRL        0x3C /* Transmit Control (Antenna, Power Amp) */
#define AX_FIFO_CHUNK_REPEATDATA    0x62 /* Repeat Data */
#define AX_FIFO_CHUNK_TXPWR         0xFD /* Transmit Power */
/* Receive */
#define AX_FIFO_CHUNK_RSSI          0x31 /* RSSI */
#define AX_FIFO_CHUNK_FREQOFFS      0x52 /* Frequency Offset */
#define AX_FIFO_CHUNK_ANTRSSI2      0x55 /* Background Noise Calculation RSSI */
#define AX_FIFO_CHUNK_TIMER         0x70 /* Timer */
#define AX_FIFO_CHUNK_RFFREQOFFS    0x73 /* RF Frequency Offset */
#define AX_FIFO_CHUNK_DATARATE      0x74 /* Datarate */
#define AX_FIFO_CHUNK_ANTRSSI3      0x75 /* Antenna Selection RSSI *



#define AX_FIFO_TXCTRL_SETTX    (1 << 6) /* Copy TXSE and TXDIFF to MODCFGA */
#define AX_FIFO_TXCTRL_TXSE     (1 << 5)
#define AX_FIFO_TXCTRL_TXDIFF   (1 << 4)
#define AX_FIFO_TXCTRL_SETANT   (1 << 3) /* Copy ANTSTATE to DIVERSITY */
#define AX_FIFO_TXCTRL_ANTSTATE (1 << 2)
#define AX_FIFO_TXCTRL_SETPA    (1 << 1) /* Copy PASTATE to PWRAMP */
#define AX_FIFO_TXCTRL_PASTATE  (1 << 0)

/**
 * Transmit DATA Command
 */
#define AX_FIFO_TXDATA_UNENC    (1 << 5) /* Bypass framing and encoder */
#define AX_FIFO_TXDATA_RAW      (1 << 4) /* Bypass framing */
#define AX_FIFO_TXDATA_NOCRC    (1 << 3) /* Don't generate CRC */
#define AX_FIFO_TXDATA_RESIDUE  (1 << 2) /* Residue mode on last byte */
#define AX_FIFO_TXDATA_PKTEND   (1 << 1) /* END flag */
#define AX_FIFO_TXDATA_PKTSTART (1 << 0) /* START flag */

/**
 * Receive DATA Command
 */
#define AX_FIFO_RXDATA_ABORT    (1 << 6) /* Packet has been aborted */
#define AX_FIFO_RXDATA_SIZEFAIL (1 << 5) /* Size checks failed */
#define AX_FIFO_RXDATA_ADDRFAIL (1 << 4) /* Address checks failed */
#define AX_FIFO_RXDATA_CRCFAIL  (1 << 3) /* CRC check failed */
#define AX_FIFO_RXDATA_RESIDUE  (1 << 2) /* Residue mode on last byte */
#define AX_FIFO_RXDATA_PKTEND   (1 << 1) /* END flag */
#define AX_FIFO_RXDATA_PKTSTART (1 << 0) /* START flag */




#define AX_REG_SILICONREVISION  0x000   /* Silicon Revision */
#define AX_REG_SCRATCH          0x001   /* Scratch */
#define AX_REG_PWRMODE          0x002   /* Power Mode */

/**
 * Voltage Regulator
 */
#define AX_REG_POWSTAT          0x003   /* Power Management Status */
#define AX_REG_POWSTICKYSTAT    0x004   /* Power Management Sticky Status */
#define AX_REG_POWIRQMASK       0x005   /* Power Management Interrupt Mask */

/**
 * Interrupt control
 */
#define AX_REG_IRQMASK          0x006   /* IRQ Mask */
#define AX_REG_RADIOEVENTMASK   0x008   /* Radio Event Mask */
#define AX_REG_IRQINVERSION     0x00A   /* IRQ Inversion */
#define AX_REG_IRQREQUEST       0x00C   /* IRQ Request */
#define AX_REG_RADIOEVENTREQ    0x00E   /* Radio Event Request */

/**
 * Modulation & Framing
 */
#define AX_REG_MODULATION       0x010   /* Modulation */
#define AX_REG_ENCODING         0x011   /* Encoding */
#define AX_REG_FRAMING          0x012   /* Framing Mode */
#define AX_REG_CRCINIT          0x014   /* CRC Initial Value */

/**
 * FEC
 */
#define AX_REG_FEC              0x018   /* Forward Error Correction */
#define AX_REG_FECSYNC          0x019   /* Forward Error Correction Sync Threshold */
#define AX_REG_FECSTATUS        0x01A   /* Forward Error Correction Status */

/**
 * Status
 */
#define AX_REG_RADIOSTATE       0x01C   /* Radio Controller State */
#define AX_REG_XTALSTATUS       0x01D   /* Crystal Oscillator Status */

/**
 * Pin Configuration
 */
#define AX_REG_PINSTATE         0x020   /* Pin State */
#define AX_REG_PINFUNCSYSCLK    0x021   /* Pin Function SYSCLK */
#define AX_REG_PINFUNCDCLK      0x022   /* Pin Function DCLK */
#define AX_REG_PINFUNCDATA      0x023   /* Pin Function DATA */
#define AX_REG_PINFUNCIRQ       0x024   /* Pin Function IRQ */
#define AX_REG_PINFUNCANTSEL    0x025   /* Pin Function ANTSEL */
#define AX_REG_PINFUNCPWRAMP    0x026   /* Pin Function PWRAMP */
#define AX_REG_PWRAMP           0x027   /* PWRAMP Control */

/**
 * FIFO
 */
#define AX_REG_FIFOSTAT         0x028   /* FIFO Control */
#define AX_REG_FIFODATA         0x029   /* FIFO Data */
#define AX_REG_FIFOCOUNT        0x02A   /* Number of Words currently in FIFO */
#define AX_REG_FIFOFREE         0x02C   /* Number of Words that can be written to FIFO */
#define AX_REG_FIFOTHRESH       0x02E   /* FIFO Threshold */

/**
 * Synth
 */
#define AX_REG_PLLLOOP          0x030   /* PLL Loop Filter Settings */
#define AX_REG_PLLCPI           0x031   /* PL Charge Pump Current */
#define AX_REG_PLLVCODIV        0x032   /* PLL Divider Settings */
#define AX_REG_PLLRANGINGA      0x033   /* PLL Autoranging A */
#define AX_REG_FREQA            0x034   /* Frequency A */
#define AX_REG_PLLLOOPBOOST     0x038   /* PLL Loop Filter Settings (Boosted) */
#define AX_REG_PLLCPIBOOST      0x039   /* PLL Charge Pump Current (Boosted) */
#define AX_REG_PLLRANGINGB      0x03B   /* PLL Autoranging B */
#define AX_REG_FREQB            0x03C   /* Frequency B */

/**
 * Signal strength
 */
#define AX_REG_RSSI             0x040   /* Received Signal Strength Indicator */
#define AX_REG_BGNDRSSI         0x041   /* Background RSSI */
#define AX_REG_DIVERSITY        0x042   /* Antenna Diversity Configuration */
#define AX_REG_AGCCOUNTER       0x043   /* AGC Counter */

/**
 * Rx tracking
 */
#define AX_REG_TRKDATARATE      0x045   /* Datarate Tracking */
#define AX_REG_TRKAMPLITUDE     0x048   /* Amplitude Tracking */
#define AX_REG_TRKPHASE         0x04A   /* Phase Tracking */
#define AX_REG_TRKRFFREQ        0x04D   /* RF Frequency Tracking */
#define AX_REG_TRKFREQ          0x050   /* Frequency Tracking */
#define AX_REG_TRKFSKDEMOD      0x052   /* FSK Demodulator Tracking */
#define AX_REG_TRKAFSKDEMOD     0x054   /* AFSK Demodulator Tracking */

/**
 * Timer
 */
#define AX_REG_TIMER            0x059   /* 1MHz Timer */
#define AX_REG_WAKEUPTIMER      0x068   /* Wakeup Timer */
#define AX_REG_WAKEUP           0x06A   /* Wakeup Time */
#define AX_REG_WAKEUPFREQ       0x06C   /* Wakeup Frequency */
#define AX_REG_WAKEUPXOEARLY    0x06E   /* Wakeup Crystal Oscillator Early */

/**
 * Receiver parameters
 */
#define AX_REG_IFFREQ           0x100   /* 2nd LO / IF Frequency */
#define AX_REG_DECIMATION       0x102   /* Decimation Factor */
#define AX_REG_RXDATARATE       0x103   /* Receiver Datarate */
#define AX_REG_MAXDROFFSET      0x106   /* Maximum Receiver Datarate Offset */
#define AX_REG_MAXRFOFFSET      0x109   /* Maximum Receiver RF Offset */
#define AX_REG_FSKDMAX          0x10C   /* Four FSK Rx Maximum Deviation */
#define AX_REG_FSKDMIN          0x10E   /* Four FSK Rx Minimum Deviation */
#define AX_REG_AFSKSPACE        0x110   /* AFSK Space (0) Frequency */
#define AX_REG_AFSKMARK         0x112   /* AFSK Mark (1) Frequency */
#define AX_REG_AFSKCTRL         0x114   /* AFSK Control */
#define AX_REG_AMPLFILTER       0x115   /* Amplitude Filter */
#define AX_REG_FREQUENCYLEAK    0x116   /* Baseband Frequency Recovery Loop Leakiness */
#define AX_REG_RXPARAMSETS      0x117   /* Receiver Parameter Set Indirection */
#define AX_REG_RXPARAMCURSET    0x118   /* Receiver Parameter Current Set */

/**
 * Receiver Parameter Sets
 */
#define AX_REG_RX_PARAMETER0    0x120
#define AX_REG_RX_PARAMETER1    0x130
#define AX_REG_RX_PARAMETER2    0x140
#define AX_REG_RX_PARAMETER3    0x150

#define AX_RX_AGCGAIN           0x0 /* AGC Speed */
#define AX_RX_AGCTARGET         0x1 /* AGC Target */
#define AX_RX_AGCAHYST          0x2 /* AGC Analog Hysteresis */
#define AX_RX_AGCMINMAX         0x3 /* AGC Analog Update Behaviour */
#define AX_RX_TIMEGAIN          0x4 /* Time Estimator Bandwidth */
#define AX_RX_DRGAIN            0x5 /* Data Rate Estimator Bandwidth */
#define AX_RX_PHASEGAIN         0x6 /* Phase Estimator Bandwidth */
#define AX_RX_FREQUENCYGAINA    0x7 /* Frequency Estimator Bandwidth A */
#define AX_RX_FREQUENCYGAINB    0x8 /* Frequency Estimator Bandwidth B */
#define AX_RX_FREQUENCYGAINC    0x9 /* Frequency Estimator Bandwidth C */
#define AX_RX_FREQUENCYGAIND    0xA /* Frequency Estimator Bandwidth D */
#define AX_RX_AMPLITUDEGAIN     0xB /* Amplitude Estimator Bandwidth */
#define AX_RX_FREQDEV           0xC /* Receiver Frequency Deviation */
#define AX_RX_FOURFSK           0xE /* Four FSK Control */
#define AX_RX_BBOFFSRES         0xF /* Baseband Offset Compensation Resistors */

/**
 * Transmitter Parameters
 */
#define AX_REG_MODCFGF          0x160   /* Modulator Configuration F */
#define AX_REG_FSKDEV           0x161   /* FSK Deviation */
#define AX_REG_MODCFGA          0x164   /* Modulator Configuration A */
#define AX_REG_TXRATE           0x165   /* Transmitter Bitrate */
#define AX_REG_TXPWRCOEFFA      0x168   /* Transmitter Predistortion Coefficient A */
#define AX_REG_TXPWRCOEFFB      0x16A   /* Transmitter Predistortion Coefficient B */
#define AX_REG_TXPWRCOEFFC      0x16C   /* Transmitter Predistortion Coefficient C */
#define AX_REG_TXPWRCOEFFD      0x16E   /* Transmitter Predistortion Coefficient D */
#define AX_REG_TXPWRCOEFFE      0x170   /* Transmitter Predistortion Coefficient E */

/**
 * PLL Paramters
 */
#define AX_REG_PLLVCOI          0x180   /* PLL VCO Current */
#define AX_REG_PLLVCOIR         0x181   /* PLL VCO Current Readback */
#define AX_REG_PLLLOCKDET       0x182   /* PLL Lock Detect Delay */
#define AX_REG_PLLRNGCLK        0x183   /* PLL Autoranging Clock */

/**
 * Crystal Oscillator
 */
#define AX_REG_XTALCAP          0x184   /* Crystal Oscillator Load Capacitance */

/**
 * Baseband
 */
#define AX_REG_BBTUNE           0x188   /* Baseband Tuning */
#define AX_REG_BBOFFSCAP        0x189   /* Baseband Offset Compensation Capacitors */

/**
 * Packet format
 */
#define AX_REG_PKTADDRCFG       0x200   /* Packet Address Config */
#define AX_REG_PKTLENCFG        0x201   /* Packet Length Configuration */
#define AX_REG_PKTLENOFFSET     0x202   /* Packet Length Offset */
#define AX_REG_PKTMAXLEN        0x203   /* Packet Maximum Length */
#define AX_REG_PKTADDR          0x204   /* Packet Address */
#define AX_REG_PKTADDRMASK      0x208   /* Packet Address Mask */

/**
 * Pattern match
 */
#define AX_REG_MATCH0PAT        0x210   /* Pattern Match Unit 0, Pattern */
#define AX_REG_MATCH0LEN        0x214   /* Pattern Match Unit 0, Pattern Length */
#define AX_REG_MATCH0MIN        0x215   /* Pattern Match Unit 0, Minimum Match */
#define AX_REG_MATCH0MAX        0x216   /* Pattern Match Unit 0, Maximum Match */
#define AX_REG_MATCH1PAT        0x218   /* Pattern Match Unit 1, Pattern */
#define AX_REG_MATCH1LEN        0x21C   /* Pattern Match Unit 1, Pattern Length */
#define AX_REG_MATCH1MIN        0x21D   /* Pattern Match Unit 1, Minimum Match */
#define AX_REG_MATCH1MAX        0x21E   /* Pattern Match Unit 1, Maximum Match */

/**
 * Packet controller
 */
#define AX_REG_TMGTXBOOST       0x220   /* Transmit PLL Boost Time */
#define AX_REG_TMGTXSETTLE      0x221   /* Transmit PLL (post Boost) Settling Time */
#define AX_REG_TMGRXBOOST       0x223   /* Receive PLL Boost Time */
#define AX_REG_TMGRXSETTLE      0x224   /* Receive PLL (post Boost) Settling Time */
#define AX_REG_TMGRXOFFSACQ     0x225   /* Receive Baseband DC Offset Acquisition Time */
#define AX_REG_TMGRXCOARSEAGC   0x226   /* Receive Coarse AGC Time */
#define AX_REG_TMGRXAGC         0x227   /* Receiver AGC Settling Time */
#define AX_REG_TMGRXRSSI        0x228   /* Receiver RSSI Settling Time */
#define AX_REG_TMGRXPREAMBLE1   0x229   /* Receiver Preamble 1 Timeout */
#define AX_REG_TMGRXPREAMBLE2   0x22A   /* Receiver Preamble 2 Timeout */
#define AX_REG_TMGRXPREAMBLE3   0x22B   /* Receiver Preamble 3 Timeout */
#define AX_REG_RSSIREFERENCE    0x22C   /* RSSI Offset */
#define AX_REG_RSSIABSTHR       0x22D   /* RSSI Absolute Threshold */
#define AX_REG_BGNDRSSIGAIN     0x22E   /* Background RSSI Averaging Time Constant */
#define AX_REG_BGNDRSSITHR      0x22F   /* Background RSSI Relative Threshold */
#define AX_REG_PKTCHUNKSIZE     0x230   /* Packet Chunk Size */
#define AX_REG_PKTMISCFLAGS     0x231   /* Packet Controller Miscellaneous Flags */
#define AX_REG_PKTSTOREFLAGS    0x232   /* Packet Controller Store Flags */
#define AX_REG_PKTACCEPTFLAGS   0x233   /* Packet Controller Accept Flags */

/**
 * GPADC
 */
#define AX_REG_GPADCCTRL        0x300   /* General Purpose ADC Control */
#define AX_REG_GPADCPERIOD      0x301   /* GPADC Sampling Period */
#define AX_REG_GPADC13VALUE     0x308   /* GPADC13 Value */

/**
 * LPOSC Calibration
 */
#define AX_REG_LPOSCCONFIG      0x310   /* LPOSC Calibration Configuration */
#define AX_REG_LPOSCSTATUS      0x311   /* LPOSC Calibration Status */
#define AX_REG_LPOSCKFILT       0x312   /* LPOSC Calibration Filter Constant */
#define AX_REG_LPOSCREF         0x314   /* LPOSC Reference Frequency */
#define AX_REG_LPOSCFREQ        0x316   /* LPOSC Frequency Tuning */
#define AX_REG_LPOSCPER         0x318   /* LPOSC Period */

/**
 * DAC
 */
#define AX_REG_DACVALUE         0x330   /* DAC Value */
#define AX_REG_DACCONFIG        0x332   /* DAC Configuration */

/**
 * Performance Tuning
 */
#define AX_REG_POWCTRL          0xF08   /* Power Control */
#define AX_REG_REF              0xF0D   /* Reference */
#define AX_REG_XTALOSC          0xF10   /* Crystal Oscillator Control */
#define AX_REG_XTALAMPL         0xF11   /* Crystal Oscillator Amplitude Control */



#define AX_STATUS_POWER_READY               (1 << 15)
#define AX_STATUS_PLL_LOCK                  (1 << 14)
#define AX_STATUS_FIFO_OVERFLOW             (1 << 13)
#define AX_STATUS_FIFO_UNDERFLOW            (1 << 12)
#define AX_STATUS_THRESHOLD_FREE            (1 << 11)
#define AX_STATUS_THRESHOLD_COUNT           (1 << 10)
#define AX_STATUS_FIFO_FULL                 (1 << 9)
#define AX_STATUS_FIFO_EMPTY                (1 << 8)
#define AX_STATUS_PWRGOOD                   (1 << 7)
#define AX_STATUS_PWR_INTERRUPT_PENDING     (1 << 6)
#define AX_STATUS_RADIO_EVENT_PENDING       (1 << 5)
#define AX_STATUS_XTAL_OSCILLATOR_RUNNING   (1 << 4)
#define AX_STATUS_WAKEUP_INTERRUPT_PENDING  (1 << 3)
#define AX_STATUS_LPOSC_INTERRUPT_PENDING   (1 << 2)
#define AX_STATUS_GPADC_INTERRUPT_PENDING   (1 << 1)

/**
 * Revision
 */
#define AX_SILICONREVISION  0x51

/**
 * Scratch
 */
#define AX_SCRATCH          0xC5

/**
 * Power Mode
 */
#define AX_PWRMODE_POWERDOWN    0  /* 400nA */
#define AX_PWRMODE_DEEPSLEEP    1  /* 50nA */
#define AX_PWRMODE_STANDBY  5  /* 230µA */
#define AX_PWRMODE_FIFOON   7  /* 310µA */
#define AX_PWRMODE_SYNTHRX  8  /* 5mA */
#define AX_PWRMODE_FULLRX   9  /* 7-11mA */
#define AX_PWRMODE_WORRX    11 /* 500nA */
#define AX_PWRMODE_SYNTHTX  12 /* 5mA */
#define AX_PWRMODE_FULLTX   13 /* 6-70mA */

#define AX_PWRMODE_WDS      (1 << 4) /* Wakeup from Deep Sleep */
#define AX_PWRMODE_REFEN    (1 << 5) /* Power to internal reference */
#define AX_PWRMODE_XOEN     (1 << 6) /* Crystal Oscillator Enable */
#define AX_PWRMODE_RST      (1 << 7) /* Reset */

/**
 * Power Status
 */
#define AX_POWSTAT_SVIO     (1 << 0) /* IO Voltage Large Enough (not Brownout) */
#define AX_POWSTAT_SBEVMODEM    (1 << 1) /* Modem Domain Voltage Brownout Error (Inverted) */
#define AX_POWSTAT_SBEVANA  (1 << 2) /* Analog Domain Voltage Brownout Error (Inverted) */
#define AX_POWSTAT_SVMODEM  (1 << 3) /* Modem Domain Voltage Regulator Ready */
#define AX_POWSTAT_SVANA    (1 << 4) /* Analog Domain Voltage Regulator Ready */
#define AX_POWSTAT_SVREF    (1 << 5) /* Reference Voltage Regulator Ready */
#define AX_POWSTAT_SREF     (1 << 6) /* Reference Ready */
#define AX_POWSTAT_SSUM     (1 << 7) /* Summary Ready Status */

/**
 * Interrupt Control
 */
#define AX_IRQMFIFONOTEMPTY (1 << 0) /* FIFO not empty interrupt */
#define AX_IRQMFIFONOTFULL  (1 << 1) /* FIFO not full interrupt */
#define AX_IRQMFIFOTHRCNT   (1 << 2) /* FIFO count > threshold interrupt */
#define AX_IRQMFIFOTHRFREE  (1 << 3) /* FIFO free > threshold interrupt */
#define AX_IRQMFIFOERROR    (1 << 4) /* FIFO error interrupt */
#define AX_IRQMPLLUNLOCK    (1 << 5) /* PLL lock lost interrupt */
#define AX_IRQMRADIOCTRL    (1 << 6) /* Radio Controller interrupt */
#define AX_IRQMPOWER        (1 << 7) /* Power interrupt */
#define AX_IRQMXTALREADY    (1 << 8) /* Crystal Oscillator Ready interrupt */
#define AX_IRQMWAKEUPTIMER  (1 << 9) /* Wakeup Timer interrupt */
#define AX_IRQMLPOSC        (1 << 10) /* Low Power Oscillator interrupt */
#define AX_IRQMGPADC        (1 << 11) /* GPADC interrupt */
#define AX_IRQMPLLRNGDONE   (1 << 12) /* PLL autoranging done interrupt */

/**
 * Radio Event Mask
 */
#define AX_REVMDONE     (1 << 0) /* Transmit or Receive Done Radio Event */
#define AX_REVMSETTLED      (1 << 1) /* PLL Settled Radio Event */
#define AX_REVMRADIOSTATECHG    (1 << 2) /* Radio State Changed Event */
#define AX_REVMRXPARAMSETCHG    (1 << 3) /* Receiver Parameter Set Changed Event */
#define AX_REVMFRAMECLK     (1 << 4) /* Frame Clock Event */

/**
 * Modulation
 */
#define AX_MODULATION_ASK           0
#define AX_MODULATION_ASK_COHERENT  1
#define AX_MODULATION_PSK           4
#define AX_MODULATION_CW            5 /* not documented.. */
#define AX_MODULATION_OQSK          6
#define AX_MODULATION_MSK           7
#define AX_MODULATION_FSK           8
#define AX_MODULATION_4_FSK         9
#define AX_MODULATION_AFSK          10
#define AX_MODULATION_FM            11
#define AX_MODULATION_HALFSPEED     (1 << 4)

/**
 * Encoding
 */
#define AX_ENC_INV      (1 << 0) /* Invert data */
#define AX_ENC_DIFF     (1 << 1) /* Differential Encode/Decode data */
#define AX_ENC_SCRAM    (1 << 2) /* Enable Scrambler / Descrambler */
#define AX_ENC_MANCH    (1 << 3) /* Enable manchester encoding/decoding */
#define AX_ENC_NOSYNC   (1 << 4) /* Disable Dibit synchronisation in 4-FSK mode */

#define AX_ENC_NRZ      (0x0)      /* NRZ - level encodes data */
#define AX_ENC_NRZI     (0x3)      /* NRZI - inversion encodes data */
#define AX_ENC_FM0      (0xA)      /* FM0 - biphase space */
#define AX_ENC_FM1      (0xB)      /* FM1 - biphase mark */

/**
 * Framing
 */
#define AX_FRAMING_ABORT            (1 << 0)
#define AX_FRAMING_MODE_RAW         (0 << 1)
#define AX_FRAMING_MODE_RAW_SOFT_BITS       (1 << 1)
#define AX_FRAMING_MODE_HDLC            (2 << 1)
#define AX_FRAMING_MODE_RAW_PATTERN_MATCH   (3 << 1)
#define AX_FRAMING_MODE_WIRELESS_MBUS       (4 << 1)
#define AX_FRAMING_MODE_WIRELESS_MBUS_4_TO_6    (5 << 1)
#define AX_FRAMING_CRCMODE_OFF          (0 << 4)
#define AX_FRAMING_CRCMODE_CCITT        (1 << 4)
#define AX_FRAMING_CRCMODE_CRC_16       (2 << 4)
#define AX_FRAMING_CRCMODE_DNP          (3 << 4)
#define AX_FRAMING_CRCMODE_CRC_32       (4 << 4)
#define AX_FRAMING_RX               (1 << 7)

/**
 * FEC
 */
#define AX_FEC_ENA      (1 << 0) /* Enable FEC (Convolutional Encoder) */
#define AX_FEC_POS      (1 << 4) /* Enable noninverted Interleaver Synchronisation */
#define AX_FEC_NEG      (1 << 5) /* Enable inverted Interleaver Synchronisation */
#define AX_FEC_RSTVITERBI   (1 << 6) /* Reset Viterbi Decoder */
#define AX_FEC_SHORTMEM     (1 << 7) /* Shorten Backtrack Memory */

/**
 * FEC Status
 */
#define AX_FECSTATUS_INVERTED_SYNC  (1 << 7)

/**
 * Radio State
 */
#define AX_RADIOSTATE_IDLE      0
#define AX_RADIOSTATE_POWERDOWN     1
#define AX_RADIOSTATE_TX_PLL_SETTLING   4
#define AX_RADIOSTATE_TX        6
#define AX_RADIOSTATE_TX_TAIL       7
#define AX_RADIOSTATE_RX_PLL_SETTLING   8
#define AX_RADIOSTATE_RX_ANTENNA_SELECTION  9
#define AX_RADIOSTATE_RX_PREAMBLE_1 12
#define AX_RADIOSTATE_RX_PREAMBLE_2 13
#define AX_RADIOSTATE_RX_PREAMBLE_3 14
#define AX_RADIOSTATE_RX        15

/**
 * XTAL Status
 */
#define AX_XTALSTATUS_RUNNING   (1 << 0)

/**
 * Pin State
 */
#define AX_PSSYSCLK (1 << 0) /* Signal Level on Pin SYSCLK */
#define AX_PSDCLK   (1 << 1) /* Signal Level on Pin DCLK */
#define AX_PSDATA   (1 << 2) /* Signal Level on Pin DATA */
#define AX_PSIRQ    (1 << 3) /* Signal Level on Pin IRQ */
#define AX_PSANTSEL (1 << 4) /* Signal Level on Pin ANTSEL */
#define AX_PSPWRAMP (1 << 5) /* Signal Level on Pin PWRAMP */

/**
 * Sysclk Pin Status
 */
#define AX_SYSCLK_OUTPUT_0      0
#define AX_SYSCLK_OUTPUT_1      1
#define AX_SYSCLK_OUTPUT_Z      2
#define AX_SYSCLK_OUTPUT_INVERTED_XTAL  3
#define AX_SYSCLK_OUTPUT_XTAL       4
#define AX_SYSCLK_OUTPUT_XTAL_DIV_2 5
#define AX_SYSCLK_OUTPUT_XTAL_DIV_4 6
#define AX_SYSCLK_OUTPUT_XTAL_DIV_8 7
#define AX_SYSCLK_OUTPUT_XTAL_DIV_16    8
#define AX_SYSCLK_OUTPUT_XTAL_DIV_32    9
#define AX_SYSCLK_OUTPUT_XTAL_DIV_64    10
#define AX_SYSCLK_OUTPUT_XTAL_DIV_128   11
#define AX_SYSCLK_OUTPUT_XTAL_DIV_256   12
#define AX_SYSCLK_OUTPUT_XTAL_DIV_512   13
#define AX_SYSCLK_OUTPUT_XTAL_DIV_1024  14
#define AX_SYSCLK_OUTPUT_LPOSC      15
#define AX_SYSCLK_OUTPUT_TEST       16
#define AX_SYSCLK_PU_ENABLE     (1 << 7) /* Weak Pullup Enable */

/**
 * FIFO Status (FIFOSAT)
 */
#define AX_FIFO_EMPTY       (1 << 0) /* FIFO is empty if 1 (SEE NOTE)  */
#define AX_FIFO_FULL        (1 << 1) /* FIFO is full if 1 */
#define AX_FIFO_UNDER       (1 << 2) /* FIFO underrun occured since last read of FIFOSTAT when 1 */
#define AX_FIFO_OVER        (1 << 3) /* FIFO overrun occured since last read of FIFOSTAT when 1 */
#define AX_FIFO_CNT_THR     (1 << 4) /* 1 if the FIFO count is > FIFOTHRESH */
#define AX_FIFO_FREE_THR    (1 << 5) /* 1 if the FIFO free space is > FIFOTHRESH */
#define AX_FIFO_AUTO_COMMIT (1 << 7) /* If one, FIFO bytes are automatically committed on every write */

#define AX_FIFOCMD_NO_OPERATION     0
#define AX_FIFOCMD_CLEAR_FIFO_DATA  1
#define AX_FIFOCMD_CLEAR_FIFO_ERROR_FLAGS   2
#define AX_FIFOCMD_CLEAR_FIFO_DATA_AND_FLAGS    3
#define AX_FIFOCMD_COMMIT       4
#define AX_FIFOCMD_ROLLBACK     5

/**
 * PLL LOOP
 */
#define AX_PLLLOOP_EXTERNAL_FILTER              0
#define AX_PLLLOOP_INTERNAL_FILTER_BW_100_KHZ   1
#define AX_PLLLOOP_INTERNAL_FILTER_BW_200_KHZ   2
#define AX_PLLLOOP_INTERNAL_FILTER_BW_500_KHZ   3
#define AX_PLLLOOP_FILTER_ENABLE_EXTERNAL       (1 << 2)
#define AX_PLLLOOP_FILTER_DIRECT                (1 << 3)
#define AX_PLLLOOP_FREQSEL_A                    (0 << 7)
#define AX_PLLLOOP_FREQSEL_B                    (1 << 7)

/**
 * PLL VCO Divider
 */
#define AX_PLLVCODIV_DIVIDE_1   0
#define AX_PLLVCODIV_DIVIDE_2   1
#define AX_PLLVCODIV_DIVIDE_4   2
#define AX_PLLVCODIV_DIVIDE_8   3
#define AX_PLLVCODIV_RF_DIVIDER_NONE            (0 << 2)
#define AX_PLLVCODIV_RF_DIVIDER_DIV_TWO         (1 << 2)

#define AX_PLLVCODIV_RF_INTERNAL_VCO                    (0 << 4)
#define AX_PLLVCODIV_RF_INTERNAL_VCO_EXTERNAL_INDUCTOR  (3 << 4)
#define AX_PLLVCODIV_RF_EXTERNAL_VCO                    (1 << 4)


/**
 * PLL Ranging
 */
#define AX_PLLRANGING_RNG_START     (1 << 4)
#define AX_PLLRANGING_RNGERR        (1 << 5)
#define AX_PLLRANGING_PLL_LOCK      (1 << 6)
#define AX_PLLRANGING_STICKY_LOCK   (1 << 7)

/**
 * 5.15 Receiver Parameters ----------------------------------------
 */

/**
 * Max RF offset
 */
#define AX_MAXRFOFFSET_FREQOFFSCORR_FIRST_LO    (1 << 23)
#define AX_MAXRFOFFSET_FREQOFFSCORR_SECOND_LO   (0 << 23)

/**
 * FREQGAIN registers
 */
/* A */
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_AMPLITUDE_GATE    (1 << 4)
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_WRAP_HALF_MODULO  (1 << 5)
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_WRAP_MODULO       (1 << 6)
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_WRAP_LIMIT        (1 << 7)
/* B */
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_AVERAGE_CONSECUTIVE   (1 << 6)
#define AX_FREQGAIN_BB_FREQUENCY_RECOVERY_FREEZE_LOOP           (1 << 7)
/* D */
#define AX_FREQGAIN_RF_FREQUENCY_RECOVERY_FREEZE_LOOP       (1 << 7)

/**
 * AMPLGAIN
 */
#define AX_AMPLGAIN_TRY_TO_CORRECT_AMPLITUDE_ON_AGC_JUMP    (1 << 6)
#define AX_AMPLGAIN_AMPLITUDE_RECOVERY_PEAKDET      (0 << 7)
#define AX_AMPLGAIN_AMPLITUDE_RECOVERY_AVERAGING    (1 << 7)

/**
 * FOURFSK
 */
#define AX_FOURFSK_ENABLE_DEVIATION_UPDATE  (1 << 4)

/**
 * 5.16 Transmitter Parameters ----------------------------------------
 */

/**
 * Modulation Config - Frequency (MODCFGF)
 */
#define AX_MODCFGF_FREQSHAPE_UNSHAPED           (0 << 0)
#define AX_MODCFGF_FREQSHAPE_GAUSSIAN_BT_0_3    (2 << 0)
#define AX_MODCFGF_FREQSHAPE_GAUSSIAN_BT_0_5    (3 << 0)

/**
 * FSK Deviation - FM Mode
 */
#define AX_FSKDEV_FMSHIFT_DIV_32768 0
#define AX_FSKDEV_FMSHIFT_DIV_16384 1
#define AX_FSKDEV_FMSHIFT_DIV_8192  2
#define AX_FSKDEV_FMSHIFT_DIV_4096  3
#define AX_FSKDEV_FMSHIFT_DIV_2048  4
#define AX_FSKDEV_FMSHIFT_DIV_1024  5
#define AX_FSKDEV_FMSHIFT_DIV_512   6
#define AX_FSKDEV_FMSHIFT_DIV_256   7
#define AX_FSKDEV_FMINPUT_GPADC13   (0 << 8)
#define AX_FSKDEV_FMINPUT_GPADC1    (1 << 8)
#define AX_FSKDEV_FMINPUT_GPADC2    (2 << 8)
#define AX_FSKDEV_FMINPUT_GPADC3    (3 << 8)
#define AX_FSKDEV_FMSEXT            (1 << 14) /* ADC Sign Extension */
#define AX_FSKDEV_FMOFFS            (1 << 15) /* ADC Offset Subtract */

/**
 * Modulation Config - Amplitude (MODCFGA)
 */
#define AX_MODCFGA_TXDIFF                   (1 << 0) /* Differential TX */
#define AX_MODCFGA_TXSE                     (1 << 1) /* Single Ended TX */
#define AX_MODCFGA_AMPLSHAPE_RAISED_COSINE  (1 << 2) /* RC Filter on TX */
#define AX_MODCFGA_SLOWRAMP_1_BIT_TIME      (0 << 4) /* 1 bit time startup */
#define AX_MODCFGA_SLOWRAMP_2_BIT_TIME      (1 << 4) /* 2 bit time startup */
#define AX_MODCFGA_SLOWRAMP_4_BIT_TIME      (2 << 4) /* 4 bit time startup */
#define AX_MODCFGA_SLOWRAMP_8_BIT_TIME      (3 << 4) /* 8 bit time startup */
#define AX_MODCFGA_PTTLCK_GATE_ENABLE       (1 << 6) /* Disable TX if PLL unlocks */
#define AX_MODCFGA_BROWN_GATE_ENABLE        (1 << 7) /* Disable TX if brownout */

/**
 * 5.17 PLL Parameters ----------------------------------------
 */

/**
 * PLL VCO Current
 */
#define AX_PLLVCOI_ENABLE_MANUAL    (1 << 7)

/**
 * PLL Ranging Clock
 */
#define AX_PLLRNGCLK_DIV_256    0
#define AX_PLLRNGCLK_DIV_512    1
#define AX_PLLRNGCLK_DIV_1024   2
#define AX_PLLRNGCLK_DIV_2048   3
#define AX_PLLRNGCLK_DIV_4096   4
#define AX_PLLRNGCLK_DIV_8192   5
#define AX_PLLRNGCLK_DIV_16384  6
#define AX_PLLRNGCLK_DIV_32768  7

/**
 * 5.22 Packet Controller ----------------------------------------
 */

#define AX_PKT_MAXIMUM_CHUNK_SIZE_1_BYTES       1
#define AX_PKT_MAXIMUM_CHUNK_SIZE_2_BYTES       2
#define AX_PKT_MAXIMUM_CHUNK_SIZE_4_BYTES       3
#define AX_PKT_MAXIMUM_CHUNK_SIZE_8_BYTES       4
#define AX_PKT_MAXIMUM_CHUNK_SIZE_16_BYTES      5
#define AX_PKT_MAXIMUM_CHUNK_SIZE_32_BYTES      6
#define AX_PKT_MAXIMUM_CHUNK_SIZE_64_BYTES      7
#define AX_PKT_MAXIMUM_CHUNK_SIZE_128_BYTES     8
#define AX_PKT_MAXIMUM_CHUNK_SIZE_160_BYTES     9
#define AX_PKT_MAXIMUM_CHUNK_SIZE_192_BYTES     10
#define AX_PKT_MAXIMUM_CHUNK_SIZE_224_BYTES     11
#define AX_PKT_MAXIMUM_CHUNK_SIZE_240_BYTES     12

#define AX_PKT_FLAGS_RSSI_UNITS_MICROSECONDS    (0 << 0)
#define AX_PKT_FLAGS_RSSI_UNITS_BIT_TIME        (1 << 0)
#define AX_PKT_FLAGS_AGC_UNITS_MICROSECONDS     (0 << 1)
#define AX_PKT_FLAGS_AGC_UNITS_BIT_TIME         (1 << 1)
#define AX_PKT_FLAGS_ENABLE_BGND_RSSI           (1 << 2)
#define AX_PKT_FLAGS_AGC_SETTLING_DETECTION     (1 << 3)

#define AX_PKT_STORE_TIMER                  (1 << 0)
#define AX_PKT_STORE_FREQUENCY_OFFSET       (1 << 1)
#define AX_PKT_STORE_RF_OFFSET              (1 << 2)
#define AX_PKT_STORE_DATARATE_OFFSET        (1 << 3)
#define AX_PKT_STORE_RSSI                   (1 << 4)
#define AX_PKT_STORE_CRC_BYTES              (1 << 5)
#define AX_PKT_STORE_RSSI_ON_ANTENNA_SELECT (1 << 6)

#define AX_PKT_ACCEPT_RESIDUE           (1 << 0)
#define AX_PKT_ACCEPT_ABORTED           (1 << 1)
#define AX_PKT_ACCEPT_CRC_FAILURES      (1 << 2)
#define AX_PKT_ACCEPT_ADDRESS_FAILURES  (1 << 3)
#define AX_PKT_ACCEPT_SIZE_FAILURES     (1 << 4)
#define AX_PKT_ACCEPT_MULTIPLE_CHUNKS   (1 << 5)

/**
 * 5.24 Low Power Oscillator --------------------------------------
 */
#define AX_LPOSC_ENABLE     (1 << 0)
#define AX_LPOSC_640_HZ     (0 << 1)
#define AX_LPOSC_10240_HZ   (1 << 1)
#define AX_LPOSC_IRQR       (1 << 2)
#define AX_LPOSC_IRQF       (1 << 3)
#define AX_LPOSC_CALIBF     (1 << 4)
#define AX_LPOSC_CALIBR     (1 << 5)
#define AX_LPOSC_OSC_DOUBLE (1 << 6)
#define AX_LPOSC_OSC_INVERT (1 << 7)

/**
 * 5.25 DAC --------------------------------------
 */
#define AX_DAC_INPUT_DACVALUE       (0)
#define AX_DAC_INPUT_TRKAMPLITUDE   (1)
#define AX_DAC_INPUT_TRKRFFREQUENCY (2)
#define AX_DAC_INPUT_TRKFREQUENCY   (3)
#define AX_DAC_INPUT_FSKDEMOD       (4)
#define AX_DAC_INPUT_AFSKDEMOD      (5)
#define AX_DAC_INPUT_RXSOFTDATA     (6)
#define AX_DAC_INPUT_RSSI           (7)
#define AX_DAC_INPUT_SAMPLE_ROT_I   (8)
#define AX_DAC_INPUT_SAMPLE_ROT_Q   (9)
#define AX_DAC_INPUT_GPADC13        (10)

#define AX_DEC_CLKX2            (1 << 6)
#define AX_DAC_MODE_DELTA_SIGMA (0 << 7)
#define AX_DAC_MODE_PWM         (1 << 7)
