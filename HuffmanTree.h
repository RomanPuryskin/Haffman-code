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
      
      Node(char ch, int freq, Node* left, Node* right) 
      {
        SetInSetByChar(ch);
      	SetFreq(freq);
      	SetLeft(left);
      	SetRight(right);
      }

      Node(std::set<char> temp , int freq , Node* left , Node* right)
      {
        SetInSetBySet(temp);
        SetFreq(freq);
        SetLeft(left);
        SetRight(right);
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


    HuffmanTree() {m_root = nullptr;}
    ~HuffmanTree();
    void DeleteTree(Node* node);
    double encode(const std::string &fileName , const std::string &fileName1);
    std::string encode(char ch,const std::string &fileName);
    void encode(Node* node, char ch, std::string Code, std::string& encodedChar,const std::string &fileName);
    bool buildHuffmanTree(const std::string &fileName);
    bool decode(const std::string &fileName , const std::string &fileName1);

  
private:
    Node *m_root = nullptr;
};