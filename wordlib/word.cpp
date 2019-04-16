#include "word.h"

Word::Word(): _len(0)
{
	// Keeps word clean.
	for(unsigned i = 0; i < WORD_OBJECT_SIZE + 1; i++)
		_text[i] = 0;
}

