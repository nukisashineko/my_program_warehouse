#!/usr/bin/clisp

(defun copy (x)
	(cond	((atom x) x)
		(t (cons (car x) (cdr x))) ))


