

def prime_still(n)
prime=[2,3]
 5.upto(n) do|c|
  flag=true
  prime.each{|p| flag=false if c%p==0}
  if flag
   prime[-1].upto(Math::sqrt(c)){|k|flag=false if c%k==0}
   prime<<c
  end
 end
 return prime
end

p prime_still(10**10)
