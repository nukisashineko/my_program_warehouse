#!/usr/bin/clisp


(defun atom-count (x)
	(cond	((null x) 0)
		((atom x) 1)
		((and (null (car x)) (consp (cdr x)))
			(1+ (atom-count (cdr x))))
		(t (+	(atom-count (car x))
			(atom-count (cdr x))))
	)
)

(print (atom-count '((nil a) nil b)))
