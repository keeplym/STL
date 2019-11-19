1.新建一个字符串

常见的 string 类构造函数有以下几种形式：

string strs //生成空字符串
string s(str) //生成字符串str的复制品
string s(str, stridx) //将字符串str中始于stridx的部分作为构造函数的初值
string s(str, strbegin, strlen) //将字符串str中始于strbegin、长度为strlen的部分作为字符串初值
string s(cstr) //以C_string类型cstr作为字符串s的初值
string s(cstr,char_len)    //以C_string类型cstr的前char_len个字符串作为字符串s的初值
strings(num, c) //生成一个字符串，包含num个c字符
strings(strs, beg, end)    //以区间[beg, end]内的字符作为字符串s的初值

2.获取字符串长度

size() 和 length()：这两个函数会返回 string 类型对象中的字符个数，且它们的执行效果相同。

max_size()：max_size() 函数返回 string 类型对象最多包含的字符数。一旦程序使用长度超过 max_size() 的 string 操作，编译器会拋出 length_error 异常。

capacity()：该函数返回在重新分配内存之前，string 类型对象所能包含的最大字符数。

3.字符串比较

s.compare (pos,n, s2);

若参与比较的两个串值相同，则函数返回 0；若字符串 S 按字典顺序要先于 S2，则返回负值；反之，则返回正值;


	  string A ("aBcdef");
    string B ("AbcdEf");
    string C ("123456");
    string D ("123dfg");
    //下面是各种比较方法
    int m=A.compare (B); //完整的A和B的比较   返回正数
    int n=A.compare(1,5,B); //"Bcdef"和"AbcdEf"比较 返回正数
    int p=A.compare(1,5,B,4,2); //"Bcdef"和"Ef"比较 返回负数
    int q=C.compare(0,3,D,0,3); //"123"和"123"比较  返回0

    string a = "a";
    int m = a.compare("A");  //返回正数

4.字符串修改

assign():

    string str1 ("123456");
    string str;
    str.assign (str1); //直接赋值   
    cout << str << endl;
    str.assign (str1, 3, 3); //赋值给子串 str = 456
    cout << str << endl;
    str.assign (str1,2,str1.npos);//赋值给从位置 2 至末尾的子串
    cout << str << endl;
    str.assign (5,'X'); //重复 5 个'X'字符
    cout << str << endl;
    string::iterator itB;
    string::iterator itE;
    itB = str1.begin ();
    itE = str1.end();
    str.assign (itB, (--itE)); //从第 1 个至倒数第 2 个元素，赋值给字符串 str
    cout << str << endl;

erase():

	(1)erase(pos,n); 删除从pos开始的n个字符，比如erase(0,1)就是删除第一个字符
	(2)erase(position);删除position处的一个字符(position是个string类型的迭代器)
	(3)erase(first,last);删除从first到last之间的字符（first和last都是迭代器）

	  string str ("This is an example phrase.");
  	string::iterator it;

  	// 第(1)种用法
  	str.erase (10,8);
  	cout << str << endl;        // "This is an phrase."

  	// 第(2)种用法
  	it=str.begin()+9;
  	str.erase (it);
  	cout << str << endl;        // "This is a phrase."

  	// 第(3)种用法
  	str.erase (str.begin()+5, str.end()-7);
  	cout << str << endl;        // "This phrase."

swap():

	string str = "12234";
    string str2 ("abcdn");
    str.swap (str2); // str = abcdn
    cout << str << endl; 

insert():

string &insert(int p0, const char *s);——在p0位置插入字符串s

string &insert(int p0, const char *s, int n);——在p0位置插入字符串s的前n个字符

string &insert(int p0,const string &s);——在p0位置插入字符串s

string &insert(int p0,const string &s, int pos, int n);——在p0位置插入字符串s从pos开始的连续n个字符

string &insert(int p0, int n, char c);//在p0处插入n个字符c

iterator insert(iterator it, char c);//在it处插入字符c，返回插入后迭代器的位置

void insert(iterator it, const_iterator first, const_iterator last);//在it处插入从first开始至last-1的所有字符

void insert(iterator it, int n, char c);//在it处插入n个字符c

  string str = "to be question";
  string str2 = "the ";
  string str3 = "or not to be";
  string::iterator it;
    
  str.insert(6,str2);                 
    cout << str <<endl;  // str = to be the question
  str.insert(6,str3,3,4);            
    cout << str <<endl; // str = to be not the question
  str.insert(10,"that is cool",8);    
    cout << str <<endl; // str = to be not that is the question
  str.insert(10,"to be ");            
    cout << str <<endl; // str = to be not to be that is the question
  str.insert(15,1,':');               
    cout << str <<endl;  // str = to be not to be: that is the question
  it = str.insert(str.begin()+5,','); 
  str.insert (str.end(),3,'.');      
    cout << str <<endl; // str = to be, not to be: that is the question...
  str.insert (it+2,str3.begin(),str3.begin()+3); 
  cout << str <<endl; // str = to be, or not to be: that is the question...


append():

  string str;
  string str2="Writing ";
  string str3="print 10 and then 5 more";

  
  str.append(str2);                       // "Writing "
  str.append(str3,6,3);                   // "10 "
  str.append("dots are cool",5);          // "dots "
  str.append("here: ");                   // "here: "
  str.append(10,'.');                    // ".........."
  str.append(str3.begin()+8,str3.end());  // " and then 5 more"
  str.append(5,'.');                // "....."

  cout << str <<endl;//Writing 10 dots here: .......... and then 5 more.....


replace():

	  用str替换指定字符串从起始位置pos开始长度为len的字符
	  line=line.replace(line.find("&"),1,"1");//将line中的第一个&替换成1

	  用str替换 迭代器起始位置 到 结束位置 的字符 
	  line=line.replace(line.begin(),line.begin()+6,"1");//将line从begin位置开始的6个字符替换成1 
	  
	  用substr的指定子串（给定起始位置和长度）替换从指定位置上的字符串
	  line=line.replace(0,5,substr,substr.find("1"),3);//将line字符串0到5位置上的字符替换为substr的指定子串（从'1'位置开始的3个字符）
	  
	  用str替换大串指定位置上的子串
	  line=line.replace(0,5,str);//用str替换从指定位置0开始长度为5的字符串 
	  
	  用str替换从指定迭代器位置的字符串 
	  line=line.replace(line.begin(),line.begin()+9,str);
	  
	  用s的前n个字符替换从开始位置pos长度为len的字符串 
	  line=line.replace(0,9,str,5);//用str的前5个字符替换从0位置开始长度为9的字符串
	  
	  用s的前n个字符替换指定迭代器位置(从i1到i2)的字符串
	  line=line.replace(line.begin(),line.begin()+9,str,5);//用str的前5个字符替换指定迭代器位置的字符串  
	  
	  用重复n次的c字符替换从指定位置pos长度为len的内容 
	  line=line.replace(0,9,3,c);//用重复3次的c字符替换从指定位置0长度为9的内容

5. 输入输出

	string s1, s2;
	getline(cin, s1);
	getline(cin, s2, ' ');
	//终端输入
	//fgf gkgkjg xsx
    //ddw dwdw cxcx
	cout << "You inputed chars are: " << s1 << endl;//You inputed chars are: fgf gkgkjg xsx
	cout << "You inputed chars are: " << s2 << endl;//You inputed chars are: ddw


6.查找

find() 和 rfind():

	size_type find (value_type _Chr, size_type _Off = 0) const;
	//find()函数的第1个参数是被搜索的字符、第2个参数是在源串中开始搜索的下标位置
	
	size_type find (const value_type* _Ptr , size_type _Off = 0) const;
	//find()函数的第1个参数是被搜索的字符串，第2个参数是在源串中开始搜索的下标位置
	
	size_type find (const value_type* _Ptr, size_type _Off = 0, size_type _Count) const;
	//第1个参数是被搜索的字符串，第2个参数是源串中开始搜索的下标，第3个参数是关于第1个参数的字符个数，可能是 _Ptr 的所有字符数，也可能是 _Ptr 的子串宇符个数
	
	size_type find (const basic_string& _Str, size_type _Off = 0) const;
	//第1个参数是被搜索的字符串，第2参数是在源串中开始搜索的下标位置


    string str (" Hi, Peter, I'm sick. Please bought some drugs for me.");

    string::size_type m = str.find ('P', 5);
    string::size_type rm = str.rfind('P', 5);

    cout << "Example - find() : The position (forward) of 'P' is: " << (int) m << endl; // 5
    cout << "Example - rfind(): The position (reverse) of 'P' is: " << (int) rm << endl; // 5

    string::size_type n = str.find ("some", 0);
    string::size_type n2 = str.find ("sotme", 0);//被查找子串完全匹配才行，否则-1
    string::size_type rn = str.rfind ("some", 0);

    cout << "Example - find () : The position (forward) of 'some' is: " << (int) n << endl; //36
    cout << "Example - find () : The position (forward) of 'sotme' is: " << (int) n2 << endl; //-1 
    cout << "Example - rfind () : The position (reverse) of 'some' is: " << (int) rn << endl; // -1
    
    string::size_type mo = str.find ("drugs", 0, 5);
    string::size_type rmo = str.rfind ("drugs", 0, 5);

    cout << "Example - find(): The position (forward) of 'drugs' is: " << (int) mo << endl; // 41
    cout << "Example - rfind(): The position (reverse) of 'drugs' is: " << (int) rmo << endl; // -1 
    
    string str_ch ("for");
    string::size_type no = str.find (str_ch, 0);
    string::size_type rno = str.rfind(str_ch, 0);

    cout << "Example - find (): The position of 'for' is: " << (int) no << endl; // 47
    cout << "Example - rfind(): The position of 'for' is: " << (int) rno << endl; // -1


find_first_of() 和 find_last_of():

ind_first_of() 函数可实现在源串中搜索某字符串的功能，
该函数的返回值是被搜索字符串的第 1 个字符第 1 次出现的下标（位置）。若查找失败，则返回 npos。

find_last_of() 函数同样可实现在源串中搜索某字符串的功能。
与 find_first_of() 函数所不同的是，该函数的返回值是被搜索字符串的最后 1 个字符的下标（位置）。
若查找失败，则返回 npos。

string str("Hi, Peter, I'm sick. Please bought some drugs for me. ");
    int length = str.length();
    string::size_type m = str.find_first_of ('P');
    string::size_type rm = str.find_last_of ('P');
    cout << "Example - find_first_of (): The position (forward) of 'P' is: " << (int) m << endl;//4
    cout << "Example - find_last_of (): The position (reverse) of 'P' is： " << (int) rm << endl;//21
    string:: size_type n = str.find_first_of ("some", 0);    //只要匹配参数中字串的任意字符就返回其位置
    string:: size_type rn = str.find_last_of ("some", (length -1));
    cout << "Example - find_first_of(): The position (forward) of 'some' is: " << (int) n << endl;//5
    cout << "Example - find_last_of(): The position (reverse) of 'some' is: " << (int) rn << endl;//51
    string:: size_type mo = str.find_first_of ("drugs", 0, 5);
    string:: size_type rmo = str.find_last_of ("drugs", (length-1), 5);
    cout << "Example - find_first_of () : The position (forward) of 'drugs' is: " << (int) mo << endl;//8
    cout << "Example - find_last_of () : The position (reverse) of 'drugs' is: " << (int) rmo << endl;//48
    string str_ch ("for");
    string::size_type no = str.find_first_of (str_ch, 0);
    string::size_type rno = str.find_last_of (str_ch, (length -1));
    cout << "Example - find_first_of() : The position of 'for' is: " << (int) no << endl;//8
    cout << "Example - find_last_of () : The position of 'for' is: " << (int) rno << endl;//48


find_first_not_of() 和 find_last_not_of():

find_first_not_of() 函数可实现在源字符串中搜索与指定字符（串）不相等的第 1 个字符；
find_last_not_of() 函数可实现在源字符串中搜索与指定字符（串）不相等的最后 1 个字符。
这两个函数的参数意义和前面几个函数相同，它们的使用方法和前面几个函数也基本相同




