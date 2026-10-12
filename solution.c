#include <stdio.h>

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    // Simple array approach for smaller constraints
    int segments[1005];  // x-1 segments between stations
    
    // Initialize all segments with k seats
    for (int i = 0; i < x - 1; i++) {
        segments[i] = k;
    }
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        int start_seg = u - 1;
        int end_seg = v - 2;
        
        if (start_seg > end_seg) {
            printf("N\n");
            continue;
        }
        
        // Check if all segments have enough seats
        int can_fulfill = 1;
        for (int j = start_seg; j <= end_seg; j++) {
            if (segments[j] < n) {
                can_fulfill = 0;
                break;
            }
        }
        
        if (can_fulfill) {
            printf("T\n");
            // Subtract seats from all segments
            for (int j = start_seg; j <= end_seg; j++) {
                segments[j] -= n;
            }
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}