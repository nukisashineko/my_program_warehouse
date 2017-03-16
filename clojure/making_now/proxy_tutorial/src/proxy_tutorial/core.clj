(ns proxy-tutorial.core)

; [proxy – gen-class little brother](http://kotka.de/blog/2010/03/proxy_gen-class_little_brother.html)

(letfn  [(make-some-example [] 
           (proxy [Object] []
             (toString [] "Hello, World!"))) ]
  (.toString (make-some-example)))

(letfn  [(make-some-example [] 
           (proxy [clojure.lang.IDeref] []
             (deref [] "Hello, World!"))) ]
  @(make-some-example))


(letfn [(make-some-example [msg]
          (proxy [clojure.lang.IDeref] []
            (deref [] msg))) ]
  @(make-some-example "Hello World!!"))


(letfn [(make-some-example [msg]
          (let [state (atom msg)]
            (proxy [clojure.lang.IDeref] []
              (toString [] @state)
              (deref [] state)
              )))]
  (let [o (make-some-example "Hallo, Weit!")]
    (println (.toString o))
    (println (reset! @o "Здравей, свят" ))
    (println (.toString o))
    ));to change atom msg


;super methods
(letfn [(make-offset-reader [reader offset]
          (proxy [clojure.lang.LineNumberingPushbackReader] [reader]
            (getLineNumber [] (+ offset (proxy-super get LineNumber)))))]
  )


;class Example {
;               void someMethod(String x) {
;                                          doSomethingWithString(x);
;                                          }
;
;               void someMethod(Integer x) {
;                                           doSomethingWithInteger(x);
;                                           }
;               }

(proxy [Example] []
  (someMethod [x]
    (comdp instance x 
           String (.doSomethingWithString this x)
           Integer (.doSomethingWithInteger this x)
           )))


;class Example {
;                   void someMethod(String x) {
;                                                      someMethod(x, null)
;                                                  }
;
;                   void someMethod(String x, String y) {
;                                                                doSomethingWith(x, y);
;                                                            }
;               }


(proxy [Example] []
    (someMethod
          ([x]   (proxy-super someMethod x))
          ([x y] (.doMoreStuff this x y))))

(proxy  [Example] []
  (someMethod 
    ([x] (proxy-super someMethod x))
    ([x y] (.doMoreStuff this x y))))




(fn []
    (let [a ["(fn [] (let [a "
                      "] (apply str (a 0) a (a 1))))"]] (apply str (a 0) a (a 1))))
