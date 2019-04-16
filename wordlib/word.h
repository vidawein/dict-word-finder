#ifndef WORDLIB_WORD_HPP
#define WORDLIB_WORD_HPP

#include <cstdio>

// Word size that can capture length of any word
// in the dictionary
#define WORD_OBJECT_SIZE 25


class Word {
public:
	Word();
	~Word(){}

	int getLength() const { return _len; }

	void snip()
	{
		_text[--_len] = 0;
		if(_len < 0)
			_len = 0;
	}
	void append(char ch)
	{
		if(_len < WORD_OBJECT_SIZE)
			_text[_len++] = ch;
	}

	void print() const
	{
		std::printf("%s\n", _text);
	}
private:
	char _text[WORD_OBJECT_SIZE + 1];
	int _len;
};

#endif // WORDLIB_WORD_HPP
