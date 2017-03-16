#!/usr/bin/clisp
(setq phonelist 
	'((reiko "037125648")
	 (kimiko "424861416")
	 (junko "034327601"))
	 (fukumi "425920293")
	 (akemi "035833198"))
(print (assoc 'kimiko phonelist))

(defun update-phone (p x y)
	(cond ((null p) nil)
		((eq (caar p) x)
		 (cons (cons x y) (cdr p)) )
		(t (cons (car p) (update-phone (cdr p) x y)) )))
(print (phonelist) (update-phone 'kimiko "neko"))

 (defun update-phone1 (p x y)
	(rplacd (assoc x p) y)
	y )

(defun update-phone2 (p friend number)
	(prog (f.n)
	(setq f.n (assoc friend p))
	(return
		(cond	(f.n (rplacd f.n number) p)
			(t (cons (cons friend number) p)) ))))


(defun remove-1 (x y)
	(cond 	((null y) nil)
		((eql x (car y)) (cdr y))
		(t (cons  (car y) (remove-1 x (cdr y)))) ))

(defun removeall (x y)
	(cond 	((null y) nil)
		((eql x (car y)) (removeall x (cdr y)))
		(t (cons  (car y) (removeall x (cdr y)))
) ))
(defun delete-1 (x y) 
	(setq y (cons 'dummy y))
	(del2 x y nil)
	(cdr y))
(defun del2 (x y z)
	(cond	((null y) nil)
		((eq (car y) x) (rplacd z (cdr y)))
		(t (del2 x (cdr y) y)) ))

(defun del2 (x y)
	(cond	((null (cdr y)) nil)
		((eq (cadr y) x)
			(rplacd y (cddr y)))
		(t (del2 x (cddr y) (cdr y))) ))

(defun update-phone3 (p friend number)
	(prog (f.n)
	(setq f.n (assoc friend p))
	(return
		(cond	((eq number 'sukinanoni) (delete-1 f.n p))
			(f.n (rplacd f.n number) p)
			(t (cons (cons friend number) p)) ))))


(defun nreverse (x) (setq x (nrev2 x nil)))
(defun nrev2 (x r)
	(cond	((null x) r)
		(t 	(prog1	(nrev2 (cdr x) x)
				(rplacd x r) )) ))



