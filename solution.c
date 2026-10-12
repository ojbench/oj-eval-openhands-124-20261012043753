#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000005

int tree[MAX_SIZE * 4];
int lazy[MAX_SIZE * 4];
int n;

void push(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node];
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(int node, int start, int end, int l, int r, int val) {
    push(node, start, end);
    if (start > r || end < l) return;
    
    if (start >= l && end <= r) {
        lazy[node] += val;
        push(node, start, end);
        return;
    }
    
    int mid = (start + end) / 2;
    update_range(2 * node, start, mid, l, r, val);
    update_range(2 * node + 1, mid + 1, end, l, r, val);
    
    push(2 * node, start, mid);
    push(2 * node + 1, mid + 1, end);
    if (tree[2 * node] < tree[2 * node + 1]) {
        tree[node] = tree[2 * node];
    } else {
        tree[node] = tree[2 * node + 1];
    }
}

int query_range(int node, int start, int end, int l, int r) {
    if (start > r || end < l) return 2147483647; // INT_MAX
    
    push(node, start, end);
    if (start >= l && end <= r) {
        return tree[node];
    }
    
    int mid = (start + end) / 2;
    int left_min = query_range(2 * node, start, mid, l, r);
    int right_min = query_range(2 * node + 1, mid + 1, end, l, r);
    return left_min < right_min ? left_min : right_min;
}

void init_tree(int node, int start, int end, int initial_value) {
    if (start == end) {
        tree[node] = initial_value;
    } else {
        int mid = (start + end) / 2;
        init_tree(2 * node, start, mid, initial_value);
        init_tree(2 * node + 1, mid + 1, end, initial_value);
        tree[node] = initial_value;
    }
}

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    n = x - 1;
    init_tree(1, 0, n - 1, k);
    
    for (int i = 0; i < p; i++) {
        int u, v, n_seats;
        scanf("%d %d %d", &u, &v, &n_seats);
        
        int start_seg = u - 1;
        int end_seg = v - 2;
        
        if (start_seg > end_seg) {
            printf("N\n");
            continue;
        }
        
        int min_available = query_range(1, 0, n - 1, start_seg, end_seg);
        
        if (min_available >= n_seats) {
            printf("T\n");
            update_range(1, 0, n - 1, start_seg, end_seg, -n_seats);
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}