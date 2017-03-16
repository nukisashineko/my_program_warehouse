#!/usr/bin/clisp
(defun count-anywhere(x y)
	(cond ((eql x y) 1)
		((atom y) 0)
		(t (+	(count-anywhere x (first y))
			(count-anywhere x (rest y))))))
(print (count-anywhere 'a '(a ((a) b )a)))
