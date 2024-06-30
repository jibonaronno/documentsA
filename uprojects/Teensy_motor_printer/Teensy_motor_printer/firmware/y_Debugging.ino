void auditPrintBuffer()
{
  Serial.println( "auditPrintBuffer()" );
  struct HP_Print_Element* p_hppe;
  for( int i = 0; i < _printBufferSize; i++ )
  {
// struct HP_Print_Element
// {
//   int
//     Position,
//     PrintDataSize
//     ;
//   char PrintData [ HP_COMMAND_LARGE_VALUE_ALLOC ];
// };
    p_hppe = getPrintElement( i );
    Serial.print( "\ti:  " );
    Serial.print( i );
    Serial.print( "   Position:  ");
    Serial.print( p_hppe->Position );
    Serial.print( "  \tData:  " );
    for( int o = 0; o < p_hppe->PrintDataSize; o++ )
    {
      if( p_hppe->PrintData[o] == 0x0 )
      {
        Serial.print( "     " );
      }
      else
      {
        Serial.print( "[" );
        if( p_hppe->PrintData[o] < 0x10 )
        {
          Serial.print( "0" );
        }
        Serial.print( p_hppe->PrintData[o], HEX );
        Serial.print( "]" );
        if( o < (p_hppe->PrintDataSize - 1) )
        {
          Serial.print( " " );
        }
      }
    }

#ifdef PRINT_LEGACY
    Serial.print( "\tLegacyBuffer:  " );
    for( int o = 0; o < ADDRESS_COUNT; o++ )
    {
      if( p_hppe->LegacyBuffer[o] < 0x10 )
      {
        Serial.print( "000" );
      }
      else if( p_hppe->LegacyBuffer[o] < 0x100 )
      {
        Serial.print( "00" );
      }
      else if( p_hppe->LegacyBuffer[o] < 0x1000 )
      {
        Serial.print( "0" );
      }
      Serial.print(p_hppe->LegacyBuffer[o], HEX );
      Serial.print( " " );
    }
#endif // PRINT_LEGACY
    // Serial.print( p_hppe->PrintData );
    Serial.print( "   Size:  " );
    Serial.print( p_hppe->PrintDataSize );
    Serial.print( "   Transition Count:  " );
    Serial.print( p_hppe->TransitionCount );
    Serial.println( "" );
  }
}
void auditNozzleController( struct NozzleControl* p_nc )
{
  Serial.print( "auditNozzleController( 0x" );
  Serial.print( (long) p_nc, HEX );
  Serial.println( " )" );

  Serial.print( "\t      NozzleNumber:  " );
  Serial.println( p_nc->NozzleNumber );
  Serial.print( "\t           Address:  " );
  Serial.println( p_nc->Address, DEC );
  Serial.print( "\t         Primitive:  " );
  Serial.println( p_nc->Primitive, DEC );
  Serial.print( "\t          Suppress:  " );
  Serial.println( p_nc->Suppress ? "true" : "FALSE" );
  Serial.print( "\t   NextBurstAtTime:  " );
  Serial.println( p_nc->NextBurstAtTime );
  Serial.print( "\t     BurstInterval:  " );
  Serial.println( p_nc->InkDensity );
  Serial.print( "\t   TransitionCount:  " );
  Serial.println( p_nc->TransitionCount );
  Serial.print( "\t         ByteIndex:  " );
  Serial.println( p_nc->ByteIndex, DEC );
  Serial.print( "\t          BitShamt:  " );
  Serial.println( p_nc->BitShamt, DEC );
  // Serial.print( "\t         SweepSize:  " );
  // Serial.println( p_nc->SweepsSize );

  // for( int i = 0; i < p_nc->SweepsSize; i++ )
  // {
  //   Serial.print( "\t\tP_SweepCount / P_SweepsRequired [ " );
  //   Serial.print( i );
  //   Serial.print( " ] \t" );
  //   Serial.print( p_nc->P_SweepCount[i], DEC );
  //   Serial.print( " / " );
  //   Serial.println( p_nc->P_SweepsRequired[i], DEC );

  // }
  // Serial.print( "\tMoreSweepsRequired:  " );
  // Serial.println( p_nc->MoreSweepsRequired );
}

void auditRawBufferFast( char* buffer, int blen )
{
  char* rb = buffer;
  Serial.print( "|" );
  for( int i = 0; i < blen; i++ )
  {
    if( i > 0 )
    {
      Serial.print( " " );
    }
    if( buffer[i] < 0x10 )
    {
      Serial.print( "0");
    }
    Serial.print( buffer[i], HEX );
  }
  Serial.print( "|" );
}
void auditRawBuffer( char* buffer )
{
  Serial.print( "auditRawBuffer( 0x" );
  Serial.print( (int) buffer, HEX );
  Serial.println( " )" );

  char* rb = buffer;

  Serial.print( "\tbuffer:  |" );

  do
  {
    if( rb != buffer )
    {
      Serial.print( " " );
    }
    if( *rb < 0x10 )
    {
      Serial.print( "0");
    }
    Serial.print( *rb, HEX );
  }while( !isLineEnd( *rb++ ) );
  Serial.println( "|" );
}
void auditRawBuffer( char* buffer, int bsz )
{
  Serial.print( "auditRawBuffer( 0x" );
  Serial.print( (int) buffer, HEX );
  Serial.print( ", " );
  Serial.print( bsz );
  Serial.println( " )" );

  char* rb = buffer;

  Serial.print( "\tbuffer:  |" );
  for( int i = 0; i < bsz; i++ )
  {
    if( i != 0 )
    {
      Serial.print( " " );
    }
    if( buffer[i] < 0x10 )
    {
      Serial.print( "0");
    }
    Serial.print( buffer[i], HEX );
  }

  Serial.println( "|" );
}