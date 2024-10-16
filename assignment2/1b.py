def reorder(a, n):
    left = 0
    right = n - 1
    while left < right - 1:
        middle = (left + right) // 2
        print(left, middle, right)
        if a[left] < a[middle]:
            left = middle
        if a[middle] < a[right]:
            right = middle
    return right

uid = [7,1,2,3,4,5,6]
print(reorder(uid, len(uid)))
