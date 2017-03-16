(defun prod (x)
	(if (null x)
		1
		(* (car x) (prod (cdr x)) ) 
	)
)

(format t "~A=~A~%" '(1 2 3 4 5) (prod '(1 2 3 4 5) ) )