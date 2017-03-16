(ns try-memorize.core)

(defn foo
  "I don't do a whole lot."
  [x]
  (println x "Hello, World!"))
(identity [:a])


(defn fib [n]
  (condp = n
    0 1
    1 1
    (+ (fib (dec n)) (fib (- n 2)))))

(time (fib 30))
(def m-fib 
  (memoize (fn [n]
             (condp = n
               0 1
               1 1
               (+ (m-fib (dec n)) (m-fib (- n 2)))))))

(time (m-fib 30 ))

(let [m-fib (atom nil )]
  (reset! m-fib
    (memoize (fn [n]
               (condp = n
                 0 1
                 1 1
                 (+ (@m-fib (dec n)) (@m-fib (- n 2)))))))
   (time (@m-fib 30 ))
  )

(let [m-fib (atom nil)]
  (reset! m-fib 
    (memoize (fn [n]
               (condp = n 
                 0 1
                 1 1
                 (+ (@m-fib (dec n) )(@m-fib (- n 2)))))))
  (time (@m-fib  30 ))
  )
