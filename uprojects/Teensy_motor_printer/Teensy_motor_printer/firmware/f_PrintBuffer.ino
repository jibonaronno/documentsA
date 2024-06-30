struct HP_Print_Element** _pp_printBuffer;
int
  _printBufferAlloc = PRINT_BUFFER_INITIAL_ALLOC,
  _printBufferSize = 0,
  _highestPosition = -1
  ;
char* _p_blankBuffer;

void initPrintBuffer()
{
  // Serial.println( "initPrintBuffer()" );
  int
    // peSize = sizeof(struct HP_Print_Element),
    ppeSize = sizeof(struct HP_Print_Element*),
    pppeSize = _printBufferAlloc * ppeSize
    ;
  
  _pp_printBuffer = (struct HP_Print_Element**) malloc( pppeSize );
  allocTracker( pppeSize );

  // Serial.print( "\t ppeSize:  " );
  // Serial.println( ppeSize );
  // Serial.print( "\tpppeSize:  " );
  // Serial.println( pppeSize );

  // for( int i = 0; i < _printBufferAlloc; i++ )
  // {
  //   _pp_printBuffer[i] = (struct HP_Print_Element*) malloc( peSize );
  //   allocTracker( peSize );
  // }

  _p_blankBuffer = (char*) malloc( HP_COMMAND_LARGE_VALUE_ALLOC );
  allocTracker( HP_COMMAND_LARGE_VALUE_ALLOC );

  for( int i = 0; i < HP_COMMAND_LARGE_VALUE_ALLOC; i++ )
  {
    _p_blankBuffer[i] = 0;
  }


}

int getPrintBufferSize()
{
  return _printBufferSize;
}

void reallocBuffer()
{
  struct HP_Print_Element* pp_temp [_printBufferSize];

  for( int i = 0; i < _printBufferSize; i++ )
  {
    pp_temp[i] = _pp_printBuffer[i];
  }

  free( _pp_printBuffer );
  allocTracker( -_printBufferAlloc );

  _pp_printBuffer = (struct HP_Print_Element**) malloc( _printBufferAlloc <<= 1 );
  allocTracker( _printBufferAlloc );

  for( int i = 0; i < _printBufferSize; i++ )
  {
    _pp_printBuffer[i] = pp_temp[i];
  }


}

void addPrintElement( char* position, char* printData )
{
  // Serial.print( "addPrintElement( 0x" );
  // Serial.print( (int) position, HEX );
  // Serial.print( ", 0x" );
  // Serial.print( (int) printData, HEX );
  // Serial.println( " )" );

  if( printData == 0 || *printData == '\0' )
  {
    // Serial.println( "addPrintElement( Bad args )" );
    return;
  }
  // Serial.print( "addPrintElement( \"" );
  // Serial.print( position );
  // Serial.print( "\", \"" );
  // Serial.print( printData );
  // Serial.println( "\" )" );
  // Serial.print( "\t_printBufferSize:  " );
  // Serial.println( _printBufferSize );
  // Serial.print( "\t_printBufferAlloc:  " );
  // Serial.println( _printBufferAlloc );

  if( _printBufferSize == _printBufferAlloc )
  {
    // Serial.println( "\tReallocating" );
    reallocBuffer();
    // Serial.print( "\t_printBufferSize:  " );
    // Serial.println( _printBufferSize );
    // Serial.print( "\t_printBufferAlloc:  " );
    // Serial.println( _printBufferAlloc );
  }

  int hppeSize = sizeof(struct HP_Print_Element);
  _pp_printBuffer[ _printBufferSize ] = (struct HP_Print_Element*) malloc( hppeSize );
  allocTracker( hppeSize );

#ifdef PRINT_LEGACY
  for( int i = 0; i < ADDRESS_COUNT; i++ )
  {
    _pp_printBuffer[ _printBufferSize ]->LegacyBuffer[i] = 0;
  }
#endif // PRINT_LEGACY

  // Serial.print( "\tAllocated " );
  // Serial.print( hppeSize );
  // Serial.print( " Bytes at 0x" );
  // Serial.println( (long) _pp_printBuffer[_printBufferSize], HEX );

  _pp_printBuffer[ _printBufferSize ]->Position = B64_to_B10( position );
  // Serial.print( "\t_pp_printBuffer[ " );
  // Serial.print( _printBufferSize );
  // Serial.print( " ]->Position:  " );
  // Serial.println( _pp_printBuffer[ _printBufferSize ]->Position );

  _highestPosition = _pp_printBuffer[ _printBufferSize ]->Position > _highestPosition ? _pp_printBuffer[ _printBufferSize ]->Position : _highestPosition;

  // Serial.print( "\t_highestPosition:  " );
  // Serial.println( _highestPosition );

  char* rt = _pp_printBuffer[ _printBufferSize ]->PrintData;
  
  // Serial.print( "\t->PrintData:\t");
  do
  {
    *rt++ = 0x0ff & B64_to_B10(*printData);
    // Serial.print( " " );
    // if( *(rt - 1) < 0x10 )
    // {
    //   Serial.print( "0" );
    // }
    // Serial.print( *(rt - 1), HEX );

  }while( *printData++ != '\0' );

  // Serial.println( "" );

  _pp_printBuffer[ _printBufferSize ]->PrintDataSize = rt - (_pp_printBuffer[ _printBufferSize ]->PrintData);

  // Serial.print( "\t->PrintDataSize:  " );
  // Serial.println( _pp_printBuffer[ _printBufferSize ]->PrintDataSize );

  _pp_printBuffer[ _printBufferSize ]->SweepCount = 0;

  int address, primitive,
    currentNozzle = 0
    ;
  bool nozzleState = false;

#ifdef PRINT_LEGACY
  for( int B = 0; B < _pp_printBuffer[ _printBufferSize ]->PrintDataSize; B++ )
  {
    for( int b = 0; b < 6; b++ )
    {
      address = addressLookup( currentNozzle );
      primitive = primitiveLookup( currentNozzle );
      nozzleState = 0x1 & ((_pp_printBuffer[ _printBufferSize ]->PrintData[B]) >> b);
      _pp_printBuffer[ _printBufferSize ]->LegacyBuffer[address] |= (((int)nozzleState) << primitive);
      currentNozzle++;
    }
  }
#endif // PRINT_LEGACY


  _printBufferSize++;
  // printAllocTracker();
}

void clearPrintBuffer()
{
  int hppeSize = sizeof(struct HP_Print_Element);
  for( int i = 0; i < _printBufferSize; i++ )
  {
    // free( _pp_printBuffer[i] );
    // allocTracker( -hppeSize );

    for( int o = 0; o < _pp_printBuffer[i]->PrintDataSize; o++ )
    {
      _pp_printBuffer[i]->PrintData[o] = 0;
    }
    _pp_printBuffer[i]->Position = 0;
    _pp_printBuffer[i]->PrintDataSize = 0;
    _pp_printBuffer[i]->TransitionCount = 0;
    _pp_printBuffer[i]->Length = 0;
    _pp_printBuffer[i]->Detail = 0;
    _pp_printBuffer[i]->SweepsRequired = 0;
    _pp_printBuffer[i]->SweepCount = 0;
    //     Position,
    // PrintDataSize,
    // TransitionCount,
    // Length,
    // Detail,
    // SweepsRequired,
    // SweepCount = 0

  }
  _printBufferSize = 0;
  _highestPosition = -1;
}

bool isValidPrintElementIndex( int i )
{
  return i >= 0 && i < _printBufferSize;
}

struct HP_Print_Element* getPrintElement(int index)
{
  if( !isValidPrintElementIndex( index ) )
  {
    return 0;
  }

  return _pp_printBuffer[index];
}

int getHighestPositionInBuffer()
{
  return _highestPosition;
}

bool positionIsStillInBuffer( int position )
{
  return position < _highestPosition;
}

#ifdef TESTS
int gHPE_test(int position)
{
  // Serial.print( "gHPE_test( " );
  // Serial.print( position );
  // Serial.println( " )" );

  if( _printBufferSize == 0 )
  {
    // Serial.println( "\tnothing in buffer" );
    return -1;
  }
  struct HP_Print_Element* p_prev = _pp_printBuffer[0];
  struct HP_Print_Element* p_hppe = 0;

  int prevIndex = 0;

  for( int i = 0; i < _printBufferSize; i++ )
  {
    p_hppe = _pp_printBuffer[i];

    // Serial.print( "\t_pp_printBuffer[ " );
    // if( i < 10 )
    // {
    //   Serial.print( " " );
    // }
    // Serial.print( i );
    // Serial.print( " ] = 0x" );
    // Serial.print( (int) p_hppe, HEX );
    // Serial.print( "->PrintData:  " );
    // Serial.print( "(taken as read)" );
    // // for( int o = 0; o < p_hppe->PrintDataSize; o++ )
    // // {
    // //   Serial.print( " " );
    // //   if( p_hppe->PrintData[i] < 0x10 )
    // //   {
    // //     Serial.print( "0" );
    // //   }
    // //   Serial.print( p_hppe->PrintData[i], HEX );
    // // }
    // Serial.print( "\t->Position:  " );
    // Serial.print( p_hppe->Position );

    if( p_hppe->Position == position )
    {
      // Serial.println( "\tFOUND at precise index" );
      return i;
    }
    if( p_hppe->Position > position )
    {
      // Serial.println( "\tFOUND at highest index lower than position" );
      return (i-1) < 0 ? 0 : (i-1);
    }
    // Serial.println( "\tcontinuing" );

    p_prev = p_hppe;
    prevIndex = i;
  }

  // Serial.println( "\tDid not find, returning last index" );
  return prevIndex;
}
#endif // TESTS

struct HP_Print_Element* getHighestPrintElementLowerThanOrEqualToPosition(int position, int* p_index, int startingIndex ) // will probably use this the most
{
  if( _printBufferSize <= 0 )
  {
    *p_index = 0;
    return 0;
  }
  struct HP_Print_Element* p_prev = _pp_printBuffer[0];
  struct HP_Print_Element* p_hppe = 0;

  for( int i = startingIndex; i < _printBufferSize; i++ )
  {
    p_hppe = _pp_printBuffer[i];
    if( p_hppe->Position == position )
    {
      *p_index = i;
      return p_hppe;
    }
    if( p_hppe->Position > position )
    {
      *p_index = i == 0 ? 0 : (i - 1);
      return p_prev;
    }

    p_prev = p_hppe;
  }

  *p_index = _printBufferSize - 1;
  return p_prev;
}
struct HP_Print_Element* getLowestPrintElementGreaterThanOrEqualToPosition(int position)
{
  if( _printBufferSize == 0 )
  {
    return 0;
  }
  int maxIndex = _printBufferSize - 1;
  struct HP_Print_Element* p_prev = _pp_printBuffer[maxIndex];
  struct HP_Print_Element* p_hppe = 0;

  for( int i = maxIndex; i >= 0; i-- )
  {
    p_hppe = _pp_printBuffer[i];
    if( p_hppe->Position == position )
    {
      return p_hppe;
    }
    if( p_hppe->Position < position )
    {
      return p_prev;
    }

    p_prev = p_hppe;
  }

  return p_hppe;
}

int getElementTransitionCountTest( char* buffer, int blen )
{
  // Serial.println( "getElementTransitionCountTest( ..., ... )" );

  char mask = 0x1;
  int currentValue,
    transitionCount = 0
    ;
  bool currentBit, previousBit = buffer[0] & 0x1;

  for( int i = 0; i < blen; i++ )
  {
    // Serial.print( "i:  " );
    // Serial.println( i );
    currentValue = buffer[i];
    // Serial.print( "\tcurrentValue:  " );
    // Serial.print( currentValue );
    // Serial.print( " ( 0x" );
    // if( currentValue < 0x10 )
    // {
    //   Serial.print( "0" );
    // }
    // Serial.print( currentValue, HEX );
    // Serial.println( " )" );

    mask = 0x1;
    for( int shamt = 0; shamt < 6; shamt++ )
    {
      // Serial.print( "\t\tshamt:  " );
      // Serial.print( shamt );
      currentBit = (currentValue & mask) >> shamt;
      // Serial.print( "   mask:  0x" );
      // if( mask < 0x10 )
      // {
      //   Serial.print( "0" );
      // }
      // Serial.print( mask, HEX );
      // Serial.print( "   currentBit:  " );
      // Serial.print( currentBit );
      // Serial.print( "   previousBit:  " );
      // Serial.print( previousBit );

      if( currentBit != previousBit )
      {
        transitionCount++;
      }
      // Serial.print( "   transitionCount:  " );
      // Serial.println( transitionCount );

      mask <<= 1;
      previousBit = currentBit;
    }
  }

  return transitionCount;
}



/**
 *  Analyzes the print data associated with a single element of the Print Data Buffer
 *  Gives an approximation of the complexity of a single element of the Print Data Buffer.
 *  Does not describe WHICH nozzles are firing, only how many nozzles are in a different state from contiguous nozzles.
 *  Does not describe for how long the single element will be used, before the next Print Data Buffer element must be fetched.
 *  The idea is that a higher return value implies that more nozzles are firing and not firing closer together.  Program can then decide to modulate burst interval accordingly.
 *  @param index The index within the Print Data Buffer to be analyzed
 *  @return The count of how many times the nozzles turn on or off relative to the next numerical nozzle
 */
int getElementTransitionCount( int index )
{
  if( !isValidPrintElementIndex( index ) )
  {
    return -1;
  }
  // each element in the print buffer represents some state of the nozzles for some distance with respect to the virtual velocity
  // since the arrangement of the print data in the buffer correlates to the actual image, it is therefore possible to conclude that a lot of successive transitions between 1 and 0 between bits is directly proportional to the complexity of the image
  struct HP_Print_Element* p_hppe = _pp_printBuffer[index];
  char* buffer = p_hppe->PrintData;
  char mask = 0x1;
  int currentValue,
    transitionCount = 0
    ;
  bool currentBit, previousBit = false;

  for( int i = 0; i < p_hppe->PrintDataSize; i++ )
  {
    currentValue = buffer[i];

    mask = 0x1;
    for( int shamt = 0; shamt < 6; shamt++ )
    {
      currentBit = (currentValue & mask) >> shamt;
      if( currentBit != previousBit )
      {
        transitionCount++;
      }
      mask <<= 1;
      previousBit = currentBit;
    }
  }

  return transitionCount;
}

int getElementLength( int index )
{
  if( !isValidPrintElementIndex( index ) )
  {
    return -1;
  }
  int maxIndex = _printBufferSize - 1;

  if( index >= maxIndex )
  {
    return 0; // returns zero for the last valid index since that is the end of print, the last element should be all zeroes anyway so there's nothing to print (else it would continue to print indefinitely absent any programmatic checks for "end-of-buffer")
  }

  struct HP_Print_Element* p_currentHppe = _pp_printBuffer[index];
  struct HP_Print_Element* p_nextHppe = _pp_printBuffer[index + 1];

  return p_nextHppe->Position - p_currentHppe->Position;
}

bool isElementEmpty( int index )
{
  if( !isValidPrintElementIndex( index ) )
  {
    return true;
  }
  for( int i = 0; i < _pp_printBuffer[index]->PrintDataSize; i++ )
  {
    if( _pp_printBuffer[index]->PrintData[i] != 0 )
    {
      return false;
    }
  }
  return true;
}

bool printBufferNozzleLookup( int nozzleNumber, int blen, int* pBufferIndexTarget, int* pBitIndexTarget )
{
  if( nozzleNumber < 0 || nozzleNumber >= NOZZLE_COUNT || blen == 0 )
  {
    return false;
  }
  
  if( pBufferIndexTarget != 0 )
  {
    *pBufferIndexTarget = (nozzleNumber / 6) % blen;
  }
  if( pBitIndexTarget != 0 )
  {
    *pBitIndexTarget = nozzleNumber % 6;
  }
  
  return true;
}

int getNozzleTransitions( int nozzleNumber )
{
  // Serial.print( "getNozzleTransitions( " );
  // Serial.print( nozzleNumber );
  // Serial.println( " )" );
  if( !isValidNozzleNumber( nozzleNumber ) || _printBufferSize <= 0 )
  {
    // Serial.println( "\tExiting, bad number or insufficient buffer size" );
    return -1;
  }
  
  int byteIndex, bitIndex;
  if( !printBufferNozzleLookup( nozzleNumber, 50, &byteIndex, &bitIndex ) )
  {
    // Serial.println( "\tExiting, could not lookup nozzle number" );
    return -1;
  }
  // so within each element of _pp_printBuffer, byteIndex and bitIndex will together point to the information that controls a particular nozzle

  // Serial.print( "\tbyteIndex:  " );
  // Serial.print( byteIndex );
  // Serial.print( "\tbitIndex:  " );
  // Serial.println( bitIndex );

  bool
    currentBit,
    previousBit = 0x1 & (_pp_printBuffer[0]->PrintData[byteIndex] >> bitIndex);
    ;
  int currentValue, transitionCount = 0;

  for( int i = 0; i < _printBufferSize; i++ )
  {
    currentValue = _pp_printBuffer[i]->PrintData[byteIndex];
    currentBit = (currentValue >> bitIndex) & 0x1;

    transitionCount += previousBit != currentBit ? 1 : 0;

    // Serial.print( "\t\tcurrentValue:  ");
    // Serial.print( currentValue );
    // Serial.print( "\tcurrentBit:  " );
    // Serial.print( currentBit );
    // Serial.print( "\tpreviousBit:  " );
    // Serial.print( previousBit );
    // Serial.print( "\ttransitionCount:  " );
    // Serial.println( transitionCount );

    previousBit = currentBit;
  }
  return transitionCount;
}

void analyzeBuffer()  // this should be called immediately after the buffer is done loading; it only needs to be called once per job, so execution time isn't terribly important but should be expedient
{
  // Serial.println( "analyzeBuffer()" );
  int meanNozzleTCount = 0;
  for( int i = 0; i < NOZZLE_COUNT; i++ )  // commented-out for testing only!
  {
    meanNozzleTCount += (getNozzleController(i)->TransitionCount = getNozzleTransitions(i));
  }

  meanNozzleTCount /= NOZZLE_COUNT;

  // Serial.print( "\tmeanNozzleTCount:  " );
  // Serial.println( meanNozzleTCount );

  double
    maxTCount = 0.0,
    minTCount = 300.0
    ;

  for( int i = 0; i < _printBufferSize; i++ )
  {
    _pp_printBuffer[i]->TransitionCount = getElementTransitionCount(i);
    _pp_printBuffer[i]->Length = getElementLength(i);

    maxTCount = _pp_printBuffer[i]->TransitionCount > maxTCount ? _pp_printBuffer[i]->TransitionCount : maxTCount;
    minTCount = _pp_printBuffer[i]->TransitionCount < minTCount ? _pp_printBuffer[i]->TransitionCount : minTCount;
    /**
     *  Working logic:
     *    High transition count for an element = "a lot of detail" (and vice-versa)
     *    If an element has a lot of detail, then the nozzle fire interval should be lowered; likewise, if an element does not have a lot of detail, the nozzle fire interval should be increased.
     *    However, if the element dictates the fire interval should be lowered, and a particular nozzle does not have a lot of transitions, then its fire interval should be increased;
     *    Likewise, if the element dictates the fire interval should be raised, and a particular nozzle does have a lot of transitions, then its fire interval should be lowered
     */

  }
  // step one:  Classify elements according to detail intensity

  for( int i = 0; i < _printBufferSize; i++ )
  {
    
    _pp_printBuffer[i]->Detail = (int) linterp( minTCount, maxTCount, (double) PRINT_ELEMENT_DETAIL_LOW, (double) PRINT_ELEMENT_DETAIL_HIGH, _pp_printBuffer[i]->TransitionCount, true );
    _pp_printBuffer[i]->SweepsRequired = (int) linterp( (double) PRINT_ELEMENT_DETAIL_LOW, (double) PRINT_ELEMENT_DETAIL_HIGH, (double) PRINT_ELEMENT_MAX_SWEEPS, 1.0, _pp_printBuffer[i]->Detail, true );

    // if( isElementEmpty(i) )  // leave this out for now
    // {
    //   _pp_printBuffer[i]->SweepsRequired = 0;
    // }

    // Serial.print( "\tBuffer index " );
    // Serial.print( i );
    // Serial.print( "\tDetail:  " );
    // Serial.print( _pp_printBuffer[i]->Detail );
    // Serial.print( "\tSweepsRequired:  " );
    // Serial.println( _pp_printBuffer[i]->SweepsRequired );
  }
  // Serial.println( "========= BEGINNING NOZZLE ANALYSIS =========" );
  // at this point each element knows how much detail it's responsible for, and can describe as such on a scale of 0-9 (0 being low detail, 9 being high detail)
  // now to transfer this data to the nozzle controllers...

  // had to abandon this plan because it takes up too much memory
  // struct NozzleControl* p_nc;
  // int nozzleTCount;
  // for( int i = 0; i < NOZZLE_COUNT; i++ )
  // {
  //   p_nc = getNozzleController(i);
  //   nozzleTCount = p_nc->TransitionCount;

  //   p_nc->P_SweepsRequired = (char*) malloc( _printBufferSize );
  //   p_nc->P_SweepCount = (char*) malloc( _printBufferSize );
  //   allocTracker( _printBufferSize << 1 );

  //   printAllocTracker();
    
  //   p_nc->SweepsSize = _printBufferSize;

  //   Serial.print( "\tNozzle " );
  //   Serial.print( i );
  //   Serial.print( "\tat 0x" );
  //   Serial.print( (int) p_nc, HEX );
  //   Serial.print( "\tnozzleTCount " );
  //   Serial.print( nozzleTCount );
  //   Serial.print( "\tAllocated " );
  //   Serial.print( _printBufferSize );
  //   Serial.print( " Bytes at 0x" );
  //   Serial.print( (long) p_nc->P_SweepsRequired, HEX );
  //   Serial.println( " (for individual nozzle transition tracking per each buffer element)" );

  //   for( int o = 0; o < _printBufferSize; o++ )  // commented-out for testing only
  //   {
  //     if( nozzleTCount > meanNozzleTCount )     // if the individual nozzle's transition count for the entire job is higher than the override threshold, it should defer to individual print elements to determine sweep count.
  //     {
  //       p_nc->P_SweepsRequired[o] = _pp_printBuffer[o]->SweepsRequired;
  //     }
  //     else                                                                // otherwise, if the nozzle's transition count is less than or equal to the override threshold (which implies the nozzle is responsible for low-detail printing) then sweep count should be maximized
  //     {
  //       p_nc->P_SweepsRequired[o] = PRINT_ELEMENT_MAX_SWEEPS;
  //     }
  //     p_nc->P_SweepCount[o] = 0;
  //     // Serial.print( "\t\tp_nc->P_SweepsRequired[ " );
  //     // Serial.print( o );
  //     // Serial.print( " ]: \t" );
  //     // Serial.print( p_nc->P_SweepsRequired[o], DEC );
  //     // Serial.print( "\t(mean:  " );
  //     // Serial.print( meanNozzleTCount );
  //     // Serial.println( ")" );
  //   }

  //   p_nc->BurstInterval = 0;    // \_ only needs to be zeroed out here; BurstInterval & NextBurstAtTime change depending on how many sweeps are required for a particular buffer element during actual printing
  //   p_nc->NextBurstAtTime = 0;  // /

  //   // auditNozzleController( p_nc );
  //   // Serial.println( "========= END OF NOZZLE =========" );
  // }
}
char* getBlankBuffer()
{
  return _p_blankBuffer;
}
