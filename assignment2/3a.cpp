#include <vector>

#define MAX_VAL 10
class FreqStack {
    private:
        std::vector<int> stack;
        int freq[MAX_VAL] = {0};
        int maxFreq(void) {
            int max = 0;
            for (int i = 0; i < MAX_VAL; i++) {
                if (freq[i] > max) {
                    max = freq[i];
                }
            }
            return max;
        }
    public:
        FreqStack() {
            stack = std::vector<int>();
        }
        void push(int val) {
            stack.push_back(val); // O(1) operation
            freq[val]++;
        }
        int pop(void) {
            int _maxFreq = maxFreq();
            int i = stack.size() - 1;
            while (i > 0) {
                if (freq[stack[i]] == _maxFreq) {
                    freq[stack[i]]--;
                    break;
                }
                i--;
            }
            int _val = stack[i];
            stack.erase(stack.begin() + i); // O(n) operation
            return _val;
        }
};

#include <cstdio>
int main() {
    FreqStack freqStack = FreqStack();
    freqStack.push(5);
    freqStack.push(7);
    freqStack.push(5);
    freqStack.push(7);
    freqStack.push(4);
    freqStack.push(5);
    for (int i = 0; i < 4; i++) {
        printf("%d\n", freqStack.pop());
    }
    return 0;
}