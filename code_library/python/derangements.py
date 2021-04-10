from math import exp, factorial
from decimal import Decimal


def derangement(n, m):
    """
    number of ways to assign n people to m seats subject to the following condition:
    a seat can allocate at most one people and no people numbered x can be assigned to the seat numbered x
    the people are numbered from 1 to n and seats are numbered from 1 to m
    if m=n, then it is the standard derangement problem

    :param n: number of people
    :param m: number of seats
    :return:  number of ways to assign n seats from m seats to n people satisfying the condition above
    """

    if n > m:
        return 0

    x, y = 1, m - n
    for k in range(2, n + 1):
        z = (m - n) * y + (k - 1) * (x + y)
        x, y = y, z

    return x if n == 0 else y


def derangement_probability(n):
    """
    probability that if a random permutation from 1 to n is chosen, it is a derangement
    limit of ratio of derangement to permutation as n approaches infinity is 1 / e
    """
    if n > 20:
        return exp(-1)

    x = derangement(n, n)
    y = factorial(n)
    return float(Decimal(x) / Decimal(y))


def main():
    assert derangement(0, 0) == 1
    assert derangement(1, 1) == 0
    assert derangement(2, 2) == 1
    assert derangement(3, 3) == 2
    assert derangement(4, 4) == 9
    assert derangement(4, 3) == 0
    assert derangement(4, 10) == 3333
    assert derangement(20, 20) == 895014631192902121
    assert derangement(50, 60) == 995388150220927603258765357437017485681332235328576602372114257773098037151
    
    data = [
        (0, 1),
        (1, 0),
        (2, 0.5),
        (5, 0.36666666666666664),
        (10, 0.3678794642857143),
        (15, 0.3678794411713972),
        (20, 0.36787944117144233),
        (500, 0.36787944117144233),
    ]
    
    for n, expected_result in data:
        assert abs(derangement_probability(n) - expected_result) < 1e-9


if __name__ == '__main__':
    main()
