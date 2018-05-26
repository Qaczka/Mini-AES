#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *mnoz(int a[], int b[], int l)
{
	int stopien_R[7], nr, red[7], n, i, m, konc[4];

	for (i = 0; i<7; i++)
	{
		stopien_R[i] = 0;
	}

	for (i = 0; i<4; i++)
	{
		for (m = 0; m<4; m++)
		{
			//nr=stopien_A[m]+stopien_B[i];
			nr = (3 - m) + (3 - i);
			stopien_R[nr] = stopien_R[nr] + (a[i] * b[m]);
		}
	}

	// printf("Wielomian to: ");

	for (i = 0; i<7; i++)
	{
		stopien_R[6 - i] = stopien_R[6 - i] % 2;
		//printf("%i ",stopien_R[6-i]);
		red[i] = 0;
	}

	//printf("\n");

	int tymczas_R;
	tymczas_R = 0;

	for (m = 0; m<3; m++)
	{
		tymczas_R = stopien_R[6 - m];

		if (stopien_R[6 - m] != 0)
		{
			red[6 - m] = 1;
			red[6 - m - 3] = 1;
			red[6 - m - 4] = 1;

			// printf("RED TO: ");


			//printf("\n");

			for (n = 0 + m; n<7; n++)
			{
				// printf("%i",tymczas_R);
				stopien_R[6 - n] = (stopien_R[6 - n] + (tymczas_R*red[6 - n])) % 2;
			}

			//  printf("Stopien R to\n");


			/* for(n=0;n<7;n++)
			{
			printf("%i ",stopien_R[6-n]);
			}
			printf("\n");
			*/
			red[6 - m] = 0;
			red[6 - m - 3] = 0;
			red[6 - m - 4] = 0;
		}
	}
	return (int*)stopien_R[l];// mozna wyjac tylko element wg l-a
}

int * obciecie(int stopien_R[], int m)
{
	int *tymczas_R[4], n;

	for (n = 3; n >= 0; n--)
	{
		tymczas_R[3 - n] = (int*)stopien_R[n];
	}

	return tymczas_R[m];
}


//--------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------



int main()
{
	int a[16], b[16], dodawanie[16], i, mnozenie[4], redukcyjny[4], m, z1, z2, stopien_R[7], n;
	char WPISa[16], WPISb[16];

	//-------------------------------------------------------------------------------------------------------------------------------------//

	//DEFINICJE SBOXOW


	int SBoxE[16][4] = { { 0,0,0,0 },{ 0,0,0,1 },{ 0,0,1,0 },{ 0,0,1,1 },{ 0,1,0,0 },{ 0,1,0,1 },{ 0,1,1,0 },{ 0,1,1,1 },{ 1,0,0,0 },{ 1,0,0,1 },{ 1,0,1,0 },{ 1,0,1,1 },{ 1,1,0,0 },{ 1,1,0,1 },{ 1,1,1,0 },{ 1,1,1,1 } },
		SBoxD[16][4] = { { 1,1,1,0 },{ 0,1,0,0 },{ 1,1,0,1 },{ 0,0,0,1 },{ 0,0,1,0 },{ 1,1,1,1 },{ 1,0,1,1 },{ 1,0,0,0 },{ 0,0,1,1 },{ 1,0,1,0 },{ 0,1,1,0 },{ 1,1,0,0 },{ 0,1,0,1 },{ 1,0,0,1 },{ 0,0,0,0 },{ 0,1,1,1 } };


	//-------------------------------------------------------------------------------------------------------------------------------------//

	a[0] = 0;
	a[1] = 0;
	a[2] = 1;
	a[3] = 1;
	a[4] = 1;
	a[5] = 1;
	a[6] = 0;
	a[7] = 0;
	a[8] = 1;
	a[9] = 1;
	a[10] = 0;
	a[11] = 0;
	a[12] = 0;
	a[13] = 0;
	a[14] = 1;
	a[15] = 1;

	//b[0]=1;
	scanf("%i", &b[0]);
	b[1] = 0;
	b[2] = 1;
	b[3] = 1;
	b[4] = 0;
	//b[5]=0;
	scanf("%i", &b[5]);
	b[6] = 1;
	b[7] = 0;
	b[8] = 1;
	b[9] = 1;
	b[10] = 1;
	//b[11]=1;
	scanf("%i", &b[11]);
	//b[12]=0;
	scanf("%i", &b[12]);
	b[13] = 1;
	b[14] = 1;
	b[15] = 0;

	/*
	for(i=0;i<16;i++)
	{
	scanf("%i",&a[i]);
	}
	*/

	printf("Dodanie klucza poczatkowego do tekstu: ");

	for (i = 0; i<16; i++)
	{
		dodawanie[i] = (a[i] + b[i]) % 2;
		printf("%i", dodawanie[i]);
	}
	int t[4][4];

	for (m = 0; m<4; m++)
	{
		t[0][m] = dodawanie[m];
		t[1][m] = dodawanie[m + 4];
		t[2][m] = dodawanie[m + 8];
		t[3][m] = dodawanie[m + 12];
	}

	//-------------------------------------------------------------------------------------------------------------------------------------//

	int zaszlo0 = 0, zaszlo1 = 0, zaszlo2 = 0, zaszlo3 = 0;

	for (i = 0; i<16; i++)
	{
		if ((t[0][0] == SBoxE[i][0]) && (t[0][1] == SBoxE[i][1]) && (t[0][2] == SBoxE[i][2]) && (t[0][3] == SBoxE[i][3]) && zaszlo0 == 0)
		{
			zaszlo0 = 1;

			for (m = 0; m<4; m++)
			{
				t[0][m] = SBoxD[i][m];
			}
		}
		else if ((t[1][0] == SBoxE[i][0]) && (t[1][1] == SBoxE[i][1]) && (t[1][2] == SBoxE[i][2]) && (t[1][3] == SBoxE[i][3]) && zaszlo1 == 0)
		{
			zaszlo1 = 1;


			for (m = 0; m<4; m++)
			{
				t[1][m] = SBoxD[i][m];
			}
		}
		else if ((t[2][0] == SBoxE[i][0]) && (t[2][1] == SBoxE[i][1]) && (t[2][2] == SBoxE[i][2]) && (t[2][3] == SBoxE[i][3]) && zaszlo2 == 0)
		{
			zaszlo2 = 1;

			for (m = 0; m<4; m++)
			{
				t[2][m] = SBoxD[i][m];
			}
		}
		else if ((t[3][0] == SBoxE[i][0]) && (t[3][1] == SBoxE[i][1]) && (t[3][2] == SBoxE[i][2]) && (t[3][3] == SBoxE[i][3]) && zaszlo3 == 0)
		{
			zaszlo3 = 1;

			for (m = 0; m<4; m++)
			{
				t[3][m] = SBoxD[i][m];
			}
		}
	}

	for (m = 0; m<4; m++)
	{
		dodawanie[m] = t[0][m];
		dodawanie[m + 4] = t[1][m];
		dodawanie[m + 8] = t[2][m];
		dodawanie[m + 12] = t[3][m];
	}


	printf("\n");

	printf("Pierwszy SBox: ");

	for (m = 0; m<16; m++)
	{
		printf("%i", dodawanie[m]);
	}

	printf("\n");


	//-------------------------------------------------------------------------------------------------------------------------------------//

	int ZK[16], tymczas[4];


	for (m = 0; m<16; m++)
	{
		ZK[m] = dodawanie[m];
	}


	for (m = 0; m<4; m++)
	{
		tymczas[0 + m] = dodawanie[8 + m];
		dodawanie[8 + m] = dodawanie[12 + m];
		dodawanie[12 + m] = tymczas[0 + m];
	}

	printf("Pierwsze ZK: ");

	for (m = 0; m<16; m++)
	{
		printf("%i", dodawanie[m]);
	}

	printf("\n");

	//-------------------------------------------------------------------------------------------------------------------------------------//

	int  a0[4] = { 0,0,1,1 }, a1[4] = { 0,0,1,0 }, a2[4] = { 0,0,1,0 }, a3[4] = { 0,0,1,1 }, m0[4], m1[4], m2[4], m3[4];
	int mn1[4], mn2[4], kon0[4], kon1[4], kon2[4], kon3[4];


	for (m = 0; m<4; m++)
	{
		m0[m] = dodawanie[m];
		m1[m] = dodawanie[m + 4];
		m2[m] = dodawanie[m + 8];
		m3[m] = dodawanie[m + 12];
	}




	for (i = 0; i<4; i++)
	{

		for (n = 0; n<4; n++)
		{
			mn1[3 - n] = (int)mnoz(a0, m0, n);
			mn2[3 - n] = (int)mnoz(a1, m2, n);
		}

		//printf("mn1 to: \n");

		for (n = 0; n<4; n++)
		{
			// printf("%i",mn1[n]);
		}

		// printf("\n");
		// printf("mn2 to: \n");

		for (n = 0; n<4; n++)
		{
			// printf("%i",mn2[n]);
		}

		// printf("\n");

		for (i = 0; i<4; i++)
		{
			kon0[3 - i] = (mn1[i] + mn2[i]) % 2;
			// printf("%i",kon0[3-i]);
		}

		//printf("\n");
		//  printf("\n");


		// mnozenie[i]=(a[i]*b[i]+a[4+i]*b[8+i]);

		for (n = 0; n<4; n++)
		{
			mn1[3 - n] = (int)mnoz(a0, m1, n);
			mn2[3 - n] = (int)mnoz(a1, m3, n);
		}

		// printf("mn1 to: \n");

		for (n = 0; n<4; n++)
		{
			//  printf("%i",mn1[n]);
		}

		//  printf("\n");
		// printf("mn2 to: \n");

		for (n = 0; n<4; n++)
		{
			//  printf("%i",mn2[n]);
		}

		// printf("\n");

		for (i = 0; i<4; i++)
		{
			kon1[3 - i] = (mn1[i] + mn2[i]) % 2;
			//  printf("%i",kon1[3-i]);
		}

		//  printf("\n");
		// printf("\n");


		// mnozenie[4+i]=(a[i]*b[4+i]+a[4+i]*b[12+i]);

		for (n = 0; n<4; n++)
		{
			mn1[3 - n] = (int)mnoz(a2, m0, n);
			mn2[3 - n] = (int)mnoz(a3, m2, n);
		}

		// printf("mn1 to: \n");

		for (n = 0; n<4; n++)
		{
			//  printf("%i",mn1[n]);
		}

		// printf("\n");
		// printf("mn2 to: \n");

		for (n = 0; n<4; n++)
		{
			// printf("%i",mn2[n]);
		}

		// printf("\n");

		for (i = 0; i<4; i++)
		{
			kon2[3 - i] = (mn1[i] + mn2[i]) % 2;
			//printf("%i",kon2[3-i]);
		}

		//printf("\n");
		// printf("\n");


		// mnozenie[8+i]=(a[8+i]*b[i]+a[12+i]*b[8+i]);

		for (n = 0; n<4; n++)
		{
			mn1[3 - n] = (int)mnoz(a2, m1, n);
			mn2[3 - n] = (int)mnoz(a3, m3, n);
		}

		//   printf("mn1 to: \n");

		for (n = 0; n<4; n++)
		{
			//  printf("%i",mn1[n]);
		}

		//  printf("\n");
		//  printf("mn2 to: \n");

		for (n = 0; n<4; n++)
		{
			//  printf("%i",mn2[n]);
		}
		//  printf("\n");

		for (i = 0; i<4; i++)
		{
			kon3[3 - i] = (mn1[i] + mn2[i]) % 2;
			//printf("%i",kon3[3-i]);
		}

		//  printf("\n");
		//   printf("\n");

		// mnozenie[12+i]=(a[8+i]*b[4+i]+a[12+i]*b[12+i]);
	}

	int operacyjna[16];

	for (i = 0; i<4; i++)
	{
		dodawanie[0 + i] = kon3[i];
	}
	for (i = 0; i<4; i++)
	{
		dodawanie[4 + i] = kon2[i];
	}
	for (i = 0; i<4; i++)
	{
		dodawanie[8 + i] = kon1[i];
	}
	for (i = 0; i<4; i++)
	{
		dodawanie[12 + i] = kon0[i];
	}


	printf("Wynik mnozenia to: ");

	for (m = 0; m<16; m++)
	{
		operacyjna[m] = dodawanie[15 - m];
		printf("%i", operacyjna[m]);
	}

	printf("\n");

	//-------------------------------------------------------------------------------------------------------------------------------------//


	//int kp[16]={1,0,1,1,0,0,1,0,1,1,1,1,0,1,1,0},k1[16],dod1[4]={0,0,0,1},SBoxEk[4];
	int kp[16], k1[16], dod1[4] = { 0,0,0,1 }, SBoxEk[4];

	for (i = 0; i<16; i++)
	{
		kp[i] = b[i];
	}

	//12 13 14 15
	zaszlo0 = 0;



	for (i = 0; i<16; i++)
	{

		if ((kp[12] == SBoxE[i][0]) && (kp[13] == SBoxE[i][1]) && (kp[14] == SBoxE[i][2]) && (kp[15] == SBoxE[i][3]) && zaszlo0 == 0)
		{
			zaszlo0 = 1;

			for (m = 0; m<4; m++)
			{
				SBoxEk[m] = SBoxD[i][m];
			}
		}
	}

	for (i = 0; i<4; i++)
	{
		k1[i] = (kp[i] + SBoxEk[i] + dod1[i]) % 2;
		// printf("%i",k1[i]);
	}
	// printf("\n");

	//8 9 10 11

	for (i = 0; i<4; i++)
	{
		k1[8 + i] = (kp[8 + i] + k1[i]) % 2;
		//printf("%i",k1[i+8]);
	}
	// printf("\n");

	for (i = 0; i<4; i++)
	{
		k1[4 + i] = (kp[4 + i] + k1[8 + i]) % 2;
		// printf("%i",k1[i]);
	}
	//printf("\n");

	for (i = 0; i<4; i++)
	{
		k1[i + 12] = (kp[12 + i] + k1[4 + i]) % 2;
		//printf("%i",k1[i]);
	}
	// printf("\n");
	printf("Klucz 1 to: ");

	for (m = 0; m<16; m++)
	{
		printf("%i", k1[m]);
	}
	printf("\n");


	//---------------------------------------------------

	zaszlo0 = 0;

	int k2[16];

	dod1[0] = 0;
	dod1[1] = 0;
	dod1[2] = 1;
	dod1[3] = 0;

	for (i = 0; i<16; i++)
	{

		if ((k1[12] == SBoxE[i][0]) && (k1[13] == SBoxE[i][1]) && (k1[14] == SBoxE[i][2]) && (k1[15] == SBoxE[i][3]) && zaszlo0 == 0)
		{
			zaszlo0 = 1;

			for (m = 0; m<4; m++)
			{
				SBoxEk[m] = SBoxD[i][m];
			}
		}
	}

	for (i = 0; i<4; i++)
	{
		k2[i] = (k1[i] + SBoxEk[i] + dod1[i]) % 2;
	}

	//8 9 10 11

	for (i = 0; i<4; i++)
	{
		k2[8 + i] = (k1[8 + i] + k2[i]) % 2;
	}

	for (i = 0; i<4; i++)
	{
		k2[4 + i] = (k1[4 + i] + k2[8 + i]) % 2;
	}

	for (i = 0; i<4; i++)
	{
		k2[i + 12] = (k1[12 + i] + k2[4 + i]) % 2;
	}

	printf("Klucz 2 to: ");

	for (m = 0; m<16; m++)
	{
		printf("%i", k2[m]);
	}
	printf("\n");

	//-------------------------------------------------------------------------------------------------------------------------------------//


	for (i = 0; i<16; i++)
	{
		operacyjna[i] = (operacyjna[i] + k1[i]) % 2;
	}

	printf("Dodanie klucza 1: ");


	for (i = 0; i<16; i++)
	{
		printf("%i", operacyjna[i]);
	}

	//-------------------------------------------------------------------------------------------------------------------------------------//

	zaszlo0 = 0;
	zaszlo1 = 0;
	zaszlo2 = 0;
	zaszlo3 = 0;

	for (i = 0; i<16; i++)
	{
		if ((operacyjna[0] == SBoxE[i][0]) && (operacyjna[1] == SBoxE[i][1]) && (operacyjna[2] == SBoxE[i][2]) && (operacyjna[3] == SBoxE[i][3]) && zaszlo0 == 0)
		{
			zaszlo0 = 1;


			for (m = 0; m<4; m++)
			{
				operacyjna[m] = SBoxD[i][m];
			}
		}
		if ((operacyjna[4] == SBoxE[i][0]) && (operacyjna[5] == SBoxE[i][1]) && (operacyjna[6] == SBoxE[i][2]) && (operacyjna[7] == SBoxE[i][3]) && zaszlo1 == 0)
		{
			zaszlo1 = 1;

			for (m = 0; m<4; m++)
			{
				operacyjna[m + 4] = SBoxD[i][m];
			}
		}
		if ((operacyjna[8] == SBoxE[i][0]) && (operacyjna[9] == SBoxE[i][1]) && (operacyjna[10] == SBoxE[i][2]) && (operacyjna[11] == SBoxE[i][3]) && zaszlo2 == 0)
		{
			zaszlo2 = 1;

			for (m = 0; m<4; m++)
			{
				operacyjna[m + 8] = SBoxD[i][m];
			}
		}
		if ((operacyjna[12] == SBoxE[i][0]) && (operacyjna[13] == SBoxE[i][1]) && (operacyjna[14] == SBoxE[i][2]) && (operacyjna[15] == SBoxE[i][3]) && zaszlo3 == 0)
		{
			zaszlo3 = 1;

			for (m = 0; m<4; m++)
			{
				operacyjna[m + 12] = SBoxD[i][m];
			}
		}
	}



	printf("\n");

	printf("Drugi raz SBox: ");


	for (m = 0; m<16; m++)
	{
		printf("%i", operacyjna[m]);
	}

	printf("\n");

	//-------------------------------------------------------------------------------------------------------------------------------------//


	for (m = 0; m<4; m++)
	{
		tymczas[0 + m] = operacyjna[8 + m];
		operacyjna[8 + m] = operacyjna[12 + m];
		operacyjna[12 + m] = tymczas[0 + m];
	}

	printf("Druga operacja ZK: ");


	for (m = 0; m<16; m++)
	{
		printf("%i", operacyjna[m]);
	}

	printf("\n");

	//-------------------------------------------------------------------------------------------------------------------------------------//

	for (i = 0; i<16; i++)
	{
		operacyjna[i] = (operacyjna[i] + k2[i]) % 2;
	}

	printf("Ostateczny szyfrogram to: ");


	for (i = 0; i<16; i++)
	{
		printf("%i", operacyjna[i]);
	}

	//-------------------------------------------------------------------------------------------------------------------------------------//


	int po[4], po2[4], po3[4], zaszE = 0, zaszD = 0, dod[4];

	printf("\n");

	printf("Wpisz dwie czterobitowe liczby: ");


	for (i = 0; i<4; i++)
	{
		scanf("%i", &po[i]);
	}

	for (i = 0; i<4; i++)
	{
		scanf("%i", &po2[i]);
	}

	for (n = 0; n<4; n++)
	{
		po3[3 - n] = (int)mnoz(po, po2, n);
	}

	for (m = 0; m<4; m++)
	{
		printf("%i", po3[m]);
	}

	printf("\n");


	for (m = 0; m<4; m++)
	{
		scanf("%i", &po3[m]);
		dod[m] = po3[m];
	}

	for (i = 0; i<16; i++)
	{
		if ((po3[0] == SBoxE[i][0]) && (po3[1] == SBoxE[i][1]) && (po3[2] == SBoxE[i][2]) && (po3[3] == SBoxE[i][3]) && zaszE == 0)
		{
			zaszE = 1;

			for (m = 0; m<4; m++)
			{
				po3[m] = SBoxD[i][m];
			}
		}
	}

	printf("\n");

	printf("SboxE: ");

	printf("\n");

	for (m = 0; m<4; m++)
	{
		printf("%i", po3[m]);
	}

	for (i = 0; i<16; i++)
	{
		if ((dod[0] == SBoxD[i][0]) && (dod[1] == SBoxD[i][1]) && (dod[2] == SBoxD[i][2]) && (dod[3] == SBoxD[i][3]) && zaszD == 0)
		{
			zaszD = 1;

			for (m = 0; m<4; m++)
			{
				dod[m] = SBoxE[i][m];
			}
		}
	}

	printf("\n");

	printf("SboxD: ");

	printf("\n");

	for (m = 0; m<4; m++)
	{
		printf("%i", dod[m]);
	}


	return 0;
}
