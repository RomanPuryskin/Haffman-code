#include "HuffmanTree.h"

int main()
{
	std::string text = "Huffman coding is a data compression algorithm.";

  HuffmanTree tree;

	//buildHuffmanTree(text);
  tree.buildHuffmanTree(text);

	return 0;
}