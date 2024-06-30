double
  _virtualPosition = 0.0
  ;
int
  _virtualVelocity = VIRTUAL_VELOCITY_DEFAULT  // position and velocity are given in millimeters (velocity, obviously, is per second)
  ;

void setVirtualVelocity( int virtualVelocity )
{
  if( virtualVelocity < VIRTUAL_VELOCITY_MIN || virtualVelocity >= VIRTUAL_VELOCITY_MAX )
  {
    return;
  }

  _virtualVelocity = virtualVelocity;
}

void clearVirtualPosition()
{
  _virtualPosition = 0;
}

void updateVirtualPosition()
{
  // Serial.print( "updateVirtualPosition()   " );
  double  // using doubles to ensure fractions are not being lost in computation, to avoid propagating fractional errors
    deltaTime = ((double) getDeltaTime())/1000000.0,   // deltaTime given in seconds
    dVel = ((double)_virtualVelocity) * 1000.0,     // dVel given in microns per second
    deltaPosition = dVel * deltaTime                // deltaPosition is given in microns
    ;
  // Serial.print( "deltaTime: ");
  // Serial.print( deltaTime );
  // Serial.print( "us   dVel: " );
  // Serial.print( dVel );
  // Serial.print( "um/s   deltaPosition: ");
  // Serial.print( deltaPosition );
  // Serial.print( "um   _virtualPosition: " );
  
  _virtualPosition += deltaPosition;

#ifdef TESTS
  int testIndex = gHPE_test( (int)_virtualPosition );

  Serial.print( _virtualPosition );
  Serial.print( "um   (" );
  Serial.print( ((int)_virtualPosition) / 1000000 );
  Serial.print( "." );
  int token = (((int)_virtualPosition) / 1000) % 1000;
  Serial.print( token );
  if( token < 10 )
  {
    Serial.print( "00" );
  }
  else if( token < 100 )
  {
    Serial.print( "0" );
  }
  Serial.print( "m)   " );
  Serial.println( testIndex );
#endif // TESTS

}
int getVirtualPosition(int side)
{
  if( side < -1 || side > 1 )
  {
    return -1;
  }
  else if( side == 0 )
  {
    return (int)_virtualPosition;
  }
  // from this point on, side is guaranteed to be either -1 or 1
  int
    rawPosition = (int)_virtualPosition,
    offset = (DISTANCE_BETWEEN_NOZZLES >> 1) * side
    ;
  return rawPosition + offset;
}
