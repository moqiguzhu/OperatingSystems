#include <stdio.h>

#ifndef MESSAGE
	#define MESSAGE "You wish!!!"
#endif

#define message_for(a,b) \
	printf(#a " and " #b ": We love you!\n")

#define tokenpaster(n) printf("token" #n " = %d\n", token##n)

#if defined(MESSAGE)
	#define MESSAGE "I wish!"
#endif

#define square(x) ((x) * (x))

int main()
{
	printf("File: %s\n", __FILE__);
	printf("Time: %s\n", __TIME__);
	
	printf("message is: %s\n", MESSAGE);
	int token34 = 40;
	tokenpaster(34);
	printf("test square function: %d\n", square(2));

	return 0;
}
