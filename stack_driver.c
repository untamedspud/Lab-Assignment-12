#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stack.h>

/* 
 * You'll want something like this in your stack.h:

	#define MAX_PAYLOAD_STRLEN 10

	// data to be stored in the stack
	typedef struct stack_element_t {
	        char payload[ MAX_PAYLOAD_STRLEN ];
	} stack_element_t;


	// the stack structure itself
	typedef struct stack_node_s {
	        stack_element_t         element;
	        struct stack_node_s     *restp;
	} stack_node_t;


	// a pointer (and count) of information about the stack (singleton).
	typedef struct {
	        stack_node_t            *topp;
	        int                     count;
	} mystack_t;

 *
 */


// turn this on to enable more debugging output when the prorgram is run
#define DEBUG


// function prototypes
int 		push ( mystack_t *sp, char c[] );
stack_element_t pop(mystack_t *sp);
void 		booktest( void );
void 		increment_decrement_test( void );


// handy debug macro
// probably shouldn't do this in new code, but I'm including it here as
// an example of what not to do.  New versions of the C compiler make 
// this avoidable.
#ifdef DEBUG
#define WALK(x,y)	{ puts(x); walk(y); }
#else
#define WALK(x,y)
#endif


int main()
{

	booktest( );

	increment_decrement_test( );

	return EXIT_SUCCESS;

}



void increment_decrement_test( void )
{
	mystack_t s = { NULL, 0 };

	char *items[] = { "2", "7", "4", "5", "10", "W", "6" };
	char *answr[] = { "12", "17", "14", "15", "20", "W", "16" };
	int items_i = 0;
	int n = sizeof items / sizeof items[0] ;
	
	for ( items_i = 0; items_i < n; items_i++ )
		assert( push( &s, items[ items_i ] ) == items_i + 1 );


	WALK( "Before Adjustment", &s );	// print out the stack
	adjust( &s, 10 );			// add 10 to all numeric values
	WALK( "After Adjustment", &s );		// print out the stack


	int i = n;
	while ( s.count > 0 ) {
		char *m = pop( &s ).payload;
		i--;
		printf( "%-3s=>%3s,  ", m, answr[i] );
		assert( strcmp( m, answr[ i ] ) == 0 );
	}
	puts( "\nend of inc/dec test");
	
	return;
}



void booktest( void ) 
{
	mystack_t 	s = { NULL, 0 };
	int 		i;
	char 		*items[] = { "2", "+", "C" };
	int 		items_i = 0;
	
	i = push( &s, items[ items_i++ ]  );
	assert( i == 1 );
	i = push( &s, items[ items_i++ ]  );
	assert( i == 2 );
	i = push( &s, items[ items_i++ ]  );
	assert( i == 3 );

#ifdef DEBUG
	printf( "Dumping stack:\n" );
	walk( &s );
#endif

	while ( s.topp != NULL ) {
		printf( "stack count=%d payload=%s\n", s.count, pop( &s ).payload );
	}

#ifdef DEBUG
	printf( "Dumping stack:\n" );
	walk( &s );
#endif

	return;
}
