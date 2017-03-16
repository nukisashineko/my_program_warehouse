#!/usr/bin/clisp
(declaim (optimize (debug 3) (safety 3)
                   (speed 0) (space 0) (compilation-speed 0)))

(defun mappend (fn &rest lsts)
  "maps elements in list and finally appends all resulted lists."
  (apply #'append (apply #'mapcar fn lsts)))

(defun one-of (set)
"Pick one element of set, and make a list of it."
	(list (random-elt set)))
(defun random-elt (choices)
"Choose an elemant from a list at random"
	(elt choices (random (length choices))))

;-------------------------------------------------
(defun sentence () (append (noun-phrase) (verb-phrase)))
(defun noun-phrase () (append (Article) (Noun)))
(defun verb-phrase () (append (Verb) (noun-phrase)))
(defun Article () (one-of '(the a)))
(defun Noun () (one-of '(man ball woman table)))
(defun Verb () (one-of '(hit took saw liked)))

(print "正攻法による解法（区構構造文法）" )
;(dotimes (i 10)	(print (sentence)))

;----------------------------------------------------
(defun Adj*()
	(if (= (random 2) 0)
		nil
		(append (Adj) (Adj*))))
(defun PP* ()
	(if (random-elt '(t nil))
		nil
		(append (PP) (PP*))))

(defun noun-phrase () (append (Article) (Adj*) (Noun) (PP*)))
(defun PP () (append (Prep) (noun-phrase)))
(defun Adj () (one-of '(big little blue green adiabatic)))
(defun Prep () (one-of '(to  in with by on)))

(print "正攻法による解法（区構構造文法）2" )
;(dotimes (i 10) (print (sentence)))
;-----------------------------------------------------------

(defparameter *simple-grammar*
	'((sentence -> (noun-phrase verb-phrase))
	  (noun-phrase -> (Article Noun))
	  (verb-phrase -> (Verb noun-phrase))
	  (Article -> the a)
	  (Noun -> man ball woman table)
	  (Verb -> hit took saw liked))
"A grammar for a trivial subset of English.")

(defvar *grammar* *simple-grammar*
"The grammar used by  generate. Initally, this is *simple-grammar* , but we can switch to other grammars.")

(defun rule-lhs (rule)
	"The left-hand side of a rule."
	(first rule))
(defun rule-rhs (rule)
	"The right-hand side of a rule."
	(rest (rest rule)))
(defun rewrites (category)
	"Return a list of the possible rewritess for this category"
	(rule-rhs (assoc category *grammar*)))

(defun generate (phrase)
"Generate a random sentence or phrase"
(if (listp phrase) 
	(mappend #'generate phrase)
	(let ((choices (rewrites phrase)))
		(if (null choices)
			(list phrase)
			(generate (random-elt choices)))
	)))
(print "ルールベースによる解法" )
(dotimes (i 10)	(print (generate 'sentence)))


;-----------------------------------------------------------

(defparameter *big-grammar*
	'((sentence -> (noun-phrase verb-phrase))
	  (noun-phrase -> (Article Adj* Noun PP*) (Name) (Pronoun))
	  (verb-phrase -> (Verb noun-phrase PP*))
	  (PP* -> () (PP PP*))
	  (Adj* -> () (Adj Adj*))
	  (PP -> () (Prep noun-phrase))
	  (Adj ->  big little blue green adiabatic)
	  (Article -> the a)
	  (Name -> Pat Kim Lee Terry Robin)
	  (Noun -> man ball woman table)
	  (Verb -> hit took saw liked)
	  (Pronoun -> he she it these those that))) 

(setf *grammar* *big-grammar*)
(print "ルールベースによる解法 2" )
(dotimes (i 10)
	(print (generate 'sentence)))

;-------------------------------------------------------------

(defun generate-tree (phrase)
"Generate a random sentence or phrase, with a complete tree"
(cond	((listp phrase) (mapcar #'generate-tree phrase))
	((rewrites phrase) 
		(cons  phrase (generate-tree (random-elt (rewrites phrase)))))
	(t (list phrase))))

(print "同じデータを使用した複数のプログラム開発　" )
;(dotimes (i 10) (print (generate-tree 'sentence)))


;---------------------------------------------------
(setf *grammar* *simple-grammar*)

(defun generate-all (phrase)
"Generate a list of all posible expansions of this phrase."
(cond	((null phrase) nil)
	((listp phrase)
		(combine-all	(generate-all (first phrase))
				(generate-all (rest phrase))))
	((rewrites phrase) 
		(mappend #'generate-all (rewrites phrase)))
	(t (list phrase))))
(defun combine-all (xlist ylist)
"Return a list of lists formed by appending a y to an x.
 E.g., (combine-all '((a)(b)) '((1)(2)) ) -> ((A 1)(B 1)(A 2)(B 2))"
	(mappend #'(lambda (y)
		(mapcar #'(lambda (x) (append x y)) xlist))
		ylist))
(print "同じデータを使用した複数のプログラム開発 2" )
(print (generate-all 'Article))
(print (generate-all 'Noun))
(print (length (generate-all 'sentence)))


