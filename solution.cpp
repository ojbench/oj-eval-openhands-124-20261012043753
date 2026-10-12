#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class LazySegmentTree {
private:
    vector<int> tree;
    vector<int> lazy;
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
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    
    int query_range(int node, int start, int end, int l, int r) {
        if (start > r || end < l) return INT_MAX;
        
        push(node, start, end);
        if (start >= l && end <= r) {
            return tree[node];
        }
        
        int mid = (start + end) / 2;
        int left_min = query_range(2 * node, start, mid, l, r);
        int right_min = query_range(2 * node + 1, mid + 1, end, l, r);
        return min(left_min, right_min);
    }
    
public:
    LazySegmentTree(int size, int initial_value) : n(size) {
        tree.resize(4 * n, initial_value);
        lazy.resize(4 * n, 0);
    }
    
    void update_range(int l, int r, int val) {
        update_range(1, 0, n - 1, l, r, val);
    }
    
    int query_range(int l, int r) {
        return query_range(1, 0, n - 1, l, r);
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    // We have x-1 segments between stations
    LazySegmentTree st(x - 1, k);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Convert to 0-based indexing for segments
        int start_seg = u - 1;
        int end_seg = v - 2;  // v-1 station, so last segment is v-2
        
        if (start_seg > end_seg) {
            printf("N\n");
            continue;
        }
        
        // Check minimum available seats in the range
        int min_available = st.query_range(start_seg, end_seg);
        
        if (min_available >= n) {
            printf("T\n");
            // Update all segments in the range (subtract n seats)
            st.update_range(start_seg, end_seg, -n);
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}