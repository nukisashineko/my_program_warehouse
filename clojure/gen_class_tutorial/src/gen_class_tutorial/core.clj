;(ns gen-class-tutorial.core)

;[ClojureでJavaのクラスを作る - CLOVER](http://d.hatena.ne.jp/Kazuhira/20121027/1351328382)


(ns gen-class-tutorial.core
    (:gen-class
         :methods [#^{:static true} [bar [String] String]
                                #^{:static true}[fuga [] void]
                                [echo [String] String]]))

(defn -main [] (println "Hello World Main Method"))
(defn -bar [name] (str "Hello World By " name " !!"))
(defn -fuga [] (println "Hello World"))

(defn -echo [this param] param)




