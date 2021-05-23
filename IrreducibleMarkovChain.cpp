#include "vMatrix.h"
// https://github.com/xiexiexx/DSAD/blob/master/Ch03/vMatrix.h

// 基于Floyd-Warshall算法判断Markov链的不可约性, P为单步概率转移矩阵.
bool Irreducible(matrix<double> P)
{
  if (P.dimX() != P.dimY())	// 不是方阵报错.
    return false;
  size_t n = P.dimX();
  size_t count = 0;
  for (size_t i = 0; i < n; ++i)
    for (size_t j = 0; j < n; ++j)
      if (P(i, j) > 0)		// 预先统计正概率值.
        ++count;
      else if (P(i, j) < 0)	// 存在负值报错.
        return false;
  // Floyd-Warshall算法.
  for (size_t k = 0; k < n; ++k)
  {
    if (count == n * n)		// 若全部概率为正则为不可约, 提前返回.
      return true;
    for (size_t i = 0; i < n; ++i)
      for (size_t j = 0; j < n; ++j)
        if (P(i, j) == 0 && P(i, k) > 0 && P(k, j) > 0)	// 短路表达式.
        {
          P(i, j) = P(i, k) + P(k, j);	// 随意赋值一个正概率.
          ++count;						// 该元素经Relax操作从0变为正概率值才计数.
        }
  }
  return (count == n * n) ? true : false;	// 全部概率值为正则不可约.
}
