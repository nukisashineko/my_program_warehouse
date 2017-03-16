#!/usr/bin/clisp
(defun reverse1 (x)
	(prog	(result)
		(while	(x (return result)
			(setq result (cons (car x) result))
			(setq x (cdr x)) ))))
