(defun sigma (x)
	(if (< x 1)
		0
		(+ x (sigma (- x 1)) ) 
	)
)

(format t "~A=~A~%" '10 (sigma 10) )