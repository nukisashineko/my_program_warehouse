(defun leap_year (x)
	(if (= (mod x 400) 0)
		t
		(if (= (mod x 100) 0)
			nil
			(if (= (mod x 4) 0)
				t
				nil				
			)
		)
	)
	
)
(format t "leap_year 2100 = ~A~%"(leap_year 2100))
(format t "leap_year 2000 = ~A~%"(leap_year 2000))
(format t "leap_year 2400 = ~A~%"(leap_year 2004))
(format t "leap_year 2100 = ~A~%"(leap_year 2001))