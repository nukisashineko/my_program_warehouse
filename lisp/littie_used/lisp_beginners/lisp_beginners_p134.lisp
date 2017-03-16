#!/usr/bin/clisp
(defun member1 (x y)
	(cond	((null y) nil)
		(eql x (car y)
		(t (member1 (x (cdr y))) ))))

