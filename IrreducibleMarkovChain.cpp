#include "vMatrix.h"
// https://github.com/xiexiexx/DSAD/blob/master/Ch03/vMatrix.h

// ����Floyd-Warshall�㷨�ж�Markov���Ĳ���Լ��, PΪ��������ת�ƾ���.
bool Irreducible(matrix<double> P)
{
	if (P.dimX() != P.dimY())	// ���Ƿ��󱨴�.
		return false;
	size_t n = P.dimX();
	size_t count = 0;
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j)
			if (P(i, j) > 0)		// Ԥ��ͳ��������ֵ.
				++count;
			else if (P(i, j) < 0)	// ���ڸ�ֵ����.
				return false;
	// Floyd-Warshall�㷨.
	for (size_t k = 0; k < n; ++k)
	{
		if (count == n * n)		// ��ȫ������Ϊ����Ϊ����Լ, ��ǰ����.
			return true;
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < n; ++j)
				if (P(i, j) == 0 && P(i, k) > 0 && P(k, j) > 0)	// ��·���ʽ.
				{
					P(i, j) = P(i, k) + P(k, j);	// ���⸳ֵһ��������.
					++count;						// ��Ԫ�ؾ�Relax������0��Ϊ������ֵ�ż���.
				}
	}
	return (count == n * n) ? true : false;	// ȫ������ֵΪ���򲻿�Լ.
}
