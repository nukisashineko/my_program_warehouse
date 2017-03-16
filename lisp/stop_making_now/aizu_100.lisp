#!/usr/bin/clisp

(defvar mean-end 0)
(defvar filename "aizu_100.csv")
(defvar counter 0)
(defvar file (open  filename :direction :input ))
;
(defun split-string-by-space (string)
       (loop
         for i = 0 then (1+ j)
         as j = (position #\Space string :start i)
         collect (subseq  string i j)
         while j))
;cvsファイルを一度の処理に必要な分だけ読み込む
(defun one-read-cvs (file)
       (let ((counter (read-from-string (read-line file))))
            (loop repeat counter
                  for line-string = (split-string-by-space (read-line file))
                  collect (mapcar #'read-from-string line-string))
            )
       )
;main
(when  (open filename :direction :probe)
       (with-open-file (f filename :direction :input )
                       (loop for cvs = (one-read-cvs f)
                             while cvs
                             do (print cvs)
                             )))
;作りかけてやめた何か
(let ((cvs-lists '((1001 2000 520) (1002 1800 450) (1003 1600 625) (1001 200 1220)) ))
     (let ((list-sum ((1001 10000) (1002 000))))
          (if (member (car cvs-list) list-sum :key #'car)
              (change (+ (cdr it) ( )))
              (funcall #'(lambda (a b c) (push `(a ,(* b c)) list-sum)) cvs-list)
              (subst-if #'(lambda (temp) (eql () 1001) ))))

     )
;これが分化して合計を出す関数
(let ((cvs-lists '((1001 2000 520) (1002 1800 450) (1003 1600 625) (1001 200 1220)) ))
     (mapcar #'(lambda (cvs) (let ((a (car cvs)) (b (cadr cvs)) (c (caddr cvs))) `(,a ,(* b c)))) cvs-lists))
;何がしたいのか
;ループさせてsumで拾う
;doneに終わった社員を書く
;;;;;;;;;


(defparameter done)
(defparameter cvs)
(if (find number done)
    ;find
    (exit)
    ;not find
    (push number sum))


(member number lst :key #'car)


(loop for x in lst
      until x
      sum (cdr x))


(defun temp (lst done)
       (let((number (caar lst))
            (sum 0))
         (when (null lst) done)
         (if (find number done)
             ;done
             (temp (cdr lst) done )
             ;not find
             (temp (cdr lst) (cons done (sum-member number lst ))))))


(defun sum-member (number lst)
       (loop for x in (member number lst :key #'car)
             until x
             sum (cdr x)))



(let ((lst  '((1001 2000 ) (1002 1800 ) (1003 1600) (1001 200)))
      (done nil))
     (loop  for l on lst 
            as number = (caar l)
            unless (find  number done)
            collet (progn
                      (push number done)
                      (loop for x = l then (cdr y)
                            as y = (member number x )
                            while y
                            collect (car y) )
                      )))




(let ((lst)(done nil))
     (unless (find number done)
              body
     )
     (push number done) )



(let ((lst  '((1001 2000 ) (1002 1800 ) (1003 1600) (1001 200)))
      (done nil))
     (loop  for l on lst 
            as number = (caar l)
            if (find number (cdr l) :key #'car) collect (car l) ))





(let ((l  '((1001 2000 ) (1002 1800 ) (1003 1600) (1001 200)))
      (done nil))
     (loop  for x = l then (cdr y)
            as y = (member 1001 x :key #'car)
            while y collect (car y)))




(let ((lst  '((1001 2000 ) (1002 1800 ) (1003 1600) (1001 200)))
      (done nil))
     (if (find number done)
         (push number done) 
         (push 
           (cons number
           (loop  for l on lst 
                  as number = (caar l)
                  if (find number (car l) :key #'car) sum
                  (cdr 
                    (loop  for x = l then (cdr y)
                           as y = (member number x :key #'car)
                           while y collect (car y)))))
           done))
;わけわかめすぎる、諦めたわ・・・
