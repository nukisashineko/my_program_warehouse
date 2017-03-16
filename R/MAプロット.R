#http://stat.biopapyrus.net/ggplot/geom-point.html
#MA プロット
#ggplot を利用して MA プロットを描く例。MA プロットは 2 つの実験群のデータそれぞれの平均を計算し、両者の差（M 値）を縦軸に、両者の平均（A 値）を横軸にプロットした図である。（詳細）。
#利用するサンプルデータは RNA-seq の擬似データである。全部で 4000 個の遺伝子発現量を含み、最初の 800 個と後の 3200 個が性質が異なるので、ここでは色を塗り分ける。

library(ggplot2)

# データを読み込んで、正規化する（合計値を 100 万にする）
data <- read.table("http://stat.biopapyrus.net/data/count.txt", header = TRUE)
cpm <- sweep(data, 2, 1e+06 / colSums(data))

# group 1 と group 2 の平均を計算
mean.group1 <- log2(rowMeans(cpm[, 1:3]))
mean.group2 <- log2(rowMeans(cpm[, 4:6]))

# group 1 を DEG とラベルし、group 2 を non-DEG とラベルする
tag <- c(rep("DEG", 800), rep("non-DEG", 3200))

# ggplot 用のデータフレームを作成
df <- data.frame(
  m.values = mean.group2 - mean.group1,
  a.values = (mean.group2 + mean.group1) / 2,
  gene = tag
)

# 描画レイヤーを描く
g <- ggplot(                 # データのセットアップ
  df,                      # データの入っているデータフレーム
  aes(
    x = a.values,        # df の a.values 列を x 座標とする
    y = m.values         # df の m.values 列を y 座標とする
  ) 
)
g <- g + geom_point(         # プロット属性を指定
  aes(colour = gene),      # DEG か non-DEG かで色を塗り分ける
  size = 2,
  pch = 20,
  na.rm = TRUE             # 非数値をプロットしない
)
g <- g + xlab("A-value")     # 横軸ラベル
g <- g + ylab("M-value")     # 縦軸ラベル
g <- g + ggtitle("M-A plot") # グラフタイトル

plot(g)

