+#include <cstdio>
#include <cstdlib>

void merge_sort(int dataset[], int start_idx, int end_idx);
void merge(int dataset[], int start_idx, int middle_idx, int end_idx);

void merge_sort(int dataset[], int start_idx, int end_idx) {
    if(1 > end_idx - start_idx) return;

    int middle_idx = 0;
    middle_idx = (start_idx + end_idx) / 2;

    merge_sort(dataset, start_idx, middle_idx);
    merge_sort(dataset, middle_idx+1, end_idx);

    merge(dataset, start_idx, middle_idx, end_idx);
}

void merge(int dataset[], int start_idx, int middle_idx, int end_idx) {
    int i = 0;
    int left = start_idx;
    int right = middle_idx+1;
    int dest_idx = 0;

    int *destination = (int *)malloc(sizeof(int)*(end_idx - start_idx +1));

    while(left <= middle_idx && right <= end_idx) {
        if(dataset[left] < dataset[right]) {
            destination[dest_idx] = dataset[left++];
        } else {
            destination[dest_idx] = dataset[right++];
        }
        ++dest_idx;
    }

    while(left <= middle_idx)
        destination[dest_idx++] = dataset[left++];

    while(right <= end_idx)
        destination[dest_idx++] = dataset[right++];

    dest_idx = 0;

    for(i = start_idx; end_idx >= i; ++i) {
        dataset[i] = destination[dest_idx++];
    }

    free(destination);
}

int main(void) {
    int dataset[] = {334, 6, 4, 2, 3, 1, 5, 117, 12, 34};
    int Length = sizeof dataset / sizeof dataset[0];
    int i = 0;

    merge_sort(dataset, 0, Length-1);

    for(i = 0; Length > i; ++i) {
        printf("%d ", dataset[i]);
    }

    printf("\n");

    return 0;
}
