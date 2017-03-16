#!/usr/bin/clisp
(defun last1 (x)
	(cond ((null x))
		(t (last2 x)) ))
(defun last2 (x)
	(cond	((null (cdr x)) x)
		(t (last2 (cdr x))) ))
(defun nconc1 (x y)
	(cond	((null x) y) 
		(t (rplacd (last x) y) x ) ))



