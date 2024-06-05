p = 4168994591;
q = 2585929961;
n = 10780728020113840951;
phi = 10780728013358916400;
e = 4075877470489037497;
d = 4220016392015130233;



modexp(a, b, n) = {
    local(d, bin); 
    d = 1; 
    bin = binary(b); 
    for (i = 1, length(bin), 
        d = (d*d)%n; 
        if (bin[i] == 1, 
            d = (d*a)%n; 
        ); 
    ); 
    return(d); 
}



encript(x) = modexp(x,e,n);
decript(y) = modexp(y,d,n);