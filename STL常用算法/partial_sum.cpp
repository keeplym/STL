partial_sum 
#include <iostream>     // std::cout
#include <functional>   // std::multiplies
#include <numeric>      // std::partial_sum

int myop (int x, int y) {return x+y+1;}

int main () {
  int val[] = {1,2,3,4,5};
  int result[5];

  std::partial_sum (val, val+5, result);
  std::cout << "using default partial_sum: ";
  for (int i=0; i<5; i++) std::cout << result[i] << ' '; //生成一个累加数组
  std::cout << '\n';

  std::partial_sum (val, val+5, result, std::multiplies<int>());
  // 第一个数是1， 第二个是1x2， 第三个是1x2x3，第四是1x2x3x4，第五个是1x2x3x4x5 
  std::cout << "using functional operation multiplies: "; 
  for (int i=0; i<5; i++) std::cout << result[i] << ' ';
  std::cout << '\n';

  std::partial_sum (val, val+5, result, myop);
  std::cout << "using custom function: ";
  for (int i=0; i<5; i++) std::cout << result[i] << ' ';
  std::cout << '\n';
  return 0;
}
 Edit & Run


Output:

using default partial_sum: 1 3 6 10 15
using functional operation multiplies: 1 2 6 24 120
using custom function: 1 4 8 13 19



Complexity:
Linear in the distance between first and last, minus one (in number of additions or applications of binary_op).
