##http://www1.doshisha.ac.jp/~mjin/R/33/33.html
#R と時系列データ
class(lh)
lh

start(UKgas)
end(UKgas)
frequency(UKgas)
UKgas
window(UKgas,c(1975,2),c(1979,3))

ts.plot(lh)
ts.plot(UKgas)
#凡例をマウスで指定する。
ts.plot(ldeaths,mdeaths,fdeaths,gpars=list(xlab="year",ylab='death count',lty=c(1:3),col=c(1:3)))
legend(locator(1),c('全体','男性','女性'),lty=c(1:3),col = c(1:3))


temp<- ts(1:120,start= c(1995,6),frequency=12)
class(temp)
temp


ldeaths 
lag(ldeaths,k=5)
class(ldeaths)
union(ldeaths,mdeaths)
intersect(ldeaths,mdeaths)

plot(diff(UKgas))
plot(diff(UKgas,differences=2))
plot(UKgas)

#自己共鳴
acf(UKgas)
frequency(UKgas)
par(mai=rep(0.2,4),mfrow=c(4,1))
for(i in 1:4) plot(diff(log(UKgas),lag=i))

#相互関数
dev.off()
ccf(mdeaths,fdeaths)

par(mfrow=c(2,2))
spec.pgram(UKgas)
spec.pgram(UKgas,spans=c(3,3))
spec.pgram(ldeaths)
spec.pgram(ldeaths,spans=c(3,3))

