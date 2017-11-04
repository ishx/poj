#include <stdio.h>

#define PI 3.14
int main()
{
  float tempX = 0.00,tempY = 0.00;
  int year[100] = {0};
  int i = 0,iMax = 0;
  scanf("%d",&iMax);
  while(i++ < iMax)
  {
    scanf("%f%f",&tempX,&tempY);
    year[i] = (int) (PI*(tempX*tempX+tempY*tempY)+99.99)/100;
  }
  for(i = 1; i<= iMax;i++)
  printf("Property %d: This property will begin eroding in year %d.\n"
  ,i,year[i]);
  printf("END OF OUTPUT.\n");
  return 1;
}