#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<windows.h>
#define MAX 60000
#define OK 1
#define ERROR 0
int prime[4701];//�������㣬ֻ��Ҫǰ4700����������
using namespace std;
int TheFirstPartPrime()
{//����ǰ4700������ 
	int N = 45310;
	int *Location = new int[N + 1];
	for (int i = 2; i != N + 1; ++i)
	{
		Location[i] = 1;
	}
	int num_prime = 0;
	for (int i = 2; i < N; i++)
	{//����ɸ��          
		if (Location[i])
			prime[++num_prime] = i;
		for (int j = 1; j <= num_prime && i * prime[j] < N; j++)
		{
			Location[i * prime[j]] = 0;
			if (!(i % prime[j]))
				break;
		}
	}
	prime[0] = num_prime;
	return OK;
}

int BigPrime(int N)
{
	int MNUM;
	bool *Location = new bool[MAX + 1];
	int p, q, end, m, tmp, pm = 45307;
	Location[0] = 0;
	TheFirstPartPrime();
	if (N <= 4700)
	{//����NС�ڵ���4700
		//printf("The %dth prime is ", N);
		printf("%d\n", prime[N]);
		return OK;
	}
	while (1)
	{//����N����4700 
		m = pm;
		int a;
		a = pm % 3;
		for (int i = 1; i <= MAX; i += 6)
		{//Ԥ��ɸ��2��3�ı��� 
			Location[i] = false;
			Location[i + 2] = false;
			Location[i + 4] = false;
			if (a == 0)
			{
				Location[i + 1] = true;
				Location[i + 3] = true;
				Location[i + 5] = false;
			}
			else if (a == 1)
			{
				Location[i + 1] = false;
				Location[i + 3] = true;
				Location[i + 5] = true;
			}
			else
			{
				Location[i + 1] = true;
				Location[i + 3] = false;
				Location[i + 5] = true;
			}
		}
		end = (int)sqrt((double)(MNUM = pm + MAX)) + 1;
		p = prime[3];
		for (int i = 3; p<end; i++)
		{
			p = prime[i];
			q = m / p + 1;
			switch (int tmp = q % (2 * 3))
			{//��Ϊ2��3�ı����Ѿ�������ˣ����ദ��������ദ�� 
			case 0:
			{
				q += 1;
				for (long long k = p * q; k <= MNUM; k *= p)
					Location[k - m] = false;
				q += 4;
				for (long long k = p * q; k <= MNUM; k *= p)
					Location[k - m] = false;
				break;
			}
			case 1:
			{
				for (long long k = p * q; k <= MNUM; k *= p)
					Location[k - m] = false;
				q += 4;
				for (long long k = p * q; k <= MNUM; k *= p)
					Location[k - m] = false;
				break;
			}
			case 2:
			{
				q += 3;
				break;
			}
			case 3:
			{
				q += 2;
				break;
			}
			case 4:
			{
				q += 1;
				break;
			}
			default:
				break;
			}
			while (p * q <= MNUM)
			{//ɸ���� 
				for (long long k = p * q; k <= MNUM; k *= p)
					Location[k - m] = false;
				q += 2;
				for (long long k = p * q; k <= MNUM; k *= p)
					Location[k - m] = false;
				q += 4;
			}

		}
		p = prime[3];
		int num = prime[0];
		for (int i = 1; i <= MAX; ++i)
		{//������N������ 
			if (Location[i])
			{
				++num;
				tmp = i + pm;
				if (num == N)
				{
					//printf("The %dth prime is ", num);
					printf("%d\n", tmp);
					return OK;
				}
			}
		}
		prime[0] = num;
		pm = tmp;
	}

}

int get_prime()
{
	//printf("Please input number(1 - 100660000):");
	char str[100];
	gets_s(str);
	int i = 0;
	while (str[i] != '\0')
	{//�����Ƿ�Ϊ���ּ�� 
		if (str[i] >= '0'&&str[i] <= '9')
			i++;
		else
		{
			puts("INPUT ERROR!");
			return ERROR;
		}
	}
	int nth;
	if (str[i] == '\0')
		nth = atoi(str);
	if (nth <= 0 || nth > 100660000)
	{//�����Ƿ񳬷�Χ��� 
		puts("INPUT RANGE ERROR!");
		return ERROR;
	}
	//printf("Computing...\n");
	//double time_start, time_end;
	//time_start = GetTickCount();//��ʱ 
	BigPrime(nth);
	//time_end = GetTickCount();
	//printf("Time costs: %.2f seconds\n\n", (time_end - time_start) / 1000);
	return OK;
}
int main()
{//�ɹ�����1st-100660000th prime! 
		get_prime();
		return OK;
}