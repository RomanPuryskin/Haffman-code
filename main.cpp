#include "HuffmanTree.h"

int main()
{
	std::string text = "ehal greka 4erez reky";

  HuffmanTree tree;

  std::string Text = "Text.txt";
  std::string EncodedText = "EncodedText.txt";
  std::string DecodedText = "DecodedText.txt";

  tree.buildHuffmanTree(Text);
  tree.encode(Text,EncodedText);
  tree.decode(EncodedText , DecodedText);
  double Compress = tree.getCompression(Text, EncodedText);
  std::cout<<Compress;
	return 0;
}