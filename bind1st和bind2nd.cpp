bind1st 和 bind2nd 函数用于将一个二元算子（binary functor，bf）转换成一元算子（unary functor，uf）。
它们均需要两个参数：要转换的 fn 和一个值 x。简单理解，bind1st 把 x 作为 fn 的左值，bind2nd 把 x 作为 fn 的右值。看以下代码即可看出其功能：


vector<int> vec = {1, 2, 2, 3, 4};
vec.erase(remove_if(vec.begin(), vec.end(),bind1st(less_equal<int>(), 2)), vec.end()); // 删除大于等于2的数  2 <= x 
for(auto& x : vec)
    cout << x << " ";
//ouput: 1



vector<int> vec = {1, 2, 2, 3, 4};
vec.erase(remove_if(vec.begin(), vec.end(),bind2nd(less_equal<int>(), 2)), vec.end()); // 删除小于等于2的数  x <= 2
for(auto& x : vec)
    cout << x << " ";
//output: 3 4



/****/
int a[] = {1, 2, 100, 200};

std::vector< int> arr(a, a + 4);

// 移除所有小于100的元素
arr.erase( std::remove_if( arr.begin(), arr.end(),
std::bind2nd( std::less< int>(), 100)), arr.end());

这里的比较表达式相当于arr.value < 100

如果用bind1st则表达的意思就恰恰相反

// 移除所有大于100的元素
arr.erase( std::remove_if( arr.begin(), arr.end(),
std::bind1st( std::less< int>(), 100)), arr.end());

这里的表达式相当于100 < arr.value

当然为了实现删除大于100的元素你同样可以使用bind2nd

// 移除所有大于100的元素
arr.erase( std::remove_if( arr.begin(), arr.end(),
std::bind2nd( std::greater< int>(), 100)), arr.end());

前面说道=的比较，比如说x <= k怎么实现呢，std又提供了一个好东西not1，我们可以说 !(x > k) 和 x <= k是等价的，那么我们看看下面的表达式：

// 移除所有小于等于100的元素
arr.erase( std::remove_if( arr.begin(), arr.end(),
std::not1(std::bind2nd( std::greater< int>(), 100))), arr.end());

说明：not1是否定返回值是单目的函数，std中还有not2它是否定返回值是双目的函数

