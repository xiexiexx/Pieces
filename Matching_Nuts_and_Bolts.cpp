// ��ĸ����˨����.
// �������۲μ�: http://www.wisdom.weizmann.ac.il/~naor/PUZZLES/nuts_solution.html.

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using std::vector;
using std::multiset;
using std::sort;

// ��������İ汾:
bool NutsBolts_Sort_Version(vector<int>& Nuts, vector<int>& Bolts)
{
	if (Nuts.size() != Bolts.size())	// ���Ȳ���, ��Ȼ��ƥ��!
		return false;
	sort(Nuts.begin(), Nuts.end());		// ����ĸ�������.
	sort(Bolts.begin(), Bolts.end());	// ����˨�������.
	size_t i = 0;
	while (i < Nuts.size() && Nuts[i] == Bolts[i])	// ���ö�·���ʽ����ѭ��.
		++i;										// ���ƥ�������ɨ��.
	return (i == Nuts.size()) ? true : false;		// ����ƥ����.
}

// ���ڶ��ؼ��ϵİ汾:
bool NutsBolts_Multiset_Version(vector<int>& Nuts, vector<int>& Bolts)
{
	if (Nuts.size() != Bolts.size())	// ���Ȳ���, ��Ȼ��ƥ��!
		return false;
	multiset<int> MS(Nuts.cbegin(), Nuts.cend());	// ����ĸ�Ĺ��ȫ��������ؼ���.
	for (size_t i = 0; i < Bolts.size(); ++i)
	{
		auto iter = MS.find(Bolts[i]);				// �ڶ��ؼ�����Ѱ�ҵ�ǰ��˨���������ĸ.
		if (iter != MS.end())
			MS.erase(iter);							// �ҵ���ɾ����Ӧ����ĸ.
		else
			break;									// δ�ҵ�������.
	}
	return (MS.size() == 0) ? true : false;			// �Զ��ؼ������Ĵ�С��Ϊƥ��������.
}
