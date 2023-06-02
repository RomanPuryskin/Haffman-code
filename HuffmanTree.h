#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iterator>
#include <list>
#include <fstream>

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
  
      void SetInSetByChar (char ch) {m_symbols.insert(ch);}
      void SetInSetBySet (std::set<char> temp) 
      {
        m_symbols.insert(temp.begin() , temp.end());
      }

      std::set<char> GetSet()
      {
        return m_symbols;
      }
  
      Node *GetLeft() { return m_left; }
  
      Node *GetRight() { return m_right; }
  
      void SetLeft(Node *left) { m_left = left; }
  
      void SetRight(Node *right) { m_right = right; }
    
  private:
      std::set<char> m_symbols;
      Node *m_left = nullptr;
      Node *m_right = nullptr;
      int m_freq;
    };
  
    Node* getNodeByChar(char ch, int freq, Node* left, Node* right)
      {
      	Node* node = new Node();
        node->SetInSetByChar(ch);
      	node->SetFreq(freq);
      	node->SetLeft(left);
      	node->SetRight(right);
        return node;
      }

    Node* getNodeBySet(std::set<char> temp , int freq , Node* left , Node* right)
      {
        Node* node = new Node();
        node->SetInSetBySet(temp);
        node->SetFreq(freq);
        node->SetLeft(left);
        node->SetRight(right);
        return node;
      }

    HuffmanTree() {m_root = nullptr;}
    ~HuffmanTree();
    void DeleteTree(Node* node);
    double getCompression(const std::string &text , const std::string &encodedText);
    bool encode(const std::string &fileName , const std::string &fileName1);
    std::string encode(char ch);
    void encode(Node* node, char ch, std::string Code, std::string& encodedChar);
    bool buildHuffmanTree(const std::string &fileName);
    bool decode(const std::string &fileName , const std::string &fileName1);

  
private:
    Node *m_root = nullptr;
};