(do '(i 0 (+ i 1))
	((> i 10) 'done)
	(if (mod i 2)
		(format t "~A," i)
		null
	)	
)