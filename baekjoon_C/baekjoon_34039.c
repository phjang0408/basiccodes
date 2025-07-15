#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100001 // 곡 길이의 최대값 (1부터 100,000)
#define MAX_SONGS 200001 // 곡의 최대 개수 (초기 200,000 + 추가될 수 있는 곡)

// 세그먼트 트리를 위한 구조체
typedef struct {
    long long count; // 해당 구간의 총 곡 개수
    long long total_length; // 해당 구간의 총 곡 길이 합
} Node;

Node tree[4 * MAX_LEN]; // 세그먼트 트리는 보통 배열 크기의 4배 필요
int songs[MAX_SONGS];    // 각 인덱스에 어떤 길이의 곡이 저장되어 있는지 기록

// 세그먼트 트리 초기화 함수
// node_idx: 현재 노드의 인덱스, start: 구간 시작, end: 구간 끝
void build(int node_idx, int start, int end) {
    if (start == end) {
        tree[node_idx].count = 0;
        tree[node_idx].total_length = 0;
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node_idx, start, mid);
    build(2 * node_idx + 1, mid + 1, end);
    tree[node_idx].count = tree[2 * node_idx].count + tree[2 * node_idx + 1].count;
    tree[node_idx].total_length = tree[2 * node_idx].total_length + tree[2 * node_idx + 1].total_length;
}

// 세그먼트 트리 업데이트 함수
// node_idx: 현재 노드의 인덱스, start: 구간 시작, end: 구간 끝
// target_idx: 업데이트할 곡 길이, diff_count: 개수 변화량 (+1 또는 -1)
void update(int node_idx, int start, int end, int target_idx, int diff_count) {
    if (start == end) {
        tree[node_idx].count += diff_count;
        tree[node_idx].total_length += (long long)diff_count * target_idx; // 길이 변화 반영
        return;
    }
    int mid = (start + end) / 2;
    if (target_idx <= mid) {
        update(2 * node_idx, start, mid, target_idx, diff_count);
    } else {
        update(2 * node_idx + 1, mid + 1, end, target_idx, diff_count);
    }
    tree[node_idx].count = tree[2 * node_idx].count + tree[2 * node_idx + 1].count;
    tree[node_idx].total_length = tree[2 * node_idx].total_length + tree[2 * node_idx + 1].total_length;
}

// 주어진 시간 T 내에 재생 가능한 최대 곡 수를 찾는 함수
// node_idx: 현재 노드의 인덱스, start: 구간 시작, end: 구간 끝, T: 남은 시간
int query_max_songs(int node_idx, int start, int end, long long T) {
    if (T < 0) return 0; // 남은 시간이 없으면 0곡
    if (start == end) { // 리프 노드에 도달
        // 현재 곡 길이 (start)로 재생 가능한 곡 수 계산
        long long can_play = T / start;
        return (int)((tree[node_idx].count < can_play) ? tree[node_idx].count : can_play);
    }

    int mid = (start + end) / 2;
    int total_songs = 0;

    // 왼쪽 자식 노드의 모든 곡을 재생할 수 있는 경우
    if (tree[2 * node_idx].total_length <= T) {
        total_songs += tree[2 * node_idx].count; // 왼쪽 자식 노드의 모든 곡 추가
        total_songs += query_max_songs(2 * node_idx + 1, mid + 1, end, T - tree[2 * node_idx].total_length); // 남은 시간으로 오른쪽 탐색
    } else {
        // 왼쪽 자식 노드의 일부만 재생해야 하는 경우
        total_songs += query_max_songs(2 * node_idx, start, mid, T);
    }
    return total_songs;
}


int main() {
    // 입출력 속도 향상
    setvbuf(stdin, NULL, _IOFBF, 1<<20); // 1MB 버퍼
    setvbuf(stdout, NULL, _IOFBF, 1<<20); // 1MB 버퍼
    // `setvbuf`는 `stdio.h`에 선언되어 있습니다.
    // `stdlib.h`는 필요 없을 수 있지만, 백준에서는 습관적으로 넣기도 합니다.

    int commandCount;
    int songCount; // 현재 총 곡의 개수
    scanf("%d %d", &songCount, &commandCount);

    // 세그먼트 트리 빌드 (초기에는 모든 개수 0)
    build(1, 1, MAX_LEN - 1); // 곡 길이는 1부터 MAX_LEN-1 까지 (100,000)

    // 초기 곡 입력
    for (int i = 0; i < songCount; i++) {
        scanf("%d", &songs[i]);
        update(1, 1, MAX_LEN - 1, songs[i], 1); // 세그먼트 트리에 추가
    }

    for (int cmdNum = 0; cmdNum < commandCount; cmdNum++) {
        int cmd;
        scanf("%d", &cmd);

        if (cmd == 1) {
            int i, j; // i: (1-based) 변경할 곡의 인덱스, j: 새로운 길이
            scanf("%d %d", &i, &j);
            i--; // 0-based index

            // 유효성 검사
            if (i >= 0 && i < songCount) {
                int old_len = songs[i];
                // 세그먼트 트리에서 old_len 감소, j 증가
                update(1, 1, MAX_LEN - 1, old_len, -1); // 이전 길이의 곡 개수 1 감소
                update(1, 1, MAX_LEN - 1, j, 1);       // 새 길이의 곡 개수 1 증가
                songs[i] = j; // songs 배열 업데이트
            }
        } else if (cmd == 2) {
            long long T; // 총 재생 시간 (long long으로 받아야 함, 최대 2*10^14)
            scanf("%lld", &T);

            int result = query_max_songs(1, 1, MAX_LEN - 1, T);
            printf("%d\n", result);
        } else if (cmd == 3) {
            int j; // 추가할 곡의 길이
            scanf("%d", &j);

            // songs 배열에 추가 (현재 총 곡의 개수 songCount 사용)
            if (songCount < MAX_SONGS) { // 배열 오버플로우 방지
                songs[songCount] = j;
                update(1, 1, MAX_LEN - 1, j, 1); // 세그먼트 트리에 추가
                songCount++; // 총 곡 개수 증가
            }
        }
    }

    return 0;
}