class Solution:
    def asteroidCollision(self, asteroids: List[int]) -> List[int]:
        stack = []
        for asteroid in asteroids:
            while asteroid < 0 and stack and stack[-1] > 0:
                if abs(asteroid) == stack[-1]:
                    stack.pop()
                    asteroid = 0
                elif abs(asteroid) > stack[-1]:
                    stack.pop()
                elif abs(asteroid) < stack[-1]:
                    asteroid = 0
            if asteroid != 0:
                stack.append(asteroid)
        return stack