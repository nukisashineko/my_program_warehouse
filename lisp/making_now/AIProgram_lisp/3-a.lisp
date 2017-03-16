#!/usr/bin/clisp
; apropos 
(apropos 'string)
; describe 
(describe 'make-string)
;inspect
;documentation 

;error
;cerror
;assert
;check-type
;break

;with-open-file 
(with-open-file (s "temp.txt" :output :direction))
;format
(let ((num '(10 20 30 40 50)))
	(format t "~&~{~r~^ plus ~} is  ~@r"
		 num (apply #'+ num)))
;typep
(typep 123 'number)
;subtypep
(subtypep 'fixnum 'number)
;intersection r s
;union r s
;set-difference r s ->xor
;member 'd r
;(subsetp s r)
;adjoin 'b s 


;rem 11 5





(defun sqr (x)
"Multiply x by itserf"
(asser (numberp x) (x))
(* x x))


; time 
;compile


(defun adder (c)
"return a function that adds c to its argument."
#'(lambda (x) (+ x c)))

(mapcar (adder 3) '(1 3 10))
(mapcar (adder 10) '(1 3 10))

(defun bank-account (balance)
"Open abank acccount starting with the giben balance."
#'(lambda (action amount)
	(case action 
		(deposit (setf balance (+ balance amount)))
		(withdraw (setf balance (- balance amount))))))

(let (	(my (bank-account))
	(your (bank-account)))
	(funcall my 'withdraw 75.00)
	(funcall your 'deposit 75.00)
	(funcall my 'withdraw 75.00)
	(funcall your 'deposit 75.00))


;value a b c
;multiple-ablue-bind (a b c)


; &body
; &aux -> not used



;-1 
(defun length-a (a)
	(labels f (c) (#'lambda (x) (incf c)))
	(if (null a) 0)
		(let ((cc (f 1)))
		(reduce cc a)))
