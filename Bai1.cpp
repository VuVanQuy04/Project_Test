#include <stdio.h>

int main()
{
	float a,b;
	printf("nhap hai so thuc a va b: ");
	scanf("%f %f" , &a ,&b);
	float T = a / b ;
	if (b=0)
	{
		printf("khong chia duoc!");
	}
	else
	{
		printf ("T = %.0f" , T);
	}
}
