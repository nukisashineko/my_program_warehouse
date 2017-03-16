#!/usr/bin/clisp



(defun cons-count (x)
	(cond	((atom x) 0)
		(t (+ 1 (cons-count (car x))
			(cons-count (cdr x))))
	)
)
(print (cons-count '(()())) )
