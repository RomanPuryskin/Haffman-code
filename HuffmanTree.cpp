#pragma once
#include "HuffmanTree.h"


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

std::string HuffmanTree::encode(const std::string &text)
{
    std::string encodedText = "";
 
    for (char ch : text)
    {
        encodedText += encode(ch);
    }
  return encodedText;
}
//--------------------------------------------------------------//


double HuffmanTree::encode(const std::string &text , const std::string &encodedText)
  {
    return (text.size() * 8) / encodedText.size() ;
  }


//-----------------------Построение дерева----------------------------//
void HuffmanTree::buildHuffmanTree(const std::string &text)
  {

    std::list <Node *> nodes;
    // посчитали частоты для каждого символа
    std::unordered_map<char, int> freq;
  	for (char ch: text) 
  		freq[ch]++;
    // заполняем лист нодами
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

}
//-------------------------------------------------------------//

std::string HuffmanTree::decode(std::string &encodedText)
{
  std::string decodedText = "";
  Node* temp = m_root;
  for (char ch : encodedText)
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
        decodedText += *it;
        temp = m_root;
      }
    }
  return decodedText;
}

