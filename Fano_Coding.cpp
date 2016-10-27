#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

// Ϊ�����, �����������ͱ�����������Ϊȫ�ֱ���, �ݹ����ʱ���Լ��ٲ�����Ŀ.
// ���߿ɽ��������дΪ��.
std::vector<double> P;			// ��������.
std::vector<std::string> C;		// ��������, ����ʹ��ʱCҪ��P��һ��Ԫ�������ڱ�.

// ���ֵ��±귶Χ��[L, R), ������Ҫ�������仮�ֳ�[L, S), [S, R), ʹ�ò�ֵ��С.
// ���ô˺�����Ҫ��������ǿ�, Ҳ����L <= R. 
size_t partiton(size_t L, size_t R)
{
	size_t S = L;		// ���ֳ�ʼ�趨.
	// R_LΪ���Ҳ�ֵ, ����Ϊ�Ұ벿�ּ�ȥ��벿��. �����ǳ�ֵ�趨.
	double R_L = 0;		
	for (size_t i = L; i < R; ++i)
		R_L += P[i];
	double delta = fabs(R_L);
	for (size_t d = L + 1; d < R + 1; ++d)
	{
		R_L -= P[d - 1] + P[d - 1];	// ��ֵ�仯.
		if (fabs(R_L) < delta)
		{
			delta = fabs(R_L);
			S = d;
		}
	}
	return S;
}

// ��ɶ�[L, R)�����Fano����, ���ǽ�����ǰ׺����C�в��𲽱��, ����Ҫ��Ϊ����������.
void Fano_Coding(size_t L, size_t R)
{
	if (R - L > 1)
	{
		// ����������������Ԫ�زŽ��б���. ����, �õ��ÿɱ�֤����ǿ�.
		size_t S = partiton(L, R);
		// ע�⸳ֵ����, C[L]�ı�������ܽ���.
		C[S] = C[L] + "1";	// �Ƚ����Ұ벿�ֵ�ǰ׺�������.
		C[L] = C[L] + "0";	// �ٽ�����벿�ֵ�ǰ׺�������.
		Fano_Coding(L, S);
		Fano_Coding(S, R);
	}
}

void example()
{
	// ����ֵ�趨.
	P = { 0.125, 0.125, 0.125, 0.5, 0.125 };
	// ע��: �����������ֻ��һ��Ԫ��, ����Ϊ���ַ���.
	if (P.size() > 0)
	{
		// Fano����Ҫ��Ը��ʽ�������.
		sort(P.begin(), P.end());
		// C��Ԥ��һ���ڱ�ֵ, �Ա�֤������ֳ����߽�ĸ�ֵ����.
		C.resize(P.size() + 1);
		C[0] = "";		// �����ֵΪ���ַ���.
		Fano_Coding(0, P.size());
		C.pop_back();	// ���ڱ�ȥ��.
	}
	for (size_t i = 0; i < C.size(); ++i)
		std::cout << C[i] << std::endl;
}
