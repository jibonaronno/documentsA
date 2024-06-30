struct NozzleControl** _pp_nozzleControllers;
struct NozzleControl** _pp_nozzleFiringOrder;
char* _p_blankBuffer_nozzleFile;

// int
//   _previousOddIndex = -1,
//   _previousEvenIndex = -1
//   ;
int _startingMicros = 0;    // FYI:  It looks like the software can execute consistent with a virtual velocity of about 20.372mm/s

int _hardwareAddress = 0;

void initNozzleController()
{
  initPins();
  nozzleLookupInit();

  int
    ncAlloc = sizeof( struct NozzleControl ),
    pncAlloc = sizeof( struct NozzleControl* ),
    ppncAlloc = pncAlloc * NOZZLE_COUNT
    ;
  
  _pp_nozzleControllers = (struct NozzleControl**) malloc( ppncAlloc );
  allocTracker( ppncAlloc );
  _pp_nozzleFiringOrder = (struct NozzleControl**) malloc( ppncAlloc );
  allocTracker( ppncAlloc );

  for( int nozzleNumber = 0; nozzleNumber < NOZZLE_COUNT; nozzleNumber++ )
  {
    _pp_nozzleControllers[nozzleNumber] = (struct NozzleControl*) malloc( ncAlloc );
    allocTracker( ncAlloc );

    _pp_nozzleControllers[nozzleNumber]->Address = addressLookup(nozzleNumber);
    _pp_nozzleControllers[nozzleNumber]->Primitive = primitiveLookup(nozzleNumber);
    _pp_nozzleControllers[nozzleNumber]->NozzleNumber = nozzleNumber;
    _pp_nozzleControllers[nozzleNumber]->Suppress = false;

    for( int nnSCheck = 0; nnSCheck < SUPPRESSED_NOZZLES_COUNT; nnSCheck++ )
    {
      if( _pp_nozzleControllers[nozzleNumber]->NozzleNumber == SUPPRESSED_NOZZLES[nnSCheck] )
      {
        // Serial.print( "Suppressing Nozzle " );
        // Serial.println( _pp_nozzleControllers[nozzleNumber]->NozzleNumber );
        _pp_nozzleControllers[nozzleNumber]->Suppress = true;
      }
    }

    _pp_nozzleControllers[nozzleNumber]->NextBurstAtTime = 0;
    _pp_nozzleControllers[nozzleNumber]->BurstInterval = 0;
    
    _pp_nozzleControllers[nozzleNumber]->TransitionCount = 0;
    _pp_nozzleControllers[nozzleNumber]->SweepsSize = 0;

    _pp_nozzleControllers[nozzleNumber]->ByteIndex = _pp_nozzleControllers[nozzleNumber]->NozzleNumber / 6;
    _pp_nozzleControllers[nozzleNumber]->BitShamt = _pp_nozzleControllers[nozzleNumber]->NozzleNumber % 6;

    // auditNozzleController( _pp_nozzleControllers[nozzleNumber] );
  }

  int firingOrderSize = 0;
  // Serial.println( "Building Nozzle Firing Order" );
  for( int addr = 0; addr < ADDRESS_COUNT; addr++ )
  {
    for( int prim = 0; prim < PRIMITIVE_COUNT; prim++ )
    {
      for( int nozzleNumber = 0; nozzleNumber < NOZZLE_COUNT; nozzleNumber++ )
      {
        if( _pp_nozzleControllers[nozzleNumber]->Address == addr )
        {
          if( _pp_nozzleControllers[nozzleNumber]->Primitive == prim )
          {
            _pp_nozzleFiringOrder[firingOrderSize++] = _pp_nozzleControllers[nozzleNumber];
          }
        }
      }
      // nozzleNumber = getNozzleNumber( addr, prim );
      // Serial.print( "\taddr:  " );
      // Serial.print( addr );
      // Serial.print( "\tprim:  " );
      // Serial.print( prim );
      // Serial.print( "\tnozzleNumber:  " );
      // Serial.println( nozzleNumber );
      // _pp_nozzleFiringOrder[firingOrderSize++] = _pp_nozzleControllers[nozzleNumber];

      // if( isValidNozzleNumber( nozzleNumber ) )
      // {
      //   // Serial.print( "Firing order:  ( " );
      //   // if( addr < 10 )
      //   // {
      //   //   Serial.print( " " );
      //   // }
      //   // Serial.print( addr );
      //   // Serial.print( " & " );
      //   // if( prim < 10 )
      //   // {
      //   //   Serial.print( " " );
      //   // }
      //   // Serial.print( prim );
      //   // Serial.print( " -> " );
      //   // if( nozzleNumber < 10 )
      //   // {
      //   //   Serial.print( "  " );
      //   // }
      //   // else if( nozzleNumber < 100 )
      //   // {
      //   //   Serial.print( " " );
      //   // }
      //   // Serial.print( nozzleNumber );
      //   // Serial.println( " )" );
      //   _pp_nozzleFiringOrder[firingOrderSize++] = _pp_nozzleControllers[nozzleNumber];
      // }
    }
  }
  // Serial.print( "firingOrderSize:  " );
  // Serial.println( firingOrderSize );

  // Serial.println( "Nozzle Firing Order is as follows:" );
  // int addr, prim, nznum;
  // for( int i = 0; i < NOZZLE_COUNT; i++ )
  // {
  //   addr = (int) _pp_nozzleFiringOrder[i]->Address;
  //   prim = (int) _pp_nozzleFiringOrder[i]->Primitive;
  //   nznum = _pp_nozzleFiringOrder[i]->NozzleNumber;

  //   Serial.print( "\ti:  " );
  //   if( i < 10 )
  //   {
  //     Serial.print( "  " );
  //   }
  //   else if( i < 100 )
  //   {
  //     Serial.print( " " );
  //   }
  //   Serial.print( i );
  //   Serial.print( " \tA:  " );
  //   if( addr < 10 )
  //   {
  //     Serial.print( " " );
  //   }
  //   Serial.print( addr );
  //   Serial.print( " \tP:  " );
  //   if( prim < 10 )
  //   {
  //     Serial.print( " " );
  //   }
  //   Serial.print( prim );
  //   Serial.print( " \t#:  " );
  //   if( nznum < 10 )
  //   {
  //     Serial.print( "  " );
  //   }
  //   else if( nznum < 100 )
  //   {
  //     Serial.print( " " );
  //   }
  //   Serial.println( nznum );

  // }

  _p_blankBuffer_nozzleFile = getBlankBuffer();
}
void initPins()
{
  // PRIMITIVE_CLOCK_PIN = 29,
  // PRIMITIVE_CLEAR_PIN = 33,
  // PRIMITIVE_PIN_MAP [14] = { 24, 16, 28, 15, 26, 14, 27, 20, 8, 18, 7, 17, 25, 19 },
  // ADDRESS_CLOCK_PIN = 3,
  // ADDRESS_RESET_PIN = 2,
  // HEAD_ENABLE_PIN = 23,
  // NOZZLE_CHECK_PIN = 22,
  // SENSE_TSR_PIN = A11,
  // SENSE_10X_PIN = A10,
  pinMode( PRIMITIVE_CLOCK_PIN, OUTPUT );
  pinMode( PRIMITIVE_CLEAR_PIN, OUTPUT );
  pinMode( ADDRESS_CLOCK_PIN, OUTPUT );
  pinMode( ADDRESS_RESET_PIN, OUTPUT );
  pinMode( HEAD_ENABLE_PIN, OUTPUT ); // this closes the ground node of the printhead itself, critical if you want to do... anything
  pinMode( NOZZLE_CHECK_PIN, INPUT );
  pinMode( SENSE_TSR_PIN, INPUT );
  pinMode( SENSE_10X_PIN, INPUT );
  for( int i = 0; i < PRIMITIVE_COUNT; i++ )
  {
    pinMode( PRIMITIVE_PIN_MAP[i], OUTPUT );
  }
}
void setHeadEnable( bool headEnabled )
{
  digitalWrite( HEAD_ENABLE_PIN, headEnabled );
}
void setStartingMicros()
{
  _startingMicros = micros();
}


struct NozzleControl* getNozzleController( int nozzleNumber )
{
  if( !isValidNozzleNumber( nozzleNumber ) )
  {
    return 0;
  }
  return _pp_nozzleControllers[nozzleNumber];
}

// #ifdef NOZZLE_FIRE_TEST
// void setPrevIndices( int prevOdd, int prevEven )
// {
//   // Serial.print( "setPrevIndices( " );
//   // Serial.print( prevOdd );
//   // Serial.print( ", " );
//   // Serial.print( prevEven );
//   // Serial.println( " )" );
//   _previousOddIndex = prevOdd;
//   _previousEvenIndex = prevEven;
// }
// #endif // NOZZLE_FIRE_TEST

#ifdef NOZZLE_LOOP_TIME_TEST
const int NTT_LIST_SIZE_MAX = 100;
int _nttSize = 0;
int* _p_nttStartMicros;
void nttInit()
{
  _p_nttStartMicros = (int*) malloc( NTT_LIST_SIZE_MAX );
}
#endif // NOZZLE_LOOP_TIME_TEST

#ifdef PRINT_LEGACY
void fireNozzlesLegacy( short burst [ 22 ] )
{
  bool bit;

  
  noInterrupts();
  setHeadEnable(true);

  digitalWrite( ADDRESS_RESET_PIN, HIGH );
  delayMicroseconds( 1 );
  digitalWrite( ADDRESS_RESET_PIN, LOW );
  delayMicroseconds( 1 );
  for( int a = 0; a < 22; a++ )
  {
    // next address
    digitalWrite( ADDRESS_CLOCK_PIN, HIGH );
    delayMicroseconds( 1 );
    digitalWrite( ADDRESS_CLOCK_PIN, LOW );
    delayMicroseconds( 1 );

    // start the primitive pin setting
    digitalWrite( PRIMITIVE_CLOCK_PIN, LOW );   // enables the latch
    digitalWrite( PRIMITIVE_CLEAR_PIN, HIGH );  // clears all primitive settings

    for( int pShamt = 0; pShamt < PRIMITIVE_COUNT; pShamt++ )
    {
      bit = 0x1 & (burst[a] >> pShamt);
      // set the actual primitive pins
      digitalWrite( PRIMITIVE_PIN_MAP[pShamt], bit );
    }

    digitalWrite( PRIMITIVE_CLOCK_PIN, HIGH );  // disables the latch

    //NOP delay (12 loops of 8 NOP's is ca 1.8us) (10=1.6, 14=2.1, 17=2.4) taken directly from dragonator's code
    for (uint8_t d = 0; d < 12; d++)
    {
      __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"); //8 NOP's
    }

    digitalWrite( PRIMITIVE_CLEAR_PIN, LOW ); // resets the primitive clear pin for RE-trigger on next go-round
    digitalWrite( PRIMITIVE_CLOCK_PIN, LOW );

  }
  // reset the address counter
  digitalWrite( ADDRESS_RESET_PIN, HIGH );
  delayMicroseconds( 1 );
  digitalWrite( ADDRESS_RESET_PIN, LOW );
  delayMicroseconds( 1 );


  setHeadEnable(false);
  interrupts();

}
#endif // PRINT_LEGACY

#ifndef PRINT_LEGACY
void fireNozzles( struct HP_Print_Element* p_oddHppe, struct HP_Print_Element* p_evenHppe, bool oddOnly, bool evenOnly, int oddBurstInterval, int evenBurstInterval )
{
  // recall the original software iterated from addresses 0 < addr < 22, and subiterated from primitives 0 < 16 (enacting pulse splits so each control cycle only hit a third of the primitives in a single pass)
  // overhead required for a for-loop nested inside another for-loop is considerable, and potentially time-consuming
  // instead, this function is built around having the nozzles arranged in their firing order,
  // which is to say they are arranged such that the first nozzle in the list corresponds to Address 0 Primitive 0, the second corresponds to Address 0 Primitive 1, and so-on
  // The nozzles are arranged in their firing order at startup, these arrangements are not hardcoded.  The Address and Primitive Nozzle arrays in the Nozzle Tables file control the ordering; as such, if they are ever updated with more-accurate information, the nozzles will be arranged accordingly.
  
#ifdef NOZZLE_LOOP_TIME_TEST
  _p_nttStartMicros[_nttSize++] = micros();
#endif // NOZZLE_LOOP_TIME_TEST

#ifdef NOZZLE_RUNTIME_TEST
  long fStartTime = micros();
#endif // NOZZLE_RUNTIME_TEST

#ifdef NOZZLE_DEBUG_TEST
  Serial.print( "fireNozzles( 0x" );
  Serial.print( (int) p_oddHppe, HEX );
  Serial.print( ", 0x" );
  Serial.print( (int) p_evenHppe, HEX );
  // Serial.print( ", " );
  // Serial.print( oddBufferIndex );
  // Serial.print( ", " );
  // Serial.print( evenBufferIndex );
  Serial.print( ", " );
  Serial.print( oddOnly ? "true" : "false" );
  Serial.print( ", " );
  Serial.print( evenOnly ? "true" : "false" );
  Serial.println( " )" );
#endif // NOZZLE_DEBUG_TEST


  noInterrupts();
  setHeadEnable(true);

  digitalWrite( ADDRESS_RESET_PIN, HIGH );
  delayMicroseconds( 1 );
  digitalWrite( ADDRESS_RESET_PIN, LOW );
  delayMicroseconds( 1 );
  // clearAddress();


  char
    address,
    prevAddr = 0,
    // remainingSweeps,
    *currentBuffer,
    *p_evenBuffer = oddOnly ? _p_blankBuffer_nozzleFile : p_evenHppe == 0 ? _p_blankBuffer_nozzleFile : p_evenHppe->PrintData,
    *p_oddBuffer = evenOnly ? _p_blankBuffer_nozzleFile : p_oddHppe == 0 ? _p_blankBuffer_nozzleFile : p_oddHppe->PrintData
    ;
  bool
    nozzleEnable,
    intervalComplete,
    // hasRemainingSweeps,
    // isNewOddIndex = oddBufferIndex == (_previousOddIndex + 1),
    // isNewEvenIndex = evenBufferIndex == (_previousEvenIndex + 1),
    oddIsNonNull = p_oddHppe != 0,
    evenIsNonNull = p_evenHppe != 0
    ;

  int
    nozzleNumber,
    currentMicros = micros(),
    byteIndex,
    bitShamt,
    previousPrimitive = 0
    ;
  // Serial.print( "\t" );
  // Serial.print( currentMicros - _startingMicros );
  // Serial.print( " us" );
#ifdef NOZZLE_DEBUG_TEST
  // Serial.print( "\t isNewOddIndex: " );
  // Serial.println( isNewOddIndex ? "t" : "F" );
  // Serial.print( "\tisNewEvenIndex: " );
  // Serial.println( isNewEvenIndex ? "t" : "F" );
  Serial.print( "\t  oddIsNonNull: " );
  Serial.println( oddIsNonNull ? "t" : "F" );
  Serial.print( "\t evenIsNonNull: " );
  Serial.println( evenIsNonNull ? "t" : "F" );
#endif // NOZZLE_DEBUG_TEST
  struct NozzleControl* p_currentNozzle;

  for( int i = 0; i < NOZZLE_COUNT; i++ )
  {
    // first initialize all iteration-dedicated variables
    p_currentNozzle = _pp_nozzleFiringOrder[i];
    nozzleNumber = p_currentNozzle->NozzleNumber;
    address = p_currentNozzle->Address;
    // remainingSweeps = p_currentNozzle->P_SweepsRequired[(nozzleNumber & 0x1) ? oddBufferIndex : evenBufferIndex] - p_currentNozzle->P_SweepCount[(nozzleNumber & 0x1) ? oddBufferIndex : evenBufferIndex];

#ifdef NOZZLE_DEBUG_TEST
    Serial.print( "\t\ti: " );
    if( i < 10 )
    {
      Serial.print( "  " );
    }
    else if( i < 100 )
    {
      Serial.print( " " );
    }
    Serial.print( i );
    Serial.print( "  nozzleNumber: " );
    Serial.print( nozzleNumber );
    if( nozzleNumber < 10 )
    {
      Serial.print( "  " );
    }
    else if( nozzleNumber < 100 )
    {
      Serial.print( " " );
    }
    Serial.print( (nozzleNumber & 0x1) ? "  [odd]" : " [even]" );
    // Serial.print( "\tcurrBuffInx: " );
    // Serial.print( (nozzleNumber & 0x1) ? oddBufferIndex : evenBufferIndex );
    Serial.print( "  p_currNz: 0x" );
    Serial.print( (int) p_currentNozzle, HEX );
    Serial.print( "  addr: " );
    Serial.print( address, DEC );
    // Serial.print( "  prevAddr: " );
    // Serial.print( prevAddr, DEC );
    Serial.print( "  prim: " );
    Serial.print( p_currentNozzle->Primitive, DEC );
    // Serial.print( "  remSwps: " );
    // Serial.print( remainingSweeps, DEC );
    // Serial.print( "\tp_currentNozzle[...]->P_SweepsRequired: " );
    // Serial.print( p_currentNozzle->P_SweepsRequired[(nozzleNumber & 0x1) ? oddBufferIndex : evenBufferIndex], DEC );
    // Serial.print( "\tp_currentNozzle->P_SweepCount[...]: " );
    // Serial.print( p_currentNozzle->P_SweepCount[(nozzleNumber & 0x1) ? oddBufferIndex : evenBufferIndex], DEC );
#endif // NOZZLE_DEBUG_TEST

    // check to determine if the address counter needs to be advanced & primitive counter cleared
    if( i == 0 || address != prevAddr )
    {
#ifdef NOZZLE_DEBUG_TEST
      Serial.print( "  INCR ADDR CTER" );
#endif // NOZZLE_DEBUG_TEST

      // TODO:  Make sure the elapsed time between executions of this specific conditional code segment are similar to the dragonator's program
      if( i != 0 )
      {
        
        digitalWrite( PRIMITIVE_CLOCK_PIN, HIGH );  // disables the latch

        //NOP delay (12 loops of 8 NOP's is ca 1.8us) (10=1.6, 14=2.1, 17=2.4) taken directly from dragonator's code
        for (uint8_t d = 0; d < 12; d++)
        {
          __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"); //8 NOP's
        }

        digitalWrite( PRIMITIVE_CLEAR_PIN, LOW ); // resets the primitive clear pin for RE-trigger on next go-round
        digitalWrite( PRIMITIVE_CLOCK_PIN, LOW );


        // primitivePinsPostFire();
      }
      // next address
      digitalWrite( ADDRESS_CLOCK_PIN, HIGH );
      delayMicroseconds( 1 );
      digitalWrite( ADDRESS_CLOCK_PIN, LOW );
      delayMicroseconds( 1 );

      // start the primitive pin setting
      digitalWrite( PRIMITIVE_CLOCK_PIN, LOW );   // enables the latch
      digitalWrite( PRIMITIVE_CLEAR_PIN, HIGH );  // clears all primitive settings




      // advanceAddress();
      // primitivePinsPreFire();
      previousPrimitive = 0;
    }

    p_currentNozzle->BurstInterval = nozzleNumber & 0x1 ? oddBurstInterval : evenBurstInterval; // burstIntervalLookup( p_currentNozzle->P_SweepsRequired[(nozzleNumber & 0x1) ? oddBufferIndex : evenBufferIndex] );  // very important to set the burst interval to the correct length for the required sweeps per each buffer element

#ifdef NOZZLE_DEBUG_TEST
    Serial.print( "  prvprm: " );
    Serial.print( previousPrimitive );
    Serial.print( "\tBIntv: " );
    if( p_currentNozzle->BurstInterval < 10 )
    {
      Serial.print( " " );
    }
    Serial.print( p_currentNozzle->BurstInterval );

    Serial.print( intervalComplete ? "  [in cp]" : " [in nc] " );
    Serial.print( "\t_hardwareAddress:  " );
    Serial.print( _hardwareAddress );
    // Serial.print( hasRemainingSweeps ? "  [rm sw]" : " [nr sw] " );
#endif // NOZZLE_DEBUG_TEST

    // byteIndex = nozzleNumber / 6;
    // bitShamt = nozzleNumber % 6;
    // struct HP_Print_Element* p_hppe = ((nozzleNumber & 0x1) ? p_oddHppe : p_evenHppe);
    // short legacyChar = (((nozzleNumber & 0x1) ? p_oddHppe : p_evenHppe)->LegacyBuffer[(int)p_currentNozzle->Address]);
    


    // decide if the nozzle shall be fired
    if(                                                                                                         // these conditionals aren't variablized because it executes much faster without variables
        currentMicros >= p_currentNozzle->NextBurstAtTime &&                                                    // checks to see if its time to fire this nozzle
        // (0x1 & ((((nozzleNumber & 0x1) ? p_oddHppe : p_evenHppe)->LegacyBuffer[(int)p_currentNozzle->Address]) >> p_currentNozzle->Primitive)) &&   // DON'T TOUCH THIS!!!
        // (0x1 & (((nozzleNumber & 0x1) ? p_oddBuffer : p_evenBuffer)[byteIndex] >> bitShamt)) &&  // checks to make sure the buffer has data which requires the nozzle to fire
        (0x1 & (((nozzleNumber & 0x1) ? p_oddBuffer : p_evenBuffer)[49 - (nozzleNumber / 6)] >> (nozzleNumber % 6))) &&  // checks to make sure the buffer has data which requires the nozzle to fire
        !p_currentNozzle->Suppress                                                                              // checks to make sure the nozzle hasn't been suppressed
      )
    {
/*
  so for nozzleNumber = 17
    Byte would be 17/6 = 2
    Shamt would be 17%6 = 5
    Byte 0 corresponds with nozzles 0-5, Byte 1 corresponds with nozzles 6-11, Byte 2 corresponds with nozzles 12-17; within that Byte 2, nozzle 12 would need LRS of 0, 13 LRS 1, 14 LRS 2, 15 LRS 3, 16 LRS 4, 17 LRS 5

  for nozzleNumber = 299
    Byte would be 299/6 = 49
    Shamt would be 299%6 = 5
 */
      digitalWrite( PRIMITIVE_PIN_MAP[p_currentNozzle->Primitive], HIGH );
#ifdef NOZZLE_DEBUG_TEST
      bool nozzleFired = true; // /*(!p_currentNozzle->Suppress) &*/ (0x1 & (((nozzleNumber & 0x1) ? p_oddBuffer : p_evenBuffer)[byteIndex] >> bitShamt));
      Serial.print( "\tset primitive pin " );
      Serial.print( PRIMITIVE_PIN_MAP[p_currentNozzle->Primitive] );
#endif // NOZZLE_DEBUG_TEST


      p_currentNozzle->NextBurstAtTime = currentMicros /*micros()*/ + p_currentNozzle->BurstInterval;
#ifdef NOZZLE_DEBUG_TEST
      Serial.print( "  NxBrst: " );
      Serial.print( p_currentNozzle->NextBurstAtTime );
#endif // NOZZLE_DEBUG_TEST

    }
    else
    {
      digitalWrite( PRIMITIVE_PIN_MAP[p_currentNozzle->Primitive], LOW );
#ifdef NOZZLE_DEBUG_TEST
      bool nozzleFired = true; // /*(!p_currentNozzle->Suppress) &*/ (0x1 & (((nozzleNumber & 0x1) ? p_oddBuffer : p_evenBuffer)[byteIndex] >> bitShamt));
      Serial.print( "\tcleared primitive pin " );
      Serial.print( PRIMITIVE_PIN_MAP[p_currentNozzle->Primitive] );
#endif // NOZZLE_DEBUG_TEST
    }

    if( i == 0 )
    {
  #ifdef NOZZLE_DEBUG_TEST
        Serial.print( "\tclearing Primitive " );
        Serial.print( 0 );
        Serial.print( " (pin " );
        Serial.print( PRIMITIVE_PIN_MAP[ 0 ] );
        Serial.print( ")" );
  #endif // NOZZLE_DEBUG_TEST
      digitalWrite( PRIMITIVE_PIN_MAP[0], LOW );
    }
    else
    {
      while( (previousPrimitive + 1) < p_currentNozzle->Primitive )
      {
  #ifdef NOZZLE_DEBUG_TEST
        Serial.print( "\tclearing Primitive " );
        Serial.print( previousPrimitive % PRIMITIVE_COUNT );
        Serial.print( " (pin " );
        Serial.print( PRIMITIVE_PIN_MAP[ previousPrimitive % PRIMITIVE_COUNT ] );
        Serial.print( ")" );
  #endif // NOZZLE_DEBUG_TEST
        digitalWrite( PRIMITIVE_PIN_MAP[ previousPrimitive % PRIMITIVE_COUNT ], LOW );
        previousPrimitive++;
      }
    }

    

    // set prevAddr to the current address so that the loop can test for new address on the next iteration
    prevAddr = address;
    previousPrimitive = p_currentNozzle->Primitive;

#ifdef NOZZLE_DEBUG_TEST
    Serial.println( "" );
#endif // NOZZLE_DEBUG_TEST
  }

  digitalWrite( PRIMITIVE_CLOCK_PIN, HIGH );  // disables the latch

  //NOP delay (12 loops of 8 NOP's is ca 1.8us) (10=1.6, 14=2.1, 17=2.4) taken directly from dragonator's code
  for (uint8_t d = 0; d < 12; d++)
  {
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"); //8 NOP's
  }

  digitalWrite( PRIMITIVE_CLEAR_PIN, LOW ); // resets the primitive clear pin for RE-trigger on next go-round
  digitalWrite( PRIMITIVE_CLOCK_PIN, LOW );
  
  // reset the address counter
  digitalWrite( ADDRESS_RESET_PIN, HIGH );
  delayMicroseconds( 1 );
  digitalWrite( ADDRESS_RESET_PIN, LOW );
  delayMicroseconds( 1 );


  setHeadEnable(false);
  interrupts();


  // primitivePinsPostFire();
  // clearAddress();

  // set _previous[Odd/Even]Index variables so the function can test for new indices in either nozzle row, and thus will know to increment the appropriate nozzles' sweep counters
  // _previousOddIndex = oddBufferIndex;
  // _previousEvenIndex = evenBufferIndex;

#ifdef NOZZLE_RUNTIME_TEST
  int fEndTime = micros();
  Serial.print( "fireNozzles() executed within " );
  Serial.print( fEndTime - fStartTime );
  Serial.println( "us" );
#endif // NOZZLE_RUNTIME_TEST
#ifdef NOZZLE_LOOP_TIME_TEST
  if( _nttSize == NTT_LIST_SIZE_MAX )
  {
    Serial.println( "Raw times at start of invocation & elapsed time since last invocation" );
    int prevMicros = _p_nttStartMicros[0];
    for( int i = 0; i < _nttSize; i++ )
    {
      Serial.print( "t = " );
      Serial.print( _p_nttStartMicros[i] );
      Serial.print( "us\t")
      Serial.print( _p_nttStartMicros[i] - prevMicros );
      Serial.println( "us" );
      prevMicros = _p_nttStartMicros[i];
    }
    _nttSize = 0;
  }
#endif // NOZZLE_LOOP_TIME_TEST
}

void nozzlePreheat( int repetitions )
{
  noInterrupts();
  setHeadEnable(true);

  for( int i = 0; i < repetitions; i++ )
  {

    digitalWrite( ADDRESS_RESET_PIN, HIGH );
    delayMicroseconds( 1 );
    digitalWrite( ADDRESS_RESET_PIN, LOW );
    delayMicroseconds( 1 );

    for( int address = 0; address < ADDRESS_COUNT; address++ )
    {
      // next address
      digitalWrite( ADDRESS_CLOCK_PIN, HIGH );
      delayMicroseconds( 1 );
      digitalWrite( ADDRESS_CLOCK_PIN, LOW );
      delayMicroseconds( 1 );

      // start the primitive pin setting
      digitalWrite( PRIMITIVE_CLOCK_PIN, LOW );   // enables the latch
      digitalWrite( PRIMITIVE_CLEAR_PIN, HIGH );  // clears all primitive settings

      for( int primitive = 0; primitive < PRIMITIVE_COUNT; primitive++ )
      {
        digitalWrite( PRIMITIVE_PIN_MAP[ primitive ], HIGH );
      }

      digitalWrite( PRIMITIVE_CLOCK_PIN, HIGH );  // disables the latch

      __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"); //18 NOP's, ca. 200ns
      __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"); //18 NOP's, ca. 200ns
      __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"); //18 NOP's, ca. 200ns

      digitalWrite( PRIMITIVE_CLEAR_PIN, LOW ); // resets the primitive clear pin for RE-trigger on next go-round
      digitalWrite( PRIMITIVE_CLOCK_PIN, LOW );

    }

    // reset the address counter
    digitalWrite( ADDRESS_RESET_PIN, HIGH );
    delayMicroseconds( 1 );
    digitalWrite( ADDRESS_RESET_PIN, LOW );
    delayMicroseconds( 1 );

  }

  setHeadEnable(false);
  interrupts();
}

#endif // PRINT_LEGACY

bool moreSweepsRequired()
{
  for( int i = 0; i < NOZZLE_COUNT; i++ )
  {
    if( _pp_nozzleControllers[i]->MoreSweepsRequired )
    {
      return true;
    }
  }

  return false;
}

void primitivePinsPreFire()
{
  digitalWrite( PRIMITIVE_CLOCK_PIN, LOW );   // enable the latch
  digitalWrite( PRIMITIVE_CLEAR_PIN, HIGH );  //
}
void primitivePinsPostFire()
{
  digitalWrite( PRIMITIVE_CLOCK_PIN, HIGH );  // disable the latch
  // this particular combination of assembly no-ops and the for-loop takes 1.8us, which according to dragonator's program, is important.
  // would like for this to be handled in hardware moving forward
  for( int i = 0; i < 12; i++ )
  {
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
  }
  digitalWrite( PRIMITIVE_CLEAR_PIN, LOW );  // may not be necessary if the clear pin on the decade counter is rising-edge-triggered; if it isn't, uncomment this
  digitalWrite( PRIMITIVE_CLOCK_PIN, LOW );  // enabling the latch at the end of the function is probably not necessary


}


void advanceAddress()
{
  digitalWrite( ADDRESS_CLOCK_PIN, LOW );
  delayMicroseconds(1);
  digitalWrite( ADDRESS_CLOCK_PIN, HIGH );
  delayMicroseconds(1);
  digitalWrite( ADDRESS_CLOCK_PIN, LOW );
  delayMicroseconds(1);
  _hardwareAddress++;
}
void clearAddress()
{
  digitalWrite( ADDRESS_RESET_PIN, LOW );
  delayMicroseconds(1);
  digitalWrite( ADDRESS_RESET_PIN, HIGH );
  delayMicroseconds(1);
  digitalWrite( ADDRESS_RESET_PIN, LOW );
  delayMicroseconds(1);
  _hardwareAddress = 0;
}
// void clearPrimitive()
// {
//   // _currentPrimitive = 0;
//   // leave blank for now
// }
int burstIntervalLookup( int sweepsRequired )
{
  switch( sweepsRequired )
  {
    case 1: return NOZZLE_INTERVAL_MICROS_ONE_SWEEP;
    case 2: return NOZZLE_INTERVAL_MICROS_TWO_SWEEPS;
    case 3: return NOZZLE_INTERVAL_MICROS_THREE_SWEEPS;
  }
  return NOZZLE_INTERVAL_MICROS_ONE_SWEEP;
}

// void releaseAllNozzleControllerSweepCounts()
// {
//   for( int i = 0; i < NOZZLE_COUNT; i++ )
//   {
//     releaseNozzleControllerSweepCounts( i );
//   }
// }
// void releaseNozzleControllerSweepCounts( int nozzleNumber )
// {
//   if( !isValidNozzleNumber( nozzleNumber ) )
//   {
//     return;
//   }
//   releaseNozzleControllerSweepCounts( _pp_nozzleControllers[nozzleNumber] );
// }
// void releaseNozzleControllerSweepCounts( struct NozzleControl* p_nc )
// {
//   for( int i = 0; i < p_nc->SweepsSize; i++ )
//   {
//     // free( (void*) p_nc->P_SweepCount[i] );
//     // free( (void*) p_nc->P_SweepsRequired[i] );
//   }
//   p_nc->SweepsSize = 0;
// }
