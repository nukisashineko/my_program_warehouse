#!/usr/bin/clisp
;
(defun mappend (fn &rest lsts)
  "maps elements in list and finally appends all resulted lists."
  (apply #'append (apply #'mapcar fn lsts)))

(defun cross-product (fn xlist ylist)
"Return a list of all (fn x y) value."
(mappend #'(lambda (x) (mapcar #'(lambda (y) (funcall fn x y)) ylist)) xlist ))

;(combine-all (xlist ylist) #'append xlist ylist)

(print (cross-product #'+ '(1 2 3) '(10 20 30)))
(print (cross-product #'list '(a b c d e f g h) '(1 2 3 4 5 6 7 8)))
