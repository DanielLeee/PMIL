#include <stdio.h>
#include <Windows.h>

int main()
{
	LARGE_INTEGER freq;
	::QueryPerformanceFrequency(&freq); // Execute this only once.

	LARGE_INTEGER counterStart, counterFinish;
	::QueryPerformanceCounter(&counterStart);
	int sum = 0;
	for (int i = 0; i < 999; ++i)
	{
		sum += i;
	}
	printf("sum = %d\n", sum);
	::QueryPerformanceCounter(&counterFinish);
	LONGLONG span = counterFinish.QuadPart - counterStart.QuadPart;
	double spanInSecond = (double)span / (double)freq.QuadPart;
	printf("Span = %lf seconds.\n", spanInSecond);

	return 0;
}