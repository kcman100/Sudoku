
#include "conio.h"

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <fcntl.h>

/*
#include <pthread.h>

static const unsigned KEY_BUFFER_SIZE = 64 ;
static int key_buffer[KEY_BUFFER_SIZE] ;
static unsigned key_buffer_add_ptr = 0 ;
static unsigned key_buffer_rmv_ptr = 0 ;

static pthread_mutex_t cs_mutex ;

void *kbhit_thread( void *thread_id )
{
	while( true )
	{
  	struct termios oldattr, newattr;
  	int ch;
  	tcgetattr( STDIN_FILENO, &oldattr );
  	newattr = oldattr;
  	newattr.c_lflag &= ~( ICANON | ECHO );
  	tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
  	ch = getchar();

		// Enter the critical section -- other threads are locked out
 		pthread_mutex_lock( &cs_mutex );  	  
  	
  	key_buffer[key_buffer_add_ptr] = ch ;
  	key_buffer_add_ptr = (key_buffer_add_ptr + 1) & (KEY_BUFFER_SIZE - 1) ;
  	
	  // Leave the critical section -- other threads can now pthread_mutex_lock()
 		pthread_mutex_unlock( &cs_mutex );    	
  	
  	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );

  	//sleep(1) ; // So we do not take 100% CPU ?
  }
}

void create_kbhit_thread( void )
{
  pthread_t kbhit_thread_id ;
  int rc = pthread_create( &kbhit_thread_id, NULL, kbhit_thread, NULL ) ;
  if( rc )
  {
  	printf("Error: Unable to create kbhit thread\r\n") ;
  }	
}

int kbhit( void )
{
	int return_value = (1==0) ;
	
	// Enter the critical section -- other threads are locked out
 	pthread_mutex_lock( &cs_mutex );  	  

	if( key_buffer_rmv_ptr != key_buffer_add_ptr )
		return_value = (1==1) ;
 		
  // Leave the critical section -- other threads can now pthread_mutex_lock()
	pthread_mutex_unlock( &cs_mutex );    	

	return return_value ;	
}

int getch( void )
{
	while( true )
	{
		// Enter the critical section -- other threads are locked out
 		pthread_mutex_lock( &cs_mutex );  	  

		if( key_buffer_rmv_ptr != key_buffer_add_ptr )
		{
			int return_value = key_buffer[key_buffer_rmv_ptr] ;
			key_buffer_rmv_ptr = (key_buffer_rmv_ptr + 1) & (KEY_BUFFER_SIZE - 1) ;
		  // Leave the critical section -- other threads can now pthread_mutex_lock()
 			pthread_mutex_unlock( &cs_mutex );    	
			return return_value ;	
		}
 		
	  // Leave the critical section -- other threads can now pthread_mutex_lock()
 		pthread_mutex_unlock( &cs_mutex );    	
 
  	//sleep(1) ; // So we do not take 100% CPU ?
	}	
}
*/

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

// reads from keypress, doesn't echo
int getch(void)
{
  struct termios oldattr, newattr;
  int ch;
  tcgetattr( STDIN_FILENO, &oldattr );
  newattr = oldattr;
  newattr.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
  return ch;
}


/*
// reads from keypress, echoes
int getche(void)
{
  struct termios oldattr, newattr;
  int ch;
  tcgetattr( STDIN_FILENO, &oldattr );
  newattr = oldattr;
  newattr.c_lflag &= ~( ICANON );
  tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
  return ch;
}
*/

// Color codes

// FG_BLACK = 30
// FG_RED      = 31,
// FG_GREEN    = 32,
// FG_YELLOW = 33
// FG_BLUE     = 34,
// FG_DEFAULT  = 39,
// FG_WHITE = 97

// BG_RED      = 41,
// BG_GREEN    = 42,
// BG_BLUE     = 44,
// BG_DEFAULT  = 49

// FG_DEFAULT = 39, FG_BLACK = 30, FG_RED = 31, FG_GREEN = 32, FG_YELLOW = 33, FG_BLUE = 34, FG_MAGENTA = 35, FG_CYAN = 36, FG_LIGHT_GRAY = 37, FG_DARK_GRAY = 90, FG_LIGHT_RED = 91, FG_LIGHT_GREEN = 92, FG_LIGHT_YELLOW = 93, FG_LIGHT_BLUE = 94, FG_LIGHT_MAGENTA = 95, FG_LIGHT_CYAN = 96, FG_WHITE = 97, BG_RED = 41, BG_GREEN = 42, BG_BLUE = 44, BG_DEFAULT = 49

//echo -e "Normal \e[1mBold \e[21mNormal"
//echo -e "Normal \e[2mDim \e[22mNormal"
//echo -e "Normal \e[4mUnderlined \e[24mNormal"
//echo -e "Normal \e[5mBlink \e[25mNormal"
//echo -e "Normal \e[7minverted \e[27mNormal"
//echo -e "Normal \e[8mHidden \e[28mNormal"

static bool display_color_codes_enabled_flag = true ;


void enable_color_coded_console_display( void )
{
	display_color_codes_enabled_flag = true ;
}

void disable_color_coded_console_display( void )
{
	display_color_codes_enabled_flag = false ;
}

bool query_color_coded_console_display_enabled( void )
{
	return display_color_codes_enabled_flag ;
}

void set_console_color_to_red( void )
{
	if( display_color_codes_enabled_flag )
		printf("\033[31m") ;
}

void set_console_color_to_green( void )
{
	if( display_color_codes_enabled_flag )
		printf("\033[32m") ;
}

void set_console_color_to_blue( void )
{
	if( display_color_codes_enabled_flag )
		printf("\033[33m") ;
}

void set_console_color_back_to_default( void )
{
	if( display_color_codes_enabled_flag )
		printf("\033[39m\033[49m") ;
}