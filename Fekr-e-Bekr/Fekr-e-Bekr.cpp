// Fekr-e-Bekr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "string.h"
#include "time.h"
#include "math.h"

#define ESCAPE_CHAR 27

char rndchs[9 * 8 * 7 * 6][4];
int max_available;
int validate[9][9][9][9];
int bnum[9][9][9][9];
int dnum[9][9][9][9];
time_t ltime;

void solve();
int check_valid(int a, int b, int c, int d);
void set_valid();
void setv(int a, int b, int c, int d, int e);
int print_number();
void setb(int a, int b, int c, int d, int e);
void reset_validate();
void rndnum(int* a, int b, int c, int d);
void fill_rndchs();

int _tmain(int argc, _TCHAR* argv[])
{
	while(true)
	{
		reset_validate();
		solve();
		printf("\n\n--------------------------------------------------------------------------------\n\n");
	}

	return 0;
}

void solve()
{
	char c;

	printf("\n\n          Choose your 4-digit number and press Enter to start the game");
	while(true)
	{
		c = getch();
		if(c == ESCAPE_CHAR) exit(3);
		if(c == '\r') break;
		continue;
	}

	while(true) 
	{
		set_valid();
		if(print_number() == 1) return;
	}
}

int check_valid(int a, int b, int c, int d)
{
	int i, j, n, m;
	int x = 0, count = 0;

	for(i = 0; i < 9; ++i)
		for(j = 0; j < 9; ++j)
			for(n = 0; n < 9; ++n)
				for(m = 0; m < 9; ++m)
				{
					if(validate[i][j][n][m] == 2) 
					{
						x = bnum[i][j][n][m] + dnum[i][j][n][m];

						if(a == i || a == j || a == n || a == m) ++count;
						if(b == i || b == j || b == n || b == m) ++count;
						if(c == i || c == j || c == n || c == m) ++count;
						if(d == i || d == j || d == n || d == m) ++count;

						if(count < x) return -1;
						count = 0;
					}
				}
	return 1;
}

void set_valid()
{
	int i, j, n, m;

	for(i = 0; i < 9; ++i)
		for(j = 0; j < 9; ++j)
			for(n = 0; n < 9; ++n)
				for(m = 0; m < 9; ++m)
					if(validate[i][j][n][m] != 2)
						if(check_valid(i, j, n, m) == -1) validate[i][j][n][m] = 0;
}

int print_number()
{
	int rndhelp;
	int a1[4] = {0};
	int i, j, n, m;
	int i1, j1, n1, m1;
	int x = 0, b = 0, d = 0;
	char str[5] = {0};

	for(i = 0; i < 9; ++i)
		for(j = 0; j < 9; ++j)
			for(n = 0; n < 9; ++n)
				for(m = 0; m < 9; ++m)
				{
					fill_rndchs();
					if(max_available < 0) break;
					rndnum(&rndhelp, 1, 0, max_available);
					i = rndchs[rndhelp][0];
					j = rndchs[rndhelp][1];
					n = rndchs[rndhelp][2];
					m = rndchs[rndhelp][3];
					printf("\n\n     %d%d%d%d", i + 1, j + 1, n + 1, m + 1);

					while(true)
					{
						printf("\n\n the answer is(d & b): ");

						while(true)
						{
							str[x] = getch();

							if(str[x] == 27) //27 == Escape
							{	
								printf("\n\n\n\n     press \"r\" to play again and press \"q\" to quit");
								while(true)
								{
									switch(getch())
									{
									case 'r' :
									case 'R' :
										return 1;
									case 'q' :
									case 'Q' :
										exit(0);
									default :
										break;
									}
								}
							}

							if(x > 3)
								if(str[x] != '\r' && str[x] != 8) continue; //8 = BackSpace

							if(str[x] != '\r' && str[x] != 'b' && str[x] != 'd' && str[x] != 'B' && str[x] != 'D' && str[x] != 8)
								continue;
							
							if(str[x] == 8) //8 = BackSpace
							{
								if(x > 0)
								{
									putchar(str[x]);
									putchar(' ');
									putchar(str[x]);

									str[x] = '\0';
									--x;
								}
								continue;
							}

							putchar(str[x]);
							if(str[x] == '\r')
							{
								str[x] = '\0';
								break;
							}
							++x;
						}
						
						break;
					}

					for(x = 0; x < 4; ++x)
					{
						if(str[x] == 'b') ++b;
						if(str[x] == 'd') ++d;
					}

					setv(i, j, n, m, b + d);
					setb(i, j, n, m, b);
					
					if(b == 4)
					{
						printf("\n\n     Successful finish. press \"r\" to play again and press \"q\" to quit");
						while(1 < 2)
						{
							switch(getch())
							{
							case 'r' :
							case 'R' :
								return 1;
							case 'q' :
							case 'Q' :
								exit(0);
							default :
								break;
							}
						}
					}

					bnum[i][j][n][m] = b;
					dnum[i][j][n][m] = d;

					validate[i][j][n][m] = 2;

					return 0;
				}
				printf("\n\n     Error:you have made a mistake.press \"r\" to play again and press \"q\" to quit");
				while(1 < 2)
				{
					switch(getch())
					{
					case 'r' :
					case 'R' :
						return 1;
					case 'q' :
					case 'Q' :
						exit(0);
					default :
						break;
					}
				}
}

void setv(int a, int b, int c, int d, int e)
{
	int i, j, n, m;
	int count = 0;

	for(i = 0; i < 9; ++i)
		for(j = 0; j < 9; ++j)
			for(n = 0; n < 9; ++n)
				for(m = 0; m < 9; ++m)
				{
					if(validate[i][j][n][m] == 1)
					{
						if(a == i || a == j || a == n || a == m) ++count;
						if(b == i || b == j || b == n || b == m) ++count;
						if(c == i || c == j || c == n || c == m) ++count;
						if(d == i || d == j || d == n || d == m) ++count;

						if(count != e) validate[i][j][n][m] = 0;
					}
					count = 0;
				}
}

void setb(int a, int b, int c, int d, int e)
{
	int i, j, n, m;
	int count = 0;

	for(i = 0; i < 9; ++i)
		for(j = 0; j < 9; ++j)
			for(n = 0; n < 9; ++n)
				for(m = 0; m < 9; ++m)
				{
					if(validate[i][j][n][m] == 1)
					{
						if(a == i) ++count;
						if(b == j) ++count;
						if(c == n) ++count;
						if(d == m) ++count;

						if(count != e) validate[i][j][n][m] = 0;
					}
					count = 0;
				}
}

void reset_validate()
{
	int i, j, n, m;

	for(i = 0; i < 9; ++i)
		for(j = 0; j < 9; ++j)
			for(n = 0; n < 9; ++n)
				for(m = 0; m < 9; ++m)
				{
					bnum[i][j][n][m] = 0;
					dnum[i][j][n][m] = 0;

					if(i == j || i == n || i == m || j == n || j == m || n == m) 
						validate[i][j][n][m] = 0;
					else
						validate[i][j][n][m] = 1;
				}
}

void rndnum(int* a, int b, int c, int d)
{
	int i = 0, j, k = 0;
	long double r1;
	long int r3;
	time(&ltime);
	while(1 < 2)
	{
		++ltime;
		r1 = ltime;
		r1 = abs(sin((long double) ltime));
		r1 *= d;
		r3 = (long int) r1;
		r3 += c;

		for(j = i - 1; j >= 0; --j)
			if(a[j] == r3)
			{
				k = 1;
				break; 
			}

		if(k == 1)
		{
			k = 0;
			continue;
		}
		a[i] = r3;
		++i;
		if(i == b) return;
	}
}

void fill_rndchs()
{
	int i, j, n, m;
	int b = 0;

	for(i = 0; i < 9; ++i)
		for(j = 0; j < 9; ++j)
			for(n = 0; n < 9; ++n)
				for(m = 0; m < 9; ++m)
					if(validate[i][j][n][m] == 1)
					{
						rndchs[b][0] = i;
						rndchs[b][1] = j;
						rndchs[b][2] = n;
						rndchs[b][3] = m;
						++b;
					}
	max_available = b - 1;
}

