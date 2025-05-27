#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    vector<int> data;
    int n;

    // Function to build the segment tree
    void buildTree(int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            buildTree(2 * node, start, mid);
            buildTree(2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    // Function to update the segment tree
    void updateTree(int node, int start, int end, int idx, int value) {
        if (start == end) {
            data[idx] = value;
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                updateTree(2 * node, start, mid, idx, value);
            } else {
                updateTree(2 * node + 1, mid + 1, end, idx, value);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    // Function to query the sum in a range
    int queryTreeSum(int node, int start, int end, int L, int R) {
        if (R < start || end < L) {
            return 0;
        }
        if (L <= start && end <= R) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int leftSum = queryTreeSum(2 * node, start, mid, L, R);
        int rightSum = queryTreeSum(2 * node + 1, mid + 1, end, L, R);
        return leftSum + rightSum;
    }

public:
    SegmentTree(const vector<int>& input) {
        data = input;
        n = data.size();
        tree.resize(4 * n);
        buildTree(1, 0, n - 1);
    }

    void update(int idx, int value) {
        updateTree(1, 0, n - 1, idx, value);
    }

    int query(int L, int R) {
        return queryTreeSum(1, 0, n - 1, L, R);
    }
};

int main() {
    vector<int> data ;
    data.push_back(3);
    data.push_back(7);
    data.push_back(1);
    data.push_back(6);
    SegmentTree segTree(data);

    // Query the sum of the range [1, 3]
    cout << "Sum of range [1, 3]: " << segTree.query(1, 3) << endl;

    // Update index 1 to value 10
    segTree.update(1, 10);
    segTree.update(2,28);
    // Query the sum of the range [1, 3] after the update
    cout << "Sum of range [1, 3] after update: " << segTree.query(1, 3) << endl;

    return 0;
}
