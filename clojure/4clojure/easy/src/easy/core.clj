(ns easy.core)

; count 
((fn [a ] 
   (if (= a ()) 
     0 
     (loop [list a count 1] 
       (if (= (rest list) ()) 
         count 
         (recur (rest list) (inc count)) )))) 
                                              [1 23 45 3])

;nth element 
( (fn [l num](loop [list l n num] (if(= n 0) (first list) (recur (rest list) (dec n))))) [ 1 2 3 4] 2)


;count a sequce
#(reduce (fn [x y] (inc x) ) 0 %)

;Reverse a Sequence
#(reduce (fn [x y] (concat [y] x)) [] %)
;Sum It All Up
#(reduce (fn [x y] (+ x y) ) 0 %) 
;Find the odd numbers
#(filter odd? %)
;Fibonacci Sequence
#(take % ((fn fib-recur [a b] (cons a (lazy-seq (fib-recur b (+ a b) )))) 1 1))
;Palindrome Detector
(fn [x] 
  (if (string? x) 
    (= x (apply str (reverse x) )) 
    (= x (reverse x)) ))
;Flatten a Sequence
(fn flat [n]
  (let [[x & xs] n] 
    (cond 
          (empty? n) '()
          (coll? x) (concat (flat x) (flat xs))
          :else (cons x (flat xs)) ))) 
;get the gaps
#(apply str (clojure.string/split % #"[^A-Z]*"))
;compress a sequence
(fn [x] 
  (let [fv (map first (partition-by identity x))] 
    (if (string? x) 
      (apply str fv) 
      (apply list fv)))) 
;Pack a Sequence
#(partition-by identity %)
;Duplicate a Sequence
(fn [lat] (reduce concat (map #(take 2 (repeat %)) lat)))
;Replicate a Sequence
(fn [lat n] (reduce concat (map #(take n (repeat %)) lat)))
;Implement range
(fn [a b](take (- b a) (iterate inc a)))
;Local bindings
(fn [& n] (let [[x & xs] n] (if (empty? n) '() (reduce (fn [a b] (if (< a b) b a)) x xs))))
;Interleave Two Seqs
((fn my-ileave [a b] 
   (let [[x & xs] a [y & ys] b] 
     (if (some empty?  [xs ys]) 
       [x y] 
       (concat  [x y] (my-ileave xs ys))))) 
                                            [1 2 3] [:a :b :c])
;interpose a seq
(fn my-interpose [a b]
  (let [[x & xs] b] 
    (if (empty? xs) [x] (concat [x a] (my-interpose a xs)))))

;Drop Every Nth Item
((fn [lat n] (flatten (map #(if (= (count %) n) (drop-last %) %) (partition-all n lat)))) [1 2 3 4 5 6 7 8] 3)
((fn [lat n] (flatten (map #(if (= (count %) n) (drop-last %) %) (partition-all n lat)))) [1 2 3 4 5 6 7 8] 3)
(fn [lat n] (->> (partition-all n lat) (map #(if (= (count %) n) (drop-last %) %)) flatten) )

;Factorial Fun
#(apply * (range 1 (inc %)))
;Reverse Interleave
(fn [lat n](->> (partition-all n lat) (apply mapv vector )))
(fn [x lat ]
  ( let [ len (count lat)
         n (if (> len x)
             (->> (take-while (partial > len) (iterate #(+ len  %) x)) last )
             (->> (take-while (partial < 0) (iterate #(- len  %) x)) last ))  
         left (take n lat) 
         right (drop n lat)]
    (concat right left) ))

( (fn [x lat ] ( let [ len (count lat) n (->> (take-while (partial > len) (iterate #(+ len  %) x)) last )  left (take n lat) right (drop n lat)] (concat right left) )) -2 [1 2 3 4 5])
;blac box test
(fn [coll] 
  (let [base (empty coll)]
    (cond
      (= base {}) :map
      (= base #{}) :set
      (= base '()) (if (reversible? base) :vector :list )
      )))


;filp out 
(fn [f] (fn [ & args] (apply f (reverse args))) )

;split-at
(fn [n coll]
  [(take n coll) (drop n coll)])
;Split by Type
(defn temp  [coll]
  (defn add-vec-to-set [type-hash t x] 
    (let [ar-val (type-hash t)  
          array (if (= ar-val nil) [] ar-val) ] 
      (into type-hash {t (conj array x)})))
  (vals
    (loop [ col coll type-hash {}]
      (let [[x & xs] col
            t (type x)]
        (if (empty? col) type-hash 
          (recur xs (add-vec-to-set type-hash t x)))))))
(fn  [coll]
  (vals
    (loop [ col coll type-hash {}]
      (let [[x & xs] col
            t (type x)]
        (if (empty? col) type-hash
          (recur xs (let [ar-val (type-hash t)  
                          array (if (= ar-val nil) [] ar-val) ] 
                      (into type-hash {t (conj array x)}))))))))
(fn split-by-type [v]
  (for [[key value] (group-by class v)]
    value))


(defn longest-increasing-sub-seq [coll]
  (let [a (partition-by #(apply < %) (partition 2 1 coll))
        b (filter (fn [[[x1 x2]]] (< x1 x2)) a) 
        c (first (sort-by count > b))]
    (concat (first c) (map last (rest c)))))

;Count Occurrences
(fn [coll]
  (let [ a (group-by identity coll)
        b  (for [[key value] a]   [key (count value)])]
    (into {} (vec b))))
;Partition a Sequence
(fn [n coll]
  (loop [coll coll held []] 
    (if (<= (count coll) (dec n)) (seq held)
      (recur (drop n coll) (conj  held (take n coll))))))

;Find Distinct Items
(fn [coll]
  (reduce (fn [x y] (if (some #(= y %) x) x (conj x y))) [] coll))

;Function Composition
(fn [& fs] (fn [x]
             [ x (reverse  fs)] 
             (loop [fs (reverse fs) x x]
               (let [[f & fs] fs]
                 (if (<= (count fs) 0) (f x) 
                   (recur fs (f x)))))))

;58: Function Composition
(fn ([& fs]
      (let [fs (reverse (list* fs))]
        (fn [& args] (loop [ret (apply (first fs) args) fs (next fs)]
                       (if fs (recur ((first fs) ret) (next fs))
                         ret))))))

;Juxtaposition
(defn myjuxt [& fs] 
  (fn ([& args] (reduce #(conj  %1 (apply %2  args)) [] fs))))

;Sequence Reductions
(def myreductions 
  (letfn [(myreductions
            ([f coll]
              (lazy-seq 
                        (if-let [s (seq coll)]
                          (myreductions f (first s) (rest s))
                          (list (f)))))
            ([f init coll]
              (cons init 
                    (lazy-seq
                      (when-let [s (seq coll)]
                        (myreductions f (f init (first s)) (rest s)))))))]
    (fn 
      ([f coll] (myreductions f coll))
      ([f init coll] (myreductions f init coll))))
  )


;map construction
(def myzipmap 
  (fn  [x y]
    (reduce #(into %1 %2) {}  (map #(identity {%1 %2}) x y)))
  )


;Re-implement Iterate
(def myiterate 
  (fn [f init]
    (letfn [(myiterate
              ([f init]
                (cons init (lazy-seq (myiterate f (f init))))))]
      (myiterate f init)))
  )
;group a sequence
(def mygroup-by 
  (fn [f coll]
    (if-let [s (seq coll)]
      (reduce #(let [x (f %2) elem  (%1 x [])]
                 (into %1 {x (conj elem %2)}))
              {} coll)
      {}))
  )
;Greatest Common Divisor
(fn [a b]
  (if (zero? b)
    a
    (recur b (mod a b))))

;Prime Numbers
(def prime-number 
  (fn [n] 
    (loop [ret [] n n i 2]
      (if (zero? n) 
        ret
        (if (some #(zero? (mod i %)) ret) 
          (recur ret n (inc i))
          (recur (conj ret i) (dec n) (inc i))))))
  )


;Merge with a Function
(def mymerge-with 
  (fn 
    [f & maps]
    (letfn  [(merge-entry [m e]
               (let [k (key e) v (val e)]
                 (if (contains? m k)
                   (assoc m k (f (get m k) v))
                   (assoc m k v))))
             (merge2 [m1 m2]
               (reduce merge-entry (or m1 {}) m2))]
      (reduce merge2 maps)))
  )
;Word Sorting
(def temp
  #(sort-by clojure.string/lower-case (clojure.string/split %  #"\W") )
  )



;Rearrangig Code: ->>
#(apply + %)


;Analyze a Tic-Tac-Toe Board
(def __ 
  (fn [matrix]
    (letfn [(judge [v]
              (cond (every? #(= :o %) v) :o
                    (every? #(= :x %) v) :x
                    :else nil))
            (transpose [m]
              (apply mapv vector m))]
      (let [crosses [(map #(-> matrix (nth %1) (nth %1)) (range 0 3)) 
                     (map #(-> matrix (nth %1) (nth (- 2 %1))) (range 0 3))]
            res (apply clojure.set/union (map set 
                                              [(map #(judge %) matrix)
                                               (map #(judge %) (transpose matrix))
                                               (map #(judge %) crosses)]))]
        (cond (some #(= :o %) res) :o
              (some #(= :x %) res) :x
              :else nil))))
  )

(= nil (__ [[:e :e :e]
            [:e :e :e]
            [:e :e :e]]))
(= :x (__ [[:x :e :o]
           [:x :e :e]
           [:x :e :o]]))
(= :o (__ [[:e :x :e]
           [:o :o :o]
           [:x :e :x]]))
(= nil (__ [[:x :e :o]
            [:x :x :e]
            [:o :x :o]]))
(= :x (__ [[:x :e :e]
           [:o :x :e]
           [:o :e :x]]))
(= :o (__ [[:x :e :o]
           [:x :o :e]
           [:o :e :x]]))
(= nil (__ [[:x :o :x]
            [:x :o :x]
            [:o :x :o]]))

;Filter Perfect Squares
(def __ 
  (fn [string]
    (let [ data (map #(Integer/parseInt %) (clojure.string/split  string  #","))
          square?  (fn [x] (let [t (-> x Math/abs Math/sqrt)]
                             (= t (double (int t)))))
          squares (filter square? data)]
      (apply str (interpose "," squares))))

  )
(= (__ "4,5,6,7,8,9") "4,9")
(= (__ "15,16,25,36,37") "16,25,36")

;Euler's Totient Function

(def __ 
  (fn [n]
    (letfn [(gcd [a b] (if (zero? b) a (recur b (mod a b))))]
      (count (filter #(= 1 (gcd n %)) (range 1 (inc n))))))
  )
(= (__ 1) 1)
(= (__ 10) (count '(1 3 7 9)) 4)
(= (__ 40) 16)
(= (__ 99) 60)

(fn [n]
  (letfn [(gcd [a b] (if (zero? b) a (recur b (mod a b))))]
    (count (filter #(= 1 (gcd n %)) (range 1 (inc n)))))
  )

;Intro to Trampoline
;[Trampolining Through Mutual Recursion With Clojure - Jake McCrary](http://jakemccrary.com/blog/2010/12/06/trampolining-through-mutual-recursion)

;Anagram Finder
(def __ 
  (fn [coll]
    (let [ count-char-map (fn [x] (apply (partial merge-with + ) (map  #(sorted-map % 1) x)))
          s (group-by count-char-map  coll)
          lst (filter #(< 1 (count (val %))) s)]
      (set (map #(set (val %)) lst))))
  )
(= (__ ["meat" "mat" "team" "mate" "eat"])
   #{#{"meat" "team" "mate"}})
(= (__ ["veer" "lake" "item" "kale" "mite" "ever"])
   #{#{"veer" "ever"} #{"lake" "kale"} #{"mite" "item"}})



;Reimplement Trampoline
(def __ trampoline)
(= (letfn [(triple [x] #(sub-two (* 3 x)))
           (sub-two [x] #(stop?(- x 2)))
           (stop? [x] (if (> x 50) x #(triple x)))]
     (__ triple 2))
   82)
(= (letfn [(my-even? [x] (if (zero? x) true #(my-odd? (dec x))))
           (my-odd? [x] (if (zero? x) false #(my-even? (dec x))))]
     (map (partial __ my-even?) (range 6)))
   [true false true false true false])

(def __
  (fn [f & args]
    (loop [ret (apply f args)]
      (if (fn? ret)
        (recur (ret))
        ret)))
  )

;Triangle Minimal Path
(= 7 (__ '(
            [1]
            [2 4]
            [5 1 4]
            [2 3 4 5]))) ; 1->2->1->3
(= 20 (__ '(
             [3]
             [2 4]
             [1 9 3]
             [9 9 2 4]
             [4 6 6 7 8]
             [5 7 3 5 1 4]))) ; 3->4->3->2->7->1

(def __ 
  (fn [tree]
    (letfn [(treesize [v] (reduce + 0 v)) 
            (triangle-minimal-path [current-tree index tree]
              (if (empty? tree) current-tree
                (let [ [t & ts] tree 
                      left-minimal-tree (triangle-minimal-path (conj current-tree (nth t index)) index ts)
                      right-minimal-tree (triangle-minimal-path (conj current-tree (nth t (inc index))) (inc index) ts)]
                  (min-key treesize left-minimal-tree right-minimal-tree))))
            (triangle-minimal-path2 [tree]
              (let [ index 0 
                    current-tree []
                    [t & ts] tree ]
                (triangle-minimal-path (conj current-tree (nth t index)) index ts)))]
      (treesize(triangle-minimal-path2 tree))))
  )

;Perfect Numbers
(= (__ 6) true)
(= (__ 7) false)
(= (__ 496) true)
(= (__ 500) false)
(= (__ 8128) true)
(def __
  (fn [n] (= n (apply + (filter #(= 0 (mod n %)) (range 1 n)))))
  )


; A nil key
(def __ 
  #(and (contains? %2 %1) (nil? (%2 %1)))
  )
(true?  (__ :a {:a nil :b 2}))
(false? (__ :b {:a nil :b 2}))
(false? (__ :c {:a nil :b 2}))

;for the win 
(def )
(= __ (1 5 9 13 17 21 25 29 33 37))
(= __ (for [x (iterate #(+ 4 %) 0)
            :let [z (inc x)]
            :while (< z 40)]
        z))
(= __ (for [[x y] (partition 2 (range 20))]
        (+ x y)))

;A Half-Truth
(def __ 
  (fn [& args]
    (let [s (set args)]
      (and (contains? s true) (contains? s false) )))
  )
(__ false false)

;Word Chains

(def __
  )
(= true (__ #{"hat" "coat" "dog" "cat" "oat" "cot" "hot" "hog"}))
(= false (__ #{"cot" "hot" "bat" "fat"}))
(= false (__ #{"to" "top" "stop" "tops" "toss"}))
(= true (__ #{"spout" "do" "pot" "pout" "spot" "dot"}))
(= true (__ #{"share" "hares" "shares" "hare" "are"}))
(= false (__ #{"share" "hares" "hare" "are"}))

(def __ 
  (fn [path-set]
    (letfn [(chainable? [x y] 
              (let 
                [char-diff-count1? #(= (count %1) (inc (count %2)))
                 change-length-chain?  (fn [x y]
                                         (loop [[x & xs] x [y & ys] y ignore 0]
                                           (cond 
                                                 (nil? y) (or (and (= ignore 0) (nil? xs))
                                                              (and (= ignore 1) (nil? x)))
                                                 (nil? x) (and (= ignore 1) (nil? ys))
                                                 :else  (if (= x y) 
                                                          (recur xs ys ignore)
                                                          (recur xs (cons y ys) (inc ignore))))))
                 change-letter-chain?  (fn [x y]
                                         (loop [[x & xs] x [y & ys] y ignore 0]
                                           (cond
                                             (nil? y) (= ignore 1)
                                             (nil? x) false
                                             :else (if (= x y)
                                                     (recur xs ys ignore)
                                                     (recur xs ys (inc ignore))))))
                 a (map identity x)
                 b (map identity y)]
                (cond
                  (char-diff-count1? x y) (when (change-length-chain? a b) {[x y] 0,[y x] 0})
                  (char-diff-count1? y x) (when (change-length-chain? b a) {[y x] 0,[x y] 0})
                  (= (count x) (count y)) (when (change-letter-chain? a b) {[x y] 0,[y x] 0})
                  :else nil )))
            (chainable-path-set [coll]
              (->> (for [elem coll]
                     (->> (for [t coll :when (not (= t elem))] 
                            (chainable? t elem))
                       (remove nil?)
                       (apply merge))) 
                (apply merge)))
            (close-path-all-from [coll in]
              (->> 
                (for [out coll :when (not (= in out))] {[in out] 1,[out in] 1})
                (apply merge))) 
            (passable-path [current path-set] 
              (->> (for [p path-set]
                     (when (and (= (first (key p)) current) (= (val p) 0) )  p))
                (remove nil?)))
            (patrol [current chainable-path coll]
              (letfn [(patrol2 [in current-path chainable-path]
                        (let [path (passable-path in chainable-path)]
                          (if (empty? path)
                            current-path
                            (for [[[in out] _] path]
                              (patrol2 out (into current-path {in out}) (merge chainable-path (close-path-all-from coll in))))
                            )))]
                (flatten (patrol2 current {} chainable-path))))
            (filter-pass-all [route coll]
              (filter #(= (dec (count coll)) (count %)) route))
            ]
      (let [chainable-path (chainable-path-set path-set)
            unicursal? (->> (for [elem path-set]
                             (let [route (patrol elem chainable-path path-set)
                                   pass-all (filter-pass-all route path-set)]
                               (if (nil? (first pass-all)) false true)))
                        (some identity ))]
        (if unicursal? true false))))
  )


;それはチェイン可能か？
;チェイン可能を全て列挙を作成。cat->cot
;全ての経路を巡回する。
;この時足跡として {["cat","cot"] 1}
;全周回完了 そのマップの大きさが全てのnodeを巡回していることを確認


;Power Set
(def __
  (letfn [(subsets [n items]
            (cond 
                  (= n 0) '(())
                  (empty? items) '()
                  :else (concat (map 
                                     #(cons (first items) %)
                                     (subsets (dec n) (rest items)))
                                (subsets n (rest items)))))]
    (fn [coll]
      (->> 
        (reduce #(concat %1 (subsets %2 (seq coll))) [] (range 1 (inc (count coll))))
        (cons '())
        (map set)
        (set))))
  )

(= (__ #{1 :a}) #{#{1 :a} #{:a} #{} #{1}})
(= (__ #{}) #{#{}})
(= (__ #{1 2 3})
   #{#{} #{1} #{2} #{3} #{1 2} #{1 3} #{2 3} #{1 2 3}})
(= (count (__ (into #{} (range 10)))) 1024)


;[combinatorics - Enumerate k-combinations in Clojure (P26 from 99 problems) - Code Review Stack Exchange](http://codereview.stackexchange.com/questions/8930/enumerate-k-combinations-in-clojure-p26-from-99-problems)

;Happy numbers
(= (__ 7) true)
(= (__ 986543210) true)
(= (__ 2) false)
(= (__ 3) false)
(def __
  (fn [n]
    (loop [n n seen #{}]
      (cond (= n 1) true
            (seen n) false
            :else (recur (->> (str n)
                           (map str)
                           (map #(Long/parseLong %))
                           (map #(* % %))
                           (apply +))
                         (conj seen n)))))
  )
;2015/08/02 15:45 [Happy numbers - Rosetta Code](http://rosettacode.org/wiki/Happy_numbers#Clojure)


;Symmetric Difference
 
(def __ clojure.set/difference )
(def __
  (fn [x y]
    (clojure.set/union (clojure.set/difference x y)
                       (clojure.set/difference y x)))
  )
(= (__ #{1 2 3 4 5 6} #{1 3 5 7}) #{2 4 6 7})
(= (__ #{:a :b :c} #{}) #{:a :b :c})
(= (__ #{} #{4 5 6}) #{4 5 6})
(= (__ #{[1 2] [2 3]} #{[2 3] [3 4]}) #{[1 2] [3 4]})


;Graph Tour
(def __ 
  (fn [coll]
    (let [ path (loop [ s {}  lst coll ]
                  (if (nil? lst)
                    s
                    (let [[x y]  (first lst)]
                      (let [ s (into s {x (inc (s x 0))})] 
                        (recur (into s {y (inc (s y 0))}) (next lst)))))) 
          odd-count (->> (vals path) (filter odd?) count)]
      (if (contains? [0 2] odd-count) true false)))
  )
(= true (__ [[:a :b]]))
(= false (__ [[:a :a] [:b :b]]))
(= false (__ [[:a :b] [:a :b] [:a :c] [:c :a]
              [:a :d] [:b :d] [:c :d]]))
(= true (__ [[1 2] [2 3] [3 4] [4 1]]))
(= true (__ [[:a :b] [:a :c] [:c :b] [:a :e]
             [:b :e] [:a :d] [:b :d] [:c :e]
             [:d :e] [:c :f] [:d :f]]))
(= false (__ [[1 2] [2 3] [2 4] [2 5]]))

(def temp  [[:a :b] [:a :b] [:a :c] [:c :a] [:a :d] [:b :d] [:c :d]])
(def temp  [[:a :b] [:a :b] [:a :c] [:c :a] [:a :d] [:b :d] [:c :d]])
(def temp  [[:a :b] [:a :b] [:a :c] [:c :a] [:a :d] [:b :d] [:c :d]])
(assoc [[:a :b] [:a :b] [:a :c] [:c :a] [:a :d] [:b :d] [:c :d]] :a)
({:a :b} {:a :c} {:c :a} {:a :d} {:b :d} {:c :d}) 
(def t
(->> temp  (map (fn [[x y]] {x y})) merge distinct  ) 
)
(identity #{:a :b :c :d})
(def p) (->> (for [x temp] {x 0}) set )
(or 
(for [  
      in_out (->> p (map keys)  (mapcat identity) (filter #(=  :a (first %))) )
      throughable (->> (get p {b 0}))
      ]
  (when throughable (can-goto-all-element (disj path throughable )))
  ))
(defn can-goto-all-element [coll start path]

  (do (println :coll coll :start start :path path))
  (if (=  0 (count coll)) true
  (if-let [nxt (get path start)]
   (can-goto-all-element (disj coll start) nxt path)
    false)
  )
  )
(can-goto-all-element #{ :a :b :c :d } :a {:a :b, :b :c, :c :d, :d :a})
(can-goto-all-element #{ :a :b :c :d :e} :a {:a :b, :b :c, :c :d, :d :a})
(def aaa #{:a :b})
(disj aaa :a)
(keys {:a :b})
((->> temp 
(map #(identity {(first %) (second %)})) 
)
(map #(identity %1 %2) ())
(hash-map #{:a :b})
(flatten temp)
;オイラーグラフで周回可能か調べる
;木は分裂していないかを調べる

(def __ 
  (fn [coll]
    (let [
          path (loop [ s {}  lst coll ]
                  (if (nil? lst)
                    s
                    (let [[x y]  (first lst)]
                      (let [ s (into s {x (inc (s x 0))})] 
                        (recur (into s {y (inc (s y 0))}) (next lst)))))) 
          odd-count (->> (vals path) (filter odd?) count)]
      (if (contains? [0 2] odd-count) true false)))
  )
)
({} :a 0)
 (__ [[:a :b] [:a :c] [:c :b] [:a :e]
             [:b :e] [:a :d] [:b :d] [:c :e]
             [:d :e] [:c :f] [:d :f]])
(def __ 
  (fn [path-set]
    (letfn [
         (close-path-all-from [coll in]
              (->> 
                (for [out coll ] {[in out] 1})
                (apply merge))) 
            (passable-path [current path-set] 
              (->> (for [p path-set]
                     (when (and (= (first (key p)) current) (= (val p) 0) )  p))
                (remove nil?)))
            (patrol [current chainable-path coll]
              (letfn [(patrol2 [in current-path chainable-path]
                        (let [path (passable-path in chainable-path)]
                            (if (empty? path)
                              current-path
                              (for [[[in out] _] path]
                                (patrol2 out (into current-path {in out}) (merge chainable-path {[in out] 1})))
                              ))
                        )]
                (flatten (patrol2 current {} chainable-path))))
            (filter-pass-all [routes coll]
                  (filter #(=  (set coll) (clojure.set/union (set (keys %)) (set (vals %)))) routes)
              )
            ]
      (let [
            path (loop [ s {}  lst path-set ]
                   (if (nil? lst)
                     s
                     (let [[x y]  (first lst)]
                       (let [ s (into s {x (inc (s x 0))})] 
                         (recur (into s {y (inc (s y 0))}) (next lst)))))) 
            odd-count (->> (vals path) (filter odd?) count)
            chainable-path (->> (for [x path-set] {x 0}) (apply merge) )
            unicursal? (let [coll (->> path keys seq)] coll
                         (->> (for [elem coll]
                                (let [routes (patrol elem chainable-path coll)
                                      pass-all (filter-pass-all routes coll)]
                                  (if (nil? (first pass-all)) false true)))
                           (some identity ))) 
            ]
        (println  :path path :odd-count odd-count :chainable-path chainable-path  :unicursal? unicursal?))))
  )

;できない


;Map Defaults
(def __ (fn [x ylst] (->> (for [y ylst] {y x}) (apply merge))))
(= (__ 0 [:a :b :c]) {:a 0 :b 0 :c 0})
(= (__ "x" [1 2 3]) {1 "x" 2 "x" 3 "x"})
(= (__ [:a :b] [:foo :bar]) {:foo [:a :b] :bar [:a :b]})


;Indexing Sequences
(def __ (fn [lst]  (->> (zipmap lst (range (count lst))  ) vec reverse )))
(= (__ [:a :b :c]) [[:a 0] [:b 1] [:c 2]])
(= (__ [0 1 3]) '((0 0) (1 1) (3 2)))
(= (__ [[:foo] {:bar :baz}]) [[[:foo] 0] [{:bar :baz} 1]])

;Decurry
(def __
  (fn [f]
    (fn [& lst]
      (loop [f f lst lst]
        (if (empty? lst) f
          (recur (f (first lst)) (rest lst))))))
  )
(= 10 ((__ (fn [a]
             (fn [b]
               (fn [c]
                 (fn [d]
                   (+ a b c d))))))
        1 2 3 4))

(= 24 ((__ (fn [a]
             (fn [b]
               (fn [c]
                 (fn [d]
                   (* a b c d))))))
        1 2 3 4))
(= 25 ((__ (fn [a]
             (fn [b]
               (* a b))))
        5 5))


;Beauty is Symmetry
(def __
(fn [tree]
  (letfn [(reverse-tree [tree] 
            (let [[key right left] tree
                  right-tree (if-not (nil? right) (reverse-tree right) nil)
                  left-tree (if-not (nil? left) (reverse-tree left) nil)
                  ]
              [key left-tree right-tree]
              )
            )]
    (let [[key right left] tree]
      (= right (reverse-tree left))
      )))
)
(= (__ '(:a (:b nil nil) (:b nil nil))) true)
(= (__ '(:a (:b nil nil) nil)) false)
(= (__ '(:a (:b nil nil) (:c nil nil))) false)
(= (__ [1 [2 nil [3 [4 [5 nil nil] [6 nil nil]] nil]]
                  [2 [3 nil [4 [6 nil nil] [5 nil nil]]] nil]])
      true)
(= (__ [1 [2 nil [3 [4 [5 nil nil] [6 nil nil]] nil]]
                  [2 [3 nil [4 [5 nil nil] [6 nil nil]]] nil]])
      false)
(= (__ [1 [2 nil [3 [4 [5 nil nil] [6 nil nil]] nil]]
                  [2 [3 nil [4 [6 nil nil] nil]] nil]])
      false)



;Pascal's Triangle
(def __ 
  (fn [n]
    (letfn [ (pascal-triangle-next [lst] 
               (let [lst-with-i (zipmap (range (count lst)) lst)] 
                 (->> (for [[k v] lst-with-i]
                        (for [ i (range (inc (count lst-with-i)))] 
                          (if (or (= k i) (= (inc k)  i))
                            v 0)))
                   (apply map  +)))) ]
      (if (< n 0) nil
        (loop [n n lst [1]]
          (if (= n 1)
            lst
            (recur (dec n) (pascal-triangle-next lst))))))
    )
  )

;Equivalence Classes
(def __ #(->> (group-by %1 %2) vals (map set) set))
(= (__ #(* % %) #{-2 -1 0 1 2})
      #{#{0} #{1 -1} #{2 -2}})
(= (__ #(rem % 3) #{0 1 2 3 4 5 })
      #{#{0 3} #{1 4} #{2 5}})
(= (__ identity #{0 1 2 3 4})
      #{#{0} #{1} #{2} #{3} #{4}})
(= (__ (constantly true) #{0 1 2 3 4})
      #{#{0 1 2 3 4}})
;Product Digits
(def  __
  (fn [x y] (->>  (* x y)  str (map identity ) (map #(Character/digit % 10))))
  )
;2015/08/03 16:09 [lcm « Clojure Companion Cube](http://clojure.roboloco.net/?tag=lcm)
(fn [& nums]
  (letfn [ (multiple-of-all? [n factors]
              (every? #(zero? (rem n %)) factors))]
    (let [ns (sort > nums)
                  mx (first ns)]
          (first (filter #(multiple-of-all? % ns) (iterate #(+ mx %) mx))))))

;Simple closures
(def __
  #(fn [x] (->> (repeat  % x) (apply *)))
  )
((__ 8) 2)

;Lazy Searching
(def __
  (fn [& args] 
    (letfn [(lazy-search
              ([fl sl] 
              (let [f (first fl) s (first sl)]  
                (cond 
                      (= f s) f 
                      (< f s) (lazy-search (next fl) sl) 
                      (< s f) (lazy-search fl (next sl)) 
                      )))
              ([fl sl tl] 
              (let [f (first fl) s (first sl) t (first tl)]  
                (cond 
                      (= f s t) f 
                      (every? identity (map #(<= f %) [s t])) (lazy-search (next fl) sl tl) 
                      (every? identity (map #(<= s %) [f t])) (lazy-search fl (next sl) tl)
                      (every? identity (map #(<= t %) [f s])) (lazy-search fl sl (next tl))
                      )))
              )]
    (cond
      (= 1 (count args)) (ffirst args)
      (= 2 (count args)) (lazy-search (first args) (second args))
      (= 3 (count args)) (lazy-search (first args) (second args) (nth args 2))
      )))
  )

(= 4 (__ [1 2 3 4 5 6 7] [0.5 3/2 4 19]))
(= 7 (__ (range) (range 0 100 7/6) [2 3 5 7 11 13]))
(= 64 (__ (map #(* % % %) (range)) ;; perfect cubes
                    (filter #(zero? (bit-and % (dec %))) (range)) ;; powers of 2
                    (iterate inc 20))) ;; at least as large as 20

;Sequence of pronunciations
(def __
(fn [lst]
  (letfn [(sequence-of-pronunciations [lst]
            (let [nxt (->> (partition-by identity  lst)
                        (map #(identity [(count %) (first %)] ))
                        flatten 
                        vec) ]
              (cons nxt (lazy-seq (sequence-of-pronunciations nxt)))
              ))]
    (sequence-of-pronunciations lst)))
 ) 
(= [[1 1] [2 1] [1 2 1 1]] (take 3 (__ [1])))
(= [3 1 2 4] (first (__ [1 1 1 4 4])))
(= [1 1 1 3 2 1 3 2 1 1] (nth (__ [1]) 6))
(= 338 (count (nth (__ [3 2]) 15)))


;Cartesian Product
#(set (for [a  %1 b %2] [a b]))

;Universal Computation Engine
(def __
  (fn [form] 
    (letfn [(step [s]
              (let [formulars (re-seq #"\([^\(\)]+\)" s)] 
                (if (seq formulars)
                  (let [formulars-results (map (fn [formular]
                                                 (let [formular-seq (re-seq #"[\d\+\-\*/]+" formular) ]
                                                   formular-seq 
                                                   (apply (case (first formular-seq)
                                                            "+" +
                                                            "-" -
                                                            "*" *
                                                            "/" /)
                                                          (map #(Integer/parseInt % 10) (rest formular-seq)))) 
                                                 ) formulars)]
                    (step (reduce #(clojure.string/replace %1 (key %2) (str (val %2))) s (apply assoc {} (interleave formulars formulars-results)))))
                  (Integer/parseInt s 10))))]
      (fn [m]
        (let [form-str (str form)]
          (step (reduce #(.replace %1 (str (key %2)) (str (val %2))) form-str m))))))
  )


(= 2 ((__ '(/ a b))
             '{b 8 a 16}))
(= 8 ((__ '(+ a b 2))
       '{a 2 b 4}))
(= [6 0 -4]
   (map (__ '(* (+ 2 a)
                (- 10 b)))
        '[{a 1 b 8}
          {b 5 a -2}
          {a 2 b 11}]))

(= 1 ((__ '(/ (+ x 2)
              (* 3 (+ y 1))))
       '{x 4 y 1}))

;2015/08/05 15:00 [4clojure-answer/121-universal-computation-engine.clj at master · khotyn/4clojure-answer](https://github.com/khotyn/4clojure-answer/blob/master/121-universal-computation-engine.clj)



;dot product
(def __ 
  (fn [x y] (->> (interleave x y) (partition 2 ) (map #(apply * %)) (apply +)))
  )

;Oscilrate
(def __
  (fn [init & fs]
    (letfn [ (repeat-fs [fs] 
               (cons (first fs) 
                     (lazy-seq (repeat-fs (concat (rest fs) [(first fs)]))))) 
            (oscilrate [init  fs]
              (cons init
                    (lazy-seq (oscilrate ((first fs) init) (rest fs))))) ]
      (let [fs (repeat-fs fs)]
        (oscilrate init fs))))
  )
(= (take 3 (__ 3.14 int double)) [3.14 3 3.0])
(= (take 5 (__ 3 #(- % 3) #(+ 5 %))) [3 0 5 2 7])
(= (take 12 (__ 0 inc dec inc dec inc)) [0 1 0 1 0 1 2 1 2 1 2 3])


;Trees into tables
(def __
  (fn [m]
    (->>
      (map (fn [t]
             (let [ a (key t) b (val t)]
               (map #(identity {[a (key %)] (val %)}) b)))
           m)
      flatten 
      reverse
      (apply merge )
      ))
  )
(= (__ '{a {p 1, q 2}
                  b {m 3, n 4}})
      '{[a p] 1, [a q] 2
             [b m] 3, [b n] 4})
(= (__ '{[1] {a b c d}
                  [2] {q r s t u v w x}})
      '{[[1] a] b, [[1] c] d,
             [[2] q] r, [[2] s] t,
             [[2] u] v, [[2] w] x})
(= (__ '{m {1 [a b c] 3 nil}})
      '{[m 1] [a b c], [m 3] nil})

;Pascal's Trapezoid
(def __
  (fn [lst]
    (letfn [ (pascal-triangle-next [lst]
               (loop [current [0] lst lst]
                 (if (empty? lst)
                   (reverse current)
                   (let [[cf & cs] current 
                         [lf & ls] lst]
                     (recur (cons lf (cons (+' lf cf) cs)) ls)))
                 ))
               (pascal-trapezoid [lst]
                                 (cons lst 
                    (lazy-seq (pascal-trapezoid (pascal-triangle-next lst)))) 
              )]
      (pascal-trapezoid lst)
      ))
  )

(= (second (__ [2 3 2])) [2 5 5 2])
(= (take 5 (__ [1])) [[1] [1 1] [1 2 1] [1 3 3 1] [1 4 6 4 1]])
(= (take 2 (__ [3 1 2])) [[3 1 2] [3 4 3 2]])
(= (take 100 (__ [2 4 2])) (rest (take 101 (__ [2 2]))))

;Through the Looking Class
java.lang.Class



;Infix Calculator
(def __ 
  (fn [& lst]
    (letfn [(infix-calculator [current [lf & lst]]
              (cond 
                    (nil? lf) (first current)
                    (fn? lf) (let [nxt (lf (first current) (first lst))] 
                               (infix-calculator (cons nxt (rest current)) (rest lst))
                               )
                    :else (infix-calculator (cons lf current) lst)))]
      (infix-calculator [] lst)
      ))
  )
(= 7  (__ 2 + 5))
(= 42 (__ 38 + 48 - 2 / 2))
(= 8  (__ 10 / 2 - 1 * 2))
(= 72 (__ 20 / 2 + 2 + 4 + 8 - 6 - 10 * 9))

;Digits and bases

(def __
  (fn [n base]
    (loop [current [] n n]
      (if  (= 0 n) 
        (if (empty? current) [0] current)
        (recur (cons (mod n base) current) (quot n base))))
    )
  )
(= [1 2 3 4 5 0 1] (__ 1234501 10))
(= [0] (__ 0 11))
(= [1 0 0 1] (__ 9 2))
(= [1 0] (let [n (rand-int 100000)](__ n n)))
(= [16 18 5 24 15 1] (__ Integer/MAX_VALUE 42))

;Re-implement Map
(def __
  (fn [f coll]
    (letfn [
            (mymap [f coll]
              (lazy-seq
                (let [s (seq coll)]
                  (when s
                    (cons (f (first s))
                          (mymap f (rest s)))))))
            ]
      (mymap f coll)))
  )
(= [3 4 5 6 7]
   (__ inc [2 3 4 5 6]))
(= (repeat 10 nil)
      (__ (fn [_] nil) (range 10)))
(= [1000000 1000001]
      (->> (__ inc (range))
                (drop (dec 1000000))
                (take 2)))

;To Tree, or not to Tree


(def __
  (fn [tree]
   (letfn [(binary-tree? [tree]
             (cond 
                   (nil? tree) true
                   (not (sequential? tree)) false
                   (empty? tree) false
                   :else (let [[key right left] tree]
                           (if 
                             (and (= 3 (count tree)) 
                                  (not (nil? key)) 
                                  (binary-tree? right) 
                                  (binary-tree? left))  
                             true
                             false))))]
     (binary-tree? tree)))
  )
(= (__ '(:a (:b nil nil) nil))
      true)
(= (__ '(:a (:b nil nil)))
      false)
(= (__ [1 nil [2 [3 nil nil] [4 nil nil]]])
      true)
(= (__ [1 [2 nil nil] [3 nil nil] [4 nil nil]])
      false)
(= (__ [1 [2 [3 [4 nil nil] nil] nil] nil])
      true)
(= (__ [1 [2 [3 [4 false nil] nil] nil] nil])
      false)
(= (__ '(:a nil ()))
      false)
 

;Recognize Playing Cards
(def __ 
 (fn [string]
   (let [[s r] (map identity string)
         suits {\D :diamond \H :heart \C :club \S :spade}
         ranks  (apply assoc {} (interleave (map identity "23456789TJQKA")  (range 13)))]
         {:suit (suits s) :rank (ranks r)}
     ))
)
(= {:suit :diamond :rank 10} (__ "DQ"))
(= {:suit :heart :rank 3} (__ "H5"))
(= {:suit :club :rank 12} (__ "CA"))
(= (range 13) (map (comp :rank __ str)
                   '[S2 S3 S4 S5 S6 S7
                     S8 S9 ST SJ SQ SK SA]))

;Balancing Brackets
(def __ 
  (fn [string]
   (letfn [(have-brackets? [string] (if (re-seq #"[\(\)\[\]\{\}]" string) true false))
           (patten-cleaning [string search-patten clean_patten] 
             (let [brankets-strings (re-seq search-patten string) 
                   brankets-strings-result (map #(clojure.string/replace % clean_patten "") brankets-strings) ]
               (if (seq brankets-strings)
                   (reduce #(clojure.string/replace %1 (key %2) (val %2)) string (apply assoc {} (interleave brankets-strings brankets-strings-result)))
                   string
               )
             ))
           (brankets-clean [string]
             (let [patten-map { #"\([^\[\]\{\}\(\)]*\)"  #"[\(\)]" #"\[[^\[\]\{\}\(\)]*\]"  #"[\[\]]" #"\{[^\[\]\{\}\(\)]*\}"  #"[\{\}]" }]
             (reduce #(patten-cleaning %1 (key %2) (val %2)) string  patten-map)
               )
             )]
     (if (have-brackets? string) 
       (let [cleaned (brankets-clean string)]
           (if (= cleaned string)
             false 
             (recur cleaned)) )
       true)
     )) 
    )
(__ "This string has no brackets.")
(__ "class Test {
          public static void main(String[] args) {
            System.out.println(\"Hello world.\");
          }
        }")
(not (__ "(start, end]"))
(not (__ "())"))
(not (__ "[ { ] } "))
(__ "([]([(()){()}(()(()))(([[]]({}()))())]((((()()))))))")
(not (__ "([]([(()){()}(()(()))(([[]]({}([)))())]((((()()))))))"))
(not (__ "["))

;Pairwise Disjoint Sets
(def __ 
  (fn [coll] 
   (every? identity 
   (for [i coll j coll k j] 
      (cond
        (= i j) true
        (contains? i k) false
        :else true
        )) 
     ))
  )
(= (__ #{#{\U} #{\s} #{\e \R \E} #{\P \L} #{\.}})
      true)
(= (__ #{#{:a :b :c :d :e}
                  #{:a :b :c :d}
                  #{:a :b :c}
                  #{:a :b}
                  #{:a}})
      false)
(= (__ #{#{[1 2 3] [4 5]}
                  #{[1 2] [3 4 5]}
                  #{[1] [2] 3 4 5}
                  #{1 2 [3 4] [5]}})
      true)
(= (__ #{#{'a 'b}
                  #{'c 'd 'e}
                  #{'f 'g 'h 'i}
                  #{''a ''c ''f}})
      true)
(= (__ #{#{'(:x :y :z) '(:x :y) '(:z) '()}
                  #{#{:x :y :z} #{:x :y} #{:z} #{}}
                  #{'[:x :y :z] [:x :y] [:z] [] {}}})
      false)
(= (__ #{#{(= "true") false}
                  #{:yes :no}
                  #{(class 1) 0}
                  #{(symbol "true") 'false}
                  #{(keyword "yes") ::no}
                  #{(class '1) (int \0)}})
      false)
(= (__ #{#{distinct?}
                  #{#(-> %) #(-> %)}
                  #{#(-> %) #(-> %) #(-> %)}
                  #{#(-> %) #(-> %) #(-> %)}})
      true)
(= (__ #{#{(#(-> *)) + (quote mapcat) #_ nil}
                  #{'+ '* mapcat (comment mapcat)}
                  #{(do) set contains? nil?}
                  #{, , , #_, , empty?}})
      false)

; intoCamelCase
(def __
  (fn [string]
      (let [lowers (re-seq #"-\w+" string)
            convert-results (->> lowers 
                              (map #(rest (map identity %))) 
                              (map #(cons (Character/toUpperCase (first %)) (rest %)))
                              (map #(apply str %)  ) ) ]
        (if (seq lowers) 
          (reduce #(clojure.string/replace %1 (key %2) (val %2)) string (apply assoc {} (interleave lowers convert-results)))
          string)))
  ) 
(= (__ "something") "something")
(= (__ "multi-word-key") "multiWordKey")
(= (__ "leaveMeAlone") "leaveMeAlone")

;Generating k-combinations
(def __
  (letfn [(subsets [n items]
            (cond 
                  (= n 0) '(())
                  (empty? items) '()
                  :else (concat (map 
                                     #(cons (first items) %)
                                     (subsets (dec n) (rest items)))
                                (subsets n (rest items)))))]
    (fn [n coll]
      (->> 
        (subsets n (seq coll))
        (map set)
        (set)))
        )
  )
(= (__ 1 #{4 5 6}) #{#{4} #{5} #{6}})
(= (__ 10 #{4 5 6}) #{})
(= (__ 2 #{0 1 2}) #{#{0 1} #{0 2} #{1 2}})
(= (__ 3 #{0 1 2 3 4}) #{#{0 1 2} #{0 1 3} #{0 1 4} #{0 2 3} #{0 2 4}
                         #{0 3 4} #{1 2 3} #{1 2 4} #{1 3 4} #{2 3 4}})
(= (__ 4 #{[1 2 3] :a "abc" "efg"}) #{#{[1 2 3] :a "abc" "efg"}})
(= (__ 2 #{[1 2 3] :a "abc" "efg"}) #{#{[1 2 3] :a} #{[1 2 3] "abc"} #{[1 2 3] "efg"}
                                      #{:a "abc"} #{:a "efg"} #{"abc" "efg"}})

;The Balance of N
(def __ 
  (fn [n]
    (let [m (->> n str (map identity) (map #(Character/digit % 10)))
          len (count m)
          halflen (quot len 2)
          right-sum (->> m (take halflen) (apply +) )
          left-sum (->> m (drop (if (odd? len) (inc halflen) halflen)) (apply +) )
          ]
      (if (= right-sum left-sum) true false)))
  )
(= true (__ 11))
(= true (__ 121))
(= false (__ 123))
(= true (__ 0))
(= false (__ 88099))
(= true (__ 89098))
(= true (__ 89089))
(= (take 20 (filter __ (range)))
      [0 1 2 3 4 5 6 7 8 9 11 22 33 44 55 66 77 88 99 101])  



;Prime Sandwich
(def __
  (fn [n]
    (letfn [(prime-search [s]
              (if (prime? (first s))
                (cons (first s) (lazy-seq (prime-search (rest s))))
                (prime-search (rest s)))
              )
            (prime? [n]
              (.isProbablePrime (BigInteger/valueOf n) 5)) ]
      (if (prime? n)
        (let [ [right _] (prime-search (iterate dec (dec n)))
              [left _] (prime-search (iterate inc (inc n))) ]
          (if (and
                (> left 0)
                (> right 0)
                (= (/ (+ right left) 2) n)) 
            true 
            false)
          )
        false)
      ))
  )

(= false (__ 4))
(= true (__ 563))
(= 1103 (nth (filter __ (range)) 15))



;Identify keys and values
(defn make [[x & xs] y]
  (if (empty? xs)
    [x y]
    (loop [lst [x []] [x & xs] xs]
      (if (empty? xs)
        (conj lst  x y)
        (recur (conj lst  x []) xs))))
  )
(def __ 
  (fn [v]
    (letfn [(make-two-pair [[x & xs] y]
              (if (empty? xs)
                [x y]
                (loop [lst [x []] [x & xs] xs]
                  (if (empty? xs)
                    (conj lst  x y)
                    (recur (conj lst  x []) xs))))
              )]
      (if (empty? v) {} 
        (->> (partition-by type v)
          (partition 2 ) 
          (mapcat #(apply make-two-pair %)) 
          (apply assoc {})
          ))))
  )
(= {} (__ []))
(= {:a [1]} (__ [:a 1]))
(= {:a [1], :b [2]} (__ [:a 1, :b 2]))
(= {:a [1 2 3], :b [], :c [4]} (__ [:a 1 2 3 :b :c 4]))




;Partially Flatten a Sequence

(def __ 
  (fn [x]
    (filter #(and (sequential? %) (every? (complement sequential?) %) )
            (rest (tree-seq sequential? seq x)))
    )
  )

(= (__ [["Do"] ["Nothing"]])
      [["Do"] ["Nothing"]])
(= (__ [[[[:a :b]]] [[:c :d]] [:e :f]])
      [[:a :b] [:c :d] [:e :f]])
(= (__ '((1 2)((3 4)((((5 6)))))))
      '((1 2)(3 4)(5 6)))

;Global take-while

(def __ 
  (fn global-take-while [n f coll]
    (let [[elem & elems] coll]
      (if (f elem)
        (when (> n 1)
          (lazy-seq (cons elem (global-take-while (dec n) f elems))))
        (lazy-seq (cons elem (global-take-while n f elems))))))
  )
;2015/08/07 16:14 [4clojure-answer/114-global-take-while.clj at master · khotyn/4clojure-answer](https://github.com/khotyn/4clojure-answer/blob/master/114-global-take-while.clj)

(= [2 3 5 7 11 13]
   (__ 4 #(= 2 (mod % 3))
       [2 3 5 7 11 13 17 19 23]))
(= ["this" "is" "a" "sentence"]
   (__ 3 #(some #{\i} %)
       ["this" "is" "a" "sentence" "i" "wrote"]))
(= ["this" "is"]
   (__ 1 #{"a"}
       ["this" "is" "a" "sentence" "i" "wrote"]))



;Insert between two items
(def  __
  (fn insert-between-two-items [f sep lst]
    (if (nil? (second lst))
      lst
      (let [ res (f (first lst) (second lst))]
        (lazy-seq (cons (first lst)
              (if res
                (lazy-seq (cons sep (insert-between-two-items f sep (rest lst) )))
                (insert-between-two-items f sep (rest lst) )))))))
  )
(= '(1 :less 6 :less 7 4 3) (__ < :less [1 6 7 4 3]))
(= '(2) (__ > :more [2]))
(= [0 1 :x 2 :x 3 :x 4]  (__ #(and (pos? %) (< % %2)) :x (range 5)))
(empty? (__ > :more ()))
(= [0 1 :same 1 2 3 :same 5 8 13 :same 21]
   (take 12 (->> [0 1]
              (iterate (fn [[a b]] [b (+ a b)]))
              (map first) ; fibonacci numbers
              (__ (fn [a b] ; both even or both odd
                    (= (mod a 2) (mod b 2)))
                  :same))))


;Write Roman Numerals
(def __
  (fn [n]
    (letfn [ (number-to-roman-numerals [n]
               (cond 
                     (<= 1000 n) (cons "M" (number-to-roman-numerals (- n 1000)))
                     (<= 900 n) (cons "CM" (number-to-roman-numerals (- n 900)))
                     (<= 500 n) (cons "D" (number-to-roman-numerals (- n 500)))
                     (<= 400 n) (cons "CD" (number-to-roman-numerals (- n 400)))
                     (<= 100 n) (cons "C" (number-to-roman-numerals (- n 100)))
                     (<= 90 n) (cons "XC" (number-to-roman-numerals (- n 90)))
                     (<= 50 n) (cons "L" (number-to-roman-numerals (- n 50)))
                     (<= 40 n) (cons "XL" (number-to-roman-numerals (- n 40)))
                     (<= 10 n) (cons "X" (number-to-roman-numerals (- n 10)))
                     (<= 9 n) (cons "IX" (number-to-roman-numerals (- n 9)))
                     (<= 5 n) (cons "V" (number-to-roman-numerals (- n 5)))
                     (<= 4 n) (cons "IV" (number-to-roman-numerals (- n 4)))
                     (<= 1 n) (cons "I" (number-to-roman-numerals (- n 1))))) ]
      (apply str (number-to-roman-numerals n))
      ))
  )
(= "I" (__ 1))
(= "XXX" (__ 30))
(= "IV" (__ 4))
(= "CXL" (__ 140))
(= "DCCCXXVII" (__ 827))
(= "MMMCMXCIX" (__ 3999))
(= "XLVIII" (__ 48))


;Intervals
(def __
  (fn intervals [v]
    (if (empty? v)
      []
      (let [v (sort v)]
        (loop [ start (first v) end (first v) v (rest v) result [] ]
          (if (empty? v)
            (conj result [start end])
            (let [ felem (first v) ]
              (if (or (= end felem) (= (inc end) felem))
                (recur start felem (rest v) result)
                (recur felem felem (rest v) (conj result [start end])))))))))
  )
(= (__ [1 2 3]) [[1 3]])
(= (__ [10 9 8 1 2 3]) [[1 3] [8 10]])
(= (__ [1 1 1 1 1 1 1]) [[1 1]])
(= (__ []) [])
(= (__ [19 4 17 1 3 10 2 13 13 2 16 4 2 15 13 9 6 14 2 11])
          [[1 4] [6 6] [9 11] [13 17] [19 19]])





;Sequs Horribilis
(fn sequs-horribilis2 [n coll sum current]
  (cond 
        (< n  sum ) [current sum]
        (empty? coll) [current sum]
        :else (let [[fcoll & rcoll] coll]
                (if (sequential? fcoll)
                (let [[current sum] (sequs-horribilis2 n fcoll sum current)]
                (cond 
                     (< n  sum) current
                      :else (sequs-horribilis2 n rcoll sum (conj current fcoll))
                      )
                )
    )
  
   ) 
        ))

             (println :n n :coll coll :current current :sum sum)
(def __ 
  (fn sequs-horribilis [n coll]
   (letfn [ (sequs-horribilis2 [n coll current sum]
              (cond (empty? coll) [current sum]
                    :else(let [[fcoll & rcoll] coll] 
                           (if (sequential? fcoll)
                             (let [[result sum] (sequs-horribilis2 n fcoll [] sum)]
                               (if (> sum n)
                                 [(conj current result) sum]
                                 (sequs-horribilis2 n rcoll (conj current result) sum)))
                             (if (> (+ sum fcoll ) n)
                               [current (+ sum fcoll)]
                               (sequs-horribilis2 n rcoll (conj current fcoll) (+ sum fcoll))))))) ]
     (first (sequs-horribilis2 n coll [] 0))
     ) 
    )
  )
(=  (__ 10 [1 2 [3 [4 5] 6] 7])
    '(1 2 (3 (4))))
(=  (__ 30 [1 2 [3 [4 [5 [6 [7 8]] 9]] 10] 11])
    '(1 2 (3 (4 (5 (6 (7)))))))
(=  (__ 9 (range))
    '(0 1 2 3))
(=  (__ 1 [[[[[1]]]]])
    '(((((1))))))
(=  (__ 0 [1 2 [3 [4 5] 6] 7])
    '())
(=  (__ 0 [0 0 [0 [0]]])
    '(0 0 (0 (0))))
(=  (__ 1 [-10 [1 [2 3 [4 5 [6 7 [8]]]]]])
    '(-10 (1 (2 3 (4)))))


;Palindromic Numbers
(def __
  (fn palindrome [n] 
    (let [digits-len #(loop [n % c 0] 
                       (if (= n 0) 
                         c
                         (recur (quot n 10) (inc c) )))
          even-digits? #(let [count (digits-len %) ]
                          (even? count)
                          )
          left-middle #(let [len (if (even-digits? %) 
                                   (quot (digits-len % ) 2) 
                                   (inc (quot (digits-len % ) 2)))]
                          (quot % (long (Math/pow 10 (- (digits-len %) len)))))
        mirror (fn [[num dig]]
                 (loop [a num r (if (= dig :even) num (quot num 10))]
                   (if (= 0 r)
                     a
                     (recur (+ (* a 10) (mod r 10)) (quot r 10)))))
        init #(let [s (left-middle %)] 
                (vector s 
                        (if (even-digits? %) :even :odd) 
                        (long (Math/pow 10 (digits-len s)))))
        nextp (fn [[num even goal]] 
                (let [m (inc num)] 
                  (if (= m goal)
                    (if (= even :even)
                      [goal :odd (* 10 goal)]
                      [(/ goal 10) :even goal])
                    [m even goal] )))
        i  (init  n) 
        palindromes (iterate nextp i) ] 
    (filter (partial <= n ) (map mirror palindromes))))
)
(map __ [1 11 111 1111])
(time
(= (take 26 (__ 0))
      [0 1 2 3 4 5 6 7 8 9 
           11 22 33 44 55 66 77 88 99 
           101 111 121 131 141 151 161])
)
(time
(= (take 16 (__ 162))
      [171 181 191 202 
           212 222 232 242 
           252 262 272 282 
           292 303 313 323])
)
(time
(= (take 6 (__ 1234550000))
      [1234554321 1234664321 1234774321 
           1234884321 1234994321 1235005321])
)
(time
(= (first (__ (* 111111111 111111111)))
      (* 111111111 111111111))
)
(time
(= (set (take 199 (__ 0)))
      (set (map #(first (__ %)) (range 0 10000))))
)
(time
(= true 
      (apply < (take 6666 (__ 9999999))))
)
(time
(= (nth (__ 0) 10101)
      9102019)
)
;2015/08/08 20:03 [clojure - 4clojure palindrome number timeout issue - Stack Overflow](http://stackoverflow.com/questions/19249851/4clojure-palindrome-number-timeout-issue)

;Parentheses... Again
(def __
  (fn parens
    ([n] (parens "" n 0 0))
    ([s n open close]
      (if (= n close)
        #{s}
        (clojure.set/union
          (if (< open n)
            (parens (str s "(") n (inc open) close)
            #{})
          (if (< close open)
            (parens (str s ")") n open (inc close))
            #{})
          ))))
  )
(= #{"((()))" "()()()" "()(())" "(())()" "(()())"} (__ 3))
(= 16796 (count (__ 10)))
(= (nth (sort (filter #(.contains ^String % "(()()()())") (__ 9))) 6) "(((()()()())(())))")
(= (nth (sort (__ 12)) 5000) "(((((()()()()()))))(()))")
;[4clojure/195 - Parentheses... Again.clj at master · MikaelSmith/4clojure](https://github.com/MikaelSmith/4clojure/blob/master/195%20-%20Parentheses...%20Again.clj)


;Infinite Matrix

(def __ 
  (fn infinite-matrix 
    ([f] (infinite-matrix f 0 0))
    ([f m n]
      (letfn [(nextn [m n] (lazy-seq (cons (f m n) (nextn m (inc n)))))]
        (lazy-seq 
          (cons (nextn m n)
                (infinite-matrix f (inc m) n)))))
    ([f m n s t]
      (take s (map #(take t %) (infinite-matrix f m n)))))
  )
(take 5 (map #(take 6 %) (__ str)))
(take 6 (map #(take 5 %) (__ str 3 2)))
(= (__ #(/ % (inc %2)) 1 0 6 4)
      [[1/1 1/2 1/3 1/4]
           [2/1 2/2 2/3 1/2]
           [3/1 3/2 3/3 3/4]
           [4/1 4/2 4/3 4/4]
           [5/1 5/2 5/3 5/4]
           [6/1 6/2 6/3 6/4]])
(= (class (__ (juxt bit-or bit-xor)))
      (class (__ (juxt quot mod) 13 21))
      (class (lazy-seq)))
(= (class (nth (__ (constantly 10946)) 34))
      (class (nth (__ (constantly 0) 5 8) 55))
      (class (lazy-seq)))
(= (let [m 377 n 610 w 987
                  check (fn [f s] (every? true? (map-indexed f s)))
                  row (take w (nth (__ vector) m))
                  column (take w (map first (__ vector m n)))
                  diagonal (map-indexed #(nth %2 %) (__ vector m n w w))]
          (and (check #(= %2 [m %]) row)
                         (check #(= %2 [(+ m %) n]) column)
                         (check #(= %2 [(+ m %) (+ n %)]) diagonal)))
      true)



;The Big Divide
(def __
  (fn [n a b] 
    (let [e #(quot (- n 1) %)
          f #(*' % (/ (*' (e %) (inc' (e %))) 2))
          x (f a) 
          y (f b) 
          z (f (* a b))]
      (-' (+' x y) z)))
)
; I can't understand this problem and people getted an idea. How do you get this solution (or algorithm)?
; [4Clojure Problem 148](https://gist.github.com/Jaskirat/1587473#file-jaskirat-4clojure-solution148-clj-L3)

;Read Roman numerals
(def __ 
  (fn roman-numerals-to-number [string]
    (let [roman-numerals-list {"M" 1000 "CM" 900 "D" 500 "CD" 400 "C" 100 "XC" 90  "L" 50  "XL" 40 "X" 10 "IX" 9 "V" 5 "IV" 4 "I" 1} ]
      (->> (re-seq #"CM|M|CD|D|XC|C|XL|L|X|IX|V|IV|I" string) 
        (map #(roman-numerals-list %))
        (apply +))))
  )



;life of game 

(def __
  (fn life-game-next
    ([v] (life-game-next v (count v) (.length v)))
    ([v n m]
      (letfn [(getnm [v i j] (-> v (nth i) (nth j)))
              (count-around-cell [v n m x y] 
                (->> 
                  (for [i (range (- x 1)  (+ x 2)) j (range (- y 1)  (+ y 2))  
                        :when (and 
                                   (not (and (= i x) (= j y))) 
                                   (<=  0 i) (<= 0 j)
                                   (<  i n) (< j m)
                                   )]
                    (getnm v i j)) 
                  (filter #(= \# %))
                  count))
              (next-state [v n m x y]
                (let [cnt (count-around-cell v n m x y)]
                  (cond 
                        (= cnt 3)  \#
                        (= cnt 2) (getnm v x y)
                        :else  \space))) ]
        (for [i (range 0 n)]
          (->> (for [j (range 0 m)]
                 (next-state v n m i j))
            (apply str)) ))))
  )

(= (__ ["      "  
        " ##   "
        " ##   "
        "   ## "
        "   ## "
        "      "])
   ["      "  
    " ##   "
    " #    "
    "    # "
    "   ## "
    "      "])
(= (__ ["     "
        "     "
        " ### "
        "     "
        "     "])
   ["     "
    "  #  "
    "  #  "
    "  #  "
    "     "])
(= (__ ["      "
        "      "
        "  ### "
        " ###  "
        "      "
        "      "])
   ["      "
    "   #  "
    " #  # "
    " #  # "
    "  #   "
    "      "])


;Number Maze
(def __
(fn number-maze
   ([n goal]
     (let [nextp (fn [n goal cnt] 
                   (cond
                     (= n goal) #{cnt}
                     (even? n) #{[(* n 2) goal (inc cnt)] [(+ n 2) goal (inc cnt)] [(/ n 2) goal (inc cnt)]} 
                     :else  #{[(* n 2) goal (inc cnt)] [(+ n 2) goal (inc cnt)]}))
           nextset (fn [coll] (apply clojure.set/union (map #(apply nextp %) coll) ))
           reach #(first (filter (complement sequential?) %))
           init #{[n goal 1]} ]
       (loop [coll init] 
         (let [nxt (nextset coll)
               res (reach nxt)]
           (if-not (nil? res)
             res
             (recur nxt)))))))
 )
(= 1 (__ 1 1))  ; 1
(= 3 (__ 3 12)) ; 3 6 12
(= 3 (__ 12 3)) ; 12 6 3
(= 3 (__ 5 9))  ; 5 7 9
(= 9 (__ 9 2))  ; 9 18 20 10 12 6 8 4 2
(= 5 (__ 9 12)) ; 9 11 22 24 12




; Win at Tic-Tac-Toe
(def __
  (fn win-at-tic-tac-toe [mark matrix]
    (let [win? (fn [matrix]
                 (letfn [(judge [v]
                           (cond (every? #(= :o %) v) :o
                                 (every? #(= :x %) v) :x
                                 :else nil))
                         (transpose [m]
                           (apply mapv vector m))]
                   (let [crosses [(map #(-> matrix (nth %1) (nth %1)) (range 0 3)) 
                                  (map #(-> matrix (nth %1) (nth (- 2 %1))) (range 0 3))]
                         res (apply clojure.set/union (map set 
                                                           [(map #(judge %) matrix)
                                                            (map #(judge %) (transpose matrix))
                                                            (map #(judge %) crosses)]))]
                     (cond (some #(= :o %) res) :o
                           (some #(= :x %) res) :x
                           :else nil))))
          search-empty (fn [matrix] 
                         (for [i (range 3) j (range 3) 
                               :when (= (-> matrix (nth i) (nth j)) :e)]
                           [i j]))
          copy-v-with-marker (fn [[x y] mark matrix]
                               (for [i (range 3)]
                                 (for[ j (range 3) ]
                                   (if (and (= i x) (= j y)) 
                                     mark
                                     (-> matrix (nth i) (nth j))))))] 
      (->>
        (for [elem (search-empty matrix)
              :when (= mark (win? (copy-v-with-marker elem mark matrix)))]
          elem)
        set)))
  )
(= (__ :x [[:o :e :e] 
           [:o :x :o] 
           [:x :x :e]])
   #{[2 2] [0 1] [0 2]})
(= (__ :x [[:x :o :o] 
           [:x :x :e] 
           [:e :o :e]])
   #{[2 2] [1 2] [2 0]})
(= (__ :x [[:x :e :x] 
           [:o :x :o] 
           [:e :o :e]])
   #{[2 2] [0 1] [2 0]})
(= (__ :x [[:x :x :o] 
           [:e :e :e] 
           [:e :e :e]])
   #{})
(= (__ :o [[:x :x :o] 
           [:o :e :o] 
           [:x :e :e]])
   #{[2 2] [1 1]})




;For Science!
(def __ 
  (fn for-science
    ([v] (for-science v (count v) (.length (first v))))
    ([v m n]
      (let [getmn (fn [v y x] (-> v (nth y) (nth x)))
            where-char(fn [chr]  (fn [v]  (->> (for [i (range m) j (range n) :when (= (getmn v i j) chr) ] [i j]) first)))
            where-c (where-char \C)
            where-m (where-char \M)
            passable? (fn [v y x] 
                        (and  (>= y 0) (>= x 0)
                              (< y m) (< x n)
                              (not (= (getmn v y x) \#))))
            get-ways (fn [v cy cx]
                       (for [a (range -1 2) b (range -1 2)  
                             :when   (and (= (Math/abs (+ a b)) 1) 
                                          (passable? v (+ a cy) (+ b cx))) ]
                         [(+ a cy) (+ b cx)]))
            next-passable-path (fn [v insert-positions] 
                                 (let [nxt-insert-lst (mapcat (fn [[i j]] (get-ways v i j)) insert-positions)]
                                   (if (empty? nxt-insert-lst)
                                     [v ] 
                                     (let [nxt-insert-hash (->> (mapcat (fn [[i j]] (get-ways v i j)) insert-positions)
                                                             (#(interleave % (repeat \C)))
                                                             (apply assoc {} ))

                                           newv (->> (for [i (range m)  j (range n)]
                                                       (cond
                                                         (nxt-insert-hash [i j]) (nxt-insert-hash [i j])
                                                         :else (getmn v i j)))
                                                  (partition n )) ]
                                       [newv (keys nxt-insert-hash)]
                                       ))))
            passable-path  (loop [current-passable v insert-positions [(where-c v)]]
                             (let [[new-passable insert-positions] (next-passable-path current-passable insert-positions)]
                               (if (= new-passable current-passable)
                                 current-passable
                                 (recur new-passable insert-positions))))
            ]
        (let [[my mx] (where-m v)]
          (= (getmn passable-path my mx) \C)
          ))))
  )

(get-in 
 (vec
(map vec ["M   C"])
)
[ 0 4])
(get-in ["M  C"] [0 4] )
(= true  (__ ["M   C"]))
(= false (__ ["M # C"]))
(= true  (__ ["#######"
              "#     #"
              "#  #  #"
              "#M # C#"
              "#######"]))
(= false (__ ["########"
              "#M  #  #"
              "#   #  #"
              "# # #  #"
              "#   #  #"
              "#  #   #"
              "#  # # #"
              "#  #   #"
              "#  #  C#"
              "########"]))
(= false (__ ["M     "
              "      "
              "      "
              "      "
              "    ##"
              "    #C"]))
(= true  (__ ["C######"
              " #     "
              " #   # "
              " #   #M"
              "     # "]))
(= true  (__ ["C# # # #"
              "        "
              "# # # # "
              "        "
              " # # # #"
              "        "
              "# # # #M"]))




(fn [ & coll]
  (reify
    java.lang.Object
    (toString [this]
      (->> coll sort (interpose ", ") (apply str)))
    clojure.lang.Seqable
    (seq [this]
      (letfn [(step [coll result]
                (if (seq? coll)
                  (let [head (first coll)]
                    (if (some #{head} result)
                      (step (next coll) result)
                      (step (next coll) (concat result [head]))))
                  result))]
        (step coll nil)))) )




; Tricky card games
(def __
  (fn [mark]
     (fn [stock] 
       (let [s (if (nil? mark) stock (filter #(=  (:suit %) mark) stock))
             rank #(.indexOf (vector 3 4 5 6 7 8 9 10 11 12 13 1 2 ) %)]
         (first (sort-by #(rank (:rank %)) > s)))))
  ) 
(let [notrump (__ nil)]
  (and (= {:suit :club :rank 9}  (notrump [{:suit :club :rank 4}
                                           {:suit :club :rank 9}]))
       (= {:suit :spade :rank 2} (notrump [{:suit :spade :rank 2}
                                           {:suit :club :rank 10}]))))
(= {:suit :club :rank 10} ((__ :club) [{:suit :spade :rank 2}
                                       {:suit :club :rank 10}]))
(= {:suit :heart :rank 8}
   ((__ :heart) [{:suit :heart :rank 6} {:suit :heart :rank 8}
                 {:suit :diamond :rank 10} {:suit :heart :rank 4}]))


; Crossword puzzle
 
(transpose
  ["abcde"
   "12345"]
  )
((fn similar? [origin v]
   (loop [[fo & ro] origin [fv & rv] v]
     (if (and (nil? fo) (nil? fv))
       true
       (if (or (= fv \_) (= fv fo))
         (recur ro rv)
         false))
     ))
  (vec "1234") (vec "_23_"))
(def __
  (fn crossword-puzzle [string matrix]
    (letfn [(transpose [m] (apply mapv vector m))
            (get-path [v] (->> v (partition-by #(= % \#)) (remove #(= (first %) \#) )) ) 
            (get-all-path [matrix]
              (concat 
                      (mapcat #(get-path (vec %))  matrix)
                      (mapcat #(get-path (vec %))  (transpose matrix))))
            (similar? [origin v]
              (loop [[fo & ro] origin [fv & rv] v]
                (if (and (nil? fo) (nil? fv))
                  true
                  (if (or (= fv \_) (= fv fo))
                    (recur ro rv)
                    false))))]
      (let [matrix (map #(clojure.string/replace % " " "") matrix)]
        (->>  (get-all-path matrix) 
          (filter #(= (count %) (count string)))
          (some (partial similar? (vec string)))
          ((comp not nil?))))))
  )
(= true  (__ "the" ["_ # _ _ e"]))
(= false (__ "the" ["c _ _ _"
                    "d _ # e"
                    "r y _ _"]))
(= true  (__ "joy" ["c _ _ _"
                    "d _ # e"
                    "r y _ _"]))
(= false (__ "joy" ["c o n j"
                    "_ _ y _"
                    "r _ _ #"]))
(= true  (__ "clojure" ["_ _ _ # j o y"
                        "_ _ o _ _ _ _"
                        "_ _ f _ # _ _"]))



;Best Hand

(def __
  (fn [hand]
    (let [
          string-to-card (fn [string]
                           (let [[s r] (map identity string)
                                 suits {\D :diamond \H :heart \C :club \S :spade}
                                 ranks  (apply assoc {} (interleave (map identity "23456789TJQKA")  (range 13)))]
                             {:suit (suits s) :rank (ranks r)}))
          hand (map string-to-card hand)
          pairs (->> hand
                  (group-by :rank)
                  vals
                  (map count) 
                  (filter #(> % 1)))
          straight? (let [straight? (fn [ranks] 
                                      (if (empty? ranks)
                                        false
                                        (loop [[fh sh & rh] ranks]
                                          (if (nil? sh)
                                            true
                                            (if  (= (inc fh) sh)
                                              (recur (cons sh rh) )
                                              false)))))
                          ranks (->> hand (map  :rank) sort)
                          oranks (let [ranks (vec ranks)
                                       at (.indexOf ranks 12)] 
                                   (if (= at -1) 
                                     []
                                     (sort (assoc ranks at -1)))) 
                          ]
                      (or (straight? ranks) (straight? oranks) ))

          flush?      (= 5 (->> hand
                             (group-by :suit)
                             vals
                             (map count) 
                             (apply max))) ]
      (cond
        (and straight? flush?) :straight-flush
        (some #(= % 4) pairs) :four-of-a-kind
        (and (some #(= % 2) pairs) (some #(= % 3) pairs)) :full-house
        flush? :flush
        straight? :straight
        (some #(= % 3) pairs) :three-of-a-kind
        (= (count (filter #(= % 2) pairs)) 2) :two-pair
        (some #(= % 2) pairs) :pair
        :else :high-card )))
  )

(= :high-card (__ ["HA" "D2" "H3" "C9" "DJ"])) 
(= :pair (__ ["HA" "HQ" "SJ" "DA" "HT"])) 
(= :two-pair (__ ["HA" "DA" "HQ" "SQ" "HT"])) 
(= :three-of-a-kind (__ ["HA" "DA" "CA" "HJ" "HT"])) 
(= :straight (__ ["HA" "DK" "HQ" "HJ" "HT"])) 
(= :straight (__ ["HA" "H2" "S3" "D4" "C5"])) 
(= :flush (__ ["HA" "HK" "H2" "H4" "HT"])) 
(= :full-house (__ ["HA" "DA" "CA" "HJ" "DJ"])) 
(= :four-of-a-kind (__ ["HA" "DA" "CA" "SA" "DJ"])) 
(= :straight-flush (__ ["HA" "HK" "HQ" "HJ" "HT"]))





;Levenshtein Distance

(def __
  (fn levenshtein-distance [s t]
    (let [m (count s)
          n (count t) 
          init (apply merge (for [i (range (inc m)) j (range (inc n))] {[i j] 0}))
          d (merge init 
                   (apply merge (for [i (range 1 (inc m))] {[i 0] i}))
                   (apply merge (for [j (range 1 (inc n))] {[0 j] j})))
          lst (for [j (range 1 (inc n)) i (range 1 (inc m))] [i j])
          ]
      (loop [[[i j] & rlst] lst d d] 
        (if (nil? i)
          (d [m n])
          (if (= (nth s (dec i)) (nth t (dec j)))
            (recur rlst (assoc d [i j] (d [(dec i) (dec j)])))
            (recur rlst (assoc d [i j] (min (inc (d [(dec i) j]))
                                            (inc (d [i (dec j)]))
                                            (inc (d [(dec i) (dec j)]))))))))))
  )
(= (__ "kitten" "sitting") 3)
(= (__ "closure" "clojure") (__ "clojure" "closure") 1)
(= (__ "xyx" "xyyyx") 2)
(= (__ "" "123456") 6)
(= (__ "Clojure" "Clojure") (__ "" "") (__ [] []) 0)
(= (__ [1 2 3 4] [0 2 3 4 5]) 2)
(= (__ '(:a :b :c :d) '(:a :d)) 2)
(= (__ "ttttattttctg" "tcaaccctaccat") 10)
(= (__ "gaattctaatctc" "caaacaaaaaattt") 9)



;Analyze Reversi
(def __
  (fn [matrix mark]
    (let [m (count matrix) 
          n (count (first matrix)) 
          other-mark (if (= mark 'w) 'b 'w)
          ]
      (letfn [(top-left [y x] (map #(identity [%1 %2]) (range y -1 -1) (range x -1 -1)))
              (top-right  [y x] (map #(identity [%1 %2]) (range y -1 -1) (range x n 1)))
              (bottom-right  [y x] (map #(identity [%1 %2]) (range y m 1) (range x n 1)))
              (bottom-left  [y x] (map #(identity [%1 %2]) (range y m 1) (range x -1 -1)))
              (top [y x] (map #(identity [%1 %2]) (range y -1 -1) (repeat x)))
              (bottom [y x] (map #(identity [%1 %2]) (range y m 1) (repeat x)))
              (right [y x] (map #(identity [%1 %2]) (repeat y) (range x n 1)))
              (left [y x] (map #(identity [%1 %2]) (repeat y) (range x -1 -1)))
              (get-pushable-point [path] 
                (let [v (map  (partial get-in matrix) path) ]
                  (when (= (first v) 'e)
                    (loop [[vf & vs] (next v) [lf & ls] (next path) recode #{}]
                      (cond (and ((comp not empty?) recode) (= vf mark))  recode
                            (= vf other-mark) (recur vs  ls (conj recode lf)))))))
              (all-way [x y] ((juxt top top-left left bottom-left bottom bottom-right right top-right) x y))
              (get-by-point[x y]
                (->>
                  (map get-pushable-point (all-way x y))
                  (filter (comp not nil?))
                  (apply merge))) ]
        (->> (for [i (range 0 n) j (range 0 m)]
               (let [ x (get-by-point i j)] 
                 (when ((comp not empty?) x) 
                   {[i j] x})))
          (apply merge))
        )))
  )

(= {[1 3] #{[1 2]}, [0 2] #{[1 2]}, [3 1] #{[2 1]}, [2 0] #{[2 1]}}
   (__ '[[e e e e]
         [e w b e]
         [e b w e]
         [e e e e]] 'w))
(= {[3 2] #{[2 2]}, [3 0] #{[2 1]}, [1 0] #{[1 1]}}
   (__ '[[e e e e]
         [e w b e]
         [w w w e]
         [e e e e]] 'b))
(= {[0 3] #{[1 2]}, [1 3] #{[1 2]}, [3 3] #{[2 2]}, [2 3] #{[2 2]}}
   (__ '[[e e e e]
         [e w b e]
         [w w b e]
         [e e b e]] 'w))
(= {[0 3] #{[2 1] [1 2]}, [1 3] #{[1 2]}, [2 3] #{[2 1] [2 2]}}
   (__ '[[e e w e]
         [b b w e]
         [b w w e]
         [b w w w]] 'b))

;Love Triangle
(map #(identity [%1 %2]) (range 0 2) (range 2 0 -1))
(= 15 (__ [1 3 7 15 31]))
(def __
(fn [coll]
(let [

      binary (fn  [n]
               (loop [n n lst []]
                 (if (= n 0) (vec (reverse lst)) 
                   (recur (quot n 2) (conj lst (mod n 2))))))
      binarys (mapv binary coll)
      max-size (apply max (map count binarys ))
      resize #(vec (concat (repeat (- max-size (count %)) 0) %))
      table (mapv resize binarys)
      m (count table)
      n (count (first table))
      dir-range (fn [start end dir] 
                  (if (= start end) [start]
                    (->> start
                      (iterate #(mapv + % dir)) 
                      (partition-by #(= end %))
                      (take 2)
                      (apply concat)))
                  )
      dir-iterate (fn [point [inc-start inc-end] dir]
                    (map #(dir-range (mapv + point (mapv * [% %] inc-start))
                                     (mapv + point  (mapv * [% %] inc-end))
                                     dir)
                         (range)))
      get-triangle-size (fn [point incremental dir]
                          (->>
                            (dir-iterate point incremental dir)
                            (partition-by (partial every? #(= (get-in table %) 1)))
                            first
                            count
                            (#(apply + (range (inc %))) )
                            ))
      max-triangle-size (fn [point]
                          (->> {[[ 1 0][0  1]] [-1  1]
                                [[ 1 0][0 -1]] [-1 -1]
                                [[-1 0][0  1]] [ 1  1]
                                [[-1 0][0 -1]] [ 1 -1]
                               }
                            (apply list)
                            (map (fn [[incremental dir]] 
                                   (get-triangle-size point incremental dir)))
                            (apply max)))
      ]
  (->>
  (for [i (range m) j (range n)]
    (max-triangle-size [i j] )
    )
    (apply max))
)
)
;straith
     [[-1 1] [1 1]] [1 0] 
                                [[-1 -1] [1 -1]] [1 0] 
                                [[1 -1] [1 1]] [0 1] 
                                [[-1 -1] [-1 1]] [0 1]
                            
(__ [7 6 4])
(__ [1 3 7])
{[1 1] [-1 1]
 [1 -1] [-1 -1] 
 [-1 1] [1 1]
 [-1 -1] [1 -1]}

dir-iterate (fn [point [inc-start inc-end] dir]
              (map #(dir-range (mapv + point (mapv * [% %] inc-start))
                               (mapv + point  (mapv * [% %] inc-end))
                               dir)
                   (range)))
get-triangle-size (fn [point incremental dir]
                    (->>
                      (dir-iterate point incremental dir)
                      (partition-by (partial every? #(= (get-in table %) 1)))
                      first
                      count
                      (#(apply + (range (inc %))) )
                      ))
max-triangle-size (fn [point]
                    (->> {[[ 1 0][0  1]] [-1  1]
                          [[ 1 0][0 -1]] [-1 -1]
                          [[-1 0][0  1]] [ 1  1]
                          [[-1 0][0 -1]] [ 1 -1]}


(Math/sin 6.28)


(map (partial every? #(= (get-in table %) 1))
'(([0 1] [1 0]) ([0 2] [1 1] [2 0]) ([0 3] [1 2] [2 1] [3 0]) ([0 4] [1 3] [2 2] [3 1] [4 0]) ([0 5] [1 4] [2 3] [3 2] [4 1] [5 0]))  ))
(map (partial every? vector?)  
'(([0 1] [1 0]) ([0 2] [1 1] [2 0]) ([0 3] [1 2] [2 1] [3 0]) ([0 4] [1 3] [2 2] [3 1] [4 0]) ([0 5] [1 4] [2 3] [3 2] [4 1] [5 0]))  ))
(every? vector? 
'([0 1] [1 0])
)
(apply + (range 10))


    (partition-by (partial every? #(= (get-in table %) 1))) 
  (def table [[1 1 1][1 1 0][1 0 0]])
(get-in
  table
  [0 2]
  )
[[0 2] [1 1] [2 0]]
table
(take-while (partial every? #(= (get-in table %) 1)))
  table

(->>
        '((1) (1 0) (1 1) (1 0 0) (1 0 1) (1 1 0) (1 1 1) (1 0 0 0))
        )
(repeat 10 0)

1 1 1 
1 1 0
1 0 0
[0 0] [0+0 0] [0 0+0]
[0 1] [1 0]   => [0+1 0] [0 0+1]
[0 2] [1 1] [2 0] => [0+2 0] [0 0+2] {1 -1}
triangle top-left
(defn dir-range [start end dir] 
  (->>
    start
    (iterate #(mapv + % dir)) 
    (partition-by #(= end %))
    (take 2)
    (apply concat))
  )
(dir-range (mapv + [0 0]  [1 0])
           (mapv + [0 0]  [0 1])
           [-1 1])
(dir-range (mapv + [0 0]  [2 0])
           (mapv + [0 0]  [0 2])
           [-1 1])
(defn natural-sum [n] (/ (* n (inc n)) 2) )
(defn )
(natural-sum 5)
;これで三角形の個数を手に入れることができる。
(Math/pow 2 3)

(take-while (partial every? #(= (get-in table %) 1))
(dir-iterate [0 0] [1 1] [1 -1] )
(nth 1)
)
(dir)

(natural-sum 4)

(defn dir-iterate[point [incy incx] dir]
  (map
  #(dir-range (mapv + point  [0 (* % incx)])
             (mapv + point [(* % incy) 0])
             dir)
       [1 2])
  )

1 1 1
0 1 1 
0 0 1
[0 2] [0+0 2] [0 2+0]
[1 2] [0 1]   => [0+1 3] [0 3-1]
[2 2] [1 1] [0 0] => [0+2 0] [0 2-2] {-1 -1}
(dir-range (mapv + [0 2]  [1 0])
           (mapv + [0 2]  [0 -1])
           [-1 -1])
(dir-range (mapv + [0 2]  [2 0])
           (mapv + [0 2]  [0 -2])
           [-1 -1])
(defn dir-iterate[point [incy incx] dir]
  (map
  #(dir-range (mapv + point  [0 (* % incx)])
             (mapv + point [(* % incy) 0])
             dir)
       [1 2])
  )
(def table [[1 1 1] [0 1 1] [0 0 1])


1 0 0
1 1 0 
1 1 1
[2 0]
[1 0] [2 1] => [2-1 0] [2 0+1]
[0 0] [1 1] [2 2] => [2-2 0] [2 0+2]
(dir-range (mapv + [2 0]  [-1 0])
           (mapv + [2 0]  [0 1])
           [1 1])
(dir-range (mapv + [2 0]  [-2 0])
           (mapv + [2 0]  [0 2])
           [1 1])



0 0 1
0 1 1 
1 1 1
[2 2]
[1 2] [2 1] => [2-1 2] [2 2-1]
(dir-range (mapv + [2 2]  [-1 0])
           (mapv + [2 2]  [0 -1])
           [1 -1])
(dir-range (mapv + [2 2]  [-2 0])
           (mapv + [2 2]  [0 -2])
           [1 -1])


0 0 0 1
0 0 1 1
0 1 1 1
0 0 1 1
0 0 0 1
            [2 1] => [2-0 1+0] [2+0 1+0]
      [1 2] [2 2] [3 2] => [2-1 1+1] [2-1+(2*1) 1+1] => {1 0}
[0 3] [1 3] [2 3] [3 3] [4 3] => [2-2 1] [2-2+(2*2) 1+2] => {1 0}
[2-i  1+i] [2+i 2+i]
=>> [y+-i x+i]
right
[[-1 1] [1 1]] [1 0] 

=>>[y+-i x-i]
left
[[-1 -1] [1 -1]] [1 0] 

=>>[y+i x+-i]
top
[[1 -1] [1 1]] [0 1] 

=>>[y-i x+-i]
down
[[-1 -1] [-1 1]] [0 1] 








test not run  
(= 10 (__ [15 15 15 15 15]))
; 1111      1111
; 1111      *111
; 1111  ->  **11
; 1111      ***1
; 1111      ****
test not run  
(= 15 (__ [1 3 7 15 31]))
; 00001      0000*
; 00011      000**
; 00111  ->  00***
; 01111      0****
; 11111      *****
test not run  
(= 3 (__ [3 3]))
; 11      *1
; 11  ->  **
test not run  
(= 4 (__ [7 3]))
; 111      ***
; 011  ->  0*1
test not run  
(= 6 (__ [17 22 6 14 22]))
; 10001      10001
; 10110      101*0
; 00110  ->  00**0
; 01110      0***0
; 10110      10110
test not run  
(= 9 (__ [18 7 14 14 6 3]))
; 10010      10010
; 00111      001*0
; 01110      01**0
; 01110  ->  0***0
; 00110      00**0
; 00011      000*1
test not run  
(= nil (__ [21 10 21 10]))
; 10101      10101
; 01010      01010
; 10101  ->  10101
; 01010      01010
test not run  
(= nil (__ [0 31 0 31 0]))
; 00000      00000
; 11111      11111
; 00000  ->  00000
; 11111      11111
; 00000      00000

