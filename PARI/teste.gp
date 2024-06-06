p = prime(random(2^8));
q = prime(random(2^8));
n = p*q;
phi = (p-1)*(q-1);
e = random(eulerphi(n));
while (gcd(e, eulerphi(n)) != 1, e = random(eulerphi(n)))
d = bezout(e, eulerphi(n))[1];

#printf(p);
#printf(q);
#printf(n);
#printf(phi);
#printf(e);
#printf(d);


x = 9999;
y = (x^e)%n;
x2 = (y^d)%n;
printf(x2);