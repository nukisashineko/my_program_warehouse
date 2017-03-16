#!/usr/bin/clisp


(let((foo nil)) (dotimes (var 5 var) (push var foo)) (print foo) )

(let ((foo nil)
  (print foo))

