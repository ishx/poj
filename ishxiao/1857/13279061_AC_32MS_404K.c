#include <stdio.h>
int b,l,n;    //b the max weight the bridge can afford, l the bridge length, n cars to transport
double r[1001];  // 记录DP算法，到当前位置最优解的最短时间
int w[1001];  // 记录各车的重量
int s[1001];  // 记录各车的速度

void SolveDP()
{
    l *= 60;    //因为最后求分钟，速度是小时每千米,先*60一样的
    r[0] = 0;
    
    int speed, weight;
    double time_best, time_now;
    
    for (int i = 1; i <= n; i++) {  //从1开始记录下标,r[0] = 0作为哨兵,便于程序统一处理
        
        scanf("%d%d", &(w[i]), &(s[i]));
        
        //第一种分组尝试,i单独一组
        weight = w[i];
        speed = s[i];
        time_best = r[i - 1] + (double)l / (double)speed;
        
        //尝试其它所有可能的包含i的分组
        for (int j = i - 1; j && (weight += w[j]) <= b; j-- ){
            if (s[j] < speed)
                speed = s[j];

            time_now = r[j - 1] + (double)l / (double)speed;
            if (time_now < time_best)
                time_best = time_now; 

        }
        r[i] = time_best;
    }
    printf("%.1f\n", r[n]);
}

int main(int argc, char *argv[])
{
    while (1) {
        
        scanf("%d%d%d",&b, &l, &n);
        
        if (b == 0 && l ==0 && n ==0)
            break;

        SolveDP();
    }
    return 0;
}