#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <algorithm>
using namespace std;

class HuffmanTree
{
public:
    class Node
    {
    public:
      ~Node() = default;
      Node() 
      {
        m_freq = 0;
        m_left = nullptr;
        m_right = nullptr;
      }
      Node(int freq) {
        m_freq = freq;
        m_left = nullptr;
        m_right = nullptr;
      }
      
      int GetFreq() { return m_freq; }
  
      void SetFreq(int freq) { m_freq = freq; }
  
      int GetChar() {return m_char;}
  
      void SetChar(char ch){ m_char = ch;}
  
      Node *GetLeft() { return m_left; }
  
      Node *GetRight() { return m_right; }
  
      void SetLeft(Node *left) { m_left = left; }
  
      void SetRight(Node *right) { m_right = right; }
    private:
      char m_char;
      Node *m_left = nullptr;
      Node *m_right = nullptr;
      int m_freq = 1;
    };
    
   Node* getNode(char ch, int freq, Node* left, Node* right)
      {
      	Node* node = new Node();
      
      	node->SetChar(ch);
      	node->SetFreq(freq);
      	node->SetLeft(left);
      	node->SetRight(right);
      
      	return node;
      }

  void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
    {
    	if (root == nullptr)
    		return;
    
    	if (!root->GetLeft() && !root->GetRight()) {
    		huffmanCode[root->GetChar()] = str;
    	}
    
    	encode(root->GetLeft(), str + "0", huffmanCode);
    	encode(root->GetRight(), str + "1", huffmanCode);
    }
  void decode(Node* root, int &index, string str)
    {
    	if (root == nullptr) {
    		return;
    	}
    
    	if (!root->GetLeft() && !root->GetRight())
    	{
    		cout << root->GetChar();
    		return;
    	}
    
    	index++;
    
    	if (str[index] =='0')
    		decode(root->GetLeft(), index, str);
    	else
    		decode(root->GetRight(), index, str);
    }


  void buildHuffmanTree(string text)
  {
  	std::list<Node *> nodes;

    
    std::sort(nodes.begin(), nodes.end(), [](Node *first, Node *second) {
        return first->GetFreq() < second->GetFreq();
    });
 
    while (nodes.size() > 1) {
        Node *subTreeRoot = nullptr;
 
        std::list<Node *>::iterator seeker = nodes.begin();
        while (seeker != nodes.end() && (*seeker)->GetFreq() <= subTreeRoot->GetFreq()) {
            seeker++;
        }
        nodes.insert(seeker, subTreeRoot);
    }
  }
 
private:
    Node *m_root = nullptr;
};
 


// Huffman coding algorithm

int main()
{
	string text = "Huffman coding is a data compression algorithm.";

  HuffmanTree tree;

	//buildHuffmanTree(text);
  tree.buildHuffmanTree(text);

	return 0;
}