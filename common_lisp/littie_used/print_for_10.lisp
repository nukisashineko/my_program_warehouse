(do '(i 0 (+ i 1))
	((> i 10) 'done)
	(format t "~A," i)
)