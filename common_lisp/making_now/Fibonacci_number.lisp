(defun Fibonacci_number (x)
	(if (< x 2)
		x
		(+ (Fibonacci_number (- x 1)) (Fibonacci_number (- x 2))) 
	)
)

(format t "~A=~A~%" '6 (Fibonacci_number 6) )