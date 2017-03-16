
(defun my_max(x)
	(if (null (cdr x))
		(car x)
		(progn
			(let( (local_max (my_max (cdr x))) )
				(if (< local_max (car x) )
					(car x)
					local_max
				)
			)
		)
	)
)

(format t "~%max=~A~%" (my_max '(125 2 5 6 7 65 4978 6 2) ) )