// 螺母和螺栓问题.
// 深入讨论参见: http://www.wisdom.weizmann.ac.il/~naor/PUZZLES/nuts_solution.html.

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using std::vector;
using std::multiset;
using std::sort;

// 基于排序的版本:
bool NutsBolts_Sort_Version(vector<int>& Nuts, vector<int>& Bolts)
{
	if (Nuts.size() != Bolts.size())	// 长度不合, 必然不匹配!
		return false;
	sort(Nuts.begin(), Nuts.end());		// 按螺母规格排序.
	sort(Bolts.begin(), Bolts.end());	// 按螺栓规格排序.
	size_t i = 0;
	while (i < Nuts.size() && Nuts[i] == Bolts[i])	// 善用短路表达式结束循环.
		++i;										// 规格匹配则继续扫描.
	return (i == Nuts.size()) ? true : false;		// 返回匹配结果.
}

// 基于多重集合的版本:
bool NutsBolts_Multiset_Version(vector<int>& Nuts, vector<int>& Bolts)
{
	if (Nuts.size() != Bolts.size())	// 长度不合, 必然不匹配!
		return false;
	multiset<int> MS(Nuts.cbegin(), Nuts.cend());	// 将螺母的规格全部放入多重集合.
	for (size_t i = 0; i < Bolts.size(); ++i)
	{
		auto iter = MS.find(Bolts[i]);				// 在多重集合中寻找当前螺栓可适配的螺母.
		if (iter != MS.end())
			MS.erase(iter);							// 找到则删除对应的螺母.
		else
			break;									// 未找到则跳出.
	}
	return (MS.size() == 0) ? true : false;			// 以多重集合最后的大小作为匹配结果返回.
}
