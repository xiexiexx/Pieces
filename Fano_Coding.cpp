#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

// 为简单起见, 将概率向量和编码向量设置为全局变量, 递归调用时可以减少参数数目.
// 读者可将本程序改写为类.
std::vector<double> P;			// 概率向量.
std::vector<std::string> C;		// 编码向量, 具体使用时C要比P多一个元素用于哨兵.
std::vector<double> SUM;		// 概率部分和, SUM[i]存放[0, i)区间的概率和, 长度是P.size() + 1.

// 划分的下标范围是[L, R), 我们需要将该区间划分成[L, S), [S, R), 使得差值最小.
// 调用此函数的要求是区间非空, 也就是L < R. 
size_t partiton(size_t L, size_t R)
{
	size_t S = L;		// 划分初始设定.
	// R_L为左右差值, 定义为右半部分减去左半部分, 直接从预先算好的部分和中提取而不需要重复再算.
	double R_L = SUM[R]- SUM[L];		
	double delta = fabs(R_L);
	for (size_t d = L + 1; d < R + 1; ++d)
	{
		R_L -= P[d - 1] + P[d - 1];	// 差值变化.
		if (fabs(R_L) < delta)
		{
			delta = fabs(R_L);
			S = d;
		}
	}
	return S;
}

// 完成对[L, R)区间的Fano编码, 我们将编码前缀放在C中并逐步变更, 不需要作为参数来传递.
void Fano_Coding(size_t L, size_t R)
{
	if (R > L + 1)
	{
		// 区间中至少有两个元素才进行编码. 此外, 该调用可保证区间非空.
		size_t S = partiton(L, R);
		// 注意赋值次序, C[L]的变更最后才能进行.
		C[S] = C[L] + "1";	// 先进行右半部分的前缀变更操作.
		C[L] = C[L] + "0";	// 再进行左半部分的前缀变更操作.
		Fano_Coding(L, S);
		Fano_Coding(S, R);
	}
}

void example()
{
	// 概率值设定.
	P = { 0.125, 0.125, 0.125, 0.5, 0.125 };
	// 注意: 如果概率向量只有一个元素, 编码为空字符串.
	// Fano编码要求对概率进行排序.
	sort(P.begin(), P.end());
	// C中多预留一个哨兵值, 以保证不会出现超出边界的赋值错误, 这样亦可解决空概率向量的问题
	C.resize(P.size() + 1);
	C[0] = "";		// 编码初值为空字符串.
	// 提前计算部分和以备后续编码之需.
	SUM.resize(P.size() + 1);
	SUM[0] = 0;
	for (size_t i = 1; i < SUM.size(); ++i)
		SUM[i] = SUM[i - 1] + P[i - 1];
	Fano_Coding(0, P.size());
	C.pop_back();	// 将哨兵去除.
	for (size_t i = 0; i < C.size(); ++i)
		std::cout << C[i] << std::endl;
}
