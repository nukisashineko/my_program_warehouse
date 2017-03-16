#!/usr/bin/clisp
(defun assoc1 (x y)
	(cond 	((null y) nil)
		((eql x (caar y) y)
		(t (assoc1 x (cdr y))) )))

(defun rassoc1 (x y)
	(cond 	((null y) nil)
		((eql x (cadr y) y)
		(t (assoc1 x (cdr y))) )))

	
