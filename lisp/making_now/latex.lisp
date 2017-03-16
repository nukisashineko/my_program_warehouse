(length "hoge")
(concatenate  'string  "neko" "kawaii")

(defun document (&rest body) (concatenate 'string "\\begin{document}\n" (concatenate 'string body)  "\n\\end{document}\n" ))
(defun document2 (&rest body) (concatenate 'string body))
(document2 "koredeiikana" "nekoda")

(mapcan #'(lambda (x) (concatenate 'string x)) ("neko" "inu") )



