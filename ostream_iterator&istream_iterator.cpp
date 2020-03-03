1.ostream_iterator
template <class T, class charT=char, class traits=char_traits<charT> >
  class ostream_iterator;


Ostream iterators are output iterators that write sequentially to an output stream (such as cout).

They are constructed from a basic_ostream object, to which they become associated, so that whenever an assignment operator (=) 
is used on the ostream_iterator (dereferenced or not) it inserts a new element into the stream.

Optionally, a delimiter can be specified on construction. This delimiter is written to the stream after each element is inserted.

// ostream_iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy

int main () {
  std::vector<int> myvector;
  for (int i=1; i<10; ++i) myvector.push_back(i*10);

  std::ostream_iterator<int> out_it (std::cout,", "); //cout是一个对象
  std::copy ( myvector.begin(), myvector.end(), out_it ); //10, 20, 30, 40, 50, 60, 70, 80, 90, 
  return 0;
}



2.istream_iterator
template <class T, class charT=char, class traits=char_traits<charT>, 
          class Distance = ptrdiff_t>
  class istream_iterator;


Istream iterators are input iterators that read successive elements from an input stream (such as cin).

They are constructed from a basic_istream object, to which they become associated, so that whenever operator++ 
is used on the iterator, it extracts an element from the stream (using operator>>).

This kind of iterator has a special state as an end-of-stream iterator, which is acquired if an input operations fails 
(as returned by fail after an operation with the associated stream), and is also the resulting value of a default-constructed object.


Ex1:
// istream_iterator example
#include <iostream>     // std::cin, std::cout
#include <iterator>     // std::istream_iterator

int main () {
  double value1, value2;
  std::cout << "Please, insert two values: "; // 2 32

  std::istream_iterator<double> eos;              // end-of-stream iterator
  std::istream_iterator<double> iit (std::cin);   // stdin iterator

  if (iit!=eos) value1=*iit;

  ++iit;
  if (iit!=eos) value2=*iit;

  std::cout << value1 << "*" << value2 << "=" << (value1*value2) << '\n'; // 2*32=64

  return 0;
}

Ex2:
#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <algorithm>
 
int main()
{
    std::istringstream str("0.1 0.2 0.3 0.4");
    std::partial_sum(std::istream_iterator<double>(str),
                     std::istream_iterator<double>(),
                     std::ostream_iterator<double>(std::cout, " "));
 
    std::istringstream str2("1 3 5 7 8 9 10");
    std::cout << "\nThe first even number is " <<
        *std::find_if(std::istream_iterator<int>(str2),
                      std::istream_iterator<int>(),
                      [](int i){return i%2 == 0;})
        << ".\n";
    //" 9 10" left in the stream
}
Output:

0.1 0.3 0.6 1 
The first even number is 8.




