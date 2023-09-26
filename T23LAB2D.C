/* Dyakonov Nickolay, ND4, 31.10.2020 */
#include <stdio.h>
#include <string.h>

#define MAX 20
#define INFINITY 10000

int Adj[MAX][MAX],
  Was[MAX], 
  ///PathLen = 0, BestPath[MAX], Path[MAX],
  ///BestPathLen = 0, 
  From[MAX], From1[MAX],
  Len[MAX], Len1[MAX];

void LabInit( void )
{
  int i, k;

  for (i = 0; i < MAX; i++)
    for (k = 0; k < MAX; k++)
      Adj[i][k] = 0, Was[i] = 0, From[i] = -1, From1[i] = -1, Len[i] = INFINITY, Len1[i] = INFINITY;
}

void LabLoad( void )
{
  int a, b, i, len, n;
  char buf[100];
  FILE *F;

  if ((F = fopen("AV6LAB.txt", "r")) == NULL)
    return;
  while (fgets(buf, sizeof(buf) - 1, F) != NULL)
  {
    n = sscanf(buf, "%d%d%d", &a, &b, &len);
    if (n == 2)
      len = 1;
    if (n > 1)
      adj[a][b] = adj[b][a] = len;
  }  
}

void Display( int A, int B )
{
  int i;

  printf("%d ", A);
  for (i = 0; i < BestPathLen; i++)
    printf("%d ", BestPath[i]);
  printf("%d", B);
}

void Go( int A, int B )
{
  int i;

  if (Adj[A][B] == 1)
  {
    if (BestPathLen == 0 || PathLen < BestPathLen)
    {
      BestPathLen = PathLen;
      memcpy(BestPath, Path, sizeof(int) * PathLen);
    }
  }

  Was[A] = 1;

  for (i = 0; i < MAX; i++)
    if (i != A && i != B && Was[i] == 0 && Adj[A][i] != 0)
    {
      Was[i] = 1;
      Path[PathLen++] = i;
      Go(i, B);
      PathLen--;
      Was[i] = 0;
    }
}

void main( void )
{
  int a, b;

  printf("A: ");
  scanf("%d", &a);

  printf("B: ");
  scanf("%d", &b);

  LabInit();
  LabLoad();
  Go(a, b);
  Display(a, b);
  getchar();
  getchar();
}
