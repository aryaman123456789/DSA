class Solution:
    def calculate(self, s: str) -> int:
        stack = []
        curr = 0
        last = '+'
        for i, char in enumerate(s):
            if char.isdigit():
                curr = curr * 10 + int(char)
            if char in '+-*/' or i == len(s) - 1:
                if last == '+':
                    stack.append(curr)
                elif last == '-':
                    stack.append(-curr)
                elif last == '*':
                    stack.append(stack.pop() * curr)
                elif last == '/':
                    stack.append(int(stack.pop() / curr))
                curr = 0
                last = char
        return sum(stack)