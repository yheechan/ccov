//example1.c
int static_var = 1;

int f1(int a) {
	static_var++;
	//if-else
	if( a == 1) {
		return 2;
	} else {
		return 4;
	}
}

int main() {
	int a = 0;
	a = f1(a);
	//if-else if-else
	if( a == 1 && a == 3 && a == 4) {
		a =  2;
	} else if ( a == 2){
		a = 1;
	} else {
		a = 4;
	}	
}