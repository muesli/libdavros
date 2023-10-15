def binarySearch(arr, l, r, x):
    while l <= r:
        mid = l + (r - l) // 2
        if arr[mid] == x:
            return mid
        elif arr[mid] < x:
            l = mid + 1
        else:
            r = mid - 1
    return -1

if __name__ == '__main__':
    arr = list(map(int, input("Enter a sorted array (space-separated): ").split()))
    x = int(input("Enter the element to search for: "))
    result = binarySearch(arr, 0, len(arr) - 1, x)
    if result != -1:
        print("Element is present at index", result)
    else:
        print("Element is not present in the array")
