#include <stdio.h>
#include <math.h>

int main(void)
{
    int T;
    int x1, y1, r1;
    int x2, y2, r2;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        scanf("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);
        double distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); // 서로 거리
        double substract = r1 > r2 ? r1 - r2 : r2 - r1;            // 반지름 거리 차

        if (distance == 0 && substract == 0)
        {
            printf("-1\n");
        }
        else if (distance == r1 + r2 || distance == substract)
        {
            printf("1\n");
        }
        else if (distance < r1 + r2 && distance > substract)
        {
            printf("2\n");
        }
        else
        {
            printf("0\n");
        }
    }
}