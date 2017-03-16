#!/usr/bin/clisp
(defun length (x)
	(do	((count 0 (1+ count))
		 (lst x (cdr lst))
		((null lst)) count)))
(
