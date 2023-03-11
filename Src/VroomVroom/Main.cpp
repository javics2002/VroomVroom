#include <iostream>

using namespace std;

void hello() {
	cout << "hello\n";
}

#ifdef _DEBUG
void main() {
	hello();
}
#endif
