data(Cars93, package="MASS")

coplot(Horsepoweer~MPG.city |Origin, data=Cars93)


barworld.series <- scan("http://lib.stat.cmu.edu/datasets/wseries",
                        skip =35,
                        nlines =23, 
                        what = list(year = integer(0),
                                    patten = character(0)) )
order(barworld.series$year)

#順番を取得
perm <- order(barworld.series$year)
#それでソートする
world.series <- list(year = barworld.series$year[perm],
                     patten = barworld.series$petten[perm])
#ソートされたことを確認
barworld.series

#レシピ2.9 名前・値の関連リストを作成する

#example
lst <- list(mid=0.5, right = 8.41, far.right = 0.977)
lst <- list()
lst['name'] <- 'value' 
lst <- list(far.left= 0.023, left = 0.159, mid = 0.500, right = 0.841, far.right=0.977) 
#↑=
lst <-list()
lst$far.left<-0.023
lst$left = 0.159
lst$mid = 0.500
lst$right = 0841
lst$far.right = 0.977

#↑=
values <- pnorm(-2:2)
names <- c('far.left','left','mid','right','far.right')
lst <- list()
lst[names] <- values

#list と atom の違い？
cat('The left limit is ',lst[['left']],'\n')
cat('The right limit is',lst[['right']],'\n')
for(nm in names(lst)) cat('The', nm ,'limit is',lst[[nm]],'\n')
for(nm in names(lst)) cat('The', nm ,'limit is',lst[[nm]],'\n') ##error リストだから

#レシピ、３.１　ベクトルをグループに分割する。
#groups <- split(x,f)
#groups <- unstack(data.frame(x,f))

library(MASS)
split(Cars93$MPG.city,Cars93$Origin)
g <- split(Cars93$MPG.city, Cars93$Origin)
median(g[[1]])
#各リストの要素に関数を適用する。
#lst <- lapply(lst,fun)
#s<-sapply(lst,fun) #同じ長さのみ可能


#レシピ3.5 データのグループにっ関数を適用する。
#tapply(x,f,fun)
#データの合計と平均の算出
pop <- c(2853114,90352, 171782, 94487, 102746, 106221,147779,76031,70834,72616, 74239,83048,67232,75386,63348,91452)
sum(pop)
mean(pop)
#フィルタをかけながら、合計と平均の算出を実行
country <- c('Cook','Kenosha','Kane','Kane','Lake(In)','Kendall','DuPage','Cook','Will','Cook','Cook','Lake(IN)','Cook','Cook','Cook','Lake')
tapply(pop,country,sum)
tapply(pop,country,mean)
#データのいみあいが全く可割ることに気がつく（例えば、地域によって、データがひとつしか無いとか・・・。）

#レシピ5.10確率を分位数に変換する。
#確率分布数は関数にqがつく
qnorm(0.05, mean=100, sd=15)
qnorm(0.025)
qnorm(0.975)
qnorm(c(0.025, 0.975))
#二項分布
#qbinom(p,size,prob)
#幾何分布
# qgeom(p, prob)
#ポアソン分布
#qpois(p, lambda)


#レシピ、5.11　密度関数をプロットする。
x <- seq(from = -3, to=+3, length.out=100)
plot(x,dnorm(x)) 

#other #いっぺんに４つ表示してしまいましょう
x<- seq(from = 0, to= 6, length.out = 100)
ylim <- c(0,0.6)
par(mfrow = c(2,2))
plot(x, dunif(x,min=2,max=4), main='Uniform',type='l',ylim=ylim)
plot(x, dnorm(x,mean=3,sd=1), main='Normal',type='l',ylim=ylim)
plot(x, dexp(x,rate=1/2), main='Exponential',type='l',ylim=ylim)
plot(x, dgamma(x,dgamma(x,shape=2,rate=1)), main='Gamma',type='l',ylim=ylim)
par(mfrow = c(1,1))

#網掛けをする。
#todo: 画面分割表示の修正かんすうを配置
x<-seq(from = -3, to=+3, length.out = 100)
y <- dnorm(x)
plot (x,y ,main='Standard Normal Distribution', type='l',ylab = 'Density',xlab="Quantile")
abline(h=0)
#多角形は1<=z<=2である密度曲線に従う
region.x <- x[1 <= x & x <= 2]
region.y <- y[1 <= x & x <= 2]
region.x <- c(region.x[1], region.x, tail(region.x,1)) #xの範囲は1<=x & x<=3
region.y <- c(0, region.y, 0)
#polygon はちょっと使用がわから無いけどこれで網掛けができる。
polygon(region.x, region.y, density =10)
polygon(region.x, region.y, density =10, col='red')

#検証足跡
#polygon(c(-1,c(0,1,2),3),c(0,c(0.1,0.2,0.3),0.2))
#polygon(c(-1,4),c(0,2))
#twwit 今,R勉強してるんだけど、polygonの仕様がよくわからん
#polygon(c(-1,4),c(0,2))これはわかる
#polygon(c(-1,c(0,1,2),3),c(0,c(0.1,0.2,0.3),0.2))　・・・。なんだこれ？？
#ああ、flattenして、多角形を書くと考えればいいのね。なる。
#やばい。いろつくのは、なんとなくかっこいい。

#ファ？なんでそのまま叩くだけで出てくるの？？？でーたせっとおもしろい。　
airquality

#棒グラフを作成する。
#レシピ、7.9　棒グラフを作成する。
#barplot(c(height_1,height_2,height_3,...))

heights <- tapply(airquality$Temp, airquality$Month, mean)
par(mfrow = c(1,2))
barplot(heights)
barplot(heights,
        main="Mean Temp. by  Month",
        names.arg = c('May','Jun',"Jul",'Aug','Sep'),
        ylab='Temp(deg. F)')
par(mfrow = c(1,1))

#7.10 棒グラフに信頼区間を追加する。

library(gplots)
barplot2(x,plot.ci =TRUE, ci.l=lower, ci.u=upper)

#レシピ、7.26 １ページに複数の図を表示する。
#par(mfrow = (c(N,M))
par(mfrow = c(2,2))
par(mfcol = c(2,1))

Quantile <- seq(from= 0 , to = 1 , length.out =30)
plot(Quantile, dbeta(Quantile, 2,4),type= 'l',mian='First')
plot(Quantile, dbeta(Quantile, 4,2),type= 'l',mian='Second')
plot(Quantile, dbeta(Quantile, 1,1),type= 'l',mian='Three')
plot(Quantile, dbeta(Quantile, 0.5,0.5),type= 'l',mian='Fourth')


#その他豆知識
class(Sys.Date())
#sample(set, n, replace =TRUE)
 # グラフィックスパラメータの値の一時退避と復帰
oldpar <- par(no.readonly = TRUE)
oldpar <- par(col=1, lty = 2)
par(oldpar)
#自分の関数内でparで設定するときは元のグラフィクスパラメータに戻すようにしておく
myfunc <- function () {
  oldpar<- par(no.readonly = TRUE);
  on.exit(par(oldpar))
  par(col=2,); plot(1:10)
}

mat <- matrix(c(1,0,2,2),2,2,byrow=TRUE)
mat
layout(mat)
plot(sin)
plot(cos)

split.screen(c(2,1))
split.screen(c(1,3), screen = 2)
screen(1);
plot(rnorm(10)) # 画面 1 にプロット 
screen(3); plot(rnorm(10), type="l") # 画面 3 にプロット 
screen(4); plot(rnorm(10), type="S") # 画面 4 にプロット 
screen(5); plot(rnorm(10), type="h") # 画面 5 にプロット

     
#全ての絵を消す。（図の分割はそのまま）
frame()
#全ての絵を消す。（分割を解除する）
close.screen(all=T) 




