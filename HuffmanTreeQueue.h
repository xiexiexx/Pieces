#include <string>
#include <vector>

#ifndef X_HUFFMAN_TREE
#define X_HUFFMAN_TREE

// Huffman����㶨��
struct HuffmanNode {
	double weight;			// Ȩֵ
	size_t number;			// ���
	// ��ԭʼ���Ź�N��,�����Ա������ԭʼ���Ž��ͱ�������г��ֵ��½��,
	// ԭʼ���Ž����Ϊ0��N - 1, �½��ͳһ���ΪN.
	HuffmanNode* lChild;	// ����
	HuffmanNode* rChild;	// �Һ���
};

class HuffmanTree {
public:
	// ���뺯��
	void HuffmanCoding(std::vector<double>& P, std::vector<std::string>& C);
private:
	// �����
	HuffmanNode* root;
	// �ݹ���뺯��
	void CodingAll(HuffmanNode* p, const std::string& prefix);
	// ������������HC
	std::vector<std::string> HC;
};

# endif	// X_HUFFMAN_TREE
