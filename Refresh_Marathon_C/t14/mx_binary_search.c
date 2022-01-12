int mx_strcmp(const char *s1, const char *s2);
int mx_binary_search(char **arr, int size, const char*s, int *count) {
    int l = 0;
    int r = size - 1;
    int c = 0;
    while (l <= r) {
        c++;
        *count = c;
        int mid = l + (r - l) / 2;
        if (mx_strcmp(arr[mid], s) == 0) {
            return mid;
        }
        if (mx_strcmp(arr[mid], s) > 0) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    *count = 0;
    return -1;
}

