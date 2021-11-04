







void selectionSort(int x[], int n);
// void troca(int v[], int i, int j);

// void troca(int v[], int i, int j){   
//   int aux;
//   aux = v[i];
//   v[i] = v[j];
//   v[j] = aux;
// }

void selectionSort(int x[], int n){
  int menor,pos;
  int i,k = 0;

  while (k < n){
    menor = INFINITO;
    for (i = k; i < n; i++)
      if (x[i] < menor){
        menor = x[i];
        pos = i;
      }
    troca(x,k,pos);
    k++;
  }
}

