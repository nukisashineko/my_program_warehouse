#http://stat.biopapyrus.net/ggplot/geom-point.html
#平均分散プロット
#データの特徴を捉えるとき、平均分散プロットもよく用いられる。横軸を平均値、縦軸を分散としたプロットである。

# データを読み込んで、group 1 と group 2 に分ける
data <- read.table("http://stat.biopapyrus.net/data/count.txt", header = TRUE)
g1 <- sweep(data[, 1:3], 2, mean(colSums(data[, 1:3])) / colSums(data[, 1:3]), "*")
g2 <- sweep(data[, 4:6], 2, mean(colSums(data[, 4:6])) / colSums(data[, 4:6]), "*")

# group 1 の平均と分散を計算
g1.m <- log2(apply(g1, 1, mean))
g1.v <- log2(apply(g1, 1, var))

# group 2 の平均と分散を計算
g2.m <- log2(apply(g2, 1, mean))
g2.v <- log2(apply(g2, 1, var))

# ggplot 用データフレームを作成
df <- data.frame(
  MEAN = c(g1.m, g2.m),
  VAR = c(g1.v, g2.v)
)

# ggplot の描画レやーを作成
g <- ggplot(
  df,
  aes(                 # 散布図の x, y 座標を指定
    x = MEAN,
    y = VAR
  )
)
g <- g + geom_point(     # 点の属性を指定
  color = "darkgrey",
  size = 2,
  pch = 20,
  na.rm = TRUE
)
g <- g + geom_abline(    # y = x の直線を図に描き入れる
  intercept = 0,
  slope = 1,
  lwd = 1.5,
  col = "orange"
)
g <- g + xlab("MEAN")
g <- g + ylab("VARIANCE")
g <- g + ggtitle("MEAN-VARIANCE plot")

plot(g)

