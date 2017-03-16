#!/usr/bin/clisp


(defun factorial (n)
	(if (= 0 n)
		1
		(* n (factorial (1- n))))
)
(print (factorial 5))
