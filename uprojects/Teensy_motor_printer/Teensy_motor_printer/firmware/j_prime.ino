void prime( int burstCount)
{
  Serial.println( "prime()" );
  int
    shalloc = sizeof( short ),
    pshalloc = shalloc * ADDRESS_COUNT
    ;

  short* prmBuffer = (short*) malloc( pshalloc );

  for( int a = 0; a < ADDRESS_COUNT; a++ )
  {
    prmBuffer[a] = -1;
  }

  noInterrupts();
  setHeadEnable(true);

  for( int i = 0; i < burstCount; i++ )
  {
    // reset the address counter
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
        // set the actual primitive pins
        digitalWrite( PRIMITIVE_PIN_MAP[primitive], 0x1 & (prmBuffer[address] >> primitive) );
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
  }


  setHeadEnable(false);
  interrupts();


  free( prmBuffer );
}

void fireSingleAddress( int targetAddress, int burstCount)
{
  // Serial.print( "fireSingleAddress( " );
  // Serial.print( targetAddress );
  // Serial.print( ", " );
  // Serial.print( burstCount );
  // Serial.println( " )" );

  int
    shalloc = sizeof( short ),
    pshalloc = shalloc * ADDRESS_COUNT
    ;

  short* prmBuffer = (short*) malloc( pshalloc );

  for( int a = 0; a < ADDRESS_COUNT; a++ )
  {
    prmBuffer[a] = -1;
  }

  noInterrupts();
  setHeadEnable(true);

  for( int i = 0; i < burstCount; i++ )
  {
    // reset the address counter
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
        // set the actual primitive pins
        digitalWrite( PRIMITIVE_PIN_MAP[primitive], (address == targetAddress) && (0x1 & (prmBuffer[address] >> primitive)) );
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
  }


  setHeadEnable(false);
  interrupts();


  free( prmBuffer );
}

void fireSinglePrimitive( int targetPrimitive, int burstCount )
{
  // Serial.print( "fireSingleAddress( " );
  // Serial.print( targetAddress );
  // Serial.print( ", " );
  // Serial.print( burstCount );
  // Serial.println( " )" );

  int
    shalloc = sizeof( short ),
    pshalloc = shalloc * ADDRESS_COUNT
    ;

  short* prmBuffer = (short*) malloc( pshalloc );

  for( int a = 0; a < ADDRESS_COUNT; a++ )
  {
    prmBuffer[a] = -1;
  }

  noInterrupts();
  setHeadEnable(true);

  for( int i = 0; i < burstCount; i++ )
  {
    // reset the address counter
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
        // set the actual primitive pins
        digitalWrite( PRIMITIVE_PIN_MAP[primitive], (primitive == targetPrimitive) && (0x1 & (prmBuffer[address] >> primitive)) );
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
  }


  setHeadEnable(false);
  interrupts();


  free( prmBuffer );
}