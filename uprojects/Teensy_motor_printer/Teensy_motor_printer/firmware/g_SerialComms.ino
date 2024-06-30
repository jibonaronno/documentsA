char* _p_serialRx;
char* _p_command;
char* _p_smallRaw;
char* _p_bigRaw;

void initSerial()
{
  Serial.begin(115200);
  _p_serialRx = (char*) malloc( SERIAL_BUFFER_ALLOC );
  allocTracker( SERIAL_BUFFER_ALLOC );
  _p_command = 0;
  _p_smallRaw = 0;
  _p_bigRaw = 0;
}
void updateSerial()
{
  clearSerialRxBuffer();
  // motor controller will send at most a relatively small, fixed-length buffer in each cycle
  if( Serial.available() )
  {
    // for( int i = 0; i < SERIAL_BUFFER_ALLOC; i++ )
    // {
    //   _p_serialRx[i] = '\0';
    // }
    // auditRawBuffer( _p_serialRx, SERIAL_BUFFER_ALLOC );
    int blen = Serial.readBytes( _p_serialRx, SERIAL_BUFFER_ALLOC );
    char* endFinder = _p_serialRx;

    for( int i = 0; i < blen; i++ )
    {
      if( _p_serialRx[i] < 0x20 )
      {
        _p_serialRx[i] = '\0';
        blen = i;
        break;
      }
    }



    // Serial.print( "Received:  \"" );
    // Serial.print( _p_serialRx );
    // Serial.print( "\" (" );
    // Serial.print( blen );
    // Serial.println( " Bytes)" );

    // auditRawBuffer( _p_serialRx, SERIAL_BUFFER_ALLOC );

    tokenizeBuffer();

    // Serial.print( "\t_p_command:  " );
    // if( _p_command != 0 )
    // {
    //   Serial.print( "\"" );
    //   Serial.print( _p_command );
    //   Serial.println( "\"" );
    // }
    // else
    // {
    //   Serial.println( "null" );
    // }

    // Serial.print( "\t_p_smallRaw:  " );
    // if( _p_smallRaw != 0 )
    // {
    //   Serial.print( "\"" );
    //   Serial.print( _p_smallRaw );
    //   Serial.println( "\"" );
    // }
    // else
    // {
    //   Serial.println( "null" );
    // }

    // Serial.print( "\t_p_bigRaw:  " );
    // if( _p_bigRaw != 0 )
    // {
    //   Serial.print( "\"" );
    //   Serial.print( _p_bigRaw );
    //   Serial.println( "\"" );
    // }
    // else
    // {
    //   Serial.println( "null" );
    // }

    if( beginsWith( _p_serialRx, (char*) SCOMM_TOKEN_SBR ) )  // most comms will begin with SBR, so this case should be handled as speedily as possible
    {
      // Serial.println( "SBR detected!" );
      // char* rs = _p_serialRx;
      // char* p_sPosition = 0;
      // char* p_sPrintData = 0;
      // while( !isLineEnd(*rs) )  // remember Inkjet Commander, and thus the motor controller, terminates lines with \n\r\0 for some reason
      // {
      //   if( *rs == ' ' )
      //   {
      //     *rs = '\0';
      //     if( p_sPosition == 0 )
      //     {
      //       p_sPosition = rs + 1;
      //     }
      //     else if( p_sPrintData == 0 )
      //     {
      //       p_sPrintData = rs + 1;
      //     }
      //     else
      //     {
      //       // error code should go here, since there should only be 2 space chars in the comm
      //     }
      //   }
      //   rs++;
      // }

      // // Serial.println( "Refined buffer follows" );

      // // Serial.println( "Command" );
      // // auditRawBuffer( _p_serialRx );
      
      // // Serial.println( "Position" );
      // // auditRawBuffer( p_sPosition );
      
      // Serial.println( "Data before reversal:" );
      // auditRawBuffer( _p_bigRaw );

      reverseBuffer( _p_bigRaw, 60 );
      
      // Serial.println( "Data after reversal:" );
      // auditRawBuffer( _p_bigRaw );

      addPrintElement( _p_smallRaw, _p_bigRaw);
      clearSerialRxBuffer();

      auditPrintBuffer();

      // Serial.println( "\tAdded print element, serial buffer reset" );
    }

    // auditRawBuffer( _p_serialRx, SERIAL_BUFFER_ALLOC );


  }

}
const char* getRxCommand()
{
  return _p_command;
}
const char* getRxSmallRaw()
{
  return _p_smallRaw;
}
const char* getRxBigRaw()
{
  return _p_bigRaw;
}
// int getSerialRxLength()
// {
//   return _serialRxSize;
// }
// char* getRxSerialBuffer()
// {
//   return _p_serialRx;
// }
void clearSerialRxBuffer()
{
  for( int i = 0; i < SERIAL_BUFFER_ALLOC; i++ )
  {
    _p_serialRx[i] = '\0';
  }
  _p_command = 0;
  _p_smallRaw = 0;
  _p_bigRaw = 0;
}

// assigns the pointers _p_command, _p_smallRaw, and _p_bigRaw to appropriate starting points within the RX buffer, eliminates any newline or carriage return chars, and converts spaces into null chars, so those three pointers become complete, null-terminated strings
void tokenizeBuffer()
{
  _p_command = _p_serialRx;
  _p_smallRaw = 0;
  _p_bigRaw = 0;
  char* rb = _p_serialRx;
  while( *rb != '\0' )
  {
    switch( *rb )
    {
      case '\n':
      case '\r':
      {
        *rb = '\0';
        break;
      }
      case ' ':
      {
        *rb = '\0';
        if( _p_smallRaw == 0 )
        {
          _p_smallRaw = rb + 1;
        }
        else if( _p_bigRaw == 0 )
        {
          _p_bigRaw = rb + 1;
        }
        else
        {
          // error code
        }
        break;
      }
    }
    rb++;
  }
}

bool sendReadyToPrintSignal()
{
  char* buffer = (char*) malloc( 6 );
  char* rb = buffer;
  rb += copy( SCOMM_READY_TO_PRINT_FULL_SIGNAL, rb );
  rb += copy( "\n\r\0", rb );

  Serial.println( buffer );
  free( buffer );

  // Serial.println( "sendReadyToPrintSignal()" );
  // leave blank for now
  return true;
}