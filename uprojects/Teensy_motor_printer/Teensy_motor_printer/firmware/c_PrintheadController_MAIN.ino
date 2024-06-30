// #define TESTS
#define PRINT_TESTS
// #define PRINT_LEGACY
// #define NOZZLE_FIRE_TEST
// #define NOZZLE_DEBUG_TEST
// #define NOZZLE_LOOP_TIME_TEST
// #define NOZZLE_RUNTIME_TEST
// #define BLINK_STANDARD
// #define BLINK_ON_RX


int
  _allocTracker = 0,
  _deviceState = STATE_STANDBY,
  _currentMicros,
  _previousMicros,
  _deltaMicros,
  _previousOddIndex = 0,
  _previousEvenIndex = 0,
  _leaveVerifyStateAtTime = 4000
  ;
unsigned int
  _printStartTime = 0
  ;
struct HP_Print_Element
  *_p_hppeOddPrevious,
  *_p_hppeEvenPrevious
  ;

bool _pb = false;

void printAllocTracker()
{
  Serial.print( "_allocTracker:  " );
  Serial.println( _allocTracker );
}
void setup()
{
  initSerial();
  initPrintBuffer();
  initNozzleController();
  // printAllocTracker();

  test();

#ifdef NOZZLE_FIRE_TEST
  nozzleFireTest();
#endif  // NOZZLE_FIRE_TEST
#ifdef NOZZLE_LOOP_TIME_TEST
  nttInit();
#endif // NOZZLE_LOOP_TIME_TEST

  // auditNozzleLookup();

  switchState( STATE_CONFIRM_LAUNCH );  // commented-out for testing only!
  // switchState( STATE_AWAIT_VTRI );

}

void loop()
{
  handleDeltaTime();
  cyclicTest();
  
  handleStates();

}

void handleDeltaTime()
{
  _currentMicros = micros();
  _deltaMicros = _currentMicros - _previousMicros;
  _previousMicros = _currentMicros;
}
int getDeltaTime()
{
  return _deltaMicros;
}

void switchState( int updatedState )
{
  _deviceState = updatedState;
}

void handleStates()
{
  // digitalWrite( LED_BUILTIN, HIGH );
  // digitalWrite( LED_BUILTIN, getPrintBufferSize() > 0 );
  // Serial.print( "_deviceState:  0x" );
  // Serial.println( _deviceState, HEX );

  switch( _deviceState )
  {
    case STATE_STANDBY:
    {
      
      // bool ledOn = getPrintBufferSize() > 0;
      
      updateSerial();
      // First check to ensure buffer can receive properly

      const char* Cmd = getRxCommand();
      const char* Svr = getRxSmallRaw();
      const char* Bvr = getRxBigRaw();
      

      if( Cmd != 0 )
      {

        // Serial.println( "Serial RX detected!" );
        // Serial.print( "\tCmd:  \"" );
        // Serial.print( Cmd );
        // Serial.println( "\"" );
        // Serial.print( "\tSvr:  \"" );
        // Serial.print( Svr );
        // Serial.println( "\"" );
        // Serial.print( "\tBvr:  \"" );
        // Serial.print( Bvr );
        // Serial.println( "\"" );

        if( beginsWith( (char*) Cmd, (char*) SCOMM_TOKEN_EOB ) )
        {
          // ledOn = true;
          // Serial.println( "EOB detected, proceeding to analyze buffer" );
          // digitalWrite( LED_BUILTIN, HIGH );
          switchState( STATE_ANALYZE_BUFFER );  // commented-out for testing only!
          // switchState( STATE_VERIFY );
        }
        else if( beginsWith( (char*) Cmd, (char*) SCOMM_TOKEN_VAUD ) )
        {
          auditPrintBuffer();
        }
        else if( beginsWith( (char*) Cmd, (char*) SCOMM_TOKEN_TEST ) )
        {
          switchState( STATE_PRINT_SETUP );
        }
        else if( beginsWith( (char*) Cmd, (char*) SCOMM_TOKEN_PRIME ) )
        {
          prime(10);
        }
        else if( beginsWith( (char*) Cmd, (char*) SCOMM_TOKEN_CLEAR_BUFFER ) )
        {
          clearPrintBuffer();
        }
        else if( beginsWith( (char*) Cmd, (char*) SCOMM_TOKEN_FIRE_SINGLE_ADDRESS ) )
        {
          int
            address = B64_to_B10( (char*) Svr ),
            reps = B64_to_B10( (char*) Bvr )
            ;
          fireSingleAddress( address, reps );
        }
        else if( beginsWith( (char*) Cmd, (char*) SCOMM_TOKEN_FIRE_SINGLE_PRIMITIVE ) )
        {
          int
            primitive = B64_to_B10( (char*) Svr ),
            reps = B64_to_B10( (char*) Bvr )
            ;
          fireSinglePrimitive( primitive, reps );
        }
        // else
        // {
          
        //   switchState( STATE_VERIFY );
        // }
      }
      // clearSerialRxBuffer();


      // awaits comms from motor controller
      // any comm that begins with "SBR" is automatically added to the buffer (buffer is sent over multiple cycles)
      // exit condition is a comm that begins with "EOB" or suchlike
      // digitalWrite( LED_BUILTIN, ledOn );
      break;
    }
    case STATE_ANALYZE_BUFFER:
    {
      analyzeBuffer();
      switchState( STATE_SEND_READY_TO_PRINT );
      // at this state the buffer has been received and needs to be analyzed to determine areas of high detail and low detail, and which nozzles are responsible for more and less detail
      // exit condition is conclusion of buffer analysis
      break;
    }
    case STATE_SEND_READY_TO_PRINT:
    {
      // sendReadyToPrintSignal();  // leave this blank for now, safe to assume the motor controller is ready at this point
      switchState( STATE_AWAIT_VTRI ); // commented out for testing only!
      // switchState( STATE_VERIFY );    // it gets to this point okay
      break;
    }
    case STATE_AWAIT_VTRI:
    {
      // digitalWrite( LED_BUILTIN, HIGH );
      updateSerial();
      const char* Cmd = getRxCommand();
      if( Cmd != 0 )
      {
        // Serial.print( "Cmd:  \"" );
        // Serial.print( Cmd );
        // Serial.println( "\"" );
        // switchState( STATE_VERIFY );  // so this should activate as soon as it gets the VTRI signal
        if( cmpStr( (char*) Cmd, (char*) SCOMM_TOKEN_VTRI ) )
        {
          // digitalWrite( LED_BUILTIN, HIGH );
          // switchState( STATE_VERIFY );  // so this should activate as soon as it gets the VTRI signal
          // switchState( STATE_PRINT_PREHEAT );
          switchState( STATE_PRINT_SETUP );
        }
        else
        {
          // error code goes here
        }
      }
      clearSerialRxBuffer();
      // exit condition is a comm signal that begins with "VTRI"
      break;
    }
    case STATE_PRINT_PREHEAT:
    {
      // digitalWrite( LED_BUILTIN, HIGH );
      //nozzlePreheat( int repetitions )
      for( int i = 0; i < 5; i++ )
      {
        nozzlePreheat( 1000 );
        delay( 200 );
      }
      switchState( STATE_PRINT_SETUP );
    }
    case STATE_PRINT_SETUP:
    {
      digitalWrite( LED_BUILTIN, HIGH );
      // Serial.println( "STATE_PRINT_SETUP" );
      clearVirtualPosition();
      setStartingMicros();
      _p_hppeOddPrevious = getPrintElement( 0 );
      _p_hppeEvenPrevious = getPrintElement( 0 );
      // virtual position is reset to 0
      // exit condition is completion of these tasks
      switchState( STATE_PRINT_SWEEP );
      _printStartTime = micros();
      break;
    }
    case STATE_PRINT_SWEEP:
    {
      // digitalWrite( LED_BUILTIN, HIGH );


      // updateSerial();  // leave this out for now

      // virtual position begins incrementing according to virtual velocity with respect to time
      // during this state, elements from the buffer are fetched according to "the highest position in the buffer that is lower than the virtual position"
      // the print data associated with that buffer element (already converted to useable from serial format) is used to determine which nozzles are enabled during a particular element.
      // nozzles are accessed by way of the address and primitive breakout given by the buffer element, but to help runtime they are also arranged in firing order during startup
      // 
      // exit condition is reaching

      updateVirtualPosition();
      
      int
        oddNozzlePosition = getVirtualPosition( ODD_NOZZLES ),
        evenNozzlePosition = getVirtualPosition( EVEN_NOZZLES ),
        oddBufferIndex,
        evenBufferIndex
        ;

      // Serial.print( oddNozzlePosition );
      // Serial.print( " um   " );
      // Serial.print( evenNozzlePosition );
      // Serial.print( " um   " );
      // Serial.print( getHighestPositionInBuffer() );

      // if( positionIsStillInBuffer( oddNozzlePosition ) )
      // {
      //   struct HP_Print_Element* p_oddHppe = getHighestPrintElementLowerThanOrEqualToPosition( oddNozzlePosition );
      // }
      // if( positionIsStillInBuffer( evenNozzlePosition ) )
      // {
      //   struct HP_Print_Element* p_evenHppe = getHighestPrintElementLowerThanOrEqualToPosition( evenNozzlePosition );
      // }

      bool
        oddComplete = !positionIsStillInBuffer( oddNozzlePosition ),
        evenComplete = !positionIsStillInBuffer( evenNozzlePosition )
        ;
      if( oddComplete && _p_hppeOddPrevious != 0 )
      {
        _p_hppeOddPrevious->SweepCount++;
      }
      if( evenComplete && _p_hppeEvenPrevious != 0 )
      {
        _p_hppeEvenPrevious->SweepCount++;
      }

      setHeadEnable( !(oddComplete || evenComplete) );

      if( oddComplete && evenComplete )
      {
        unsigned int printFinishTime = micros();
        // Serial.println( "\tBoth nozzles are complete" );
        // needs to cycle through all print buffer elements to determine if any elements require more sweeps
        // actually... my software rebuild is so good it seems to get everything in one go.  Keep the multi-sweep framework in case we discover any deficiencies later
        switchState( STATE_STANDBY );  // commented-out for testing only!
        _leaveVerifyStateAtTime = millis() + 4000;
#ifndef PRINT_TESTS
        clearPrintBuffer();
#endif // PRINT_TESTS
        digitalWrite( LED_BUILTIN, LOW );
        Serial.print( printFinishTime - _printStartTime );
        Serial.println( " us" );
        // switchState( STATE_VERIFY );
      }
      else
      {
        struct HP_Print_Element* p_oddHppe = oddComplete ? 0 : getHighestPrintElementLowerThanOrEqualToPosition( oddNozzlePosition, &oddBufferIndex, _previousOddIndex );
        struct HP_Print_Element* p_evenHppe = evenComplete ? 0 : getHighestPrintElementLowerThanOrEqualToPosition( evenNozzlePosition, &evenBufferIndex, _previousEvenIndex );

        // Serial.print( "\tp_oddHppe->Position:  " );
        // if( p_oddHppe != 0 )
        // {
        //   Serial.print( p_oddHppe->Position );
        // }
        // else
        // {
        //   Serial.print( "null" );
        // }
        // Serial.print( "\tp_evenHppe->Position:  " );
        // if( p_evenHppe != 0 )
        // {
        //   Serial.print( p_evenHppe->Position );
        // }
        // else
        // {
        //   Serial.print( "null" );
        // }

        int oddBurstInterval, evenBurstInterval;

        if( p_oddHppe != 0 )
        {
          oddBurstInterval = burstIntervalLookup( p_oddHppe->SweepsRequired );
        }
        else
        {
          oddBurstInterval = NOZZLE_INTERVAL_MICROS_DEFAULT;
        }
        if( p_evenHppe != 0 )
        {
          evenBurstInterval = burstIntervalLookup( p_evenHppe->SweepsRequired );
        }
        else
        {
          evenBurstInterval = NOZZLE_INTERVAL_MICROS_DEFAULT;
        }
        // int
        //   oddBurstInterval = burstIntervalLookup( p_oddHppe->SweepsRequired ),
        //   evenBurstInterval = burstIntervalLookup( p_evenHppe->SweepsRequired )
        //   ;
        if( oddBufferIndex != _previousOddIndex )
        {
          if( _p_hppeOddPrevious != 0 )
          {
            _p_hppeOddPrevious->SweepCount++;
            // Serial.print( "\t_p_hppeOddPrevious->SweepCount:  " );
            // Serial.print( _p_hppeOddPrevious->SweepCount );
          }
        }
        if( evenBufferIndex != _previousEvenIndex )
        {
          if( _p_hppeEvenPrevious != 0 )
          {
            _p_hppeEvenPrevious->SweepCount++;
            // Serial.print( "\t_p_hppeEvenPrevious->SweepCount:  " );
            // Serial.print( _p_hppeEvenPrevious->SweepCount );
          }
        }
#ifdef PRINT_LEGACY
        short p_singleBurst [ ADDRESS_COUNT ];
        for( int i = 0; i < ADDRESS_COUNT; i++ )
        {
          p_singleBurst[i] = p_oddHppe->LegacyBuffer[i] & 0x5555;
          // p_singleBurst[i] |= p_evenHppe->LegacyBuffer[i] & 0xaaaa;
        }
        fireNozzlesLegacy( p_singleBurst );
#endif  // PRINT_LEGACY
#ifndef PRINT_LEGACY
        fireNozzles( p_oddHppe, p_evenHppe, true, false, oddBurstInterval, evenBurstInterval );
#endif  // !PRINT_LEGACY
        _previousOddIndex = oddBufferIndex;
        _previousEvenIndex = evenBufferIndex;
        _p_hppeOddPrevious = p_oddHppe;
        _p_hppeEvenPrevious = p_evenHppe;
      }
      
      // Serial.println( "" );
      break;
    }
    case STATE_ERROR:
    {
      break;
    }
    case STATE_VERIFY:
    {

#ifdef BLINK_ON_RX
    // enableBlink( _pb || ( *Cmd == 'E' ));
    // _pb |= ( *Cmd == 'E' );
    enableBlink(true);

    // Serial.print( "Cmd:  \"" );
    // Serial.print( Cmd );
    // Serial.println( "\"" );


    // Device starts the blinking when Serial receives a transmission.  Moving on to test for correctenss of reception
    // Device starts blinking when addPrintElement(...) completes
    // Testing if device detects EOB signal.
    // Testing if device detects VTRI signal.  
    // Testing run-through of printing
#endif // BLINK_ON_RX
      if( millis() >= _leaveVerifyStateAtTime )
      {
        switchState( STATE_STANDBY );
      }

      break;
    }
    case STATE_CONFIRM_LAUNCH:
    {
      if( millis() >= 4000 )
      {
        digitalWrite( LED_BUILTIN, LOW );
        switchState( STATE_STANDBY );
      }
      else
      {
        digitalWrite( LED_BUILTIN, HIGH );
      }
      break;
    }
  }
}


void allocTracker( int sizeChange )
{
  _allocTracker += sizeChange;
}

// void calculateNozzleDensity( struct NozzleControl* pnc )
// {
//   float
//     dpi = 
// }
