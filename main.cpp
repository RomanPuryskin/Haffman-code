#include "HuffmanTree.h"

int main()
{
	std::string text = "Huffman coding is a data compression algorithm.";

  HuffmanTree tree;

	//buildHuffmanTree(text);
  tree.buildHuffmanTree(text);
  std::string EncodedText = tree.encode(text);
  double Compress = tree.encode(text, EncodedText);

  std::string DecodedText = tree.decode(EncodedText);
  std::cout<< DecodedText;
	return 0;
}