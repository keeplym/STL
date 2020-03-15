
std::vector::swap()

The std::swap function is used to swap two elements where as the std::vector::swap()
function can swap all elements of two different vector containers.



The std::vector::swap() function is used to swap the entire contents of one vector with another vector of same type and size.



	vector<int> v1 = {1, 2, 3}; 
    vector<int> v2 = {4, 5, 6}; 
      
    // swapping the above two vectors 
    // using std::vector::swap 
    v1.swap(v2); 