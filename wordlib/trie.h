#ifndef WORDLIB_TRIE_HPP
#define WORDLIB_TRIE_HPP

#include <iostream>
#include <climits>
#include "word.h"
 
// Implmentation of trie structure for checking membership of large set of strings
 
#define TRIE_SIZE SCHAR_MAX + 1
 
/**
 * enum to denote the state of a trie node.
 */
struct TrieState
{
	enum Kind
	{
		Empty,
		Part,
		End
	};
};
 
class TrieNode
{
public:
	static void cleanChildren(TrieNode** child);
	TrieNode();
	~TrieNode();
	// Trie is indexed with char type
	TrieState::Kind& stateAt(char index)
	{
		return _states[index % TRIE_SIZE];
	}
 
    // Trie is indexed with char type.
	TrieNode* childAt(char index) const
	{
		return _children[index % TRIE_SIZE];
	}
 
	void setChildAt(TrieNode* child, char index)
	{
		_children[index % TRIE_SIZE] = child;
	}
 
	bool isEmptyAt(char index) const
	{
		return _children[index % TRIE_SIZE] == nullptr;
	}
private:
	TrieNode* _children[TRIE_SIZE];
	TrieState::Kind _states[TRIE_SIZE];
};
 
// Used for manufacturing instances of tries, and inserting strings.
class TrieManager
{
public:
	static void insert(TrieNode* trie, const char* string);
 
	static bool contains(TrieNode* trie, const char* string);

	static void printWithPrefix(TrieNode* trie, const char* prefix, Word& word);
};

#endif 
