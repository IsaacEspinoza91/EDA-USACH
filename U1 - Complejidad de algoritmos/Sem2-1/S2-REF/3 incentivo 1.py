

def algo(A):
    n = len(A)
    aux1 = n/2
    for i in range(0,n):
        acum = 0
        for u in range(0,n):
            if A[i]==A[u]:
                acum = acum + 1
        if acum > aux1:
            return A[i]
    return -1
    


lista = [1,2,2,2,1,2]

print(f"el valor de mayoria del array es {algo(lista)}")