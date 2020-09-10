#include <iostream>
#include <cstdlib>
using namespace std;
class Pair
{
public:
	int x, y;
	Pair(int x1 = 0, int y1 = 0) { x = x1; y = y1; }
};
int main() {
	int const SIZE = 10;
	int a, b;
	
	Pair* all = new Pair[SIZE];
	int tot = 0;
	for (int i = 0; i < SIZE; i++)
	{
		cout << "Enter two Integers >";
		cin >> a >> b;
		all[i] = Pair(a, b);
		tot += all[i].x + all[i].y;
	}

	cout << tot << endl;
	return 0;
}