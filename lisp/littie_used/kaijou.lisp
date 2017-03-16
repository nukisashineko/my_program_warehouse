#!/usr/bin/clisp

;なんて言うか斬新・・・
(defun fact-cps (n &optional (cout #'identity))
	(if (zerop n)
			(funcall cout 1)
			(fact-cps (1- n) #'(lambda (x) (funcall cout (* n x))))
	)
)

(defun fact-cps (n cont)
  (if (zerop n)
	      (funcall cont 1)
				    (fact-cps (1- n) #'(lambda (x) (funcall cont (* n x))))))

(print (fact-cps 10 #'identity))

 (dotimes (x 15) (fact-cps x #'(lambda (x) (print x))))
