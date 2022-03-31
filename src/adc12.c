#include <driverlib.h>

void adc12_init() {
  // If ref generator busy, WAIT
  while (Ref_A_isRefGenBusy(REF_A_BASE))
    ;

  // Select internal ref = 1.2V
  Ref_A_setReferenceVoltage(REF_A_BASE, REF_A_VREF1_2V);

  // Turn on Reference Voltage
  Ref_A_enableReferenceVoltage(REF_A_BASE);

  // P3.3 功能 3 连接到 ADC A15 端口
  GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN3,
                                              GPIO_TERNARY_MODULE_FUNCTION);
  // 配置 ADC12B
  ADC12_B_initParam initParam = {0};
  initParam.sampleHoldSignalSourceSelect = ADC12_B_SAMPLEHOLDSOURCE_SC;
  initParam.clockSourceSelect = ADC12_B_CLOCKSOURCE_ADC12OSC;
  initParam.clockSourceDivider = ADC12_B_CLOCKDIVIDER_1;
  initParam.clockSourcePredivider = ADC12_B_CLOCKPREDIVIDER__1;
  initParam.internalChannelMap = ADC12_B_NOINTCH;
  ADC12_B_init(ADC12_B_BASE, &initParam);
  ADC12_B_setupSamplingTimer(ADC12_B_BASE, ADC12_B_CYCLEHOLD_16_CYCLES,
                             ADC12_B_CYCLEHOLD_4_CYCLES,
                             ADC12_B_MULTIPLESAMPLESDISABLE);
  // 使能 ADC12B 模块
  ADC12_B_enable(ADC12_B_BASE);

  // Configure Memory Buffer
  /**
   * Base address of the ADC12B Module
   * Configure memory buffer 0
   * Map input A15 to memory buffer 0
   * Vref+ = IntBuffer
   * Vref- = AVss
   * Memory buffer 0 is not the end of a sequence
   */
  ADC12_B_configureMemoryParam configureMemoryParam = {0};
  configureMemoryParam.memoryBufferControlIndex = ADC12_B_MEMORY_0;
  configureMemoryParam.inputSourceSelect = ADC12_B_INPUT_A15;
  configureMemoryParam.refVoltageSourceSelect =
      ADC12_B_VREFPOS_INTBUF_VREFNEG_VSS;
  configureMemoryParam.endOfSequence = ADC12_B_NOTENDOFSEQUENCE;
  configureMemoryParam.windowComparatorSelect =
      ADC12_B_WINDOW_COMPARATOR_DISABLE;
  configureMemoryParam.differentialModeSelect =
      ADC12_B_DIFFERENTIAL_MODE_DISABLE;
  ADC12_B_configureMemory(ADC12_B_BASE, &configureMemoryParam);
  ADC12_B_clearInterrupt(ADC12_B_BASE, 0, ADC12_B_IFG0);
  ADC12_B_enableInterrupt(ADC12_B_BASE, ADC12_B_IE0, 0, 0);
}