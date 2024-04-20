#include <stdio.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>

inline int is_straight(int *k);
inline int is_quadsorfullhouse(int* k);
inline int is_quadsorfullhouse_table(int* k);
inline bool bit_check(int number, int n);

std::vector<int> straight_table, quadsorfullhouse_table;

int main()
{
	const int TABLE_SIZE = 16384;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		int x = 0;

		for (int j = 0; j < 14; j++)
		{
			if (bit_check(i, j))
			{
				x++;
			}
			else if (j == 1)
			{
				x = 0;
			}
			else if (x != 0)
			{
				break;
			}
		}

		if (x == 5)
		{
			straight_table.push_back(1);
		}
		else
		{
			straight_table.push_back(0);
		}
	}

	// Neloset tai täyskäsi
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		int x = 0;

		for (int j = 0; j < 14; j++)
		{
			if (bit_check(i, j))
			{
				x++;
			}
		}

		if (x == 2)
		{
			quadsorfullhouse_table.push_back(1);
		}
		else
		{
			quadsorfullhouse_table.push_back(0);
		}
	}

	

  int k0, k1, k2, k3, k4; /* Pakan kortit, 0..51*/
  int k[5]; /* Korttien numeroarvot, 2..14*/
  int suoria, quadsorfullhouse; /* Suorien lkm*/
  clock_t t1, t2;

  t1 = clock();
  suoria = 0;
  quadsorfullhouse = 0;
  for (k0 = 0; k0 < 52; ++k0) {
  for (k1 = 0; k1 < 52; ++k1) { if (k1==k0)continue;
  for (k2 = 0; k2 < 52; ++k2) { if (k2==k0||k2==k1)continue;
  for (k3 = 0; k3 < 52; ++k3) { if (k3==k0||k3==k1||k3==k2)continue;
  for (k4 = 0; k4 < 52; ++k4) { if (k4==k0||k4==k1||k4==k2||k4==k3)continue;

	    /*
	      Lasketaan korttien numeroarvot ja
	      tarkistetaan onko suora.
	    */
	    k[0] = (k0 % 13) + 2;
	    k[1] = (k1 % 13) + 2;
	    k[2] = (k2 % 13) + 2;
	    k[3] = (k3 % 13) + 2;
	    k[4] = (k4 % 13) + 2;
		if (is_straight(k))
			++suoria;
		if (is_quadsorfullhouse_table(k))
			++quadsorfullhouse;

	  }}}}}
  t2 = clock();
  printf("Suoria     : %d kpl (oikea arvo 1228800)\n", suoria);
  printf("Nelosia tai Tayskasia     : %d kpl (oikea arvo 524160)\n", quadsorfullhouse);
  printf("Aikaa kului: %.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

  return 0;
}

// ~6s hakutaululla
inline int is_quadsorfullhouse_table(int* k)
{
	int* x = k;
	int bit_vector = 0;

	for (int i = 0; i < 5; i++)
	{
		bit_vector = bit_vector | ((int)1 << (*x) - 1);
		x++;
	}

	return quadsorfullhouse_table[bit_vector];
}

// ~60s ilman hakutaulua
inline int is_quadsorfullhouse(int* k)
{
	int* x = k;
	std::sort(x, x + 5);

	int counter = 0;

	for (int i = 0; i < 5; i++)
	{
		if (*x == *(x + 1))
		{
			counter++;
		}
		x++;
	}

	if (counter == 3)
	{
		return 1;
	}

	return 0;
}

// ~60s ilman hakutaulua
// ~6s hakutaululla
inline int is_straight(int *k)
{
	int* x = k;
	int bit_vector = 0;

	for (int i = 0; i < 5; i++)
	{
		bit_vector = bit_vector | ((int)1 << (*x) -1);

		if (*x == 14)
		{
			bit_vector = bit_vector | ((int)1 << 0);
		}
		x++;
	}

	return straight_table[bit_vector];

	
	//int* x = k;
	//std::sort(x, x + 5);

	//if (*x == *(x + 1) - 1)
	//	if (*(x + 1) == *(x + 2) - 1)
	//		if (*(x + 2) == *(x + 3) - 1)
	//			if (*(x + 3) == *(x + 4) - 1 || (*(x + 4) == 14 && *x == 2))
	//				return 1;

	//return 0;
}

inline bool bit_check(int number, int n)
{
	return (number >> n) & (int)1;
}
