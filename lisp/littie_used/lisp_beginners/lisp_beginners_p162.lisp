#!/usr/bin/clisp
(defun sublis1 (alist tree)
	(let ((pair (assoc tree alist)))
		(cond	(pair (cdr pair))
			((atom tree) tree)
			(t (let ((a (sublis1 alist (car tree))
				 (b (sublis1 alist (cdr tree)))
				(cond	((and (eql a (car tree))
					    (eql b (cdr tree)) )
					 tree)
					(t (cons a d)) ))))))))
	
