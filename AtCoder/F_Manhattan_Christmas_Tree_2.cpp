You are given an integer n.



We write the integers from 1 to n in a sequence from left to right. Then, alternately apply the following two operations until only one integer remains, starting with operation 1:



Operation 1: Starting from the left, delete every second number.

Operation 2: Starting from the right, delete every second number.

Return the last remaining integer.



 



Example 1:



Input: n = 8



Output: 3



Explanation:



Write [1, 2, 3, 4, 5, 6, 7, 8] in a sequence.

Starting from the left, we delete every second number: [1, 2, 3, 4, 5, 6, 7, 8]. The remaining integers are [1, 3, 5, 7].

Starting from the right, we delete every second number: [1, 3, 5, 7]. The remaining integers are [3, 7].

Starting from the left, we delete every second number: [3, 7]. The remaining integer is [3].©leetcode





the idea i developed for this one is that at each stage we know this is formign an arp and the states of that ao are changn



initially the starter =a = 1 commond difference d = 1 and the ast element l = n and at every stap the common diference increases by doubel multiplier and either the first element remains same or the last remains the same based on which operation it ws typ of 1 or 2 , tis is logarithmic compleity and from one state we can derive other step, also at any step we can find the number of eements in this ap aith a d and l so when this number of elements becomes 1 we stop implement this in this template



class Solution {

public:

    long long lastInteger(long long n) {

        

    }

};©leetcode