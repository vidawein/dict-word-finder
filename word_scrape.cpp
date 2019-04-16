#include <iostream>
#include <cstdio>
#include <cctype>
#include "WordBuilder.h"

#define LINE_BUFFER_SIZE 1024

static const char* SCRAPE_USAGE = "$ word_scrape <dictionary> <output file>";


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
					if(wBuild.getLength() > 3) {
						std::fputs(wBuild.getWord(), dstp);
					}
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
