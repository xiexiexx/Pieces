#include "HuffmanTreeQueue.h"

#include <algorithm>
#include <queue>

void HuffmanTree::CodingAll(HuffmanNode* p, const std::string& prefix)
{
	// 若p不为NULL则递归对以p为根的子树所有结点进行编码
	if (p != NULL)
	{
		// 结点p的左子树所有前缀是prefix配0
		CodingAll(p->lChild, prefix + "0");
		// 结点p的右子树所有前缀是prefix配1
		CodingAll(p->rChild, prefix + "1");
		// 叶子结点编号为自然数, 以此对编码向量相应位置赋码字prefix.
		if (p->number < HC.size())
			HC[p->number] = prefix;
	}
}

void HuffmanTree::HuffmanCoding(std::vector<double>& P, std::vector<std::string>& C)
{
	// 后续处理可保证P.size() > 1, 否则不进行编码直接返回.
	if (P.size() <= 1)
		return;		
	// 编码向量HC的长度设置为概率向量的长度.
	HC.resize(P.size());
	// 对概率向量进行排序.
	sort(P.begin(), P.end());
	// 一次性给出所有在编码中会出现的结点.
	std::vector <HuffmanNode> data(2 * P.size() - 1);
	std::queue<HuffmanNode*> QN;	// 待编码的结点指针.
	std::queue<HuffmanNode*> QT;	// 编码过程中形成的树指针.
	
	// index作为编号, 指示当前会使用data[index]处的结点.
	size_t index;		// 注意其作用域不仅限于下面的for循环.
	// 初始放入n棵仅有根结点的树.
	for (index = 0; index < P.size(); index++)
	{
		// 对应需编码的符号, 编号为自然数.
		data[index] = { P[index], index, NULL, NULL };
		// 放入队列QN中.
		QN.push(&data[index]);
	}
	// 循环处理以构建Huffman树, 两个队列中只剩下一个元素时终止.
	while (QN.size() + QT.size() > 1)
	{
		// 在两个队列中取出依次取出最小元作为左右孩子, 优先处理QN中元素以保证码长方差最小.
		HuffmanNode* Childs[2];	// 左右孩子指针.
		for (size_t i = 0; i < 2; ++i)
			if (!QN.empty())
			{
				Childs[i] = QN.front();
				// 若QT队首权值更小则更新, 否则取QN队首元素.
				if (!QT.empty() && QT.front()->weight < Childs[i]->weight)
				{
					Childs[i] = QT.front();
					QT.pop();
				}
				else
					QN.pop();
			} 
			else
			{
				// QN中无元素, 直接取QT中队首元素.
				Childs[i] = QT.front();
				QT.pop();
			}
		// 处理新结点数据, 编号统一为HC.size().
		data[index] = { Childs[0]->weight + Childs[1]->weight, HC.size(), Childs[0], Childs[1] };
		HuffmanNode* p = &data[index];
		// 将新树放入队列HT中.
		QT.push(p);
		// 编号更新, 下次使用新结点.
		++index;
	}
	// 根据QT中所剩的唯一Huffman树进行编码.
	CodingAll(QT.front(), "");
	C = HC;		// 将最终编码复制给C
}
