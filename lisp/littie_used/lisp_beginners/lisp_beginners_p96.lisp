#!/usr/bin/clisp

(defun reverse (x) (reverse2 x nil))

(defun reverse2 (x y) 
	(cond ((null x) y)
		(t (reverse2 (cdr x) (cons (car x) y))) ))


(setq temp '(a b c d))
(print (reverse  temp))


(defun length (x) (length2 x 0))
(defun length2 (x c)
	(cond	((null x) c)
		(t (length2 (cdr x) (1+ c))) ))

(print (length temp))

(defun factorial (n) (fact2 (n 1)))
(defun fact2 (n c)
	(cond	((= n 1) c)
		(t (fact2 ((1- n) (* n c))) )))
(print (factorial 10))
 
