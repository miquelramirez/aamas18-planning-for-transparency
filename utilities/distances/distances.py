import math

def kld(P,Q):

    assert len(P) == len(Q)

    sum_dkl = 0

    for i in range(0, len(P)):

        if(P[i] != 0):
            term_dkl = P[i]*math.log(P[i]/Q[i],2)
        else :
            term_dkl = 0

        sum_dkl += term_dkl

    return sum_dkl



