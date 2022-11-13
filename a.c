#include "test.h"

int main()
{
	unsigned char tp;

	tp |= TOUT;
	tp |= TDOC;
	tp |= TIN;
	printf("%d\n", tp);
}