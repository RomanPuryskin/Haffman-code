#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
#include <list>

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
      
      Node(int freq) 
      {
        m_freq = freq;
        m_left = nullptr;
        m_right = nullptr;
      }
      
      int GetFreq() { return m_freq; }
  
      void SetFreq(int freq) { m_freq = freq; }
  
      char GetChar() {return m_char;}
  
      void SetChar(char ch){ m_char = ch;}
  
      Node *GetLeft() { return m_left; }
  
      Node *GetRight() { return m_right; }
  
      void SetLeft(Node *left) { m_left = left; }
  
      void SetRight(Node *right) { m_right = right; }
    
  private:
      char m_char;
      Node *m_left = nullptr;
      Node *m_right = nullptr;
      int m_freq;
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

    void encode(Node* root, std::string str, std::unordered_map<char, std::string> &huffmanCode);
    double encode(const std::string &text , const std::string &EncodedString);
    std::string encode(const std::string &text);
    void decode(Node* root, int &index, std::string &str);
    void buildHuffmanTree(const std::string &text);
    std::string decode(std::string &EncodedString);
  
private:
    Node *m_root = nullptr;
};