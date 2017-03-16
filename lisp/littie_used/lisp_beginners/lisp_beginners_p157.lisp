#!/usr/bin/clisp


(defun subst1 (new old tree)
	(cond 	((eql tree old) new)
		((atom tree) tree)
		(t (cons (subst new old (car tree))
			 (subst new old (cdr tree)))) ))


(setq temp '(a b (b ba ) nil a ))
(print "temp is  ")(print temp)
(print "after subst nil to kk ")(print (subst1 'kk nil temp) )
