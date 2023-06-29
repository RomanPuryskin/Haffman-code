#include "HuffmanTree.h"

int main()
{

  HuffmanTree tree;

  std::string Text = "Text.txt";
  std::string EncodedText = "EncodedText.txt";
  std::string DecodedText = "DecodedText.txt";

 // tree.buildHuffmanTree(Text);
  //tree.encode(Text,EncodedText);
  double Compress = tree.encode(Text,EncodedText);
  tree.decode(EncodedText , DecodedText);
  //double Compress = tree.encode(Text,EncodedText);
  std::cout<<Compress;
	return 0;
}