#include <iostream>
#include <cstdio>
#include <cctype>
#include "trie.h"
#include "WordBuilder.h"

static const char* USAGE_STRING = "$ word_finder <prefix> <wordtextfile>";

static TrieNode trieBase;

int main(int argc, char const *argv[])
{
	WordBuilder<30> builder;
	std::FILE* srcp;
	TrieNode* triePtr = &trieBase;
	char chGot = '\0';
	if(argc != 3) {
		std::cout << "ArgumentError: Expected 2 arguments but got: " << (argc - 1) << "\n";
		std::cout << USAGE_STRING << "\n";
		return 1; 
	}

	srcp = std::fopen(argv[2], "r");
	if(srcp == nullptr) {
		std::cout << "Could not open file at path: " << argv[1] << ", exiting\n";
		return 3;
	}
	while((chGot = std::fgetc(srcp)) != EOF) {
		if(!chGot)
			break;
		if(std::isalpha(chGot)) {
			builder.append(chGot);
		} else if(chGot == '\n') {
			TrieManager::insert(triePtr, builder.getWord());
			builder.clean();
		} else {
			std::printf("TypeError: Got illegal char '%c'\n", chGot);
			return 6;
		}
	}
	Word wordMake;
	TrieManager::printWithPrefix(triePtr, argv[1], wordMake);
	return 0;
}
