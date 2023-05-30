#pragma once
#include "HuffmanTree.h"

void HuffmanTree::encode(Node* root, std::string str, std::unordered_map<char, std::string> &huffmanCode)
    {
    	if (root == nullptr)
    		return;
    
    	if (!root->GetLeft() && !root->GetRight()) {
    		huffmanCode[root->GetChar()] = str;
    	}
    
    	encode(root->GetLeft(), str + "0", huffmanCode);
    	encode(root->GetRight(), str + "1", huffmanCode);
    }

std::string HuffmanTree::encode(const std::string &text)
  {
    
    std::unordered_map<char, std::string> huffman;
  	encode(m_root, "", huffman);
    std::cout << "Huffman Codes are :\n" << '\n';
  	for (auto pair: huffman)
  		std::cout << pair.first << " " << pair.second << '\n';

    std::string EncodedString = "";
  	for (char ch: text) 
  		EncodedString += huffman[ch];

    return EncodedString;
  }

double HuffmanTree::encode(const std::string &text , const std::string &EncodedString)
  {
    return (text.size() * 8) / EncodedString.size() ;
  }

void HuffmanTree:: decode(Node* root, int &index, std::string &str)
    {
    	if (root == nullptr) {
    		return;
    	}
    
    	if (!root->GetLeft() && !root->GetRight())
    	{
    		std::cout << root->GetChar();
    		return;
    	}
    
    	index++;
    
    	if (str[index] =='0')
    		decode(root->GetLeft(), index, str);
    	else
    		decode(root->GetRight(), index, str);
    }




void HuffmanTree::buildHuffmanTree(const std::string &text)
  {

    std::list <Node *> nodes;
    // посчитали частоты для каждого символа
    std::unordered_map<char, int> freq;
  	for (char ch: text) 
  		freq[ch]++;
    // заполняем лист нодами
    for (auto pair: freq)
  		nodes.push_back(getNode(pair.first, pair.second, nullptr, nullptr));

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
        subTreeRoot = getNode('\0', sum ,left, right);

        std::list<Node *>::iterator seeker = nodes.begin();
        while (seeker != nodes.end() && (*seeker)->GetFreq() <= subTreeRoot->GetFreq()) {
            seeker++;
        }
        nodes.insert(seeker, subTreeRoot);
    }
      
  // корень дерева - оставшаяся последняя нода
    m_root = nodes.front();
    nodes.pop_front();

  }

std::string HuffmanTree::decode(std::string &EncodedString)
{
  std::string DecodedString = "";
  Node* temp = m_root;
  for (char ch : EncodedString)
    {
      if(ch == '0')
        temp = temp->GetLeft();
      else
        temp = temp ->GetRight();

      if(!temp->GetLeft() && !temp->GetRight())
      {
        DecodedString += temp->GetChar();
        temp = m_root;
      }
    }
  return DecodedString;
}