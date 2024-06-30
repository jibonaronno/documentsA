/**
Useful test buffer input

SBR uN AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
SBR BCu AAAAA////////////////////////////////////////AAAAA
SBR BDY AAAAAgAABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgAABAAAAA
SBR BEC AAAAA////////////////////////////////////////AAAAA
SBR BEt AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

 */

const int

  STATE_STANDBY             = 0x0000,
  STATE_ANALYZE_BUFFER      = 0x0100,
  STATE_SEND_READY_TO_PRINT = 0x0110,
  STATE_AWAIT_VTRI          = 0x0200,
  STATE_PRINT_SETUP         = 0x1000,
  STATE_PRINT_PREHEAT       = 0x1080,
  STATE_PRINT_SWEEP         = 0x1100,
  STATE_PRINT_SWEEP_ODD     = 0x1101,
  STATE_PRINT_SWEEP_EVEN    = 0x1102,
  STATE_ERROR               = 0x2000,
  STATE_VERIFY              = 0x3000,
  STATE_CONFIRM_LAUNCH      = 0x3f00,

  SERIAL_BUFFER_ALLOC = 128,
  HP_COMMAND_LARGE_VALUE_ALLOC = 51,
  PRINT_BUFFER_INITIAL_ALLOC = 300,  // 300 initial allocation is based on previous testing that overwhelmingly demonstrated 300 buffer elements is enough for most high-detail print jobs
  NOZZLE_COUNT = 300,
  ADDRESS_COUNT = 22,
  PRIMITIVE_COUNT = 14,
  PRINT_BUFFER_USED_BYTES_MAX = 50,
  PRINT_ELEMENT_DETAIL_HIGH = 9,
  PRINT_ELEMENT_DETAIL_LOW = 0,
  PRINT_ELEMENT_MAX_SWEEPS = 3,
  NOZZLE_TRANSITION_COUNT_OVERRIDE_THRESHOLD = 1,
  NOZZLE_INTERVAL_MICROS_DEFAULT = 1100, // 1300, //1250,
  NOZZLE_INTERVAL_MICROS_ONE_SWEEP = NOZZLE_INTERVAL_MICROS_DEFAULT,       // keep these zeroed out for now
  NOZZLE_INTERVAL_MICROS_TWO_SWEEPS = NOZZLE_INTERVAL_MICROS_DEFAULT,      
  NOZZLE_INTERVAL_MICROS_THREE_SWEEPS = NOZZLE_INTERVAL_MICROS_DEFAULT,    
  VIRTUAL_VELOCITY_MIN = 0,
  VIRTUAL_VELOCITY_MAX = 40,
  VIRTUAL_VELOCITY_DEFAULT = 15,  // 23 executed in 684095 microseconds

  DISTANCE_BETWEEN_NOZZLES = 4050,

  ODD_NOZZLES = 1,
  EVEN_NOZZLES = -1,

// FYI:  This is how dragonator set all the pins.
//Printhead HP45(        29,              33,         24,         16,         28,         15,         26,         14,         27,         20,          8,         18,           7,          17,          25,          19,              3,              2,          23,             22,          A11,          A10);
//Printhead(uint8_t primclk, uint8_t primclr, uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7, uint8_t p8, uint8_t p9, uint8_t p10, uint8_t p11, uint8_t p12, uint8_t p13, uint8_t addclk, uint8_t addrst, uint8_t hen, uint8_t ncheck, uint8_t stsr, uint8_t s10x) {
//Printhead HP45(29, 33, 24, 16, 28, 15, 26, 14, 27, 20, 8, 18, 7, 17, 25, 19, 3, 2, 23, 22, A11, A10);
//Printhead(uint8_t primclk, uint8_t primclr, uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7, uint8_t p8, uint8_t p9, uint8_t p10, uint8_t p11, uint8_t p12, uint8_t p13, uint8_t addclk, uint8_t addrst, uint8_t hen, uint8_t ncheck, uint8_t stsr, uint8_t s10x) {
/**
    primclk 29    primitiveClock
    primclr 33    primitiveClear
    p0      24
    p1      16
    p2      28
    p3      15
    p4      26
    p5      14
    p6      27
    p7      20
    p8      8
    p9      18
    p10     7
    p11     17
    p12     25
    p13     19
    addclk  3     addressClock
    addrst  2     addressReset
    hen     23    headEnable
    ncheck  22    nozzleCheck
    stsr    A11   senseTSR
    s10x    A10   sense10X
 */
  PRIMITIVE_CLOCK_PIN = 29,
  PRIMITIVE_CLEAR_PIN = 33,
  PRIMITIVE_PIN_MAP [14] = { 24, 16, 28, 15, 26, 14, 27, 20, 8, 18, 7, 17, 25, 19 },
  ADDRESS_CLOCK_PIN = 3,
  ADDRESS_RESET_PIN = 2,
  HEAD_ENABLE_PIN = 23,
  NOZZLE_CHECK_PIN = 22,
  SENSE_TSR_PIN = A11,
  SENSE_10X_PIN = A10,
  SUPPRESSED_NOZZLES_COUNT = 14,
  SUPPRESSED_NOZZLES [SUPPRESSED_NOZZLES_COUNT] = { 8, 36,    43, 69,   132, 170,     172, 178,     184, 196,     243, 255,     293, 299 }
  ;

const char
  *SCOMM_TOKEN_SBR = "SBR",
  *SCOMM_TOKEN_EOB = "EOB",
  *SCOMM_TOKEN_VTRI = "VTRI",
  *SCOMM_TOKEN_VAUD = "VAUD",
  *SCOMM_TOKEN_TEST = "TEST",
  *SCOMM_TOKEN_PRIME = "PRM",
  *SCOMM_TOKEN_CLEAR_BUFFER = "BCL",
  *SCOMM_TOKEN_FIRE_SINGLE_ADDRESS = "FSA",
  *SCOMM_TOKEN_FIRE_SINGLE_PRIMITIVE = "FSP",
  *SCOMM_READY_TO_PRINT_FULL_SIGNAL = "RTP"
  ;