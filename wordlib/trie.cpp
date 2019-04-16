#include "trie.h"


void TrieNode::cleanChildren(TrieNode** child)
{
		for(size_t i = 0; i < TRIE_SIZE ; i++)
			child[i] = nullptr;
}

TrieNode::TrieNode()
{
	TrieNode::cleanChildren(_children);
	for(size_t i = 0; i < TRIE_SIZE; i++)
		_states[i] = TrieState::Empty;
}

TrieNode::~TrieNode()
{
	for(size_t i = 0; i < TRIE_SIZE ; i++) 
		delete _children[i];
}


void TrieManager::insert(TrieNode* trie, const char* string)
{
		TrieNode* traverse = trie;
		char indexKey;
		// Does not insert anything if string is empty
		while(*(string + 1))
		{
			indexKey = *string++;
			switch(traverse->stateAt(indexKey))
			{
				case TrieState::Empty:
				        traverse->setChildAt(new TrieNode(), indexKey);
				        traverse->stateAt(indexKey) = TrieState::Part;
				        traverse = traverse->childAt(indexKey);
				        break;
				case TrieState::Part:
				       traverse = traverse->childAt(indexKey);
				       break;
				case TrieState::End:
				       if(traverse->childAt(indexKey) == nullptr)
				       	       traverse->setChildAt(new TrieNode(), indexKey);
				       //traverse->stateAt(indexKey) = TrieState::Part;
				       traverse = traverse->childAt(indexKey);
				       break;
			}
		}
		// handles last character in string.
		indexKey = *string;
		switch(traverse->stateAt(indexKey))
			{
				case TrieState::Empty:
				        traverse->stateAt(indexKey) = TrieState::End;
				        break;
				case TrieState::Part:
				       traverse->stateAt(indexKey) = TrieState::End;
				       return;
				case TrieState::End:
				       return;
			}
}

bool TrieManager::contains(TrieNode* trie, const char* string)
	{
		TrieNode* traverse = trie;
		while(*string)
		{
			switch(traverse->stateAt(*string))
			{
				case TrieState::Empty:
				     return false;
				case TrieState::Part:
				     traverse = traverse->childAt(*string);
				     string++;
				     break;
				case TrieState::End:
				     return true;
 
			}
		}
		return false;
}

void TrieManager::printWithPrefix(TrieNode* trie, const char* prefix, Word& word)
{
	if(*prefix) {
	  word.append(*prefix);
      switch(trie->stateAt(*prefix))
      {
        case TrieState::Part:
              TrieManager::printWithPrefix(trie->childAt(*prefix), prefix + 1, word);
              return;
        case TrieState::End:
              // End counts as part and end, not to overwrite direct words.
              if(trie->childAt(*prefix) != nullptr)
              	   TrieManager::printWithPrefix(trie->childAt(*prefix), prefix + 1, word);
              return; 
        case TrieState::Empty:
              return;
      }
	} else { //prefix is null, can start printing words
		for(char i = 0; i < SCHAR_MAX; i++) {
			switch(trie->stateAt(i)) {
				case TrieState::Part:
				     word.append(i);
				     TrieManager::printWithPrefix(trie->childAt(i), prefix, word);
				     word.snip();
				     break;
				case TrieState::End:
				     word.append(i);
				     if(trie->childAt(*prefix) != nullptr)
				     	TrieManager::printWithPrefix(trie->childAt(i), prefix, word);
				     word.print();
				     word.snip();
				     break;
				case TrieState::Empty:
				     break;
			}
		}
	}
 }
