
/*========================
     B L O C K S R A I N
  ========================*/


// Inclusions
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


// Definitions
// ...none...


// Function Prototypes
void printPlane( unsigned char *plane, unsigned int *width, unsigned int *height );
void fillPlane( unsigned char *plane, unsigned char input, unsigned int *size );
void fillLine( unsigned char *plane, unsigned char input, unsigned int line, unsigned int *width, unsigned int *height );
void placeOnPlane( unsigned char *plane, unsigned char input, unsigned int x, unsigned int y, unsigned int *width );
void moveBlocksDown( unsigned char *plane, unsigned int *width, unsigned int *height );
void spawnNewLine( unsigned char *plane, unsigned int *width, unsigned int *max );

// Main
int main( int argc, char* argv[ ] ) {

  // Variables
  unsigned int   delay        = 0;
  unsigned int   maxPerSpawn  = 3;
  unsigned int   screenHeight = 8;
  unsigned int   screenWidth  = 32;
  unsigned int   size         = 256;
  unsigned char *plane        = NULL;

  // Inputs
  printf( "Screen Height:        " );
  scanf( "%i", &screenHeight );
  printf( "Screen Width:         " );
  scanf( "%i", &screenWidth );
  printf( "Max Per Spawn:        " );
  scanf( "%i", &maxPerSpawn );
  printf( "Time Between Spawns:  " );
  scanf( "%i", &delay );

  // Calculations
  size = screenHeight * screenWidth;
  srand( time( 0 ) );

  // Create Block Plane
  plane = ( unsigned char * )malloc( size * sizeof( unsigned char ) );
  fillPlane( plane, ' ', &size );
  printPlane( plane, &screenWidth, &screenHeight );

  // Frst Line
  spawnNewLine( plane, &screenWidth, &maxPerSpawn );
  printPlane( plane, &screenWidth, &screenHeight );
  usleep( delay );

  // Raining
  while( 1 ) {

    moveBlocksDown( plane, &screenWidth, &screenHeight );
    fillLine( plane, ' ', 0, &screenWidth, &screenHeight );
    spawnNewLine( plane, &screenWidth, &maxPerSpawn );
    printPlane( plane, &screenWidth, &screenHeight );
    usleep( delay );

  }

  free( plane );

  return 0;

}


// Function Development

// printPlane - display the block plane.
void printPlane( unsigned char *plane, unsigned int *width, unsigned int *height ) {
  size_t i = 0;  // Height Index
  size_t j = 0;  // Width Index
  for( i = 0; i < *height; i++ ) {
    for ( j = 0; j < *width; j++ ) {
      printf( "%c", plane[ i * ( *width ) + j ] );
    }
    printf( "\n" );
  }
}

// fillPlane - fill entire plane with one character.
void fillPlane( unsigned char *plane, unsigned char input, unsigned int *size ) {
  size_t i = 0;  // Size Index
  for( i = 0; i < *size; i++ ) {
    plane[i] = input;
  }
}

// fillLine - fill entire line with one character.
void fillLine( unsigned char *plane, unsigned char input, unsigned int line, unsigned int *width, unsigned int *height ) {
  size_t i = 0;  // Width Index
  for ( i = 0; i < *width; i++ ) {
    plane[ line * ( *width ) + i ] = input;
  }
}

// placeOnPlace - put a character on a given position in the plane.
void placeOnPlane( unsigned char *plane, unsigned char input, unsigned int x, unsigned int y, unsigned int *width ) {
  plane[ y * ( *width ) + x ] = input;
}

// moveBlocksDown - push all blocks down a column on the plane.
void moveBlocksDown( unsigned char *plane, unsigned int *width, unsigned int *height ) {
  size_t i = 0;                                                             // Height Index
  size_t j = 0;                                                             // Width Index
  for( i = ( *height - 1 ); i >= 1; i-- ) {                                 // Must start at the bottom so as not to overwrite.
    for ( j = 0; j < *width; j++ ) {                                        //   For each element in that column...
      plane[ i * ( *width ) + j ] = plane[ ( i - 1 ) * ( *width ) + j ];    //     Set this one to the one directly above it (-*width)!
    }
  }
}

// spawnNewLine - add new blocks to the top.
void spawnNewLine( unsigned char *plane, unsigned int *width, unsigned int *max ) {
  // Variables
  size_t         i        = 0;                                              // Array Index
  unsigned int   choice   = 0;                                              // Choice Made
  unsigned int   spawnNum = 0;                                              // Number to Spawn
  unsigned char *options  = NULL;                                           // Array for Duplicate Avoidance
  // Prevent Duplicates.
  options = ( unsigned char * )malloc( *width * sizeof( unsigned char ) );  // Create array to store choices, preventing choosing same index twice.
  for( i = 0; i < *width; i++ ) {                                           // For the width (length of this array)...
    options[i] = '0';                                                       //   Fill with '0's to indicate not chosen by default.
  }
  // Perform Spawn
  spawnNum = rand( ) % ( *max );                                            // Make a random choice between 0 to max for how many will spawn.
  for( i = 0; i < spawnNum; i++ ) {                                         // For that amount...
    choice = rand( ) % ( *width );                                          //   Make a random choice from 0 to one less than width.
    if( options[choice] != '0' ) {                                          //   If this one was already chosen...
      i--;                                                                  //     Decrement to have it make another choice.
    } else {                                                                //   Otherwise...
      placeOnPlane( plane, 'O', choice, 0, width );                         //     Place object.
      options[choice] = '1';                                                //     Mark as chosen.
    }
  }

  free( options );                                                          // Free the allocated options array.

}



// END blocksRain.c  - EWG SDG
