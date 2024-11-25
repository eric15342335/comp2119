def quick_sort(A, p, r):
    """QuickSort function to sort the array A[p..r]."""
    if p < r:
        print(f"QuickSort called on: {A[p:r+1]}")
        q = partition(A, p, r)
        print(f"Pivot placed at index {q}, array: {A}")
        quick_sort(A, p, q)       # Sort the left partition
        quick_sort(A, q + 1, r)   # Sort the right partition


def partition(A, p, r):
    """Partition function to rearrange the array A[p..r]."""
    # pivot: second largest element in A[p..r]
    v = A[r - 1]
    print(f"Partitioning with pivot {v} in: {A[p:r+1]}")
    i = p - 1
    j = r + 1

    while True:
        # Move j left until an element <= pivot is found
        while True:
            j -= 1
            if A[j] <= v:
                break

        # Move i right until an element >= pivot is found
        while True:
            i += 1
            if A[i] >= v:
                break

        if i < j:
            print(f"Swapping {A[i]} and {A[j]} at indices {i} and {j}")
            A[i], A[j] = A[j], A[i]  # Swap A[i] and A[j]
        else:
            print(f"Partition complete. Returning index {j}")
            return j


# Example usage:
if __name__ == "__main__":
    A = [1,2,3,4,5]  # Array with all elements equal
    print(f"Original array: {A}")
    quick_sort(A, 0, len(A) - 1)
    print(f"Sorted array: {A}")