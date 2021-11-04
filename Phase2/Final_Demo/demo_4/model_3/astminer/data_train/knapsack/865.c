



void knapsack(int n, float weight[], float profit[], float capacity)
{
   float x[20] , tp = 0; 
   int i, j, u; 
   u = capacity; 

   for (i = 0; i < n; i++)
      x[i] = 0.0;
   for (i = 0; i < n; i++)
   {
      if (weight[i] > u)
        break;

      else
      {
         x[i] = 1.0;
         tp = tp + profit[i];
         u = u - weight[i]; 
      }
   }
 
   if (i < n)
      x[i] = u / weight[i];

   tp = tp + (x[i] * profit[i]); 

   printf("\nThe vector is:- \n");
      for (i = 0; i < n; i++)
      printf("%f\t", x[i]); 

   printf("\nMaximum profit is:- %f\n", tp);

}

