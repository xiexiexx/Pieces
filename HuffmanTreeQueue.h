#include <string>
#include <vector>

#ifndef X_HUFFMAN_TREE
#define X_HUFFMAN_TREE

// Huffman树结点定义
struct HuffmanNode {
  double weight;			// 权值
  size_t number;			// 编号
  // 设原始符号共N个,我们以编号区分原始符号结点和编码过程中出现的新结点,
  // 原始符号结点编号为0到N - 1, 新结点统一编号为N.
  HuffmanNode* lChild;	// 左孩子
  HuffmanNode* rChild;	// 右孩子
};

class HuffmanTree {
public:
  // 编码函数
  void HuffmanCoding(std::vector<double>& P, std::vector<std::string>& C);
private:
  // 根结点
  HuffmanNode* root;
  // 递归编码函数
  void CodingAll(HuffmanNode* p, const std::string& prefix);
  // 保存编码的向量HC
  std::vector<std::string> HC;
};

# endif	// X_HUFFMAN_TREE
