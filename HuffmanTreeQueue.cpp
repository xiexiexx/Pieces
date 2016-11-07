#include "HuffmanTreeQueue.h"

#include <algorithm>
#include <queue>

void HuffmanTree::CodingAll(HuffmanNode* p, const std::string& prefix)
{
	// ��p��ΪNULL��ݹ����pΪ�����������н����б���
	if (p != NULL)
	{
		// ���p������������ǰ׺��prefix��0
		CodingAll(p->lChild, prefix + "0");
		// ���p������������ǰ׺��prefix��1
		CodingAll(p->rChild, prefix + "1");
		// Ҷ�ӽ����Ϊ��Ȼ��, �Դ˶Ա���������Ӧλ�ø�����prefix.
		if (p->number < HC.size())
			HC[p->number] = prefix;
	}
}

void HuffmanTree::HuffmanCoding(std::vector<double>& P, std::vector<std::string>& C)
{
	// ��������ɱ�֤P.size() > 1, ���򲻽��б���ֱ�ӷ���.
	if (P.size() <= 1)
		return;		
	// ��������HC�ĳ�������Ϊ���������ĳ���.
	HC.resize(P.size());
	// �Ը���������������.
	sort(P.begin(), P.end());
	// һ���Ը��������ڱ����л���ֵĽ��.
	std::vector <HuffmanNode> data(2 * P.size() - 1);
	std::queue<HuffmanNode*> QN;	// ������Ľ��ָ��.
	std::queue<HuffmanNode*> QT;	// ����������γɵ���ָ��.
	
	// index��Ϊ���, ָʾ��ǰ��ʹ��data[index]���Ľ��.
	size_t index;		// ע���������򲻽����������forѭ��.
	// ��ʼ����n�ý��и�������.
	for (index = 0; index < P.size(); index++)
	{
		// ��Ӧ�����ķ���, ���Ϊ��Ȼ��.
		data[index] = { P[index], index, NULL, NULL };
		// �������QN��.
		QN.push(&data[index]);
	}
	// ѭ�������Թ���Huffman��, ����������ֻʣ��һ��Ԫ��ʱ��ֹ.
	while (QN.size() + QT.size() > 1)
	{
		// ������������ȡ������ȡ����СԪ��Ϊ���Һ���, ���ȴ���QN��Ԫ���Ա�֤�볤������С.
		HuffmanNode* Childs[2];	// ���Һ���ָ��.
		for (size_t i = 0; i < 2; ++i)
			if (!QN.empty())
			{
				Childs[i] = QN.front();
				// ��QT����Ȩֵ��С�����, ����ȡQN����Ԫ��.
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
				// QN����Ԫ��, ֱ��ȡQT�ж���Ԫ��.
				Childs[i] = QT.front();
				QT.pop();
			}
		// �����½������, ���ͳһΪHC.size().
		data[index] = { Childs[0]->weight + Childs[1]->weight, HC.size(), Childs[0], Childs[1] };
		HuffmanNode* p = &data[index];
		// �������������HT��.
		QT.push(p);
		// ��Ÿ���, �´�ʹ���½��.
		++index;
	}
	// ����QT����ʣ��ΨһHuffman�����б���.
	CodingAll(QT.front(), "");
	C = HC;		// �����ձ��븴�Ƹ�C
}
