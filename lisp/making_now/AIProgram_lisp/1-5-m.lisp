#!/usr/bin/clisp
(defun dot-product (x y)
	(apply #'+ (mapcar #'* x y)))
(print (dot-product '(10 20) '(3 4)))
