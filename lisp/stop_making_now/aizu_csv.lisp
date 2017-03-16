(defvar mean-end 0)
;文字列をスペースによって分けて返す
(defun split-string-by-space (string)
       (loop
         for i = 0 then (1+ j)
         as j = (position #\Space string :start i)
         collect (subseq  string i j)
         while j))
;cvsファイルを一度の処理に必要な分だけ読み込む
(defun one-read-cvs (file)
       (let ((counter (read-from-string (read-line file))))
            (loop repeat counter
                  for line-string = (split-string-by-space (read-line file))
                  collect (mapcar #'read-from-string line-string))
            )
       )
