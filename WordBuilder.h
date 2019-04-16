#ifndef WORD_BUILDER_HPP
#define WORD_BUILDER_HPP

// Can make a char always lower case.
#define MAKE_LOWER_CHAR(ch) ((((ch) >= 0x41) && ((ch) <= 0x5A)) ? (ch) | 0x20 : (ch))

template<unsigned _wsize>
class WordBuilder {
public:
	WordBuilder(): _len(0), _state(false)
	{
		// Ensures clean memory
		for(unsigned i = 0; i < _wsize; i++)
			_word[i] = 0;
	}
	~WordBuilder(){}

	const char* getWord() const { return _word; }

	void stateOn() { _state = true; }
	void stateOff() { _state = false; }
	bool getState() const { return _state; }

	unsigned getLength() const { return _len; }

	void append(const char ch) {
		if(_len != _wsize)
			_word[_len++] = MAKE_LOWER_CHAR(ch);
	}

	void clean() {
		for(unsigned i = 0; i < _wsize; i++)
			_word[i] = 0;
		_len = 0;	
	}

	WordBuilder& operator<<(const char ch) {
		append(ch);
		return *this;
	}
private:
	char _word[_wsize];
	unsigned _len;
	bool _state;
};

#endif
