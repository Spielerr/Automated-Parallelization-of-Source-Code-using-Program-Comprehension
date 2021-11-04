

void greedyknap(int n, float wt[], float value[], float capacity) {
   float x[20], tp = 0;
   int i, j, u;
   u = capacity;

   for (i = 0; i < n; i++)
      x[i] = 0.0;

   for (i = 0; i < n; i++) {
      if (wt[i] > u)
         break;
      else {
         x[i] = 1.0;
         tp = tp + value[i];
         u = u - wt[i];
      }
   }

   if (i < n)
      x[i] = u / wt[i];

   tp = tp + (x[i] * value[i]);

   printf("\nThe result vector is: ");
   for (i = 0; i < n; i++)
      printf("%f\t", x[i]);

   printf("\nMaximum value is: %f", tp);

}

