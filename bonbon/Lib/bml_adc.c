#include "bml_adc.h"
#include "Lib/bml_rcc.h"
#include "Lib/bml_nvic.h"

/*
void ADC_Init(int num) {
  ADC_Init(num, ADC_TRIG_POL_DISABLE, 0, 0);
}
*/

void ADC_EasyInit(int num, int channel) {
  ADC_SingleInit(num, ADC_TRIG_POL_DISABLE, ADC_TRIG_POL_DISABLE, 0, 0, channel);
}

void ADC_SingleInit(int num, ADC_TRIG_POL_t trigpol, ADC_TRIG_POL_t jtrigpol, ADC_EXTSEL_t extsel, ADC_JEXTSEL_t jextsel, int channel) {
  volatile ADC_REGS_SINGLE_t *ADC;
  switch (num) {
    case 1:
      ADC = ADC1;
      Rcc->APB2ENR.bits.ADC1EN = 1;
      break;
    case 2:
      ADC = ADC2;
      Rcc->APB2ENR.bits.ADC2EN = 1;
      break;
    case 3:
      ADC = ADC3;
      Rcc->APB2ENR.bits.ADC3EN = 1;
      break;
    default:
      return;
  }

  ADC->CR2.bits.ADON = 1;

  ADC->CR2.bits.EXTEN = trigpol;
  ADC->CR2.bits.JEXTEN = jtrigpol;
  ADC->CR2.bits.EXTSEL = extsel;
  ADC->CR2.bits.JEXTSEL = jextsel;

  ADC->CR2.bits.CONT = 0;
  ADC->CR2.bits.DMA = 0; // disable DMA
  ADC->CR2.bits.DDS = 0;
  ADC->CR2.bits.EOCS = 0;
  ADC->CR2.bits.ALIGN = 0;

  ADC->CR1.bits.EOCIE = 1; // interrupt at end of conversion
  ADC->CR1.bits.JEOCIE = 1; // interrupt at end of injected conversion
  bmlNvicEnableIrq(ADC_IRQn); // enable interrupt at nvic

  ADC->SQR1.bits.L = 0; // number of conversions - 1
  ADC->SQR3.bits.SQ1 = channel;
}

void ADC_SingleConversion(volatile ADC_REGS_SINGLE_t *ADC, int injected) {
  if (injected) {
    ADC->CR2.bits.JSWSTART = 1;
  } else {
    ADC->CR2.bits.SWSTART = 1;
  }
}

unsigned int ADC_Read(volatile ADC_REGS_SINGLE_t *ADC, int injected) {
  if (injected) {
    return ADC->JDR1.value;
  } else {
    return ADC->DR.value;
  }
  }