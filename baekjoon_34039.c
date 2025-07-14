#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100001
#define MAX_SONGS 200001

int main()
{
    int commandCount, songCount;
    scanf("%d %d", &songCount, &commandCount);

    int songs[MAX_SONGS];
    int count[MAX_LEN] = {0}; // 각 곡 길이별 개수

    // 초기 곡 입력
    for (int i = 0; i < songCount; i++)
    {
        scanf("%d", &songs[i]);
        count[songs[i]]++;
    }

    for (int cmdNum = 0; cmdNum < commandCount; cmdNum++)
    {
        int cmd;
        scanf("%d", &cmd);

        if (cmd == 1)
        {
            int i, j;
            scanf("%d %d", &i, &j);
            i--;

            if (i >= 0 && i < songCount && j >= 0 && j < MAX_LEN)
            {
                int oldLen = songs[i];
                if (oldLen >= 0 && oldLen < MAX_LEN)
                {
                    count[oldLen]--;
                }
                count[j]++;
                songs[i] = j;
            }
        }
        else if (cmd == 2)
        {
            int T;
            scanf("%d", &T);

            int totalSongs = 0;
            for (int i = 1; i < MAX_LEN && T > 0; i++)
            {
                if (count[i] == 0)
                    continue;

                int canPlay = T / i;
                int playCount = (count[i] < canPlay) ? count[i] : canPlay;

                totalSongs += playCount;
                T -= playCount * i;
            }

            printf("%d\n", totalSongs);
        }
        else if (cmd == 3)
        {
            int j;
            scanf("%d", &j);
            if (j >= 0 && j < MAX_LEN && songCount < MAX_SONGS)
            {
                songs[songCount++] = j;
                count[j]++;
            }
        }
    }
    return 0;
}
