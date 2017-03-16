
( (fn [l num](loop [list l n num] (if(= n 0) (first list) (recur (rest list) (dec n))))) [ 1 2 3 4] 2)

