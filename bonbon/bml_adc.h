/**
 * @file bml_adc.h
 * @brief AD-Wandler Modul auf dem STM32F446RE
 *
 * @defgroup BML_ADC ADC ADC-Treiber
 * @brief Konfiguration und Steuerung des AD-Wandlers
 * @{
 */

#ifndef __BML_ADC
#define __BML_ADC

// Register structs

typedef struct {
  union {
    struct {
      unsigned int AWD   :1;
      unsigned int EOC   :1;
      unsigned int JEOC  :1;
      unsigned int JSTRT :1;
      unsigned int STRT  :1;
      unsigned int OVR   :1;
      unsigned int resv  :26;
    } bits;
    unsigned int all;
  };
} ADC_SR_t;

typedef struct {
  union {
    struct {
      unsigned int AWDCH   :5;
      unsigned int EOCIE   :1;
      unsigned int AWDIE   :1;
      unsigned int JEOCIE  :1;
      unsigned int SCAN    :1;
      unsigned int AWDSGL  :1;
      unsigned int JAUTO   :1;
      unsigned int DISCEN  :1;
      unsigned int JDISCEN :1;
      unsigned int DISCNUM :3;
      unsigned int resv0   :6;
      unsigned int JAWDEN  :1;
      unsigned int AWDEN   :1;
      unsigned int RES     :2;
      unsigned int OVRIE   :1;
      unsigned int resv1   :5;
    } bits;
    unsigned int all;
  };
} ADC_CR1_t;

typedef struct {
  union {
    struct {
      unsigned int ADON     :1;
      unsigned int CONT     :1;
      unsigned int resv0    :6;
      unsigned int DMA      :1;
      unsigned int DDS      :1;
      unsigned int EOCS     :1;
      unsigned int ALIGN    :1;
      unsigned int resv1    :4;
      unsigned int JEXTSEL  :4;
      unsigned int JEXTEN   :2;
      unsigned int JSWSTART :1;
      unsigned int resv2    :1;
      unsigned int EXTSEL   :4;
      unsigned int EXTEN    :2;
      unsigned int SWSTART  :1;
      unsigned int resv3    :1;
    } bits;
    unsigned int all;
  };
} ADC_CR2_t;

typedef struct {
  union {
    struct {
      unsigned int SMP10 :3;
      unsigned int SMP11 :3;
      unsigned int SMP12 :3;
      unsigned int SMP13 :3;
      unsigned int SMP14 :3;
      unsigned int SMP15 :3;
      unsigned int SMP16 :3;
      unsigned int SMP17 :3;
      unsigned int SMP18 :3;
      unsigned int resv  :5;
    } bits;
    unsigned int all;
  };
} ADC_SMPR1_t;

typedef struct {
  union {
    struct {
      unsigned int SMP0 :3;
      unsigned int SMP1 :3;
      unsigned int SMP2 :3;
      unsigned int SMP3 :3;
      unsigned int SMP4 :3;
      unsigned int SMP5 :3;
      unsigned int SMP6 :3;
      unsigned int SMP7 :3;
      unsigned int SMP8 :3;
      unsigned int SMP9 :3;
      unsigned int resv :2;
    } bits;
    unsigned int all;
  };
} ADC_SMPR2_t;

typedef struct {
  unsigned int value :12;
  unsigned int resv  :20;
} ADC_VAL12_t;

typedef struct {
  union {
    struct {
      unsigned int SQ13 :5;
      unsigned int SQ14 :5;
      unsigned int SQ15 :5;
      unsigned int SQ16 :5;
      unsigned int L    :4;
      unsigned int resv :8;
    } bits;
    unsigned int all;
  };
} ADC_SQR1_t;

typedef struct {
  union {
    struct {
      unsigned int SQ7  :5;
      unsigned int SQ8  :5;
      unsigned int SQ9  :5;
      unsigned int SQ10 :5;
      unsigned int SQ11 :5;
      unsigned int SQ12 :5;
      unsigned int resv :2;
    } bits;
    unsigned int all;
  };
} ADC_SQR2_t;

typedef struct {
  union {
    struct {
      unsigned int SQ1  :5;
      unsigned int SQ2  :5;
      unsigned int SQ3  :5;
      unsigned int SQ4  :5;
      unsigned int SQ5  :5;
      unsigned int SQ6  :5;
      unsigned int resv :2;
    } bits;
    unsigned int all;
  };
} ADC_SQR3_t;

typedef struct {
  union {
    struct {
      unsigned int JSQ1 :5;
      unsigned int JSQ2 :5;
      unsigned int JSQ3 :5;
      unsigned int JSQ4 :5;
      unsigned int JL   :2;
      unsigned int resv :10;
    } bits;
    unsigned int all;
  };
} ADC_JSQR_t;

typedef struct {
  unsigned int value :16;
  unsigned int resv  :16;
} ADC_VAL16_t;

typedef struct {
  union {
    unsigned char AWD   :1;
    unsigned char EOC   :1;
    unsigned char JEOC  :1;
    unsigned char JSTRT :1;
    unsigned char STRT  :1;
    unsigned char OVR   :1;
    unsigned char resv  :2;
  };
  unsigned char all;
} ADC_CSR_SINGLE_t;

typedef struct {
  union {
    struct {
      ADC_CSR_SINGLE_t ADC1;
      ADC_CSR_SINGLE_t ADC2;
      ADC_CSR_SINGLE_t ADC3;
      unsigned int resv :8;
    };
    unsigned int all;
  };
} ADC_CSR_t;

typedef struct {
  union {
    struct {
      unsigned int MULTI   :5;
      unsigned int resv0   :3;
      unsigned int DELAY   :4;
      unsigned int resv1   :1;
      unsigned int DDS     :1;
      unsigned int DMA     :2;
      unsigned int ADCPRE  :2;
      unsigned int resv2   :4;
      unsigned int VBATE   :1;
      unsigned int TSVREFE :1;
      unsigned int resv3   :8;
    } bits;
    unsigned int all;
  };
} ADC_CCR_t;

typedef struct {
  union {
    struct {
      unsigned int DATA1 :16;
      unsigned int DATA2 :16;
    } bits;
    unsigned int all;
  };
} ADC_CDR_t;

typedef struct {
  ADC_SR_t SR;
  ADC_CR1_t CR1;
  ADC_CR2_t CR2;
  ADC_SMPR1_t SMPR1;
  ADC_SMPR2_t SMPR2;
  ADC_VAL12_t JOFR1;
  ADC_VAL12_t JOFR2;
  ADC_VAL12_t JOFR3;
  ADC_VAL12_t JOFR4;
  ADC_VAL12_t HTR;
  ADC_VAL12_t LTR;
  ADC_SQR1_t SQR1;
  ADC_SQR2_t SQR2;
  ADC_SQR3_t SQR3;
  ADC_JSQR_t JSQR;
  ADC_VAL16_t JDR1;
  ADC_VAL16_t JDR2;
  ADC_VAL16_t JDR3;
  ADC_VAL16_t JDR4;
  ADC_VAL16_t DR;
} ADC_REGS_SINGLE_t;

typedef struct {
  ADC_CSR_t CSR;
  ADC_CCR_t CCR;
  ADC_CDR_t CDR;
} ADC_REGS_COMMON_t;

// Adressen und Offsets
#define ADC_BASE_ADR 0x40012000
#define ADC_ADC1_OFFSET 0x000
#define ADC_ADC2_OFFSET 0x100
#define ADC_ADC3_OFFSET 0x200
#define ADC_COMMON_OFFSET 0x300

// Zeiger auf Register
#define ADC1 ((volatile ADC_REGS_SINGLE_t *)(ADC_BASE_ADR + ADC_ADC1_OFFSET))
#define ADC2 ((volatile ADC_REGS_SINGLE_t *)(ADC_BASE_ADR + ADC_ADC2_OFFSET))
#define ADC3 ((volatile ADC_REGS_SINGLE_t *)(ADC_BASE_ADR + ADC_ADC3_OFFSET))
#define ADC_COMMON ((volatile ADC_REGS_COMMON_t *)(ADC_BASE_ADR + ADC_COMMON_OFFSET))

typedef enum {
  ADC_EXTSEL_TIM1_CH1    = 0b0000,
  ADC_EXTSEL_TIM1_CH2    = 0b0001,
  ADC_EXTSEL_TIM1_CH3    = 0b0010,
  ADC_EXTSEL_TIM2_CH2    = 0b0011,
  ADC_EXTSEL_TIM2_CH3    = 0b0100,
  ADC_EXTSEL_TIM2_CH4    = 0b0101,
  ADC_EXTSEL_TIM2_TRGO   = 0b0110,
  ADC_EXTSEL_TIM3_CH1    = 0b0111,
  ADC_EXTSEL_TIM3_TRGO   = 0b1000,
  ADC_EXTSEL_TIM5_CH1    = 0b1001,
  ADC_EXTSEL_TIM5_CH2    = 0b1010,
  ADC_EXTSEL_TIM5_CH3    = 0b1011,
  ADC_EXTSEL_TIM5_CH4    = 0b1100,
  ADC_EXTSEL_TIM8_CH1    = 0b1101,
  ADC_EXTSEL_TIM8_TRGO   = 0b1110,
  ADC_EXTSEL_EXTI_LINE11 = 0b1111
} ADC_EXTSEL_t;

typedef enum {
  ADC_JEXTSEL_TIM1_CH4    = 0b0000,
  ADC_JEXTSEL_TIM1_TRGO   = 0b0001,
  ADC_JEXTSEL_TIM2_CH1    = 0b0010,
  ADC_JEXTSEL_TIM2_TRGO   = 0b0011,
  ADC_JEXTSEL_TIM3_CH2    = 0b0100,
  ADC_JEXTSEL_TIM3_CH4    = 0b0101,
  ADC_JEXTSEL_TIM4_CH1    = 0b0110,
  ADC_JEXTSEL_TIM4_CH2    = 0b0111,
  ADC_JEXTSEL_TIM4_CH3    = 0b1000,
  ADC_JEXTSEL_TIM4_TRGO   = 0b1001,
  ADC_JEXTSEL_TIM5_CH4    = 0b1010,
  ADC_JEXTSEL_TIM5_TRGO   = 0b1011,
  ADC_JEXTSEL_TIM8_CH2    = 0b1100,
  ADC_JEXTSEL_TIM8_CH3    = 0b1101,
  ADC_JEXTSEL_TIM8_CH4    = 0b1110,
  ADC_JEXTSEL_EXTI_LINE15 = 0b1111
} ADC_JEXTSEL_t;

typedef enum {
  ADC_TRIG_POL_DISABLE = 0b00,
  ADC_TRIG_POL_RISING  = 0b01,
  ADC_TRIG_POL_FALLING = 0b10,
  ADC_TRIG_POL_BOTH    = 0b11
} ADC_TRIG_POL_t;

/**
 * @brief Initialisiert den Basisbetrieb vom ADCnum Modul mit Single Conversion auf Kanal channel.
 *
 * Diese Funktion initialisiert die ADCnum Register so, dass mit der ADC_SingleConversion() Methode
 * eine Konvertierung angestoßen werden kann (bspw. Periodisch durch Systick).
 * Zum Ende der Konvertierung wird ein Interrupt ausgelöst, in dem dann mit ADC_Read() der Amplitudenwert
 * ausgelesen werden kann.
 *
 * @param[in] num         Zahl des ADC Moduls (1/2/3)
 * @param[in] channel     Kanal des ADC Eingangs, an dem das Analogsignal anliegt
 *
 * @code
 * // AD-Wandler für Additional Function ADC1_IN1 von PA1 initialisieren
 * ADC_EasyInit(1, 1);
 * @endcode
 *
 */
void ADC_EasyInit(int num, int channel);

/**
 * @brief Initialisiert den Basisbetrieb vom ADCnum Modul mit Single Conversion auf Kanal channel.
 *
 * Diese Funktion initialisiert die ADCnum Register so, dass mit der ADC_SingleConversion() Methode
 * eine Konvertierung angestoßen werden kann (bspw. Periodisch durch Systick).
 * Auch durch eine Quelle (j)extsel kann eine Conversion ausgelöst werden.
 * Zum Ende der Konvertierung wird ein Interrupt ausgelöst, in dem dann mit ADC_Read() der Amplitudenwert
 * ausgelesen werden kann.
 * Die Quelle, die die Conversion auslöst, kann angegeben werden.
 *
 * @param[in] num         Zahl des ADC Moduls (1/2/3)
 * @param[in] channel     Kanal des ADC Eingangs, an dem das Analogsignal anliegt
 * @param[in] extsel      Quelle, von der eine Conversion ausgelöst wird
 * @param[in] trigpol     Mit welcher Bedingung das Quellensignal die Conversion auslöst
 * @param[in] jextsel     Quelle, von der eine Injected Conversion ausgelöst wird
 * @param[in] jtrigpol    Mit welcher Bedingung das Quellensignal die Injected Conversion auslöst
 *
 * @code
 * // AD-Wandler für Additional Function ADC1_IN1 von PA1 initialisieren,
 * // sodass der Timer1 an Kanal 1 eine Conversion auslösen kann.
 * // Die injected conversion ist deaktiviert.
 * ADC_SingleInit(1, ADC_TRIG_POL_RISING, ADC_TRIG_POL_DISABLE, ADC_EXTSEL_TIM3_CH1, 0, 1);
 * @endcode
 *
 */
void ADC_SingleInit(int num, ADC_TRIG_POL_t trigpol, ADC_TRIG_POL_t jtrigpol, ADC_EXTSEL_t extsel, ADC_JEXTSEL_t jextsel, int channel);

/**
 * @brief Startet eine Konversion von ADCx
 *
 * Diese Funktion startet eine Konversion des ADCx Moduls.
 * Wenn injected == 1, dann ist es eine injected conversion.
 *
 * @param[in] *ADC        Pointer auf das ADC-Modul-Register
 * @param[in] injected    injected conversion wählen
 *
 * @code
 * // AD-Wandler Konvertierung an ADC1_IN1 starten
 * ADC_SingleConversion(ADC1, 1);
 * @endcode
 *
 */
void ADC_SingleConversion(volatile ADC_REGS_SINGLE_t *ADC, int injected);

/**
 * @brief Liest den AD-gewandelten Wert aus ADCx aus.
 *
 * Mit dieser Funktion kann der Digitalwert nach der AD-Wandlung ausgelesen werden.
 * Wenn injected == 1, dann wird aus dem Register der injected conversion gelesen.
 *
 * @param[in] *ADC        Pointer auf das ADC-Modul-Register
 * @param[in] injected    injected conversion Register wählen
 *
 * @code
 * // Gewandelten Wert aus ADC1 auslesen (reguläre Conversion)
 * unsigned int value = ADC_Read(ADC1, 0);
 * @endcode
 *
 */
unsigned int ADC_Read(volatile ADC_REGS_SINGLE_t *ADC, int injected);

#endif //__BML_ADC