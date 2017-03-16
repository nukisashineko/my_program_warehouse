(ns hello.core
        (:gen-class))

(defn foo
  "I don't do a whole lot."
  [x]
  (println x "Hello, World!"))
(defn -main
        "Application entry point"
        [name]
        (foo name))


(def tttt (->> "aaa" (partition-by identity) (first)))
