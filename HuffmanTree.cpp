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

    else
    {
      if(root->GetLeft())
      { 
        std::set<char> tempLeft = root->GetLeft()->GetSet();
  
    
        if ( tempLeft.find(ch) != tempLeft.end())
          encode(root->GetLeft(), ch , Code + "0", encodedChar);
        else
        {
          if (root->GetRight())
          {
            std::set<char> tempRight = root->GetRight()->GetSet();
            encode(root->GetRight(),ch, Code + "1", encodedChar);
          }
        }
      }
    }

}

bool HuffmanTree::encode(const std::string &fileName , const std::string &fileName1)
{
    char ch;
    std::ifstream file(fileName);
    std::ofstream file1(fileName1);
    if ( !file.is_open() || !file1.is_open() )
      return false;
    std::string encodedText = "";
 
    while (file.get(ch))
      {
        encodedText += encode(ch);
      }

    for (char ch : encodedText)
      file1<<ch;

  file.close();
  file1.close();
  return true;
}
//--------------------------------------------------------------//


double HuffmanTree::getCompression(const std::string &text , const std::string &encodedText)
{
  char ch;
  std::ifstream file(text);
  std::ifstream file1(encodedText);
  if ( !file.is_open() || !file1.is_open() )
      return -1;
  double textSize = 0;
  double encodedTextSize = 0;
  double Compression = 0;
  while(file.get(ch))
    textSize++ ;
  while(file1.get(ch))
    encodedTextSize++;
  Compression = ( textSize * 8 ) / encodedTextSize;

  if(textSize == 0 || encodedTextSize == 0)
    return -1;
  file.close();
  file1.close();
  return Compression;
  
}


//-----------------------Построение дерева----------------------------//
bool HuffmanTree::buildHuffmanTree(const std::string &fileName)
  {

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
  		nodes.push_back(getNodeByChar(pair.first, pair.second, nullptr, nullptr));

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
        
        subTreeRoot = getNodeBySet(temp, sum ,left, right);

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

