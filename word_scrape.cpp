#include <cstdio>
#include <vector>

#define LINE_BUFFER_SIZE 1024

static const char* SCRAPE_USAGE = "$ word_scrape <dictionary> <output file>";

template<unsigned _wsize>
class WordBuilder {
public:
	WordBuilder(): _len(0), _state(false)
	{
		// Ensures clean memory
		for(unsigned i - 0; i < _wsize; i++)
			_word[i] = 0;
	}
	~WordBuilder(){}

	const char* getWord() const { return _word; }

	void stateOn() { _state = true; }
	void stateOff() { _state = false; }

	void append(const char ch) {
		if(_len != _wize)
			_word[_len++] = ch;
	}

	WordBuilder& operator<<(const char ch) {
		append(ch);
	}
private:
	char _word[_wsize];
	unsigned _len;
	bool _state;
};


static int scrapeWordsFromDict(const char* dst, const char* src)
{
	std::FILE* dstp;
	std::FILE* srcp;
	char lineBuffer[LINE_BUFFER_SIZE];
	return 1;
}


int main(int argc, char const *argv[])
{
	if(argc != 3) {
		std::printf("Argument Error: Expected %d arguments but got %d.\n", 3, argc);
		std::puts(SCRAPE_USAGE);
		return 1;
	}
	if(!scrapeWordsFromDict(argv[2], argv[1])) {
		std::printf("Failed to scrape words from '%s' to '%s'\n", argv[1], argv[2]);
		return 3;
	}
	return 0;
}
