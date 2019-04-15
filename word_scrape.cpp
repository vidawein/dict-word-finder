#include <iostream>
#include <cstdio>
#include <cctype>

#define LINE_BUFFER_SIZE 1024

static const char* SCRAPE_USAGE = "$ word_scrape <dictionary> <output file>";

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

// fgets(line_buf, sizeof(line_buf) - 1, proc) != NULL
static int scrapeWordsFromDict(const char* dst, const char* src)
{
	std::FILE* dstp;
	std::FILE* srcp;
	char lineBuffer[LINE_BUFFER_SIZE];
	WordBuilder<512> wBuild;
	dstp = std::fopen(dst, "w");
	srcp = std::fopen(src, "r");
	if(dstp == nullptr) {
		std::printf("File Error: Cannot open file at path '%s'\n", dst);
		return 0;
	}

	if(srcp == nullptr) {
		std::printf("File Error: Cannot open file at path '%s'\n", src);
		return 0;
	}

	while(std::fgets(lineBuffer, sizeof(lineBuffer), srcp) != nullptr) {
		const char* reader = lineBuffer;
		while(*reader) {
			if(wBuild.getState()) {
				if(!std::isupper(*reader)) {
					wBuild.append('\n'); // So words can be read line by line
					wBuild.stateOff();
					// we don't want words less than 3 in length
					if(wBuild.getLength() > 3)
						std::fputs(wBuild.getWord(), dstp);
					wBuild.clean();
				} else {
					wBuild.append(*reader); // builds the word.
				}
			} else {
				if(std::isupper(*reader) && reader[1] && std::isupper(reader[1])){
					wBuild.stateOn();
				    wBuild.append(*reader++);
				    wBuild.append(*reader);
				}
			}
		    reader++;
		}
	}
	std::fclose(srcp);
	std::fclose(dstp);
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
