(defun sigma (x)
	(if (< x 1)
		0
		(+ (* x x) (sigma (- x 1)) ) 
	)
)

(format t "~A=~A~%" '3 (sigma 3) )