# include <iostream>
# include <time.h>

int main() {

 clock_t tic = clock();
	
	int a = 1;       //Sequential instructions
	int b = 2;       //-----------------------
	
	if (b == 2)      //Jump instruction
		std::cout << "OI \n";
	clock_t toc = clock();
	double tt = (double)(toc - tic); // CLOCKS_PER_SEC)
	std::cout << tt;
 return 0;
}
