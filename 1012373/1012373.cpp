#include <iostream>
#include <stdio.h>

using namespace std;

FILE *fr, *fw;
int **a, *b;

typedef struct
{
	int nhan;
	int sophantu;
} Dinh;

void NhapSoPhanTu(FILE *f, int &n);
void NhapMaTran(FILE *f, int **a, int n);
void Delete(int **a, int n);
int ThanhPhanLienThong(int **a, int n);
void Visit(int label, int *b, int i, int **a, int n);
void XuatCacThanhPhanLienThong(FILE *fw, int *b, int n, int nlabel);
void SapXep(Dinh *c, int n);

void main(int agrv, char *argc[])
{
	int n, nlabel;

	fr = fopen(argc[1], "rt");
	fw = fopen(argc[2], "wt");

	NhapSoPhanTu(fr, n);

	a = new int*[n];
	
	for (int i = 0; i<n; i++)
		a[i] = new int[n];

	NhapMaTran(fr, a, n);

	nlabel = ThanhPhanLienThong(a, n);

	fprintf(fw, "So Thanh Phan Lien Thong : %d\n", nlabel);
	XuatCacThanhPhanLienThong(fw, b, n, nlabel);

	delete []b;
	Delete(a, n);

	fclose(fr);
	fclose(fw);
}

void NhapSoPhanTu(FILE *f, int &n)
{
	fscanf(f, "%d", &n);
}

void NhapMaTran(FILE *f, int **a, int n)
{
	int i, j;

	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			fscanf(f, "%d", &a[i][j]);
}

void Delete(int **a, int n)
{
	for (int i = 0; i<n; i++)
		delete []a[i];

	delete []a;
}

int ThanhPhanLienThong(int **a, int n)
{
	int label = 0;
	int i;

	b = new int[n];

	for (i=0; i<n; i++)
		b[i] = 0;

	label = 0;

	for (i=0; i<n; i++)
		if (b[i] == 0)
		{
			label++;
			Visit(label, b, i, a, n);
		}

	return label;	
}

void Visit(int label, int *b, int i, int **a, int n)
{
	b[i] = label;

	for (int j=0; j<n; j++)
	{
		if ((b[j] == 0) && (a[i][j] != 0 || a[j][i] != 0))
			Visit(label, b, j, a, n);
	}
}

void XuatCacThanhPhanLienThong(FILE *fw, int *b, int n, int nlabel)
{
	int i, j;

	Dinh *dem = new Dinh[nlabel];

	for (i=1; i<=nlabel; i++)
	{
		dem[i-1].nhan = i;

		for (j=0; j<n; j++)
		{
			if (b[j] == i)
				dem[i-1].sophantu ++;
		}
	}

	SapXep(dem, nlabel);

	for (i=0; i<nlabel; i++)
	{
		for (j=0; j<n; j++)
		{
			if (b[j] == dem[i].nhan)
				fprintf(fw, "%d ", j);
		}

		fprintf(fw, "\n");
	}

	delete []dem;
}

void SapXep(Dinh *c, int n)
{
	int i, j;
	Dinh temp;

	for (i=0; i<n-1; i++)
		for (j=i+1; j<n; j++)
		{
			if (c[i].sophantu > c[j].sophantu)
			{
				temp = c[i];
				c[i] = c[j];
				c[j] = temp;
			}
		}
}