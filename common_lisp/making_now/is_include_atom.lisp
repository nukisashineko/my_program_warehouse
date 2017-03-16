
(defun is_include_atom (x y)
(format t "~A=~A~%" x y )

)

(is_include_atom 'a ('b 'c 'd 'e))
(format t "~A=~A~%" '(1 (2 3 1 5) ) (is_include_atom 'a ('b 'c 'd 'a)) )