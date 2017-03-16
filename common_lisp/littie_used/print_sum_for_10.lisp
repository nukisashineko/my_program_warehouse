(do ((i 0 (+ i 1))(sum 0 (+ sum i))) ((> i 11) 'done)
	(format (> i 10) "~A," sum)
)
