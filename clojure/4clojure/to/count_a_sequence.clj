((fn [a ] 
  (if (= a ()) 
   0 
   (loop [list a count 1] 
    (if (= (rest list) ()) 
     count 
     (recur (rest list) (inc count)) )))) 
 [1 23 45 3])

