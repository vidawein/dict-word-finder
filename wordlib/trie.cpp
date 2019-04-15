#include <iostream>
#include <climits>
 
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
	static void cleanChildren(TrieNode** child)
	{
		for(size_t i = 0; i < TRIE_SIZE ; i++)
			child[i] = nullptr;
	}
	TrieNode()
	{
		TrieNode::cleanChildren(_children);
	}
	~TrieNode()
	{
		for(size_t i = 0; i < TRIE_SIZE ; i++) 
			delete _children[i];
	}
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
	static void insert(TrieNode* trie, const char* string)
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
				       traverse->stateAt(indexKey) = TrieState::Part;
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
				case TrieState::End:
				       return;
			}
	}
 
	static bool contains(TrieNode* trie, const char* string)
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

  static void printFirst(TrieNode* trie)
  {
    for(char i = 0; i < SCHAR_MAX; i++)
    {
      switch(trie->stateAt(i))
      {
        case TrieState::Part:
              std::cout << i;
              TrieManager::printFirst(trie->childAt(i));
              return;
        case TrieState::End:
              std::cout << i << '\n';
              return; 
        case TrieState::Empty:
              break;
      }
    }
  }
};



 
int main(int argc, char const *argv[])
{
	TrieNode* trie = new TrieNode();
	TrieManager::insert(trie, "Foo!");
	TrieManager::insert(trie, "Doo!");
	TrieManager::insert(trie, "Food!");
	TrieManager::insert(trie, "Aaaaaaa");
	std::cout << "Contains Doo! " << TrieManager::contains(trie, "Doo!") << "\n";
	TrieManager::printFirst(trie);
	delete trie;
	return 0;
}
