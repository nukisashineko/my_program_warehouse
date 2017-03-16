#!/usr/bin/clisp

(defun is-prime (x)
       (loop for y from 2 below x  never  (= (mod x y) 0)))
(defun prime-count-below (n)
       (loop for x from 2 below n  count (is-prime x) ))
(print (prime-count-below 1000))
