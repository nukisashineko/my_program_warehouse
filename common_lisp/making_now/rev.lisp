(defun rev (x)
	(if (null (cdr x))
		(cons (car x) () )
		(append (rev (cdr x)) (cons (car x) ()) ) 
	)
)

(format t "~A=~A~%" '(1 2 3 4 5) (rev '(1 2 3 4 5) ) )