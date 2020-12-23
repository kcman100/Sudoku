//---------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#pragma hdrstop

//---------------------------------------------------------------------------

// Test if the input is invalid!
// This can also be used to test if solution is correct !!
bool test_input_validity( int input[9][9] )
{
  // Check each row for the same number twice
  for( int row_index=0 ; row_index<9 ; row_index++ )
  {
    bool numbers_found[10] = {false,false,false,false,false,false,false,false,false,false} ;
    for( int column_index=0 ; column_index<9 ; column_index++ )
      if( input[row_index][column_index] > 0 )
        if( numbers_found[input[row_index][column_index]] != false  )
        {
          printf("Duplicate number (%d) in row %d\r\n",input[row_index][column_index],row_index+1) ;
          return false ;
        }
        else
        {
          numbers_found[input[row_index][column_index]] = true ;
        }
  }

  // Check each column for the same number twice
  for( int column_index=0 ; column_index<9 ; column_index++ )
  {
    bool numbers_found[10] = {false,false,false,false,false,false,false,false,false,false} ;
    for( int row_index=0 ; row_index<9 ; row_index++ )
      if( input[row_index][column_index] > 0 )
        if( numbers_found[input[row_index][column_index]] != false  )
        {
          printf("Duplicate number (%d) in column %d\r\n",input[row_index][column_index],column_index+1) ;
          return false ;
        }
        else
        {
          numbers_found[input[row_index][column_index]] = true ;
        }
  }


    // Table of row-column coordinates for each block
    const struct
      {
        unsigned row_index[9] ;
        unsigned column_index[9] ;
      } block[9]
      =
      {
        {{0,0,0,1,1,1,2,2,2},{0,1,2,0,1,2,0,1,2}},
        {{0,0,0,1,1,1,2,2,2},{3,4,5,3,4,5,3,4,5}},
        {{0,0,0,1,1,1,2,2,2},{6,7,8,6,7,8,6,7,8}},
        {{3,3,3,4,4,4,5,5,5},{0,1,2,0,1,2,0,1,2}},
        {{3,3,3,4,4,4,5,5,5},{3,4,5,3,4,5,3,4,5}},
        {{3,3,3,4,4,4,5,5,5},{6,7,8,6,7,8,6,7,8}},
        {{6,6,6,7,7,7,8,8,8},{0,1,2,0,1,2,0,1,2}},
        {{6,6,6,7,7,7,8,8,8},{3,4,5,3,4,5,3,4,5}},
        {{6,6,6,7,7,7,8,8,8},{6,7,8,6,7,8,6,7,8}},
      } ;

  for( int block_index=0 ; block_index<9 ; block_index++ )
  {
    bool numbers_found[10] = {false,false,false,false,false,false,false,false,false,false} ;

    for( int cell_index=0 ; cell_index<9 ; cell_index++ )
      if( input[block[block_index].row_index[cell_index]][block[block_index].column_index[cell_index]] > 0 )
        if( numbers_found[input[block[block_index].row_index[cell_index]][block[block_index].column_index[cell_index]]] != false  )
        {
          printf("Duplicate number (%d) in 3x3 block %d\r\n",input[block[block_index].row_index[cell_index]][block[block_index].column_index[cell_index]],block_index+1) ;
          return false ;
        }
        else
        {
          numbers_found[input[block[block_index].row_index[cell_index]][block[block_index].column_index[cell_index]]] = true ;
        }
  }


  return true ;
}


#pragma argsused
int main(int argc, char* argv[])
{

  // Okay, list the matrix we want to solve
  // Want values from 1 to 9, 0 means I don't know (need to figure out)
  /*
  int input[9][9] =
    {
      { 0 , 0 , 0 , 5 , 0 , 7 , 4 , 2 , 0 } ,
      { 0 , 3 , 0 , 0 , 4 , 0 , 8 , 7 , 0 } ,
      { 0 , 0 , 4 , 0 , 0 , 0 , 3 , 0 , 0 } ,
      { 0 , 8 , 0 , 0 , 0 , 0 , 0 , 0 , 1 } ,
      { 0 , 0 , 0 , 9 , 6 , 3 , 0 , 0 , 0 } ,
      { 9 , 0 , 0 , 0 , 0 , 0 , 0 , 3 , 0 } ,
      { 0 , 0 , 1 , 0 , 0 , 0 , 7 , 0 , 0 } ,
      { 0 , 4 , 6 , 0 , 8 , 0 , 0 , 9 , 0 } ,
      { 0 , 7 , 2 , 6 , 0 , 1 , 0 , 0 , 0 }
    } ;
  */
  /*
  int input[9][9] =
    {
      { 0 , 5 , 0 , 0 , 6 , 4 , 0 , 0 , 0 } ,
      { 8 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 3 } ,
      { 0 , 0 , 7 , 0 , 0 , 0 , 1 , 6 , 0 } ,
      { 0 , 9 , 6 , 2 , 0 , 0 , 0 , 8 , 0 } ,
      { 5 , 0 , 0 , 9 , 0 , 1 , 0 , 0 , 2 } ,
      { 0 , 3 , 0 , 0 , 0 , 8 , 5 , 7 , 0 } ,
      { 0 , 4 , 9 , 0 , 0 , 0 , 2 , 0 , 0 } ,
      { 7 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 6 } ,
      { 0 , 0 , 0 , 4 , 1 , 0 , 0 , 9 , 0 }
    } ;
  */
  int input[9][9] =
    {
      { 0 , 9 , 0 , 3 , 0 , 0 , 7 , 2 , 0 } ,
      { 0 , 0 , 8 , 0 , 2 , 0 , 9 , 0 , 0 } ,
      { 0 , 0 , 4 , 0 , 0 , 0 , 0 , 0 , 5 } ,
      { 0 , 0 , 0 , 9 , 0 , 0 , 1 , 7 , 0 } ,
      { 9 , 0 , 2 , 0 , 0 , 0 , 3 , 0 , 4 } ,
      { 0 , 8 , 1 , 0 , 0 , 3 , 0 , 0 , 0 } ,
      { 1 , 0 , 0 , 0 , 0 , 0 , 6 , 0 , 0 } ,
      { 0 , 0 , 7 , 0 , 3 , 0 , 4 , 0 , 0 } ,
      { 0 , 2 , 6 , 0 , 0 , 7 , 0 , 9 , 0 }
    } ;

  if( argc > 1 )
  {
    FILE *fp_in = fopen( argv[1] , "rb" ) ;
    if( fp_in != NULL )
    {
    	// Read in matrix
		  for( int row_index=0 ; row_index<9 ; row_index++ )
    	{
      	for( int column_index=0 ; column_index<9 ; column_index++ )
        {
          char in_char = 0 ;
          for( ;; )
          {
          	if( fread( &in_char , sizeof(in_char) , 1 , fp_in ) != 1 )
            {
          		// Error reading in...
              in_char = ' ' ;
          	}
            if( in_char == ' ' )
              break ; // space is a valid character, means no number for that spot
            if( (in_char >= '1') && (in_char <= '9') )
              break ;
          }
          input[row_index][column_index] = in_char & 0xF ; // Works for convertering space to 0 and 1-9 to 1-9
        }
    	}
      fclose( fp_in ) ;
    }
  }
  else
  {
    printf("Usage:  Sudoku <infile>\r\n") ;
    printf("  input file should be the puzzle, with spaces for the blocks that are unknown\r\n") ;
    printf("Example:\r\n") ;
    printf(" 5  64   \r\n") ;
    printf("8       3\r\n") ;
    printf("  7   16 \r\n") ;
    printf(" 962   8 \r\n") ;
    printf("5  9 1  2\r\n") ;
    printf(" 3   857 \r\n") ;
    printf(" 49   2  \r\n") ;
    printf("7       6\r\n") ;
    printf("   41  9 \r\n") ;
    printf("hit any key to exit") ;
    getch() ;
    return 0 ;
  }

  printf("Your input puzzle:\r\n") ;
  for( int row_index=0 ; row_index<9 ; row_index++ )
  {
 		for( int column_index=0 ; column_index<9 ; column_index++ )
      printf("%d",input[row_index][column_index]) ;
    printf("\r\n") ;
  }
  printf("\r\n") ;

  // Okay, should check that an invalid puzzle was not typed in!!!
  if( !test_input_validity( input ) )
  {
    printf("Invalid puzzle, not attempting to solve\r\n") ;
    printf("hit any key to exit\r\n") ;
    getch() ;
    return 0 ;
  }



  // Save original input, in case we have to re-try the solution
  int original_input[9][9] ;

  for( int row_index=0 ; row_index<9 ; row_index++ )
    for( int column_index=0 ; column_index<9 ; column_index++ )
      original_input[row_index][column_index] = input[row_index][column_index] ;

  bool possible_numbers[9][9][9] ;

  // First, make all possible choices possible
  for( int row_index=0 ; row_index<9 ; row_index++ )
    for( int column_index=0 ; column_index<9 ; column_index++ )
      for( int choice_index=0 ; choice_index<9 ; choice_index++ )
        possible_numbers[row_index][column_index][choice_index] = true ;

  int number_of_times_tried = 0 ;

start_over:

  number_of_times_tried++ ;

  // Start eliminating choices, first put in the values we know
  for( int row_index=0 ; row_index<9 ; row_index++ )
    for( int column_index=0 ; column_index<9 ; column_index++ )
      if( input[row_index][column_index] != 0 )
      {
        // Okay, only the 'known' ('given') possible choices for the given inputs
        for( int choice_index=0 ; choice_index<9 ; choice_index++ )
          if( (choice_index+1) != input[row_index][column_index] )
            possible_numbers[row_index][column_index][choice_index] = false ;
      }

  for( ; (1==1) ; )
  {
  // Okay, now eliminate possible choices that are used somewhere else in the same column, row, or block
  for( int row_index=0 ; row_index<9 ; row_index++ )
    for( int column_index=0 ; column_index<9 ; column_index++ )
      if( input[row_index][column_index] != 0 )
      {
        //printf("removing %d found at row %d and column %d\r\n",input[row_index][column_index],row_index,column_index) ;
        //getch() ;

        // remove this value from other rows in this column
        for( int row_loop=0 ; row_loop<9 ; row_loop++ )
          if( row_loop != row_index ) // Don't take out the one we know!
            possible_numbers[row_loop][column_index][input[row_index][column_index]-1] = false ;

        // remove this value from other columns in this row
        for( int column_loop=0 ; column_loop<9 ; column_loop++ )
          if( column_loop != column_index ) // Don't take out the one we know!
            possible_numbers[row_index][column_loop][input[row_index][column_index]-1] = false ;

        // remove this value from others in this block
        if( (row_index >= 0) && (row_index <= 2) && (column_index >= 0) && (column_index <= 2) )
        {
          for( int row_loop=0 ; row_loop<=2 ; row_loop++ )
            for( int column_loop=0 ; column_loop<=2 ; column_loop++ )
              if( (row_loop != row_index) || (column_loop != column_index) )
                possible_numbers[row_loop][column_loop][input[row_index][column_index]-1] = false ;
        }
        else if( (row_index >= 0) && (row_index <= 2) && (column_index >= 3) && (column_index <= 5) )
        {
          for( int row_loop=0 ; row_loop<=2 ; row_loop++ )
            for( int column_loop=3 ; column_loop<=5 ; column_loop++ )
              if( (row_loop != row_index) || (column_loop != column_index) )
                possible_numbers[row_loop][column_loop][input[row_index][column_index]-1] = false ;
        }
        else if( (row_index >= 0) && (row_index <= 2) && (column_index >= 6) && (column_index <= 8) )
        {
          for( int row_loop=0 ; row_loop<=2 ; row_loop++ )
            for( int column_loop=6 ; column_loop<=8 ; column_loop++ )
              if( (row_loop != row_index) || (column_loop != column_index) )
                possible_numbers[row_loop][column_loop][input[row_index][column_index]-1] = false ;
        }
        else if( (row_index >= 3) && (row_index <= 5) && (column_index >= 0) && (column_index <= 2) )
        {
          for( int row_loop=3 ; row_loop<=5 ; row_loop++ )
            for( int column_loop=0 ; column_loop<=2 ; column_loop++ )
              if( (row_loop != row_index) || (column_loop != column_index) )
                possible_numbers[row_loop][column_loop][input[row_index][column_index]-1] = false ;
        }
        else if( (row_index >= 3) && (row_index <= 5) && (column_index >= 3) && (column_index <= 5) )
        {
          for( int row_loop=3 ; row_loop<=5 ; row_loop++ )
            for( int column_loop=3 ; column_loop<=5 ; column_loop++ )
              if( (row_loop != row_index) || (column_loop != column_index) )
                possible_numbers[row_loop][column_loop][input[row_index][column_index]-1] = false ;
        }
        else if( (row_index >= 3) && (row_index <= 5) && (column_index >= 6) && (column_index <= 8) )
        {
          for( int row_loop=3 ; row_loop<=5 ; row_loop++ )
            for( int column_loop=6 ; column_loop<=8 ; column_loop++ )
              if( (row_loop != row_index) || (column_loop != column_index) )
                possible_numbers[row_loop][column_loop][input[row_index][column_index]-1] = false ;
        }
        else if( (row_index >= 6) && (row_index <= 8) && (column_index >= 0) && (column_index <= 2) )
        {
          for( int row_loop=6 ; row_loop<=8 ; row_loop++ )
            for( int column_loop=0 ; column_loop<=2 ; column_loop++ )
              if( (row_loop != row_index) || (column_loop != column_index) )
                possible_numbers[row_loop][column_loop][input[row_index][column_index]-1] = false ;
        }
        else if( (row_index >= 6) && (row_index <= 8) && (column_index >= 3) && (column_index <= 5) )
        {
          for( int row_loop=6 ; row_loop<=8 ; row_loop++ )
            for( int column_loop=3 ; column_loop<=5 ; column_loop++ )
              if( (row_loop != row_index) || (column_loop != column_index) )
                possible_numbers[row_loop][column_loop][input[row_index][column_index]-1] = false ;
        }
        else if( (row_index >= 6) && (row_index <= 8) && (column_index >= 6) && (column_index <= 8) )
        {
          for( int row_loop=6 ; row_loop<=8 ; row_loop++ )
            for( int column_loop=6 ; column_loop<=8 ; column_loop++ )
              if( (row_loop != row_index) || (column_loop != column_index) )
                possible_numbers[row_loop][column_loop][input[row_index][column_index]-1] = false ;
        }
      }

    // Now have we figured out any blocks for sure?
    // Or do we have to start guessing?

    // Okay, put ones we know for sure, back in the 'input' matrix, and solve again
    bool solved_one_flag = false ;
    for( int row_index=0 ; row_index<9 ; row_index++ )
      for( int column_index=0 ; column_index<9 ; column_index++ )
        if( input[row_index][column_index] == 0 )
        {
          int number_of_possibles = 0 ;
          int only_possible_choice_index = 0 ;
          for( int choice_index=0 ; choice_index<9 ; choice_index++ )
            if( possible_numbers[row_index][column_index][choice_index] == true )
            {
              only_possible_choice_index = choice_index ;
              number_of_possibles++ ;
            }
          if( number_of_possibles == 1 )
          {
            input[row_index][column_index] = only_possible_choice_index + 1 ;
            solved_one_flag = true ;
            printf("solved [%d][%d] as %d  (A)\r\n",row_index,column_index,only_possible_choice_index+1) ;
          }
        }

    if( solved_one_flag )
    {
      printf("solved_one_flag = true  (A)\r\n") ;
      continue ;
    }

    // Okay, now look for rows/columns/blocks where there is only one block with a 'possible' value we need

    // Check columns first
    for( int row_index=0 ; row_index<9 ; row_index++ )
      for( int choice_index=0 ; choice_index<9 ; choice_index++ )
      {
        int number_of_possibles = 0 ;
        int only_possible_column_index = 0 ;
        for( int column_index=0 ; column_index<9 ; column_index++ )
          if( possible_numbers[row_index][column_index][choice_index] == true )
          {
            only_possible_column_index = column_index ;
            number_of_possibles++ ;
          }
        if( (number_of_possibles == 1) && (input[row_index][only_possible_column_index] == 0) )
        {
          input[row_index][only_possible_column_index] = choice_index + 1 ;
          solved_one_flag = true ;
          printf("solved [%d][%d] as %d  (B)\r\n",row_index,only_possible_column_index,choice_index+1) ;
        }
      }

    if( solved_one_flag )
    {
      printf("solved_one_flag = true  (B)\r\n") ;
      continue ;
    }

    // Check rows
    for( int column_index=0 ; column_index<9 ; column_index++ )
      for( int choice_index=0 ; choice_index<9 ; choice_index++ )
      {
        int number_of_possibles = 0 ;
        int only_possible_row_index = 0 ;
        for( int row_index=0 ; row_index<9 ; row_index++ )
          if( possible_numbers[row_index][column_index][choice_index] == true )
          {
            only_possible_row_index = row_index ;
            number_of_possibles++ ;
          }
        if( (number_of_possibles == 1) && (input[only_possible_row_index][column_index] == 0)  )
        {
          input[only_possible_row_index][column_index] = choice_index + 1 ;
          solved_one_flag = true ;
          printf("solved [%d][%d] as %d  (C)\r\n",only_possible_row_index,column_index,choice_index+1) ;
        }
      }

    if( solved_one_flag )
    {
      printf("solved_one_flag = true  (C)\r\n") ;
      continue ;
    }

    // Check blocks (3x3 mini squares)

    // Table of row-column coordinates for each block
    const struct
      {
        unsigned row_index[9] ;
        unsigned column_index[9] ;
      } block[9]
      =
      {
        {{0,0,0,1,1,1,2,2,2},{0,1,2,0,1,2,0,1,2}},
        {{0,0,0,1,1,1,2,2,2},{3,4,5,3,4,5,3,4,5}},
        {{0,0,0,1,1,1,2,2,2},{6,7,8,6,7,8,6,7,8}},
        {{3,3,3,4,4,4,5,5,5},{0,1,2,0,1,2,0,1,2}},
        {{3,3,3,4,4,4,5,5,5},{3,4,5,3,4,5,3,4,5}},
        {{3,3,3,4,4,4,5,5,5},{6,7,8,6,7,8,6,7,8}},
        {{6,6,6,7,7,7,8,8,8},{0,1,2,0,1,2,0,1,2}},
        {{6,6,6,7,7,7,8,8,8},{3,4,5,3,4,5,3,4,5}},
        {{6,6,6,7,7,7,8,8,8},{6,7,8,6,7,8,6,7,8}},
      } ;

    for( int block_index=0 ; block_index<9 ; block_index++ )
      for( int choice_index=0 ; choice_index<9 ; choice_index++ )
      {
        int number_of_possibles = 0 ;
        int only_possible_cell_index = 0 ;
        //printf("BlockCheck:") ;
        for( int cell_index=0 ; cell_index<9 ; cell_index++ )
        {
          //printf("(%d,%d)",block[block_index].row_index[cell_index],block[block_index].column_index[cell_index]) ;
          if( possible_numbers[block[block_index].row_index[cell_index]][block[block_index].column_index[cell_index]][choice_index] == true )
          {
            only_possible_cell_index = cell_index ;
            number_of_possibles++ ;
          }
        }
        //printf("\r\n") ;
        if( (number_of_possibles == 1) && (input[block[block_index].row_index[only_possible_cell_index]][block[block_index].column_index[only_possible_cell_index]] == 0) )
        {
          input[block[block_index].row_index[only_possible_cell_index]][block[block_index].column_index[only_possible_cell_index]] = choice_index + 1 ;
          solved_one_flag = true ;
          printf("solved [%d][%d] as %d  (D)\r\n",block[block_index].row_index[only_possible_cell_index],block[block_index].column_index[only_possible_cell_index],choice_index+1) ;
        }
      }

    if( solved_one_flag )
    {
      printf("solved_one_flag = true  (D)\r\n") ;
      continue ;
    }

    break ;

  } // End of for() loop, aka infinite loop

  // Okay, if we made it here, we cannot solve any more cells
  // hopefully this means we have solved all cells,
  // but it might mean we need to 'guess' a cell!

  int my_solution[9][9] ;

  for( int row_index=0 ; row_index<9 ; row_index++ )
  {
    for( int column_index=0 ; column_index<9 ; column_index++ )
    {
      printf("[%d][%d] = ",row_index,column_index) ;

      my_solution[row_index][column_index] = 0 ; // Can pack up mulitple solutions by multiplying be ten as we add

      for( int choice_index=0 ; choice_index<9 ; choice_index++ )
        if( possible_numbers[row_index][column_index][choice_index] )
        {
          printf(" %d",choice_index+1) ;
          my_solution[row_index][column_index] = (my_solution[row_index][column_index] * 10) + (choice_index + 1) ;
        }

      printf("\r\n") ;
    }
  }

  // Okay, if this was a retry after a guess, we might have come up with a guess that was invalid
  // this will make some cells equal to zero (no possible solutions)
  // If this is the case, we need to go back and do the original solution, and make a new guess
  bool we_have_invalid_solution = false ;
  for( int row_index=0 ; row_index<9 ; row_index++ )
    for( int column_index=0 ; column_index<9 ; column_index++ )
      if( my_solution[row_index][column_index] == 0 ) // no possible solution
        we_have_invalid_solution = true ;

  if( we_have_invalid_solution )
  {
    // Wait, if this is the first time through, it should not be invalid, unless the original puzzle is not valid
    if( number_of_times_tried == 1 )
    {
      printf("Invalid input puzzle !!!\r\n") ;
      printf("Check that you typed in the puzzle correctly\r\n") ;
      printf("The same number is not in a column, row, or block\r\n") ;
      getch() ;
      return 0 ;
    }

    printf("Invalid solution, going back to original solution\r\n") ;
    //printf("hit any key to continue\r\n") ;
    //getch() ;

    // Restore original input
    for( int row_index=0 ; row_index<9 ; row_index++ )
      for( int column_index=0 ; column_index<9 ; column_index++ )
        input[row_index][column_index] = original_input[row_index][column_index] ;

    // Second, make all possible choices possible
    for( int row_index=0 ; row_index<9 ; row_index++ )
      for( int column_index=0 ; column_index<9 ; column_index++ )
        for( int choice_index=0 ; choice_index<9 ; choice_index++ )
          possible_numbers[row_index][column_index][choice_index] = true ;

    goto start_over ;
  }

  // Okay lets see if we really solved it?
  // That is, do we have only one solution for each cell
  bool we_have_solved_it = true ;
  for( int row_index=0 ; row_index<9 ; row_index++ )
    for( int column_index=0 ; column_index<9 ; column_index++ )
      if( my_solution[row_index][column_index] > 9 ) // if greater then 1-9, means we have a second solution, multiplied up by ten
        we_have_solved_it = false ;

  if( !we_have_solved_it )
  {
    // Okay, need to pice a cell to guess an answer for and try again, hopefully it works!?

    // First, make all possible choices possible
    for( int row_index=0 ; row_index<9 ; row_index++ )
      for( int column_index=0 ; column_index<9 ; column_index++ )
        for( int choice_index=0 ; choice_index<9 ; choice_index++ )
          possible_numbers[row_index][column_index][choice_index] = true ;

    for( ; (1==1) ; ) // lets loop and look at some cels and pick one to 'guess'
    {
      // Just pick a cell at random, and see if we want to guess it (it has only two choices, so we have a 50%-50% chance of guessing right
      int row_index = random(9) ;
      int column_index = random(9) ;
      if( (my_solution[row_index][column_index] > 9) && (my_solution[row_index][column_index] < 100) )
      {
        printf("Going to guess a solution for cell[%d][%d] = %d\r\n",row_index,column_index,my_solution[row_index][column_index]) ;
        // okay found a cell with exactly two solutions, pick one
        int my_guess ;
        if( random(2) == 1 )
          my_guess = (my_solution[row_index][column_index] % 10) ; // choose the bottom choice
        else
          my_guess = (my_solution[row_index][column_index] / 10) ; // choose the top choice

        // lets pick one, and try solving again!
        for( int choice_index=0 ; choice_index<9 ; choice_index++ )
          possible_numbers[row_index][column_index][choice_index] = false ;
        possible_numbers[row_index][column_index][my_guess-1] = true ;

        printf("Guessing a cell, my_guess=%d for cell[%d][%d]\r\n",my_guess,row_index,column_index) ;
        printf("hit any key to continue\r\n") ;
        //getch() ;

        goto start_over ;
      }
    }

  }

  for( int row_index=0 ; row_index<9 ; row_index++ )
  {
    for( int column_index=0 ; column_index<9 ; column_index++ )
    {
      printf("%5d",my_solution[row_index][column_index]) ;
    }
    printf("\r\n") ;
  }

  if( test_input_validity( my_solution ) )
  {
    printf("Solution tests as valid !!!\r\n") ;
  }
  else
  {
    printf("Solution tests as invalid, you have defeated the computer (programmer) !!!\r\n") ;
  }

  printf("hit any key to exit") ;
  getch() ;

  return 0;
}
//---------------------------------------------------------------------------
