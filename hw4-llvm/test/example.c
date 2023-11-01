//example.c
int static_var = 1;

struct HelloWorld {
	int x;
	int y;
	int z;
};

struct HelloWorld hw[10];

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
	hw[1].z = 22;
	int b = f1(hw[1].z);

	int a = 0;
	a = f1(a);
	//if-else if-else
	if( a == 1) {
		a =  2;
	} else if ( a == 2){
		a = 1;
	} else {
		a = 4;
	}	
	
	//for	
	for( int i = 0 ; i < 10 ; i++ ) {
		a += i;
	}
	
	//while
	while( a < 100 ) {
		a += a;
	}
	
	//do-while
	do {
		switch(a) {
			case 100: 
				a += 10;
				break;
			case 200: 
				a = a == 3 ? 1 : 2;// ?: operator 
				a += 20;
				break;
			default:
				a += 1;
		}
	} while( a == 0 );

	switch(a) {
		case 150:
			a+=20;
			break;
		case 250:
			a+=30;
			break;
	}
}

/* Condition coverage for one execution:
   --------
7.0 -> 0, 1
18.0 -> 0, 1
20.0 -> 0, 1
27.0 -> 10, 1
32.0 -> 2, 1
38.0 -> 0, 0
38.1 -> 0, 0
38.2 -> 1, 0
49.0 -> 0, 1
51.0 -> 0, 0
51.1 -> 0, 0
51.2 -> 1, 0
Total: 18 branches, Covered: 10 branches
*/
