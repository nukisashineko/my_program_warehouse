#!/usr/bin/clisp

(defun append (x y)
	(cond	((null x) y)
		(t (cons (car x) (append (cdr x) y))) ))

(print (append '(west south) '(west north) ))
