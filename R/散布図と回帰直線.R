#http://stat.biopapyrus.net/ggplot/geom-point.html
#散布図と回帰直線
#geom_point 関数を利用して散布図を描き、その上に geom_smooth 関数により回帰直線を書き加える。

library(ggplot2)

# 乱数を利用してサンプルデータを作成
x <- sort(runif(1000, 1, 10))
y <- rnorm(1000, 50, 10) * sort(runif(1000,1, 10))

# ggplot に代入するためのデータフレームを作成
df <- data.frame(x=x, y=y)

# 作成したデータフレームを確認
head(df)
##          x        y
## 1 1.017262 49.10280
## 2 1.020018 41.57822
## 3 1.021907 66.32804
## 4 1.037068 60.73542
## 5 1.050855 34.18668
## 6 1.085932 67.09626

# ggplot 描画レイヤーを準備
g <- ggplot(
  df,                       # ggplot 用データフレーム
  aes (
    x = x,                  # x 軸に df$x を指定
    y = y                   # y 軸に df$y を指定
  )
)
g <- g +  geom_point(
  shape = 20,               # プロットのタイプを指定
  size = 0.8,               # プロットのサイズを指定
  na.rm = TRUE              # 非数値を無視
)
g <- g + geom_smooth(       # 近似線
  method = "lm"             # 近似線は回帰法によって求める
)
g <- g + xlab("Label X")    # x 軸ラベル
g <- g + ylab("Label Y")    # y 軸ラベル
g <- g + ggtitle("ggplot2") # グラフタイトル

plot(g)

