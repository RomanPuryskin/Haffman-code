#include "HuffmanTree.h"

int main()
{
	std::string text = "ehal greka 4erez reky";

  HuffmanTree tree;

  tree.buildHuffmanTree(text);
  std::string EncodedText = tree.encode(text);
  //double Compress = tree.encode(text, EncodedText);
  //std::cout<<Compress;
  //std::string DecodedText = tree.decode(EncodedText);
  std::cout<< EncodedText<<std::endl;
  std::string DecodedText = tree.decode(EncodedText);
  std::cout<<DecodedText;
	return 0;
}