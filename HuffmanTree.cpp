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


void HuffmanTree:: decode(Node* root, int &index, std::string str)
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




void HuffmanTree::buildHuffmanTree(std::string text)
  {

    std::vector<Node *> nodes;
    // посчитали частоты для каждого символа
    std::unordered_map<char, int> freq;
  	for (char ch: text) 
  		freq[ch]++;
    // заполняем лист нодами
    for (auto pair: freq)
  		nodes.push_back(getNode(pair.first, pair.second, nullptr, nullptr));
    
    std::sort(nodes.begin(), nodes.end(), [](Node *first, Node *second) {
        return first->GetFreq() < second->GetFreq();
    });

    
    while (nodes.size() > 1) 
    {
        Node *subTreeRoot = nullptr;

        Node *left = nodes.front(); nodes.erase(nodes.begin());
  		  Node *right = nodes.front();	nodes.erase(nodes.begin());
        int sum = left->GetFreq() + right->GetFreq();
        subTreeRoot = getNode('\0', sum ,left, right);

        std::vector<Node *>::iterator seeker = nodes.begin();
        while (seeker != nodes.end() && (*seeker)->GetFreq() <= subTreeRoot->GetFreq()) {
            seeker++;
        }
        nodes.insert(seeker, subTreeRoot);
    }
      

  
    // корень дерева - оставшаяся последняя нода
    Node* root = nodes.front();

  	std::unordered_map<char, std::string> huffmanCode;
  	encode(root, "", huffmanCode);
  
  	std::cout << "Huffman Codes are :\n" << '\n';
  	for (auto pair: huffmanCode)
  		std::cout << pair.first << " " << pair.second << '\n';
  
  	std::cout << "\nOriginal string was :\n" << text << '\n';
  
  	// print encoded string
  	std::string str = "";
  	for (char ch: text) 
  		str += huffmanCode[ch];
  
  	std::cout << "\nEncoded string is :\n" << str << '\n';
  
  	// traverse the Huffman Tree again and this time
  	// decode the encoded string
  	int index = -1;
  	std::cout << "\nDecoded string is: \n";
  	while (index < (int)str.size() - 2)
  		decode(root, index, str);
  }