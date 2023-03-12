#include<iostream>
class Base{ 
  public: 
	int base_int; 
 
	Base (int i){ 
		this -> base_int = i; 
    } 
 
    virtual int getInt(){ 
		return this -> base_int; 
	} 
}; 
 
class Derived : public Base{ 
  public: 
    int derived_int; 
 
    Derived (int i , int j) : Base(j){ 
	    	this -> derived_int = i; 
    }  
 
    int getInt(){ 
	    	return this -> derived_int; 
    } 
}; 
 
int main() { 
	Base* basePointerToBase = new Base(0); 
	Base* basePointerToDerived = new Derived(10, 5); 
	std::cerr << basePointerToBase ->getInt() << std::endl; 
	std::cerr << basePointerToDerived ->getInt() << std::endl;
	return 0; 
} 