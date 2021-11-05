#ifndef CONIO_H
#define CONIO_H

void create_kbhit_thread( void ) ;

int kbhit (void) ;

int getch(void) ;

//int getche(void) ;

void enable_color_coded_console_display( void ) ;
void disable_color_coded_console_display( void ) ;
bool query_color_coded_console_display_enabled( void ) ;

void set_console_color_to_red( void ) ;
void set_console_color_to_green( void ) ;
void set_console_color_to_blue( void ) ;
void set_console_color_back_to_default( void ) ;



#endif // CONIO_H

