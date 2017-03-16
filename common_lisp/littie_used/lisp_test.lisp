

(defun qadd (queue element)
  (if (consp queue)
    (let ((newcons (cons (car queue) (cdr queue))))
      (setf (car queue) element)
      (setf (cdr queue) newcons))
    nil))

(defun my_set (queue element)
  (if (consp queue)
    (let ((newcons (cons (car queue) (cdr queue))))
      (setf (car queue) element)
    )
    nil))

(setf myqueue '(a))
(format t "~A~%" myqueue)
(qadd myqueue '(b bb bbb bbbb))
(format t "~A~%" myqueue)
(my_set myqueue 'c)
(format t "~A~%" myqueue)
(qadd myqueue 'd)
(format t "~A~%" myqueue)