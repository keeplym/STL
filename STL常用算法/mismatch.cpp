1.mismatch()

mismatch() 的 4 个版本和 equal() 一样有相同的参数——第二个序列有或没有结束迭代器，有或没有定义比较的额外的函数对象参数。
mismatch() 返回的 pair 对象包含两个迭代器。它的 first 成员是一个来自前两个参数所指定序列的迭代器，second 是来自于第二个序列的迭代器。
当序列不匹配时，pair 包含的迭代器指向第一对不匹配的元素；因此这个 pair 对象为 pair<iter1+n，iter2 + n>，这两个序列中索引为 n 的元素是第一个不匹配的元素。

当序列匹配时，pair 的成员取决于使用的 mismatch() 的版本和具体情况。
iter1 和 end_iter1 表示定义第一个序列的迭代器，iter2 和 end_iter2 表示第二个序列的开始和结束迭代器。
返回的匹配序列的 pair 的内容如下：

(1) 对于 mismatch(iter1，end_iter1，iter2):
返回 pair<end_iter1，(iter2 + (end_ter1 - iter1))>，pair 的成员 second 等于 iter2 加上第一个序列的长度。
如果第二个序列比第一个序列短，结果是未定义的。

(2) 对于 mismatch(iterl, end_iter1, iter2, end_iter2)：
当第一个序列比第二个序列长时，返回 pair<end_iter1, (iter2 + (end_iter1 - iter1))>，所以成员 second 为 iter2 加上第一个序列的长度。
当第二个序列比第一个序列长时，返回 pair<(iter1 + (end_iter2 - iter2)),end_iter2>， 所以成员 first 等于 iter1 加上第二个序列的长度。
当序列的长度相等时，返回 pair<end_iter1, end_iter2>。


int main() {
    vector<string> range1 {"one", "three", "five"};
    vector<string> range2 {"nine", "five", "eighteen"};
    auto pr = mismatch(begin(range1), end(range1), begin(range2), end(range2), [](const string& s1, const string& s2) { 
        return s1.back() == s2.back(); 
    });
    if(pr.first == std::end(range1) || pr.second == std::end(range2))
        std::cout << "The ranges are identical." << std::endl;
    else
        std::cout << *pr.first << " is not equal to " << *pr.second <<std::endl;
}

//five is not equal to eighteen


