#!/usr/bin/clisp
(defun reverse1 (x)
	(prog	(result)
		(setq result nil)
	loop (cond ((null x ) (return result))
		   (t	(setq result (cons (car x) result))
			(setq x (cdr x))
			(go loop) ))))
(print (reverse1 '(a b c d)))
