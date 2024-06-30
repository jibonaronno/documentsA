struct HP_Print_Element
{
  int
    Position,
    PrintDataSize,
    TransitionCount,
    Length,
    Detail,
    SweepsRequired,
    SweepCount = 0
    ;
  char PrintData [ HP_COMMAND_LARGE_VALUE_ALLOC ];
#ifdef PRINT_LEGACY
  short LegacyBuffer [ ADDRESS_COUNT ];
#endif  // PRINT_LEGACY

};

struct NozzleControl
{
  char
    Address,
    Primitive,
    ByteIndex,
    BitShamt
    ;
  unsigned long NextBurstAtTime;
  int
    BurstInterval,
    InkDensity,        // this is calculated with each new element in the print buffer
    TransitionCount,
    SweepsSize = 0,
    NozzleNumber
    ;
  // char* P_SweepsRequired;  // suppose a maximum of 300 elements in the print buffer, at 300 nozzle controllers, at one byte per nozzle per buffer element, that's 90,000 bytes
  // char* P_SweepCount;
  bool MoreSweepsRequired;
  bool Suppress;
};
