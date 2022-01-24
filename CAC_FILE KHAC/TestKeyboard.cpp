#include <iostream>
#include <conio.h>
using namespace std;

int main(){
	char kytu;
	while(1){
		if (kbhit()){
			kytu = getch();
			cout << (int)kytu;
			if (kytu == -32){
				kytu = getch();
				cout << (int)kytu;
			}
		}
	}
	
	system("pause");
}
