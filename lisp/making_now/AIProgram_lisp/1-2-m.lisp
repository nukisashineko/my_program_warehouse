(defun power (x y)
	"power raises x to the nth power. N must be an integer >=0.
	This executes in log n time, because of the check for even n."
	(cond ((= y 0) 1)
		((evenp y) (expt (power x (/ y 2)) 2))
		(t (* x (power x (1- y))))))
(print (power 3 2))
