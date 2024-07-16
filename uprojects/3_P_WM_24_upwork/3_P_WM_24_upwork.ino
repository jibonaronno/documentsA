#define SAMPLES 100  // 6.9 kHz
#include <libmaple/dma.h>

dma_tube_config dma_cfg, dma_cfg2, dma_cfg3, dma_cfg4;

int flag1 = 0,  flag2 = 0 , flag3 = 0, flag4 = 0;
int out1 = PB7, out2 = PA8, out3 = PB1, out4 = PA3;
int val1[SAMPLES],  val2[SAMPLES], val3[SAMPLES], val4[SAMPLES];

//============================================ timers  =======================
int amp = 50;
int cnt = 0;
int time_track = 0;
float stp = 6.2831 / SAMPLES;
int ret = 17;

timer_dev *dev1 = PIN_MAP[out1].timer_device;
timer_dev *dev2 = PIN_MAP[out2].timer_device;
timer_dev *dev3 = PIN_MAP[out3].timer_device;
timer_dev *dev4 = PIN_MAP[out4].timer_device;
uint8 cc_channel1 = PIN_MAP[out1].timer_channel;
uint8 cc_channel2 = PIN_MAP[out2].timer_channel;
uint8 cc_channel3 = PIN_MAP[out3].timer_channel;
uint8 cc_channel4 = PIN_MAP[out4].timer_channel;

void fun1()
{
  flag1++;
}

void fun2()
{
  flag2++;
}
void fun3()
{
  flag3++;
}
void fun4()
{
  flag4++;
}
void timer_conf()
{
  //PB7
  timer_dma_set_base_addr(dev1, TIMER_DMA_BASE_CCR2);        //
  timer_dma_set_burst_len(dev1, 1);
  timer_dma_enable_req(dev1, cc_channel1);
  timer_set_reload(dev1, 102);
  timer_set_prescaler(dev1, 0);
  //PA8
  timer_dma_set_base_addr(dev2, TIMER_DMA_BASE_CCR1);        //
  timer_dma_set_burst_len(dev2, 1);
  timer_dma_enable_req(dev2, cc_channel2);
  timer_set_reload(dev2, 102);
  timer_set_prescaler(dev2, 0);
  // PB1 TIM3_CH4 DMA CH3
  timer_dma_set_base_addr(dev3, TIMER_DMA_BASE_CCR4);         //
  timer_dma_set_burst_len(dev3, 1);
  timer_dma_enable_req(dev3, PIN_MAP[out3].timer_channel);   
  timer_set_reload(dev3, 102);
  timer_set_prescaler(dev3, 0);
  //++++++++++++++++++++++++++++++++++
  // PA2 TIM2_CH4 DMA
  timer_dma_set_base_addr(dev4, TIMER_DMA_BASE_CCR3);         //
  timer_dma_set_burst_len(dev4, 1);
  timer_dma_enable_req(dev4, PIN_MAP[out4].timer_channel);   
  timer_set_reload(dev4, 102);
  timer_set_prescaler(dev4, 0);
  //++++++++++++++++++++++++++++++++
}

void dma_conf()
{
  dma_init(DMA1);
  /* T4C2 DMA C4 */
  //PB7
  dma_cfg.tube_dst = &(dev1->regs.gen->DMAR);
  dma_cfg.tube_dst_size = DMA_SIZE_32BITS;
  dma_cfg.tube_src = val1;
  dma_cfg.tube_src_size = DMA_SIZE_32BITS;
  dma_cfg.tube_nr_xfers = SAMPLES;
  dma_cfg.tube_flags = DMA_CFG_SRC_INC | DMA_CFG_CIRC | DMA_CFG_CMPLT_IE;
  dma_cfg.tube_req_src = DMA_REQ_SRC_TIM4_CH2;
  dma_cfg.target_data = 0;
  ret = dma_tube_cfg(DMA1, DMA_CH4, &dma_cfg);

  /* T1C1 DMA C2 */
  //PA8
  dma_cfg.tube_dst = &(dev2->regs.gen->DMAR);
  dma_cfg.tube_dst_size = DMA_SIZE_32BITS;
  dma_cfg.tube_src = val2;
  dma_cfg.tube_src_size = DMA_SIZE_32BITS;
  dma_cfg.tube_nr_xfers = SAMPLES;
  dma_cfg.tube_flags = DMA_CFG_SRC_INC | DMA_CFG_CIRC | DMA_CFG_CMPLT_IE;
  dma_cfg.tube_req_src = DMA_REQ_SRC_TIM1_CH1;
  dma_cfg.target_data = 0;
  ret = dma_tube_cfg(DMA1, DMA_CH2, &dma_cfg);

  // PB1 TIM3_CH4 DMA CH3
  dma_cfg.tube_dst = &(dev3->regs.gen->DMAR);
  dma_cfg.tube_dst_size = DMA_SIZE_32BITS;
  dma_cfg.tube_src = val3;
  dma_cfg.tube_src_size = DMA_SIZE_32BITS;
  dma_cfg.tube_nr_xfers = SAMPLES;
  dma_cfg.tube_flags = DMA_CFG_SRC_INC | DMA_CFG_CIRC;
  dma_cfg.tube_req_src = DMA_REQ_SRC_TIM3_CH4; //
  dma_cfg.target_data = 0;
  ret = dma_tube_cfg(DMA1, DMA_CH3, &dma_cfg);
  //+++++++++++++++++++++
  // PA3 TIM2_CH4 DMA CH1
  dma_cfg.tube_dst = &(dev4->regs.gen->DMAR);
  dma_cfg.tube_dst_size = DMA_SIZE_32BITS;
  dma_cfg.tube_src = val4;
  dma_cfg.tube_src_size = DMA_SIZE_32BITS;
  dma_cfg.tube_nr_xfers = SAMPLES;
  dma_cfg.tube_flags = DMA_CFG_SRC_INC | DMA_CFG_CIRC;
  dma_cfg.tube_req_src = DMA_REQ_SRC_TIM2_CH4;             //****************************
  dma_cfg.target_data = 0;
  ret = dma_tube_cfg(DMA1, DMA_CH1, &dma_cfg);           //????????????
  //+++++++++++++++++++++

}

void dma_start()
{
  dma_attach_interrupt(DMA1, DMA_CH4, fun1);
  dma_enable(DMA1, DMA_CH4);
  timer_resume(dev1);

  dma_attach_interrupt(DMA1, DMA_CH2, fun2);
  dma_enable(DMA1, DMA_CH2);
  timer_resume(dev2);

  // PB1 TIM3_CH4 DMA CH3
    dma_attach_interrupt(DMA1, DMA_CH1, fun3);
  dma_enable(DMA1, DMA_CH3);
  timer_resume(dev3);


  //PA3 TIM2 _CH4
  //+++++++++++++
  dma_attach_interrupt(DMA1, DMA_CH1, fun4);
  dma_enable(DMA1, DMA_CH1);
  timer_resume(dev4);
  //+++++++++++++

}
//============================================ end timers  =======================
void init_wave()
{
  int i;
  for (i = 0; i < SAMPLES; i++)
  {
    val1[i] = 50 + amp * sin(stp * i);    // PB7
    val2[i] = 50 + amp * sin(stp * i);    // PA8
    val3[i] = 50 + amp * sin(stp * i );   // PB1
    val4[i] = 50 + amp * sin(stp * i );   // PA3
  }
}

//+++++++++++++++++++++++++++++++++++++++++++ setup  ++++++++++++++++++++++++++++++
void setup()
{

  int i;
  pinMode(out1, PWM);                     //  PB7
  pinMode(out2, PWM);                     //  PA8
  pinMode(out3, PWM);                     //  PB1
  pinMode(out4, PWM);                     //  PA3

  timer_conf();
  dma_conf();
  dma_start();
  init_wave();

}

//=========================================== end setup  ===========================
void loop()

{
}
