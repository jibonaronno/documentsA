int B64_to_B10( char c )
{
  int
    ic = (int) c,
    retval = 0
    ;
  
  if( c == 0x2b )
  {
    retval = 62;
  }
  else if( c == 0x2f )
  {
    retval = 63;
  }
  else if( c >= 0x30 && c <= 0x39 )
  {
    retval = ic + 4;
    // '0' -> 52
    // '9' -> 61
  }
  else if( c >= 0x41 && c <= 0x5a )
  {
    retval = ic - 65;
    // 'A' -> 0
    // 'Z' -> 25
  }
  else if( c >= 0x61 && c <= 0x7a )
  {
    char c = 'g';
    retval = ic - 71;
    // 'a' -> 26
    // 'z' -> 51
  }
  else
  {
    // error code should go here
    return 0;
  }

  return retval;
}

/**
 *  Takes a char array, which is a value expressed in base 64, and converts it to a base 10 expression.
 *  Assumes null-terminated input
 */
int B64_to_B10( char* src )
{
  int retval = 0;

  while( *src != '\0' )
  {
    retval *= 64;
    retval += B64_to_B10( *src++ );
  }
  return retval;
}

bool beginsWith( char* src, char* token )
{
  if( *token == '\0' )
  {
    return false;
  }
  while( *token != '\0' )
  {
    if( *src == '\0' )
    {
      return false;
    }
    if( *src++ != *token++ )
    {
      return false;
    }
  }
  return true;
}

int copy( char* src, char* tar )
{
  if( src == 0 || tar == 0 )
  {
    return -1;
  }
  char* rt = tar;
  while( *src != '\0' )
  {
    *rt++ = *src++;
  }
  *rt = '\0';
  return rt - tar;
}

double linterp( double xLowerBound, double xUpperBound, double yAtLowX, double yAtUpperX, double xActual, bool clamp )
{
  // Serial.print( "\t\tlinterp( " );
  // Serial.print( xLowerBound );
  // Serial.print( ", " );
  // Serial.print( xUpperBound );
  // Serial.print( ", " );
  // Serial.print( yAtLowX );
  // Serial.print( ", " );
  // Serial.print( yAtUpperX );
  // Serial.print( ", " );
  // Serial.print( xActual );
  // Serial.print( ", " );
  // Serial.print( clamp ? "clamp" : "no clamp" );
  // Serial.println( " )" );
  
  if( clamp )
  {
    if( xActual < xLowerBound )
    {
      xActual = xLowerBound;
    }
    if( xActual > xUpperBound )
    {
      xActual = xUpperBound;
    }
  }
  double
    dy = yAtUpperX - yAtLowX,
    dx = xUpperBound - xLowerBound,
    dydx = dy / dx,
    dxActual = xActual - xLowerBound,
    dyActual = dxActual * dydx,
    retval = dyActual + yAtLowX
    ;

  // Serial.print( "\t\t\tdydx:  " );
  // Serial.println( dydx );
  // Serial.print( "\t\t\tretval:  " );
  // Serial.print( retval );
  // Serial.println( " (raw)" );

  if( clamp )
  {
    if( dydx > 0 )
    {
      if( retval < yAtLowX )
      {
        retval = yAtLowX;
      }
      if( retval > yAtUpperX )
      {
        retval = yAtUpperX;
      }
    }
    else if( dydx < 0 )
    {
      if( retval > yAtLowX )
      {
        retval = yAtLowX;
      }
      if( retval < yAtUpperX )
      {
        retval = yAtUpperX;
      }
    }
  }
  // Serial.print( "\t\t\tretval:  " );
  // Serial.print( retval );
  // Serial.println( " (refined)" );

  return retval;
  
}

double stdev( double* p_numbers, int nlen, double mean )
{
  if( nlen <= 0 )
  {
    return 0.0;
  }
  double
    squaredDistance,
    rsum = 0.0
    ;
  for( int i = 0; i < nlen; i++ )
  {
    squaredDistance = p_numbers[i] - mean;
    squaredDistance *= squaredDistance;
    rsum += squaredDistance;
  }

  return sqrt( rsum / ((double) nlen) );
}

bool isLineEnd( char c )
{
  return c == '\n' || c == '\r' || c == '\0' || c == 0x0d || c == 0x0a;
}

void reverseBuffer( char* p_buffer, int blen )
{
  char* stack = (char*) malloc( blen );
  char* rb = p_buffer;
  char* rs = stack;

  while( *rb != '\0' )
  {
    *rs++ = *rb++;
  }
  rs--;

  // Serial.println( "p_buffer:" );
  // auditRawBuffer( p_buffer );
  // Serial.println( "stack:" );
  // auditRawBuffer( stack );

  rb = p_buffer;
  while( rs >= stack )
  {
    *rb++ = *rs--;
  }

  free( stack );
  // Serial.println( "p_buffer:" );
  // auditRawBuffer( p_buffer );
  
}

bool cmpStr( char* s0, char* s1 )
{
  while( *s0 != '\0' )
  {
    if( *s0++ != *s1++ )
    {
      return false;
    }
  }
  return *s1 == '\0';
}