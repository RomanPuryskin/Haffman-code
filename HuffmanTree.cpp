#pragma once
#include "HuffmanTree.h"

//---------------Деструктор----------------//
HuffmanTree::~HuffmanTree()
{
    DeleteTree(m_root);
}
 
void HuffmanTree::DeleteTree(Node* node)
{
    if (node)
    {
        DeleteTree(node->GetLeft());
        DeleteTree(node->GetRight());
 
        delete node;
    }
}
//------------------------------------------//

//-------------------------Кодирование-----------------------------//
std::string HuffmanTree::encode(char ch) 
{
    std::string encodedChar = "";
    encode(m_root, ch, "", encodedChar);
    return encodedChar;
}

//std::string HuffmanTree::encode(Node* root, char ch, std::string Code)
void HuffmanTree::encode(Node* root, char ch, std::string Code, std::string& encodedChar)
{


    if (!root)
    {
      return;
    }
  
    if (!root->GetLeft() && !root->GetRight()) 
      {
        encodedChar = Code;
    	}

    if(root->GetLeft())
      { 
        std::set<char> tempLeft = root->GetLeft()->GetSet();
        if ( tempLeft.find(ch) != tempLeft.end())
          encode(root->GetLeft(), ch , Code + "0", encodedChar);
        else
          encode(root->GetRight(), ch , Code + "1", encodedChar);
      }
}

double HuffmanTree::encode(const std::string &fileName , const std::string &fileName1)
{
    buildHuffmanTree(fileName);
    if(m_root == nullptr)
      return 0;
    std::ifstream file(fileName);
    std::ofstream file1(fileName1);
    if ( !file.is_open() || !file1.is_open() )
      return -1;

    double textSize = 0;
    double EncodedTextSize = 0;
    char ch;
    while (file.get(ch))
      {
        textSize++;
        std::string str = encode(ch);
        file1 << str;
        EncodedTextSize +=str.size();
      }

  double Compression = (textSize * 8)/EncodedTextSize;
  file.close();
  file1.close();
  return Compression;
}
//--------------------------------------------------------------//



//-----------------------Построение дерева----------------------------//
bool HuffmanTree::buildHuffmanTree(const std::string &fileName)
  {

    DestroyTree(m_root);
    char ch;
    std::ifstream file(fileName);
    if ( !file.is_open())
      return false;
    std::list <Node *> nodes;
    // посчитали частоты для каждого символа
    std::unordered_map<char, int> freq;
    while (file.get(ch))
      {
        freq[ch]++;
      }

    // заполняем лист нодами

    file.close();
    for (auto pair: freq)
  		nodes.push_back(new Node(pair.first, pair.second, nullptr, nullptr));

    nodes.sort([](Node* left , Node* right)
      {
        return left->GetFreq() < right->GetFreq();
    });

    
    while (nodes.size() > 1) 
    {
        Node *subTreeRoot = nullptr;

        Node *left = nodes.front(); nodes.pop_front();
  		  Node *right = nodes.front();	nodes.pop_front();
        int sum = left->GetFreq() + right->GetFreq();

        std::set<char> temp;
        std::set<char> leftTemp = left->GetSet();
        std::set<char> rightTemp = right->GetSet();
        temp.insert(  leftTemp.begin() , leftTemp.end()   );
        temp.insert(   rightTemp.begin() , rightTemp.end()   );
        
        subTreeRoot = new Node(temp, sum ,left, right);

        std::list<Node *>::iterator seeker = nodes.begin();
        while (seeker != nodes.end() && (*seeker)->GetFreq() <= subTreeRoot->GetFreq())           seeker++;
        nodes.insert(seeker, subTreeRoot);
    }
      
  // корень дерева - оставшаяся последняя нода
    m_root = nodes.front();
    nodes.pop_front();
    return true;
}
//-------------------------------------------------------------//

bool HuffmanTree::decode(const std::string &fileName ,const std::string &fileName1)
{
  char ch;
  std::ofstream file1(fileName1);
  std::ifstream file(fileName);
  if ( !file.is_open() || !file1.is_open() )
    return false;
  Node* temp = m_root;

  while (file.get(ch))
      {
        if(ch == '0')
          temp = temp->GetLeft();
        else
          temp = temp ->GetRight();

       if(!temp->GetLeft() && !temp->GetRight())
        {
          std::set<char> tempTemp = temp->GetSet();
          std::set<char>::iterator it;
          it = tempTemp.begin();
          file1 << *it;
          temp = m_root;
        }
      }
  file.close();
  file1.close();
  return true;
}

