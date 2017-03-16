#!/usr/bin/clisp

(defun count-atom (exp)
	(cond ((null exp) 0)
		((atom exp) 1)
		(t (+	(count-atom (first exp))
			(count-atom (rest exp))))))
(defun count-atom-all(exp &optional (if-null 1))
	(cond ((null exp) if-null)
		((atom exp) 1)
		(t (+	(count-atom-all (first exp) 1)
			(count-atom-all (rest exp) 0)))))

(defvar x '(a () c  ) )
(print x)
(print (count-atom x ))
(print (count-atom-all x 1))
