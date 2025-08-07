#include<iostream>
#include<memory>

using namespace std;

int main() {
	
    shared_ptr<int> p1(new int); // ? substituindo o malloc -> template de ponteiro inteligente
	*p1 = 10;
	shared_ptr<int> p2 = p1;
	*p2 = 5; // 
	cout << *p1;
    p1.reset();    // ? substituindo o delete, sintexe do reset sem parametro restorna o ponteiro para nullptr
	p1 = nullptr;
	*p2 = 6;       // ! erro proposital 
    cout << *p2;
    return 0;

}
