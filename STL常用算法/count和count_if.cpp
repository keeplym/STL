１）count(first,last,value)：first是容器的首迭代器，last是容器的末迭代器，value是询问的元素，整个函数返回ｉｎｔ型。
count函数的功能是：统计容器中等于value元素的个数。

２）count_if(first,last,comp) (在comp为true的情况下计数）
或者 count_if(first,last,value,comp) 
(这个是在comp为true的情况下统计容器中等于value的元素）：first为首迭代器，last为末迭代器，value为要查询的元素，
comp为比较bool函数，为true则计数，函数返回型是int。

注：此两个函数复杂度是线性的，适用于小规模运算。



下面看例子：

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
 
bool comp(int n)
{
   cin>>n;
   return n>5;
}
 
 
 int main()
{
    int n;
    vector <int> V;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int temp;
        cin>>temp;
        V.push_back(temp);
    }
    int ask;
    while(cin>>ask)
    {
        int num１=count(V.begin(),V.end(),ask);//统计容器中等于ａｓｋ值的元素的个数
　　　　　int num2=count(V.begin(),V.end(),comp);//若输入的ｎ大于５，则计数
        cout<<num１<<endl;
　　　　　cout<<num2<<endl;
    }
    return 0;
}
