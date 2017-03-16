(defun sum (x)
	(if (null x)
		0
		(+ (car x) (sum (cdr x)) ) 
	)
)

(format t "~A=~A~%" '(1 2 3 4 5) (sum '(1 2 3 4 5) ) )