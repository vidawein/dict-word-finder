#include <cstdio>
#include <vector>

#define LINE_BUFFER_SIZE 1024

static const char* SCRAPE_USAGE = "$ word_scrape <dictionary> <output file>";

template<unsigned _wsize>
class WordBuilder {
public:
	WordBuilder(): _len(0)
	{}
	~WordBuilder(){}

	const char* getWord() const { return _word; }
private:
	char _word[_wsize];
	unsigned _len;
};


static int scrapeWordsFromDict(const char* dst, const char* src)
{

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
