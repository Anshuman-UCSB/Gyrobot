// CPP program to demonstrate multithreading 
// using three different callables. 
#include <iostream> 
#include <thread> 
using namespace std; 
int n = 0;
// A dummy function 
void foo() 
{ 
	while(true){
        n++;
    }
} 

int main() 
{ 
	thread th1(foo);
    for(int i = 0;i<10000000;i++){}
    cout<<n<<endl;
    
	// Wait for thread t1 to finish 
	th1.join(); 

	return 0; 
} 
