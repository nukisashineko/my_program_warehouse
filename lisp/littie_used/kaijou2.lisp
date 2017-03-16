#!/usr/bin/clisp


	(dotimes (foo 10)
		(let ((temp nil))
			(dotimes (baz foo)
				(push (1+ baz ) temp))
			(print (apply #'* temp))))
