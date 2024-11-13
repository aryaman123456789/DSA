class ListNode:
    def __init__(self, next = None, val = 0):
        self.next = next
        self.val = val

def deleteNode(head, n):
    dummy = ListNode(0)
    dummy.next = head
    left, right = dummy, dummy
    for _ in range(n):
        right = right.next
    while right and right.next:
        left = left.next
        right = right.next
    left.next = left.next.next
    return dummy.next

node1 = ListNode(1)
node2 = ListNode(2)
node3 = ListNode(3)
node4 = ListNode(4)
node5 = ListNode(5)
node1.next = node2
node2.next = node3
node3.next = node4
node4.next = node5

new_head = deleteNode(node1, 2)

while new_head:
    print(new_head.val, end = " -> ")
    new_head = new_head.next