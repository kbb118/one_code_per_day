;;;; Land of Lisp 写経

;; This data structure is called association list (alist).
(defparameter *nodes* '((living-room (you are in the living-room.
                                        a wizard is snoring loudly on the couch.))
                       (garden (you are in a beautiful garden.
                                    there is a well in front of you.))
                       (attic (you are in the attic.
                                   there is a giant welding torch in the corner.))))

(defun describe-location (location nodes)
  (cadr (assoc location nodes)))

(defparameter *edges* '((living-room (garden west door)
                                    (attic upstairs ladder))
                       (garden (living-room east door))
                       (attic (living-room downstaris ladder))))

; 準クオート ruby で言う変数展開かな？でも文字列じゃないし、違うかな
(defun describe-path (edge)
  `(there is a ,(caddr edge) going ,(cadr edge) from here.))

;; プレーヤーの現在の場所とゲームマップのエッジ(通り道)のalistを受取り、現在の場所からのすべての通り道を返す。
(defun describe-paths (location edges)
  (apply #'append (mapcar #'describe-path (cdr (assoc location edges)))))

; mapcar は 引数に他の関数とリストを受け取って、リストの要素一つ一つについてそれを引数として受け取った関数を呼び出す。
; このような他の関数を引数に受け取る関数を高階関数と呼ぶ
(mapcar #'sqrt '(1 2 3 4 5))
(mapcar #'car '((foo bar) (baz piyo)))
; #'hoge は単に (function hoge) の略記
(mapcar (function car) '((foo bar) (baz piyo)))

; プレーヤーが手に取って使うことのできるオブジェクト(アイテム)
(defparameter *objects* '(whiskey bucket frog chain))
(defparameter *object-locations* '((whiskey living-room)
                                   (bucket living-room)
                                   (chain garden)
                                   (frog garden)))
(defun objects-at (loc objs obj-locs)
  (labels ((at-loc-p (obj) ; 真偽値を返す関数は -p をつける慣わし
              (eq (cadr (assoc obj obj-locs)) loc)))
    (remove-if-not #'at-loc-p objs))) ; 真を返す要素だけをフィルタする

(defun describe-objects (loc objs obj-loc)
  (labels ((describe-obj (obj)
            `(you see a ,obj on the floor.)))
    (apply #'append (mapcar #'describe-obj (objects-at loc objs obj-loc)))))

(defparameter *location* 'living-room)

(defun look()
  (append (describe-location *location* *nodes*)
          (describe-paths *location* *edges*)
          (describe-objects *location* *objects* *object-locations*)))

(print (look))
