#include "stdafx.h"
#include "Utility.h"

/* Returns a random number in the range [i, j) */
int Utility::rand_range(int i, int j)
{
	if (i >= j)
		return 0;

	return i + rand() % (j - i);
}
